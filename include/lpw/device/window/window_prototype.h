#pragma once

#include "window.h"

typedef struct LpwWindowInfo
{
    LpwVec2_i32              pos;
    LpwVec2_ui32             size;
    const char*              name;
    LpwWindowPfnCallbackList pfn_callback_list;
    LpwBool                  is_active;
}LpwWindowInfo;

typedef struct LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwWindow)
{
    LpwWindowInfo  info;
    void*          user_ptr;
    LpwDevice      root_device;
}LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwWindow);