@echo off

rem @call makeapp.bat
rem @call makeskinzip.bat

set CURRENT=%~dp0
set PROJECTS_TOOLS_DIR=%CURRENT%\..
set EXENSISW=%PROJECTS_TOOLS_DIR%\NSIS\makensisw.exe
set EXENSIS=%PROJECTS_TOOLS_DIR%\NSIS\makensis.exe
set DIR_source=%CURRENT%\source

"%EXENSISW%" "%DIR_source%\installer.nsi"

rem ".\NSIS\makensis.exe" ".\source\setup.nsi"
