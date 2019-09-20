#pragma once

#include "keyboard.h"

#include "../../macro/platform_sdk.h"
#include "../../external/platform/platform_sdk.h"

typedef struct LpwKeyboardInfo
{
    LpwEnumKeyboardKeyState      key_state_table[LPW_ENUM_KEYBOARD_KEY_MAX_ENUM];
    LpwKeyboardPfnCallbackList   pfn_callback_list;
#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
    DWORD                        pre_time_table[LPW_ENUM_KEYBOARD_KEY_MAX_ENUM];
    DWORD                        time_interval;
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

#endif
    //xcb_timestamp_t         pre_time_table[LPW_ENUM_MOUSE_BUTTON_MAX_ENUM];
}LpwKeyboardInfo;

typedef struct LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwKeyboard)
{
    LpwKeyboardInfo     info;
    void*               user_ptr;
    LpwDevice           root_device;
}LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwKeyboard);


#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
#define LPW_KEYBOARD_MAX_KEY_NUM 512
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )
#define LPW_KEYBOARD_MAX_KEY_NUM 512
#endif

extern LpwEnumKeyboardKey lpw_global_keyboard_key_table[LPW_KEYBOARD_MAX_KEY_NUM];
extern LpwBool lpw_global_is_init_keyboard_key_table;
static void lpwGlobalMapKeyboardKey();