# Microsoft Developer Studio Project File - Name="dllserve" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=dllserve - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dllserve.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dllserve.mak" CFG="dllserve - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dllserve - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "dllserve - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "dllserve - Win32 Release"

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
# PROP Target_File "dllserve.dll"
# PROP Bsc_Name "dllserve.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "dllserve - Win32 Debug"

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
# PROP Target_File "dllserve.dll"
# PROP Bsc_Name "dllserve.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "dllserve - Win32 Release"
# Name "dllserve - Win32 Debug"

!IF  "$(CFG)" == "dllserve - Win32 Release"

!ELSEIF  "$(CFG)" == "dllserve - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\car.cpp
# End Source File
# Begin Source File

SOURCE=.\crucar.cpp
# End Source File
# Begin Source File

SOURCE=.\dllserve.cpp
# End Source File
# Begin Source File

SOURCE=.\factory.cpp
# End Source File
# Begin Source File

SOURCE=.\sample.cpp
# End Source File
# Begin Source File

SOURCE=.\server.cpp
# End Source File
# Begin Source File

SOURCE=.\utilcar.cpp
# End Source File
# Begin Source File

SOURCE=.\dllserve.def
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\car.h
# End Source File
# Begin Source File

SOURCE=.\crucar.h
# End Source File
# Begin Source File

SOURCE=.\dllserve.h
# End Source File
# Begin Source File

SOURCE=.\factory.h
# End Source File
# Begin Source File

SOURCE=.\sample.h
# End Source File
# Begin Source File

SOURCE=.\server.h
# End Source File
# Begin Source File

SOURCE=.\utilcar.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\dllserve.rc
# End Source File
# Begin Source File

SOURCE=.\dllserve.ico
# End Source File
# End Group 
# End Target
# End Project
