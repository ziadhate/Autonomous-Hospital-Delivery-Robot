#include "battery.h"

static batt_level_t s_level = BATT_UNKNOWN;

void battery_init(void) { s_level = BATT_UNKNOWN; }

float battery_counts_to_pack_v(float counts)
{
    float v_adc = counts * (BATT_ADC_VREF_MV / 1000.0f) / BATT_ADC_MAX_COUNTS;
    return v_adc * (BATT_DIV_R_TOP_OHM + BATT_DIV_R_BOT_OHM) / BATT_DIV_R_BOT_OHM;
}

static bool adc_sample(float *avg_counts)
{
    uint32_t sum = 0;
    for (int i = 0; i < BATT_ADC_OVERSAMPLE; i++) {
        if (HAL_ADC_Start(&hadc1) != HAL_OK) return false;
        if (HAL_ADC_PollForConversion(&hadc1, 2) != HAL_OK) {
            HAL_ADC_Stop(&hadc1);
            return false;
        }
        sum += HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
    }
    *avg_counts = (float)sum / BATT_ADC_OVERSAMPLE;
    return true;
}

static batt_level_t classify(float cell_v, batt_level_t prev)
{
    /* Hysteresis on the way back up so level doesn't chatter. */
    float h = BATT_HYSTERESIS_V;
    if (cell_v < BATT_CELL_CRIT_V) return BATT_CRITICAL;
    if (prev == BATT_CRITICAL && cell_v < BATT_CELL_CRIT_V + h) return BATT_CRITICAL;
    if (cell_v < BATT_CELL_LOW_V) return BATT_LOW;
    if (prev == BATT_LOW && cell_v < BATT_CELL_LOW_V + h) return BATT_LOW;
    return BATT_OK;
}

battery_data_t battery_read(uint32_t now_ms)
{
    battery_data_t d = {0};
    d.level = BATT_UNKNOWN;
    float counts;
    if (!adc_sample(&counts)) {
        d.status = MEAS_UNAVAILABLE;
        return d;
    }
    d.pack_v = battery_counts_to_pack_v(counts);
    d.cell_v = d.pack_v / BATT_CELL_COUNT;
    if (d.cell_v > BATT_CELL_MAX_V || d.cell_v < BATT_CELL_MIN_V) {
        d.status = MEAS_OUT_OF_RANGE;   /* disconnected divider, wrong cell count, etc. */
        return d;
    }
    s_level = classify(d.cell_v, s_level);
    d.level = s_level;
    d.status = MEAS_OK;
    d.timestamp_ms = now_ms;
    return d;
}
