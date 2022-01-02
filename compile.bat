@echo off

g++ -std=c++17 include/engine/*.cpp include/engine/material/*.cpp include/engine/mesh/*.cpp include/engine/descriptors/*.cpp include/engine/window/*.cpp include/engine/world_object/*.cpp include/engine/device/*.cpp include/engine/texture/*.cpp include/engine/pipeline/*.cpp source/main.cpp -Iinclude/engine/ -o build/GamingTime.exe -Iinclude/ -Llib/ -lglfw3 -lvulkan-1 -lgdi32

if ERRORLEVEL 1 echo Error Compiling Code
if %ERRORLEVEL% EQU 0 echo Code compiled succesfully

for %%I in (build/shaders/*.vert) do (
	glslc build/shaders/%%I -o build/shaders/%%I.spv
	if %ERRORLEVEL% EQU 0 echo compiled %%I
	if %ERRORLEVEL% EQU 0 echo couldnt compile %%I
)

for %%I in (build/shaders/*.frag) do (
	glslc build/shaders/%%I -o build/shaders/%%I.spv
	if %ERRORLEVEL% EQU 0 echo compiled %%I
	if %ERRORLEVEL% EQU 0 echo couldnt compile %%I
)

if ERRORLEVEL 1 echo Error Compiling Shaders
if %ERRORLEVEL% EQU 0 echo Shaders compiled succesfully
