# Microsoft Developer Studio Project File - Name="todosvr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=todosvr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "todosvr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "todosvr.mak" CFG="todosvr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "todosvr - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "todosvr - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "todosvr - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "release\"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release\"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "release\todosvr.ocx"
# PROP Bsc_Name "todosvr.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "todosvr - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "debug\"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug\"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "debug\todosvr.ocx"
# PROP Bsc_Name "todosvr.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "todosvr - Win32 Release"
# Name "todosvr - Win32 Debug"

!IF  "$(CFG)" == "todosvr - Win32 Release"

!ELSEIF  "$(CFG)" == "todosvr - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\CDOCOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\DOREG.CPP
# End Source File
# Begin Source File

SOURCE=.\GUIDS.CPP
# End Source File
# Begin Source File

SOURCE=.\IODOC.CPP
# End Source File
# Begin Source File

SOURCE=.\IODOCVW.CPP
# End Source File
# Begin Source File

SOURCE=.\MENU.CPP
# End Source File
# Begin Source File

SOURCE=.\TODOCTL.CPP
# End Source File
# Begin Source File

SOURCE=.\TODOPPG.CPP
# End Source File
# Begin Source File

SOURCE=.\TODOSVR.CPP
# End Source File
# Begin Source File

SOURCE=.\TODOSVR.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\CDOCOBJ.H
# End Source File
# Begin Source File

SOURCE=.\DISPIDS.H
# End Source File
# Begin Source File

SOURCE=.\DWINVERS.H
# End Source File
# Begin Source File

SOURCE=.\GUIDS.H
# End Source File
# Begin Source File

SOURCE=.\LOCALOBJ.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\TODOCTL.H
# End Source File
# Begin Source File

SOURCE=.\TODOPPG.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\TODOSVR.RC
# End Source File
# Begin Source File

SOURCE=.\TODOCTL.BMP
# End Source File
# End Group 
# End Target
# End Project
