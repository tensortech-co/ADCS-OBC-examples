/*
 * bsp_adcs.c
 *
 *  Created on: May 30, 2024
 *      Author: henry
 */


#include "bsp_adcs.h"
// from tt_parser/
#include "tt_parser.h"

// from Core/
#include "usart.h"
// from Driver/
#include "stm32h7xx_hal_uart.h"

// private variable
static reg_adcs register_adcs;
static TtParser parser;
static uint8_t rx_buffer;
static uint8_t command[9];

// private function declare

uint8_t generateChecksum(const uint8_t *buf, uint16_t len)
{
  uint8_t sum = 0;
  while(len--)
  {
    sum += *buf++;
  };
 return (0xFF - sum + 1);
}


// weak function overwrite

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t map_id;
	uint8_t word_count;
	uint8_t reg_id;
	if (huart->Instance == USART2)
	{
		if (TtParserUpdate(&parser, rx_buffer))
		{
			if (READ_RESPONSE == TtParserGetMsgType(&parser))
			{
				TtParserGetHeaderInfo(&parser, &map_id, &reg_id, &word_count);
				switch(map_id)
				{
				case 0:
					TtParserCopyMsgBody(&parser, &register_adcs.user_map, reg_id, word_count);
					break;
				case 1:
					TtParserCopyMsgBody(&parser, &register_adcs.sen_act_map, reg_id, word_count);
					break;
				case 2:
					TtParserCopyMsgBody(&parser, &register_adcs.param_map, reg_id, word_count);
					break;
				}
			}
		}
		HAL_UART_Receive_IT(huart, &rx_buffer, 1); // You need to toggle a breakpoint on this line!
	}
}

// private function implement

void BspAdcsInit()
{
	TtParserInit(&parser, 0x64);
	HAL_UART_Receive_IT(&huart2, &rx_buffer, 1);
}

void BspAdcsTask()
{
	// User map
	command[0] = 0xc9;
	command[1] = 0x00;
	command[2] = 0xA2;
	command[3] = 0x00;
	command[4] = 0x95;
	HAL_UART_Transmit_IT(&huart2,  command, 5);
	HAL_Delay(100);

	// Sensor/ Actuator map
	command[0] = 0xc9;
	command[1] = 0x00;
	command[2] = 0x62;
	command[3] = 0x10;
	command[4] = 0xc5;
	HAL_UART_Transmit_IT(&huart2,  command, 5);
	HAL_Delay(100);
}

void BspAdcsGetSNID(reg_snid_t *snid)
{
	*snid = register_adcs.user_map.SNID;
}

bool BspAdcsSetMode(ConfMode mode)
{
	bool result;
	uint8_t checksum = 0x00;
	command[0] = 0xc8;
	command[1] = 0x04;
	command[2] = 0x01;
	command[3]= 0x00;
	command[4] = mode; // mode
	command[5] = 0x00;
	command[6] = 0x00;
	command[7] = 0x00;
	command[8] = 0x00;

	checksum = generateChecksum(command, 9);
	command[8] = checksum;

	result = (HAL_UART_Transmit_IT(&huart2,  command, 9) == HAL_OK);
	HAL_Delay(10);
	return result;
}

bool BspAdcsSetCmgGRateUser(uint8_t id, float gimbal_rate)
{
	bool result;
	uint8_t checksum = 0x00;
	uint8_t data[4];
	memcpy(data, &gimbal_rate, 4);

	command[0] = 0xc8;
	command[1] = 0x6a + 2*id;
	command[2] = 0x01;
	command[3] = 0x00;
	command[4] = data[0];
	command[5] = data[1];
	command[6] = data[2];
	command[7] = data[3];
	command[8] = 0x00;

	checksum = generateChecksum(command, 9);
	command[8] = checksum;

	result = (HAL_UART_Transmit_IT(&huart2,  command, 9) == HAL_OK);
	HAL_Delay(10);
	return result;
}

bool BspAdcsSetCmgWTorqueUser(uint8_t id, float wheel_torque)
{
	bool result;
	uint8_t checksum = 0x00;
	uint8_t data[4];
	memcpy(data, &wheel_torque, 4);

	command[0] = 0xc8;
	command[1] = 0x6b + 2*id;
	command[2] = 0x01;
	command[3] = 0x00;
	command[4] = data[0];
	command[5] = data[1];
	command[6] = data[2];
	command[7] = data[3];
	command[8] = 0x00;

	checksum = generateChecksum(command, 9);
	command[8] = checksum;

	result = (HAL_UART_Transmit_IT(&huart2,  command, 9) == HAL_OK);
	HAL_Delay(10);
	return result;
}

void BspAdcsGetSTAT(reg_status_t *status)
{
	*status = register_adcs.user_map.STAT;
}

void BspAdcsGetIMUx_S(uint8_t id, reg_imux_s_t *imu_s)
{
	*imu_s = register_adcs.sen_act_map.IMU_DATA[id];
}
