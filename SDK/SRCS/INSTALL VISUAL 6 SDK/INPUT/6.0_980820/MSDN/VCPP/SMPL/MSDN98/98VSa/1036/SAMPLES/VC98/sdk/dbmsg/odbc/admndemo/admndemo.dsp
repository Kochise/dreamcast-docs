# Microsoft Developer Studio Project File - Name="admndemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=admndemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "admndemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "admndemo.mak" CFG="admndemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "admndemo - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "admndemo - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "admndemo - Win32 Release"

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
# PROP Target_File "win32\release\admndemo.exe"
# PROP Bsc_Name "admndemo.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "admndemo - Win32 Debug"

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
# PROP Target_File "win32\debug\admndemo.exe"
# PROP Bsc_Name "admndemo.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "admndemo - Win32 Release"
# Name "admndemo - Win32 Debug"

!IF  "$(CFG)" == "admndemo - Win32 Release"

!ELSEIF  "$(CFG)" == "admndemo - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\ADMNDEMO.C
# End Source File
# Begin Source File

SOURCE=.\DIALOGS.C
# End Source File
# Begin Source File

SOURCE=.\ERRCHECK.C
# End Source File
# Begin Source File

SOURCE=.\EXECUTE.C
# End Source File
# Begin Source File

SOURCE=.\INFO.C
# End Source File
# Begin Source File

SOURCE=.\INI.C
# End Source File
# Begin Source File

SOURCE=.\MENU.C
# End Source File
# Begin Source File

SOURCE=.\RESULTS.C
# End Source File
# Begin Source File

SOURCE=.\STANDARD.C
# End Source File
# Begin Source File

SOURCE=.\ADMNDEMO.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\ADMNDEMO.H
# End Source File
# Begin Source File

SOURCE=.\CHILD.H
# End Source File
# Begin Source File

SOURCE=.\DIALOGS.H
# End Source File
# Begin Source File

SOURCE=.\ERRCHECK.H
# End Source File
# Begin Source File

SOURCE=.\EXECUTE.H
# End Source File
# Begin Source File

SOURCE=.\INFO.H
# End Source File
# Begin Source File

SOURCE=.\INI.H
# End Source File
# Begin Source File

SOURCE=.\MENU.H
# End Source File
# Begin Source File

SOURCE=.\RESULTS.H
# End Source File
# Begin Source File

SOURCE=.\STANDARD.H
# End Source File
# Begin Source File

SOURCE=.\STRINGS.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\ADMNDEMO.RC
# End Source File
# Begin Source File

SOURCE=.\ADMNDEMO.ICO
# End Source File
# Begin Source File

SOURCE=.\CONNECT.ICO
# End Source File
# Begin Source File

SOURCE=.\RESULTS.ICO
# End Source File
# End Group 
# End Target
# End Project
