# Microsoft Developer Studio Project File - Name="TstCon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TstCon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TstCon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TstCon.mak" CFG="TstCon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TstCon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TstCon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TstCon - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "TCProps\Release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 NUL
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Release/TstCon32.exe"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Building help file...
PostBuild_Cmds=makehelp.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TstCon - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "TCProps\Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 NUL
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/TstCon32.exe" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Building help file...
PostBuild_Cmds=makehelp.bat
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "TstCon - Win32 Release"
# Name "TstCon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AProp.Cpp
# End Source File
# Begin Source File

SOURCE=.\APropDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\BindHost.Cpp
# End Source File
# Begin Source File

SOURCE=.\ComCatDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\ConInfDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\EvLogPg.Cpp
# End Source File
# Begin Source File

SOURCE=.\ExcepInf.Cpp
# End Source File
# Begin Source File

SOURCE=.\ExtCtl.Cpp
# End Source File
# Begin Source File

SOURCE=.\FeatPg.Cpp
# End Source File
# Begin Source File

SOURCE=.\IFacesPg.Cpp
# End Source File
# Begin Source File

SOURCE=.\InsCtlDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\Log.Cpp
# End Source File
# Begin Source File

SOURCE=.\LogDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\MacroCB.Cpp
# End Source File
# Begin Source File

SOURCE=.\MacroDB.Cpp
# End Source File
# Begin Source File

SOURCE=.\MacroDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.Cpp
# End Source File
# Begin Source File

SOURCE=.\MethInfo.Cpp
# End Source File
# Begin Source File

SOURCE=.\MethodDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\MFileWnd.Cpp
# End Source File
# Begin Source File

SOURCE=.\NewAPDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\OutWndVw.Cpp
# End Source File
# Begin Source File

SOURCE=.\PBagDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\PChngPg.Cpp
# End Source File
# Begin Source File

SOURCE=.\PEdReqPg.Cpp
# End Source File
# Begin Source File

SOURCE=.\PropBag.Cpp
# End Source File
# Begin Source File

SOURCE=.\RegCtlDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\Script.Cpp
# End Source File
# Begin Source File

SOURCE=.\ScrMngr.Cpp
# End Source File
# Begin Source File

SOURCE=.\ServPg.Cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabOrdDg.Cpp
# End Source File
# Begin Source File

SOURCE=.\TCDoc.Cpp
# End Source File
# Begin Source File

SOURCE=.\TCItem.Cpp
# End Source File
# Begin Source File

SOURCE=.\TCSplit.Cpp
# End Source File
# Begin Source File

SOURCE=.\TCTrace.Cpp
# End Source File
# Begin Source File

SOURCE=.\TCView.Cpp
# End Source File
# Begin Source File

SOURCE=.\TstCon.Cpp
# End Source File
# Begin Source File

SOURCE=.\TstCon.odl
# ADD MTL /h "TstConIF.H" /iid "TstCon_i.C"
# End Source File
# Begin Source File

SOURCE=.\TstCon.rc

!IF  "$(CFG)" == "TstCon - Win32 Release"

# ADD BASE RSC /l 0x409 /i "Release"
# ADD RSC /l 0x409 /fo"Release/TstCon.res" /i "Release" /i "TCProps\Release"

!ELSEIF  "$(CFG)" == "TstCon - Win32 Debug"

# ADD BASE RSC /l 0x409 /i "Debug"
# ADD RSC /l 0x409 /fo"Debug/TstCon.res" /i "Debug" /i "TCProps\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TypeAttr.Cpp
# End Source File
# Begin Source File

SOURCE=.\VarUtils.Cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AProp.H
# End Source File
# Begin Source File

SOURCE=.\APropDg.H
# End Source File
# Begin Source File

SOURCE=.\BindHost.H
# End Source File
# Begin Source File

SOURCE=.\ComCatDg.H
# End Source File
# Begin Source File

SOURCE=.\ConInfDg.H
# End Source File
# Begin Source File

SOURCE=.\EvLogPg.H
# End Source File
# Begin Source File

SOURCE=.\ExcepInf.H
# End Source File
# Begin Source File

SOURCE=.\ExtCtl.H
# End Source File
# Begin Source File

SOURCE=.\FeatPg.H
# End Source File
# Begin Source File

SOURCE=.\IFacesPg.H
# End Source File
# Begin Source File

SOURCE=.\InsCtlDg.H
# End Source File
# Begin Source File

SOURCE=.\Log.H
# End Source File
# Begin Source File

SOURCE=.\LogDg.H
# End Source File
# Begin Source File

SOURCE=.\MacroCB.H
# End Source File
# Begin Source File

SOURCE=.\MacroDB.H
# End Source File
# Begin Source File

SOURCE=.\MacroDg.H
# End Source File
# Begin Source File

SOURCE=.\MainFrm.H
# End Source File
# Begin Source File

SOURCE=.\MethInfo.H
# End Source File
# Begin Source File

SOURCE=.\MethodDg.H
# End Source File
# Begin Source File

SOURCE=.\MFileWnd.H
# End Source File
# Begin Source File

SOURCE=.\NewAPDg.H
# End Source File
# Begin Source File

SOURCE=.\OutputDialogBar.H
# End Source File
# Begin Source File

SOURCE=.\OutputLogEdit.H
# End Source File
# Begin Source File

SOURCE=.\OutWndVw.H
# End Source File
# Begin Source File

SOURCE=.\PBagDg.H
# End Source File
# Begin Source File

SOURCE=.\PChngPg.H
# End Source File
# Begin Source File

SOURCE=.\PEdReqPg.H
# End Source File
# Begin Source File

SOURCE=.\PropBag.H
# End Source File
# Begin Source File

SOURCE=.\RegCtlDg.H
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\resource.hm
# End Source File
# Begin Source File

SOURCE=.\Script.H
# End Source File
# Begin Source File

SOURCE=.\ScrMngr.H
# End Source File
# Begin Source File

SOURCE=.\ServPg.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabOrdDg.H
# End Source File
# Begin Source File

SOURCE=.\TCDoc.H
# End Source File
# Begin Source File

SOURCE=.\TCItem.H
# End Source File
# Begin Source File

SOURCE=.\TCSplit.H
# End Source File
# Begin Source File

SOURCE=.\TCTrace.H
# End Source File
# Begin Source File

SOURCE=.\TCView.H
# End Source File
# Begin Source File

SOURCE=.\TestCon.H
# End Source File
# Begin Source File

SOURCE=.\TstCon.H
# End Source File
# Begin Source File

SOURCE=.\TypeAttr.H
# End Source File
# Begin Source File

SOURCE=.\VarUtils.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\macro.ico
# End Source File
# Begin Source File

SOURCE=.\res\macrobar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TstCon.ICO
# End Source File
# Begin Source File

SOURCE=.\res\TstCon.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\TstCon.Reg
# End Source File
# End Target
# End Project
