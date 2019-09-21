#pragma once

#include "../macro/platform_sdk.h"
#include "../external/platform/platform_sdk.h"

#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )

LRESULT CALLBACK _lpwDeviceEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

#include "device.h"

void _lpwDeviceEventHandler(const xcb_generic_event_t* xcb_event, LpwDevice device);

#endif