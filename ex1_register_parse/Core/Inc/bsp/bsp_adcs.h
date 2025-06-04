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

typedef struct bsp_adcs
{
	reg_imu_stat_t IMU_STAT;
	reg_imux_s_t IMU_S[ADCS_XM_IMU_NUM];
} BspAdcsImuData;

void BspAdcsInit();
void BspAdcsTask();

/* ----- User Map getters ----- */ 

void BspAdcsGetFact(Fact *fact);
void BspAdcsGetSNID(Snid *snid);
void BspAdcsGetSTAT(AdcsXStat *status);

/* ----- Sen/Act Map getters ----- */

void BspAdcsGetImuData(BspAdcsImuData *data);

#endif /* INC_BSP_BSP_ADCS_H_ */
