# Microsoft Developer Studio Project File - Name="SmbSmp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=SmbSmp - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SmbSmp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SmbSmp.mak" CFG="SmbSmp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SmbSmp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\SmbSmp\Release"
# PROP BASE Intermediate_Dir ".\SmbSmp\Release"
# PROP BASE Target_Dir ".\SmbSmp"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\SmbSmp\Release"
# PROP Intermediate_Dir ".\SmbSmp\Release"
# PROP Target_Dir ".\SmbSmp"
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\SmbSmp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\SmbSmp\Debug"
# PROP BASE Intermediate_Dir ".\SmbSmp\Debug"
# PROP BASE Target_Dir ".\SmbSmp"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\SmbSmp\Debug"
# PROP Intermediate_Dir ".\SmbSmp\Debug"
# PROP Target_Dir ".\SmbSmp"
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".\SmbSmp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\SmbSmp\AlphaRel"
# PROP BASE Intermediate_Dir ".\SmbSmp\AlphaRel"
# PROP BASE Target_Dir ".\SmbSmp"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\SmbSmp\AlphaRel"
# PROP Intermediate_Dir ".\SmbSmp\AlphaRel"
# PROP Target_Dir ".\SmbSmp"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /alpha
CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /YX /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /I ".\SmbSmp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /dll /machine:ALPHA

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\SmbSmp\AlphaDbg"
# PROP BASE Intermediate_Dir ".\SmbSmp\AlphaDbg"
# PROP BASE Target_Dir ".\SmbSmp"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\SmbSmp\AlphaDbg"
# PROP Intermediate_Dir ".\SmbSmp\AlphaDbg"
# PROP Target_Dir ".\SmbSmp"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /alpha
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /YX /MDd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I ".\SmbSmp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /YX /FD /MDd /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:ALPHA

!ENDIF 

# Begin Target

# Name "SmbSmp - Win32 Release"
# Name "SmbSmp - Win32 Debug"
# Name "SmbSmp - Win32 (ALPHA) Release"
# Name "SmbSmp - Win32 (ALPHA) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\SmbSmp\SmbSmp.c

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

NODEP_CPP_MYROO=\
	"{$(INCLUDE)}\clusapi.h"\
	"{$(INCLUDE)}\resapi.h"\
	

NODEP_CPP_MYROO=\
	"{$(INCLUDE)}\clusapi.h"\
	"{$(INCLUDE)}\resapi.h"\
	
!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

NODEP_CPP_MYROO=\
	"{$(INCLUDE)}\clusapi.h"\
	"{$(INCLUDE)}\resapi.h"\
	

NODEP_CPP_MYROO=\
	"{$(INCLUDE)}\clusapi.h"\
	"{$(INCLUDE)}\resapi.h"\
	
!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

NODEP_CPP_MYROO=\
	"{$(INCLUDE)}\clusapi.h"\
	"{$(INCLUDE)}\resapi.h"\
	

NODEP_CPP_MYROO=\
	"{$(INCLUDE)}\clusapi.h"\
	"{$(INCLUDE)}\resapi.h"\
	
!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

NODEP_CPP_MYROO=\
	"{$(INCLUDE)}\clusapi.h"\
	"{$(INCLUDE)}\resapi.h"\
	

NODEP_CPP_MYROO=\
	"{$(INCLUDE)}\clusapi.h"\
	"{$(INCLUDE)}\resapi.h"\
	
!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SmbSmp\SmbSmp.def
# End Source File
# Begin Source File

SOURCE=.\SmbSmp\SmbSmp.rc
# ADD BASE RSC /l 0x409 /i "SmbSmp"
# ADD RSC /l 0x409 /i ".\SmbSmp" /i "SmbSmp"
# End Source File
# Begin Source File

SOURCE=.\SmbSmp\ReadMe.txt
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
