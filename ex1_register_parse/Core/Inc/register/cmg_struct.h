#ifndef CMG_STRUCT_H_ 
#define CMG_STRUCT_H_ 

#include <stdint.h>
#include "common_struct.h"

typedef union {
  uint32_t raw_u32;
  struct {
    unsigned mode : 8;
    unsigned : 24;
  } bits;
} CmgXConf;

typedef union {
  uint32_t raw_u32;
  struct {
    int16_t x : 16;
    int16_t y : 16;
  };
} CmgXRef;

typedef union {
  uint32_t raw_u32;
  struct {
    unsigned ot : 1;
    unsigned rs485 : 1;
    unsigned oc3 : 1;
    unsigned oc5 : 1;
    unsigned uv5 : 1;
    unsigned ov5 : 1;
    unsigned dini : 1;
    unsigned sini : 1;
    unsigned sat : 1;
    unsigned hsat : 1;
    unsigned : 6;
    unsigned derr : 8;
    unsigned : 8;
  } bits;
} CmgXStat;

typedef union {
  uint32_t raw_u32;
  struct {
    int16_t betadot : 16;
    uint16_t beta : 16;
  };
} CmgXGimbal;

typedef union {
  uint32_t raw_u32;
  struct {
    int16_t acc : 16;
    int16_t spd : 16;
  };
} CmgXWheel;

typedef union {
  uint32_t raw_u32;
  struct {
    int16_t toptmp : 16;
    int16_t bottmp : 16;
  };
} CmgXTmp;

typedef union {
  uint32_t raw_u32;
  struct {
    uint16_t i5v : 16;
    uint16_t i3v3 : 16;
  };
} CmgXCur;

typedef union {
  uint32_t raw_u32;
  struct {
    uint16_t v5v : 16;
    uint16_t v3v3 : 16;
  };
} CmgXVolt;

#endif // CMG_STRUCT_H_ 

