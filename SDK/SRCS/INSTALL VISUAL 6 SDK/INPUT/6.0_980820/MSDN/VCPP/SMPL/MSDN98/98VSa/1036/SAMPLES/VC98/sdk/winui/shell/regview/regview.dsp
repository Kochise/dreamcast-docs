# Microsoft Developer Studio Project File - Name="RegView" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RegView - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RegView.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RegView.mak" CFG="RegView - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RegView - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegView - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RegView - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Special Build Tool
OutDir=.\Release
SOURCE=$(InputPath)
PostBuild_Cmds=regsvr32.exe /s /c $(OUTDIR)\RegView.dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "RegView - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Debug
SOURCE=$(InputPath)
PostBuild_Cmds=regsvr32.exe /s /c $(OUTDIR)\RegView.dll
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "RegView - Win32 Release"
# Name "RegView - Win32 Debug"
# Begin Source File

SOURCE=.\binary.ico
# End Source File
# Begin Source File

SOURCE=.\ClsFact.cpp
# End Source File
# Begin Source File

SOURCE=.\ClsFact.h
# End Source File
# Begin Source File

SOURCE=.\DockWndw.cpp
# End Source File
# Begin Source File

SOURCE=.\DockWndw.h
# End Source File
# Begin Source File

SOURCE=.\EnumIDL.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumIDL.h
# End Source File
# Begin Source File

SOURCE=.\ExtrIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtrIcon.h
# End Source File
# Begin Source File

SOURCE=.\folder.ico
# End Source File
# Begin Source File

SOURCE=.\folderop.ico
# End Source File
# Begin Source File

SOURCE=.\Guid.h
# End Source File
# Begin Source File

SOURCE=.\InfoTip.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoTip.h
# End Source File
# Begin Source File

SOURCE=.\PidlMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\PidlMgr.h
# End Source File
# Begin Source File

SOURCE=.\RegView.cpp
# End Source File
# Begin Source File

SOURCE=.\RegView.def
# End Source File
# Begin Source File

SOURCE=.\RegView.ico
# End Source File
# Begin Source File

SOURCE=.\RegView.rc

!IF  "$(CFG)" == "RegView - Win32 Release"

!ELSEIF  "$(CFG)" == "RegView - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ShlFldr.cpp
# End Source File
# Begin Source File

SOURCE=.\ShlFldr.h
# End Source File
# Begin Source File

SOURCE=.\ShlView.cpp
# End Source File
# Begin Source File

SOURCE=.\ShlView.h
# End Source File
# Begin Source File

SOURCE=.\string.ico
# End Source File
# Begin Source File

SOURCE=.\Tools.h
# End Source File
# Begin Source File

SOURCE=.\Utility.cpp
# End Source File
# Begin Source File

SOURCE=.\Utility.h
# End Source File
# End Target
# End Project
