#include "../../include/lpw/device/device_prototype.h"
#include "../../include/lpw/device/platform_data_prototype.h"


#include <malloc.h>
#include <assert.h>

LpwDevice lpwCreateDevice(const LpwDeviceCreateInfo* ci_ptr)
{
    LpwDevice device = (LpwDevice_Prototype*)malloc(sizeof(LpwDevice_Prototype));
    device->root = LPW_NULL_HANDLE;
    device->user_ptr = NULL;
    device->platform_data = (LpwPlatformData_Prototype*)malloc(sizeof(LpwPlatformData_Prototype));
    {
        device->platform_data->wnd_class_name = NULL;
        device->platform_data->instance = NULL;
        device->platform_data->hwnd = NULL;
    }
    device->window = LPW_NULL_HANDLE;
    //device->mouse = LPW_NULL_HANDLE;
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