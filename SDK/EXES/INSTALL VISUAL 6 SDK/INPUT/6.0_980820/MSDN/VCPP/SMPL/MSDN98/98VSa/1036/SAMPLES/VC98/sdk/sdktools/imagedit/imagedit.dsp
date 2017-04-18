# Microsoft Developer Studio Project File - Name="imagedit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=imagedit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "imagedit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "imagedit.mak" CFG="imagedit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "imagedit - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "imagedit - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "imagedit - Win32 Release"

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
# PROP Target_File "imagedit.exe"
# PROP Bsc_Name "imagedit.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "imagedit - Win32 Debug"

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
# PROP Target_File "imagedit.exe"
# PROP Bsc_Name "imagedit.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "imagedit - Win32 Release"
# Name "imagedit - Win32 Debug"

!IF  "$(CFG)" == "imagedit - Win32 Release"

!ELSEIF  "$(CFG)" == "imagedit - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\COLORWP.C
# End Source File
# Begin Source File

SOURCE=.\DEVINFO.C
# End Source File
# Begin Source File

SOURCE=.\FILE.C
# End Source File
# Begin Source File

SOURCE=.\GLOBALS.C
# End Source File
# Begin Source File

SOURCE=.\ICCLIP.C
# End Source File
# Begin Source File

SOURCE=.\IMAGE.C
# End Source File
# Begin Source File

SOURCE=.\IMAGEDC.C
# End Source File
# Begin Source File

SOURCE=.\IMAGEDIT.C
# End Source File
# Begin Source File

SOURCE=.\IMAGEDLG.C
# End Source File
# Begin Source File

SOURCE=.\IMAGLINK.C
# End Source File
# Begin Source File

SOURCE=.\IMAGUNDO.C
# End Source File
# Begin Source File

SOURCE=.\MENUCMD.C
# End Source File
# Begin Source File

SOURCE=.\PROPBAR.C
# End Source File
# Begin Source File

SOURCE=.\RWBMP.C
# End Source File
# Begin Source File

SOURCE=.\RWICOCUR.C
# End Source File
# Begin Source File

SOURCE=.\RWPAL.C
# End Source File
# Begin Source File

SOURCE=.\TOOLBOX.C
# End Source File
# Begin Source File

SOURCE=.\UTIL.C
# End Source File
# Begin Source File

SOURCE=.\VIEWWP.C
# End Source File
# Begin Source File

SOURCE=.\WORKWP.C
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\DIALOGS.H
# End Source File
# Begin Source File

SOURCE=.\GLOBALS.H
# End Source File
# Begin Source File

SOURCE=.\IDS.H
# End Source File
# Begin Source File

SOURCE=.\IEFUNCS.H
# End Source File
# Begin Source File

SOURCE=.\IEHELP.H
# End Source File
# Begin Source File

SOURCE=.\IMAGEDIT.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\RES.RC
# End Source File
# End Group 
# End Target
# End Project
