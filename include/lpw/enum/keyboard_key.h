#pragma once

#include "../basic_type/basic_type.h"

typedef enum LpwEnumKeyboardKey
{
    LPW_ENUM_KEYBOARD_KEY_NULL,
    //number begin
    LPW_ENUM_KEYBOARD_KEY_NUM_0,
    LPW_ENUM_KEYBOARD_KEY_NUM_1,
    LPW_ENUM_KEYBOARD_KEY_NUM_2,
    LPW_ENUM_KEYBOARD_KEY_NUM_3,
    LPW_ENUM_KEYBOARD_KEY_NUM_4,
    LPW_ENUM_KEYBOARD_KEY_NUM_5,
    LPW_ENUM_KEYBOARD_KEY_NUM_6,
    LPW_ENUM_KEYBOARD_KEY_NUM_7,
    LPW_ENUM_KEYBOARD_KEY_NUM_8,
    LPW_ENUM_KEYBOARD_KEY_NUM_9,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_0,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_1,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_2,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_3,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_4,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_5,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_6,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_7,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_8,
    LPW_ENUM_KEYBOARD_KEY_NUMPAD_9,
    //number end
    //alphabet begin
    LPW_ENUM_KEYBOARD_KEY_A,
    LPW_ENUM_KEYBOARD_KEY_B,
    LPW_ENUM_KEYBOARD_KEY_C,
    LPW_ENUM_KEYBOARD_KEY_D,
    LPW_ENUM_KEYBOARD_KEY_E,
    LPW_ENUM_KEYBOARD_KEY_F,
    LPW_ENUM_KEYBOARD_KEY_G,
    LPW_ENUM_KEYBOARD_KEY_H,
    LPW_ENUM_KEYBOARD_KEY_I,
    LPW_ENUM_KEYBOARD_KEY_J,
    LPW_ENUM_KEYBOARD_KEY_K,
    LPW_ENUM_KEYBOARD_KEY_L,
    LPW_ENUM_KEYBOARD_KEY_M,
    LPW_ENUM_KEYBOARD_KEY_N,
    LPW_ENUM_KEYBOARD_KEY_O,
    LPW_ENUM_KEYBOARD_KEY_P,
    LPW_ENUM_KEYBOARD_KEY_Q,
    LPW_ENUM_KEYBOARD_KEY_R,
    LPW_ENUM_KEYBOARD_KEY_S,
    LPW_ENUM_KEYBOARD_KEY_T,
    LPW_ENUM_KEYBOARD_KEY_U,
    LPW_ENUM_KEYBOARD_KEY_V,
    LPW_ENUM_KEYBOARD_KEY_W,
    LPW_ENUM_KEYBOARD_KEY_X,
    LPW_ENUM_KEYBOARD_KEY_Y,
    LPW_ENUM_KEYBOARD_KEY_Z,
    //alphabet end
    //function key begin
    LPW_ENUM_KEYBOARD_KEY_F1 ,
    LPW_ENUM_KEYBOARD_KEY_F2 ,
    LPW_ENUM_KEYBOARD_KEY_F3 ,
    LPW_ENUM_KEYBOARD_KEY_F4 ,
    LPW_ENUM_KEYBOARD_KEY_F5 ,
    LPW_ENUM_KEYBOARD_KEY_F6 ,
    LPW_ENUM_KEYBOARD_KEY_F7 ,
    LPW_ENUM_KEYBOARD_KEY_F8 ,
    LPW_ENUM_KEYBOARD_KEY_F9 ,
    LPW_ENUM_KEYBOARD_KEY_F10,
    LPW_ENUM_KEYBOARD_KEY_F11,
    LPW_ENUM_KEYBOARD_KEY_F12,
    LPW_ENUM_KEYBOARD_KEY_F13,
    LPW_ENUM_KEYBOARD_KEY_F14,
    LPW_ENUM_KEYBOARD_KEY_F15,
    LPW_ENUM_KEYBOARD_KEY_F16,
    LPW_ENUM_KEYBOARD_KEY_F17,
    LPW_ENUM_KEYBOARD_KEY_F18,
    LPW_ENUM_KEYBOARD_KEY_F19,
    LPW_ENUM_KEYBOARD_KEY_F20,
    LPW_ENUM_KEYBOARD_KEY_F21,
    LPW_ENUM_KEYBOARD_KEY_F22,
    LPW_ENUM_KEYBOARD_KEY_F23,
    LPW_ENUM_KEYBOARD_KEY_F24,
    //function key end
    //arrow key begin
    LPW_ENUM_KEYBOARD_KEY_LEFT  ,
    LPW_ENUM_KEYBOARD_KEY_RIGHT ,
    LPW_ENUM_KEYBOARD_KEY_UP    ,
    LPW_ENUM_KEYBOARD_KEY_DOWN  ,
    //arrow key end
    //page key begin
    LPW_ENUM_KEYBOARD_KEY_PRIOR ,
    LPW_ENUM_KEYBOARD_KEY_NEXT  ,
    LPW_ENUM_KEYBOARD_KEY_HOME  ,
    LPW_ENUM_KEYBOARD_KEY_END   ,
    //page key end

    
    //extension for user key begin
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_0 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_1 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_2 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_3 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_4 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_5 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_6 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_7 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_8 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_9 ,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_10,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_11,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_12,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_13,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_14,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_15,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_16,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_17,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_18,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_19,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_20,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_21,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_22,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_23,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_24,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_25,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_26,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_27,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_28,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_29,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_30,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_31,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_32,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_33,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_34,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_35,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_36,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_37,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_38,
    LPW_ENUM_KEYBOARD_KEY_EXT_USER_39,
    //extension for user key end
    //LPW_ENUM_KEYBOARD_KEY_,
    LPW_ENUM_KEYBOARD_KEY_MAX_ENUM,
}LpwEnumKeyboardKey;
typedef LpwFlags LpwKeyboardKey;