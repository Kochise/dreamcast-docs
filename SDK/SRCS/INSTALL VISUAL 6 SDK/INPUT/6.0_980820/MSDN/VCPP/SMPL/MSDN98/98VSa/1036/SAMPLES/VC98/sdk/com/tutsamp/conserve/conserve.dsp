# Microsoft Developer Studio Project File - Name="conserve" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=conserve - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "conserve.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "conserve.mak" CFG="conserve - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "conserve - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "conserve - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "conserve - Win32 Release"

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
# PROP Target_File "conserve.dll"
# PROP Bsc_Name "conserve.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "conserve - Win32 Debug"

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
# PROP Target_File "conserve.dll"
# PROP Bsc_Name "conserve.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "conserve - Win32 Release"
# Name "conserve - Win32 Debug"

!IF  "$(CFG)" == "conserve - Win32 Release"

!ELSEIF  "$(CFG)" == "conserve - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\ball.cpp
# End Source File
# Begin Source File

SOURCE=.\connect.cpp
# End Source File
# Begin Source File

SOURCE=.\conserve.cpp
# End Source File
# Begin Source File

SOURCE=.\factory.cpp
# End Source File
# Begin Source File

SOURCE=.\server.cpp
# End Source File
# Begin Source File

SOURCE=.\conserve.def
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\ball.h
# End Source File
# Begin Source File

SOURCE=.\connect.h
# End Source File
# Begin Source File

SOURCE=.\conserve.h
# End Source File
# Begin Source File

SOURCE=.\factory.h
# End Source File
# Begin Source File

SOURCE=.\server.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\conserve.rc
# End Source File
# Begin Source File

SOURCE=.\conserve.ico
# End Source File
# End Group 
# End Target
# End Project
