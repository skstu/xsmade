#!/bin/bash
ORIGINAL_DIR=$(pwd)
CURRENT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
BIN_DIR="$CURRENT_DIR/../../../bin"
COPY_TO_FILE="$BIN_DIR/brw.zip"
DATE=$(date +%y%m%d%H%M%S)
PACKET_NAME="brw_$DATE.zip"

echo "Original directory: $ORIGINAL_DIR"
echo "Current directory: $BIN_DIR"
echo "Chrome directory: $PACKET_NAME"

cd $BIN_DIR
zip -r $PACKET_NAME * -x "$*.txt" "*.zip" "cache/*" "packets/*" "temp/*" "plugins/*"

rm -rf $COPY_TO_FILE

cp $PACKET_NAME $COPY_TO_FILE

cd $ORIGINAL_DIR
