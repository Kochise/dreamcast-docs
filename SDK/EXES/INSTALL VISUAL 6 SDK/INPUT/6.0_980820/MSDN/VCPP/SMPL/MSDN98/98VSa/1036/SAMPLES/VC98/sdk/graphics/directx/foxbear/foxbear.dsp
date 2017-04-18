# Microsoft Developer Studio Project File - Name="foxbear" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=foxbear - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "foxbear.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "foxbear.mak" CFG="foxbear - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "foxbear - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "foxbear - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "foxbear - Win32 Release"

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
# PROP Target_File "release\foxbear.exe"
# PROP Bsc_Name "foxbear.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "foxbear - Win32 Debug"

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
# PROP Target_File "debug\foxbear.exe"
# PROP Bsc_Name "foxbear.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "foxbear - Win32 Release"
# Name "foxbear - Win32 Debug"

!IF  "$(CFG)" == "foxbear - Win32 Release"

!ELSEIF  "$(CFG)" == "foxbear - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\BMP.C
# End Source File
# Begin Source File

SOURCE=.\DDRAW.C
# End Source File
# Begin Source File

SOURCE=.\FBSOUND.C
# End Source File
# Begin Source File

SOURCE=.\FOXBEAR.C
# End Source File
# Begin Source File

SOURCE=.\GAMEPROC.C
# End Source File
# Begin Source File

SOURCE=.\GFX.C
# End Source File
# Begin Source File

SOURCE=.\PLANE.C
# End Source File
# Begin Source File

SOURCE=.\SPRITE.C
# End Source File
# Begin Source File

SOURCE=.\TILE.C
# End Source File
# Begin Source File

SOURCE=.\FOXBEAR.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\FBSOUND.H
# End Source File
# Begin Source File

SOURCE=.\FOXBEAR.H
# End Source File
# Begin Source File

SOURCE=.\GAMEPROC.H
# End Source File
# Begin Source File

SOURCE=.\GFX.H
# End Source File
# Begin Source File

SOURCE=.\PLANE.H
# End Source File
# Begin Source File

SOURCE=.\RCIDS.H
# End Source File
# Begin Source File

SOURCE=.\SPRITE.H
# End Source File
# Begin Source File

SOURCE=.\TILE.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\FOXBEAR.RC
# End Source File
# Begin Source File

SOURCE=.\FOX.ICO
# End Source File
# End Group 
# End Target
# End Project
