@echo off

set CURRENT=%~dp0
set TARGET_SRC_DIR=%CURRENT%/../x265/source
set INSTALL_DIR=%CURRENT%/../installed

cd %TARGET_SRC_DIR%

ls

mkdir build_win32
cd build_win32

cmake -DENABLE_SHARED=OFF -G Ninja ..

cmake --build .

cmake --install . --prefix %INSTALL_DIR%

cd ..
rm -rf build_win32
cd %CURRENT%
rem echo %CURRENT%