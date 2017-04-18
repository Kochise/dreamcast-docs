# Microsoft Developer Studio Project File - Name="Trace1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=Trace1 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Trace1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trace1.mak" CFG="Trace1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trace1 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "Trace1 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Trace1 - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f Trace.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Trace.exe"
# PROP BASE Bsc_Name "Trace.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f Trace.mak CFG="Trace - Win32 Release""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Trace.dll"
# PROP Bsc_Name "Trace1.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "Trace1 - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f Trace.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Trace.exe"
# PROP BASE Bsc_Name "Trace.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f Trace.mak CFG="Trace - Win32 Debug""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Trace.dll"
# PROP Bsc_Name "Trace1.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "Trace1 - Win32 Release"
# Name "Trace1 - Win32 Debug"

!IF  "$(CFG)" == "Trace1 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trace1 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\Trace.mak
# End Source File
# End Target
# End Project
