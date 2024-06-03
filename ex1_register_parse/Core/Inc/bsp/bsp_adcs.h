/*
 * bsp_adcs.h
 *
 *  Created on: May 30, 2024
 *      Author: henry
 */

#ifndef INC_BSP_BSP_ADCS_H_
#define INC_BSP_BSP_ADCS_H_

// from tt_parser/
#include "adcs_register.h"
// from std c
#include <stdbool.h>

// typedef
typedef enum
{
	MODE_SAFE = 0,
	MODE_DETUMBLING = 1,
	MODE_SUN_POINTING = 2,
	MODE_FINE_POINTING = 3,
	MODE_LVLH = 4,
	MODE_TARGET_TRACKING = 5,
	MODE_SUN_SPINING = 6,
	MODE_MANUAL = 7,
} ConfMode;

void BspAdcsInit();
void BspAdcsTask();

// User Map
void BspAdcsGetSNID(reg_snid_t *snid);
bool BspAdcsSetMode(ConfMode mode);

bool BspAdcsSetCmgGRateUser(uint8_t id, float gimbal_rate);
bool BspAdcsSetCmgWTorqueUser(uint8_t id, float wheel_torque);

void BspAdcsGetSTAT(reg_status_t *status);

// Sen/Act Map
void BspAdcsGetIMUx_S(uint8_t id, reg_imux_s_t *imu_s);

#endif /* INC_BSP_BSP_ADCS_H_ */
