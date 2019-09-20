#pragma once

#include "mouse.h"

#include "../../macro/platform_sdk.h"
#include "../../external/platform/platform_sdk.h"

typedef struct LpwMouseInfo
{
    LpwVec2_ui32            pos;
    LpwVec2_ui32            pre_pos;
    LpwEnumMouseButtonState button_state_table[LPW_ENUM_MOUSE_BUTTON_MAX_ENUM];
    LpwMousePfnCallbackList pfn_callback_list;
#if defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )
    xcb_timestamp_t         pre_time_table[LPW_ENUM_MOUSE_BUTTON_MAX_ENUM];
    uint32_t                time_interval;
#endif
}LpwMouseInfo;

typedef struct LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwMouse)
{
    LpwMouseInfo    info;
    void*           user_ptr;
    LpwDevice       root_device;
}LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwMouse);

void lpwProcessMouseButtonEvent(LpwMouse mouse, LpwEnumMouseButton button, LpwEnumMouseButtonEvent event);