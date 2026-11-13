#include "imu.h"
#include <math.h>

#define REG_SMPLRT_DIV   0x19
#define REG_CONFIG       0x1A
#define REG_GYRO_CONFIG  0x1B
#define REG_ACCEL_CONFIG 0x1C
#define REG_ACCEL_XOUT_H 0x3B
#define REG_PWR_MGMT_1   0x6B
#define REG_WHO_AM_I     0x75
#define WHO_AM_I_EXPECT  0x68

#define ADDR (IMU_I2C_ADDR_7BIT << 1)

static HAL_StatusTypeDef wr(uint8_t reg, uint8_t v)
{
    return HAL_I2C_Mem_Write(&hi2c1, ADDR, reg, 1, &v, 1, IMU_I2C_TIMEOUT_MS);
}

imu_result_t imu_init(void)
{
    uint8_t id = 0;
    if (HAL_I2C_Mem_Read(&hi2c1, ADDR, REG_WHO_AM_I, 1, &id, 1, IMU_I2C_TIMEOUT_MS) != HAL_OK)
        return IMU_ERR_BUS;
    if (id != WHO_AM_I_EXPECT) return IMU_ERR_ID;

    if (wr(REG_PWR_MGMT_1, 0x80) != HAL_OK) return IMU_ERR_BUS;   /* reset */
    HAL_Delay(100);
    if (wr(REG_PWR_MGMT_1, 0x01) != HAL_OK) return IMU_ERR_BUS;   /* PLL clock, wake */
    if (wr(REG_CONFIG, 0x03) != HAL_OK) return IMU_ERR_BUS;       /* DLPF ~44 Hz, 1 kHz base */
    if (wr(REG_SMPLRT_DIV, 9) != HAL_OK) return IMU_ERR_BUS;      /* 100 Hz */
    if (wr(REG_GYRO_CONFIG, 0x08) != HAL_OK) return IMU_ERR_BUS;  /* +/-500 dps */
    if (wr(REG_ACCEL_CONFIG, 0x08) != HAL_OK) return IMU_ERR_BUS; /* +/-4 g */
    return IMU_OK;
}

static int16_t be16(const uint8_t *p) { return (int16_t)((p[0] << 8) | p[1]); }

void imu_convert(const uint8_t r[14], imu_data_t *o)
{
    for (int i = 0; i < 3; i++) {
        o->accel_g[i]  = be16(&r[2 * i])     / IMU_ACCEL_LSB_PER_G;
        o->gyro_dps[i] = be16(&r[8 + 2 * i]) / IMU_GYRO_LSB_PER_DPS;
    }
    o->temp_c = be16(&r[6]) / 340.0f + 36.53f;
}

imu_result_t imu_read(imu_data_t *out, uint32_t now_ms)
{
    uint8_t raw[14];
    if (HAL_I2C_Mem_Read(&hi2c1, ADDR, REG_ACCEL_XOUT_H, 1, raw, 14, IMU_I2C_TIMEOUT_MS) != HAL_OK)
        return IMU_ERR_BUS;

    imu_convert(raw, out);

    /* Range checks. A frozen/all-0xFF bus or saturated axis fails here. */
    for (int i = 0; i < 3; i++) {
        if (!isfinite(out->accel_g[i]) || fabsf(out->accel_g[i]) > IMU_ACCEL_MAX_G ||
            fabsf(out->gyro_dps[i]) > IMU_GYRO_MAX_DPS)
            return IMU_ERR_RANGE;
    }
    if (out->temp_c < IMU_TEMP_MIN_C || out->temp_c > IMU_TEMP_MAX_C) return IMU_ERR_RANGE;

    out->timestamp_ms = now_ms;
    out->status = MEAS_OK;
    return IMU_OK;
}
