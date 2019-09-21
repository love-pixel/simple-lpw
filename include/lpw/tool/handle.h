#pragma once

#define LPW_MAKE_HANDLE_PROTOTYPE_NAME(object) object##_Prototype

#define LPW_DEFINE_HANDLE(object) typedef struct LPW_MAKE_HANDLE_PROTOTYPE_NAME(object)* object;

#define LPW_NULL_HANDLE 0