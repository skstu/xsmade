
# ===================== 外部插件以及宏 =============================
!include "StrFunc.nsh"
!include "WordFunc.nsh"
${StrRep}
${StrStr}
!include "LogicLib.nsh"
!include "nsDialogs.nsh"
!include "x64.nsh"
!include "WinVer.nsh" 

# ===================== 安装包版本 =============================
VIProductVersion             		"${PRODUCT_VERSION}"
VIAddVersionKey "ProductVersion"    "${PRODUCT_VERSION}"
VIAddVersionKey "ProductName"       "${PRODUCT_NAME}"
VIAddVersionKey "CompanyName"       "${PRODUCT_PUBLISHER}"
VIAddVersionKey "FileVersion"       "${PRODUCT_VERSION}"
VIAddVersionKey "InternalName"      "${EXE_NAME}"
VIAddVersionKey "FileDescription"   "${PRODUCT_NAME}"
VIAddVersionKey "LegalCopyright"    "${PRODUCT_LEGAL}"

Page custom DUIPage
UninstPage custom un.DUIPage

# ======================= DUILIB 自定义安装页面 =========================
Function DUIPage
	InitPluginsDir   	
	SetOutPath "$PLUGINSDIR"
	File "${INSTALL_LICENCE_FILENAME}"
    File "${INSTALL_RES_PATH}"
	File /oname=logo.ico "${INSTALL_ICO}" 		#此处的目标文件一定是logo.ico，否则控件将找不到文件 
	libnswxskin::StartInstall "$PLUGINSDIR\" "$PLUGINSDIR\${INSTALL_LICENCE_FILENAME}" "${INSTALL_DEFALT_SETUPPATH}"
FunctionEnd

Section "silentInstallSec" SEC01
    MessageBox MB_OK|MB_ICONINFORMATION "Test silent install. you can add your silent install code here."
SectionEnd

#================================= 自定义卸载页面 ==================================
Function un.DUIPage
	InitPluginsDir
	SetOutPath "$PLUGINSDIR"
    File "${INSTALL_RES_PATH}"
	File /oname=logo.ico "${UNINSTALL_ICO}" 		#此处的目标文件一定是logo.ico，否则控件将找不到文件 

	ReadRegStr $0 HKLM "Software\${PROJECT_NAME}\${PRODUCT_PATHNAME}" "InstPath"

	libnswxskin::StartUninstall "$PLUGINSDIR\" "$0"
FunctionEnd

Section "un.silentInstallSec" SEC02
    MessageBox MB_OK|MB_ICONINFORMATION "Test silent install. you can add your silent uninstall code here."
SectionEnd
