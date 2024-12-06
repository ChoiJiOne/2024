@ECHO OFF

ECHO ============
ECHO Start Build 
ECHO ============

where cmake > nul 2>&1
if %ERRORLEVEL% EQU 0 (
    ECHO CMake is installed on this system...
) else (
    ECHO CMake is not installed on this system...
    GOTO:EOF
)

SET VISUAL_STUDIO="Visual Studio 17 2022"
SET SOLUTION_PATH=%~dp0..\Solution

if not exist "%SOLUTION_PATH%" (
    mkdir "%SOLUTION_PATH%"
)

SET MODE=%1

if "%MODE%" == "Debug" (
    ECHO Build "%MODE%" mode...
) else if "%MODE%" == "Release" (
    ECHO Build "%MODE%" mode...
) else if "%MODE%" == "RelWithDebInfo" (
    ECHO Build "%MODE%" mode...
) else if "%MODE%" == "MinSizeRel" (
    ECHO Build "%MODE%" mode...
) else (
    ECHO "%MODE%" is illegal mode...
    GOTO:EOF
)

SET ADMIN=%2

if "%ADMIN%" == "ON" (
    SET ADMIN_OPTION="ON"
    ECHO "Enable Require Administrator."
) else if "%ADMIN%" == "on" (
    SET ADMIN_OPTION="ON"
    ECHO "Enable Require Administrator."
) else if "%ADMIN%" == "OFF" (
    SET ADMIN_OPTION="OFF"
    ECHO "Disable Require Administrator."
) else if "%ADMIN%" == "off" (
    SET ADMIN_OPTION="OFF"
    ECHO "Disable Require Administrator."
) else (
    ECHO "%ADMIN%" is illegal parameter...
    GOTO:EOF
)

SET CURRENT_PATH=%~dp0

PUSHD "%CURRENT_PATH%"
PUSHD "%SOLUTION_PATH%"

cmake .. -G %VISUAL_STUDIO% -A x64 -DREQUIRE_ADMINISTRATOR=%ADMIN_OPTION%
cmake --build . --config %mode% --clean-first --parallel  

POPD
POPD

ECHO ============
ECHO Done Build
ECHO ============