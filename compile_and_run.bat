@echo off
cls

g++ -std=c++17 include/engine/*.cpp include/engine/material/*.cpp include/engine/mesh/*.cpp include/engine/descriptors/*.cpp include/engine/window/*.cpp include/engine/world_object/*.cpp include/engine/device/*.cpp include/engine/texture/*.cpp include/engine/pipeline/*.cpp source/main.cpp -Iinclude/engine/ -o build/GamingTime.exe -Iinclude/ -Llib/ -lglfw3 -lvulkan-1 -lgdi32

if ERRORLEVEL 1 echo Error Compiling Code
if %ERRORLEVEL% EQU 0 echo Code compiled succesfully

for %%I in (build/uncompiled_shaders/*.vert) do (
	glslc build/uncompiled_shaders/%%I -o build/shaders/%%I.spv
	echo compiled %%I
)

for %%I in (build/uncompiled_shaders/*.frag) do (
	glslc build/uncompiled_shaders/%%I -o build/shaders/%%I.spv
	echo compiled %%I
)

if ERRORLEVEL 1 echo Error Compiling Shaders
if %ERRORLEVEL% EQU 0 echo Shaders compiled succesfully

if %ERRORLEVEL% EQU 0 cd build
if %ERRORLEVEL% EQU 0 GamingTime.exe

cd..