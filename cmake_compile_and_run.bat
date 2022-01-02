@echo off
cls
cmake --build ./

cd build

@REM compile_shaders.bat

for %%I in (uncompiled_shaders/*.vert) do (
	glslc uncompiled_shaders/%%I -o shaders/%%I.spv
	if %ERRORLEVEL% EQU 0 echo compiled %%I
	if %ERRORLEVEL% EQU 1 echo couldnt compile %%I
)

for %%I in (uncompiled_shaders/*.frag) do (
	glslc uncompiled_shaders/%%I -o shaders/%%I.spv
	if %ERRORLEVEL% EQU 0 echo compiled %%I
	if %ERRORLEVEL% EQU 1 echo couldnt compile %%I
)

@REM echo Compiled Shaders

Mauve.exe

cd..