#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include <stdint.h>
#include <stdbool.h>

/* Common measurement status used by every sensor. */
typedef enum {
    MEAS_OK = 0,
    MEAS_NEVER_VALID,    /* no valid sample since boot            */
    MEAS_STALE,          /* last valid sample older than max age  */
    MEAS_UNAVAILABLE,    /* bus errors / sensor not responding    */
    MEAS_OUT_OF_RANGE    /* sample read but physically implausible*/
} meas_status_t;

typedef struct {
    float accel_g[3];        /* g,   +/-4 g full scale      */
    float gyro_dps[3];       /* deg/s, +/-500 dps full scale */
    float temp_c;            /* degC                         */
    uint32_t timestamp_ms;   /* time of last VALID sample    */
    meas_status_t status;
} imu_data_t;

typedef enum { BATT_OK = 0, BATT_LOW, BATT_CRITICAL, BATT_UNKNOWN } batt_level_t;

typedef struct {
    float pack_v;            /* V (pack, after divider scaling) */
    float cell_v;            /* V (pack_v / cell count)         */
    batt_level_t level;
    uint32_t timestamp_ms;
    meas_status_t status;
} battery_data_t;

typedef struct {
    imu_data_t     imu;
    battery_data_t battery;
    uint32_t       last_update_ms;
} robot_state_t;

void robot_state_init(void);
const robot_state_t *robot_state_get(void);
void robot_state_set_imu(const imu_data_t *d);
void robot_state_set_battery(const battery_data_t *d);
/* True only if every input needed for motion is OK. */
bool robot_state_sensors_healthy(void);
#endif
