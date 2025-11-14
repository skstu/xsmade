set(PROXY_PROJECT_NAME "proxy")

set(ENABLE_USE_OPENSSL
    ON
    CACHE BOOL "" FORCE)
set(ENABLE_USE_BORINGSSL
    OFF
    CACHE BOOL "" FORCE)

if(ENABLE_USE_OPENSSL)
  set(OPENSSL_ROOT_DIR
      "${MSYS2_CLANG64_DIR}/"
      CACHE STRING "" FORCE)
  find_package(OpenSSL REQUIRED COMPONENTS SSL)
endif()

if(ENABLE_USE_BORINGSSL)
  set(OPENSSL_IS_BORINGSSL ON CACHE BOOL "" FORCE)

  # 查找已安装的 boringssl 库/头（MSYS2 mingw64 默认安装路径为 ${MSYS2_CLANG64_DIR}/lib 和 /include）
  find_library(BORINGSSL_SSL_LIBRARY
               NAMES ssl boringssl_ssl libssl
               PATHS "${MSYS2_CLANG64_DIR}/lib" "/mingw64/lib" "/usr/local/lib" NO_DEFAULT_PATH)
  find_library(BORINGSSL_CRYPTO_LIBRARY
               NAMES crypto boringssl_crypto libcrypto
               PATHS "${MSYS2_CLANG64_DIR}/lib" "/mingw64/lib" "/usr/local/lib" NO_DEFAULT_PATH)
  find_path(BORINGSSL_INCLUDE_DIR
            NAMES openssl/ssl.h
            PATHS "${MSYS2_CLANG64_DIR}/include" "/mingw64/include" "/usr/local/include" NO_DEFAULT_PATH)

  if(BORINGSSL_SSL_LIBRARY AND BORINGSSL_CRYPTO_LIBRARY AND BORINGSSL_INCLUDE_DIR)
    # 使用已安装的 BoringSSL
    if(NOT TARGET OpenSSL::SSL)
      add_library(OpenSSL::SSL UNKNOWN IMPORTED)
      set_target_properties(OpenSSL::SSL PROPERTIES
        IMPORTED_LOCATION "${BORINGSSL_SSL_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${BORINGSSL_INCLUDE_DIR}")
    endif()
    if(NOT TARGET OpenSSL::Crypto)
      add_library(OpenSSL::Crypto UNKNOWN IMPORTED)
      set_target_properties(OpenSSL::Crypto PROPERTIES
        IMPORTED_LOCATION "${BORINGSSL_CRYPTO_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${BORINGSSL_INCLUDE_DIR}")
    endif()

    set(BORINGSSL_INCLUDE_DIRS "${BORINGSSL_INCLUDE_DIR}" CACHE PATH "" FORCE)
    set(BORINGSSL_LIBRARIES OpenSSL::SSL OpenSSL::Crypto CACHE INTERNAL "")

    message(STATUS "Found BoringSSL: SSL='${BORINGSSL_SSL_LIBRARY}' CRYPTO='${BORINGSSL_CRYPTO_LIBRARY}' INCLUDE='${BORINGSSL_INCLUDE_DIR}'")
  else()
    set(BORINGSSL_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    # 未找到已安装的 BoringSSL，自动启用源码编译
    message(WARNING "BoringSSL not found in system paths, will build from source.")
    set(BORINGSSL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/boringssl/include" CACHE PATH "" FORCE)
    set(BORINGSSL_LIBRARIES ssl crypto CACHE INTERNAL "" FORCE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/boringssl)
    if(NOT TARGET OpenSSL::SSL)
      add_library(OpenSSL::SSL ALIAS ssl)
    endif()
    if(NOT TARGET OpenSSL::Crypto)
      add_library(OpenSSL::Crypto ALIAS crypto)
    endif()
  endif()
endif()

add_subdirectory(${xs3RDPARTY_DIR}/proxy/ ${PROXY_PROJECT_NAME})

# set_target_properties(${PROXY_PROJECT_NAME} PROPERTIES
# POSITION_INDEPENDENT_CODE TRUE)
