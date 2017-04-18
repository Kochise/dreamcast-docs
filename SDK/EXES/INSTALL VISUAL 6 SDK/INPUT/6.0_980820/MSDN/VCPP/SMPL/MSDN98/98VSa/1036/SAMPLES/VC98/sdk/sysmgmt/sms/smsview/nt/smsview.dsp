# Microsoft Developer Studio Project File - Name="smsview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=smsview - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "smsview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smsview.mak" CFG="smsview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "smsview - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "smsview - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "smsview - Win32 Release"

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
# PROP Target_File "win32\release\smsview.exe"
# PROP Bsc_Name "smsview.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "smsview - Win32 Debug"

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
# PROP Target_File "win32\debug\smsview.exe"
# PROP Bsc_Name "smsview.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "smsview - Win32 Release"
# Name "smsview - Win32 Debug"

!IF  "$(CFG)" == "smsview - Win32 Release"

!ELSEIF  "$(CFG)" == "smsview - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\SmsView.c
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SmsView.h
# End Source File
# Begin Source File

SOURCE=.\SmsViews.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\SmsView.Rc
# End Source File
# Begin Source File

SOURCE=.\3dCheck.Bmp
# End Source File
# Begin Source File

SOURCE=.\SmsView.Ico
# End Source File
# End Group 
# End Target
# End Project
