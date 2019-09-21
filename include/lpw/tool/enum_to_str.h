#pragma once

//#include "../enum/result.h"
//#include "../enum/process_event_type.h"
#include "../enum/window_event.h"
#include "../enum/mouse_event.h"
#include "../enum/mouse_button.h"
#include "../enum/mouse_wheel.h"
//#include "../enum/mouse_pos_flag.h"
#include "../enum/keyboard_event.h"
#include "../enum/keyboard_key.h"
#include "../enum/keyboard_key_state.h"
//#include "../enum"


const char* lpwToolEnumMouseButtonEventToStr(LpwEnumMouseButtonEvent event, const char** head_str);
const char* lpwToolEnumMouseButtonToStr(LpwEnumMouseButton button, const char** head_str);
const char* lpwToolEnumMouseWheelToStr(LpwEnumMouseWheel wheel, const char** head_str);

const char* lpwToolEnumKeyboardKeyToStr(LpwEnumKeyboardKey key, const char** head_str);
const char* lpwToolEnumKeyboardKeyEventToStr(LpwEnumKeyboardKeyEvent event, const char** head_str);
const char* lpwToolEnumKeyboardKeyStateToStr(LpwEnumKeyboardKeyState state, const char** head_str);