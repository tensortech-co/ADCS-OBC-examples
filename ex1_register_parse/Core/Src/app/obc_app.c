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

	uint8_t debug1[5] = "hello";
	HAL_UART_Transmit(&huart3, debug1, 5, 10);

	reg_snid_t snid;
	BspAdcsGetSNID(&snid);
	HAL_UART_Transmit(&huart3, snid.raw_u8, 10, 10);
	HAL_Delay(10);

	uint8_t debug2[3] = "123";
	HAL_UART_Transmit(&huart3, debug2, 5, 10);

	reg_imux_s_t imu_s;
	BspAdcsGetIMUx_S(0, &imu_s);
	HAL_UART_Transmit(&huart3, (uint8_t *) imu_s.raw_u32[0], 4, 10);
	HAL_UART_Transmit(&huart3, (uint8_t *) imu_s.raw_u32[1], 4, 10);
	HAL_UART_Transmit(&huart3, (uint8_t *) imu_s.raw_u32[2], 4, 10);
	HAL_Delay(10);

	uint8_t debug3[3] = "456";
	HAL_UART_Transmit(&huart3, debug3, 5, 10);
	HAL_Delay(10);
}
