@ECHO off

ECHO ================
ECHO Run Application
ECHO ================

SET PROJECT_NAME=%1
SET MODE=%2
SET EXE_PATH=%~dp0..\..\Solution\%MODE%\%PROJECT_NAME%.exe

if not exist %EXE_PATH% (
    ECHO Build the solution before running it....
    GOTO:EOF
)

SET CURRENT_PATH=%~dp0
SET ROOT_PATH=%~dp0..\..\

PUSHD "%CURRENT_PATH%"
PUSHD "%ROOT_PATH%"

start %EXE_PATH%

POPD
POPD