#pragma once

#include <inttypes.h>

typedef uint8_t LpwBool;
#define LPW_TRUE 1
#define LPW_FALSE 0

typedef uint32_t LpwFlags;

typedef struct LpwVec2_ui32
{
    uint32_t x;
    uint32_t y;
}LpwVec2_ui32;

typedef struct LpwVec2_i32
{
    int32_t x;
    int32_t y;
}LpwVec2_i32;