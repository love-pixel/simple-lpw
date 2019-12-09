#include "../../../include/lpw/device/window/window_prototype.h"
#include "../../../include/lpw/device/device_prototype.h"
#include "../../../include/lpw/device/platform_data_prototype.h"
#include "../../../include/lpw/device/event_handler.h"


#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

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

void lpwGetWindowPos(LpwWindow window, LpwVec2_i32* dst_ptr)
{
    assert(window != LPW_NULL_HANDLE);
    assert(dst_ptr != NULL);
    dst_ptr->x = window->info.pos.x;
    dst_ptr->y = window->info.pos.y;
}
void lpwGetWindowSize(LpwWindow window, LpwVec2_ui32* dst_ptr)
{
    assert(window != LPW_NULL_HANDLE);
    assert(dst_ptr != NULL);
    dst_ptr->x = window->info.size.x;
    dst_ptr->y = window->info.size.y;
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

uint32_t _getNumberCount(uint32_t number){
    uint32_t count = 0;
    while(number = (number / 10)){
        ++count;
    }
    ++count;
    return count;
}

void _lpwCreateNativeWindow(LpwWindow window)
{
    LpwPlatformData platform_data = window->root_device->platform_data;
    //Generate a unique window class name
	{
		static const char* lpw_pre_class_name = "Love-Pixel-Window_CLASS_NAME_";
		uint32_t lpw_unique_integer = _lpwGenerateUniqueInteger();
		char* lpw_class_name = (char*)malloc(sizeof(char) * (_getNumberCount(lpw_unique_integer) + 1));								/* Memory Leak Warning!!!! */	//Resolved
		sprintf(lpw_class_name,"%ld",lpw_unique_integer);// itoa
        //printf("ID %s\n", lpw_class_name);
        //itoa(lpw_unique_integer, lpw_class_name, 10);
        //printf("%d is %d\n", lpw_unique_integer, _getNumberCount(lpw_unique_integer));

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

void _lpwCreateNativeWindow(LpwWindow window)
{
    LpwPlatformData platform_data = window->root_device->platform_data;
    platform_data->connection = xcb_connect(NULL, NULL);

    /* get the first screen */
    platform_data->screen = xcb_setup_roots_iterator(xcb_get_setup(platform_data->connection)).data;

    /* create the window */
    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t mask_values[2] = {
        platform_data->screen->white_pixel,
        //XCB_EVENT_MASK_EXPOSURE |
        //XCB_EVENT_MASK_VISIBILITY_CHANGE | 
        XCB_EVENT_MASK_POINTER_MOTION |          //mouse move
        XCB_EVENT_MASK_STRUCTURE_NOTIFY | //move window, 
        //XCB_EVENT_MASK_PROPERTY_CHANGE | 
        XCB_EVENT_MASK_BUTTON_PRESS          |   //include click close window
        XCB_EVENT_MASK_BUTTON_RELEASE | 
        XCB_EVENT_MASK_KEY_PRESS |
        XCB_EVENT_MASK_KEY_RELEASE |
        XCB_EVENT_MASK_KEYMAP_STATE |
        0 
    };

    platform_data->window = xcb_generate_id(platform_data->connection);

    xcb_create_window(platform_data->connection,
                      0, /* depth               */
                      platform_data->window,
                      platform_data->screen->root,                  /* parent window       */
                      window->info.pos.x,       /* x                   */
                      window->info.pos.y,       /* y                   */
                      window->info.size.x,  /* width               */
                      window->info.size.y, /* height              */
                      10,                            /* border_width        */
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                      platform_data->screen->root_visual,           /* visual              */
                      mask, mask_values);                      /* masks, not used     */

    /* set the title of the window */
    xcb_change_property(platform_data->connection,
                        XCB_PROP_MODE_REPLACE,
                        platform_data->window,
                        XCB_ATOM_WM_NAME,
                        XCB_ATOM_STRING,
                        16,
                        strlen(window->info.name),
                        window->info.name);

    /* set the title of the window icon */

    char *iconTitle = "Hello World ! (iconified)";
    xcb_change_property(platform_data->connection,
                        XCB_PROP_MODE_REPLACE,
                        platform_data->window,
                        XCB_ATOM_WM_ICON_NAME,
                        XCB_ATOM_STRING,
                        16,
                        strlen(iconTitle),
                        iconTitle);

    xcb_intern_atom_cookie_t cookie = xcb_intern_atom( platform_data->connection, 1, 12, "WM_PROTOCOLS" );
	xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply( platform_data->connection, cookie, 0 );

	xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom( platform_data->connection, 0, 16, "WM_DELETE_WINDOW" );
    
    platform_data->atom_window_reply = xcb_intern_atom_reply( platform_data->connection, cookie2, 0 );
		
	xcb_change_property( platform_data->connection, XCB_PROP_MODE_REPLACE, platform_data->window,
		( *reply ).atom, 4, 32, 1,
		&( *platform_data->atom_window_reply ).atom );
	free( reply );

    /* map the window on the screen */
    xcb_map_window(platform_data->connection, platform_data->window);
    xcb_flush(platform_data->connection);

    /* Predictable autorepeat is essential for correct input management
	 * When a key is hold down :
	 * - Without predictable autorepeat, the application will receive :
	 *   "key_pressed", "key_released", "key_pressed", "key_released"
	 * - With predictable autorepeat, the application will receive :
	 *   "key_pressed, "key_pressed", ..., "key_released"
	 * Which helps differentiate between autorepeat and the same key
	 * actually pressed multiple times.
	 */
	xcb_xkb_use_extension(platform_data->connection, 1, 0);
	xcb_xkb_per_client_flags_cookie_t repeat = xcb_xkb_per_client_flags(
		platform_data->connection,
		XCB_XKB_ID_USE_CORE_KBD,
		XCB_XKB_PER_CLIENT_FLAG_DETECTABLE_AUTO_REPEAT,
		XCB_XKB_PER_CLIENT_FLAG_DETECTABLE_AUTO_REPEAT,
		0,0,0
	);
    xcb_xkb_per_client_flags_reply_t* rep = xcb_xkb_per_client_flags_reply(platform_data->connection,repeat,0);
}

void _lpwDestroyNativeWindow(LpwWindow window)
{
    LpwPlatformData platform_data = window->root_device->platform_data;
    xcb_destroy_window(
        platform_data->connection,
        platform_data->window);
    xcb_disconnect(platform_data->connection);

    free(platform_data->atom_window_reply);
}

#endif