#pragma once

typedef enum LpwEnumMouseEvent
{
    LPW_ENUM_MOUSE_EVENT_NULL           ,
    LPW_ENUM_MOUSE_EVENT_POS            ,
    LPW_ENUM_MOUSE_EVENT_WHEEL          ,
    LPW_ENUM_MOUSE_EVENT_BUTTON         ,
    LPW_ENUM_MOUSE_EVENT_MAX_ENUM       ,
}LpwEnumMouseEvent;

typedef enum LpwEnumMouseButtonEvent
{
    LPW_ENUM_MOUSE_BUTTON_EVENT_NULL    ,
    LPW_ENUM_MOUSE_BUTTON_EVENT_PRESS   ,
    LPW_ENUM_MOUSE_BUTTON_EVENT_RELEASE ,
    LPW_ENUM_MOUSE_BUTTON_EVENT_DOUBLE  ,
    LPW_ENUM_MOUSE_BUTTON_EVENT_MAX_ENUM,
}LpwEnumMouseButtonEvent;