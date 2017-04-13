# Microsoft Developer Studio Project File - Name="wins" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=wins - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wins.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wins.mak" CFG="wins - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wins - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wins - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wins - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wins - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\wins.dll
InputPath=.\Debug\wins.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "wins - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\wins.dll
InputPath=.\ReleaseMinSize\wins.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "wins - Win32 Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\wins.dll
InputPath=.\ReleaseMinDependency\wins.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "wins - Win32 Debug"
# Name "wins - Win32 Release MinSize"
# Name "wins - Win32 Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DirList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWinMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\FileItem.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WindowsList.cpp
# End Source File
# Begin Source File

SOURCE=.\wins.cpp
# End Source File
# Begin Source File

SOURCE=.\wins.def
# End Source File
# Begin Source File

SOURCE=.\wins.idl
# ADD MTL /tlb ".\wins.tlb" /h "wins.h" /iid "wins_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\wins.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DirList.h
# End Source File
# Begin Source File

SOURCE=.\DlgWinMgr.h
# End Source File
# Begin Source File

SOURCE=.\EnumWndInfo.h
# End Source File
# Begin Source File

SOURCE=.\FileItem.h
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WindowsList.h
# End Source File
# Begin Source File

SOURCE=.\winsapp.h
# End Source File
# Begin Source File

SOURCE=.\wndrect.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\toolbar_.bmp
# End Source File
# Begin Source File

SOURCE=.\WindowsList.rgs
# End Source File
# End Group
# End Target
# End Project
# Section wins : {1CDA0666-8D5F-11D1-82FC-00A0C91BC942}
# 	2:14:MyListCtrl.cpp:MyListCtrl1.cpp
# 	2:15:CLASS: SortInfo:SortInfo
# 	2:19:Application Include:resource.h
# End Section
# Section wins : {1CDA0661-8D5F-11D1-82FC-00A0C91BC942}
# 	1:13:IDD_DLGWINMGR:105
# 	2:16:Resource Include:resource.h
# 	2:11:DlgWinMgr.h:DlgWinMgr.h
# 	2:13:DlgWinMgr.cpp:DlgWinMgr.cpp
# 	2:10:ENUM: enum:enum
# 	2:13:IDD_DLGWINMGR:IDD_DLGWINMGR
# 	2:17:CLASS: CDlgWinMgr:CDlgWinMgr
# 	2:19:Application Include:resource.h
# End Section
# Section wins : {1CDA0665-8D5F-11D1-82FC-00A0C91BC942}
# 	2:15:CLASS: CWndRect:CWndRect
# 	2:11:CWinMgr.cpp:CWinMgr1.cpp
# 	2:26:FUNC: EnumChildWindowsProc:EnumChildWindowsProc
# 	2:19:CLASS: CEnumWndInfo:CEnumWndInfo
# 	2:19:Application Include:resource.h
# 	2:25:FUNC: EnumMainWindowsProc:EnumMainWindowsProc
# End Section
# Section wins : {1CDA0660-8D5F-11D1-82FC-00A0C91BC942}
# 	2:15:CLASS: CDirList:CDirList
# 	2:11:DirList.cpp:DirList.cpp
# 	2:9:DirList.h:DirList.h
# 	2:19:Application Include:resource.h
# End Section
# Section wins : {1CDA0664-8D5F-11D1-82FC-00A0C91BC942}
# 	2:14:MyListCtrl.cpp:MyListCtrl.cpp
# 	2:12:MyListCtrl.h:MyListCtrl.h
# 	2:18:CLASS: CMyListCtrl:CMyListCtrl
# 	2:19:Application Include:resource.h
# End Section
# Section wins : {1CDA0663-8D5F-11D1-82FC-00A0C91BC942}
# 	2:16:CLASS: CFileItem:CFileItem
# 	2:12:FileItem.cpp:FileItem.cpp
# 	2:10:FileItem.h:FileItem.h
# 	2:19:Application Include:resource.h
# End Section
# Section wins : {1CDA0662-8D5F-11D1-82FC-00A0C91BC942}
# 	2:15:CLASS: CWndRect:CWndRect
# 	2:11:CWinMgr.cpp:CWinMgr.cpp
# 	2:26:FUNC: EnumChildWindowsProc:EnumChildWindowsProc
# 	2:19:CLASS: CEnumWndInfo:CEnumWndInfo
# 	2:19:Application Include:resource.h
# 	2:25:FUNC: EnumMainWindowsProc:EnumMainWindowsProc
# End Section
