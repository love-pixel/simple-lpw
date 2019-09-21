#pragma once

#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
#include <Windows.h>
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB)
#include <xcb/xcb.h>

#include <xkbcommon/xkbcommon.h>
//#include <xkbcommon/xkbcommon-x11.h>
#include <xcb/xkb.h>

#include <sys/time.h>

#endif