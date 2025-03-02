Unicode true
RequestExecutionLevel admin
!define PROJECT_NAME                "MarsProjects"
!define PRODUCT_NAME           		"扇子办公宝"
!define PRODUCT_PATHNAME 			"MarsProjects"
!define INSTALL_APPEND_PATH         "MarsProjects"
!define INSTALL_DEFALT_SETUPPATH    "$PROGRAMFILES\MarsProjects"      #默认生成的安装路径  
!define EXE_NAME               		"扇子办公宝.exe"
!define PRODUCT_VERSION        		"1.0.8.0"
!define PRODUCT_PUBLISHER      		"成都火熊星猫有限公司"
!define PRODUCT_LEGAL          		"© 2025 火熊星猫"
!define INSTALL_OUTPUT_NAME    		"mars_workprojects_v6_20250120_path0.exe"
#安装包名字
Name "${PRODUCT_NAME}"

!define INSTALL_7Z_PATH 	   		"app.7z"
!define INSTALL_7Z_NAME 	   		"app.7z"
!define INSTALL_RES_PATH       		"skin.zip"
!define INSTALL_LICENCE_FILENAME    "licence.txt"
!define INSTALL_ICO 				"logo.ico"
!define UNINSTALL_ICO 				"uninst.ico"

!include "installer_ui.nsh"

OutFile "..\output\${INSTALL_OUTPUT_NAME}"

InstallDir "$PROGRAMFILES\${INSTALL_APPEND_PATH}"

Icon              "${INSTALL_ICO}"
UninstallIcon     "${UNINSTALL_ICO}"
