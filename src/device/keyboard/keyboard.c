#include "../../../include/lpw/device/keyboard/keyboard_prototype.h"
#include "../../../include/lpw/device/device_prototype.h"

#include <assert.h>
#include <malloc.h>

LpwKeyboard lpwCreateKeyboard(LpwDevice device, const LpwKeyboardCreateInfo* ci_ptr)
{
    lpwGlobalMapKeyboardKey();
    LpwKeyboard keyboard = (LpwKeyboard_Prototype*)malloc(sizeof(LpwKeyboard_Prototype));
    for(LpwKeyboardKey key = LPW_ENUM_KEYBOARD_KEY_NULL; key < LPW_ENUM_KEYBOARD_KEY_MAX_ENUM; ++key)
    {
        keyboard->info.key_state_table[key] = LPW_ENUM_KEYBOARD_KEY_STATE_NULL;
#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
        keyboard->info.pre_time_table[key] = 0;
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

#endif
    }
    keyboard->info.pfn_callback_list.pfn_key_callback = NULL;
#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
    keyboard->info.time_interval = 250;
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

#endif
    keyboard->user_ptr = NULL;
    keyboard->root_device = device;

    if(ci_ptr != NULL)
    {
        keyboard->user_ptr = (void*)ci_ptr->user_ptr;
        if(ci_ptr->pfn_callback_list_ptr != NULL)
        {
            keyboard->info.pfn_callback_list.pfn_key_callback = ci_ptr->pfn_callback_list_ptr->pfn_key_callback;
        }
    }

    device->keyboard = keyboard;
    return keyboard;
}
void lpwDestroyKeyboard(LpwKeyboard keyboard)
{
    assert(keyboard != LPW_NULL_HANDLE);
    free(keyboard);
}

LpwEnumKeyboardKeyState lpwGetKeyboardKeyState(LpwKeyboard keyboard, LpwEnumKeyboardKey key)
{
    assert(keyboard != LPW_NULL_HANDLE);
    return keyboard->info.key_state_table[key];
}

void lpwSetKeyboardUserPtr(LpwKeyboard keyboard, const void* src_ptr)
{
    assert(keyboard != LPW_NULL_HANDLE);
    keyboard->user_ptr = (void*)src_ptr;
}
void* lpwGetKeyboardUserPtr(LpwKeyboard keyboard)
{
    assert(keyboard != LPW_NULL_HANDLE);
    return keyboard->user_ptr;
}

void lpwSetKeyboardPfnCallback(LpwKeyboard keyboard, LpwEnumKeyboardEvent event, const void* src_ptr)
{
    assert(keyboard != LPW_NULL_HANDLE);
    switch(event)
    {
        case LPW_ENUM_KEYBOARD_EVENT_KEY: 
            keyboard->info.pfn_callback_list.pfn_key_callback = (PFN_LpwKeyboardKeyCallback)src_ptr;break;
        default: assert(0);
    }
}
void* lpwGetKeyboardPfnCallback(LpwKeyboard keyboard, LpwEnumKeyboardEvent event)
{
    assert(keyboard != LPW_NULL_HANDLE);
    switch(event)
    {
        case LPW_ENUM_KEYBOARD_EVENT_KEY: return keyboard->info.pfn_callback_list.pfn_key_callback;break;
        default: assert(0);
    }
    return NULL;
}

LpwKeyboard lpwGetKeyboard(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    return device->keyboard;
}
LpwDevice lpwGetDeviceFromKeyboard(LpwKeyboard keyboard)
{
    assert(keyboard != LPW_NULL_HANDLE);
    return keyboard->root_device;
}

void lpwSetKeyboardTimeInterval(LpwKeyboard keyboard, uint32_t time_interval)
{
    assert(keyboard != LPW_NULL_HANDLE);
    keyboard->info.time_interval = time_interval;
}

LpwEnumKeyboardKey lpw_global_keyboard_key_table[LPW_KEYBOARD_MAX_KEY_NUM];
LpwBool lpw_global_is_init_keyboard_key_table = LPW_FALSE;


#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )

static void lpwGlobalMapKeyboardKey()
{
    if(lpw_global_is_init_keyboard_key_table == LPW_TRUE) return;

    for(uint32_t i = 0; i < LPW_KEYBOARD_MAX_KEY_NUM; ++i)
    {
        lpw_global_keyboard_key_table[i] = LPW_ENUM_KEYBOARD_KEY_NULL;
    }

    lpw_global_keyboard_key_table['W'] = LPW_ENUM_KEYBOARD_KEY_W;
    lpw_global_keyboard_key_table['A'] = LPW_ENUM_KEYBOARD_KEY_A;
    lpw_global_keyboard_key_table['S'] = LPW_ENUM_KEYBOARD_KEY_S;
    lpw_global_keyboard_key_table['D'] = LPW_ENUM_KEYBOARD_KEY_D;
    //lpw_global_keyboard_key_table[] = LPW_ENUM_KEYBOARD_KEY;


    lpw_global_is_init_keyboard_key_table = LPW_TRUE;
}

#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

static void lpwGlobalMapKeyboardKey();

#endif
