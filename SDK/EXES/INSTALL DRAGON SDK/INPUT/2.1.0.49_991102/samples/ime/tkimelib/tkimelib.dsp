# Microsoft Developer Studio Project File - Name="~tkimelib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Static Library" 0x8604

CFG=~tkimelib - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tkimelib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tkimelib.mak" CFG="~tkimelib - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "~tkimelib - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Static Library")
!MESSAGE "~tkimelib - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Desktop"
# PROP WCE_FormatVersion "6.0"

!IF  "$(CFG)" == "~tkimelib - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /Qsh4r7 /Qs /W3 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /c
# ADD CPP /nologo /Qsh4r7 /Qs /W3 /WX /I "e:\Dragon21\public\mcpupub\s..\..\inc" /I "e:\Dragon21\public\Dragon\S..\..\inc" /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /YX /Qfast /Qpartial /Qgvp /Ogityb2 /Gs /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\retail\tkimelib.lib"

!ELSEIF  "$(CFG)" == "~tkimelib - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /Qsh4r7 /Qs /Oi /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /c
# ADD CPP /nologo /Qsh4r7 /Qs /Oi /W3 /WX /Zi /Od /I "e:\Dragon21\public\mcpupub\s..\..\inc" /I "e:\Dragon21\public\Dragon\S..\..\inc" /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /YX /Qfast /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\debug\tkimelib.lib"

!ENDIF 

# Begin Target

# Name "~tkimelib - Win32 (WCE SH4) Release"
# Name "~tkimelib - Win32 (WCE SH4) Debug"
# Begin Source File
SOURCE=.\tkime.cpp
# End Source File
# Begin Source File
SOURCE=.\editbox.cpp
# End Source File
# Begin Source File
SOURCE=.\indicator.cpp
# End Source File
# Begin Source File
SOURCE=.\romakana.cpp
# End Source File
# Begin Source File
SOURCE=.\display.cpp
# End Source File
# Begin Source File
SOURCE=.\displaykwnd.cpp
# End Source File
# Begin Source File
SOURCE=.\displayskb.cpp
# End Source File
# Begin Source File
SOURCE=.\displayswnd.cpp
# End Source File
# Begin Source File
SOURCE=.\hiragana.cpp
# End Source File
# Begin Source File
SOURCE=.\imeui.cpp
# End Source File
# Begin Source File
SOURCE=.\input.cpp
# End Source File
# Begin Source File
SOURCE=.\inputkwnd.cpp
# End Source File
# Begin Source File
SOURCE=.\inputskb.cpp
# End Source File
# Begin Source File
SOURCE=.\inputswnd.cpp
# End Source File
# Begin Source File
SOURCE=.\katakana.cpp
# End Source File
# Begin Source File
SOURCE=.\kwnd.cpp
# End Source File
# Begin Source File
SOURCE=.\romanji.cpp
# End Source File
# Begin Source File
SOURCE=.\shared.cpp
# End Source File
# Begin Source File
SOURCE=.\softkbd.cpp
# End Source File
# Begin Source File
SOURCE=.\swnd.cpp
# End Source File
# Begin Source File
SOURCE=.\ddutil.cpp
# End Source File
# Begin Source File
SOURCE=.\symbols.cpp
# End Source File
# Begin Source File
SOURCE=.\readme.txt
# End Source File

# End Target
# End Project
