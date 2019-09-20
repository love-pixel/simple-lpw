#include "../../include/lpw/device/device.h"
#include "../../include/lpw/device/window/window.h"
#include "../../include/lpw/device/keyboard/keyboard.h"

#include <malloc.h>
#include <stdio.h>

void keyboardKeyCallback(LpwKeyboard keyboard, LpwEnumKeyboardKey key, LpwEnumKeyboardKeyEvent event)
{
    const char* ckey = "Unknown";
    const char* cevent = "Unknown";
    switch(key)
    {
        case LPW_ENUM_KEYBOARD_KEY_W: ckey = "W";break;
        case LPW_ENUM_KEYBOARD_KEY_A: ckey = "A";break;
        case LPW_ENUM_KEYBOARD_KEY_S: ckey = "S";break;
        case LPW_ENUM_KEYBOARD_KEY_D: ckey = "D";break;
    }
    switch(event)
    {
        case LPW_ENUM_KEYBOARD_KEY_EVENT_PRESS: cevent = "PRESS";break;
        case LPW_ENUM_KEYBOARD_KEY_EVENT_RELEASE: cevent = "RELEASE";break;
        case LPW_ENUM_KEYBOARD_KEY_EVENT_DOUBLE: cevent = "DOUBLE";break;
    }
    printf("Keyboard Callback: Key(%s,%s)\n",ckey, cevent);
}

int main()
{
    LpwDevice device = lpwCreateDevice(NULL);
    LpwWindowCreateInfo window_ci;
    {
        window_ci.pos.x = 200;
        window_ci.pos.y = 100;
        window_ci.size.x = 800;
        window_ci.size.y = 600;
        window_ci.name = "NULL";
        window_ci.user_ptr = NULL;
        window_ci.pfn_callback_list_ptr = NULL;
    }
    LpwWindow window = lpwCreateWindow(device, &window_ci);
    LpwKeyboard keyboard = lpwCreateKeyboard(device, NULL);
    keyboard = lpwGetKeyboard(device);

    lpwSetKeyboardPfnCallback(keyboard, LPW_ENUM_KEYBOARD_EVENT_KEY, keyboardKeyCallback);

    while(lpwIsWindowActive(window) == LPW_TRUE)
    {
        lpwProcessEventByPoll(device);
    }
    lpwDestroyKeyboard(keyboard);
    lpwDestroyWindow(window);
    lpwDestroyDevice(device);
    //system("pause");
    return 0;
}