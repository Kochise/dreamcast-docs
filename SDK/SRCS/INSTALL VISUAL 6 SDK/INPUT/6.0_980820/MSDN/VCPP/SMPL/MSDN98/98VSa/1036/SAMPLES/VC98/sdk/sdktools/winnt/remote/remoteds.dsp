# Microsoft Developer Studio Project File - Name="remoteds" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=remoteds - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "remoteds.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "remoteds.mak" CFG="remoteds - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "remoteds - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "remoteds - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "remoteds - Win32 Release"

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
# PROP Target_File "remoteds.exe"
# PROP Bsc_Name "remoteds.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "remoteds - Win32 Debug"

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
# PROP Target_File "remoteds.exe"
# PROP Bsc_Name "remoteds.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "remoteds - Win32 Release"
# Name "remoteds - Win32 Debug"

!IF  "$(CFG)" == "remoteds - Win32 Release"

!ELSEIF  "$(CFG)" == "remoteds - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\CLIENT.C
# End Source File
# Begin Source File

SOURCE=.\PipeEx.c
# End Source File
# Begin Source File

SOURCE=.\rdsrelay.c
# End Source File
# Begin Source File

SOURCE=.\REMOTE.C
# End Source File
# Begin Source File

SOURCE=.\RemoteDS.c
# End Source File
# Begin Source File

SOURCE=.\SERVER.C
# End Source File
# Begin Source File

SOURCE=.\SrvAd.c
# End Source File
# Begin Source File

SOURCE=.\SrvChild.c
# End Source File
# Begin Source File

SOURCE=.\SrvCtos.c
# End Source File
# Begin Source File

SOURCE=.\SrvHShak.c
# End Source File
# Begin Source File

SOURCE=.\SrvList.c
# End Source File
# Begin Source File

SOURCE=.\SrvMain.c
# End Source File
# Begin Source File

SOURCE=.\SrvQuery.c
# End Source File
# Begin Source File

SOURCE=.\SrvStoc.c
# End Source File
# Begin Source File

SOURCE=.\SrvUtil.c
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\REMOTE.H
# End Source File
# Begin Source File

SOURCE=.\Server.h
# End Source File
# Begin Source File

SOURCE=.\SrvList.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\rdsrelay.rc
# End Source File
# Begin Source File

SOURCE=.\Remote.Rc
# End Source File
# Begin Source File

SOURCE=.\RemoteDS.Rc
# End Source File
# Begin Source File

SOURCE=.\Remote.Ico
# End Source File
# End Group 
# End Target
# End Project
