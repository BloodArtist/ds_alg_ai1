cls
@echo off
IF EXIST ..\build\.vs rmdir /s /q ..\build\.vs
IF EXIST ..\build\PR0_MemoryNode rmdir /s /q ..\build\PR0_MemoryNode
IF EXIST ..\build\PR1_Vector rmdir /s /q ..\build\PR1_Vector
IF EXIST ..\build\PR2_List rmdir /s /q ..\build\PR2_List
IF EXIST ..\build\PR3_DLList rmdir /s /q ..\build\PR3_DLList
IF EXIST ..\build\PR4_Stack rmdir /s /q ..\build\PR4_Stack
IF EXIST ..\build\PR5_Queue rmdir /s /q ..\build\PR5_Queue
IF EXIST ..\bin\debug rmdir /s /q ..\bin\debug
IF EXIST ..\bin\release rmdir /s /q ..\bin\release

IF EXIST ..\build\DS_ALG_AI1vs2017.sln del /F ..\build\DS_ALG_AI1vs2017.sln
IF EXIST ..\build\DS_ALG_AI1vs2019.sln del /F ..\build\DS_ALG_AI1vs2019.sln
