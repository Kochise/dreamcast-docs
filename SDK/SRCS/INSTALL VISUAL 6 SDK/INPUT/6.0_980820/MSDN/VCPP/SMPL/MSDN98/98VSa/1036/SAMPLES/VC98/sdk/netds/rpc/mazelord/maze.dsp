# Microsoft Developer Studio Project File - Name="maze" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=maze - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "maze.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "maze.mak" CFG="maze - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "maze - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "maze - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "maze - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "maze.exe"
# PROP Bsc_Name "maze.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "maze - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "maze.exe"
# PROP Bsc_Name "maze.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "maze - Win32 Release"
# Name "maze - Win32 Debug"

!IF  "$(CFG)" == "maze - Win32 Release"

!ELSEIF  "$(CFG)" == "maze - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\BITMAP.C
# End Source File
# Begin Source File

SOURCE=.\DRAW.C
# End Source File
# Begin Source File

SOURCE=.\DRONES.C
# End Source File
# Begin Source File

SOURCE=.\INITMAZE.C
# End Source File
# Begin Source File

SOURCE=.\MAZE.C
# End Source File
# Begin Source File

SOURCE=.\MAZEDLG.C
# End Source File
# Begin Source File

SOURCE=.\MAZEWND.C
# End Source File
# Begin Source File

SOURCE=.\NETWORK.C
# End Source File
# Begin Source File

SOURCE=.\READSGRD.C
# End Source File
# Begin Source File

SOURCE=.\SCOREWND.C
# End Source File
# Begin Source File

SOURCE=.\TEXTWND.C
# End Source File
# Begin Source File

SOURCE=.\TOPWND.C
# End Source File
# Begin Source File

SOURCE=.\MAZE.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\CRCTABLE.H
# End Source File
# Begin Source File

SOURCE=.\MAZEDLG.H
# End Source File
# Begin Source File

SOURCE=.\MAZPROTO.H
# End Source File
# Begin Source File

SOURCE=.\NET.H
# End Source File
# Begin Source File

SOURCE=.\WINMAZE.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\GRIDS.RC
# End Source File
# Begin Source File

SOURCE=.\MAZE.RC
# End Source File
# Begin Source File

SOURCE=.\MAZE.ICO
# End Source File
# End Group 
# End Target
# End Project
