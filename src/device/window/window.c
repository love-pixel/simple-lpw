#include "../../../include/lpw/device/window/window_prototype.h"
#include "../../../include/lpw/device/device_prototype.h"
#include "../../../include/lpw/device/platform_data_prototype.h"
#include "../../../include/lpw/device/event_handler.h"


#include <assert.h>
#include <malloc.h>

void _lpwCreateNativeWindow(LpwWindow window);
void _lpwDestroyNativeWindow(LpwWindow window);

LpwWindow lpwCreateWindow(LpwDevice device, const LpwWindowCreateInfo* ci_ptr)
{
    assert(device != LPW_NULL_HANDLE);
    assert(ci_ptr != NULL);
    assert(device->window == LPW_NULL_HANDLE);
    LpwWindow window = (LpwWindow_Prototype*)malloc(sizeof(LpwWindow_Prototype));
    window->info.pos = ci_ptr->pos;
    window->info.size = ci_ptr->size;
    window->info.name = ci_ptr->name;
    window->info.pfn_callback_list.pfn_pos_callback = NULL;
    window->info.pfn_callback_list.pfn_size_callback = NULL;
    window->info.is_active = LPW_FALSE;
    window->user_ptr = NULL;
    window->root_device = device;
    if(ci_ptr->pfn_callback_list_ptr != NULL)
    {
        window->info.pfn_callback_list.pfn_pos_callback = ci_ptr->pfn_callback_list_ptr->pfn_pos_callback;
        window->info.pfn_callback_list.pfn_size_callback = ci_ptr->pfn_callback_list_ptr->pfn_size_callback;
    }

    device->window = window;
    _lpwCreateNativeWindow(window);
    window->info.is_active = LPW_TRUE;
    return window;
}
void lpwDestroyWindow(LpwWindow window)
{
    assert(window != LPW_NULL_HANDLE);
    _lpwDestroyNativeWindow(window);
    free(window);
}

void lpwSetWindowUserPtr(LpwWindow window, const void* src_ptr)
{
    assert(window != LPW_NULL_HANDLE);
    window->user_ptr = (void*)src_ptr;
}
void* lpwGetWindowUserPtr(LpwWindow window)
{
    assert(window != LPW_NULL_HANDLE);
    return window->user_ptr;
}

LpwVec2_i32 lpwGetWindowPos(LpwWindow window)
{
    assert(window != LPW_NULL_HANDLE);
    return window->info.pos;
}

LpwVec2_ui32 lpwGetWindowSize(LpwWindow window)
{
    assert(window != LPW_NULL_HANDLE);
    return window->info.size;
}

const char* lpwGetWindowName(LpwWindow window)
{
    assert(window != LPW_NULL_HANDLE);
    return window->info.name;
}

void lpwSetWindowPfnCallback(LpwWindow window, LpwEnumWindowEvent event, const void* src_ptr)
{
    assert(window != LPW_NULL_HANDLE);
    switch(event)
    {
        case LPW_ENUM_WINDOW_EVENT_POS: 
            window->info.pfn_callback_list.pfn_pos_callback = (PFN_LpwWindowPosCallback)src_ptr; 
            break;
        case LPW_ENUM_WINDOW_EVENT_SIZE: 
            window->info.pfn_callback_list.pfn_size_callback = (PFN_LpwWindowSizeCallback)src_ptr; 
            break;
        default:
            assert(0);
    }
}
void* lpwGetWindowPfnCallback(LpwWindow window, LpwEnumWindowEvent event)
{
    assert(window != LPW_NULL_HANDLE);
    switch(event)
    {
        case LPW_ENUM_WINDOW_EVENT_POS: 
            return (void*)window->info.pfn_callback_list.pfn_pos_callback;
        case LPW_ENUM_WINDOW_EVENT_SIZE: 
            return (void*)window->info.pfn_callback_list.pfn_size_callback; 
        default:
            assert(0);
    }
    return NULL;
}

LpwBool lpwIsWindowActive(LpwWindow window)
{
    assert(window != LPW_NULL_HANDLE);
    return window->info.is_active;
}

//LpwEnumResult lpwGetWindow(LpwWindow window, );

LpwWindow lpwGetWindow(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    return device->window;
}
LpwDevice lpwGetDevice(LpwWindow window)
{
    assert(window != LPW_NULL_HANDLE);
    return window->root_device;
}

#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )

//LRESULT CALLBACK _lpwDeviceEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
uint32_t _lpwGenerateUniqueInteger()
{
    static uint32_t lpw_unique_integer = 0;
    lpw_unique_integer++;
    return lpw_unique_integer;
}

void _lpwCreateNativeWindow(LpwWindow window)
{
    LpwPlatformData platform_data = window->root_device->platform_data;
    //Generate a unique window class name
	{
		static const char* lpw_pre_class_name = "Love-Pixel-Window_CLASS_NAME_";
		uint32_t lpw_unique_integer = _lpwGenerateUniqueInteger();
		char* lpw_class_name = (char*)malloc(sizeof(char) * (lpw_unique_integer / 10 + 2));								/* Memory Leak Warning!!!! */	//Resolved
		itoa(lpw_unique_integer, lpw_class_name, 10);
		
		platform_data->wnd_class_name
			= (char*)malloc(sizeof(char) * strlen(lpw_pre_class_name) + strlen(lpw_class_name) + 1);					/* Memory Leak Warning!!!! */	//Resolved

		platform_data->wnd_class_name[0] = '\0';

		strcat(platform_data->wnd_class_name, lpw_pre_class_name);
		strcat(platform_data->wnd_class_name, lpw_class_name);

		free(lpw_class_name);																						/* Memory Freeing^_^ */
		lpw_class_name = NULL;
	}
    platform_data->instance = GetModuleHandle(NULL);

    WNDCLASSEX windows_class;
	{
		// Initialize the window class structure:
		windows_class.cbSize			= sizeof( WNDCLASSEX );
		windows_class.style				= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		windows_class.lpfnWndProc		= _lpwDeviceEventHandler;
		windows_class.cbClsExtra		= 0;
		windows_class.cbWndExtra		= 0;
		windows_class.hInstance			= platform_data->instance; // hInstance
		windows_class.hIcon				= LoadIcon( NULL, IDI_APPLICATION );
		windows_class.hCursor			= LoadCursor( NULL, IDC_ARROW );
		windows_class.hbrBackground		= (HBRUSH)GetStockObject( WHITE_BRUSH );
		windows_class.lpszMenuName		= NULL;
		windows_class.lpszClassName		= platform_data->wnd_class_name;
		windows_class.hIconSm			= LoadIcon( NULL, IDI_WINLOGO );
	}

    // Register window class:
	if( !RegisterClassEx( &windows_class ) ) {																		/* Memory Leak Warning!!!! */	//Resolved
		// It didn't work, so try to give a useful error:
        exit(1);
	}

    DWORD ex_style	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD style		= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | 
					  WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;

    RECT wr = { 0, 0, window->info.size.x, window->info.size.y};
	AdjustWindowRectEx( &wr, style, FALSE, ex_style );
    window->info.size.x = wr.right - wr.left;
    window->info.size.y = wr.bottom - wr.top;

    platform_data->hwnd = CreateWindowEx( 
        0,								
		platform_data->wnd_class_name,		// class name
		window->info.name,			        // app name
		style,							    // window style
		//CW_USEDEFAULT, CW_USEDEFAULT,	    // x/y coords
		window->info.pos.x,                 // x coords
        window->info.pos.y,	                // y coords
		window->info.size.x,		        // width
		window->info.size.y,			    // height
		NULL,		                        // handle to parent
		NULL,		                        // handle to menu
		platform_data->instance,	        // hInstance
		NULL );							    // no extra parameters

    HINSTANCE instance = platform_data->instance;
    HWND hwnd = platform_data->hwnd;
    assert(hwnd != NULL);

    //To make our logic device window can be used in the logic device window event handler
	SetWindowLongPtr( hwnd, GWLP_USERDATA, ( LONG_PTR )window->root_device );

    ShowWindow( hwnd, SW_SHOW );
	SetForegroundWindow( hwnd );
	SetFocus( hwnd );

}
void _lpwDestroyNativeWindow(LpwWindow window)
{
    assert(window != LPW_NULL_HANDLE);
    HINSTANCE instance = window->root_device->platform_data->instance;
    HWND hwnd = window->root_device->platform_data->hwnd;

    DestroyWindow(hwnd);								/* Memory Freeing^_^ */
    UnregisterClass(window->root_device->platform_data->wnd_class_name, 
					instance);						/* Memory Freeing^_^ */
    free(window->root_device->platform_data->wnd_class_name);								/* Memory Freeing^_^ */
}

#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )


#endif