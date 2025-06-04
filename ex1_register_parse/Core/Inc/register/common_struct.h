#ifndef COMMON_STRUCT_H_ 
#define COMMON_STRUCT_H_ 

#include <stdint.h>

typedef union {
  uint32_t raw_u32;
  struct {
    unsigned patch : 8;
    unsigned minor : 4;
    unsigned major : 4;
    unsigned mn : 16;
  } bits;
} Fact;

typedef union {
  uint32_t raw_u32[3];
  uint8_t raw_u8[12];
} Snid;

typedef union {
  uint32_t raw_u32[3];
  float value[3];
} Float3D;

typedef union {
  uint32_t raw_u32[4];
  float value[4];
} Float4D;

typedef union {
  uint32_t raw_u32[5];
  float value[5];
} Float5D;

typedef union {
  uint32_t raw_u32[7];
  float value[7];
} Float7D;

typedef union {
  uint32_t raw_u32[9];
  float value[9];
} Float9D;

typedef union {
  uint32_t raw_u32[2];
  uint8_t raw_u8[8];
} Lock;

typedef union {
  uint32_t raw_u32[3];
  struct {
    float latitude;
    float longitude;
    float altitude;
  };
} GeodeticCoordinate;

typedef union {
  uint32_t raw_u32[3];
  float sigma[3];
} MRP;

typedef union {
  uint32_t raw_u32[4];
  float q[4];
} Quaternion;

typedef union {
  uint32_t raw_u32[3];
  float value[3];
} UnitVector;

typedef union {
  uint32_t raw_u32[3];
  float value[3];
} Position;

typedef union {
  uint32_t raw_u32[3];
  float value[3];
} Rate;

typedef union {
  uint32_t raw_u32[3];
  float value[3];
} Dipole;

typedef union {
  uint32_t raw_u32[3];
  float value[3];
} MagneticField;

#endif // COMMON_STRUCT_H_ 

