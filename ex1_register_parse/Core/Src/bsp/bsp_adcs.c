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
static uint8_t rx_buffer[5];

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
		for (uint8_t i = 0; i < 5; i++)
		{
			if (!TtParserUpdate(&parser, rx_buffer[i]))
			{
				continue;
			}

			if (READ_RESPONSE == TtParserGetMsgType(&parser))
			{
				TtParserGetRequestInfo(&parser, &map_id, &reg_id, &word_count);
				switch(map_id)
				{
				case 0:
					TtParserCopyMsgBody(&parser, &register_adcs.user_map);
					break;
				case 1:
					TtParserCopyMsgBody(&parser, &register_adcs.sen_act_map);
					break;
				case 2:
					TtParserCopyMsgBody(&parser, &register_adcs.param_map);
					break;
				}
			}
		}
		HAL_UART_Receive_IT(huart, rx_buffer, 5); // You need to toggle a breakpoint on this line!
	}
}

// private function implement

void BspAdcsInit()
{
	TtParserInit(&parser, 0x64);
	HAL_UART_Receive_IT(&huart2, rx_buffer, 5);
}

void BspAdcsTask()
{
	// User map
	uint8_t read_request[5] = {0xc9, 0x00, 0xA2, 0x00, 0x95};
//	HAL_UART_Transmit_IT(&huart2,  read_request, 5);
//	HAL_Delay(200);
	// Sensor/ Actuator map
	read_request[2]= 0x62;
	read_request[3] = 0x10;
	read_request[4] = 0xc5;
	HAL_UART_Transmit_IT(&huart2,  read_request, 5);
	HAL_Delay(200);
}

void BspAdcsGetSNID(reg_snid_t *snid)
{
	*snid = register_adcs.user_map.SNID;
}

void BspAdcsGetIMUx_S(uint8_t id, reg_imux_s_t *imu_s)
{
	*imu_s = register_adcs.sen_act_map.IMU_DATA[id];
}
