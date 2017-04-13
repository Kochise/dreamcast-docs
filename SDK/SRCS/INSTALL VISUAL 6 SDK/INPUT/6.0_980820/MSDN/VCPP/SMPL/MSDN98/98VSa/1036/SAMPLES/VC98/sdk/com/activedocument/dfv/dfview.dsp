# Microsoft Developer Studio Project File - Name="dfview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=dfview - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dfview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dfview.mak" CFG="dfview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dfview - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "dfview - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "dfview - Win32 Release"

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
# PROP Target_File "dfview.exe"
# PROP Bsc_Name "dfview.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "dfview - Win32 Debug"

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
# PROP Target_File "dfview.exe"
# PROP Bsc_Name "dfview.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "dfview - Win32 Release"
# Name "dfview - Win32 Debug"

!IF  "$(CFG)" == "dfview - Win32 Release"

!ELSEIF  "$(CFG)" == "dfview - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\ABOUT.H
# End Source File
# Begin Source File

SOURCE=.\ASSERT.H
# End Source File
# Begin Source File

SOURCE=.\BITMAPS.H
# End Source File
# Begin Source File

SOURCE=.\DFV.H
# End Source File
# Begin Source File

SOURCE=.\MESSAGE.H
# End Source File
# Begin Source File

SOURCE=.\MWCLASS.H
# End Source File
# Begin Source File

SOURCE=.\STRMVWR.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\DFV.RC
# End Source File
# Begin Source File

SOURCE=.\DOCUMENT.BMP
# End Source File
# Begin Source File

SOURCE=.\FOLDER.BMP
# End Source File
# Begin Source File

SOURCE=.\DFV.ICO
# End Source File
# Begin Source File

SOURCE=.\STREAM.ICO
# End Source File
# End Group 
# End Target
# End Project
