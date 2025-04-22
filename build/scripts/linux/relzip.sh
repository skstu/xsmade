#!/bin/bash
ORIGINAL_DIR=$(pwd)
CURRENT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
BIN_DIR="$CURRENT_DIR/../../../bin"
DATE=$(date +%y%m%d%H%M%S)
PACKET_NAME="brw_$DATE.zip"

echo "Original directory: $ORIGINAL_DIR"
echo "Current directory: $BIN_DIR"
echo "Chrome directory: $PACKET_NAME"

cd $BIN_DIR
zip -r $PACKET_NAME * -x "$*.txt" "*.zip" "cache/*" "packets/*" "temp/*" "plugins/*"

sshpass -p "Marspanda.." scp $PACKET_NAME panda@10.100.4.15:/home/panda/cppdev

cd $ORIGINAL_DIR
