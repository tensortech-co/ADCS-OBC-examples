/**
 * @file adcs_register.h
 * @author Jen-Hao Cheng (henry@tensortech.co)
 * @brief ADCS registers
 * @version 0.1
 * @date 2024-05-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef ADCS_REGISTER_H_
#define ADCS_REGISTER_H_
// Tensor Tech
#include "adcs_xm_reg_map.h"
// standard C library
#include <stdint.h>

#define USER_MAP_TOTAL_WORD 174
#define SENACT_MAP_TOTAL_WORD 187
#define PARAM_MAP_TOTAL_WORD 109


typedef struct
{
    AdcsXUserMap user_map;      // map 0
    AdcsXSenActMap sen_act_map; // map 1
    AdcsXParamMap param_map;    // map 2
} reg_adcs;

#endif // ADCS_REGISTER_H_

/************************ Copyright (C) 2022 Tensor Tech ************************/