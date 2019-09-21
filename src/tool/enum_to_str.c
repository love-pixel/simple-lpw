#include "../../include/lpw/tool/enum_to_str.h"

#include <stddef.h>

const char* lpwToolEnumMouseButtonEventToStr(LpwEnumMouseButtonEvent event, const char** head_str)
{
    if(head_str != NULL)
    {
        (*head_str) = "LpwEnumMouseButtonEvent";
    }
    switch(event)
    {
        case LPW_ENUM_MOUSE_BUTTON_EVENT_NULL       :   return "NULL"   ;
        case LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS      :   return "PRESS"  ;
        case LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE    :   return "RELEASE";
        case LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE     :   return "DOUBLE" ;
        default                                     :   return "Unknown";
    }
}
const char* lpwToolEnumMouseButtonToStr(LpwEnumMouseButton button, const char** head_str)
{
    if(head_str != NULL)
    {
        (*head_str) = "LpwEnumMouseButton";
    }
    switch(button)
    {
        case LPW_ENUM_MOUSE_BUTTON_NULL             :   return "NULL"    ;
        case LPW_ENUM_MOUSE_BUTTON_LEFT             :   return "LEFT"    ;
        case LPW_ENUM_MOUSE_BUTTON_MIDDLE           :   return "MIDDLE"  ;
        case LPW_ENUM_MOUSE_BUTTON_RIGHT            :   return "RIGHT"   ;
        case LPW_ENUM_MOUSE_BUTTON_FORWARD          :   return "FORWARD" ;
        case LPW_ENUM_MOUSE_BUTTON_BACKWARD         :   return "BACKWARD";
        default                                     :   return "Unknown" ;
    }
}
const char* lpwToolEnumMouseWheelToStr(LpwEnumMouseWheel wheel, const char** head_str)
{
    if(head_str != NULL)
    {
        (*head_str) = "LpwEnumMouseWheel";
    }
    switch(wheel)
    {
        case LPW_ENUM_MOUSE_WHEEL_NULL              :   return "NULL"     ;
        case LPW_ENUM_MOUSE_WHEEL_FORWARD           :   return "FORWARD"  ;
        case LPW_ENUM_MOUSE_WHEEL_BACKWARD          :   return "BACKWARD" ;
        case LPW_ENUM_MOUSE_WHEEL_LEFTWARD          :   return "LEFTWARD" ;
        case LPW_ENUM_MOUSE_WHEEL_RIGHTWARD         :   return "RIGHTWARD";
        default                                     :   return "Unknown";
    }
}

const char* lpwToolEnumKeyboardKeyToStr(LpwEnumKeyboardKey key, const char** head_str)
{
    if(head_str != NULL)
    {
        (*head_str) = "LpwEnumKeyboardKey";
    }
    switch(key)
    {
        case LPW_ENUM_KEYBOARD_KEY_NULL         :   return "NULL";
        //number begin
        case LPW_ENUM_KEYBOARD_KEY_NUM_0        :   return "NUM_0"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_1        :   return "NUM_1"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_2        :   return "NUM_2"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_3        :   return "NUM_3"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_4        :   return "NUM_4"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_5        :   return "NUM_5"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_6        :   return "NUM_6"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_7        :   return "NUM_7"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_8        :   return "NUM_8"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUM_9        :   return "NUM_9"   ;
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_0     :   return "NUMPAD_0";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_1     :   return "NUMPAD_1";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_2     :   return "NUMPAD_2";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_3     :   return "NUMPAD_3";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_4     :   return "NUMPAD_4";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_5     :   return "NUMPAD_5";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_6     :   return "NUMPAD_6";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_7     :   return "NUMPAD_7";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_8     :   return "NUMPAD_8";
        case LPW_ENUM_KEYBOARD_KEY_NUMPAD_9     :   return "NUMPAD_9";
        //number end
        //alphabet begin
        case LPW_ENUM_KEYBOARD_KEY_A            :   return "A"  ;
        case LPW_ENUM_KEYBOARD_KEY_B            :   return "B"  ;
        case LPW_ENUM_KEYBOARD_KEY_C            :   return "C"  ;
        case LPW_ENUM_KEYBOARD_KEY_D            :   return "D"  ;
        case LPW_ENUM_KEYBOARD_KEY_E            :   return "E"  ;
        case LPW_ENUM_KEYBOARD_KEY_F            :   return "F"  ;
        case LPW_ENUM_KEYBOARD_KEY_G            :   return "G"  ;
        case LPW_ENUM_KEYBOARD_KEY_H            :   return "H"  ;
        case LPW_ENUM_KEYBOARD_KEY_I            :   return "I"  ;
        case LPW_ENUM_KEYBOARD_KEY_J            :   return "J"  ;
        case LPW_ENUM_KEYBOARD_KEY_K            :   return "K"  ;
        case LPW_ENUM_KEYBOARD_KEY_L            :   return "L"  ;
        case LPW_ENUM_KEYBOARD_KEY_M            :   return "M"  ;
        case LPW_ENUM_KEYBOARD_KEY_N            :   return "N"  ;
        case LPW_ENUM_KEYBOARD_KEY_O            :   return "O"  ;
        case LPW_ENUM_KEYBOARD_KEY_P            :   return "P"  ;
        case LPW_ENUM_KEYBOARD_KEY_Q            :   return "Q"  ;
        case LPW_ENUM_KEYBOARD_KEY_R            :   return "R"  ;
        case LPW_ENUM_KEYBOARD_KEY_S            :   return "S"  ;
        case LPW_ENUM_KEYBOARD_KEY_T            :   return "T"  ;
        case LPW_ENUM_KEYBOARD_KEY_U            :   return "U"  ;
        case LPW_ENUM_KEYBOARD_KEY_V            :   return "V"  ;
        case LPW_ENUM_KEYBOARD_KEY_W            :   return "W"  ;
        case LPW_ENUM_KEYBOARD_KEY_X            :   return "X"  ;
        case LPW_ENUM_KEYBOARD_KEY_Y            :   return "Y"  ;
        case LPW_ENUM_KEYBOARD_KEY_Z            :   return "Z"  ;
        //alphabet end
        //function key begin
        case LPW_ENUM_KEYBOARD_KEY_F1           :   return "F1" ;
        case LPW_ENUM_KEYBOARD_KEY_F2           :   return "F2" ;
        case LPW_ENUM_KEYBOARD_KEY_F3           :   return "F3" ;
        case LPW_ENUM_KEYBOARD_KEY_F4           :   return "F4" ;
        case LPW_ENUM_KEYBOARD_KEY_F5           :   return "F5" ;
        case LPW_ENUM_KEYBOARD_KEY_F6           :   return "F6" ;
        case LPW_ENUM_KEYBOARD_KEY_F7           :   return "F7" ;
        case LPW_ENUM_KEYBOARD_KEY_F8           :   return "F8" ;
        case LPW_ENUM_KEYBOARD_KEY_F9           :   return "F9" ;
        case LPW_ENUM_KEYBOARD_KEY_F10          :   return "F10";
        case LPW_ENUM_KEYBOARD_KEY_F11          :   return "F11";
        case LPW_ENUM_KEYBOARD_KEY_F12          :   return "F12";
        case LPW_ENUM_KEYBOARD_KEY_F13          :   return "F13";
        case LPW_ENUM_KEYBOARD_KEY_F14          :   return "F14";
        case LPW_ENUM_KEYBOARD_KEY_F15          :   return "F15";
        case LPW_ENUM_KEYBOARD_KEY_F16          :   return "F16";
        case LPW_ENUM_KEYBOARD_KEY_F17          :   return "F17";
        case LPW_ENUM_KEYBOARD_KEY_F18          :   return "F18";
        case LPW_ENUM_KEYBOARD_KEY_F19          :   return "F19";
        case LPW_ENUM_KEYBOARD_KEY_F20          :   return "F20";
        case LPW_ENUM_KEYBOARD_KEY_F21          :   return "F21";
        case LPW_ENUM_KEYBOARD_KEY_F22          :   return "F22";
        case LPW_ENUM_KEYBOARD_KEY_F23          :   return "F23";
        case LPW_ENUM_KEYBOARD_KEY_F24          :   return "F24";
        //function key end
        //arrow key begin
        case LPW_ENUM_KEYBOARD_KEY_LEFT         :   return "LEFT" ;
        case LPW_ENUM_KEYBOARD_KEY_RIGHT        :   return "RIGHT";
        case LPW_ENUM_KEYBOARD_KEY_UP           :   return "UP"   ;
        case LPW_ENUM_KEYBOARD_KEY_DOWN         :   return "DOWN" ;
        //arrow key end
        //page key begin
        case LPW_ENUM_KEYBOARD_KEY_PRIOR        :   return "PRIOR";
        case LPW_ENUM_KEYBOARD_KEY_NEXT         :   return "NEXT" ;
        case LPW_ENUM_KEYBOARD_KEY_HOME         :   return "HOME" ;
        case LPW_ENUM_KEYBOARD_KEY_END          :   return "END"  ;
        //page key end
        default                                 :   return "Uknown";
    }
}
const char* lpwToolEnumKeyboardKeyEventToStr(LpwEnumKeyboardKeyEvent event, const char** head_str)
{
    if(head_str != NULL)
    {
        (*head_str) = "LpwEnumKeyboardKeyEvent";
    }
    switch(event)
    {
        case LPW_ENUM_KEYBOARD_KEY_EVENT_NULL       :   return "NULL"   ;
        case LPW_ENUM_KEYBOARD_KEY_EVENT_PRESS      :   return "PRESS"  ;
        case LPW_ENUM_KEYBOARD_KEY_EVENT_RELEASE    :   return "RELEASE";
        case LPW_ENUM_KEYBOARD_KEY_EVENT_DOUBLE     :   return "DOUBLE" ;
        default                                     :   return "Unknown";
    }
}
const char* lpwToolEnumKeyboardKeyStateToStr(LpwEnumKeyboardKeyState state, const char** head_str)
{
    if(head_str != NULL)
    {
        (*head_str) = "LpwEnumKeyboardKeyState";
    }
    switch(state)
    {
        case LPW_ENUM_KEYBOARD_KEY_STATE_NULL       :   return "NULL"    ;
        case LPW_ENUM_KEYBOARD_KEY_STATE_ACTIVE     :   return "ACTIVE"  ;
        case LPW_ENUM_KEYBOARD_KEY_STATE_INACTIVE   :   return "INACTIVE";
        default                                     :   return "Unknown" ;
    }
}