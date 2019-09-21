#include "../../include/lpw/device/device.h"
#include "../../include/lpw/device/window/window.h"

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

    lpwSetWindowUserPtr(window, "Hello Ptr");
    printf("%s\n", (char*)lpwGetWindowUserPtr(window));

    lpwSetWindowPfnCallback(window, LPW_ENUM_WINDOW_EVENT_POS, windowPosCallback);
    lpwSetWindowPfnCallback(window, LPW_ENUM_WINDOW_EVENT_SIZE, windowSizeCallback);

    while(lpwIsWindowActive(window) == LPW_TRUE)
    {
        lpwProcessEventByPoll(device);
    }
    lpwDestroyWindow(window);
    printf("%s\n", (char*)lpwGetWindowUserPtr(window));
    lpwDestroyDevice(device);
    //system("pause");
    return 0;
}