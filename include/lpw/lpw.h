#pragma once

#if defined( _cplusplus )
extern "C" {
#endif

#include "macro/platform.h"
#include "macro/platform_sdk.h"
#include "macro/debug.h"

#if defined( LPW_MACRO_INCLUDE_PLATFORM_HEADER )
#include "external/platform/platform_sdk.h"
#endif
#if defined( LPW_MACRO_INCLUDE_PLATFORM_DATA_PROTOTYPE )
#include "device/platform_data_prototype.h"
#endif

#include "device/device.h"
#include "device/window/window.h"
#include "device/mouse/mouse.h"

#if defined( _cplusplus )
}
#endif