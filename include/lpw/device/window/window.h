#pragma once

#include "../device.h"
#include "../../enum/window_event.h"

LPW_DEFINE_HANDLE(LpwWindow)

typedef void (*PFN_LpwWindowPosCallback)(LpwWindow window, int32_t x, int32_t y);
typedef void (*PFN_LpwWindowSizeCallback)(LpwWindow window, uint32_t x, uint32_t y);

typedef struct LpwWindowPfnCallbackList
{
    PFN_LpwWindowPosCallback    pfn_pos_callback;
    PFN_LpwWindowSizeCallback   pfn_size_callback;
}LpwWindowPfnCallbackList;

typedef struct LpwWindowCreateInfo
{
    LpwVec2_i32                     pos;
    LpwVec2_ui32                    size;
    const char*                     name;
    const LpwWindowPfnCallbackList* pfn_callback_list_ptr;
    void*                           user_ptr;
}LpwWindowCreateInfo;

LpwWindow lpwCreateWindow(LpwDevice device, const LpwWindowCreateInfo* ci_ptr);
void lpwDestroyWindow(LpwWindow window);

void lpwSetWindowUserPtr(LpwWindow window, const void* src_ptr);
void* lpwGetWindowUserPtr(LpwWindow window);

LpwVec2_i32 lpwGetWindowPos(LpwWindow window);

LpwVec2_ui32 lpwGetWindowSize(LpwWindow window);

const char* lpwGetWindowName(LpwWindow window);

void lpwSetWindowPfnCallback(LpwWindow window, LpwEnumWindowEvent event, const void* src_ptr);
void* lpwGetWindowPfnCallback(LpwWindow window, LpwEnumWindowEvent event);

LpwBool lpwIsWindowActive(LpwWindow window);

LpwWindow lpwGetWindow(LpwDevice device);
LpwDevice lpwGetDevice(LpwWindow window);