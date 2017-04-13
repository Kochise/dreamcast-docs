# Microsoft Developer Studio Project File - Name="iviewers" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=iviewers - Win32 DLL Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "iviewers.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "iviewers.mak" CFG="iviewers - Win32 DLL Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "iviewers - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "iviewers - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "iviewers - Win32 DLL Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Win32_D0"
# PROP BASE Intermediate_Dir ".\Win32_D0"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\release"
# PROP Intermediate_Dir ".\dllrel"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MT /W4 /WX /GX /O2 /D "NDEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /FR /Yu"STDAFX.H" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /map /debug /machine:I386
# SUBTRACT LINK32 /verbose /pdb:none

!ELSEIF  "$(CFG)" == "iviewers - Win32 DLL Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Win32_D0"
# PROP BASE Intermediate_Dir ".\Win32_D0"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\debug"
# PROP Intermediate_Dir ".\dlldebug"
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MTd /W4 /WX /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_USRDLL" /D "_MBCS" /Yu"STDAFX.H" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386
# SUBTRACT LINK32 /profile
# Begin Special Build Tool
TargetDir=\rtl\mfct\vc98\samples\mfc\ole\oleview\debug
SOURCE="$(InputPath)"
PostBuild_Desc=copying iviewers.dll to system directory
PostBuild_Cmds=copy $(TargetDir)\iviewers.dll %windir%\iviewers.dll
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "iviewers - Win32 DLL Release"
# Name "iviewers - Win32 DLL Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\dataobj.cpp
# End Source File
# Begin Source File

SOURCE=.\dispatch.cpp
# End Source File
# Begin Source File

SOURCE=.\guid.cpp
# End Source File
# Begin Source File

SOURCE=.\iadvsink.cpp
# End Source File
# Begin Source File

SOURCE=.\idataobj.cpp
# End Source File
# Begin Source File

SOURCE=.\iviewer.cpp
# End Source File
# Begin Source File

SOURCE=.\iviewers.cpp
# End Source File
# Begin Source File

SOURCE=.\iviewers.def
# End Source File
# Begin Source File

SOURCE=.\iviewers.rc
# End Source File
# Begin Source File

SOURCE=.\shadow.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"STDAFX.H"
# End Source File
# Begin Source File

SOURCE=.\tlblist.cpp
# End Source File
# Begin Source File

SOURCE=.\tlbodl.cpp
# End Source File
# Begin Source File

SOURCE=.\tlbtree.cpp
# End Source File
# Begin Source File

SOURCE=.\tree.cpp
# End Source File
# Begin Source File

SOURCE=.\typelib.cpp
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\dataobj.h
# End Source File
# Begin Source File

SOURCE=.\dispatch.h
# End Source File
# Begin Source File

SOURCE=.\iadvsink.h
# End Source File
# Begin Source File

SOURCE=.\idataobj.h
# End Source File
# Begin Source File

SOURCE=.\iview.h
# End Source File
# Begin Source File

SOURCE=.\iviewer.h
# End Source File
# Begin Source File

SOURCE=.\iviewers.h
# End Source File
# Begin Source File

SOURCE=.\shadow.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\tlblist.h
# End Source File
# Begin Source File

SOURCE=.\tlbodl.h
# End Source File
# Begin Source File

SOURCE=.\tlbtree.h
# End Source File
# Begin Source File

SOURCE=.\tree.h
# End Source File
# Begin Source File

SOURCE=.\typelib.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\idr_type.ico
# End Source File
# Begin Source File

SOURCE=.\res\imagelis.bmp
# End Source File
# Begin Source File

SOURCE=.\res\iviewers.rc2
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
