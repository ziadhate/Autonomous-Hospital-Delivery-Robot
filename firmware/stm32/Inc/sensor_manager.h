#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H
#include <stdint.h>

/* Update rates and freshness limits */
#define IMU_PERIOD_MS            10     /* 100 Hz */
#define BATT_PERIOD_MS          100     /* 10 Hz  */
#define IMU_MAX_AGE_MS           50     /* stale after 5 missed samples */
#define BATT_MAX_AGE_MS         500
#define SENSOR_FAIL_LIMIT         3     /* consecutive failures => UNAVAILABLE */
#define IMU_REINIT_PERIOD_MS   1000     /* retry init while unavailable */

void sensor_manager_init(uint32_t now_ms);
/* Call from main loop (or a periodic task). Non-blocking apart from short I2C/ADC transfers. */
void sensor_manager_tick(uint32_t now_ms);

typedef struct {
    uint32_t imu_ok, imu_bus_err, imu_range_err;
    uint32_t batt_ok, batt_err;
} sensor_stats_t;
const sensor_stats_t *sensor_manager_stats(void);
#endif
