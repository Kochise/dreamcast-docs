# Microsoft Developer Studio Project File - Name="tcime" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Application" 0x8601

CFG=tcime - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tcime.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tcime.mak" CFG="tcime - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tcime - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "tcime - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Desktop"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tcime - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Qsh4r7 /Qs /W3 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /c
# ADD CPP /nologo /Qsh4r7 /Qs /W3 /WX /I "e:\Dragon21\public\mcpupub\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /YX /Qfast /Qpartial /Qgvp /Ogityb2 /Gs /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /i "e:\Dragon21\public\mcpupub\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 corelibc.lib coredll.lib commctrl.lib /nologo /machine:SH4 /nodefaultlib /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 coredll.lib corelibc.lib  ddraw.lib dinput.lib dxguid.lib  /nologo /pdb:"..\..\..\release\retail\Samples/tcime.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/tcime.exe" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "tcime - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Qsh4r7 /Qs /Oi /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /c
# ADD CPP /nologo /Qsh4r7 /Qs /Oi /W3 /WX /Zi /Od /I "e:\Dragon21\public\mcpupub\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /YX /Qfast /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /i "e:\Dragon21\public\mcpupub\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 corelibc.lib coredll.lib commctrl.lib /nologo /debug /machine:SH4 /nodefaultlib /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 coredll.lib corelibc.lib  ddraw.lib dinput.lib dxguid.lib  /nologo /incremental:no /pdb:"..\..\..\release\debug\Samples/tcime.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/tcime.exe" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "tcime - Win32 (WCE SH4) Release"
# Name "tcime - Win32 (WCE SH4) Debug"

# Begin Source File
SOURCE=.\winmain.cpp
# End Source File
# Begin Source File
SOURCE=.\input.cpp
# End Source File
# Begin Source File
SOURCE=.\ddutil.cpp
# End Source File
# Begin Source File
SOURCE=.\display.cpp
# End Source File
# Begin Source File
SOURCE=.\editbox.cpp
# End Source File
# Begin Source File
SOURCE=.\softkbd.cpp
# End Source File
# Begin Source File
SOURCE=.\readwnd.cpp
# End Source File
# Begin Source File
SOURCE=.\candwnd.cpp
# End Source File
# Begin Source File
SOURCE=.\indicate.cpp
# End Source File
# Begin Source File
SOURCE=.\inputskb.cpp
# End Source File
# Begin Source File
SOURCE=.\inputcwd.cpp
# End Source File
# Begin Source File
SOURCE=.\dspskb.cpp
# End Source File
# Begin Source File
SOURCE=.\dspcwd.cpp
# End Source File
# Begin Source File
SOURCE=.\phonetic.cpp
# End Source File
# Begin Source File
SOURCE=.\romanji.cpp
# End Source File
# Begin Source File
SOURCE=.\symbols.cpp
# End Source File
# Begin Source File
SOURCE=.\imesamp.rc
# End Source File
# Begin Source File
SOURCE=.\readme.txt
# End Source File

# End Target
# End Project
