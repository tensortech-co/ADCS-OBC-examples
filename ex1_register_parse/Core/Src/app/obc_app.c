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

static uint8_t obc_log[128];


void ObcAppInit()
{
	BspAdcsInit();
}

void ObcAppRoutine()
{
	BspAdcsTask();

	Fact fact;
	Snid snid;
	int len;
	BspAdcsImuData data;

	BspAdcsGetFact(&fact);
	BspAdcsGetSNID(&snid);
	BspAdcsGetImuData(&data);

	// Print some log
	len = snprintf((char *)obc_log, sizeof(obc_log),
			"FW Ver: %d.%d.%d, SNID: %s \r\n",
			fact.bits.major, fact.bits.minor, fact.bits.patch, snid.raw_u8);
	HAL_UART_Transmit(&huart3, obc_log, len, 20);
	HAL_Delay(50);

	len = snprintf((char *)obc_log, sizeof(obc_log),
			"IMU0: %.4f, %.4f, %.4f [rad/s] \r\nIMU1: %.4f, %.4f, %.4f [rad/s] \r\n",
			data.IMU_S[0].omega_BN_S[0], data.IMU_S[0].omega_BN_S[1], data.IMU_S[0].omega_BN_S[2],
			data.IMU_S[1].omega_BN_S[0], data.IMU_S[1].omega_BN_S[1], data.IMU_S[1].omega_BN_S[2]);
	HAL_UART_Transmit(&huart3, obc_log, len, 20);
	HAL_Delay(1000);
}
