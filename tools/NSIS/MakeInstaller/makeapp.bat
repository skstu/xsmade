@echo off

set CURRENT=%~dp0
set PROJECTS_TOOLS_DIR=%CURRENT%\..
set EXE7Z=%PROJECTS_TOOLS_DIR%\7z\7z.exe
set DIR_FilesToInstall=%CURRENT%\FilesToInstall
set DIR_source=%CURRENT%\source

del "%DIR_source%\app.7z"
%EXE7Z% a "%DIR_source%\app.7z" "%DIR_FilesToInstall%\*.*"

@set DestPath=%DIR_FilesToInstall%\
@echo off& setlocal EnableDelayedExpansion

for /f "delims=" %%a in ('dir /ad/b %DestPath%') do (
%EXE7Z% a "%DIR_source%\app.7z" "%DIR_FilesToInstall%\%%a"
@echo "compressing %DIR_FilesToInstall%\%%a"
)