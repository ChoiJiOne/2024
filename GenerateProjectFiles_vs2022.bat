@echo off

SET visualstudio=vs2022
SET project=Dodge3D
SET script=GameEngine\Script\GenerateProjectFiles.bat

%script% %visualstudio% %project% On