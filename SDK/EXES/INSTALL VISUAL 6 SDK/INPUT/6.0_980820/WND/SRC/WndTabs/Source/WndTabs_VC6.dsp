# Microsoft Developer Studio Project File - Name="WndTabs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=WndTabs - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WndTabs_VC6.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WndTabs_VC6.mak" CFG="WndTabs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WndTabs - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WndTabs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "WndTabs"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WndTabs - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GX /Zi /O2 /I "..\..\BCG\BCGControlBar" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_BCGCONTROLBAR_STATIC_" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40d /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 version.lib Lib\WndTabsLib.lib /nologo /base:"0x44000000" /subsystem:windows /dll /debug /machine:I386 /out:"Release/WndTabs.dll" /libpath:"..\..\BCG\bin" /OPT:NOREF
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "WndTabs - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /I "..\..\BCG\BCGControlBar" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_BCGCONTROLBAR_STATIC_" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40d /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib Lib\WndTabsLibD.lib /nologo /base:"0x44000000" /subsystem:windows /dll /debug /machine:I386 /out:"Debug/WndTabs.dll" /pdbtype:sept /libpath:"..\..\BCG\bin"

!ENDIF 

# Begin Target

# Name "WndTabs - Win32 Release"
# Name "WndTabs - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddInInt.cpp

!IF  "$(CFG)" == "WndTabs - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "WndTabs - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AddInComm\AICLoader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\AutoPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGSupp.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdSelDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Commands.cpp
# End Source File
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\DevStudioWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DS_MDIWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DSAddIn.cpp
# End Source File
# Begin Source File

SOURCE=.\DSWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\Extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\FancyTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Help\HelpIDs.h
# End Source File
# Begin Source File

SOURCE=.\HHSupp.cpp
# End Source File
# Begin Source File

SOURCE=.\Logger.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\PIDL.cpp
# ADD CPP /D "STRICT" /Yu
# End Source File
# Begin Source File

SOURCE=.\SDK_Supp.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellContextMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SubclassWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TabActivationShortcutsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TabManagerWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\TabsWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\TreePropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\VCVerMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\WndTabs.cpp
# End Source File
# Begin Source File

SOURCE=.\WndTabs.def
# End Source File
# Begin Source File

SOURCE=.\Help\WndTabs.hhp

!IF  "$(CFG)" == "WndTabs - Win32 Release"

USERDEP__WNDTA="Help\HelpIDs.h"	"Help\Cshelp.txt"	
# Begin Custom Build
OutDir=.\Release
TargetName=WndTabs
InputPath=.\Help\WndTabs.hhp

"$(OutDir)\$(TargetName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	MakeHH.bat $(TargetName)

# End Custom Build

!ELSEIF  "$(CFG)" == "WndTabs - Win32 Debug"

USERDEP__WNDTA="Help\HelpIDs.h"	"Help\Cshelp.txt"	
# Begin Custom Build
OutDir=.\Debug
TargetName=WndTabs
InputPath=.\Help\WndTabs.hhp

"$(OutDir)\$(TargetName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	MakeHH.bat $(TargetName)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WndTabs.odl
# ADD MTL /h "WndTabsTypes.h"
# End Source File
# Begin Source File

SOURCE=.\WndTabs.rc

!IF  "$(CFG)" == "WndTabs - Win32 Release"

# ADD BASE RSC /l 0x409 /i "Release"
# ADD RSC /l 0x409 /i "Release" /i "..\..\BCG\BCGControlBar"

!ELSEIF  "$(CFG)" == "WndTabs - Win32 Debug"

# ADD BASE RSC /l 0x1009 /i "Debug"
# ADD RSC /l 0x409 /i "Debug" /i "..\..\BCG\BCGControlBar"

!ENDIF 

# End Source File
# End Group
# Begin Group "Source Files - Dialogs"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\BugReportsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeCtxMenuDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DontShowAgainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HKWarningDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectCharDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupWizard.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolbarSetup.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddInComm\AddInComm.h
# End Source File
# Begin Source File

SOURCE=.\AddInComm\AICLoader.h
# End Source File
# Begin Source File

SOURCE=.\AutoPropPage.h
# End Source File
# Begin Source File

SOURCE=.\BCGSupp.h
# End Source File
# Begin Source File

SOURCE=.\BugReportsDlg.h
# End Source File
# Begin Source File

SOURCE=.\CfgVars.h
# End Source File
# Begin Source File

SOURCE=.\CmdSelDialog.h
# End Source File
# Begin Source File

SOURCE=.\Commands.h
# End Source File
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeCtxMenuDlg.h
# End Source File
# Begin Source File

SOURCE=.\DevStudioWnd.h
# End Source File
# Begin Source File

SOURCE=.\DontShowAgainDlg.h
# End Source File
# Begin Source File

SOURCE=.\DS_MDIWnd.h
# End Source File
# Begin Source File

SOURCE=.\DSAddIn.h
# End Source File
# Begin Source File

SOURCE=.\DSWindow.h
# End Source File
# Begin Source File

SOURCE=.\Extensions.h
# End Source File
# Begin Source File

SOURCE=.\FancyTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\HHSupp.h
# End Source File
# Begin Source File

SOURCE=.\HKWarningDlg.h
# End Source File
# Begin Source File

SOURCE=.\Imports.h
# End Source File
# Begin Source File

SOURCE=.\InfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\Logger.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\Options.h
# End Source File
# Begin Source File

SOURCE=.\PIDL.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SDK_Supp.h
# End Source File
# Begin Source File

SOURCE=.\SelectCharDialog.h
# End Source File
# Begin Source File

SOURCE=.\SetupWizard.h
# End Source File
# Begin Source File

SOURCE=.\ShellContextMenu.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutsDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubclassWnd.h
# End Source File
# Begin Source File

SOURCE=.\TabActivationShortcutsDlg.h
# End Source File
# Begin Source File

SOURCE=.\TabManagerWindow.h
# End Source File
# Begin Source File

SOURCE=.\TabsWindow.h
# End Source File
# Begin Source File

SOURCE=.\ToolbarSetup.h
# End Source File
# Begin Source File

SOURCE=.\TreePropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\VCVerMgr.h
# End Source File
# Begin Source File

SOURCE=.\VersionNo.h
# End Source File
# Begin Source File

SOURCE=.\WndTabs.h
# End Source File
# Begin Source File

SOURCE=..\WndTabsSDK\WTSDKDefs.h
# End Source File
# Begin Source File

SOURCE=..\WndTabsSDK\WTSDKDefs_Priv.h
# End Source File
# End Group
# Begin Group "Sources/Headers - 3rd party"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3rdParty\AggressiveOptimize.h
# End Source File
# Begin Source File

SOURCE=.\3rdParty\htmlhelp.h
# End Source File
# Begin Source File

SOURCE=.\3rdParty\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\3rdParty\HyperLink.h
# End Source File
# Begin Source File

SOURCE=..\WndTabsSDK\WndTabsInt.cpp
# End Source File
# Begin Source File

SOURCE=..\WndTabsSDK\WndTabsInt.h
# End Source File
# Begin Source File

SOURCE=.\3rdParty\WWhizInterface2.h
# End Source File
# Begin Source File

SOURCE=.\3rdParty\WWhizInterface2Loader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\3rdParty\WWhizInterface2Loader.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\2clip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\about.ico
# End Source File
# Begin Source File

SOURCE=.\res\banner.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bbtn256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bigbug.ico
# End Source File
# Begin Source File

SOURCE=.\res\bigbutton.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bug.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bulb2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cancel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\customize.bmp
# End Source File
# Begin Source File

SOURCE=.\res\customize2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\customize3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\generate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\go.bmp
# End Source File
# Begin Source File

SOURCE=.\res\go_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\history.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\info.bmp
# End Source File
# Begin Source File

SOURCE=.\res\info2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keyboard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\lang_dl.ico
# End Source File
# Begin Source File

SOURCE=.\res\lang_sel.ico
# End Source File
# Begin Source File

SOURCE=.\res\lg_mail.ico
# End Source File
# Begin Source File

SOURCE=.\res\lg_net.ico
# End Source File
# Begin Source File

SOURCE=.\res\light.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menubtn24b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menubtn256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menubutton.bmp
# End Source File
# Begin Source File

SOURCE=.\res\net.bmp
# End Source File
# Begin Source File

SOURCE=.\res\no.bmp
# End Source File
# Begin Source File

SOURCE=.\res\numbers.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ok.bmp
# End Source File
# Begin Source File

SOURCE=.\res\paste.bmp
# End Source File
# Begin Source File

SOURCE=.\res\qmark.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reg_opt.ico
# End Source File
# Begin Source File

SOURCE=.\res\reg_opt2.ico
# End Source File
# Begin Source File

SOURCE=.\res\register.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reload.bmp
# End Source File
# Begin Source File

SOURCE=.\res\renumber.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reorder.bmp
# End Source File
# Begin Source File

SOURCE=.\res\s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\scroll.bmp
# End Source File
# Begin Source File

SOURCE=.\res\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sw_back.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sw_banner.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tabactivate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TBarLrge.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TBarMedm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_pic.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UserBtns.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wizard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WndTabs.ico
# End Source File
# Begin Source File

SOURCE=.\res\WndTabs.rc2
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\WndTabsExt.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Help\Acknowledgments.html
# End Source File
# Begin Source File

SOURCE=.\Help\cmdref.html
# End Source File
# Begin Source File

SOURCE=.\Help\Compatibility.html
# End Source File
# Begin Source File

SOURCE=.\Help\compiling.html
# End Source File
# Begin Source File

SOURCE=.\Help\contact.html
# End Source File
# Begin Source File

SOURCE=.\Help\Cshelp.txt
# End Source File
# Begin Source File

SOURCE=.\Help\CustomizeCommands.html
# End Source File
# Begin Source File

SOURCE=.\Help\CustomizeKeyboard.html
# End Source File
# Begin Source File

SOURCE=.\Help\CustomizeOptions.html
# End Source File
# Begin Source File

SOURCE=.\Help\cvs.html
# End Source File
# Begin Source File

SOURCE=.\Help\FAQ.html
# End Source File
# Begin Source File

SOURCE=.\Help\idh_disp_delim.html
# End Source File
# Begin Source File

SOURCE=.\Help\idh_use_group_ops.html
# End Source File
# Begin Source File

SOURCE=.\Help\idh_use_wwhiz.html
# End Source File
# Begin Source File

SOURCE=.\Help\KnownProbs.html
# End Source File
# Begin Source File

SOURCE=.\Help\license.html
# End Source File
# Begin Source File

SOURCE=.\Help\notavail.html
# End Source File
# Begin Source File

SOURCE=.\Help\OptionsGeneral.html
# End Source File
# Begin Source File

SOURCE=.\Help\OptionsMenus.html
# End Source File
# Begin Source File

SOURCE=.\Help\OptionsTabs.html
# End Source File
# Begin Source File

SOURCE=.\Help\OptionsTabsAdvanced.html
# End Source File
# Begin Source File

SOURCE=.\Help\OptionsTabsContent.html
# End Source File
# Begin Source File

SOURCE=.\Help\OptionsTabsOrdering.html
# End Source File
# Begin Source File

SOURCE=.\Help\OptionsTabsTrimming.html
# End Source File
# Begin Source File

SOURCE=.\Help\OptionsWinFileMan.html
# End Source File
# Begin Source File

SOURCE=.\Help\pipeline.html
# End Source File
# Begin Source File

SOURCE=.\Help\reg.html
# End Source File
# Begin Source File

SOURCE=.\Help\VerHist.html
# End Source File
# Begin Source File

SOURCE=.\Help\Welcome.html
# End Source File
# Begin Source File

SOURCE=.\Help\WndTabsExt.html
# End Source File
# End Group
# Begin Source File

SOURCE=.\License.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ToDo.txt
# End Source File
# End Target
# End Project
