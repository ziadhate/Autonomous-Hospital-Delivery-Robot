#ifndef IMU_H
#define IMU_H
#include "robot_state.h"
#include "main.h"

/* ASSUMED SENSOR: MPU-6050/MPU-6500-class 6-axis IMU on I2C. CONFIRM MODEL.
 * Interface : I2C @ 400 kHz, 7-bit addr 0x68 (AD0 low)
 * Accel     : +/-4 g   -> 8192 LSB/g      valid |a| <= 4.0 g (per axis)
 * Gyro      : +/-500 dps -> 65.5 LSB/dps  valid |w| <= 500 dps
 * Temp      : raw/340 + 36.53 degC         valid -40..85 degC
 * Output rate: 100 Hz (SMPLRT_DIV with DLPF on: 1 kHz/(1+9))           */
#define IMU_I2C_ADDR_7BIT   0x68
#define IMU_I2C_TIMEOUT_MS  5
#define IMU_ACCEL_LSB_PER_G 8192.0f
#define IMU_GYRO_LSB_PER_DPS 65.5f
#define IMU_ACCEL_MAX_G     4.0f
#define IMU_GYRO_MAX_DPS    500.0f
#define IMU_TEMP_MIN_C     (-40.0f)
#define IMU_TEMP_MAX_C      85.0f

extern I2C_HandleTypeDef hi2c1;   /* from CubeMX */

typedef enum { IMU_OK = 0, IMU_ERR_BUS, IMU_ERR_ID, IMU_ERR_RANGE } imu_result_t;

imu_result_t imu_init(void);
imu_result_t imu_read(imu_data_t *out, uint32_t now_ms);
/* Pure conversion, exposed for unit tests. */
void imu_convert(const uint8_t raw[14], imu_data_t *out);
#endif
