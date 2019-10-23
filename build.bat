rm -r build

set DEVICE_PATH=../src/device
set EXAMPLE_PATH=../example

mkdir build
cd build
gcc -std=c99 -g ^
    ../src/tool/enum_to_str.c ^
    %DEVICE_PATH%/device.c ^
    %DEVICE_PATH%/event_handler.c ^
    %DEVICE_PATH%/window/window.c ^
    %DEVICE_PATH%/mouse/mouse.c ^
    %DEVICE_PATH%/keyboard/keyboard.c ^
    %EXAMPLE_PATH%/keyboard/test_keyboard.c ^
    -lgdi32 ^
    -o ^
    keyboard.exe 