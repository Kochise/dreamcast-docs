# Microsoft Developer Studio Project File - Name="smpab32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=smpab32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "smpab32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smpab32.mak" CFG="smpab32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "smpab32 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "smpab32 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "smpab32 - Win32 Release"

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
# PROP Target_File "smpab32.dll"
# PROP Bsc_Name "smpab32.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "smpab32 - Win32 Debug"

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
# PROP Target_File "smpab32.dll"
# PROP Bsc_Name "smpab32.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "smpab32 - Win32 Release"
# Name "smpab32 - Win32 Debug"

!IF  "$(CFG)" == "smpab32 - Win32 Release"

!ELSEIF  "$(CFG)" == "smpab32 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\ABCONT.C
# End Source File
# Begin Source File

SOURCE=.\ABCTBL1.C
# End Source File
# Begin Source File

SOURCE=.\ABCTBL2.C
# End Source File
# Begin Source File

SOURCE=.\ABCTBL3.C
# End Source File
# Begin Source File

SOURCE=.\ABGUID.C
# End Source File
# Begin Source File

SOURCE=.\ABLOGON.C
# End Source File
# Begin Source File

SOURCE=.\ABP.C
# End Source File
# Begin Source File

SOURCE=.\ABSEARCH.C
# End Source File
# Begin Source File

SOURCE=.\ABUSER.C
# End Source File
# Begin Source File

SOURCE=.\OOTID.C
# End Source File
# Begin Source File

SOURCE=.\OOUSER.C
# End Source File
# Begin Source File

SOURCE=.\ROOT.C
# End Source File
# Begin Source File

SOURCE=.\STATUS.C
# End Source File
# Begin Source File

SOURCE=.\TID.C
# End Source File
# Begin Source File

SOURCE=.\WRAP.C
# End Source File
# Begin Source File

SOURCE=.\DLL16.DEF
# End Source File
# Begin Source File

SOURCE=.\SMPAB32.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\ABCTBL.H
# End Source File
# Begin Source File

SOURCE=.\ABP.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\SAMPABP.RC
# End Source File
# End Group 
# End Target
# End Project
