#include "robot_state.h"
#include <string.h>

static robot_state_t g_state;

void robot_state_init(void)
{
    memset(&g_state, 0, sizeof g_state);
    g_state.imu.status     = MEAS_NEVER_VALID;
    g_state.battery.status = MEAS_NEVER_VALID;
    g_state.battery.level  = BATT_UNKNOWN;
}
const robot_state_t *robot_state_get(void) { return &g_state; }
void robot_state_set_imu(const imu_data_t *d)     { g_state.imu = *d; }
void robot_state_set_battery(const battery_data_t *d) { g_state.battery = *d; }
bool robot_state_sensors_healthy(void)
{
    return g_state.imu.status == MEAS_OK &&
           g_state.battery.status == MEAS_OK &&
           g_state.battery.level != BATT_CRITICAL;
}
