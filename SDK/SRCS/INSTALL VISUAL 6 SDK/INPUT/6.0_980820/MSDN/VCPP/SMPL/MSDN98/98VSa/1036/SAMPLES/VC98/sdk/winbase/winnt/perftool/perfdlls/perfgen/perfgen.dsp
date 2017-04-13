# Microsoft Developer Studio Project File - Name="perfgen" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=perfgen - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "perfgen.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "perfgen.mak" CFG="perfgen - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "perfgen - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "perfgen - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "perfgen - Win32 Release"

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
# PROP Target_File "perfgen.dll"
# PROP Bsc_Name "perfgen.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "perfgen - Win32 Debug"

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
# PROP Target_File "perfgen.dll"
# PROP Bsc_Name "perfgen.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "perfgen - Win32 Release"
# Name "perfgen - Win32 Debug"

!IF  "$(CFG)" == "perfgen - Win32 Release"

!ELSEIF  "$(CFG)" == "perfgen - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\DATAGEN.C
# End Source File
# Begin Source File

SOURCE=.\PERFGEN.C
# End Source File
# Begin Source File

SOURCE=.\PERFUTIL.C
# End Source File
# Begin Source File

SOURCE=.\PERFGEN.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\DATAGEN.H
# End Source File
# Begin Source File

SOURCE=.\GENCTRNM.H
# End Source File
# Begin Source File

SOURCE=.\PERFMSG.H
# End Source File
# Begin Source File

SOURCE=.\PERFUTIL.H
# End Source File
# Begin Source File

SOURCE=.\genctrs.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\PERFGEN.RC
# End Source File
# Begin Source File

SOURCE=.\genctrs.rc
# End Source File
# End Group 
# End Target
# End Project
