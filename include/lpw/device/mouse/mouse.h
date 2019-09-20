#pragma once

#include "../device.h"
#include "../../enum/mouse_event.h"
#include "../../enum/mouse_wheel.h"
#include "../../enum/mouse_button.h"
#include "../../enum/mouse_pos_flag.h"

LPW_DEFINE_HANDLE(LpwMouse)

typedef void (*PFN_LpwMousePosCallback)(LpwMouse mouse, uint32_t x, uint32_t y);
typedef void (*PFN_LpwMouseWheelCallback)(LpwMouse mouse, LpwEnumMouseWheel wheel);
typedef void (*PFN_LpwMouseButtonCallback)(LpwMouse mouse, LpwEnumMouseButton button, LpwEnumMouseButtonEvent event);

typedef struct LpwMousePfnCallbackList
{
    PFN_LpwMousePosCallback         pfn_pos_callback;
    PFN_LpwMouseWheelCallback       pfn_wheel_callback;
    PFN_LpwMouseButtonCallback      pfn_button_callback;
}LpwMousePfnCallbackList;

typedef struct LpwMouseCreateInfo
{
    const LpwMousePfnCallbackList*  pfn_callback_list_ptr;
    const void*                     user_ptr;
}LpwMouseCreateInfo;

LpwMouse lpwCreateMouse(LpwDevice device, const LpwMouseCreateInfo* ci_ptr);
void lpwDestroyMouse(LpwMouse mouse);

LpwEnumMouseButtonState lpwGetMouseButtonState(LpwMouse mouse, LpwEnumMouseButton button);

LpwVec2_i32 lpwGetMousePos(LpwMouse mouse, LpwEnumMousePosFlag flag);

void lpwSetMouseUserPtr(LpwMouse mouse, const void* src_ptr);
void* lpwGetMouseUserPtr(LpwMouse mouse);

void lpwSetMousePfnCallback(LpwMouse mouse, LpwEnumMouseEvent event, const void* src_ptr);
void* lpwGetMousePfnCallback(LpwMouse mouse, LpwEnumMouseEvent event);

LpwMouse lpwGetMouse(LpwDevice device);
LpwDevice lpwGetDeviceFromMouse(LpwMouse mouse);