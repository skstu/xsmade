#!/bin/bash
# chmod +x ../build/scripts/linux/install-chrome.sh
# cd /c/Users/k34ub/source/skstu/xsmade/build/scripts/ffmpeg-projects/win
#CURRENT=$(pwd)

#BUILD_CHROME_DIR="/home/ponyo/Desktop/projects/chromium_dev/130.0.6723.116/src/out/release"
BUILD_CHROME_DIR="/home/ponyo/Desktop/projects/chromium/134.0.6998.165/src/out/release"
CURRENT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
BIN_CHROMIUM_DIR="$CURRENT_DIR/../../../bin/browser/chromium/134.0.6998.165"
mkdir -p $BIN_CHROMIUM_DIR
echo "Current directory: $CURRENT_DIR"
echo "Chrome directory: $BUILD_CHROME_DIR"
#mkdir -p $BIN_CHROMIUM_DIR/chrome && cp -f /src/* /dest
#rsync -av --mkpath --progress "$BUILD_CHROME_DIR" "$BIN_CHROMIUM_DIR"
#rsync -av --mkpath --progress $BUILD_CHROME_DIR/extensions/* $BIN_CHROMIUM_DIR/extensions/*
rsync -av --mkpath --progress $BUILD_CHROME_DIR/locales/ $BIN_CHROMIUM_DIR/locales/
rsync -av --mkpath --progress $BUILD_CHROME_DIR/extensions/ $BIN_CHROMIUM_DIR/extensions/
rsync -av --mkpath --progress $BUILD_CHROME_DIR/MEIPreload/ $BIN_CHROMIUM_DIR/MEIPreload/
rsync -av --mkpath --progress $BUILD_CHROME_DIR/PrivacySandboxAttestationsPreloaded/ $BIN_CHROMIUM_DIR/PrivacySandboxAttestationsPreloaded/
rsync -av --mkpath --progress $BUILD_CHROME_DIR/resources/ $BIN_CHROMIUM_DIR/resources/

rsync -av --mkpath --progress $BUILD_CHROME_DIR/resources.pak $BIN_CHROMIUM_DIR/resources.pak
rsync -av --mkpath --progress $BUILD_CHROME_DIR/headless_command_resources.pak $BIN_CHROMIUM_DIR/headless_command_resources.pak
rsync -av --mkpath --progress $BUILD_CHROME_DIR/headless_lib_data.pak $BIN_CHROMIUM_DIR/headless_lib_data.pak
rsync -av --mkpath --progress $BUILD_CHROME_DIR/headless_lib_strings.pak $BIN_CHROMIUM_DIR/headless_lib_strings.pak
rsync -av --mkpath --progress $BUILD_CHROME_DIR/chrome_100_percent.pak $BIN_CHROMIUM_DIR/chrome_100_percent.pak
rsync -av --mkpath --progress $BUILD_CHROME_DIR/chrome_200_percent.pak $BIN_CHROMIUM_DIR/chrome_200_percent.pak
rsync -av --mkpath --progress $BUILD_CHROME_DIR/icudtl.dat $BIN_CHROMIUM_DIR/icudtl.dat

rsync -av --mkpath --progress $BUILD_CHROME_DIR/snapshot_blob.bin $BIN_CHROMIUM_DIR/snapshot_blob.bin
rsync -av --mkpath --progress $BUILD_CHROME_DIR/v8_context_snapshot.bin $BIN_CHROMIUM_DIR/v8_context_snapshot.bin

rsync -av --mkpath --progress $BUILD_CHROME_DIR/product_logo_48.png $BIN_CHROMIUM_DIR/product_logo_48.png

rsync -av --mkpath --progress $BUILD_CHROME_DIR/v8_build_config.json $BIN_CHROMIUM_DIR/v8_build_config.json
rsync -av --mkpath --progress $BUILD_CHROME_DIR/v8_features.json $BIN_CHROMIUM_DIR/v8_features.json
rsync -av --mkpath --progress $BUILD_CHROME_DIR/vk_swiftshader_icd.json $BIN_CHROMIUM_DIR/vk_swiftshader_icd.json

rsync -av --mkpath --progress $BUILD_CHROME_DIR/libEGL.so $BIN_CHROMIUM_DIR/libEGL.so
rsync -av --mkpath --progress $BUILD_CHROME_DIR/libGLESv2.so $BIN_CHROMIUM_DIR/libGLESv2.so
rsync -av --mkpath --progress $BUILD_CHROME_DIR/libqt5_shim.so $BIN_CHROMIUM_DIR/libqt5_shim.so
rsync -av --mkpath --progress $BUILD_CHROME_DIR/libqt6_shim.so $BIN_CHROMIUM_DIR/libqt6_shim.so
rsync -av --mkpath --progress $BUILD_CHROME_DIR/libVkICD_mock_icd.so $BIN_CHROMIUM_DIR/libVkICD_mock_icd.so
rsync -av --mkpath --progress $BUILD_CHROME_DIR/libVkLayer_khronos_validation.so $BIN_CHROMIUM_DIR/libVkLayer_khronos_validation.so
rsync -av --mkpath --progress $BUILD_CHROME_DIR/libvk_swiftshader.so $BIN_CHROMIUM_DIR/libvk_swiftshader.so
rsync -av --mkpath --progress $BUILD_CHROME_DIR/libvulkan.so.1 $BIN_CHROMIUM_DIR/libvulkan.so.1

rsync -av --mkpath --progress $BUILD_CHROME_DIR/chrome $BIN_CHROMIUM_DIR/chrome
rsync -av --mkpath --progress $BUILD_CHROME_DIR/mksnapshot $BIN_CHROMIUM_DIR/mksnapshot
rsync -av --mkpath --progress $BUILD_CHROME_DIR/make_top_domain_list_variables $BIN_CHROMIUM_DIR/make_top_domain_list_variables
rsync -av --mkpath --progress $BUILD_CHROME_DIR/protoc $BIN_CHROMIUM_DIR/protoc
rsync -av --mkpath --progress $BUILD_CHROME_DIR/root_store_tool $BIN_CHROMIUM_DIR/root_store_tool
rsync -av --mkpath --progress $BUILD_CHROME_DIR/flatc $BIN_CHROMIUM_DIR/flatc
rsync -av --mkpath --progress $BUILD_CHROME_DIR/top_domain_generator $BIN_CHROMIUM_DIR/top_domain_generator
rsync -av --mkpath --progress $BUILD_CHROME_DIR/transport_security_state_generator $BIN_CHROMIUM_DIR/transport_security_state_generator
rsync -av --mkpath --progress $BUILD_CHROME_DIR/chrome_crashpad_handler $BIN_CHROMIUM_DIR/chrome_crashpad_handler
rsync -av --mkpath --progress $BUILD_CHROME_DIR/character_data_generator $BIN_CHROMIUM_DIR/character_data_generator
rsync -av --mkpath --progress $BUILD_CHROME_DIR/nasm $BIN_CHROMIUM_DIR/nasm
rsync -av --mkpath --progress $BUILD_CHROME_DIR/protoc-gen-js $BIN_CHROMIUM_DIR/protoc-gen-js
rsync -av --mkpath --progress $BUILD_CHROME_DIR/protozero_plugin $BIN_CHROMIUM_DIR/protozero_plugin
rsync -av --mkpath --progress $BUILD_CHROME_DIR/cppgen_plugin $BIN_CHROMIUM_DIR/cppgen_plugin
rsync -av --mkpath --progress $BUILD_CHROME_DIR/ipc_plugin $BIN_CHROMIUM_DIR/ipc_plugin
rsync -av --mkpath --progress $BUILD_CHROME_DIR/gen-regexp-special-case $BIN_CHROMIUM_DIR/gen-regexp-special-case
rsync -av --mkpath --progress $BUILD_CHROME_DIR/brotli $BIN_CHROMIUM_DIR/brotli
rsync -av --mkpath --progress $BUILD_CHROME_DIR/bytecode_builtins_list_generator $BIN_CHROMIUM_DIR/bytecode_builtins_list_generator
rsync -av --mkpath --progress $BUILD_CHROME_DIR/wayland_scanner $BIN_CHROMIUM_DIR/wayland_scanner
rsync -av --mkpath --progress $BUILD_CHROME_DIR/v8_context_snapshot_generator $BIN_CHROMIUM_DIR/v8_context_snapshot_generator
