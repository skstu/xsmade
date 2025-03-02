@echo off

set CURRENT=%~dp0
set PROJECTS_TOOLS_DIR=%CURRENT%\..
set EXE7Z=%PROJECTS_TOOLS_DIR%\7z\7z.exe
set DIR_source=%CURRENT%\source

del "%DIR_source%\skin.zip"

%EXE7Z% a "%DIR_source%\skin.zip" "%DIR_source%\skin\*.*"

@set DestPath=%DIR_source%\skin\
@echo off& setlocal EnableDelayedExpansion

for /f "delims=" %%a in ('dir /ad/b %DestPath%') do (
%EXE7Z% a "%DIR_source%\skin.zip" "%DIR_source%\skin\%%a"
@echo "compressing %DIR_source%\skin\%%a"
)