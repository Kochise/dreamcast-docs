# Microsoft Developer Studio Project File - Name="smpxp32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=smpxp32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "smpxp32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smpxp32.mak" CFG="smpxp32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "smpxp32 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "smpxp32 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "smpxp32 - Win32 Release"

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
# PROP Target_File "smpxp32.dll"
# PROP Bsc_Name "smpxp32.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "smpxp32 - Win32 Debug"

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
# PROP Target_File "smpxp32.dll"
# PROP Bsc_Name "smpxp32.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "smpxp32 - Win32 Release"
# Name "smpxp32 - Win32 Debug"

!IF  "$(CFG)" == "smpxp32 - Win32 Release"

!ELSEIF  "$(CFG)" == "smpxp32 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\XPBASE.C
# End Source File
# Begin Source File

SOURCE=.\XPDIALOG.C
# End Source File
# Begin Source File

SOURCE=.\XPGUID.C
# End Source File
# Begin Source File

SOURCE=.\XPLOGGER.C
# End Source File
# Begin Source File

SOURCE=.\XPOPTION.C
# End Source File
# Begin Source File

SOURCE=.\XPPCH.C
# End Source File
# Begin Source File

SOURCE=.\XPQUEUE.C
# End Source File
# Begin Source File

SOURCE=.\XPRCVMSG.C
# End Source File
# Begin Source File

SOURCE=.\XPSNDMSG.C
# End Source File
# Begin Source File

SOURCE=.\XPSOF.C
# End Source File
# Begin Source File

SOURCE=.\XPSTATUS.C
# End Source File
# Begin Source File

SOURCE=.\DLL16.DEF
# End Source File
# Begin Source File

SOURCE=.\SMPXP32.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\XPBASE.H
# End Source File
# Begin Source File

SOURCE=.\XPDIALOG.H
# End Source File
# Begin Source File

SOURCE=.\XPLOGGER.H
# End Source File
# Begin Source File

SOURCE=.\XPOPTION.H
# End Source File
# Begin Source File

SOURCE=.\XPPCH.H
# End Source File
# Begin Source File

SOURCE=.\XPQUEUE.H
# End Source File
# Begin Source File

SOURCE=.\XPRESRC.H
# End Source File
# Begin Source File

SOURCE=.\XPSOF.H
# End Source File
# Begin Source File

SOURCE=.\XPSTATUS.H
# End Source File
# Begin Source File

SOURCE=.\XPTXTMSG.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\XPRESRC.RC
# End Source File
# End Group 
# End Target
# End Project
