# ##############################################################################
# Name:        build/cmake/main.cmake Purpose:     Main CMake file Author:
# Martell Created:     2024-11-08 Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
# ##############################################################################


# "${MSYS2_CLANG64_DIR}/lib/libopus.a"
# "${MSYS2_CLANG64_DIR}/lib/libaom.a"
# "${MSYS2_CLANG64_DIR}/lib/libgsm.a"
# "${MSYS2_CLANG64_DIR}/lib/libshine.a"
# "${MSYS2_CLANG64_DIR}/lib/libspeex.a"
# "${MSYS2_CLANG64_DIR}/lib/libsnappy.a"
# "${MSYS2_CLANG64_DIR}/lib/libmp3lame.a"
# "${MSYS2_CLANG64_DIR}/lib/libSvtAv1Enc.a"
# "${MSYS2_CLANG64_DIR}/lib/libtheoraenc.a"
# "${MSYS2_CLANG64_DIR}/lib/libvorbisenc.a"
# "${MSYS2_CLANG64_DIR}/lib/libtheora.a"
# "${MSYS2_CLANG64_DIR}/lib/libvorbis.a"
# "${MSYS2_CLANG64_DIR}/lib/libvpx.a"
# "${MSYS2_CLANG64_DIR}/lib/libwebp.a"
# "${MSYS2_CLANG64_DIR}/lib/libtiff.a"
# "${MSYS2_CLANG64_DIR}/lib/libdav1d.a"
# "${MSYS2_CLANG64_DIR}/lib/libmf.a"
# "${MSYS2_CLANG64_DIR}/lib/liblzma.a"
# "${MSYS2_CLANG64_DIR}/lib/libzvbi.a"
# "${MSYS2_CLANG64_DIR}/lib/libva.a"
# "${MSYS2_CLANG64_DIR}/lib/libxvidcore.a"
# "${MSYS2_CLANG64_DIR}/lib/libogg.a"
# "${MSYS2_CLANG64_DIR}/lib/libintl.a"
# "${MSYS2_CLANG64_DIR}/lib/libpng.a"
# "${MSYS2_CLANG64_DIR}/lib/libxml2.a"
# "${MSYS2_CLANG64_DIR}/lib/libwebp.a"
# "${MSYS2_CLANG64_DIR}/lib/libbz2.a"
# "${MSYS2_CLANG64_DIR}/lib/libswresample.a"
# "${MSYS2_CLANG64_DIR}/lib/libsoxr.a"
# "${MSYS2_CLANG64_DIR}/lib/libbcrypt.a"
# "${MSYS2_CLANG64_DIR}/lib/libbluray.a"
# "${MSYS2_CLANG64_DIR}/lib/librtmp.a"
# "${MSYS2_CLANG64_DIR}/lib/libsrt.a"
# "${MSYS2_CLANG64_DIR}/lib/libgnutls.a"
# "${MSYS2_CLANG64_DIR}/lib/libgmp.a"
# "${MSYS2_CLANG64_DIR}/lib/libnettle.a"
# "${MSYS2_CLANG64_DIR}/lib/libsharpyuv.a"
# "${MSYS2_CLANG64_DIR}/lib/libfreetype.a"
# "${MSYS2_CLANG64_DIR}/lib/libncrypt.a"
# "${MSYS2_CLANG64_DIR}/lib/libzstd.a"
# "${MSYS2_CLANG64_DIR}/lib/libtasn1.a"
# "${MSYS2_CLANG64_DIR}/lib/libbrotlicommon.a"
# "${MSYS2_CLANG64_DIR}/lib/libp11.a"
# "${MSYS2_CLANG64_DIR}/lib/libpkcs11.a"
# "${MSYS2_CLANG64_DIR}/lib/libssl.a"
# "${MSYS2_CLANG64_DIR}/lib/libcrypto.a"
# "${MSYS2_CLANG64_DIR}/lib/libbrotlidec.a"

macro(GFN_FIND_FFMPEG OUT_FFX_INCLUDES OUT_FFX_LIBS)
  if(WIN32)
    set(${OUT_FFX_INCLUDES} "${${xsBUILD_INSTALLED_DIR}}/ffmpeg/include/")

    set(${OUT_FFX_LIBS}
        "${MSYS2_CLANG64_DIR}/lib/libva.a"
        "${MSYS2_CLANG64_DIR}/lib/libva_win32.a"
        "${MSYS2_CLANG64_DIR}/lib/libbz2.a"
        "${MSYS2_CLANG64_DIR}/lib/liblzma.a"
        "${MSYS2_CLANG64_DIR}/lib/libsecur32.a"
        "${MSYS2_CLANG64_DIR}/lib/libbcrypt.a"
        "${MSYS2_CLANG64_DIR}/lib/libmfplat.a"
        "${MSYS2_CLANG64_DIR}/lib/libstrmiids.a"
        "${MSYS2_CLANG64_DIR}/lib/libmfuuid.a"
        "${MSYS2_CLANG64_DIR}/lib/libiconv.a"
        "${MSYS2_CLANG64_DIR}/lib/libopenjp2.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libx264.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libx265.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libfdk-aac.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libswscale.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libavcodec.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libavdevice.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libavfilter.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libavformat.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libavutil.a"
        "${xsBUILD_INSTALLED_DIR}/ffmpeg/lib/libswresample.a")
  elseif(APPLE)
    set(${OUT_FFX_INCLUDES} "")
    set(${OUT_FFX_LIBS} "")
  endif()
endmacro()
