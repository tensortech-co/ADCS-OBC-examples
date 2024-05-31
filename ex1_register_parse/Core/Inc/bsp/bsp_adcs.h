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

void BspAdcsInit();
void BspAdcsTask();

// User Map
void BspAdcsGetSNID(reg_snid_t *snid);

// Sen/Act Map
void BspAdcsGetIMUx_S(uint8_t id, reg_imux_s_t *imu_s);

#endif /* INC_BSP_BSP_ADCS_H_ */
