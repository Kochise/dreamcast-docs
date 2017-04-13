# Microsoft Developer Studio Project File - Name="crashlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=crashlib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "crashlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "crashlib.mak" CFG="crashlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "crashlib - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "crashlib - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "crashlib - Win32 Release"

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
# PROP Target_File "crashlib.lib"
# PROP Bsc_Name "crashlib.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "crashlib - Win32 Debug"

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
# PROP Target_File "crashlib.lib"
# PROP Bsc_Name "crashlib.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "crashlib - Win32 Release"
# Name "crashlib - Win32 Debug"

!IF  "$(CFG)" == "crashlib - Win32 Release"

!ELSEIF  "$(CFG)" == "crashlib - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\BROWSE.C
# End Source File
# Begin Source File

SOURCE=.\CONTROLS.C
# End Source File
# Begin Source File

SOURCE=.\DEBUG.C
# End Source File
# Begin Source File

SOURCE=.\DRWTSN32.C
# End Source File
# Begin Source File

SOURCE=.\DUMP.C
# End Source File
# Begin Source File

SOURCE=.\ERROR.C
# End Source File
# Begin Source File

SOURCE=.\EVENTLOG.C
# End Source File
# Begin Source File

SOURCE=.\GETTEB.C
# End Source File
# Begin Source File

SOURCE=.\LOG.C
# End Source File
# Begin Source File

SOURCE=.\MODULE.C
# End Source File
# Begin Source File

SOURCE=.\NOTIFY.C
# End Source File
# Begin Source File

SOURCE=.\PROCESS.C
# End Source File
# Begin Source File

SOURCE=.\REGISTRY.C
# End Source File
# Begin Source File

SOURCE=.\SYMBOLS.C
# End Source File
# Begin Source File

SOURCE=.\UI.C
# End Source File
# Begin Source File

SOURCE=.\UTIL.C
# End Source File
# Begin Source File

SOURCE=.\WALK.C
# End Source File
# Begin Source File

SOURCE=.\CONTEXT.C
# End Source File
# Begin Source File

SOURCE=.\DISASM.C
# End Source File
# Begin Source File

SOURCE=.\REGS.C
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\DISASM.H
# End Source File
# Begin Source File

SOURCE=.\REGS.H
# End Source File
# Begin Source File

SOURCE=.\messages.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\DRWATSON.RC
# End Source File
# Begin Source File

SOURCE=.\messages.rc
# End Source File
# Begin Source File

SOURCE=.\DRWATSON.ICO
# End Source File
# End Group 
# End Target
# End Project
