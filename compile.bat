@echo off
setlocal

set "RAYLIB_PATH=C:\raylib\raylib"
set "PATH=C:\raylib\w64devkit\bin;%PATH%"

g++ src\main.cpp src\cards.cpp src\costumer.cpp src\shop.cpp src\recipe.cpp src\utils.cpp src\avl.cpp src\history.cpp src\ui.cpp src\event_system.cpp src\metrics.cpp src\timer.cpp ^
    -o game.exe ^
    -I"src\headers" ^
    -I"%RAYLIB_PATH%\src" ^
    -I"%RAYLIB_PATH%\examples\shapes" ^
    -L"%RAYLIB_PATH%\src" ^
    -lraylib -lopengl32 -lgdi32 -lwinmm

if errorlevel 1 exit /b 1
