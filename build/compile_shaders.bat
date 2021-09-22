@echo off

for %%I in (shaders/*.vert) do (
	glslc shaders/%%I -o shaders/%%I.spv
	if %ERRORLEVEL% EQU 0 echo compiled %%I
	if %ERRORLEVEL% EQU 1 echo couldnt compile %%I
)

for %%I in (shaders/*.frag) do (
	glslc shaders/%%I -o shaders/%%I.spv
	if %ERRORLEVEL% EQU 0 echo compiled %%I
	if %ERRORLEVEL% EQU 1 echo couldnt compile %%I
)

echo compiled shaders