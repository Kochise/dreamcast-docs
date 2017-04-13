# Microsoft Developer Studio Project File - Name="midim32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=midim32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "midim32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "midim32.mak" CFG="midim32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "midim32 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "midim32 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "midim32 - Win32 Release"

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
# PROP Target_File "midim32.exe"
# PROP Bsc_Name "midim32.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "midim32 - Win32 Debug"

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
# PROP Target_File "midim32.exe"
# PROP Bsc_Name "midim32.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "midim32 - Win32 Release"
# Name "midim32 - Win32 Debug"

!IF  "$(CFG)" == "midim32 - Win32 Release"

!ELSEIF  "$(CFG)" == "midim32 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\ABOUT.C
# End Source File
# Begin Source File

SOURCE=.\CALLBACK.C
# End Source File
# Begin Source File

SOURCE=.\CIRCBUF.C
# End Source File
# Begin Source File

SOURCE=.\DISPLAY.C
# End Source File
# Begin Source File

SOURCE=.\FILTER.C
# End Source File
# Begin Source File

SOURCE=.\INSTDATA.C
# End Source File
# Begin Source File

SOURCE=.\MIDIMON.C
# End Source File
# Begin Source File

SOURCE=.\PREFER.C
# End Source File
# Begin Source File

SOURCE=.\CALLBACK.DEF
# End Source File
# Begin Source File

SOURCE=.\MIDIMN16.DEF
# End Source File
# Begin Source File

SOURCE=.\MIDIMNCB.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\ABOUT.H
# End Source File
# Begin Source File

SOURCE=.\CALLBACK.H
# End Source File
# Begin Source File

SOURCE=.\CIRCBUF.H
# End Source File
# Begin Source File

SOURCE=.\DISPLAY.H
# End Source File
# Begin Source File

SOURCE=.\FILTER.H
# End Source File
# Begin Source File

SOURCE=.\INSTDATA.H
# End Source File
# Begin Source File

SOURCE=.\MIDIMON.H
# End Source File
# Begin Source File

SOURCE=.\PREFER.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\MIDIMON.RC
# End Source File
# Begin Source File

SOURCE=.\MIDIMON.ICO
# End Source File
# End Group 
# End Target
# End Project
