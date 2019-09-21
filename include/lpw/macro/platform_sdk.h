#pragma once

#include "platform.h"

#if defined( LPW_MACRO_USE_PLATFORM_WINDOWS )
#define LPW_MACRO_USE_PLATFORM_SDK_WINDOWS
#elif defined( LPW_MACRO_USE_PLATFORM_LINUX )
#define LPW_MACRO_USE_PLATFORM_SDK_XCB
#endif