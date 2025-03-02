
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

!define INSTALL_PAGE_CONFIG 			0
!define INSTALL_PAGE_PROCESSING 		1
!define INSTALL_PAGE_FINISH 			2
!define INSTALL_PAGE_UNISTCONFIG 		3
!define INSTALL_PAGE_UNISTPROCESSING 	4
!define INSTALL_PAGE_UNISTFINISH 		5

# 自定义页面
Page custom DUIPage

# 自定义卸载页面
UninstPage custom un.DUIPage

# ======================= DUILIB 自定义页面 =========================
Var hInstallDlg
Var hMsgBoxDlg
Var InstallState

Function DUIPage
    StrCpy $InstallState "0"	#设置未安装完成状态
	InitPluginsDir   	
	SetOutPath "$PLUGINSDIR"
	File "${INSTALL_LICENCE_FILENAME}"
    File "${INSTALL_RES_PATH}"
	File /oname=logo.ico "${INSTALL_ICO}" 		#此处的目标文件一定是logo.ico，否则控件将找不到文件 
	nsxsskin::InitInstallPage "$PLUGINSDIR\" "${INSTALL_LICENCE_FILENAME}" #指定插件路径及协议文件名称
    Pop $hInstallDlg
	#设置安装包的标题及任务栏显示  
	nsxsskin::SetWindowTile $hInstallDlg "${PRODUCT_NAME}安装程序"
	#设置控件显示安装路径 
    nsxsskin::SetControlAttribute $hInstallDlg "editDir" "text" "$INSTDIR\"
	Call BindUIControls
	
	nsxsskin::ShowPage
FunctionEnd

# 显示提示对话框
Function ShowMsgBox
	nsxsskin::InitMessageBox "msgbox.xml" "btnOK" "btnCancel,btnClose"
	Pop $hMsgBoxDlg
	nsxsskin::SetControlAttribute $hMsgBoxDlg "lblTitle" "text" "提示"
	nsxsskin::SetControlAttribute $hMsgBoxDlg "lblMsg" "text" "$R8"
    ${If} $R5 != ""
        nsxsskin::SetControlAttribute $hMsgBoxDlg "btnOK" "text" "$R5"
    ${EndIf}
    ${If} $R5 != ""
        nsxsskin::SetControlAttribute $hMsgBoxDlg "btnCancel" "text" "$R6"   
    ${EndIf}    
	${If} "$R7" == "1"
		nsxsskin::SetControlAttribute $hMsgBoxDlg "hlCancel" "visible" "true"
	${EndIf}	
	nsxsskin::ShowMessageBox
FunctionEnd

#绑定安装的界面事件 
Function BindUIControls
	GetFunctionAddress $0 OnBtnMinimizeClick
    nsxsskin::BindCallBack $hInstallDlg "btnMinimize" $0
    
	GetFunctionAddress $0 OnExitDUISetup
    nsxsskin::BindCallBack $hInstallDlg "btnClose" $0
    
    GetFunctionAddress $0 OnCheckLicenseClick
    nsxsskin::BindCallBack $hInstallDlg "chkAgree" $0
    
    GetFunctionAddress $0 OnBtnLicenseClick
    nsxsskin::BindCallBack $hInstallDlg "btnAgreement" $0   

    GetFunctionAddress $0 OnBtnShowConfig
    nsxsskin::BindCallBack $hInstallDlg "btnAgree" $0
    
    GetFunctionAddress $0 OnBtnSelectDirClick
    nsxsskin::BindCallBack $hInstallDlg "btnSelectDir" $0	
    
    #绑定窗口通过alt+f4等方式关闭时的通知事件 
	GetFunctionAddress $0 OnSysCommandCloseEvent
    nsxsskin::BindCallBack $hInstallDlg "syscommandclose" $0
    
    GetFunctionAddress $0 OnBtnShowMoreClick
    nsxsskin::BindCallBack $hInstallDlg "btnShowMore" $0
	
	GetFunctionAddress $0 OnBtnHideMoreClick
    nsxsskin::BindCallBack $hInstallDlg "btnHideMore" $0
    
    #绑定路径变化的通知事件 
	GetFunctionAddress $0 OnEditDirTextChange
    nsxsskin::BindCallBack $hInstallDlg "editDir" $0
    
    #开始安装按钮事件
    GetFunctionAddress $0 OnBtnInstallClick
    nsxsskin::BindCallBack $hInstallDlg "btnInstall" $0

FunctionEnd

# 最小化按钮事件
Function OnBtnMinimizeClick
    SendMessage $hInstallDlg ${WM_SYSCOMMAND} 0xF020 0
FunctionEnd

# 退出安装事件
Function OnExitDUISetup
	${If} $InstallState == "0"		
		StrCpy $R8 "安装尚未完成，您确定退出安装么？"
		StrCpy $R7 "1"
		Call ShowMsgBox
		pop $0
		${If} $0 == 0
			Goto endfun
		${EndIf}
	${EndIf}
	nsxsskin::ExitDUISetup
endfun:  
FunctionEnd

#CTRL+F4关闭时的事件通知 
Function OnSysCommandCloseEvent
	Call OnExitDUISetup
FunctionEnd

# 选择安装路径
Function OnBtnSelectDirClick
    nsxsskin::SelectInstallDir $hInstallDlg "请选择安装路径"
    Pop $0
	${Unless} "$0" == ""
		#此处判断安装路径最后一段，如果已经是与我要追加的目录名一样，就不再追加了，如果不一样，则还需要追加。
		HxcUtils::FixInstallPath "$0" "${INSTALL_APPEND_PATH}"
		Pop $0
		StrCpy $INSTDIR $0
        nsxsskin::SetControlAttribute $hInstallDlg "editDir" "text" "$INSTDIR"
	${EndUnless}
FunctionEnd

#此处是路径变化时的事件通知 
Function OnEditDirTextChange
	#可在此获取路径，判断是否合法等处理 
	nsxsskin::GetControlAttribute $hInstallDlg "editDir" "text"
    Pop $0	
    StrCpy $INSTDIR "$0"
    ${If} $0 == ""
        nsxsskin::SetControlAttribute $hInstallDlg "btnInstall" "enabled" "false"
    ${Else}
        nsxsskin::GetControlAttribute $hInstallDlg "chkAgree" "selected"
        Pop $0
        ${If} $0 == "1"        
            nsxsskin::SetControlAttribute $hInstallDlg "btnInstall" "enabled" "true"
        ${Else}
            nsxsskin::SetControlAttribute $hInstallDlg "btnInstall" "enabled" "false"
        ${EndIf}            
    ${EndIf}    
FunctionEnd

#根据选中的情况来控制按钮是否灰度显示 
Function OnCheckLicenseClick
	nsxsskin::GetControlAttribute $hInstallDlg "chkAgree" "selected"
    Pop $0
	${If} $0 == "0"        
		nsxsskin::SetControlAttribute $hInstallDlg "btnInstall" "enabled" "true"
	${Else}
		nsxsskin::SetControlAttribute $hInstallDlg "btnInstall" "enabled" "false"
    ${EndIf}
FunctionEnd

Function OnBtnLicenseClick
    ;nsxsskin::ShowPageItem "wizardTab" ${INSTALL_PAGE_LICENSE}
	nsxsskin::SetControlAttribute $hInstallDlg "licenseshow" "visible" "true"
	nsxsskin::GetControlAttribute $hInstallDlg "moreconfiginfo" "visible"
	Pop $0
	${If} $0 = 0        
		nsxsskin::SetControlAttribute $hInstallDlg "licenseshow" "pos" "10,35,540,390"
		nsxsskin::SetControlAttribute $hInstallDlg "editLicense" "height" "270"		
	${Else}
		nsxsskin::SetControlAttribute $hInstallDlg "licenseshow" "pos" "10,35,540,460"
		nsxsskin::SetControlAttribute $hInstallDlg "editLicense" "height" "340"
    ${EndIf}	
FunctionEnd

Function OnBtnShowConfig
	nsxsskin::SetControlAttribute $hInstallDlg "licenseshow" "visible" "false"
FunctionEnd

Function StepHeightSizeAsc
${ForEach} $R0 410 485 + 10
  nsxsskin::SetWindowSize $hInstallDlg 550 $R0
  Sleep 20
${Next}
FunctionEnd

Function OnBtnShowMoreClick	
	nsxsskin::SetControlAttribute $hInstallDlg "moreconfiginfo" "visible" "true"
	nsxsskin::SetControlAttribute $hInstallDlg "btnShowMore" "visible" "false"
	nsxsskin::SetControlAttribute $hInstallDlg "btnHideMore" "visible" "true"
	;调整窗口高度 
	 GetFunctionAddress $0 StepHeightSizeAsc
    BgWorker::CallAndWait	
	nsxsskin::SetWindowSize $hInstallDlg 550 485
FunctionEnd

Function StepHeightSizeDsc
${ForEach} $R0 485 410 - 10
  nsxsskin::SetWindowSize $hInstallDlg 550 $R0
  Sleep 20
${Next}
FunctionEnd

Function OnBtnHideMoreClick	
	nsxsskin::SetControlAttribute $hInstallDlg "moreconfiginfo" "visible" "false"
	nsxsskin::SetControlAttribute $hInstallDlg "btnShowMore" "visible" "true"
	nsxsskin::SetControlAttribute $hInstallDlg "btnHideMore" "visible" "false"
	;调整窗口高度 
	 GetFunctionAddress $0 StepHeightSizeDsc
    BgWorker::CallAndWait
	nsxsskin::SetWindowSize $hInstallDlg 550 410
FunctionEnd

#创建开始菜单快捷方式
Function CreateStartMenuShortcut
    SetShellVarContext current
    CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"	
    WriteINIStr "$SMPROGRAMS\${PRODUCT_NAME}\XXXX公司 网站.url" "InternetShortcut" "URL" "http://www.abc.com/"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\${EXE_NAME}" "" "" 0 SW_SHOWNORMAL "" "启动${PRODUCT_NAME}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\卸载 ${PRODUCT_NAME}.lnk" "$INSTDIR\uninst.exe" "" "" 1

    SetShellVarContext all
    CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"	
    WriteINIStr "$SMPROGRAMS\${PRODUCT_NAME}\XXXX公司 网站.url" "InternetShortcut" "URL" "http://www.abc.com/"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\${EXE_NAME}" "" "" 0 SW_SHOWNORMAL "" "启动${PRODUCT_NAME}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\卸载 ${PRODUCT_NAME}.lnk" "$INSTDIR\uninst.exe" "" "" 1
    SetShellVarContext current  
FunctionEnd

Function ExtractCallback
    Pop $1
    Pop $2
    System::Int64Op $1 * 100
    Pop $3
    System::Int64Op $3 / $2
    Pop $0
	nsxsskin::SetControlAttribute $hInstallDlg "slrProgress" "value" "$0"
	nsxsskin::SetControlAttribute $hInstallDlg "slrProgressLabel" "text" "正在安装 $0%"
    
    ${If} $1 == $2
        nsxsskin::SetControlAttribute $hInstallDlg "slrProgress" "value" "100"	
        nsxsskin::SetControlAttribute $hInstallDlg "slrProgressLabel" "text" "正在安装 100%"        
    ${EndIf}
FunctionEnd

Function ExtractFunc
	#安装文件的7Z压缩包
	SetOutPath $INSTDIR

    File "${INSTALL_7Z_PATH}"
    GetFunctionAddress $R9 ExtractCallback
    nsis7zU::ExtractWithCallback "$INSTDIR\${INSTALL_7Z_NAME}" $R9
	Delete "$INSTDIR\${INSTALL_7Z_NAME}"
	
	Sleep 100
FunctionEnd


# 开始安装
Function OnBtnInstallClick
	nsxsskin::GetControlAttribute $hInstallDlg "editDir" "text"	
	pop $0
	${If} $0 == ""
        StrCpy $R8 "请选择安装路径!"
		StrCpy $R7 "0"
		Call ShowMsgBox
		Goto funcend
    ${EndIf}	

	Push "$0"
    HxcUtils::CheckPathValid
    Pop $1	
	${If} $1 == "0"
        StrCpy $R8 "您选择的安装路径无效，请重新选择!"
		StrCpy $R7 "0"
		Call ShowMsgBox
		Goto funcend
    ${EndIf}
    
    #此处判断安装路径最后一段，如果已经是与我要追加的目录名一样，就不再追加了，如果不一样，则还需要追加。
	HxcUtils::FixInstallPath "$INSTDIR" "${INSTALL_APPEND_PATH}"
    Pop $0
	StrCpy "$INSTDIR" "$0"
    
	#此处检测当前是否有程序正在运行，如果正在运行，提示先卸载再安装 
	nsProcess::_FindProcess "${EXE_NAME}"
	Pop $R0	
	${If} $R0 == 0
        StrCpy $R8 "检测到${PRODUCT_NAME}正在运行，请退出后重试!"
		StrCpy $R7 "0"
		Call ShowMsgBox
		Goto funcend
    ${EndIf}
		
	nsxsskin::SetControlAttribute $hInstallDlg "slrProgressLabel" "text" "正在安装"  
    #启动一个低优先级的后台线程解压缩程序文件(app.7z)
    GetFunctionAddress $0 ExtractFunc
    BgWorker::CallAndWait
	
    #创建开始菜单快捷方式
    Call CreateStartMenuShortcut
    
    #判断是否需要创建桌面快捷方式
	nsxsskin::GetControlAttribute $hInstallDlg "chkShotcut" "selected"	
	Pop $R0
	${If} $R0 == "1"
		SetShellVarContext all
        Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
        Sleep 10
		CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\${EXE_NAME}"
		SetShellVarContext current
	${EndIf}

	# 开机启动
	nsxsskin::GetControlAttribute $hInstallDlg "chkAutoRun" "selected"	
	Pop $R0
	${If} $R0 == "1"
		SetShellVarContext all
		CreateShortCut "$SMSTARTUP\${PRODUCT_NAME}.lnk" "$INSTDIR\${EXE_NAME}"
		SetShellVarContext current
	${EndIf}
    
    #创建卸载程序
    Call CreateUninstall
	
	StrCpy $InstallState "1"
	
	nsxsskin::ShowTabPageItem $hInstallDlg "wizardTab" ${INSTALL_PAGE_FINISH}
	
funcend:
FunctionEnd

# 生成卸载入口 
Function CreateUninstall
	#写入注册信息 
	SetRegView 32
	WriteRegStr HKLM "Software\MyApp\${PRODUCT_PATHNAME}" "InstPath" "$INSTDIR"
	
	WriteUninstaller "$INSTDIR\uninst.exe"
	
	# 添加卸载信息到控制面板
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "DisplayName" "${PRODUCT_NAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "UninstallString" "$INSTDIR\uninst.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "DisplayIcon" "$INSTDIR\${EXE_NAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "Publisher" "${PRODUCT_PUBLISHER}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "DisplayVersion" "${PRODUCT_VERSION}"
FunctionEnd

# 添加一个静默安装的入口
Section "silentInstallSec" SEC01
    MessageBox MB_OK|MB_ICONINFORMATION "Test silent install. you can add your silent install code here."
SectionEnd

#================================= 自定义卸载页面 ==================================

Var UnInstallState

Function un.DUIPage
    StrCpy $UnInstallState "0"
    InitPluginsDir
	SetOutPath "$PLUGINSDIR"
    File "${INSTALL_RES_PATH}"
	File /oname=logo.ico "${UNINSTALL_ICO}" 		#此处的目标文件一定是logo.ico，否则控件将找不到文件 
	nsxsskin::InitUnInstallPage "$PLUGINSDIR\"
    Pop $hInstallDlg
	nsxsskin::ShowTabPageItem $hInstallDlg "wizardTab" ${INSTALL_PAGE_UNISTCONFIG}
	#设置安装包的标题及任务栏显示  
	nsxsskin::SetWindowTile $hInstallDlg "${PRODUCT_NAME}卸载程序"
	nsxsskin::SetWindowSize $hInstallDlg 460 340    
    
	Call un.BindUnInstUIControls  
    nsxsskin::ShowPage 0	
FunctionEnd

#绑定卸载的事件 
Function un.BindUnInstUIControls
	GetFunctionAddress $0 un.OnBtnMinimizeClick
    nsxsskin::BindCallBack $hInstallDlg "btnMinimize" $0
    
    GetFunctionAddress $0 un.ExitDUISetup
    nsxsskin::BindCallBack $hInstallDlg "btnClose" $0
	
	; GetFunctionAddress $0 un.onUninstall
    ; nsxsskin::BindCallBack $hInstallDlg "btnUnInstall" $0
	
	GetFunctionAddress $0 un.ExitDUISetup
    nsxsskin::BindCallBack $hInstallDlg "btnCancel" $0
    
    GetFunctionAddress $0 un.ExitDUISetup
    nsxsskin::BindCallBack $hInstallDlg "btnUninstalled" $0    
FunctionEnd

Function un.OnBtnMinimizeClick
    SendMessage $hInstallDlg ${WM_SYSCOMMAND} 0xF020 0
FunctionEnd

Function un.ExitDUISetup
	nsxsskin::ExitDUISetup
FunctionEnd

# 添加一个静默卸载的入口 
Section "un.silentInstallSec" SEC02
    MessageBox MB_OK|MB_ICONINFORMATION "Test silent install. you can add your silent uninstall code here."
SectionEnd
