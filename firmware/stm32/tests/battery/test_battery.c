#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "battery.h"
#include "mock_adc.h"

#define TEST_ASSERT(condition, name)                  \
    do                                                \
    {                                                 \
        if (!(condition))                             \
        {                                             \
            printf("[FAIL] %s (line %d)\n",            \
                   name, __LINE__);                   \
            failed++;                                 \
        }                                             \
        else                                          \
        {                                             \
            printf("[PASS] %s\n", name);              \
            passed++;                                 \
        }                                             \
    } while (0)

static int passed = 0;
static int failed = 0;

/* Prepare 16 identical ADC samples. */
static void prepare_constant_samples(uint16_t counts)
{
    uint16_t samples[BATT_ADC_OVERSAMPLE];

    for (uint32_t i = 0U; i < BATT_ADC_OVERSAMPLE; i++)
    {
        samples[i] = counts;
    }

    mock_adc_reset();
    mock_adc_set_samples(samples, BATT_ADC_OVERSAMPLE);
}

/* Convert a desired cell voltage into a rounded ADC count. */
static uint16_t counts_for_cell_voltage(float cell_v)
{
    float pack_v = cell_v * (float)BATT_CELL_COUNT;

    float counts =
        pack_v *
        BATT_ADC_MAX_COUNTS *
        BATT_DIV_R_BOT_OHM /
        ((BATT_ADC_VREF_MV / 1000.0f) *
         (BATT_DIV_R_TOP_OHM + BATT_DIV_R_BOT_OHM));

    return (uint16_t)(counts + 0.5f);
}

static void test_voltage_conversion(void)
{
    float counts = 2048.0f;

    float expected =
        (counts * (BATT_ADC_VREF_MV / 1000.0f) /
         BATT_ADC_MAX_COUNTS) *
        (BATT_DIV_R_TOP_OHM + BATT_DIV_R_BOT_OHM) /
        BATT_DIV_R_BOT_OHM;

    float actual = battery_counts_to_pack_v(counts);

    TEST_ASSERT(fabsf(actual - expected) < 0.001f,
                "ADC counts to pack voltage conversion");
}

static void test_adc_boundaries(void)
{
    const uint16_t boundary_values[] =
    {
        0U, 1U, 4094U, 4095U
    };

    const char *names[] =
    {
        "ADC zero boundary",
        "ADC minimum positive boundary",
        "ADC near maximum boundary",
        "ADC maximum boundary"
    };

    for (uint32_t i = 0U; i < 4U; i++)
    {
        prepare_constant_samples(boundary_values[i]);
        battery_init();

        battery_data_t d = battery_read(100U);

        TEST_ASSERT(d.status == MEAS_OUT_OF_RANGE, names[i]);
    }

    /* The ADC is 12-bit, so 4096 is an invalid raw input.
       The battery layer must reject its resulting voltage. */
    prepare_constant_samples(4096U);
    battery_init();

    battery_data_t d = battery_read(200U);

    TEST_ASSERT(d.status == MEAS_OUT_OF_RANGE,
                "ADC count above 12-bit range rejected");
}

static void test_oversampling_average(void)
{
    uint16_t samples[BATT_ADC_OVERSAMPLE];

    for (uint32_t i = 0U; i < BATT_ADC_OVERSAMPLE; i++)
    {
        samples[i] = (i % 2U == 0U) ? 3400U : 3480U;
    }

    mock_adc_reset();
    mock_adc_set_samples(samples, BATT_ADC_OVERSAMPLE);
    battery_init();

    battery_data_t d = battery_read(300U);

    float expected = battery_counts_to_pack_v(3440.0f);

    TEST_ASSERT(d.status == MEAS_OK,
                "Oversampling produces a valid measurement");

    TEST_ASSERT(fabsf(d.pack_v - expected) < 0.001f,
                "Oversampling calculates correct average");

    TEST_ASSERT(mock_adc_get_read_count() == BATT_ADC_OVERSAMPLE,
                "Exactly 16 ADC samples are read");

}

static void test_adc_failures(void)
{
    uint16_t samples[BATT_ADC_OVERSAMPLE];

    for (uint32_t i = 0U; i < BATT_ADC_OVERSAMPLE; i++)
    {
        samples[i] = 3440U;
    }

    /* Simulate failure on the first sample. */
    mock_adc_reset();
    mock_adc_set_samples(samples, BATT_ADC_OVERSAMPLE);
    mock_adc_set_failure(MOCK_ADC_START_FAIL, 0U);
    battery_init();

    battery_data_t d = battery_read(400U);

    TEST_ASSERT(d.status == MEAS_UNAVAILABLE,
                "ADC start failure is reported as unavailable");

    TEST_ASSERT(mock_adc_get_read_count() == 0U,
                "No samples read after first-sample start failure");

    /* Simulate timeout after five successful samples. */
    mock_adc_reset();
    mock_adc_set_samples(samples, BATT_ADC_OVERSAMPLE);
    mock_adc_set_failure(MOCK_ADC_TIMEOUT, 5U);
    battery_init();

    d = battery_read(500U);

    TEST_ASSERT(d.status == MEAS_UNAVAILABLE,
                "ADC conversion timeout is reported as unavailable");

    TEST_ASSERT(mock_adc_get_read_count() == 5U,
                "Reading stops after the injected timeout");
}

static void test_battery_classification(void)
{
    battery_data_t d;

    battery_init();
    prepare_constant_samples(counts_for_cell_voltage(3.80f));
    d = battery_read(600U);

    TEST_ASSERT(d.status == MEAS_OK && d.level == BATT_OK,
                "Normal cell voltage classified as OK");

    battery_init();
    prepare_constant_samples(counts_for_cell_voltage(3.40f));
    d = battery_read(700U);

    TEST_ASSERT(d.status == MEAS_OK && d.level == BATT_LOW,
                "Low cell voltage classified as LOW");

    battery_init();
    prepare_constant_samples(counts_for_cell_voltage(3.20f));
    d = battery_read(800U);

    TEST_ASSERT(d.status == MEAS_OK && d.level == BATT_CRITICAL,
                "Critical cell voltage classified as CRITICAL");
}

static void test_hysteresis(void)
{
    battery_data_t d;

    /* Enter CRITICAL, then test the recovery hysteresis. */
    battery_init();

    prepare_constant_samples(counts_for_cell_voltage(3.20f));
    d = battery_read(900U);

    TEST_ASSERT(d.level == BATT_CRITICAL,
                "Battery enters CRITICAL state");

    prepare_constant_samples(counts_for_cell_voltage(3.34f));
    d = battery_read(1000U);

    TEST_ASSERT(d.level == BATT_CRITICAL,
                "CRITICAL state retained inside hysteresis band");

    prepare_constant_samples(counts_for_cell_voltage(3.36f));
    d = battery_read(1100U);

    TEST_ASSERT(d.level == BATT_LOW,
                "CRITICAL state recovers to LOW above hysteresis band");

    /* Enter LOW, then test the LOW recovery hysteresis. */
    battery_init();

    prepare_constant_samples(counts_for_cell_voltage(3.40f));
    d = battery_read(1200U);

    TEST_ASSERT(d.level == BATT_LOW,
                "Battery enters LOW state");

    prepare_constant_samples(counts_for_cell_voltage(3.54f));
    d = battery_read(1300U);

    TEST_ASSERT(d.level == BATT_LOW,
                "LOW state retained inside hysteresis band");

    prepare_constant_samples(counts_for_cell_voltage(3.56f));
    d = battery_read(1400U);

    TEST_ASSERT(d.level == BATT_OK,
                "LOW state recovers to OK above hysteresis band");
}

static void test_measurement_metadata(void)
{
    prepare_constant_samples(counts_for_cell_voltage(3.80f));
    battery_init();

    battery_data_t d = battery_read(12345U);

    TEST_ASSERT(d.status == MEAS_OK,
                "Valid measurement status");

    TEST_ASSERT(d.timestamp_ms == 12345U,
                "Valid measurement timestamp");

    TEST_ASSERT(d.level == BATT_OK,
                "Valid measurement battery level");
}
static void test_incomplete_adc_samples(void)
{
    uint16_t samples[BATT_ADC_OVERSAMPLE - 1U];

    for (uint32_t i = 0U; i < BATT_ADC_OVERSAMPLE - 1U; i++)
    {
        samples[i] = 3440U;
    }

    mock_adc_reset();
    mock_adc_set_samples(samples, BATT_ADC_OVERSAMPLE - 1U);
    battery_init();

    battery_data_t d = battery_read(1500U);

    TEST_ASSERT(d.status == MEAS_UNAVAILABLE,
                "Incomplete ADC samples reported as unavailable");

    TEST_ASSERT(mock_adc_get_read_count() == BATT_ADC_OVERSAMPLE - 1U,
                "Reading stops when ADC samples are exhausted");
}
static void test_failed_read_preserves_previous_level(void)
{
    battery_data_t d;
    uint16_t samples[BATT_ADC_OVERSAMPLE];

    battery_init();

    prepare_constant_samples(counts_for_cell_voltage(3.20f));
    d = battery_read(1600U);

    TEST_ASSERT(d.level == BATT_CRITICAL,
                "Initial valid reading establishes CRITICAL state");

    for (uint32_t i = 0U; i < BATT_ADC_OVERSAMPLE; i++)
    {
        samples[i] = counts_for_cell_voltage(3.34f);
    }

    mock_adc_reset();
    mock_adc_set_samples(samples, BATT_ADC_OVERSAMPLE);
    mock_adc_set_failure(MOCK_ADC_TIMEOUT, 0U);

    d = battery_read(1700U);

    TEST_ASSERT(d.status == MEAS_UNAVAILABLE,
                "Failed reading is marked unavailable");

    TEST_ASSERT(d.level == BATT_UNKNOWN,
                "Failed reading does not report a valid battery level");

    prepare_constant_samples(counts_for_cell_voltage(3.34f));
    d = battery_read(1800U);

    TEST_ASSERT(d.status == MEAS_OK &&
                d.level == BATT_CRITICAL,
                "Previous CRITICAL state preserved after failed reading");
}
static void test_full_battery_recovery(void)
{
    battery_data_t d;

    battery_init();

    prepare_constant_samples(counts_for_cell_voltage(3.20f));
    d = battery_read(1900U);

    TEST_ASSERT(d.level == BATT_CRITICAL,
                "Full recovery starts at CRITICAL");

    prepare_constant_samples(counts_for_cell_voltage(3.36f));
    d = battery_read(2000U);

    TEST_ASSERT(d.level == BATT_LOW,
                "Battery recovers from CRITICAL to LOW");

    prepare_constant_samples(counts_for_cell_voltage(3.56f));
    d = battery_read(2100U);

    TEST_ASSERT(d.level == BATT_OK,
                "Battery recovers from LOW to OK");
}
int main(void)
{
    printf("\n");
    printf("========================================\n");
    printf("     BATTERY HOST UNIT TESTS\n");
    printf("========================================\n\n");

    test_voltage_conversion();
    test_adc_boundaries();
    test_oversampling_average();
    test_adc_failures();
    test_battery_classification();
    test_hysteresis();
    test_measurement_metadata();
    test_incomplete_adc_samples();
    test_failed_read_preserves_previous_level();
    test_full_battery_recovery();

    printf("\n========================================\n");
    printf("             TEST REPORT\n");
    printf("========================================\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("Total : %d\n", passed + failed);
    printf("========================================\n");

    return (failed == 0) ? 0 : 1;
}
