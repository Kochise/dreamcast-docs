# Microsoft Developer Studio Project File - Name="poly21" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=poly21 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "poly21.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "poly21.mak" CFG="poly21 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "poly21 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "poly21 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "poly21 - Win32 Release"

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
# PROP Target_File "poly21.dll"
# PROP Bsc_Name "poly21.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "poly21 - Win32 Debug"

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
# PROP Target_File "poly21.dll"
# PROP Bsc_Name "poly21.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "poly21 - Win32 Release"
# Name "poly21 - Win32 Debug"

!IF  "$(CFG)" == "poly21 - Win32 Release"

!ELSEIF  "$(CFG)" == "poly21 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\DLLPOLY.CPP
# End Source File
# Begin Source File

SOURCE=.\ICONNPT.CPP
# End Source File
# Begin Source File

SOURCE=.\IDATAOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\IEXTCONN.CPP
# End Source File
# Begin Source File

SOURCE=.\IOLEOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\IPERSTMI.CPP
# End Source File
# Begin Source File

SOURCE=.\IPERSTOR.CPP
# End Source File
# Begin Source File

SOURCE=.\IPOLYLIN.CPP
# End Source File
# Begin Source File

SOURCE=.\IRUNOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\IVIEWOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\POLYLINE.CPP
# End Source File
# Begin Source File

SOURCE=.\POLYWIN.CPP
# End Source File
# Begin Source File

SOURCE=.\PRECOMP.CPP
# End Source File
# Begin Source File

SOURCE=.\WIN16.DEF
# End Source File
# Begin Source File

SOURCE=.\WIN32.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\POLYLINE.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\POLYLINE.RC
# End Source File
# Begin Source File

SOURCE=.\POLYLINE.ICO
# End Source File
# End Group 
# End Target
# End Project
