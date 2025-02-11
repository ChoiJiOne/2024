@echo off

SET visualstudio=vs2022
SET project=Transform3D
SET script=Script\GenerateProjectFiles.bat

%script% %visualstudio% %project% On