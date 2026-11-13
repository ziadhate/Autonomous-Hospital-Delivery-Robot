#ifndef MOCK_ADC_H
#define MOCK_ADC_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    MOCK_ADC_OK = 0,
    MOCK_ADC_START_FAIL,
    MOCK_ADC_TIMEOUT
} mock_adc_status_t;

void mock_adc_reset(void);
void mock_adc_set_samples(const uint16_t *samples, uint32_t count);
void mock_adc_set_failure(mock_adc_status_t failure, uint32_t sample_index);

bool mock_adc_read(uint16_t *value);

uint32_t mock_adc_get_read_count(void);


#endif
