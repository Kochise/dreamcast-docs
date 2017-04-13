# Microsoft Developer Studio Project File - Name="dsstream" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=dsstream - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dsstream.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dsstream.mak" CFG="dsstream - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dsstream - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "dsstream - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "dsstream - Win32 Release"

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
# PROP Target_File "release\dsstream.exe"
# PROP Bsc_Name "dsstream.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "dsstream - Win32 Debug"

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
# PROP Target_File "debug\dsstream.exe"
# PROP Bsc_Name "dsstream.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "dsstream - Win32 Release"
# Name "dsstream - Win32 Debug"

!IF  "$(CFG)" == "dsstream - Win32 Release"

!ELSEIF  "$(CFG)" == "dsstream - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\DEBUG.C
# End Source File
# Begin Source File

SOURCE=.\DSSTREAM.C
# End Source File
# Begin Source File

SOURCE=.\DSTRENUM.C
# End Source File
# Begin Source File

SOURCE=.\DSTRWAVE.C
# End Source File
# Begin Source File

SOURCE=.\NOTIFY.C
# End Source File
# Begin Source File

SOURCE=.\WASSERT.C
# End Source File
# Begin Source File

SOURCE=.\DSSTREAM.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\DEBUG.H
# End Source File
# Begin Source File

SOURCE=.\DSSTREAM.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\WASSERT.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\DSSTREAM.RC
# End Source File
# Begin Source File

SOURCE=.\ICON2.ICO
# End Source File
# Begin Source File

SOURCE=.\ICON3.ICO
# End Source File
# End Group 
# End Target
# End Project
