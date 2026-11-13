#ifndef BATTERY_H
#define BATTERY_H
#include "robot_state.h"
#ifndef BATTERY_HOST_TEST
#include "main.h"
extern ADC_HandleTypeDef hadc1;
#endif

/* ---- Hardware config: EDIT TO MATCH YOUR BOARD / PACK / BMS ----------
 * Divider: Vadc = Vpack * R_BOT / (R_TOP + R_BOT)
 * Keep Vadc below ADC Vref at full-charge voltage.
 */
#define BATT_ADC_VREF_MV        3300.0f
#define BATT_ADC_MAX_COUNTS     4095.0f     /* 12-bit */
#define BATT_DIV_R_TOP_OHM      30000.0f    /* TODO verify */
#define BATT_DIV_R_BOT_OHM      10000.0f    /* TODO verify */
#define BATT_ADC_OVERSAMPLE     16
#define BATT_CELL_COUNT         3           /* TODO verify (e.g. 3S) */

/* Per-cell thresholds. Defaults are generic Li-ion; replace with the
 * values from the cell datasheet AND the BMS cutoff settings.      */
#define BATT_CELL_MAX_V         4.25f       /* above => out of range */
#define BATT_CELL_MIN_V         2.50f       /* below => out of range */
#define BATT_CELL_LOW_V         3.50f       /* warn                   */
#define BATT_CELL_CRIT_V        3.30f       /* stop motion (> BMS cutoff) */
#define BATT_HYSTERESIS_V       0.05f       /* per cell               */


void battery_init(void);
/* Samples ADC, scales, classifies. Returns the new reading. */
battery_data_t battery_read(uint32_t now_ms);
float battery_counts_to_pack_v(float counts);   /* exposed for unit tests */
#endif
