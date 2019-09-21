#include "../../include/lpw/device/device_prototype.h"
#include "../../include/lpw/device/platform_data_prototype.h"
#include "../../include/lpw/device/event_handler.h"


#include <malloc.h>
#include <assert.h>

void _lpwInitPlatformData(LpwPlatformData data);

LpwDevice lpwCreateDevice(const LpwDeviceCreateInfo* ci_ptr)
{
    LpwDevice device = (LpwDevice_Prototype*)malloc(sizeof(LpwDevice_Prototype));
    device->root = LPW_NULL_HANDLE;
    device->user_ptr = NULL;
    device->platform_data = (LpwPlatformData_Prototype*)malloc(sizeof(LpwPlatformData_Prototype));
    _lpwInitPlatformData(device->platform_data);
    device->window = LPW_NULL_HANDLE;
    device->mouse = LPW_NULL_HANDLE;
    //device->keyboard = LPW_NULL_HANDLE;
    if(ci_ptr != NULL)
    {
        device->root = ci_ptr->root;
        device->user_ptr = (void*)ci_ptr->user_ptr;
    }
    return device;
}
void lpwDestroyDevice(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    free(device->platform_data);
    free(device);
}

#if defined( LPW_MACRO_USE_PLATFORM_SDK_WINDOWS )

void _lpwInitPlatformData(LpwPlatformData data)
{
    data->wnd_class_name = NULL;
    data->instance = NULL;
    data->hwnd = NULL;
}

void lpwProcessEvent(LpwDevice device, LpwEnumProcessEventType type)
{
    assert(device != LPW_NULL_HANDLE);
    if(type == LPW_ENUM_PROCESS_EVENT_TYPE_WAIT)
    {
        WaitMessage();
    }
    lpwProcessEventByPoll(device);
}
void lpwProcessEventByPoll(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    MSG message;
    if(PeekMessage(&message, device->platform_data->hwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}
void lpwProcessEventByWait(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    WaitMessage();
    lpwProcessEventByPoll(device);
}
#elif defined( LPW_MACRO_USE_PLATFORM_SDK_XCB )

void _lpwInitPlatformData(LpwPlatformData data)
{
    data->connection = NULL;
    data->screen = NULL;
    data->window = 0;
    data->atom_window_reply = NULL;
}

void lpwProcessEvent(LpwDevice device, LpwEnumProcessEventType type)
{
    assert(device != LPW_NULL_HANDLE);
    assert(device->platform_data->connection != NULL);

    xcb_generic_event_t* xcb_event = NULL;
    if(type == LPW_ENUM_PROCESS_EVENT_TYPE_POLL)
        xcb_event = xcb_poll_for_event(device->platform_data->connection);
    else
    if(type == LPW_ENUM_PROCESS_EVENT_TYPE_WAIT)
        xcb_event = xcb_wait_for_event(device->platform_data->connection);
    if(xcb_event == NULL) return;

    _lpwDeviceEventHandler(xcb_event, device);
    free(xcb_event);
}
void lpwProcessEventByPoll(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    assert(device->platform_data->connection != NULL);

    xcb_generic_event_t* xcb_event = xcb_poll_for_event(device->platform_data->connection);
    if(xcb_event == NULL) return;

    _lpwDeviceEventHandler(xcb_event, device);
    free(xcb_event);
}
void lpwProcessEventByWait(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    assert(device->platform_data->connection != NULL);

    xcb_generic_event_t* xcb_event = xcb_wait_for_event(device->platform_data->connection);
    if(xcb_event == NULL) return;

    _lpwDeviceEventHandler(xcb_event, device);
    free(xcb_event);
}

#endif

void lpwSetDeviceUserPtr(LpwDevice device, const void* src_ptr)
{
    assert(device != LPW_NULL_HANDLE);
    device->user_ptr = (void*)src_ptr;
}
void* lpwGetDeviceUserPtr(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    return device->user_ptr;
}

LpwPlatformData lpwGetDevicePlatformData(LpwDevice device)
{
    assert(device != LPW_NULL_HANDLE);
    return device->platform_data;
}