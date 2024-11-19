#!/bin/bash

CURRENT=$(pwd)
TARGET_SRC_DIR=$(pwd)/../x264
# 设置目标安装路径
PREFIX=$TARGET_SRC_DIR/../installed

cd $TARGET_SRC_DIR

bash ./configure --prefix="$PREFIX" --enable-static

make -j8

make install

make clean

cd $CURRENT

