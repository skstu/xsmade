# 使用Unicode编码
Unicode true

# ====================== 自定义宏 产品信息==============================
!define PRODUCT_NAME           		"NSIS打包测试"
!define PRODUCT_PATHNAME 			"MyApp"  #安装卸载项用到的KEY
!define INSTALL_APPEND_PATH         "MyApp"	  #安装路径追加的名称 
!define INSTALL_DEFALT_SETUPPATH    ""       #默认生成的安装路径  
!define EXE_NAME               		"MyApp.exe"
!define PRODUCT_VERSION        		"1.0.6.0"
!define PRODUCT_PUBLISHER      		"成都火星熊猫有限公司"
!define PRODUCT_LEGAL          		"© 2021 XXXX公司"
!define INSTALL_OUTPUT_NAME    		"mars_workprojects_v6_20250120_path0.exe"

# ====================== 自定义宏 安装信息==============================
!define INSTALL_7Z_PATH 	   		"app.7z"
!define INSTALL_7Z_NAME 	   		"app.7z"
!define INSTALL_RES_PATH       		"skin.zip"
!define INSTALL_LICENCE_FILENAME    "licence.rtf"
!define INSTALL_ICO 				"logo.ico"
!define UNINSTALL_ICO 				"uninst.ico"

#SetCompressor lzma

!include "setup_ui.nsh"

# ==================== NSIS属性 ================================

# 针对Vista和win7 的UAC进行权限请求.
# RequestExecutionLevel none|user|highest|admin
RequestExecutionLevel admin


; 安装包名字.
Name "${PRODUCT_NAME}"

# 安装程序文件名.

OutFile "..\output\${INSTALL_OUTPUT_NAME}"

;$PROGRAMFILES32\Netease\NIM\

InstallDir "$PROGRAMFILES\${INSTALL_APPEND_PATH}"

# 安装和卸载程序图标
Icon              "${INSTALL_ICO}"
UninstallIcon     "${UNINSTALL_ICO}"
