#pragma once 

#if defined( _WIN32 )
#define LPW_MACRO_USE_PLATFORM_WINDOWS
#elif defined( __linux )
#define LPW_MACRO_USE_PLATFORM_LINUX
#else
#error platform not yet support
#endif