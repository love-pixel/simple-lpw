#include "../../include/lpw/device/device.h"
#include "../../include/lpw/device/window/window.h"
#include "../../include/lpw/device/mouse/mouse.h"

#include <malloc.h>
#include <stdio.h>

void windowPosCallback(LpwWindow window, int32_t x, int32_t y)
{
    printf("Window Callback: Pos(%d,%d)\n", x, y);
}

void windowSizeCallback(LpwWindow window, uint32_t x, uint32_t y)
{
    printf("Window Callback: Size(%d,%d)\n", x, y);
}

void mousePosCallback(LpwMouse mouse, uint32_t x, uint32_t y)
{
    printf("Mouse Callback: Pos(%d,%d)\n",x,y);
}

void mouseButtonCallback(LpwMouse mouse, LpwEnumMouseButton button, LpwEnumMouseButtonEvent event)
{
    const char* cbutton = "";
    const char* cevent = "";
    switch(button){
        case LPW_ENUM_MOUSE_BUTTON_LEFT: cbutton = "LEFT";break;
        case LPW_ENUM_MOUSE_BUTTON_MIDDLE: cbutton = "MIDDLE";break;
        case LPW_ENUM_MOUSE_BUTTON_RIGHT: cbutton = "RIGHT";break;
        case LPW_ENUM_MOUSE_BUTTON_FORWARD: cbutton = "FORWARD";break;
        case LPW_ENUM_MOUSE_BUTTON_BACKWARD: cbutton = "BACKWARD";break;
        //case LPW_ENUM_MOUSE_BUTTON_: cbutton = "";break;
    }
    switch(event){
        case LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS: cevent = "PRESS";break;
        case LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE: cevent = "RELEASE";break;
        case LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE: cevent = "DOUBLE";break;
        //case LPW_ENUM_MOUSE_BUTTON_EVENT_: cevent = "";break;
    }
    printf("Mouse Callback: Button(%s,%s)\n", cbutton, cevent);
}

void mouseWheelCallback(LpwMouse mouse, LpwEnumMouseWheel wheel)
{
    const char* cwheel = "";
    switch(wheel){
        case LPW_ENUM_MOUSE_WHEEL_FORWARD: cwheel = "FORWARD";break;
        case LPW_ENUM_MOUSE_WHEEL_BACKWARD: cwheel = "BACKWARD";break;
        case LPW_ENUM_MOUSE_WHEEL_LEFTWARD: cwheel = "LEFTWARD";break;
        case LPW_ENUM_MOUSE_WHEEL_RIGHTWARD: cwheel = "RIGHTWARD";break;
        //case LPW_ENUM_MOUSE_WHEEL_: cwheel = "";break;
    }
    printf("Mouse Callback: Wheel(%s)\n", cwheel);
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
    LpwMouse mouse = lpwCreateMouse(device, NULL);

    lpwSetWindowUserPtr(window, "Hello Ptr");
    printf("%s\n", lpwGetWindowUserPtr(window));

    lpwSetWindowPfnCallback(window, LPW_ENUM_WINDOW_EVENT_POS, windowPosCallback);
    lpwSetWindowPfnCallback(window, LPW_ENUM_WINDOW_EVENT_SIZE, windowSizeCallback);

    lpwSetMousePfnCallback(mouse, LPW_ENUM_MOUSE_EVENT_POS, mousePosCallback);
    lpwSetMousePfnCallback(mouse, LPW_ENUM_MOUSE_EVENT_BUTTON, mouseButtonCallback);
    lpwSetMousePfnCallback(mouse, LPW_ENUM_MOUSE_EVENT_WHEEL, mouseWheelCallback);
    //lpwSetMousePfnCallback(mouse, LPW_ENUM_MOUSE_EVENT_, mouseCallback);

    while(lpwIsWindowActive(window) == LPW_TRUE)
    {
        lpwProcessEventByPoll(device);
    }
    lpwDestroyWindow(window);
    printf("%s\n", lpwGetWindowUserPtr(window));
    lpwDestroyDevice(device);
    system("pause");
    return 0;
}