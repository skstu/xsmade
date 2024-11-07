# ##############################################################################
# Name:        build/cmake/main.cmake Purpose:     Main CMake file Author:
# Martell Created:     2024-11-08 Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
# ##############################################################################

set(xsOPENSSL_VERSION 3.3)

set(xsOPENSSL_INCLUDE ${${MSYS2_CLANG64_DIR}}/include/)
set(xsOPENSSL_LIBRARY ${MSYS2_CLANG64_DIR}/lib/libssl.a
                      ${MSYS2_CLANG64_DIR}/lib/libcrypto.a)
