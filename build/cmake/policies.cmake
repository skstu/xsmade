
#############################################################################
# Name:        build/cmake/main.cmake
# Purpose:     Main CMake file
# Author:      Martell
# Created:     2024-11-04
# Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
#############################################################################

#[[
这些 `cmake_policy` 设置用于在 CMake 中控制特定的行为，确保在不同版本的 CMake 中的一致性。CMake 使用这些政策来处理各个版本之间引入的行为更改，使项目在不同版本的 CMake 下能够正确构建。以下是各个设置的解释：
1. **CMP0025**: Apple 的编译器 ID 从 `Clang` 改成 `AppleClang`。启用此选项确保编译器 ID 为 `AppleClang`（适用于 macOS 下使用的 Clang 编译器）。
2. **CMP0028**: 双冒号（`::`）符号的目标名称被解释为 `ALIAS` 或 `IMPORTED` 目标。启用此选项可以避免对目标名称含有双冒号的误解。
3. **CMP0038**: 不允许目标直接链接自己。设置此选项可以防止自引用链接错误。
4. **CMP0042**: 默认启用 `MACOSX_RPATH`，即 macOS 使用的运行时路径。启用此选项可以确保 macOS 系统的 RPATH 正常配置。
5. **CMP0045**: 在调用 `get_target_property` 时，若目标不存在则报错。启用此选项会在目标不存在时显示错误，而不是返回空值。
6. **CMP0046**: 在调用 `add_dependencies` 时，如果依赖的目标不存在则报错。启用此选项确保所依赖的目标必须有效存在。
7. **CMP0048**: `project()` 命令可以管理 `VERSION` 变量。启用此选项可以让 `project()` 处理项目版本信息。
8. **CMP0049**: 不在目标源条目中展开变量。启用此选项可以防止在源文件路径中意外展开变量。
9. **CMP0053**: 简化对变量引用和转义序列的评估。启用此选项可以使用更简单的变量引用格式。
10. **CMP0054**: 只有未加引号的 `if()` 参数会被解释为变量或关键字。启用此选项可以避免将引号括起来的值错误地解释为变量。
11. **CMP0060**: 即使库在隐式目录中，也通过完整路径链接库。启用此选项可以防止隐式目录中的库与错误的库发生链接。
12. **CMP0067**: 在 `try_compile()` 时遵循语言标准。启用此选项确保使用 `try_compile()` 时符合指定的语言标准。
13. **CMP0072**: `FindOpenGL` 默认优先使用 GLVND（OpenGL Vendor Neutral Dispatch library）。启用此选项可以确保在支持的系统上使用 GLVND。
14. **CMP0092**: 默认情况下，MSVC 警告标志不包含在 `CMAKE_<LANG>_FLAGS` 中。启用此选项可以保持 MSVC 编译标志的独立性。
]]

# Please keep the policies in the order of their numbers.

if(POLICY CMP0025)
    # Compiler id for Apple Clang is now AppleClang.
    cmake_policy(SET CMP0025 NEW)
endif()

if(POLICY CMP0028)
    # Double colon in target name means ALIAS or IMPORTED target.
    cmake_policy(SET CMP0028 NEW)
endif()

if(POLICY CMP0038)
    # Targets may not link directly to themselves.
    cmake_policy(SET CMP0038 NEW)
endif()

if(POLICY CMP0042)
    # MACOSX_RPATH is enabled by default.
    cmake_policy(SET CMP0042 NEW)
endif()

if(POLICY CMP0045)
    # Error on non-existent target in get_target_property.
    cmake_policy(SET CMP0045 NEW)
endif()

if(POLICY CMP0046)
    # Error on non-existent dependency in add_dependencies.
    cmake_policy(SET CMP0046 NEW)
endif()

if(POLICY CMP0048)
    # The project() command manages VERSION variables.
    cmake_policy(SET CMP0048 NEW)
endif()

if(POLICY CMP0049)
    # Do not expand variables in target source entries.
    cmake_policy(SET CMP0049 NEW)
endif()

if(POLICY CMP0053)
    # Simplify variable reference and escape sequence evaluation.
    cmake_policy(SET CMP0053 NEW)
endif()

if(POLICY CMP0054)
    # Only interpret if() arguments as variables or keywords when unquoted.
    cmake_policy(SET CMP0054 NEW)
endif()

if(POLICY CMP0060)
    # Link libraries by full path even in implicit directories.
    cmake_policy(SET CMP0060 NEW)
endif()

if(POLICY CMP0067)
    # Honor language standard in try_compile() source-file signature.
    cmake_policy(SET CMP0067 NEW)
endif()

if(POLICY CMP0072)
    # FindOpenGL prefers GLVND by default when available.
    cmake_policy(SET CMP0072 NEW)
endif()

if(POLICY CMP0092)
    # MSVC warning flags are not in CMAKE_<LANG>_FLAGS by default.
    cmake_policy(SET CMP0092 NEW)
endif()