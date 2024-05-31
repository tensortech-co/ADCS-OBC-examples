/*
 * obc_app.c
 *
 *  Created on: May 30, 2024
 *      Author: henry
 */

#include "main.h"
#include "usart.h"

#include "obc_app.h"
#include "bsp_adcs.h"

void ObcAppInit()
{
	BspAdcsInit();
}

void ObcAppRoutine()
{
	BspAdcsTask();
	HAL_Delay(1000);

	reg_snid_t snid;
	BspAdcsGetSNID(&snid);
	HAL_UART_Transmit(&huart3, snid.raw_u8, 10, 10);
	HAL_Delay(10);
}
