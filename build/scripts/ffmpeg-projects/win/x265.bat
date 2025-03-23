@echo off

set CURRENT=%~dp0
set ROOT_DIR=%CURRENT%/../../../..
set SRC_DIR=%ROOT_DIR%/3rdparty/x265/source
set INSTALL_DIR=%ROOT_DIR%/build/installed/ffmpeg

cd %SRC_DIR%

mkdir build_win
cd build_win

cmake -DENABLE_SHARED=OFF -G Ninja ..

cmake --build .

cmake --install . --prefix %INSTALL_DIR%

cd ..
rm -rf build_win
cd %CURRENT%
rem echo %CURRENT%