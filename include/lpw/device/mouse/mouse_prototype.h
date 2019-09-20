#pragma once

#include "mouse.h"

typedef struct LpwMouseInfo
{
    LpwVec2_ui32            pos;
    LpwVec2_ui32            pre_pos;
    LpwEnumMouseButtonState button_state_table[LPW_ENUM_MOUSE_BUTTON_MAX_ENUM];
    LpwMousePfnCallbackList pfn_callback_list;
}LpwMouseInfo;

typedef struct LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwMouse)
{
    LpwMouseInfo    info;
    void*           user_ptr;
    LpwDevice       root_device;
}LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwMouse);

void lpwProcessMouseButtonEvent(LpwMouse mouse, LpwEnumMouseButton button, LpwEnumMouseButtonEvent event);