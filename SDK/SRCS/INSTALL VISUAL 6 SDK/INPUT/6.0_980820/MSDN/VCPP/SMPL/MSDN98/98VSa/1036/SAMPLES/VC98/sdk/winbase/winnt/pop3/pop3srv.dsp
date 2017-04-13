# Microsoft Developer Studio Project File - Name="pop3srv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=pop3srv - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pop3srv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pop3srv.mak" CFG="pop3srv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pop3srv - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "pop3srv - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "pop3srv - Win32 Release"

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
# PROP Target_File "pop3srv.exe"
# PROP Bsc_Name "pop3srv.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "pop3srv - Win32 Debug"

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
# PROP Target_File "pop3srv.exe"
# PROP Bsc_Name "pop3srv.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "pop3srv - Win32 Release"
# Name "pop3srv - Win32 Debug"

!IF  "$(CFG)" == "pop3srv - Win32 Release"

!ELSEIF  "$(CFG)" == "pop3srv - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\DEBUG.C
# End Source File
# Begin Source File

SOURCE=.\EVENTS.C
# End Source File
# Begin Source File

SOURCE=.\PARAM.C
# End Source File
# Begin Source File

SOURCE=.\POP3.C
# End Source File
# Begin Source File

SOURCE=.\POP3SRV.C
# End Source File
# Begin Source File

SOURCE=.\POPFILE.C
# End Source File
# Begin Source File

SOURCE=.\SERVICE.C
# End Source File
# Begin Source File

SOURCE=.\SOCKET.C
# End Source File
# Begin Source File

SOURCE=.\THREADS.C
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\DEBUG.H
# End Source File
# Begin Source File

SOURCE=.\GLOBALS.H
# End Source File
# Begin Source File

SOURCE=.\POP3.H
# End Source File
# Begin Source File

SOURCE=.\POP3CTX.H
# End Source File
# Begin Source File

SOURCE=.\POP3SRVP.H
# End Source File
# Begin Source File

SOURCE=.\POPFILE.H
# End Source File
# Begin Source File

SOURCE=.\PROTOS.H
# End Source File
# Begin Source File

SOURCE=.\pop3evnt.h
# End Source File
# End Group 
# Begin Group "Resource Files" 
# Begin Source File

SOURCE=.\pop3evnt.rc
# End Source File
# End Group 
# End Target
# End Project
