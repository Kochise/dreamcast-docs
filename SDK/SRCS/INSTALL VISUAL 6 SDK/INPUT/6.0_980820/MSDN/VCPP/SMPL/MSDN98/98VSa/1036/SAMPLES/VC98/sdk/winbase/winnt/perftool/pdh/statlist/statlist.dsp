# Microsoft Developer Studio Project File - Name="statlist" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=statlist - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "statlist.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "statlist.mak" CFG="statlist - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "statlist - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "statlist - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "statlist - Win32 Release"

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
# PROP Target_File "statlist.exe"
# PROP Bsc_Name "statlist.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "statlist - Win32 Debug"

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
# PROP Target_File "statlist.exe"
# PROP Bsc_Name "statlist.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "statlist - Win32 Release"
# Name "statlist - Win32 Debug"

!IF  "$(CFG)" == "statlist - Win32 Release"

!ELSEIF  "$(CFG)" == "statlist - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\ABOUTDLG.C
# End Source File
# Begin Source File

SOURCE=.\MAINWND.C
# End Source File
# Begin Source File

SOURCE=.\STATLIST.C
# End Source File
# Begin Source File

SOURCE=.\WINUTILS.C
# End Source File
# Begin Source File

SOURCE=.\STATLIST.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\ABOUTDLG.H
# End Source File
# Begin Source File

SOURCE=.\MAINWND.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\STATLIST.H
# End Source File
# Begin Source File

SOURCE=.\WINUTILS.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\STATLIST.RC
# End Source File
# Begin Source File

SOURCE=.\HELP.BMP
# End Source File
# Begin Source File

SOURCE=.\STATLIST.BMP
# End Source File
# Begin Source File

SOURCE=.\SMALL.ICO
# End Source File
# Begin Source File

SOURCE=.\STATLIST.ICO
# End Source File
# End Group 
# End Target
# End Project
