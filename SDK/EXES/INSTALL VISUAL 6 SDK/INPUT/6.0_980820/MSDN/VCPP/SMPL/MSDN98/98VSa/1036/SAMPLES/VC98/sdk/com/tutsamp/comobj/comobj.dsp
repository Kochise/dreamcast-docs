# Microsoft Developer Studio Project File - Name="comobj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=comobj - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "comobj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "comobj.mak" CFG="comobj - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "comobj - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "comobj - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "comobj - Win32 Release"

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
# PROP Target_File "comobj.dll"
# PROP Bsc_Name "comobj.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "comobj - Win32 Debug"

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
# PROP Target_File "comobj.dll"
# PROP Bsc_Name "comobj.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "comobj - Win32 Release"
# Name "comobj - Win32 Debug"

!IF  "$(CFG)" == "comobj - Win32 Release"

!ELSEIF  "$(CFG)" == "comobj - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\car.cpp
# End Source File
# Begin Source File

SOURCE=.\comobj.cpp
# End Source File
# Begin Source File

SOURCE=.\crucar.cpp
# End Source File
# Begin Source File

SOURCE=.\utilcar.cpp
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\car.h
# End Source File
# Begin Source File

SOURCE=.\comobj.h
# End Source File
# Begin Source File

SOURCE=.\comobji.h
# End Source File
# Begin Source File

SOURCE=.\crucar.h
# End Source File
# Begin Source File

SOURCE=.\utilcar.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\comobj.rc
# End Source File
# Begin Source File

SOURCE=.\comobj.ico
# End Source File
# End Group 
# End Target
# End Project
