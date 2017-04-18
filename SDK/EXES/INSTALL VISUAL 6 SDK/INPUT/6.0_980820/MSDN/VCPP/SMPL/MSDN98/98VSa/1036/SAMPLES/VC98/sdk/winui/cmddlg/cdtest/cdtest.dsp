# Microsoft Developer Studio Project File - Name="cdtest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=cdtest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cdtest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cdtest.mak" CFG="cdtest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cdtest - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "cdtest - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "cdtest - Win32 Release"

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
# PROP Target_File "cdtest.exe"
# PROP Bsc_Name "cdtest.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "cdtest - Win32 Debug"

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
# PROP Target_File "cdtest.exe"
# PROP Bsc_Name "cdtest.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "cdtest - Win32 Release"
# Name "cdtest - Win32 Debug"

!IF  "$(CFG)" == "cdtest - Win32 Release"

!ELSEIF  "$(CFG)" == "cdtest - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\CDTEST.C
# End Source File
# Begin Source File

SOURCE=.\COLORS.C
# End Source File
# Begin Source File

SOURCE=.\FIND.C
# End Source File
# Begin Source File

SOURCE=.\FONT.C
# End Source File
# Begin Source File

SOURCE=.\OPEN.C
# End Source File
# Begin Source File

SOURCE=.\PRINT.C
# End Source File
# Begin Source File

SOURCE=.\REPLACE.C
# End Source File
# Begin Source File

SOURCE=.\SAVE.C
# End Source File
# Begin Source File

SOURCE=.\TITLE.C
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\CDTEST.H
# End Source File
# Begin Source File

SOURCE=.\COLORS.H
# End Source File
# Begin Source File

SOURCE=.\DEVMODE.H
# End Source File
# Begin Source File

SOURCE=.\DEVNAMES.H
# End Source File
# Begin Source File

SOURCE=.\FIND.H
# End Source File
# Begin Source File

SOURCE=.\FONT.H
# End Source File
# Begin Source File

SOURCE=.\LOGFONT.H
# End Source File
# Begin Source File

SOURCE=.\OPEN.H
# End Source File
# Begin Source File

SOURCE=.\PRINT.H
# End Source File
# Begin Source File

SOURCE=.\REPLACE.H
# End Source File
# Begin Source File

SOURCE=.\SAVE.H
# End Source File
# Begin Source File

SOURCE=.\TITLE.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\RES.RC
# End Source File
# Begin Source File

SOURCE=.\CDTEST.ICO
# End Source File
# End Group 
# End Target
# End Project
