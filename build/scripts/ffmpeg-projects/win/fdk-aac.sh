#!/bin/bash
# cd /c/Users/k34ub/source/skstu/xsmade/build/scripts/ffmpeg-projects/win
CURRENT=$(pwd)
ROOT_DIR=${CURRENT}/../../../..
SRC_DIR=${ROOT_DIR}/3rdparty/fdk-aac
INSTALL_DIR=${ROOT_DIR}/build/installed

cd $SRC_DIR
#CC=clang
#CXX=clang++
bash ./configure --prefix="${INSTALL_DIR}" --enable-static --disable-shared

make -j8

make install

make clean

cd $CURRENT

