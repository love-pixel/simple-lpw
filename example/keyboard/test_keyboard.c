#include "../../include/lpw/macro/platform_sdk.h"
#include "../../include/lpw/device/device.h"
#include "../../include/lpw/device/window/window.h"
#include "../../include/lpw/device/keyboard/keyboard.h"

#include "../../include/lpw/tool/enum_to_str.h"

#include <malloc.h>
#include <stdio.h>

void keyboardKeyCallback(LpwKeyboard keyboard, LpwEnumKeyboardKey key, LpwEnumKeyboardKeyEvent event)
{
    const char* key_head = "";
    lpwToolEnumKeyboardKeyToStr(key, &key_head);
    const char* event_head = "";
    lpwToolEnumKeyboardKeyEventToStr(event, &event_head);

    printf("Keyboard Callback: (%s,%s)Key(%s,%s)\n",
        key_head, event_head, lpwToolEnumKeyboardKeyToStr(key, NULL), lpwToolEnumKeyboardKeyEventToStr(event,NULL));
}

void platformKeyCodeCallback(uint32_t platform_key_code)
{
    printf("Platform Key Code: %d\n", platform_key_code);
}

int main()
{
#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )
    lpwPrivateSetGlobalKeyboardKeyMappingCode(8, LPW_ENUM_KEYBOARD_KEY_EXT_USER_0);//map the backspace(in windows the code is 8) key to EXT_USER_0
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )
    lpwPrivateSetGlobalKeyboardKeyMappingCode(22, LPW_ENUM_KEYBOARD_KEY_EXT_USER_0);//map the backspace(in xcb the code is 22) key to EXT_USER_0
#endif
    lpwSetGlobalPlatformKeyboardKeyCodePfnCallback(platformKeyCodeCallback);

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