# Microsoft Developer Studio Project File - Name="duel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=duel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "duel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "duel.mak" CFG="duel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "duel - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "duel - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "duel - Win32 Release"

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
# PROP Target_File "release\duel.exe"
# PROP Bsc_Name "duel.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "duel - Win32 Debug"

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
# PROP Target_File "debug\duel.exe"
# PROP Bsc_Name "duel.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "duel - Win32 Release"
# Name "duel - Win32 Debug"

!IF  "$(CFG)" == "duel - Win32 Release"

!ELSEIF  "$(CFG)" == "duel - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\COMM.C
# End Source File
# Begin Source File

SOURCE=.\DS3DUTIL.C
# End Source File
# Begin Source File

SOURCE=.\DUEL.C
# End Source File
# Begin Source File

SOURCE=.\GAMEPROC.C
# End Source File
# Begin Source File

SOURCE=.\GFX.C
# End Source File
# Begin Source File

SOURCE=.\INPUT.C
# End Source File
# Begin Source File

SOURCE=.\LOBBY.C
# End Source File
# Begin Source File

SOURCE=.\SFX.C
# End Source File
# Begin Source File

SOURCE=.\UTIL.C
# End Source File
# Begin Source File

SOURCE=.\WIZARD.C
# End Source File
# Begin Source File

SOURCE=.\DDUTIL.CPP
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\COMM.H
# End Source File
# Begin Source File

SOURCE=.\DDUTIL.H
# End Source File
# Begin Source File

SOURCE=.\DS3DUTIL.H
# End Source File
# Begin Source File

SOURCE=.\DUEL.H
# End Source File
# Begin Source File

SOURCE=.\GAMEPROC.H
# End Source File
# Begin Source File

SOURCE=.\GFX.H
# End Source File
# Begin Source File

SOURCE=.\INPUT.H
# End Source File
# Begin Source File

SOURCE=.\LOBBY.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\SFX.H
# End Source File
# Begin Source File

SOURCE=.\UTIL.H
# End Source File
# Begin Source File

SOURCE=.\WIZARD.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\DUEL.RC
# End Source File
# Begin Source File

SOURCE=.\CSESSION.BMP
# End Source File
# Begin Source File

SOURCE=.\DUEL.BMP
# End Source File
# Begin Source File

SOURCE=.\OSESSION.BMP
# End Source File
# Begin Source File

SOURCE=.\PLAYER.BMP
# End Source File
# Begin Source File

SOURCE=.\SPLASH.BMP
# End Source File
# Begin Source File

SOURCE=.\DUEL.ICO
# End Source File
# End Group 
# End Target
# End Project
