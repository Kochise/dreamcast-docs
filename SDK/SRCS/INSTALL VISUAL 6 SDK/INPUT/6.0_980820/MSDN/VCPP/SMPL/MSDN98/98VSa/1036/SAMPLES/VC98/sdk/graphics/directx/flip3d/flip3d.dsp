# Microsoft Developer Studio Project File - Name="flip3d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=flip3d - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "flip3d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "flip3d.mak" CFG="flip3d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "flip3d - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "flip3d - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "flip3d - Win32 Release"

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
# PROP Target_File "release\flip3d.exe"
# PROP Bsc_Name "flip3d.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "flip3d - Win32 Debug"

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
# PROP Target_File "debug\flip3d.exe"
# PROP Bsc_Name "flip3d.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "flip3d - Win32 Release"
# Name "flip3d - Win32 Debug"

!IF  "$(CFG)" == "flip3d - Win32 Release"

!ELSEIF  "$(CFG)" == "flip3d - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\D3DTEX.CPP
# End Source File
# Begin Source File

SOURCE=.\DUMB3D.CPP
# End Source File
# Begin Source File

SOURCE=.\FLIPCUBE.CPP
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\D3DTEX.H
# End Source File
# Begin Source File

SOURCE=.\DUMB3D.H
# End Source File
# Begin Source File

SOURCE=.\FLIPCUBE.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\FLIPCUBE.RC
# End Source File
# Begin Source File

SOURCE=.\CHECKER.BMP
# End Source File
# Begin Source File

SOURCE=.\WIN95.BMP
# End Source File
# Begin Source File

SOURCE=.\FLIPCUBE.ICO
# End Source File
# End Group 
# End Target
# End Project
