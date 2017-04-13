# Microsoft Developer Studio Project File - Name="tri3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=tri3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tri3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tri3.mak" CFG="tri3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tri3 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "tri3 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "tri3 - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "release\"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release\"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "release\tri3.exe"
# PROP Bsc_Name "tri3.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "tri3 - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "debug\"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug\"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "debug\tri3.exe"
# PROP Bsc_Name "tri3.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "tri3 - Win32 Release"
# Name "tri3 - Win32 Debug"

!IF  "$(CFG)" == "tri3 - Win32 Release"

!ELSEIF  "$(CFG)" == "tri3 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\D3DAPP.C
# End Source File
# Begin Source File

SOURCE=.\D3DCALLS.C
# End Source File
# Begin Source File

SOURCE=.\DDCALLS.C
# End Source File
# Begin Source File

SOURCE=.\LCLIB.C
# End Source File
# Begin Source File

SOURCE=.\MISC.C
# End Source File
# Begin Source File

SOURCE=.\TEXTURE.C
# End Source File
# Begin Source File

SOURCE=.\TRIANGLE.C
# End Source File
# Begin Source File

SOURCE=.\D3DMAIN.CPP
# End Source File
# Begin Source File

SOURCE=.\STATS.CPP
# End Source File
# Begin Source File

SOURCE=.\TRI3.DEF
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\D3DAPP.H
# End Source File
# Begin Source File

SOURCE=.\D3DAPPI.H
# End Source File
# Begin Source File

SOURCE=.\D3DDEMO.H
# End Source File
# Begin Source File

SOURCE=.\D3DMACS.H
# End Source File
# Begin Source File

SOURCE=.\D3DMAIN.H
# End Source File
# Begin Source File

SOURCE=.\D3DMATH.H
# End Source File
# Begin Source File

SOURCE=.\D3DRES.H
# End Source File
# Begin Source File

SOURCE=.\D3DSPHR.H
# End Source File
# Begin Source File

SOURCE=.\LCLIB.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\D3DMAIN.RC
# End Source File
# Begin Source File

SOURCE=.\D3D.ICO
# End Source File
# End Group 
# End Target
# End Project
