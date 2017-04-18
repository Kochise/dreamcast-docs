# Microsoft Developer Studio Project File - Name="console" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=console - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "console.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "console.mak" CFG="console - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "console - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "console - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "console - Win32 Release"

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
# PROP Target_File "console.exe"
# PROP Bsc_Name "console.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "console - Win32 Debug"

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
# PROP Target_File "console.exe"
# PROP Bsc_Name "console.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "console - Win32 Release"
# Name "console - Win32 Debug"

!IF  "$(CFG)" == "console - Win32 Release"

!ELSEIF  "$(CFG)" == "console - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\ALOCFREE.C
# End Source File
# Begin Source File

SOURCE=.\CODEPAGE.C
# End Source File
# Begin Source File

SOURCE=.\CONINFO.C
# End Source File
# Begin Source File

SOURCE=.\CONMODE.C
# End Source File
# Begin Source File

SOURCE=.\CONSOLE.C
# End Source File
# Begin Source File

SOURCE=.\CONTITLE.C
# End Source File
# Begin Source File

SOURCE=.\CREATE.C
# End Source File
# Begin Source File

SOURCE=.\CURSOR.C
# End Source File
# Begin Source File

SOURCE=.\FILLATT.C
# End Source File
# Begin Source File

SOURCE=.\FILLCHAR.C
# End Source File
# Begin Source File

SOURCE=.\FLUSH.C
# End Source File
# Begin Source File

SOURCE=.\GETLRGST.C
# End Source File
# Begin Source File

SOURCE=.\GETNUMEV.C
# End Source File
# Begin Source File

SOURCE=.\HANDLER.C
# End Source File
# Begin Source File

SOURCE=.\NUMBUT.C
# End Source File
# Begin Source File

SOURCE=.\READCHAR.C
# End Source File
# Begin Source File

SOURCE=.\READOUT.C
# End Source File
# Begin Source File

SOURCE=.\SCROLL.C
# End Source File
# Begin Source File

SOURCE=.\SIZE.C
# End Source File
# Begin Source File

SOURCE=.\WRITEIN.C
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\CONSOLE.H
# End Source File
# Begin Source File

SOURCE=.\SIZE.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\CONSOLE.RC
# End Source File
# Begin Source File

SOURCE=.\CONSOLE.ICO
# End Source File
# End Group 
# End Target
# End Project
