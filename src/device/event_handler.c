#include "../../include/lpw/device/event_handler.h"
#include "../../include/lpw/device/device_prototype.h"
#include "../../include/lpw/device/window/window_prototype.h"
#include "../../include/lpw/device/mouse/mouse_prototype.h"
#include "../../include/lpw/device/keyboard/keyboard_prototype.h"
#include "../../include/lpw/device/platform_data_prototype.h"

#include <assert.h>

#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )

LRESULT CALLBACK _lpwDeviceEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    LpwDevice device = (LpwDevice)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    if(device == LPW_NULL_HANDLE) return DefWindowProc(hWnd, uMsg, wParam, lParam);
    LpwWindow window = device->window;
    LpwMouse mouse = device->mouse;
    LpwKeyboard keyboard = device->keyboard;
    switch(uMsg)
    {
        //window
        case WM_MOVE:{
            if(window != LPW_NULL_HANDLE)
            {
                RECT window_rect;
                GetWindowRect(hWnd, &window_rect);
                window->info.pos.x = window_rect.left;
                window->info.pos.y = window_rect.top;
                if(window->info.pfn_callback_list.pfn_pos_callback != NULL)
                {
                    window->info.pfn_callback_list.pfn_pos_callback(window, window->info.pos.x, window->info.pos.y);
                }
            }
        }break;
        case WM_SIZE:{
            if(window != LPW_NULL_HANDLE)
            {
                RECT window_rect;
                GetWindowRect(hWnd, &window_rect);
                window->info.size.x = window_rect.right - window_rect.left;
                window->info.size.y = window_rect.bottom - window_rect.top;
                if(window->info.pfn_callback_list.pfn_size_callback != NULL)
                {
                    window->info.pfn_callback_list.pfn_size_callback(window, window->info.size.x, window->info.size.y);
                }
            }
        }break;
        case WM_CLOSE:{
            if(window != LPW_NULL_HANDLE)
            {
                window->info.is_active = LPW_FALSE;
            }
        }break;
        //mouse
        case WM_LBUTTONDOWN:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_LEFT, LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS);
        }break;
        case WM_LBUTTONUP:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_LEFT, LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE);
        }break;
        case WM_LBUTTONDBLCLK:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_LEFT, LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE);
        }break;

        case WM_MBUTTONDOWN:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_MIDDLE, LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS);
        }break;
        case WM_MBUTTONUP:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_MIDDLE, LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE);
        }break;
        case WM_MBUTTONDBLCLK:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_MIDDLE, LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE);
        }break;

        case WM_RBUTTONDOWN:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_RIGHT, LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS);
        }break;
        case WM_RBUTTONUP:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_RIGHT, LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE);
        }break;
        case WM_RBUTTONDBLCLK:{
            lpwProcessMouseButtonEvent(mouse, LPW_ENUM_MOUSE_BUTTON_RIGHT, LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE);
        }break;
/**
 * #if (_WIN32_WINNT >= 0x0500)
 * #define WM_XBUTTONDOWN 523
 * #define WM_XBUTTONUP 524
 * #define WM_XBUTTONDBLCLK 525
 * #define WM_MOUSELAST 525
 * #else
 * 
 * #if (_WIN32_WINNT >= 0x0500)
 * #define VK_XBUTTON1	5
 * #define VK_XBUTTON2	6
 * #endif
*/
#if (_WIN32_WINNT >= 0x0500)
        case WM_XBUTTONDOWN:{
            LpwEnumMouseButton button = LPW_ENUM_MOUSE_BUTTON_NULL;
            if ((HIWORD(wParam)) == XBUTTON2)
                button = LPW_ENUM_MOUSE_BUTTON_FORWARD;
            else 
            if ((HIWORD(wParam)) == XBUTTON1)
                button = LPW_ENUM_MOUSE_BUTTON_BACKWARD;
            lpwProcessMouseButtonEvent(mouse, button, LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS);
        }break;
        case WM_XBUTTONUP:{
            LpwEnumMouseButton button = LPW_ENUM_MOUSE_BUTTON_NULL;
            if ((HIWORD(wParam)) == XBUTTON2)
                button = LPW_ENUM_MOUSE_BUTTON_FORWARD;
            else 
            if ((HIWORD(wParam)) == XBUTTON1)
                button = LPW_ENUM_MOUSE_BUTTON_BACKWARD;
            lpwProcessMouseButtonEvent(mouse, button, LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE);
        }break;
        case WM_XBUTTONDBLCLK:{
            LpwEnumMouseButton button = LPW_ENUM_MOUSE_BUTTON_NULL;
            if ((HIWORD(wParam)) == XBUTTON2)
                button = LPW_ENUM_MOUSE_BUTTON_FORWARD;
            else 
            if ((HIWORD(wParam)) == XBUTTON1)
                button = LPW_ENUM_MOUSE_BUTTON_BACKWARD;
            lpwProcessMouseButtonEvent(mouse, button, LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE);
        }break;
#endif

        case WM_MOUSEMOVE:{
            if(mouse != LPW_NULL_HANDLE)
            {
                //if((mouse->info.pos.x != LOWORD(lParam)) && (mouse->info.pos.y != HIWORD(lParam)))
                {
                    mouse->info.pre_pos.x = mouse->info.pos.x;
                    mouse->info.pre_pos.y = mouse->info.pos.y;
                    mouse->info.pos.x = LOWORD(lParam);
                    mouse->info.pos.y = HIWORD(lParam);
                    if(mouse->info.pfn_callback_list.pfn_pos_callback != NULL){
                        mouse->info.pfn_callback_list.pfn_pos_callback(mouse, mouse->info.pos.x, mouse->info.pos.y);
                    }
                }
            }
        }break;
        case WM_MOUSEWHEEL:{
            if(mouse != LPW_NULL_HANDLE)
            {
                LpwEnumMouseWheel wheel = LPW_ENUM_MOUSE_WHEEL_NULL;
                wheel = (GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 
                LPW_ENUM_MOUSE_WHEEL_FORWARD : LPW_ENUM_MOUSE_WHEEL_BACKWARD);
                if(mouse->info.pfn_callback_list.pfn_wheel_callback != NULL){
                    mouse->info.pfn_callback_list.pfn_wheel_callback(mouse, wheel);
                }
            }
        }break;
        //case WM_MOUSEHWHEEL:
        case 0x020E:{
            if(mouse != LPW_NULL_HANDLE)
            {
                LpwEnumMouseWheel wheel = LPW_ENUM_MOUSE_WHEEL_NULL;
                wheel = (GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 
                LPW_ENUM_MOUSE_WHEEL_RIGHTWARD : LPW_ENUM_MOUSE_WHEEL_LEFTWARD);
                if(mouse->info.pfn_callback_list.pfn_wheel_callback != NULL){
                    mouse->info.pfn_callback_list.pfn_wheel_callback(mouse, wheel);
                }
            }
        }break;

        //keyboard
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:{
            if(lpw_global_platform_keyboard_key_code_callback != NULL)
            {
                lpw_global_platform_keyboard_key_code_callback(wParam);
            }
            if(keyboard != LPW_NULL_HANDLE)
            {
                LpwEnumKeyboardKey key = lpw_global_keyboard_key_table[wParam];
                if( (keyboard->info.pfn_callback_list.pfn_key_callback != NULL) &&
                    (keyboard->info.key_state_table[key] != LPW_ENUM_KEYBOARD_KEY_STATE_ACTIVE))
                {
                    DWORD current_time = GetTickCount();
                    DWORD time_interval = current_time - keyboard->info.pre_time_table[key];
                    if( (time_interval < keyboard->info.time_interval) && (time_interval > 0))
                    {
                        keyboard->info.pfn_callback_list.pfn_key_callback(keyboard, key, LPW_ENUM_KEYBOARD_KEY_EVENT_DOUBLE);
                    }
                    else
                    {
                        keyboard->info.pfn_callback_list.pfn_key_callback(keyboard, key, LPW_ENUM_KEYBOARD_KEY_EVENT_PRESS);
                    }
                    keyboard->info.pre_time_table[key] = current_time;
                }
                keyboard->info.key_state_table[key] = LPW_ENUM_KEYBOARD_KEY_STATE_ACTIVE;
            }
        }break;
        case WM_KEYUP:
        case WM_SYSKEYUP:{
            if(keyboard != LPW_NULL_HANDLE)
            {
                LpwEnumKeyboardKey key = lpw_global_keyboard_key_table[wParam];
                keyboard->info.key_state_table[key] = LPW_ENUM_KEYBOARD_KEY_STATE_INACTIVE;
                if(keyboard->info.pfn_callback_list.pfn_key_callback != NULL)
                {
                    keyboard->info.pfn_callback_list.pfn_key_callback(keyboard, key, LPW_ENUM_KEYBOARD_KEY_EVENT_RELEASE);
                }
            }
        }break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

void _lpwDeviceEventHandler(const xcb_generic_event_t* xcb_event, LpwDevice device)
{
    uint8_t message = xcb_event->response_type & ~0x80;//make sure it's value in 0~127
    LpwWindow window = device->window;
    LpwMouse mouse = device->mouse;
    LpwKeyboard keyboard = device->keyboard;
    switch(message)
    {
        //window
        case XCB_CONFIGURE_NOTIFY:
        {
            if(window != LPW_NULL_HANDLE)
            {
                xcb_configure_notify_event_t* window_event = (xcb_configure_notify_event_t*)xcb_event;
                //no matter what event is, the window_event->width and window_event->height are always the real size of the window,
                //but only move event occurred, the window_event->event_x and window_event->event_y are the pos of the window,
                //so handle size event first(must break it), then handle move event
                //size
                if( window_event->width != window->info.size.x || window_event->height != window->info.size.y)
                {
                    window->info.size.x = window_event->width;
                    window->info.size.y = window_event->height;
                    if(window->info.pfn_callback_list.pfn_size_callback != NULL)
                    {
                        window->info.pfn_callback_list.pfn_size_callback(window, window->info.size.x, window->info.size.y);
                    }
                    break;
                }
                //move
                if( (window_event->x != window->info.pos.x || window_event->y != window->info.pos.y) )
                {
                    //if( (window_event->x != 0 && window_event->y != 0) ||
                    //    (window_event->width == 0 && window_event->height == 0))
                    {
                        window->info.pos.x = window_event->x;
                        window->info.pos.y = window_event->y;
                        if(window->info.pfn_callback_list.pfn_pos_callback != NULL)
                        {
                            window->info.pfn_callback_list.pfn_pos_callback(window, window->info.pos.x, window->info.pos.y);
                        }
                    }
                    break;
                }
            }
        }break;//window move and size
        case XCB_CLIENT_MESSAGE:
        {
            if(window != LPW_NULL_HANDLE)
            {
                if (((xcb_client_message_event_t *)xcb_event)->data.data32[0] == 
                    (((xcb_intern_atom_reply_t* )device->platform_data->atom_window_reply)->atom))
                {
                    window->info.is_active = LPW_FALSE;
                }
            }
        }break;//window close

        //case XCB_FOCUS_IN://set focus
        //{
        //    //xcb_focus_in_event_t
        //}break;
        //case XCB_FOCUS_OUT://kill focus
        //{
        //    //xcb_focus_in_event_t
        //}break;
        // case XCB_CONFIGURE_WINDOW:
        //     {
        //     }
        // case XCB_CREATE_NOTIFY:
        // {
        //     printf("Event: XCB_CREATE_NOTIFY\n");
        // }

        //mouse
        case XCB_BUTTON_PRESS:
        case XCB_BUTTON_RELEASE:{
            if(mouse != LPW_NULL_HANDLE)
            {
                xcb_button_press_event_t *mouse_message = (xcb_button_press_event_t *)xcb_event;

                LpwEnumMouseButton button = LPW_ENUM_MOUSE_BUTTON_NULL;
                LpwEnumMouseButtonEvent button_event = LPW_ENUM_MOUSE_BUTTON_EVENT_NULL;
                LpwEnumMouseWheel wheel = LPW_ENUM_MOUSE_WHEEL_NULL;
                //in xcb, the mouse wheel events are seen as button, and have release event! but i ignore the wheel release event.
                //the mouse wheel(in xcb is button) event, i handle it follow the rules that in windows, them only have pfn_callback,
                //to replace the state table.
                switch (mouse_message->detail)
                {
                    case 1: button = LPW_ENUM_MOUSE_BUTTON_LEFT;        break;
                    case 2: button = LPW_ENUM_MOUSE_BUTTON_MIDDLE;      break;
                    case 3: button = LPW_ENUM_MOUSE_BUTTON_RIGHT;       break;
                    case 4: wheel  = LPW_ENUM_MOUSE_WHEEL_FORWARD;      break;
                    case 5: wheel  = LPW_ENUM_MOUSE_WHEEL_BACKWARD;     break;
                    case 6: wheel  = LPW_ENUM_MOUSE_WHEEL_LEFTWARD;     break;
                    case 7: wheel  = LPW_ENUM_MOUSE_WHEEL_RIGHTWARD;    break;
                    case 8: button = LPW_ENUM_MOUSE_BUTTON_BACKWARD;    break;
                    case 9: button = LPW_ENUM_MOUSE_BUTTON_FORWARD;     break;
                    default: assert(0);
                }//translat button and wheel

                if(message == XCB_BUTTON_PRESS)
                {
                    button_event = LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS;
                    uint32_t time_interval = mouse_message->time - mouse->info.pre_time_table[button];
                    if( (time_interval < mouse->info.time_interval) && (time_interval > 0))
                    {
                        button_event = LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE;
                    }
                    mouse->info.pre_time_table[button] = mouse_message->time;
                }//button press: check the pre_time_table to see if it is double-click event, then update pre_time_table
                else
                if(message == XCB_BUTTON_RELEASE)
                {
                    button_event = LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE;
                }//button release

                if(button != LPW_ENUM_MOUSE_BUTTON_NULL)
                {
                    lpwProcessMouseButtonEvent(mouse, button, button_event);
                }//process button event: update button state table, and call pfn_callback
                else
                if( wheel != LPW_ENUM_MOUSE_WHEEL_NULL && ( button_event == LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS ||
                                                            button_event == LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE))
                {
                    if(mouse->info.pfn_callback_list.pfn_wheel_callback != NULL){
                        mouse->info.pfn_callback_list.pfn_wheel_callback(mouse, wheel);
                    }
                }//process wheel event: call pfn_callback
            }
        }break;//mouse button and wheel
        case XCB_MOTION_NOTIFY:{
            if(mouse != LPW_NULL_HANDLE)
            {
                xcb_button_press_event_t *mouse_message = (xcb_button_press_event_t *)xcb_event;
                //if( (mouse->info.pos.x != mouse_message->event_x) && 
                //    (mouse->info.pos.y != mouse_message->event_y))//this is not need, i think the physical device cause this problem
                {
                    mouse->info.pre_pos.x = mouse->info.pos.x;
                    mouse->info.pre_pos.y = mouse->info.pos.y;
                    mouse->info.pos.x = mouse_message->event_x;
                    mouse->info.pos.y = mouse_message->event_y;
                    if(mouse->info.pfn_callback_list.pfn_pos_callback != NULL){
                        mouse->info.pfn_callback_list.pfn_pos_callback(mouse, mouse->info.pos.x, mouse->info.pos.y);
                    }
                }
            }
        }break;//mouse move

        //keyboard
        case XCB_KEY_PRESS:{
            if(lpw_global_platform_keyboard_key_code_callback != NULL)
            {
                xcb_key_press_event_t *key_event = (xcb_key_press_event_t*)xcb_event;
                lpw_global_platform_keyboard_key_code_callback(key_event->detail);
            }
            if(keyboard != LPW_NULL_HANDLE)
            {
                xcb_key_press_event_t *key_event = (xcb_key_press_event_t*)xcb_event;
                LpwEnumKeyboardKey key = lpw_global_keyboard_key_table[key_event->detail];
                if( (keyboard->info.pfn_callback_list.pfn_key_callback != NULL) &&
                    (keyboard->info.key_state_table[key] != LPW_ENUM_KEYBOARD_KEY_STATE_ACTIVE))
                {
                    clock_t current_time = clock();
                    clock_t time_interval = current_time - keyboard->info.pre_time_table[key];
                    if( (time_interval < keyboard->info.time_interval) && (time_interval > 0))
                    {
                        keyboard->info.pfn_callback_list.pfn_key_callback(keyboard, key, LPW_ENUM_KEYBOARD_KEY_EVENT_DOUBLE);
                    }
                    else
                    {
                        keyboard->info.pfn_callback_list.pfn_key_callback(keyboard, key, LPW_ENUM_KEYBOARD_KEY_EVENT_PRESS);
                    }
                    keyboard->info.pre_time_table[key] = current_time;
                }
                keyboard->info.key_state_table[key] = LPW_ENUM_KEYBOARD_KEY_STATE_ACTIVE;
            }
        }break;
        case XCB_KEY_RELEASE:{
            if(keyboard != LPW_NULL_HANDLE)
            {
                xcb_key_press_event_t *key_event = (xcb_key_press_event_t*)xcb_event;
                LpwEnumKeyboardKey key = lpw_global_keyboard_key_table[key_event->detail];
                keyboard->info.key_state_table[key] = LPW_ENUM_KEYBOARD_KEY_STATE_INACTIVE;
                if(keyboard->info.pfn_callback_list.pfn_key_callback != NULL)
                {
                    keyboard->info.pfn_callback_list.pfn_key_callback(keyboard, key, LPW_ENUM_KEYBOARD_KEY_EVENT_RELEASE);
                }
            }
        }break;
    }
}

#endif