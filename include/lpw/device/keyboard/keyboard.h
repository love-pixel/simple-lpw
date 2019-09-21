#pragma once

#include "../device.h"
#include "../../enum/keyboard_event.h"
#include "../../enum/keyboard_key.h"
#include "../../enum/keyboard_key_state.h"

LPW_DEFINE_HANDLE(LpwKeyboard)

typedef void (*PFN_LpwKeyboardKeyCallback)(LpwKeyboard keyboard,LpwEnumKeyboardKey key, LpwEnumKeyboardKeyEvent event);
//typedef void (*PFN_LpwKeyboardCallback)(LpwKeyboard keyboard,);

typedef void (*PFN_LpwPlatformKeyboardKeyCodeCallback)(uint32_t platform_key_code);

typedef struct LpwKeyboardPfnCallbackList
{
    PFN_LpwKeyboardKeyCallback pfn_key_callback;
}LpwKeyboardPfnCallbackList;

typedef struct LpwKeyboardCreateInfo
{
    const LpwKeyboardPfnCallbackList*   pfn_callback_list_ptr;
    const void*                         user_ptr;
}LpwKeyboardCreateInfo;

LpwKeyboard lpwCreateKeyboard(LpwDevice device, const LpwKeyboardCreateInfo* ci_ptr);
void lpwDestroyKeyboard(LpwKeyboard keyboard);

LpwEnumKeyboardKeyState lpwGetKeyboardKeyState(LpwKeyboard keyboard, LpwEnumKeyboardKey key);

void lpwSetKeyboardUserPtr(LpwKeyboard keyboard, const void* src_ptr);
void* lpwGetKeyboardUserPtr(LpwKeyboard keyboard);

void lpwSetKeyboardPfnCallback(LpwKeyboard keyboard, LpwEnumKeyboardEvent event, const void* src_ptr);
void* lpwGetKeyboardPfnCallback(LpwKeyboard keyboard, LpwEnumKeyboardEvent event);

LpwKeyboard lpwGetKeyboard(LpwDevice device);
LpwDevice lpwGetDeviceFromKeyboard(LpwKeyboard keyboard);

void lpwSetKeyboardTimeInterval(LpwKeyboard keyboard, uint32_t time_interval);

void lpwPrivateSetGlobalKeyboardKeyMappingCode(uint32_t platform_key_code, LpwEnumKeyboardKey key);

void lpwSetGlobalPlatformKeyboardKeyCodePfnCallback(PFN_LpwPlatformKeyboardKeyCodeCallback pfn_callback);