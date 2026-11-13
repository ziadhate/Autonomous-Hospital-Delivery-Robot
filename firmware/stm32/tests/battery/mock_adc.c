#include "mock_adc.h"

#define MOCK_ADC_MAX_SAMPLES 256U

static uint16_t s_samples[MOCK_ADC_MAX_SAMPLES];
static uint32_t s_sample_count = 0U;
static uint32_t s_sample_index = 0U;

static uint32_t s_read_count = 0U;

static mock_adc_status_t s_failure = MOCK_ADC_OK;
static uint32_t s_failure_index = 0U;


void mock_adc_reset(void)
{
    s_sample_count = 0U;
    s_sample_index = 0U;
    s_read_count = 0U;
    s_failure = MOCK_ADC_OK;
    s_failure_index = 0U;
}

void mock_adc_set_samples(const uint16_t *samples, uint32_t count)
{
    if ((samples == 0) || (count > MOCK_ADC_MAX_SAMPLES))
    {
        s_sample_count = 0U;
        return;
    }

    for (uint32_t i = 0U; i < count; i++)
    {
        s_samples[i] = samples[i];
    }

    s_sample_count = count;
    s_sample_index = 0U;
}

void mock_adc_set_failure(mock_adc_status_t failure, uint32_t sample_index)
{
    s_failure = failure;
    s_failure_index = sample_index;
}

bool mock_adc_read(uint16_t *value)
{
    if (value == 0)
    {
        return false;
    }

    if (s_sample_index >= s_sample_count)
    {
        return false;
    }

    if ((s_failure != MOCK_ADC_OK) &&
        (s_sample_index == s_failure_index))
    {
        return false;
    }

    *value = s_samples[s_sample_index];

    s_sample_index++;
    s_read_count++;

    return true;
}

uint32_t mock_adc_get_read_count(void)
{
    return s_read_count;
}
