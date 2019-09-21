#pragma once

#include "platform_data.h"

#include "../macro/platform_sdk.h"
#include "../external/platform/platform_sdk.h"

typedef struct LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwPlatformData)
{
#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )

    HINSTANCE instance;
    HWND hwnd;
    char* wnd_class_name;

#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

    xcb_connection_t* connection;
    xcb_screen_t* screen;
    xcb_window_t window;
    xcb_intern_atom_reply_t* atom_window_reply;

#endif
}LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwPlatformData);