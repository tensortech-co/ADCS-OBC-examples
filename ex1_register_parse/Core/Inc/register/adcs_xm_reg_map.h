/**
 ******************************************************************************
 * @file    adcs_xm_reg_map.h
 * @author  Henry Cheng (henry@tensortech.co)
 * @brief   Header file for ADCS-xm register map
 ******************************************************************************
 * @attention
 * Copyright (C) 2024 Tensor Tech
 ******************************************************************************
 */

#ifndef ADCS_XM_REG_MAP_H_
#define ADCS_XM_REG_MAP_H_

#ifdef __cplusplus
extern "C"
{
#endif

// from standard C
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "adcs_xm_const.h"

#include "common_struct.h"
#include "cmg_struct.h"

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned mode : 7;        // bit 0-6
      unsigned cmd : 1;         // bit 7
      unsigned : 16;            // bit 8-23
      unsigned target_elev : 8; // bit 24-31
    } bits;
  } AdcsXConf;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned : 8;       // bit 0-7
      unsigned sec01 : 4; // bit 8-11
      unsigned sec10 : 4; // bit 12-15
      unsigned min01 : 4; // bit 16-19
      unsigned min10 : 4; // bit 20-23
      unsigned hr01 : 4;  // bit 24-27
      unsigned hr10 : 4;  // bit 28-31
    } bits;
  } AdcsXTime;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned wday01 : 4;  // bit 0-3
      unsigned : 4;         // bit 4-7
      unsigned day01 : 4;   // bit 8-11
      unsigned day10 : 4;   // bit 12-15
      unsigned month01 : 4; // bit 16-19
      unsigned month10 : 4; // bit 20-23
      unsigned year01 : 4;  // bit 24-27
      unsigned year10 : 4;  // bit 28-31
    } bits;
  } AdcsXDate;

  typedef union
  {
    uint32_t raw_u32[35];
    struct
    {
      uint8_t line1[69];
      uint8_t line2[69];
      uint8_t reserved[2];
    };
  } AdcsXTle;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_GGA_WORD_SIZE];
    uint8_t raw_u8[ADCS_XM_REG_GGA_WORD_SIZE * 4];
  } reg_gga_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_ZDA_WORD_SIZE];
    uint8_t raw_u8[ADCS_XM_REG_ZDA_WORD_SIZE * 4];
  } reg_zda_t;

  typedef union
  {
    uint32_t raw_u32[2];
    struct
    {
      float gimbal_rate;  // rad/s
      float wheel_torque; // mNm
    };
  } AdcsXCmgCmd;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned mode : 7;  // bit 0-6
      unsigned : 1;       // bit 7
      unsigned ekf : 1;   // bit 8
      unsigned cussv : 1; // bit 9
      unsigned ame : 1;   // bit 10
      unsigned tumb : 1;  // bit 11
      unsigned tgl : 1;   // bit 12
      unsigned sun : 1;   // bit 13
      unsigned des : 1;   // bit 14
      unsigned tle : 1;   // bit 15
      unsigned adv : 2;   // bit 16-17
      unsigned : 6;       // bit 18-23
      unsigned gnss : 2;  // bit 24-25
      unsigned ot : 1;    // bit 26
      unsigned oc : 1;    // bit 27
      unsigned uv : 1;    // bit 28
      unsigned wdt : 1;   // bit 29
      unsigned serr : 1;  // bit 30
      unsigned herr : 1;  // bit 31
    } bits;
  } AdcsXStat;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned cmg : 4; // bit 0 - 3
      unsigned : 4;     // bit 4 - 7
      unsigned mtq : 3; // bit 8 - 10
      unsigned : 21;    // bit 11 - 31
    } bits;
  } AdcsXActErr;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned fss : 6; // bit 0-5
      unsigned : 2;     // bit 6-7
      unsigned mag : 6; // bit 8-13
      unsigned : 2;     // bit 14-15
      unsigned imu : 4; // bit 16-19
      unsigned : 4;     // bit 20-23
      unsigned str : 2; // bit 24-25
      unsigned : 6;     // bit 26-31
    } bits;
  } AdcsXSenErr;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned error : 12; // bit 0-11
      unsigned : 20;
    } bits;
  } AdcsXCssErr;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      int16_t brdtmp : 16;
      unsigned : 16;
    } bits;
  } AdcsXTmp;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      int16_t fss0tmp : 16;
      int16_t fss1tmp : 16;
    } bits;
  } reg_fss_tmp1_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      int16_t fss2tmp : 16;
      int16_t fss3tmp : 16;
    } bits;
  } reg_fss_tmp2_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      int16_t fss4tmp : 16;
      int16_t fss5tmp : 16;
    } bits;
  } reg_fss_tmp3_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned install : 6; // bit 0-5
      unsigned : 26;        // bit 6-31
    } bits;
  } AdcsXMagStat;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned cmg : 4;
      unsigned : 4;
      unsigned mtq : 3;
      unsigned : 21;
    } bits;
  } AdcsXActEn;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned : 8;
      unsigned : 8;
      unsigned imu : 4;
      unsigned : 4;
      unsigned str : 2;
      unsigned : 6;
    } bits;
  } AdcsXSenEn;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_MAG0_S_WORD_SIZE];
    float mag_s[ADCS_XM_REG_MAG0_S_WORD_SIZE]; // Unit: micro Tesla
  } reg_magx_s_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned install : 6; // bit 0-5
      unsigned : 2;         // bit 6-7
      unsigned active : 6;  // bit 8-13
      unsigned : 18;        // bit 14-31
    } bits;
  } AdcsXFssStat;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      int16_t alpha;
      int16_t beta;
    };
  } reg_fssx_sv_t;

  typedef union
  {
    uint32_t raw_u32;
    uint32_t pdsum;
  } reg_fssx_pdsum_t;

  typedef struct
  {
    reg_fssx_sv_t fss_sv;
    reg_fssx_pdsum_t fss_pdsum;
  } reg_fssx_data_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      uint8_t install : 4; // bit 0-3
      unsigned : 28;       // bit 6-31
    } bits;
  } reg_imu_stat_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_IMU0_S_WORD_SIZE];
    float omega_BN_S[ADCS_XM_REG_IMU0_S_WORD_SIZE];
  } reg_imux_s_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      uint8_t install : 2; // bit 0-1
      unsigned : 30;       // bit 2-31
    } bits;
  } reg_str_stat_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_STR0_S_WORD_SIZE];
    float q_SN[ADCS_XM_REG_STR0_S_WORD_SIZE];
  } reg_strx_s_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_CSS_WORD_SIZE];
    struct
    {
      float css0;
      float css1;
      float css2;
      float css3;
      float css4;
      float css5;
      float css6;
      float css7;
      float css8;
      float css9;
      float css10;
      float css11;
    } floats;
  } reg_css_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      uint8_t install : 4;
      unsigned : 4;
      uint8_t mode : 4;
      unsigned : 20;
    } bits;
  } reg_cmg_stat_t;

  typedef union
  {
    uint32_t raw_u32[2];
    struct
    {
      float cmgx_g_angle;
      float cmgx_w_rate;
    };
  } reg_cmgx_req_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_MTQ_WORD_SIZE];
    float mtq[ADCS_XM_REG_MTQ_WORD_SIZE];
  } reg_mtq_t;

  typedef union
  {
    uint32_t raw_u32[2];
    struct
    {
      float cmgx_g_rate;
      float cmgx_w_acc;
    };
  } reg_cmgx_resp_t;

  typedef struct
  {
    float tau[3]; // mNm
  } reg_tor_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_INE_TEN_WORD_SIZE];
    float ine_ten[ADCS_XM_REG_INE_TEN_WORD_SIZE];
  } reg_ine_ten_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_POS_HB_B_WORD_SIZE];
    float pos_hb_b[ADCS_XM_REG_POS_HB_B_WORD_SIZE];
  } reg_pos_hb_b_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_ORIEN_HB_WORD_SIZE];
    float orien_hb[ADCS_XM_REG_ORIEN_HB_WORD_SIZE];
  } reg_orien_hb_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned : 8;         // bit 0-7
      unsigned enabled : 6; // bit 8-13
      unsigned : 18;        // bit 14-31
    } bits;
  } AdcsXMagSetting;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_MAG0_ORIEN_BS_WORD_SIZE];
    float orien_bs[ADCS_XM_REG_MAG0_ORIEN_BS_WORD_SIZE];
  } reg_magx_orien_bs_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned pwr : 1;     // bit 0
      unsigned : 7;         // bit 1-7
      unsigned enabled : 6; // bit 8-13
      unsigned : 18;        // bit 14-31
    } bits;
  } AdcsXFssSetting;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_FSS0_ORIEN_BS_WORD_SIZE];
    float orien_bs[ADCS_XM_REG_FSS0_ORIEN_BS_WORD_SIZE];
  } reg_fssx_orien_bs_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned : 24;      // bit 0-23
      uint8_t amount : 8; // bit 24
    } bits;
  } reg_imu_info_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_IMU0_ORIEN_BS_WORD_SIZE];
    float orien_bs[ADCS_XM_REG_IMU0_ORIEN_BS_WORD_SIZE];
  } reg_imux_orien_bs_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      unsigned : 24;      // bit 0-23
      uint8_t amount : 8; // bit 24
    } bits;
  } reg_str_info_t;

  typedef union
  {
    uint32_t raw_u32[ADCS_XM_REG_STR0_ORIEN_BS_WORD_SIZE];
    float orien_bs[ADCS_XM_REG_STR0_ORIEN_BS_WORD_SIZE];
  } reg_strx_orien_bs_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      uint8_t conf : 2; // bit 0-1
      uint8_t baud : 3; // bit 2-4
      uint8_t pwr : 1;  // bit 5
      unsigned : 26;    // bit 6-31
    } bits;
  } reg_gnss_t;

  typedef union
  {
    uint32_t raw_u32;
    struct
    {
      uint8_t s_req : 1;  // bit 0: NVM update request
      uint8_t status : 1; // bit 1: NVM status
      unsigned : 30;
    } bits;
  } reg_nvm_t;

  typedef struct
  {
    Fact FACT;
    Snid SNID;
    CmgXStat STAT;
    CmgXGimbal GIMBAL;
    CmgXWheel WHEEL;
    CmgXTmp TMP;
    CmgXCur CUR;
    CmgXVolt VOL;
    CmgXConf CONF;
    CmgXRef REF;
  } CmgXUserReg;

  typedef struct
  {
    uint32_t count[8];
  } DebugResult;

  // Map 0
  typedef struct
  {
    Fact FACT;                                 // offset 0
    Snid SNID;                                 // offset 1
    AdcsXConf CONF;                            // offset 4
    AdcsXTime TIME;                            // offset 5
    AdcsXDate DATE;                            // offset 6
    GeodeticCoordinate LLA_REF;                // offset 7
    Quaternion Q_REF;                          // offset 10
    UnitVector POINTING_AXIS;                  // offset 14
    AdcsXTle TLE;                              // offset 17
    reg_gga_t GGA;                             // offset 52////////////////////////////
    reg_zda_t ZDA;                             // offset 84///////////////////////////
    UnitVector SV_USER;                        // offset 100
    Dipole MTQ_USER;                           // offset 103
    AdcsXCmgCmd CMG_CMD_USER[ADCS_XM_CMG_NUM]; // offset 106
    uint32_t reserved_1[14];                   // offset 114
    AdcsXStat STAT;                            // offset 128
    AdcsXActErr ACT_ERR;                       // offset 129
    AdcsXSenErr SEN_ERR;                       // offset 130
    AdcsXCssErr CSS_ERR;                       // offset 131
    Quaternion Q;                              // offset 132
    Rate RATE;                                 // offset 136
    GeodeticCoordinate LLA;                    // offset 139
    MRP ATT_ERROR;                             // offset 142
    Rate ATT_ERROR_RATE;                       // offset 145
    AdcsXTmp ADCS_TMP;                         // offset 148
    float PWR_VOL_5V;                          // offset 149
    float PWR_CUR_5V;                          // offset 150
    float PWR_VOL_3V;                          // offset 151
    float PWR_CUR_3V;                          // offset 152
    reg_fss_tmp1_t FSS_TMP1;                   // offset 153//////////////////////
    reg_fss_tmp2_t FSS_TMP2;                   // offset 154/////////////////////
    reg_fss_tmp3_t FSS_TMP3;                   // offset 155///////////////////////
    UnitVector SV;                             // offset 156
    MagneticField MAG;                         // offset 159
    MagneticField HARD_IRON;                   // offset 162
    Float9D SOFT_IRON;                         // offset 165
    Rate IMU_BIAS;                             // offset 174
    uint32_t reserved_2[79];                   // offset 177
  } AdcsXUserMap;

  // Map 1
  typedef struct
  {
    AdcsXMagStat MAG_STAT;                       // offset 0
    reg_magx_s_t MAG_S[ADCS_XM_MAG_NUM];         // offset 1, 4, 7, 10, 13, 16
    AdcsXFssStat FSS_STAT;                       // offset 19
    reg_fssx_data_t FSS_DATA[ADCS_XM_FSS_NUM];   // offset (20-21), (22-23), (24-25), (26-27), (28-29), (30-31)
    reg_imu_stat_t IMU_STAT;                     // offset 32
    reg_imux_s_t IMU_S[ADCS_XM_IMU_NUM];         // offset 33, 36, 39, 42
    reg_str_stat_t STR_STAT;                     // offset 45
    reg_strx_s_t STR_S[ADCS_XM_STR_NUM];         // offset 46, 50
    reg_css_t CSS;                               // offset 54
    reg_mtq_t MTQ;                               // offset 66
    reg_cmg_stat_t CMG_STAT;                     // offset 69
    CmgXUserReg CMG_REG[4];                      // offset (70-81), (82-93), (94-105), (106-117)
    float MEAS_MAG_B[3];                         // offset 118
    float MEAS_IMU_B[3];                         // offset 121
    reg_tor_t DESIRED_TOR;                       // offset 124
    DebugResult DBG_FSS_RESULT[ADCS_XM_FSS_NUM]; // offset 127, 135, 143, 151, 159, 167
    DebugResult DBG_CMG_RESULT[ADCS_XM_CMG_NUM]; // offset 175, 183, 191, 199
    uint32_t reserved_3[49];                     // offset 207-255
  } AdcsXSenActMap;

  // Map 2
  typedef struct
  {
    float MASS;                                        // offset 0
    reg_ine_ten_t INE_TEN;                             // offset 1
    reg_pos_hb_b_t POS_HB_B;                           // offset 10
    reg_orien_hb_t ORIEN_HB;                           // offset 13
    AdcsXMagSetting MAG_SETTING;                       // offset 17
    reg_magx_orien_bs_t MAG_ORIEN_BS[ADCS_XM_MAG_NUM]; // offset 18, 22, 26, 30, 34, 38
    AdcsXFssSetting FSS_SETTING;                       // offset 42
    reg_fssx_orien_bs_t FSS_ORIEN_BS[ADCS_XM_FSS_NUM]; // offset 43, 47, 51, 55, 59, 63
    reg_imu_info_t IMU_INFO;                           // offset 67
    reg_imux_orien_bs_t IMU_ORIEN_BS[ADCS_XM_IMU_NUM]; // offset 68, 72, 76, 80
    reg_str_info_t STR_INFO;                           // offset 84
    reg_strx_orien_bs_t STR_ORIEN_BS[ADCS_XM_STR_NUM]; // offset 85
    reg_gnss_t GNSS;                                   // offset 93
    float DCM_BB0[9];                                  // offset 94
    Quaternion MTQ_ORIEN_BA;                           // offset 103
    AdcsXActEn ACT_EN;                                 // offset 107
    AdcsXSenEn SEN_EN;                                 // offset 108
    uint32_t reserved_4[146];                          // offset 109
    reg_nvm_t NVM;                                     // offet 255
  } AdcsXParamMap;

#ifdef __cplusplus
}
#endif

#endif // ADCS_XM_REG_MAP_H_

/************************ Copyright (C) 2024 Tensor Tech ************************/
