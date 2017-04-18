# Microsoft Developer Studio Project File - Name="browseh" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=browseh - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "browseh.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "browseh.mak" CFG="browseh - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "browseh - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "browseh - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "browseh - Win32 Release"

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
# PROP Target_File "browseh.dll"
# PROP Bsc_Name "browseh.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "browseh - Win32 Debug"

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
# PROP Target_File "browseh.dll"
# PROP Bsc_Name "browseh.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "browseh - Win32 Release"
# Name "browseh - Win32 Debug"

!IF  "$(CFG)" == "browseh - Win32 Release"

!ELSEIF  "$(CFG)" == "browseh - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\browseh_i.c
# End Source File
# Begin Source File

SOURCE=.\ALIAS.CPP
# End Source File
# Begin Source File

SOURCE=.\BROWSECF.CPP
# End Source File
# Begin Source File

SOURCE=.\BROWSEH.CPP
# End Source File
# Begin Source File

SOURCE=.\COCLASS.CPP
# End Source File
# Begin Source File

SOURCE=.\COLLECT.CPP
# End Source File
# Begin Source File

SOURCE=.\CONSTANT.CPP
# End Source File
# Begin Source File

SOURCE=.\DISPFACE.CPP
# End Source File
# Begin Source File

SOURCE=.\ENUM.CPP
# End Source File
# Begin Source File

SOURCE=.\ENUMVAR.CPP
# End Source File
# Begin Source File

SOURCE=.\FUNCTION.CPP
# End Source File
# Begin Source File

SOURCE=.\INTFACE.CPP
# End Source File
# Begin Source File

SOURCE=.\MAIN.CPP
# End Source File
# Begin Source File

SOURCE=.\MODULE.CPP
# End Source File
# Begin Source File

SOURCE=.\MYDISP.CPP
# End Source File
# Begin Source File

SOURCE=.\PARAM.CPP
# End Source File
# Begin Source File

SOURCE=.\PROPERTY.CPP
# End Source File
# Begin Source File

SOURCE=.\STRUCT.CPP
# End Source File
# Begin Source File

SOURCE=.\TYPE.CPP
# End Source File
# Begin Source File

SOURCE=.\TYPEINFO.CPP
# End Source File
# Begin Source File

SOURCE=.\TYPELIB.CPP
# End Source File
# Begin Source File

SOURCE=.\UNION.CPP
# End Source File
# Begin Source File

SOURCE=.\BROWSEH.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\BROWSEH.H
# End Source File
# Begin Source File

SOURCE=.\MYDISP.H
# End Source File
# Begin Source File

SOURCE=.\tlb.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\BROWSEH.RC
# End Source File
# End Group 
# End Target
# End Project
