rd /S /Q build

set DEVICE_PATH=../src/device
set EXAMPLE_PATH=../example

mkdir build
cd build

echo build lpw.lib
gcc -std=c99 -g -shared ^
    ../src/tool/enum_to_str.c ^
    %DEVICE_PATH%/device.c ^
    %DEVICE_PATH%/event_handler.c ^
    %DEVICE_PATH%/window/window.c ^
    %DEVICE_PATH%/mouse/mouse.c ^
    %DEVICE_PATH%/keyboard/keyboard.c ^
    -lgdi32 ^
    -o ^
    lpw.lib

echo build keyboard
gcc -std=c99 -g ^
    %EXAMPLE_PATH%/keyboard/test_keyboard.c ^
    -L. ^
    -llpw ^
    -lgdi32 ^
    -o ^
    keyboard.exe 

echo build mouse
gcc -std=c99 -g ^
    %EXAMPLE_PATH%/mouse/test_mouse.c ^
    -L. ^
    -llpw ^
    -lgdi32 ^
    -o ^
    mouse.exe 

echo build window
gcc -std=c99 -g ^
    %EXAMPLE_PATH%/window/create_window.c ^
    -L. ^
    -llpw ^
    -lgdi32 ^
    -o ^
    window.exe 

pause