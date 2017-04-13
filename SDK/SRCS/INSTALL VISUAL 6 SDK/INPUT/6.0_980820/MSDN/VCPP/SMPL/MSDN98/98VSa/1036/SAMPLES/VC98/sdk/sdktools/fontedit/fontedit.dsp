# Microsoft Developer Studio Project File - Name="fontedit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=fontedit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fontedit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fontedit.mak" CFG="fontedit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fontedit - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "fontedit - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "fontedit - Win32 Release"

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
# PROP Target_File "fontedit.exe"
# PROP Bsc_Name "fontedit.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "fontedit - Win32 Debug"

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
# PROP Target_File "fontedit.exe"
# PROP Bsc_Name "fontedit.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "fontedit - Win32 Release"
# Name "fontedit - Win32 Debug"

!IF  "$(CFG)" == "fontedit - Win32 Release"

!ELSEIF  "$(CFG)" == "fontedit - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\FONTCHAR.C
# End Source File
# Begin Source File

SOURCE=.\FONTCVT.C
# End Source File
# Begin Source File

SOURCE=.\FONTDLG.C
# End Source File
# Begin Source File

SOURCE=.\FONTEDIT.C
# End Source File
# Begin Source File

SOURCE=.\FONTHEAD.C
# End Source File
# Begin Source File

SOURCE=.\FONTLOAD.C
# End Source File
# Begin Source File

SOURCE=.\TYPECVT.C
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\FCNTL.H
# End Source File
# Begin Source File

SOURCE=.\FONTEDIT.H
# End Source File
# Begin Source File

SOURCE=.\TYPECVT.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\FONTEDIT.RC
# End Source File
# Begin Source File

SOURCE=.\FONTEDIT.ICO
# End Source File
# End Group 
# End Target
# End Project
