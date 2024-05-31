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

#include <stdint.h>

#define FLOAT_3D_SIZE 3
#define FLOAT_4D_SIZE 4
#define FLOAT_9D_SIZE 9

#define MAX_MAG_AMOUNT 6
#define MAX_FSS_AMOUNT 6
#define MAX_IMU_AMOUNT 4
#define MAX_STR_AMOUNT 2
#define MAX_CMG_AMOUNT 4
#define MAX_CSS_AMOUNT 12

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint16_t version : 16;
        uint16_t na : 16;
    } bits;
} reg_fact_t;

typedef union
{
    uint32_t raw_u32[3];
    uint8_t raw_u8[12];
} reg_snid_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t mode : 3;        // bit 0
        uint8_t rfrm : 2;        // bit 3
        uint32_t na : 19;        // bit 5
        uint8_t target_elev : 8; // bit 24
    } bits;
} reg_conf_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t na : 8;    // unused
        uint8_t sec01 : 4; // bit 8
        uint8_t sec10 : 4; // bit 12
        uint8_t min01 : 4; // bit 16
        uint8_t min10 : 4; // bit 20
        uint8_t hr01 : 4;  // bit 24
        uint8_t hr10 : 4;  // bit 28
    } bits;
} reg_time_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t wday01 : 4;  // bit 0
        uint8_t na : 4;      // bit 4
        uint8_t day01 : 4;   // bit 8
        uint8_t day10 : 4;   // bit 12
        uint8_t month01 : 4; // bit 16
        uint8_t month10 : 4; // bit 20
        uint8_t year01 : 4;  // bit 24
        uint8_t year10 : 4;  // bit 28
    } bits;
} reg_date_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float pointing_axis[FLOAT_3D_SIZE]; // x(0), y(1), z(2)
} reg_pointing_axis_t;

typedef union
{
    uint32_t raw_u32[35];
    struct
    {
        uint8_t line_1[69];
        uint8_t line_2[69];
        uint8_t na[2];
    } Bytes;
} reg_tle_t;

typedef union
{
    uint32_t raw_u32[32];
    uint8_t raw_u8[128];
} reg_gga_t;

typedef union
{
    uint32_t raw_u32[16];
    uint8_t raw_u8[64];
} reg_zda_t;

typedef union
{
    uint32_t raw_u32[2];
    struct
    {
        float gimbal_rate;  // rad/s
        float wheel_torque; // mNm
    };
} reg_cmg_cmd_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t na0 : 5;   // bit 0-4
        uint8_t mode : 3;  // bit 5
        uint8_t na1 : 1;   // bit 8
        uint8_t cussv : 1; // bit 9
        uint8_t ame : 1;   // bit 10
        uint8_t tumb : 1;  // bit 11
        uint8_t tgl : 1;   // bit 12
        uint8_t sun : 1;   // bit 13
        uint8_t des : 1;   // bit 14
        uint8_t tle : 1;   // bit 15
        uint8_t na2 : 8;   // bit 16-23
        uint8_t gnss : 2;  // bit 24
        uint8_t ot : 1;    // bit 26
        uint8_t oc : 1;    // bit 27
        uint8_t uv : 1;    // bit 28
        uint8_t wdt : 1;   // bit 29
        uint8_t serr : 1;  // bit 30
        uint8_t herr : 1;  // bit 31
    } bits;
} reg_status_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t cmg : 4; // bit 0 - 4
        uint8_t na0 : 4; // bit 4 - 8
        uint8_t mtq : 3; // bit 8 - 11
    } bits;
} reg_act_err_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t fss : 6; // bit 0-5
        uint8_t na0 : 2; // bit 6
        uint8_t mag : 6; // bit 8-13
        uint8_t na1 : 2; // bit 14
        uint8_t imu : 4; // bit 16-19
        uint8_t na2 : 4; // bit 20
        uint8_t str : 2; // bit 24-25
    } bits;
} reg_sen_err_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t css0 : 1;  // bit 0
        uint8_t css1 : 1;  // bit 1
        uint8_t css2 : 1;  // bit 2
        uint8_t css3 : 1;  // bit 3
        uint8_t css4 : 1;  // bit 4
        uint8_t css5 : 1;  // bit 5
        uint8_t css6 : 1;  // bit 6
        uint8_t css7 : 1;  // bit 7
        uint8_t css8 : 1;  // bit 8
        uint8_t css9 : 1;  // bit 9
        uint8_t css10 : 1; // bit 10
    } bits;
} reg_css_err_t;

typedef union
{
    uint32_t raw_u32[FLOAT_4D_SIZE];
    float q[FLOAT_4D_SIZE]; // w = q(0), x = q(1), y = q(2), z = q(3)
} reg_q_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float rate[FLOAT_3D_SIZE]; // x(0), y(1), z(2)
} reg_rate_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    struct
    {
        float latitude;
        float longitude;
        float altitude;
    };
} reg_lla_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float att_error[FLOAT_3D_SIZE];
} reg_att_error_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float att_error_rate[FLOAT_3D_SIZE];
} reg_att_error_rate_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        int16_t brdtmp : 16;
        int16_t na : 16;
    } bits;
} reg_adcs_tmp_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        int16_t tmp1 : 16;
        int16_t tmp2 : 16;
    } bits;
} reg_cmgx_tmp_t;

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
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float sv[FLOAT_3D_SIZE];
} reg_sv_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float mag_B[FLOAT_3D_SIZE];
} reg_mag_t;

typedef union
{
    uint32_t raw_u32[FLOAT_9D_SIZE];
    float mag_mat[FLOAT_9D_SIZE];
} reg_mag_mat_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float mag_vec[FLOAT_3D_SIZE];
} reg_mag_vec_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t install : 6; // bit 0-5
        uint32_t na : 26;    // bit 6-31
    } bits;
} reg_mag_stat_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float mag_s[FLOAT_3D_SIZE];
} reg_magx_s_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t install : 6; // bit 0-5
        uint8_t na1 : 2;     // bit 6-7
        uint8_t active : 6;  // bit 8-13
        uint8_t na2 : 2;     // bit 14-15
        uint16_t na3 : 16;   // bit 16-31
    } bits;
} reg_fss_stat_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint16_t phi;
        uint16_t theta;
    };
} reg_fssx_sv_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint16_t pdsum;
        uint16_t na;
    };
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
        uint32_t na : 28;    // bit 6-31
    } bits;
} reg_imu_stat_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float omega_BN_S[FLOAT_3D_SIZE];
} reg_imux_s_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t install : 2; // bit 0-1
        uint32_t na : 30;    // bit 2-31
    } bits;
} reg_str_stat_t;

typedef union
{
    uint32_t raw_u32[FLOAT_4D_SIZE];
    float q_SN[FLOAT_4D_SIZE];
} reg_strx_s_t;

typedef union
{
    uint32_t raw_u32[MAX_CSS_AMOUNT];
    float value[MAX_CSS_AMOUNT];
} reg_css_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t install : 4;
        uint32_t na : 28;
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
} reg_cmgx_data_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float mtq[FLOAT_3D_SIZE];
} reg_mtq_t;

typedef union
{
    uint32_t raw_u32[2];
    struct
    {
        float cmgx_g_rate;
        float cmgx_w_acc;
    };
} reg_cmgx_data_rate_t;

typedef union
{
    uint32_t raw_u32[FLOAT_9D_SIZE];
    float ine_ten[FLOAT_9D_SIZE];
} reg_ine_ten_t;

typedef union
{
    uint32_t raw_u32[FLOAT_3D_SIZE];
    float pos[FLOAT_3D_SIZE];
} reg_pos_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint32_t na : 24;   // bit 6-23
        uint8_t amount : 8; // bit 24
    } bits;
} reg_mag_info_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint16_t na : 16;   // bit 0-15
        uint8_t fov : 8;    // bit 16
        uint8_t amount : 8; // bit 24
    } bits;
} reg_fss_info_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint32_t na : 24;   // bit 0-23
        uint8_t amount : 8; // bit 24
    } bits;
} reg_imu_info_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint32_t na : 24;   // bit 0-23
        uint8_t amount : 8; // bit 24
    } bits;
} reg_str_info_t;

typedef union
{
    uint32_t raw_u32;
    struct
    {
        uint8_t s_req : 1;  // bit 0: NVM update request
        uint8_t status : 1; // bit 1: NVM status
        uint32_t na : 30;
    } bits;
} reg_nvm_t;

/////////////////////////////////////////////
typedef struct
{
    reg_fact_t FACT;                            // offset 0
    reg_snid_t SNID;                            // offset 1
    reg_conf_t CONF;                            // offset 4
    reg_time_t TIME;                            // offset 5
    reg_date_t DATE;                            // offset 6
    reg_lla_t LLA_REF;                          // offset 7
    reg_q_t Q_REF;                              // offset 10
    reg_pointing_axis_t POINTING_AXIS;          // offset 14
    reg_tle_t TLE;                              // offset 17
    reg_gga_t GGA;                              // offset 52
    reg_zda_t ZDA;                              // offset 84
    reg_sv_t SV_USER;                           // offset 100
    reg_mtq_t MTQ_USER;                         // offset 103
    reg_cmg_cmd_t CMG_CMD_USER[MAX_CMG_AMOUNT]; // offset 106, 108, 110, 112
    uint32_t NA_0[14];                          // offset 114-127
    reg_status_t STAT;                          // offset 128
    reg_act_err_t ACT_ERR;                      // offset 129
    reg_sen_err_t SEN_ERR;                      // offset 130
    reg_css_err_t CSS_ERR;                      // offset 131
    reg_q_t Q;                                  // offset 132
    reg_rate_t RATE;                            // offset 136
    reg_lla_t LLA;                              // offset 139
    reg_att_error_t ATT_ERROR;                  // offset 142
    reg_att_error_rate_t ATT_ERROR_RATE;        // offset 145
    reg_adcs_tmp_t ADCS_TMP;                    // offset 148
    reg_cmgx_tmp_t CMG_TMP[MAX_CMG_AMOUNT];     // offset 149, 150, 151, 152
    reg_fss_tmp1_t FSS_TMP1;                    // offset 153
    reg_fss_tmp2_t FSS_TMP2;                    // offset 154
    reg_fss_tmp3_t FSS_TMP3;                    // offset 155
    reg_sv_t SV;                                // offset 156
    reg_mag_t MAG;                              // offset 159
    uint32_t NA_1[94];                          // offset 162-255
} reg_map_user_t;

typedef struct
{
    reg_mag_mat_t MAG_MAT;                              // offset 0
    reg_mag_vec_t MAG_VEC;                              // offset 9
    reg_mag_stat_t MAG_STAT;                            // offset 12
    reg_magx_s_t MAG_S[MAX_MAG_AMOUNT];                 // offset 13, 16, 19, 22, 25, 28
    reg_fss_stat_t FSS_STAT;                            // offset 31
    reg_fssx_data_t FSS_DATA[MAX_FSS_AMOUNT];           // offset (32-33), (34-35), (36-37), (38-39), (40-41), (42-43)
    reg_imu_stat_t IMU_STAT;                            // offset 44
    reg_imux_s_t IMU_DATA[MAX_IMU_AMOUNT];              // offset 45, 48, 51, 54
    reg_str_stat_t STR_STAT;                            // offset 57
    reg_strx_s_t STR_DATA[MAX_STR_AMOUNT];              // offset 58, 62
    reg_css_t CSS;                                      // offset 66
    reg_cmg_stat_t CMG_STAT;                            // offset 78
    reg_cmgx_data_t CMG_DATA[MAX_CMG_AMOUNT];           // offset (79-80), (81-82), (83-84), (85-86)
    reg_mtq_t MTQ;                                      // offset 87
    reg_cmgx_data_rate_t CMG_DATA_RATE[MAX_CMG_AMOUNT]; // offset (90-91), (92-93), (94-95), (96-97)
    uint32_t NA_0[158];                                 // offset 98-255
} reg_map_sen_act_t;

typedef struct
{
    float MASS;                           // offset 0
    reg_ine_ten_t INE_TEN;                // offset 1
    reg_pos_t POS_HB_B;                   // offset 10
    reg_q_t ORIEN_HB;                     // offset 13
    reg_mag_info_t MAG_INFO;              // offset 17
    reg_q_t MAG_ORIEN_BS[MAX_MAG_AMOUNT]; // offset 18, 22, 26, 30, 34, 38
    reg_fss_info_t FSS_INFO;              // offset 42
    reg_q_t FSS_ORIEN_BS[MAX_FSS_AMOUNT]; // offset 43, 47, 51, 55, 59, 63
    reg_imu_info_t IMU_INFO;              // offset 67
    reg_q_t IMU_ORIEN_BS[MAX_IMU_AMOUNT]; // offset 68, 72, 76, 80
    reg_str_info_t STR_INFO;              // offset 84
    reg_q_t STR_ORIEN_BS[MAX_STR_AMOUNT]; // offset 85, 89
    uint32_t NA_0[162];                   // offset 93-254
    reg_nvm_t NVM;                        // offset 255
} reg_map_param_t;

typedef struct
{
    reg_map_user_t user_map;       // map 0
    reg_map_sen_act_t sen_act_map; // map 1
    reg_map_param_t param_map;     // map 2
} reg_adcs;

#endif // ADCS_REGISTER_H_
/************************ Copyright (C) 2022 Tensor Tech ************************/