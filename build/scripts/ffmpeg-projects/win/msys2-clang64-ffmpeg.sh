#!/bin/bash
# cd /c/Users/k34ub/source/skstu/xsmade/build/scripts/ffmpeg-projects/win
CURRENT=$(pwd)
ROOT_DIR=${CURRENT}/../../../..
SRC_DIR=${ROOT_DIR}/3rdparty/ffmpeg
INSTALL_DIR=${ROOT_DIR}/build/installed

cd $SRC_DIR

deps_pkg_config_path=${INSTALL_DIR}/lib/pkgconfig
deps_lib_dir=${INSTALL_DIR}/lib
deps_include_dir=${INSTALL_DIR}/include

#make distclean
# ./configure --enable-gpl --enable-version3 --enable-nonfree --enable-shared --enable-pic --enable-static --enable-small --enable-runtime-cpudetect --enable-zlib --enable-libx264 --enable-libx265 --enable-libvpx --enable-libfdk-aac --enable-libopus --enable-libvorbis --enable-libfreetype --enable-libass --enable-libmp3lame --enable-libtheora --enable-libxvid --enable-libdav1d --enable-libsnappy --enable-libwebp --enable-libshine --enable-libvidstab --enable-libsoxr --enable-libopenh264 --enable-librtmp --enable-libgsm --enable-libmysofa --enable-libspeex --enable-libbluray --enable-libmfx --enable-libzvbi --enable-libfontconfig --enable-libfribidi --enable-libcelt --enable-libmodplug --enable-libcaca --enable-libcdio --enable-libaom --enable-libsvtav1 --enable-librav1e --enable-libdavs2

PKG_CONFIG_PATH=${deps_pkg_config_path}

bash ./configure \
--cc=clang \
--cxx=clang++ \
--prefix="${INSTALL_DIR}" \
--arch=x86_64 \
--disable-debug \
--disable-doc \
--enable-ffplay \
--enable-decoder='mjpeg,png,aac,libx264,libx265,libmp3lame,libfaac' \
--enable-encoder='aac,png,mjpeg,libx264,libx265,libmp3lame,libfaac' \
--enable-demuxer=image2 \
--enable-protocol=file \
--enable-zlib \
--enable-bzlib \
--enable-gpl \
--enable-nonfree \
--enable-version3 \
--disable-shared \
--enable-pic \
--enable-libx264 \
--enable-libx265 \
--enable-libvpx \
--enable-libopus \
--enable-libfdk-aac \
--enable-libmp3lame \
--enable-libfreetype \
--enable-libass \
--enable-libvorbis \
--enable-libtheora \
--enable-libxvid \
--enable-openssl \
--enable-postproc \
--enable-libwebp \
--enable-libspeex \
--enable-libzvbi \
--enable-libvidstab \
--enable-libsoxr \
--enable-libshine \
--enable-librtmp \
--enable-libopenjpeg \
--enable-libbluray \
--enable-libaom \
--enable-libdav1d \
--enable-libzimg \
--enable-libsnappy \
--enable-libsvtav1 \
--enable-libsrt \
--enable-libvmaf \
--enable-libmysofa \
--enable-libxml2 \
--enable-libgsm \
--enable-filters \
--enable-static \
--enable-avfilter \
--enable-filter=movie \
--disable-w32threads \
--enable-runtime-cpudetect \
--extra-ldflags=-LIBPATH:${deps_lib_dir} \
--extra-cflags=-I${deps_include_dir} 

#--extra-ldflags=-L/c/msys64/clang/lib 
#--extra-cflags=-I/c/msys64/clang/include 
#--extra-libs='-lssl -lcrypto -lz -lbz2 -liconv'

make -j8

make install

make clean

cd $CURRENT
