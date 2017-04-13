# Microsoft Developer Studio Project File - Name="marshal2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=marshal2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "marshal2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "marshal2.mak" CFG="marshal2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "marshal2 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "marshal2 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "marshal2 - Win32 Release"

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
# PROP Target_File "marshal2.dll"
# PROP Bsc_Name "marshal2.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "marshal2 - Win32 Debug"

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
# PROP Target_File "marshal2.dll"
# PROP Bsc_Name "marshal2.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "marshal2 - Win32 Release"
# Name "marshal2 - Win32 Debug"

!IF  "$(CFG)" == "marshal2 - Win32 Release"

!ELSEIF  "$(CFG)" == "marshal2 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\micars_p.c
# End Source File
# Begin Source File

SOURCE=.\dlldata.c
# End Source File
# Begin Source File

SOURCE=.\micars_i.c
# End Source File
# Begin Source File

SOURCE=.\marshal2.cpp
# End Source File
# Begin Source File

SOURCE=.\micars.idl
# End Source File
# Begin Source File

SOURCE=.\marshal2.def
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\micars.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\marshal2.rc
# End Source File
# Begin Source File

SOURCE=.\marshal2.ico
# End Source File
# End Group 
# End Target
# End Project
