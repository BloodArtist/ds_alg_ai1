@echo off
cls
.\GENie\genie.exe vs2019
FOR /D %%i IN (.\..\build\*.*) DO copy abgs_memory_configuration.cfg .\%%i\vs2019\

pause
