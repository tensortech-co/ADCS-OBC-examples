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

#include <stdio.h>

void ObcAppInit()
{
	BspAdcsInit();

	BspAdcsSetCmgWTorqueUser(0, 0.8);
	BspAdcsSetMode(MODE_MANUAL);
}

void ObcAppRoutine()
{
	BspAdcsTask();

	reg_snid_t snid;
	BspAdcsGetSNID(&snid);
	HAL_UART_Transmit(&huart3, snid.raw_u8, 10, 10);
	HAL_Delay(10);


	uint8_t log[40];
	int len;

	reg_imux_s_t imu_s;
	BspAdcsGetIMUx_S(0, &imu_s);
	len = snprintf((char *)log, sizeof(log),
			", omega = %.4f, %.4f, %.4f \r\n",
			imu_s.omega_BN_S[0], imu_s.omega_BN_S[1], imu_s.omega_BN_S[2]);
	HAL_UART_Transmit(&huart3, log, len, 10);
	HAL_Delay(50);
}
