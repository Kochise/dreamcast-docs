# Microsoft Developer Studio Project File - Name="icmview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=icmview - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "icmview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "icmview.mak" CFG="icmview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "icmview - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "icmview - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "icmview - Win32 Release"

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
# PROP Target_File "icmview.exe"
# PROP Bsc_Name "icmview.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "icmview - Win32 Debug"

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
# PROP Target_File "icmview.exe"
# PROP Bsc_Name "icmview.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "icmview - Win32 Release"
# Name "icmview - Win32 Debug"

!IF  "$(CFG)" == "icmview - Win32 Release"

!ELSEIF  "$(CFG)" == "icmview - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\APPINIT.C
# End Source File
# Begin Source File

SOURCE=.\CHILD.C
# End Source File
# Begin Source File

SOURCE=.\DEBUG.C
# End Source File
# Begin Source File

SOURCE=.\DIALOGS.C
# End Source File
# Begin Source File

SOURCE=.\DIBINFO.C
# End Source File
# Begin Source File

SOURCE=.\DIBS.C
# End Source File
# Begin Source File

SOURCE=.\ICMVIEW.C
# End Source File
# Begin Source File

SOURCE=.\PRINT.C
# End Source File
# Begin Source File

SOURCE=.\REGUTIL.C
# End Source File
# Begin Source File

SOURCE=.\ICMVIEW.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\APPINIT.H
# End Source File
# Begin Source File

SOURCE=.\CDERR.H
# End Source File
# Begin Source File

SOURCE=.\CHILD.H
# End Source File
# Begin Source File

SOURCE=.\DEBUG.H
# End Source File
# Begin Source File

SOURCE=.\DIALOGS.H
# End Source File
# Begin Source File

SOURCE=.\DIBINFO.H
# End Source File
# Begin Source File

SOURCE=.\DIBS.H
# End Source File
# Begin Source File

SOURCE=.\ICMVIEW.H
# End Source File
# Begin Source File

SOURCE=.\PRINT.H
# End Source File
# Begin Source File

SOURCE=.\REGUTIL.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\ICMVIEW.RC
# End Source File
# Begin Source File

SOURCE=.\ICMVIEW.ICO
# End Source File
# Begin Source File

SOURCE=.\SMALL.ICO
# End Source File
# End Group 
# End Target
# End Project
