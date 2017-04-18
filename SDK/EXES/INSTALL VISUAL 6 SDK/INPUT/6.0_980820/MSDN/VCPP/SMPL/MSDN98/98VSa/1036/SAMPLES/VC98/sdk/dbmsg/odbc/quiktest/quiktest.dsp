# Microsoft Developer Studio Project File - Name="quiktest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=quiktest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "quiktest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "quiktest.mak" CFG="quiktest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "quiktest - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "quiktest - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "quiktest - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "win32\release\"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "win32\release\"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "win32\release\quiktest.dll"
# PROP Bsc_Name "quiktest.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "quiktest - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "win32\debug\"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "win32\debug\"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "win32\debug\quiktest.dll"
# PROP Bsc_Name "quiktest.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "quiktest - Win32 Release"
# Name "quiktest - Win32 Debug"

!IF  "$(CFG)" == "quiktest - Win32 Release"

!ELSEIF  "$(CFG)" == "quiktest - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\CUSTOM.C
# End Source File
# Begin Source File

SOURCE=.\DLLSTUB.C
# End Source File
# Begin Source File

SOURCE=.\QUIKTEST.C
# End Source File
# Begin Source File

SOURCE=.\QUIKTEST.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\AUTOTEST.H
# End Source File
# Begin Source File

SOURCE=.\CUSTOM.H
# End Source File
# Begin Source File

SOURCE=.\QUIKTEST.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\CUSTOM.RC
# End Source File
# Begin Source File

SOURCE=.\QUIKTEST.RC
# End Source File
# End Group 
# End Target
# End Project
