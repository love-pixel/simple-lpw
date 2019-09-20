#include "../../include/lpw/device/event_handler.h"
#include "../../include/lpw/device/device_prototype.h"
#include "../../include/lpw/device/window/window_prototype.h"
#include "../../include/lpw/device/mouse/mouse_prototype.h"

#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )

LRESULT CALLBACK _lpwDeviceEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    LpwDevice device = (LpwDevice)GetWindowLong(hWnd, GWLP_USERDATA);
    if(device == LPW_NULL_HANDLE) return DefWindowProc(hWnd, uMsg, wParam, lParam);
    LpwWindow window = device->window;
    LpwMouse mouse = device->mouse;
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

        case WM_XBUTTONDOWN:{
            LpwEnumMouseButton button = LPW_ENUM_MOUSE_BUTTON_NULL;
            if ((HIWORD(wParam)) == XBUTTON1)
                button = LPW_ENUM_MOUSE_BUTTON_FORWARD;
            else 
            if ((HIWORD(wParam)) == XBUTTON2)
                button = LPW_ENUM_MOUSE_BUTTON_BACKWARD;
            lpwProcessMouseButtonEvent(mouse, button, LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS);
        }break;
        case WM_XBUTTONUP:{
            LpwEnumMouseButton button = LPW_ENUM_MOUSE_BUTTON_NULL;
            if ((HIWORD(wParam)) == XBUTTON1)
                button = LPW_ENUM_MOUSE_BUTTON_FORWARD;
            else 
            if ((HIWORD(wParam)) == XBUTTON2)
                button = LPW_ENUM_MOUSE_BUTTON_BACKWARD;
            lpwProcessMouseButtonEvent(mouse, button, LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE);
        }break;
        case WM_XBUTTONDBLCLK:{
            LpwEnumMouseButton button = LPW_ENUM_MOUSE_BUTTON_NULL;
            if ((HIWORD(wParam)) == XBUTTON1)
                button = LPW_ENUM_MOUSE_BUTTON_FORWARD;
            else 
            if ((HIWORD(wParam)) == XBUTTON2)
                button = LPW_ENUM_MOUSE_BUTTON_BACKWARD;
            lpwProcessMouseButtonEvent(mouse, button, LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE);
        }break;

        case WM_MOUSEMOVE:{
            if(mouse != LPW_NULL_HANDLE)
            {
                mouse->info.pre_pos.x = mouse->info.pos.x;
                mouse->info.pre_pos.y = mouse->info.pos.y;
                mouse->info.pos.x = LOWORD(lParam);
                mouse->info.pos.y = HIWORD(lParam);
                if(mouse->info.pfn_callback_list.pfn_pos_callback != NULL){
                    mouse->info.pfn_callback_list.pfn_pos_callback(mouse, mouse->info.pos.x, mouse->info.pos.y);
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
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

#endif