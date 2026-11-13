#include "sensor_manager.h"
#include "imu.h"
#include "battery.h"
#include "robot_state.h"

static uint32_t s_next_imu, s_next_batt, s_next_reinit;
static uint8_t  s_imu_fails, s_batt_fails;
static bool     s_imu_present;
static sensor_stats_t s_stats;

/* Signed-safe elapsed time for 32-bit ms tick wraparound. */
static bool due(uint32_t now, uint32_t t) { return (int32_t)(now - t) >= 0; }

void sensor_manager_init(uint32_t now_ms)
{
    robot_state_init();
    battery_init();
    s_imu_present = (imu_init() == IMU_OK);
    s_next_imu = s_next_batt = now_ms;
    s_next_reinit = now_ms + IMU_REINIT_PERIOD_MS;
}

static void age_check(uint32_t now)
{
    const robot_state_t *rs = robot_state_get();

    if (rs->imu.status == MEAS_OK && (now - rs->imu.timestamp_ms) > IMU_MAX_AGE_MS) {
        imu_data_t d = rs->imu; d.status = MEAS_STALE; robot_state_set_imu(&d);
    }
    if (rs->battery.status == MEAS_OK && (now - rs->battery.timestamp_ms) > BATT_MAX_AGE_MS) {
        battery_data_t b = rs->battery; b.status = MEAS_STALE; b.level = BATT_UNKNOWN;
        robot_state_set_battery(&b);
    }
}

void sensor_manager_tick(uint32_t now)
{
    if (s_imu_present && due(now, s_next_imu)) {
        s_next_imu += IMU_PERIOD_MS;
        if ((int32_t)(now - s_next_imu) > 0) s_next_imu = now + IMU_PERIOD_MS; /* avoid burst catch-up */

        imu_data_t d = robot_state_get()->imu;
        imu_result_t r = imu_read(&d, now);
        if (r == IMU_OK) {
            s_imu_fails = 0; s_stats.imu_ok++;
            robot_state_set_imu(&d);
        } else {
            r == IMU_ERR_BUS ? s_stats.imu_bus_err++ : s_stats.imu_range_err++;
            if (++s_imu_fails >= SENSOR_FAIL_LIMIT) {
                d = robot_state_get()->imu;
                d.status = (r == IMU_ERR_BUS) ? MEAS_UNAVAILABLE : MEAS_OUT_OF_RANGE;
                robot_state_set_imu(&d);
                if (r == IMU_ERR_BUS) s_imu_present = false;   /* go to re-init path */
            }
        }
    }

    if (!s_imu_present && due(now, s_next_reinit)) {
        s_next_reinit = now + IMU_REINIT_PERIOD_MS;
        if (imu_init() == IMU_OK) { s_imu_present = true; s_imu_fails = 0; }
        else {
            imu_data_t d = robot_state_get()->imu;
            d.status = MEAS_UNAVAILABLE; robot_state_set_imu(&d);
        }
    }

    if (due(now, s_next_batt)) {
        s_next_batt = now + BATT_PERIOD_MS;
        battery_data_t b = battery_read(now);
        if (b.status == MEAS_OK) {
            s_batt_fails = 0; s_stats.batt_ok++;
            robot_state_set_battery(&b);
        } else {
            s_stats.batt_err++;
            if (++s_batt_fails >= SENSOR_FAIL_LIMIT) {
                b.level = BATT_UNKNOWN;
                robot_state_set_battery(&b);   /* carries UNAVAILABLE / OUT_OF_RANGE */
            }
        }
    }

    age_check(now);
}

const sensor_stats_t *sensor_manager_stats(void) { return &s_stats; }
