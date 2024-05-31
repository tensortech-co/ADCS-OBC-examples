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

void BspAdcsGetSNID(reg_snid_t *snid);


#endif /* INC_BSP_BSP_ADCS_H_ */
