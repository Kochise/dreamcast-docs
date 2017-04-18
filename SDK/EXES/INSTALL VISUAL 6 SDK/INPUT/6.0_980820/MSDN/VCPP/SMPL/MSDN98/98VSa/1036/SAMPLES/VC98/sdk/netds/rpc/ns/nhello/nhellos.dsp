# Microsoft Developer Studio Project File - Name="nhellos" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=nhellos - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nhellos.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nhellos.mak" CFG="nhellos - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nhellos - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "nhellos - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "nhellos - Win32 Release"

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
# PROP Target_File "nhellos.exe"
# PROP Bsc_Name "nhellos.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "nhellos - Win32 Debug"

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
# PROP Target_File "nhellos.exe"
# PROP Bsc_Name "nhellos.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "nhellos - Win32 Release"
# Name "nhellos - Win32 Debug"

!IF  "$(CFG)" == "nhellos - Win32 Release"

!ELSEIF  "$(CFG)" == "nhellos - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\NHELLOC.C
# End Source File
# Begin Source File

SOURCE=.\NHELLOP.C
# End Source File
# Begin Source File

SOURCE=.\NHELLOS.C
# End Source File
# Begin Source File

SOURCE=.\NSSERV.C
# End Source File
# Begin Source File

SOURCE=.\SERVICE.C
# End Source File
# Begin Source File

SOURCE=.\nhello_c.c
# End Source File
# Begin Source File

SOURCE=.\nhello_s.c
# End Source File
# Begin Source File

SOURCE=.\NHELLO.IDL
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\SERVICE.H
# End Source File
# Begin Source File

SOURCE=.\nhello.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# End Group 
# End Target
# End Project
