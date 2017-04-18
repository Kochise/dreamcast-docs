# Microsoft Developer Studio Project File - Name="BCGControlBarStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=BCGControlBarStatic - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGControlBarStatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGControlBarStatic.mak" CFG="BCGControlBarStatic - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGControlBarStatic - Win32 Release MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Debug MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Unicode Release MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Unicode Debug MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/BCGControlBar", WIAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGControlBarStatic - Win32 Release MFC DLL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Bin\BCGCB474Static.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Debug MFC DLL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "DebugStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Bin\BCGCB474StaticD.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Unicode Release MFC DLL"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGControlBarStatic___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "BCGControlBarStatic___Win32_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "UReleaseStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Bin\BCGCB474StaticU.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Unicode Debug MFC DLL"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BCGControlBarStatic___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "BCGControlBarStatic___Win32_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "UDebugStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Lib\BCGControlBarStaticD.lib"
# ADD LIB32 /nologo /out:"..\Bin\BCGCB474StaticUD.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BCGControlBarStatic___Win32_Debug_MFC_Shared"
# PROP BASE Intermediate_Dir "BCGControlBarStatic___Win32_Debug_MFC_Shared"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "DebugStaticShared"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_BCGCONTROLBAR_STATIC_" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_BCGCONTROLBAR_STATIC_" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Bin\BCGCB47StaticDS.lib"
# ADD LIB32 /nologo /out:"..\Bin\BCGCB474StaticDS.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGControlBarStatic___Win32_Release_MFC_Shared"
# PROP BASE Intermediate_Dir "BCGControlBarStatic___Win32_Release_MFC_Shared"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "ReleaseStaticShared"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_BCGCONTROLBAR_STATIC_" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Bin\BCGCB47Static.lib"
# ADD LIB32 /nologo /out:"..\Bin\BCGCB474StaticS.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Unicode Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BCGControlBarStatic___Win32_Unicode_Debug_MFC_Shared"
# PROP BASE Intermediate_Dir "BCGControlBarStatic___Win32_Unicode_Debug_MFC_Shared"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "UDebugStaticShared"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "_BCGCONTROLBAR_STATIC_" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Bin\BCGCB47StaticUD.lib"
# ADD LIB32 /nologo /out:"..\Bin\BCGCB474StaticUDS.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Unicode Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGControlBarStatic___Win32_Unicode_Release_MFC_Shared"
# PROP BASE Intermediate_Dir "BCGControlBarStatic___Win32_Unicode_Release_MFC_Shared"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "UReleaseStaticShared"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "_BCGCONTROLBAR_STATIC_" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Bin\BCGCB47StaticU.lib"
# ADD LIB32 /nologo /out:"..\Bin\BCGCB474StaticUS.lib"

!ENDIF 

# Begin Target

# Name "BCGControlBarStatic - Win32 Release MFC DLL"
# Name "BCGControlBarStatic - Win32 Debug MFC DLL"
# Name "BCGControlBarStatic - Win32 Unicode Release MFC DLL"
# Name "BCGControlBarStatic - Win32 Unicode Debug MFC DLL"
# Name "BCGControlBarStatic - Win32 Debug"
# Name "BCGControlBarStatic - Win32 Release"
# Name "BCGControlBarStatic - Win32 Unicode Debug"
# Name "BCGControlBarStatic - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGAnimCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGColorBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGColorDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGColorMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGCommandManager.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGContextMenuManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGControlBarImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGDockContext.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGDropDown.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGEditListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGExCheckList.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGFrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGKeyboardManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGKeyMapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGLocalRes.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMainClientAreaWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGMDIChildWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMDIFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMouseManager.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGOleIPFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\bcgoutlookbar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGOutlookButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGPopupMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPrintPreviewView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGShowAllButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGSizingControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\bcgsound.cpp
# End Source File
# Begin Source File

SOURCE=.\bcgtabwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGTearOffManager.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarComboBoxButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDateTimeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarDropSource.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarEditBoxButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolBarImages.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarMenuButtonsButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarRegularMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarSystemMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGURLLinkButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGUserTool.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGUserToolsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGWindowsManagerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGWorkspace.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonAppearanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonsList.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonsTextList.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\CBCGToolbarCustomize.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\CBCGToolbarCustomizePages.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdUsageCount.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ColorSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\GLOBALS.CPP
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImageEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImageHash.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImagePaintArea.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyAssign.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyboardPage.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MenuHash.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuImages.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MenuPage.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MousePage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PowerColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertySheetCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\RebarState.cpp
# End Source File
# Begin Source File

SOURCE=.\RegPath.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ToolbarNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TrackMouse.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGAnimCtrl.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\bcgbarres.h
# End Source File
# Begin Source File

SOURCE=.\BCGButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGCB.h
# End Source File
# Begin Source File

SOURCE=.\bcgcbver.h
# End Source File
# Begin Source File

SOURCE=.\BCGColorBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGColorButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGColorDialog.h
# End Source File
# Begin Source File

SOURCE=.\BCGColorMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGCommandManager.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGContextMenuManager.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGControlBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGControlBarImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCGDialog.h
# End Source File
# Begin Source File

SOURCE=.\BCGDialogBar.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGDockBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGDockContext.h
# End Source File
# Begin Source File

SOURCE=.\BCGDropDown.h
# End Source File
# Begin Source File

SOURCE=.\BCGEditListBox.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGExCheckList.h
# End Source File
# Begin Source File

SOURCE=.\BCGFileDialog.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGFrameImpl.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGFrameWnd.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGKeyboardManager.h
# End Source File
# Begin Source File

SOURCE=.\BCGKeyMapDlg.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\bcglocalres.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMainClientAreaWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCGMDIChildWnd.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMDIFrameWnd.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMenuBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGMenuButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMouseManager.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMultiDocTemplate.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGOleIPFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\bcgoutlookbar.h
# End Source File
# Begin Source File

SOURCE=.\BCGOutlookButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGPopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGPopupMenuBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGPrintPreviewView.h
# End Source File
# Begin Source File

SOURCE=.\BCGRegistry.h
# End Source File
# Begin Source File

SOURCE=.\BCGShowAllButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGSizingControlBar.h
# End Source File
# Begin Source File

SOURCE=.\bcgsound.h
# End Source File
# Begin Source File

SOURCE=.\bcgtabwnd.h
# End Source File
# Begin Source File

SOURCE=.\BCGTearOffManager.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolBar.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarComboBoxButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDateTimeCtrl.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarDropSource.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarEditBoxButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolBarImages.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarMenuButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarMenuButtonsButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarRegularMenuButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarSystemMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolsPage.h
# End Source File
# Begin Source File

SOURCE=.\BCGURLLinkButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGUserTool.h
# End Source File
# Begin Source File

SOURCE=.\BCGUserToolsManager.h
# End Source File
# Begin Source File

SOURCE=.\BCGWindowsManagerDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCGWorkspace.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonAppearanceDlg.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonsList.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonsTextList.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\CBCGToolbarCustomize.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\CBCGToolbarCustomizePages.h
# End Source File
# Begin Source File

SOURCE=.\CmdUsageCount.h
# End Source File
# Begin Source File

SOURCE=.\ColorPage1.h
# End Source File
# Begin Source File

SOURCE=.\ColorPage2.h
# End Source File
# Begin Source File

SOURCE=.\ColorPopup.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ColorSelector.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\GLOBALS.H
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImageEditDlg.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImageHash.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImagePaintArea.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyAssign.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyboardPage.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyHelper.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MenuHash.h
# End Source File
# Begin Source File

SOURCE=.\MenuImages.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MenuPage.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MousePage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsPage.h
# End Source File
# Begin Source File

SOURCE=.\PowerColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\PropertySheetCtrl.h
# End Source File
# Begin Source File

SOURCE=.\RebarState.h
# End Source File
# Begin Source File

SOURCE=.\RegPath.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ToolbarNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\TrackMouse.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\color.cur
# End Source File
# Begin Source File

SOURCE=.\res\copy.cur
# End Source File
# Begin Source File

SOURCE=.\res\delete.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete.cur
# End Source File
# Begin Source File

SOURCE=.\res\down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ellipse.cur
# End Source File
# Begin Source File

SOURCE=.\res\fill.cur
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\help.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line.cur
# End Source File
# Begin Source File

SOURCE=.\res\menuimg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\move.cur
# End Source File
# Begin Source File

SOURCE=.\res\new.bmp
# End Source File
# Begin Source File

SOURCE=.\res\palette.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pen.cur
# End Source File
# Begin Source File

SOURCE=.\res\PrintPreview.bmp
# End Source File
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# Begin Source File

SOURCE=.\res\rect.cur
# End Source File
# Begin Source File

SOURCE=.\res\tool.ico
# End Source File
# Begin Source File

SOURCE=.\res\up.bmp
# End Source File
# End Target
# End Project
