@echo off
cls
.\GENie\genie.exe vs2017
FOR /D %%i IN (.\..\build\*.*) DO copy abgs_memory_configuration.cfg .\%%i\vs2017\

pause
