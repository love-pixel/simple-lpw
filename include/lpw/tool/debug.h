#pragma once

#include "../macro/debug.h"

#if defined( LPW_MACRO_USE_DEBUG )
#define LPW_DEBUG_CODE(code) code
#else
#define LPW_DEBUG_CODE(code)
#endif