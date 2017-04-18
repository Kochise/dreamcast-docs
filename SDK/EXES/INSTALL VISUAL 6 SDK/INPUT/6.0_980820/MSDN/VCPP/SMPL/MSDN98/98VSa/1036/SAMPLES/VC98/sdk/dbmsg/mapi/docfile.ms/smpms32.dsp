# Microsoft Developer Studio Project File - Name="smpms32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=smpms32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "smpms32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smpms32.mak" CFG="smpms32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "smpms32 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "smpms32 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "smpms32 - Win32 Release"

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
# PROP Target_File "smpms32.dll"
# PROP Bsc_Name "smpms32.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "smpms32 - Win32 Debug"

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
# PROP Target_File "smpms32.dll"
# PROP Bsc_Name "smpms32.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "smpms32 - Win32 Release"
# Name "smpms32 - Win32 Debug"

!IF  "$(CFG)" == "smpms32 - Win32 Release"

!ELSEIF  "$(CFG)" == "smpms32 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\MSP.C
# End Source File
# Begin Source File

SOURCE=.\MSPATCH.C
# End Source File
# Begin Source File

SOURCE=.\MSPFLD.C
# End Source File
# Begin Source File

SOURCE=.\MSPGLE.C
# End Source File
# Begin Source File

SOURCE=.\MSPGUID.C
# End Source File
# Begin Source File

SOURCE=.\MSPINIT.C
# End Source File
# Begin Source File

SOURCE=.\MSPLOGON.C
# End Source File
# Begin Source File

SOURCE=.\MSPMISC.C
# End Source File
# Begin Source File

SOURCE=.\MSPMS.C
# End Source File
# Begin Source File

SOURCE=.\MSPMSG.C
# End Source File
# Begin Source File

SOURCE=.\MSPNTFY.C
# End Source File
# Begin Source File

SOURCE=.\MSPOBJ.C
# End Source File
# Begin Source File

SOURCE=.\MSPRFS.C
# End Source File
# Begin Source File

SOURCE=.\MSPTBL.C
# End Source File
# Begin Source File

SOURCE=.\DLL16.DEF
# End Source File
# Begin Source File

SOURCE=.\SMPMS32.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\MSP.H
# End Source File
# Begin Source File

SOURCE=.\MSPRC.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\MSP.RC
# End Source File
# End Group 
# End Target
# End Project
