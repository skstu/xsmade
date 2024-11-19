#!/bin/bash

CURRENT=$(pwd)
ROOT=${CURRENT}/..
TARGET_SRC_DIR=${ROOT}/ffmpeg
# 设置目标安装路径
PREFIX=${ROOT}/installed

cd $TARGET_SRC_DIR

deps_pkg_config_path=${PREFIX}/lib/pkgconfig
deps_lib_dir=${PREFIX}/lib
deps_include_dir=${PREFIX}/include

#export PATH=/C/msys64/mingw64/bin:$PATH
#export PKG_CONFIG_PATH=${x264_pkg_config_path}

#echo ${PKG_CONFIG_PATH}

#--enable-yasm \
#--enable-asm \
# exit 0
#clang --version
#CC=gcc
make distclean

PKG_CONFIG_PATH=${deps_pkg_config_path}
bash ./configure \
--prefix="$PREFIX" \
--enable-static \
--arch=x86_64 \
--disable-x86asm \
--enable-libx265 \
--enable-libx264 \
--arch=x86_64 \
--enable-static \
--disable-shared \
--enable-gpl \
--enable-nonfree \
--enable-cross-compile \
--disable-htmlpages \
--extra-ldflags=-LIBPATH:${deps_lib_dir} \
--extra-cflags=-I${deps_include_dir} \

make -j8

make install

make clean

cd $CURRENT

