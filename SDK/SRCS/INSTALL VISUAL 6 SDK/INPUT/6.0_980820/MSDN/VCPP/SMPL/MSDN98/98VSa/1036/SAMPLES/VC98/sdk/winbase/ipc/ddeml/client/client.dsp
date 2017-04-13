# Microsoft Developer Studio Project File - Name="client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=client - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client.mak" CFG="client - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "client - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "client - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "client - Win32 Release"

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
# PROP Target_File "client.exe"
# PROP Bsc_Name "client.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

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
# PROP Target_File "client.exe"
# PROP Bsc_Name "client.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "client - Win32 Release"
# Name "client - Win32 Debug"

!IF  "$(CFG)" == "client - Win32 Release"

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\CLINIT.C
# End Source File
# Begin Source File

SOURCE=.\DDE.C
# End Source File
# Begin Source File

SOURCE=.\DDEMLCL.C
# End Source File
# Begin Source File

SOURCE=.\DIALOG.C
# End Source File
# Begin Source File

SOURCE=.\HUGE.C
# End Source File
# Begin Source File

SOURCE=.\INFOCTRL.C
# End Source File
# Begin Source File

SOURCE=.\MEM.C
# End Source File
# Begin Source File

SOURCE=.\TRACK.C
# End Source File
# Begin Source File

SOURCE=.\CLIENT.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\CLIENT.H
# End Source File
# Begin Source File

SOURCE=.\DIALOG.H
# End Source File
# Begin Source File

SOURCE=.\HUGE.H
# End Source File
# Begin Source File

SOURCE=.\INFOCTRL.H
# End Source File
# Begin Source File

SOURCE=.\TRACK.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\CLIENT.RC
# End Source File
# Begin Source File

SOURCE=.\CLIENT.ICO
# End Source File
# Begin Source File

SOURCE=.\CONV.ICO
# End Source File
# Begin Source File

SOURCE=.\LIST.ICO
# End Source File
# End Group 
# End Target
# End Project
