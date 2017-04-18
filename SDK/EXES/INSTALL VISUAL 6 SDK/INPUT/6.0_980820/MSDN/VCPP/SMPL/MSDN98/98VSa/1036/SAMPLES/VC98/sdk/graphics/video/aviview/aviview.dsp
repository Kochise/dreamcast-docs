# Microsoft Developer Studio Project File - Name="aviview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=aviview - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "aviview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "aviview.mak" CFG="aviview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "aviview - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "aviview - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "aviview - Win32 Release"

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
# PROP Target_File "aviview.exe"
# PROP Bsc_Name "aviview.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "aviview - Win32 Debug"

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
# PROP Target_File "aviview.exe"
# PROP Bsc_Name "aviview.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "aviview - Win32 Release"
# Name "aviview - Win32 Debug"

!IF  "$(CFG)" == "aviview - Win32 Release"

!ELSEIF  "$(CFG)" == "aviview - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\AUDPLAY.C
# End Source File
# Begin Source File

SOURCE=.\AVIBALL.C
# End Source File
# Begin Source File

SOURCE=.\AVIVIEW.C
# End Source File
# Begin Source File

SOURCE=.\CDIB.C
# End Source File
# Begin Source File

SOURCE=.\GUID.C
# End Source File
# Begin Source File

SOURCE=.\REGOBJS.CPP
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\AUDPLAY.H
# End Source File
# Begin Source File

SOURCE=.\AVIBALL.H
# End Source File
# Begin Source File

SOURCE=.\AVIVIEW.H
# End Source File
# Begin Source File

SOURCE=.\MULDIV32.H
# End Source File
# Begin Source File

SOURCE=.\REGOBJS.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\AVIVIEW.RC
# End Source File
# Begin Source File

SOURCE=.\AVIVIEW.ICO
# End Source File
# End Group 
# End Target
# End Project
