# Microsoft Developer Studio Project File - Name="pplane" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=pplane - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pplane.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pplane.mak" CFG="pplane - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pplane - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "pplane - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "pplane - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "release\"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release\"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "release\pplane.exe"
# PROP Bsc_Name "pplane.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "pplane - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "debug\"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug\"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "debug\pplane.exe"
# PROP Bsc_Name "pplane.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "pplane - Win32 Release"
# Name "pplane - Win32 Debug"

!IF  "$(CFG)" == "pplane - Win32 Release"

!ELSEIF  "$(CFG)" == "pplane - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\D3DUTILS.CPP
# End Source File
# Begin Source File

SOURCE=.\D3DWIN.CPP
# End Source File
# Begin Source File

SOURCE=.\DEBUG.CPP
# End Source File
# Begin Source File

SOURCE=.\DRVMGR.CPP
# End Source File
# Begin Source File

SOURCE=.\GETDXVER.CPP
# End Source File
# Begin Source File

SOURCE=.\PPLANE.CPP
# End Source File
# Begin Source File

SOURCE=.\WINMAIN.CPP
# End Source File
# Begin Source File

SOURCE=.\WINPROC.CPP
# End Source File
# Begin Source File

SOURCE=.\PPLANE.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\COMMON.H
# End Source File
# Begin Source File

SOURCE=.\D3DSCENE.H
# End Source File
# Begin Source File

SOURCE=.\D3DUTILS.H
# End Source File
# Begin Source File

SOURCE=.\D3DWIN.H
# End Source File
# Begin Source File

SOURCE=.\DEBUG.H
# End Source File
# Begin Source File

SOURCE=.\DRVMGR.H
# End Source File
# Begin Source File

SOURCE=.\PPLANE.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\WINMAIN.H
# End Source File
# Begin Source File

SOURCE=.\WINPROC.H
# End Source File
# Begin Source File

SOURCE=.\D3DUTILS.INL
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\PPLANE.RC
# End Source File
# Begin Source File

SOURCE=.\D3D.ICO
# End Source File
# End Group 
# End Target
# End Project
