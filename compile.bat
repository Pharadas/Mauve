@echo off
cmake --build ./
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
