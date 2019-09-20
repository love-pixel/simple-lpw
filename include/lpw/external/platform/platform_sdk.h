#pragma once

#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
#include <Windows.h>
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB)
#include <xcb/xcb.h>
#endif