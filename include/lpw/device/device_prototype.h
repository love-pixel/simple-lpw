#pragma once

#include "device.h"
#include "platform_data.h"
//#include "platform_data_prototype.h"

#include "window/window.h"
#include "mouse/mouse.h"
//#include "keyboard/keyboard.h"

typedef struct LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwDevice)
{
    LpwDevice       root;
    void*           user_ptr;
    LpwPlatformData platform_data;
    LpwWindow       window;
    LpwMouse        mouse;
    //LpwKeyboard     keyboard;
}LPW_MAKE_HANDLE_PROTOTYPE_NAME(LpwDevice);