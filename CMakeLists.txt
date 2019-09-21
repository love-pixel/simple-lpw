cmake_minimum_required(VERSION 3.0.0)

project("lpw")

set(
    lpw_source
    "${PROJECT_SOURCE_DIR}/src/tool/enum_to_str.c"
    "${PROJECT_SOURCE_DIR}/src/device/device.c"
    "${PROJECT_SOURCE_DIR}/src/device/event_handler.c"
    "${PROJECT_SOURCE_DIR}/src/device/window/window.c"
    "${PROJECT_SOURCE_DIR}/src/device/mouse/mouse.c"
    "${PROJECT_SOURCE_DIR}/src/device/keyboard/keyboard.c"
)

# gcc command tips as below:
# windows dependencies: -lgdi32
# linux dependencies: -lxcb -lxcb-xkb
# to enable assert or enable debug: -D _DEBUG

if(WIN32)
set(
    lpw_dependencies
    "gdi32"
)
elseif(UNIX)
set(
    lpw_dependencies
    "xcb"
    "xcb-xkb"
)
endif()

set(
    lpw_all_dependencies
    "lpw"
    ${lpw_dependencies}
)


add_library(${PROJECT_NAME} ${lpw_source})

add_subdirectory("example")