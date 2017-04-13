# Microsoft Developer Studio Project File - Name="smh32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=smh32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "smh32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smh32.mak" CFG="smh32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "smh32 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "smh32 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "smh32 - Win32 Release"

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
# PROP Target_File "smh32.dll"
# PROP Bsc_Name "smh32.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "smh32 - Win32 Debug"

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
# PROP Target_File "smh32.dll"
# PROP Bsc_Name "smh32.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "smh32 - Win32 Release"
# Name "smh32 - Win32 Debug"

!IF  "$(CFG)" == "smh32 - Win32 Release"

!ELSEIF  "$(CFG)" == "smh32 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\SMH.C
# End Source File
# Begin Source File

SOURCE=.\SMHARC.C
# End Source File
# Begin Source File

SOURCE=.\SMHATP.C
# End Source File
# Begin Source File

SOURCE=.\SMHCFG.C
# End Source File
# Begin Source File

SOURCE=.\SMHGUID.C
# End Source File
# Begin Source File

SOURCE=.\SMHINPXP.C
# End Source File
# Begin Source File

SOURCE=.\SMHMDB.C
# End Source File
# Begin Source File

SOURCE=.\SMHOLE.C
# End Source File
# Begin Source File

SOURCE=.\SMHOOF.C
# End Source File
# Begin Source File

SOURCE=.\SMHPS.C
# End Source File
# Begin Source File

SOURCE=.\SMHRK.C
# End Source File
# Begin Source File

SOURCE=.\SMHTB.C
# End Source File
# Begin Source File

SOURCE=.\SMHWB.C
# End Source File
# Begin Source File

SOURCE=.\SMHWIZ.C
# End Source File
# Begin Source File

SOURCE=.\SMH32.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\SMHNLS.H
# End Source File
# Begin Source File

SOURCE=.\SMHRC.H
# End Source File
# Begin Source File

SOURCE=.\_PCH.H
# End Source File
# Begin Source File

SOURCE=.\_SMH.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\SMH.RC
# End Source File
# Begin Source File

SOURCE=.\DOWN.BMP
# End Source File
# Begin Source File

SOURCE=.\DOWNDIS.BMP
# End Source File
# Begin Source File

SOURCE=.\DOWNINV.BMP
# End Source File
# Begin Source File

SOURCE=.\TOOLBAR.BMP
# End Source File
# Begin Source File

SOURCE=.\UP.BMP
# End Source File
# Begin Source File

SOURCE=.\UPDIS.BMP
# End Source File
# Begin Source File

SOURCE=.\UPINV.BMP
# End Source File
# Begin Source File

SOURCE=.\SMH.ICO
# End Source File
# End Group 
# End Target
# End Project
