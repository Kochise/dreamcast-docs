# Microsoft Developer Studio Project File - Name="D3DKnot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Application" 0x8601

CFG=D3DKnot - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "D3DKnot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "D3DKnot.mak" CFG="D3DKnot - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "D3DKnot - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "D3DKnot - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "H/PC Ver. 2.00"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "D3DKnot - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH4Rel"
# PROP Intermediate_Dir "WCESH4Rel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY
# ADD BASE CPP /nologo /Qsh4 /MC /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /Qs /c
# ADD CPP /nologo /Qsh4 /MC /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "DRAGON" /YX /Qs /Qfast /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /machine:SH4 /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 coredll.lib corelibc.lib ddraw.lib dinput.lib dxguid.lib floatmath.lib strig.lib shintr.lib /nologo /machine:SH4 /nodefaultlib /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /map
# Begin Special Build Tool
TargetPath=.\WCESH4Rel\D3DKnot.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Copying executable to the release directory.
PostBuild_Cmds=dccopy $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "D3DKnot - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH4Dbg"
# PROP Intermediate_Dir "WCESH4Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY
# ADD BASE CPP /nologo /Qsh4 /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /Qs /c
# ADD CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "DRAGON" /YX /Qsh4r7 /Qs -Qsh4r7 -Qs /Qfast /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /debug /machine:SH4 /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 coredll.lib corelibc.lib ddraw.lib dinput.lib dxguid.lib floatmath.lib strig.lib shintr.lib /nologo /incremental:no /debug /machine:SH4 /nodefaultlib /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\WCESH4Dbg\D3DKnot.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Copying executable to the release directory.
PostBuild_Cmds=dccopy $(TargetPath)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "D3DKnot - Win32 (WCE SH4) Release"
# Name "D3DKnot - Win32 (WCE SH4) Debug"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\D3DKnot.c
DEP_CPP_D3DKN=\
	".\D3DKnot.h"\
	".\D3DShell.h"\
	".\D3DTools.h"\
	
# End Source File
# Begin Source File

SOURCE=.\D3DKnot.rc
# End Source File
# End Group
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\D3DTools.h
# End Source File
# Begin Source File

SOURCE=.\D3DTools.lib
# End Source File
# End Group
# Begin Group "Shell"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\D3DShell.c
DEP_CPP_D3DSH=\
	".\D3DShell.h"\
	".\DDError.h"\
	
# End Source File
# Begin Source File

SOURCE=.\DDError.c
# End Source File
# End Group
# End Target
# End Project
