@echo off

SET SRC=%1
SET VALIDATOR=%~dp0..\Bin\glslangValidator.exe

for %%i in ("%SRC%") do (
    set "OUTPUT=%%~nxi"
)

echo ^>^> CHECKING GLSL SHADER FILE: %SRC% ^<^<

"%VALIDATOR%" %SRC%