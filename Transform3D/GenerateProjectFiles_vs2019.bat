@echo off

SET visualstudio=vs2019
SET project=Transform3D
SET script=Script\GenerateProjectFiles.bat

%script% %visualstudio% %project% On