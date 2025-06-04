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
static uint8_t command[128];

// private function declare

static uint8_t generateChecksum(const uint8_t *buf, uint16_t len);
static void bspAdcsRxCallback();

// private function implement

uint8_t generateChecksum(const uint8_t *buf, uint16_t len)
{
  uint8_t sum = 0;
  while(len--)
  {
    sum += *buf++;
  };
 return (0xFF - sum + 1);
}

void bspAdcsRxCallback()
{
	uint8_t map_id;
	uint8_t word_count;
	uint8_t reg_id;

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
	HAL_UART_Receive_IT(&huart2, &rx_buffer, 1); // You need to toggle a breakpoint on this line!
}

// public function implement

void BspAdcsInit()
{
	TtParserInit(&parser, 0x64);
	HAL_UART_RegisterCallback(&huart2, HAL_UART_RX_COMPLETE_CB_ID, bspAdcsRxCallback);
	HAL_UART_Receive_IT(&huart2, &rx_buffer, 1);
}

void BspAdcsTask()
{
	// User map
	command[0] = 0xc9;
	command[1] = 0x00;
	command[2] = USER_MAP_TOTAL_WORD;
	command[3] = 0x00;
	command[4] = generateChecksum(command, 4);
	HAL_UART_Transmit_IT(&huart2,  command, 5);
	HAL_Delay(100);

	// Sensor/ Actuator map
	command[0] = 0xc9;
	command[1] = 0x00;
	command[2] = SENACT_MAP_TOTAL_WORD;
	command[3] = 0x10;
	command[4] = generateChecksum(command, 4);
	HAL_UART_Transmit_IT(&huart2,  command, 5);
	HAL_Delay(100);
}

/* ----- User map getters ----- */

void BspAdcsGetFact(Fact *fact)
{
	*fact = register_adcs.user_map.FACT;
}

void BspAdcsGetSNID(Snid *snid)
{
	*snid = register_adcs.user_map.SNID;
}

void BspAdcsGetSTAT(AdcsXStat *status)
{
	*status = register_adcs.user_map.STAT;
}

/* ----- Sen/Act map getters ----- */

void BspAdcsGetImuData(BspAdcsImuData *data)
{
	data->IMU_STAT = register_adcs.sen_act_map.IMU_STAT;
	for (uint8_t i = 0; i < ADCS_XM_IMU_NUM; i++)
	{
		data->IMU_S[i] = register_adcs.sen_act_map.IMU_S[i];
	}
}