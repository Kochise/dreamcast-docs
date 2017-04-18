# Microsoft Developer Studio Project File - Name="midipl32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=midipl32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "midipl32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "midipl32.mak" CFG="midipl32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "midipl32 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "midipl32 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "midipl32 - Win32 Release"

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
# PROP Target_File "midipl32.exe"
# PROP Bsc_Name "midipl32.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "midipl32 - Win32 Debug"

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
# PROP Target_File "midipl32.exe"
# PROP Bsc_Name "midipl32.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "midipl32 - Win32 Release"
# Name "midipl32 - Win32 Debug"

!IF  "$(CFG)" == "midipl32 - Win32 Release"

!ELSEIF  "$(CFG)" == "midipl32 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\DEBUG.C
# End Source File
# Begin Source File

SOURCE=.\MAINWND.C
# End Source File
# Begin Source File

SOURCE=.\MIDIPLYR.C
# End Source File
# Begin Source File

SOURCE=.\SEQUENCE.C
# End Source File
# Begin Source File

SOURCE=.\SMF.C
# End Source File
# Begin Source File

SOURCE=.\SMFREAD.C
# End Source File
# Begin Source File

SOURCE=.\TIMEWND.C
# End Source File
# Begin Source File

SOURCE=.\UIUTILS.C
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\DEBUG.H
# End Source File
# Begin Source File

SOURCE=.\GLOBAL.H
# End Source File
# Begin Source File

SOURCE=.\MIDIPLYR.H
# End Source File
# Begin Source File

SOURCE=.\MULDIV32.H
# End Source File
# Begin Source File

SOURCE=.\SEQ.H
# End Source File
# Begin Source File

SOURCE=.\SMF.H
# End Source File
# Begin Source File

SOURCE=.\SMFI.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\MIDIPLYR.RC
# End Source File
# Begin Source File

SOURCE=.\TOOLBAR.BMP
# End Source File
# Begin Source File

SOURCE=.\MIDIPLYR.ICO
# End Source File
# End Group 
# End Target
# End Project
