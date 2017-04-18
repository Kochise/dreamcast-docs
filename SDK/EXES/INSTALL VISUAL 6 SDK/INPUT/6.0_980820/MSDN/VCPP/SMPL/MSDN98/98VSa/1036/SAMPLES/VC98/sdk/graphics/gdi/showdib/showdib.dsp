# Microsoft Developer Studio Project File - Name="showdib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=showdib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "showdib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "showdib.mak" CFG="showdib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "showdib - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "showdib - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "showdib - Win32 Release"

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
# PROP Target_File "showdib.exe"
# PROP Bsc_Name "showdib.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "showdib - Win32 Debug"

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
# PROP Target_File "showdib.exe"
# PROP Bsc_Name "showdib.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "showdib - Win32 Release"
# Name "showdib - Win32 Debug"

!IF  "$(CFG)" == "showdib - Win32 Release"

!ELSEIF  "$(CFG)" == "showdib - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\DIB.C
# End Source File
# Begin Source File

SOURCE=.\DLGOPEN.C
# End Source File
# Begin Source File

SOURCE=.\DRAWDIB.C
# End Source File
# Begin Source File

SOURCE=.\PRINT.C
# End Source File
# Begin Source File

SOURCE=.\SHOWDIB.C
# End Source File
# Begin Source File

SOURCE=.\SHOWDIB.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\SHOWDIB.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\SHOWDIB.RC
# End Source File
# Begin Source File

SOURCE=.\CRAK1.BMP
# End Source File
# Begin Source File

SOURCE=.\SHOWDIB.ICO
# End Source File
# End Group 
# End Target
# End Project
