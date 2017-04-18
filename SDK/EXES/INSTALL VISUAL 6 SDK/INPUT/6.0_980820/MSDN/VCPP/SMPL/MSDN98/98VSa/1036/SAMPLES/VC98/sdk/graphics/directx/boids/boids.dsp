# Microsoft Developer Studio Project File - Name="boids" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=boids - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "boids.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "boids.mak" CFG="boids - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "boids - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "boids - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "boids - Win32 Release"

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
# PROP Target_File "release\boids.exe"
# PROP Bsc_Name "boids.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "boids - Win32 Debug"

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
# PROP Target_File "debug\boids.exe"
# PROP Bsc_Name "boids.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "boids - Win32 Release"
# Name "boids - Win32 Debug"

!IF  "$(CFG)" == "boids - Win32 Release"

!ELSEIF  "$(CFG)" == "boids - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\BOIDS.CPP
# End Source File
# Begin Source File

SOURCE=.\D3DTEX.CPP
# End Source File
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

SOURCE=.\FLOCK.CPP
# End Source File
# Begin Source File

SOURCE=.\GETDXVER.CPP
# End Source File
# Begin Source File

SOURCE=.\WINMAIN.CPP
# End Source File
# Begin Source File

SOURCE=.\WINPROC.CPP
# End Source File
# Begin Source File

SOURCE=.\BOIDS2.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\BOIDS.H
# End Source File
# Begin Source File

SOURCE=.\COMMON.H
# End Source File
# Begin Source File

SOURCE=.\D3DSCENE.H
# End Source File
# Begin Source File

SOURCE=.\D3DTEX.H
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

SOURCE=.\BOIDS2.RC
# End Source File
# Begin Source File

SOURCE=.\DX5.BMP
# End Source File
# Begin Source File

SOURCE=.\D3D.ICO
# End Source File
# End Group 
# End Target
# End Project
