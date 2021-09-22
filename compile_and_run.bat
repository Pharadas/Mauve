@echo off
cmake --build ./
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