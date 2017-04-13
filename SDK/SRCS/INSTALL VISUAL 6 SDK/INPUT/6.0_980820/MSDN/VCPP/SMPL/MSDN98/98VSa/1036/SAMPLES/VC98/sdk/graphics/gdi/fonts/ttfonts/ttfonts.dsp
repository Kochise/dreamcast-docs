# Microsoft Developer Studio Project File - Name="ttfonts" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=ttfonts - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ttfonts.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ttfonts.mak" CFG="ttfonts - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ttfonts - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "ttfonts - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "ttfonts - Win32 Release"

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
# PROP Target_File "ttfonts.exe"
# PROP Bsc_Name "ttfonts.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "ttfonts - Win32 Debug"

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
# PROP Target_File "ttfonts.exe"
# PROP Bsc_Name "ttfonts.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "ttfonts - Win32 Release"
# Name "ttfonts - Win32 Debug"

!IF  "$(CFG)" == "ttfonts - Win32 Release"

!ELSEIF  "$(CFG)" == "ttfonts - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\ALLFONT.C
# End Source File
# Begin Source File

SOURCE=.\DIALOGS.C
# End Source File
# Begin Source File

SOURCE=.\DISPLAY.C
# End Source File
# Begin Source File

SOURCE=.\TOOLBAR.C
# End Source File
# Begin Source File

SOURCE=.\TTFONTS.C
# End Source File
# Begin Source File

SOURCE=.\TTFONTS.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\TTFONTS.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\TTFONTS.RC
# End Source File
# Begin Source File

SOURCE=.\BMDEVICE.BMP
# End Source File
# Begin Source File

SOURCE=.\BMTT.BMP
# End Source File
# Begin Source File

SOURCE=.\TTFONTS.ICO
# End Source File
# End Group 
# End Target
# End Project
