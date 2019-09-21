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
        keyboard->info.pre_time_table[key] = 0;
#endif
    }
    keyboard->info.pfn_callback_list.pfn_key_callback = NULL;
#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
    keyboard->info.time_interval = 250;//millisecond
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )
    keyboard->info.time_interval = 250 * 1000;//microsecond
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
    //keyboard->info.time_interval = time_interval;
#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
    keyboard->info.time_interval = time_interval;//millisecond
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )
    keyboard->info.time_interval = time_interval * 1000;//microsecond
#endif
}

LpwEnumKeyboardKey lpw_global_keyboard_key_table[LPW_KEYBOARD_MAX_KEY_NUM];
LpwBool lpw_global_is_init_keyboard_key_table = LPW_FALSE;
PFN_LpwPlatformKeyboardKeyCodeCallback lpw_global_platform_keyboard_key_code_callback = NULL;


void lpwPrivateSetGlobalKeyboardKeyMappingCode(uint32_t platform_key_code, LpwEnumKeyboardKey key)
{
    //assert(lpw_global_is_init_keyboard_key_table == LPW_TRUE);
    assert(platform_key_code < LPW_KEYBOARD_MAX_KEY_NUM);
    lpw_global_keyboard_key_table[platform_key_code] = key;
}

void lpwSetGlobalPlatformKeyboardKeyCodePfnCallback(PFN_LpwPlatformKeyboardKeyCodeCallback pfn_callback)
{
    lpw_global_platform_keyboard_key_code_callback = pfn_callback;
}

#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )

static void lpwGlobalMapKeyboardKey()
{
    if(lpw_global_is_init_keyboard_key_table == LPW_TRUE) return;

    //for(uint32_t i = 0; i < LPW_KEYBOARD_MAX_KEY_NUM; ++i)
    //{
    //    lpw_global_keyboard_key_table[i] = LPW_ENUM_KEYBOARD_KEY_NULL;
    //}

    //number begin
    lpw_global_keyboard_key_table['0'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_0;
    lpw_global_keyboard_key_table['1'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_1;
    lpw_global_keyboard_key_table['2'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_2;
    lpw_global_keyboard_key_table['3'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_3;
    lpw_global_keyboard_key_table['4'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_4;
    lpw_global_keyboard_key_table['5'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_5;
    lpw_global_keyboard_key_table['6'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_6;
    lpw_global_keyboard_key_table['7'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_7;
    lpw_global_keyboard_key_table['8'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_8;
    lpw_global_keyboard_key_table['9'       ] = LPW_ENUM_KEYBOARD_KEY_NUM_9;
    lpw_global_keyboard_key_table[VK_NUMPAD0] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_0;
    lpw_global_keyboard_key_table[VK_NUMPAD1] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_1;
    lpw_global_keyboard_key_table[VK_NUMPAD2] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_2;
    lpw_global_keyboard_key_table[VK_NUMPAD3] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_3;
    lpw_global_keyboard_key_table[VK_NUMPAD4] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_4;
    lpw_global_keyboard_key_table[VK_NUMPAD5] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_5;
    lpw_global_keyboard_key_table[VK_NUMPAD6] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_6;
    lpw_global_keyboard_key_table[VK_NUMPAD7] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_7;
    lpw_global_keyboard_key_table[VK_NUMPAD8] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_8;
    lpw_global_keyboard_key_table[VK_NUMPAD9] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_9;
    //lpw_global_keyboard_key_table[''] = LPW_ENUM_KEYBOARD_KEY;
    //number end
    //alphabet begin
    lpw_global_keyboard_key_table['A'       ] = LPW_ENUM_KEYBOARD_KEY_A;
    lpw_global_keyboard_key_table['B'       ] = LPW_ENUM_KEYBOARD_KEY_B;
    lpw_global_keyboard_key_table['C'       ] = LPW_ENUM_KEYBOARD_KEY_C;
    lpw_global_keyboard_key_table['D'       ] = LPW_ENUM_KEYBOARD_KEY_D;
    lpw_global_keyboard_key_table['E'       ] = LPW_ENUM_KEYBOARD_KEY_E;
    lpw_global_keyboard_key_table['F'       ] = LPW_ENUM_KEYBOARD_KEY_F;
    lpw_global_keyboard_key_table['G'       ] = LPW_ENUM_KEYBOARD_KEY_G;
    lpw_global_keyboard_key_table['H'       ] = LPW_ENUM_KEYBOARD_KEY_H;
    lpw_global_keyboard_key_table['I'       ] = LPW_ENUM_KEYBOARD_KEY_I;
    lpw_global_keyboard_key_table['J'       ] = LPW_ENUM_KEYBOARD_KEY_J;
    lpw_global_keyboard_key_table['K'       ] = LPW_ENUM_KEYBOARD_KEY_K;
    lpw_global_keyboard_key_table['L'       ] = LPW_ENUM_KEYBOARD_KEY_L;
    lpw_global_keyboard_key_table['M'       ] = LPW_ENUM_KEYBOARD_KEY_M;
    lpw_global_keyboard_key_table['N'       ] = LPW_ENUM_KEYBOARD_KEY_N;
    lpw_global_keyboard_key_table['O'       ] = LPW_ENUM_KEYBOARD_KEY_O;
    lpw_global_keyboard_key_table['P'       ] = LPW_ENUM_KEYBOARD_KEY_P;
    lpw_global_keyboard_key_table['Q'       ] = LPW_ENUM_KEYBOARD_KEY_Q;
    lpw_global_keyboard_key_table['R'       ] = LPW_ENUM_KEYBOARD_KEY_R;
    lpw_global_keyboard_key_table['S'       ] = LPW_ENUM_KEYBOARD_KEY_S;
    lpw_global_keyboard_key_table['T'       ] = LPW_ENUM_KEYBOARD_KEY_T;
    lpw_global_keyboard_key_table['U'       ] = LPW_ENUM_KEYBOARD_KEY_U;
    lpw_global_keyboard_key_table['V'       ] = LPW_ENUM_KEYBOARD_KEY_V;
    lpw_global_keyboard_key_table['W'       ] = LPW_ENUM_KEYBOARD_KEY_W;
    lpw_global_keyboard_key_table['X'       ] = LPW_ENUM_KEYBOARD_KEY_X;
    lpw_global_keyboard_key_table['Y'       ] = LPW_ENUM_KEYBOARD_KEY_Y;
    lpw_global_keyboard_key_table['Z'       ] = LPW_ENUM_KEYBOARD_KEY_Z;
    //lpw_global_keyboard_key_table[''] = LPW_ENUM_KEYBOARD_KEY;
    //alphabet end
    //function key begin
    lpw_global_keyboard_key_table[VK_F1     ] = LPW_ENUM_KEYBOARD_KEY_F1 ;
    lpw_global_keyboard_key_table[VK_F2     ] = LPW_ENUM_KEYBOARD_KEY_F2 ;
    lpw_global_keyboard_key_table[VK_F3     ] = LPW_ENUM_KEYBOARD_KEY_F3 ;
    lpw_global_keyboard_key_table[VK_F4     ] = LPW_ENUM_KEYBOARD_KEY_F4 ;
    lpw_global_keyboard_key_table[VK_F5     ] = LPW_ENUM_KEYBOARD_KEY_F5 ;
    lpw_global_keyboard_key_table[VK_F6     ] = LPW_ENUM_KEYBOARD_KEY_F6 ;
    lpw_global_keyboard_key_table[VK_F7     ] = LPW_ENUM_KEYBOARD_KEY_F7 ;
    lpw_global_keyboard_key_table[VK_F8     ] = LPW_ENUM_KEYBOARD_KEY_F8 ;
    lpw_global_keyboard_key_table[VK_F9     ] = LPW_ENUM_KEYBOARD_KEY_F9 ;
    lpw_global_keyboard_key_table[VK_F10    ] = LPW_ENUM_KEYBOARD_KEY_F10;
    lpw_global_keyboard_key_table[VK_F11    ] = LPW_ENUM_KEYBOARD_KEY_F11;
    lpw_global_keyboard_key_table[VK_F12    ] = LPW_ENUM_KEYBOARD_KEY_F12;
    lpw_global_keyboard_key_table[VK_F13    ] = LPW_ENUM_KEYBOARD_KEY_F13;
    lpw_global_keyboard_key_table[VK_F14    ] = LPW_ENUM_KEYBOARD_KEY_F14;
    lpw_global_keyboard_key_table[VK_F15    ] = LPW_ENUM_KEYBOARD_KEY_F15;
    lpw_global_keyboard_key_table[VK_F16    ] = LPW_ENUM_KEYBOARD_KEY_F16;
    lpw_global_keyboard_key_table[VK_F17    ] = LPW_ENUM_KEYBOARD_KEY_F17;
    lpw_global_keyboard_key_table[VK_F18    ] = LPW_ENUM_KEYBOARD_KEY_F18;
    lpw_global_keyboard_key_table[VK_F19    ] = LPW_ENUM_KEYBOARD_KEY_F19;
    lpw_global_keyboard_key_table[VK_F20    ] = LPW_ENUM_KEYBOARD_KEY_F20;
    lpw_global_keyboard_key_table[VK_F21    ] = LPW_ENUM_KEYBOARD_KEY_F21;
    lpw_global_keyboard_key_table[VK_F22    ] = LPW_ENUM_KEYBOARD_KEY_F22;
    lpw_global_keyboard_key_table[VK_F23    ] = LPW_ENUM_KEYBOARD_KEY_F23;
    lpw_global_keyboard_key_table[VK_F24    ] = LPW_ENUM_KEYBOARD_KEY_F24;
    //function key end
    //arrow key begin
    lpw_global_keyboard_key_table[VK_LEFT   ] = LPW_ENUM_KEYBOARD_KEY_LEFT ;
    lpw_global_keyboard_key_table[VK_RIGHT  ] = LPW_ENUM_KEYBOARD_KEY_RIGHT;
    lpw_global_keyboard_key_table[VK_UP     ] = LPW_ENUM_KEYBOARD_KEY_UP   ;
    lpw_global_keyboard_key_table[VK_DOWN   ] = LPW_ENUM_KEYBOARD_KEY_DOWN ;
    //arrow key end
    //page key begin
    lpw_global_keyboard_key_table[VK_PRIOR	] = LPW_ENUM_KEYBOARD_KEY_PRIOR;
    lpw_global_keyboard_key_table[VK_NEXT	] = LPW_ENUM_KEYBOARD_KEY_NEXT ;
    lpw_global_keyboard_key_table[VK_HOME	] = LPW_ENUM_KEYBOARD_KEY_HOME ;
    lpw_global_keyboard_key_table[VK_END    ] = LPW_ENUM_KEYBOARD_KEY_END  ;
    //page key end
    //lpw_global_keyboard_key_table[] = LPW_ENUM_KEYBOARD_KEY;


    lpw_global_is_init_keyboard_key_table = LPW_TRUE;
}

#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

static void lpwGlobalMapKeyboardKey()
{
    if(lpw_global_is_init_keyboard_key_table == LPW_TRUE) return;

    //for(uint32_t i = 0; i < LPW_KEYBOARD_MAX_KEY_NUM; ++i)
    //{
    //    lpw_global_keyboard_key_table[i] = LPW_ENUM_KEYBOARD_KEY_NULL;
    //}

    //number begin
    lpw_global_keyboard_key_table[19        ] = LPW_ENUM_KEYBOARD_KEY_NUM_0;
    lpw_global_keyboard_key_table[10        ] = LPW_ENUM_KEYBOARD_KEY_NUM_1;
    lpw_global_keyboard_key_table[11        ] = LPW_ENUM_KEYBOARD_KEY_NUM_2;
    lpw_global_keyboard_key_table[12        ] = LPW_ENUM_KEYBOARD_KEY_NUM_3;
    lpw_global_keyboard_key_table[13        ] = LPW_ENUM_KEYBOARD_KEY_NUM_4;
    lpw_global_keyboard_key_table[14        ] = LPW_ENUM_KEYBOARD_KEY_NUM_5;
    lpw_global_keyboard_key_table[15        ] = LPW_ENUM_KEYBOARD_KEY_NUM_6;
    lpw_global_keyboard_key_table[16        ] = LPW_ENUM_KEYBOARD_KEY_NUM_7;
    lpw_global_keyboard_key_table[17        ] = LPW_ENUM_KEYBOARD_KEY_NUM_8;
    lpw_global_keyboard_key_table[18        ] = LPW_ENUM_KEYBOARD_KEY_NUM_9;
    lpw_global_keyboard_key_table[90        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_0;
    lpw_global_keyboard_key_table[87        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_1;
    lpw_global_keyboard_key_table[88        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_2;
    lpw_global_keyboard_key_table[89        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_3;
    lpw_global_keyboard_key_table[83        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_4;
    lpw_global_keyboard_key_table[84        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_5;
    lpw_global_keyboard_key_table[85        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_6;
    lpw_global_keyboard_key_table[79        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_7;
    lpw_global_keyboard_key_table[80        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_8;
    lpw_global_keyboard_key_table[81        ] = LPW_ENUM_KEYBOARD_KEY_NUMPAD_9;
    //lpw_global_keyboard_key_table[''] = LPW_ENUM_KEYBOARD_KEY;
    //number end
    //alphabet begin
    lpw_global_keyboard_key_table[38       ] = LPW_ENUM_KEYBOARD_KEY_A;
    lpw_global_keyboard_key_table[56       ] = LPW_ENUM_KEYBOARD_KEY_B;
    lpw_global_keyboard_key_table[54       ] = LPW_ENUM_KEYBOARD_KEY_C;
    lpw_global_keyboard_key_table[40       ] = LPW_ENUM_KEYBOARD_KEY_D;
    lpw_global_keyboard_key_table[26       ] = LPW_ENUM_KEYBOARD_KEY_E;
    lpw_global_keyboard_key_table[41       ] = LPW_ENUM_KEYBOARD_KEY_F;
    lpw_global_keyboard_key_table[42       ] = LPW_ENUM_KEYBOARD_KEY_G;
    lpw_global_keyboard_key_table[43       ] = LPW_ENUM_KEYBOARD_KEY_H;
    lpw_global_keyboard_key_table[31       ] = LPW_ENUM_KEYBOARD_KEY_I;
    lpw_global_keyboard_key_table[44       ] = LPW_ENUM_KEYBOARD_KEY_J;
    lpw_global_keyboard_key_table[45       ] = LPW_ENUM_KEYBOARD_KEY_K;
    lpw_global_keyboard_key_table[46       ] = LPW_ENUM_KEYBOARD_KEY_L;
    lpw_global_keyboard_key_table[58       ] = LPW_ENUM_KEYBOARD_KEY_M;
    lpw_global_keyboard_key_table[57       ] = LPW_ENUM_KEYBOARD_KEY_N;
    lpw_global_keyboard_key_table[32       ] = LPW_ENUM_KEYBOARD_KEY_O;
    lpw_global_keyboard_key_table[33       ] = LPW_ENUM_KEYBOARD_KEY_P;
    lpw_global_keyboard_key_table[24       ] = LPW_ENUM_KEYBOARD_KEY_Q;
    lpw_global_keyboard_key_table[27       ] = LPW_ENUM_KEYBOARD_KEY_R;
    lpw_global_keyboard_key_table[39       ] = LPW_ENUM_KEYBOARD_KEY_S;
    lpw_global_keyboard_key_table[28       ] = LPW_ENUM_KEYBOARD_KEY_T;
    lpw_global_keyboard_key_table[30       ] = LPW_ENUM_KEYBOARD_KEY_U;
    lpw_global_keyboard_key_table[55       ] = LPW_ENUM_KEYBOARD_KEY_V;
    lpw_global_keyboard_key_table[25       ] = LPW_ENUM_KEYBOARD_KEY_W;
    lpw_global_keyboard_key_table[53       ] = LPW_ENUM_KEYBOARD_KEY_X;
    lpw_global_keyboard_key_table[29       ] = LPW_ENUM_KEYBOARD_KEY_Y;
    lpw_global_keyboard_key_table[52       ] = LPW_ENUM_KEYBOARD_KEY_Z;
    //lpw_global_keyboard_key_table[''] = LPW_ENUM_KEYBOARD_KEY;
    //alphabet end
    //function key begin
    lpw_global_keyboard_key_table[67        ] = LPW_ENUM_KEYBOARD_KEY_F1 ;
    lpw_global_keyboard_key_table[68        ] = LPW_ENUM_KEYBOARD_KEY_F2 ;
    lpw_global_keyboard_key_table[69        ] = LPW_ENUM_KEYBOARD_KEY_F3 ;
    lpw_global_keyboard_key_table[70        ] = LPW_ENUM_KEYBOARD_KEY_F4 ;
    lpw_global_keyboard_key_table[71        ] = LPW_ENUM_KEYBOARD_KEY_F5 ;
    lpw_global_keyboard_key_table[72        ] = LPW_ENUM_KEYBOARD_KEY_F6 ;
    lpw_global_keyboard_key_table[73        ] = LPW_ENUM_KEYBOARD_KEY_F7 ;
    lpw_global_keyboard_key_table[74        ] = LPW_ENUM_KEYBOARD_KEY_F8 ;
    lpw_global_keyboard_key_table[75        ] = LPW_ENUM_KEYBOARD_KEY_F9 ;
    lpw_global_keyboard_key_table[76        ] = LPW_ENUM_KEYBOARD_KEY_F10;
    lpw_global_keyboard_key_table[95        ] = LPW_ENUM_KEYBOARD_KEY_F11;
    lpw_global_keyboard_key_table[96        ] = LPW_ENUM_KEYBOARD_KEY_F12;
//    lpw_global_keyboard_key_table[VK_F13    ] = LPW_ENUM_KEYBOARD_KEY_F13;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F14    ] = LPW_ENUM_KEYBOARD_KEY_F14;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F15    ] = LPW_ENUM_KEYBOARD_KEY_F15;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F16    ] = LPW_ENUM_KEYBOARD_KEY_F16;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F17    ] = LPW_ENUM_KEYBOARD_KEY_F17;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F18    ] = LPW_ENUM_KEYBOARD_KEY_F18;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F19    ] = LPW_ENUM_KEYBOARD_KEY_F19;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F20    ] = LPW_ENUM_KEYBOARD_KEY_F20;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F21    ] = LPW_ENUM_KEYBOARD_KEY_F21;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F22    ] = LPW_ENUM_KEYBOARD_KEY_F22;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F23    ] = LPW_ENUM_KEYBOARD_KEY_F23;//i don't know the key code
//    lpw_global_keyboard_key_table[VK_F24    ] = LPW_ENUM_KEYBOARD_KEY_F24;//i don't know the key code
//    //function key end
    //arrow key begin
    lpw_global_keyboard_key_table[113       ] = LPW_ENUM_KEYBOARD_KEY_LEFT ;
    lpw_global_keyboard_key_table[114       ] = LPW_ENUM_KEYBOARD_KEY_RIGHT;
    lpw_global_keyboard_key_table[111       ] = LPW_ENUM_KEYBOARD_KEY_UP   ;
    lpw_global_keyboard_key_table[116       ] = LPW_ENUM_KEYBOARD_KEY_DOWN ;
    //arrow key end
    //page key begin
    lpw_global_keyboard_key_table[112	    ] = LPW_ENUM_KEYBOARD_KEY_PRIOR;
    lpw_global_keyboard_key_table[117	    ] = LPW_ENUM_KEYBOARD_KEY_NEXT ;
    lpw_global_keyboard_key_table[110	    ] = LPW_ENUM_KEYBOARD_KEY_HOME ;
    lpw_global_keyboard_key_table[115       ] = LPW_ENUM_KEYBOARD_KEY_END  ;
    //page key end
    //lpw_global_keyboard_key_table[] = LPW_ENUM_KEYBOARD_KEY;


    lpw_global_is_init_keyboard_key_table = LPW_TRUE;
}

#endif
