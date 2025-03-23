#!/bin/bash
# cd /c/Users/k34ub/source/skstu/xsmade/build/scripts/ffmpeg-projects/win
CURRENT=$(pwd)
ROOT_DIR=${CURRENT}/../../../..
SRC_DIR=${ROOT_DIR}/3rdparty/x264
INSTALL_DIR=${ROOT_DIR}/build/installed/ffmpeg

cd $SRC_DIR

bash ./configure --prefix="${INSTALL_DIR}" --enable-static

make -j8

make install

make clean

cd $CURRENT

