# Microsoft Developer Studio Project File - Name="gizmobar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=gizmobar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gizmobar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gizmobar.mak" CFG="gizmobar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gizmobar - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "gizmobar - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "gizmobar - Win32 Release"

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
# PROP Target_File "gizmobar.dll"
# PROP Bsc_Name "gizmobar.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "gizmobar - Win32 Debug"

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
# PROP Target_File "gizmobar.dll"
# PROP Bsc_Name "gizmobar.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "gizmobar - Win32 Release"
# Name "gizmobar - Win32 Debug"

!IF  "$(CFG)" == "gizmobar - Win32 Release"

!ELSEIF  "$(CFG)" == "gizmobar - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\API.C
# End Source File
# Begin Source File

SOURCE=.\GIZMO.C
# End Source File
# Begin Source File

SOURCE=.\GIZMOBAR.C
# End Source File
# Begin Source File

SOURCE=.\INIT.C
# End Source File
# Begin Source File

SOURCE=.\PAINT.C
# End Source File
# Begin Source File

SOURCE=.\GIZMOBAR.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\GIZMO.H
# End Source File
# Begin Source File

SOURCE=.\GIZMOINT.H
# End Source File
# Begin Source File

SOURCE=.\WIN1632.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\GIZMOBAR.RC
# End Source File
# End Group 
# End Target
# End Project
