#include "../../../include/lpw/device/mouse/mouse_prototype.h"
#include "../../../include/lpw/device/device_prototype.h"

#include <assert.h>
#include <stddef.h>
#include <malloc.h>

LpwMouse lpwCreateMouse(LpwDevice device, const LpwMouseCreateInfo* ci_ptr)
{
    assert(device != LPW_NULL_HANDLE);
    LpwMouse mouse = (LpwMouse_Prototype*)malloc(sizeof(LpwMouse_Prototype));
    mouse->info.pos.x = 0;
    mouse->info.pos.y = 0;
    mouse->info.pre_pos.x = 0;
    mouse->info.pre_pos.y = 0;
    mouse->info.pfn_callback_list.pfn_pos_callback = NULL;
    mouse->info.pfn_callback_list.pfn_button_callback = NULL;
    mouse->info.pfn_callback_list.pfn_wheel_callback = NULL;
    for(LpwEnumMouseButton button = LPW_ENUM_MOUSE_BUTTON_NULL; button < LPW_ENUM_MOUSE_BUTTON_MAX_ENUM; ++button)
    {
        mouse->info.button_state_table[button] = LPW_ENUM_MOUSE_BUTTON_STATE_NULL;
#if defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )
        mouse->info.pre_time_table[button] = 0;
#endif
    }
#if defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )
    mouse->info.time_interval = 250;
#endif
    mouse->user_ptr = NULL;
    mouse->root_device = device;
    if(ci_ptr != NULL)
    {
        if(ci_ptr->pfn_callback_list_ptr != NULL)
        {
            mouse->info.pfn_callback_list.pfn_pos_callback = ci_ptr->pfn_callback_list_ptr->pfn_pos_callback;
            mouse->info.pfn_callback_list.pfn_button_callback = ci_ptr->pfn_callback_list_ptr->pfn_button_callback;
            mouse->info.pfn_callback_list.pfn_wheel_callback = ci_ptr->pfn_callback_list_ptr->pfn_wheel_callback;
        }
        mouse->user_ptr = (void*)ci_ptr->user_ptr;
    }
    device->mouse = mouse;
    return mouse;
}
void lpwDestroyMouse(LpwMouse mouse)
{
    assert(mouse != LPW_NULL_HANDLE);
    free(mouse);
}

LpwEnumMouseButtonState lpwGetMouseButtonState(LpwMouse mouse, LpwEnumMouseButton button)
{
    assert(mouse != LPW_NULL_HANDLE);
    return mouse->info.button_state_table[button];
}

void lpwGetMousePos(LpwMouse mouse, LpwEnumMousePosFlag flag, LpwVec2_i32* pos)
{
    assert(mouse != LPW_NULL_HANDLE);
    assert(pos != NULL);
    switch(flag)
    {
        case LPW_ENUM_MOUSE_POS_FLAG_NULL:
        case LPW_ENUM_MOUSE_POS_FLAG_CURRENT:{
            pos->x = (int32_t)mouse->info.pos.x;
            pos->y = (int32_t)mouse->info.pos.y;
        }break;
        case LPW_ENUM_MOUSE_POS_FLAG_PREVIOUS:{
            pos->x = (int32_t)mouse->info.pre_pos.x;
            pos->y = (int32_t)mouse->info.pre_pos.y;
        }break;
        case LPW_ENUM_MOUSE_POS_FLAG_DIFFERENCE: {
            pos->x = (int32_t)(mouse->info.pos.x - mouse->info.pre_pos.x);
            pos->y = (int32_t)(mouse->info.pos.y - mouse->info.pre_pos.y);
        }break;
        default : assert(0);
    }
}

void lpwSetMouseUserPtr(LpwMouse mouse, const void* src_ptr)
{
    assert( mouse != LPW_NULL_HANDLE);
    mouse->user_ptr = (void*)src_ptr;
}
void* lpwGetMouseUserPtr(LpwMouse mouse)
{
    assert( mouse != LPW_NULL_HANDLE);
    return mouse->user_ptr;
}

void lpwSetMousePfnCallback(LpwMouse mouse, LpwEnumMouseEvent event, const void* src_ptr)
{
    assert( mouse != LPW_NULL_HANDLE);
    switch(event)
    {
        case LPW_ENUM_MOUSE_EVENT_POS:{
            mouse->info.pfn_callback_list.pfn_pos_callback = (PFN_LpwMousePosCallback)src_ptr;
        }break;
        case LPW_ENUM_MOUSE_EVENT_BUTTON:{
            mouse->info.pfn_callback_list.pfn_button_callback = (PFN_LpwMouseButtonCallback)src_ptr;
        }break;
        case LPW_ENUM_MOUSE_EVENT_WHEEL:{
            mouse->info.pfn_callback_list.pfn_wheel_callback = (PFN_LpwMouseWheelCallback)src_ptr;
        }break;
        default: assert(0);
    }    
}
void* lpwGetMousePfnCallback(LpwMouse mouse, LpwEnumMouseEvent event)
{
    assert( mouse != LPW_NULL_HANDLE);
    switch(event)
    {
        case LPW_ENUM_MOUSE_EVENT_POS:{
            return (void*)mouse->info.pfn_callback_list.pfn_pos_callback;
        }break;
        case LPW_ENUM_MOUSE_EVENT_BUTTON:{
            return (void*)mouse->info.pfn_callback_list.pfn_button_callback;
        }break;
        case LPW_ENUM_MOUSE_EVENT_WHEEL:{
            return (void*)mouse->info.pfn_callback_list.pfn_wheel_callback;
        }break;
        default: assert(0);
    }
    return NULL;
}

LpwMouse lpwGetMouse(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    return device->mouse;
}
LpwDevice lpwGetDeviceFromMouse(LpwMouse mouse)
{
    assert(mouse != LPW_NULL_HANDLE);
    return mouse->root_device;
}



void lpwProcessMouseButtonEvent(LpwMouse mouse, LpwEnumMouseButton button, LpwEnumMouseButtonEvent event)
{
    if(mouse != LPW_NULL_HANDLE)
    {
        LpwEnumMouseButtonState state = LPW_ENUM_MOUSE_BUTTON_STATE_NULL;
        if(event == LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS)
            state = LPW_ENUM_MOUSE_BUTTON_STATE_ACTIVE;
        else
            state = LPW_ENUM_MOUSE_BUTTON_STATE_INACTIVE;
        mouse->info.button_state_table[button] = state;
        if(mouse->info.pfn_callback_list.pfn_button_callback != NULL){
            mouse->info.pfn_callback_list.pfn_button_callback(mouse, button, event);
        }
    }
}

#if defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )
void _lpwPlatformPrivateSetMouseButtonDoubleClickTimeInterval_XCB(LpwMouse mouse, uint32_t time_interval)
{
    assert(mouse != LPW_NULL_HANDLE);
    mouse->info.time_interval = time_interval;
}
#endif