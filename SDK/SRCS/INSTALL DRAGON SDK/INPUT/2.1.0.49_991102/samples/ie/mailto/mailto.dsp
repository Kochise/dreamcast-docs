# Microsoft Developer Studio Project File - Name="mailto" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Dynamic-Link Library" 0x8602

CFG=mailto - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mailto.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mailto.mak" CFG="mailto - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mailto - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Dynamic-Link Library")
!MESSAGE "mailto - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Dreamcast"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mailto - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Qsh4 /MC /W3 /GX- /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "_MBCS" /D "_USRDLL" /D "MAILTO_EXPORTS" /YX /c
# ADD CPP /nologo /Qsh4 /MC /W3 /GX- /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "_MBCS" /D "_USRDLL" /D "MAILTO_EXPORTS" /YX /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /D "_UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /fo"retail/mailto.res" /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /D "_UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib urlmon.lib /nologo /dll /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib urlmon.lib /nologo /dll /pdb:"..\..\..\release\retail\Samples/mailto.pdb" /machine:SH4 /def:"mailto.def" /out:"..\..\..\release\retail\Samples/mailto.dll" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "mailto - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Qsh4 /MC /W3 /GX- /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "_MBCS" /D "_USRDLL" /D "MAILTO_EXPORTS" /YX /c
# ADD CPP /nologo /Qsh4 /MC /W3 /GX- /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "_MBCS" /D "_USRDLL" /D "MAILTO_EXPORTS" /YX /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /D "_UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /fo"debug/mailto.res" /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /D "_UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib urlmon.lib /nologo /dll /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib urlmon.lib /nologo /dll /incremental:no /pdb:"..\..\..\release\debug\Samples/mailto.pdb" /debug /machine:SH4 /nodefaultlib /def:"mailto.def" /out:"..\..\..\release\debug\Samples/mailto.dll" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "mailto - Win32 (WCE SH4) Release"
# Name "mailto - Win32 (WCE SH4) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mailto.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
