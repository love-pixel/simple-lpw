#pragma once

#include "../tool/handle.h"
#include "../enum/process_event_type.h"
#include "../basic_type/basic_type.h"
#include "platform_data.h"

LPW_DEFINE_HANDLE(LpwDevice)

typedef struct LpwDeviceCreateInfo
{
    LpwDevice          root;
    const void*        user_ptr;
}LpwDeviceCreateInfo;

LpwDevice lpwCreateDevice(const LpwDeviceCreateInfo* ci_ptr);
void lpwDestroyDevice(LpwDevice device);

void lpwProcessEvent(LpwDevice device, LpwEnumProcessEventType type);
void lpwProcessEventByPoll(LpwDevice device);
void lpwProcessEventByWait(LpwDevice device);

void lpwSetDeviceUserPtr(LpwDevice device, const void* src_ptr);
void* lpwGetDeviceUserPtr(LpwDevice device);

LpwPlatformData lpwGetDevicePlatformData(LpwDevice device);