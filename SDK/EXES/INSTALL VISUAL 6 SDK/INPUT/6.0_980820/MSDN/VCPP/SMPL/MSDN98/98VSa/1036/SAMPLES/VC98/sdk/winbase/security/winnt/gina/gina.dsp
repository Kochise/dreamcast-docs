# Microsoft Developer Studio Project File - Name="gina" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=gina - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gina.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gina.mak" CFG="gina - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gina - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "gina - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "gina - Win32 Release"

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
# PROP Target_File "gina.dll"
# PROP Bsc_Name "gina.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "gina - Win32 Debug"

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
# PROP Target_File "gina.dll"
# PROP Bsc_Name "gina.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "gina - Win32 Release"
# Name "gina - Win32 Debug"

!IF  "$(CFG)" == "gina - Win32 Release"

!ELSEIF  "$(CFG)" == "gina - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\DEBUG.C
# End Source File
# Begin Source File

SOURCE=.\GINA.C
# End Source File
# Begin Source File

SOURCE=.\LOGON.C
# End Source File
# Begin Source File

SOURCE=.\OPTIONS.C
# End Source File
# Begin Source File

SOURCE=.\OUT.C
# End Source File
# Begin Source File

SOURCE=.\SHUTDOWN.C
# End Source File
# Begin Source File

SOURCE=.\UTIL.C
# End Source File
# Begin Source File

SOURCE=.\WELCOME.C
# End Source File
# Begin Source File

SOURCE=.\GINA.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\DEBUG.H
# End Source File
# Begin Source File

SOURCE=.\GINA.H
# End Source File
# Begin Source File

SOURCE=.\GINADLG.H
# End Source File
# Begin Source File

SOURCE=.\GLOBALS.H
# End Source File
# Begin Source File

SOURCE=.\PROTOS.H
# End Source File
# Begin Source File

SOURCE=.\RESIDS.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\STRUCTS.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\DIALOGS.RC
# End Source File
# Begin Source File

SOURCE=.\RES.RC
# End Source File
# Begin Source File

SOURCE=.\LOCKED.BMP
# End Source File
# Begin Source File

SOURCE=.\LOCKED.ICO
# End Source File
# Begin Source File

SOURCE=.\NEWUSER.ICO
# End Source File
# Begin Source File

SOURCE=.\SHUTDOWN.ICO
# End Source File
# Begin Source File

SOURCE=.\USER.ICO
# End Source File
# End Group 
# End Target
# End Project
