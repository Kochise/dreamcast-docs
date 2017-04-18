# Microsoft Developer Studio Project File - Name="LSPcallback" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (WCE SH4) Dynamic-Link Library" 0x8602

CFG=LSPcallback - Win32 (WCE SH4) Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "LSPcallback.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "LSPcallback.mak" CFG="LSPcallback - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "LSPcallback - Win32 (WCE SH4) Release" ("Win32 (WCE SH4) Dynamic-Link Library" 用)
!MESSAGE "LSPcallback - Win32 (WCE SH4) Debug" ("Win32 (WCE SH4) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Dreamcast"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LSPcallback - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH4Rel"
# PROP Intermediate_Dir "WCESH4Rel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Ox /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD CPP /nologo /MC /W3 /Zi /Ox /I "..\inc" /I "c:\WCEDremcast\inc" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD BASE RSC /l 0x411 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x411 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /dll /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 coredll.lib ..\lib\retail\LSPdebug.lib ..\lib\retail\LSPregistry.lib ..\lib\retail\LSPsend.lib ..\lib\retail\LSPmanage.lib dplayx.lib /nologo /dll /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /out:"WCESH4Rel/LobbySP.dll" /libpath:"..\lib" /libpath:"c:\WCEDreamcast\lib\retail" /libpath:"..\..\..\DrgaonARK\lib\SH4\wince\retail" /subsystem:$(CESubsystem) /STACK:65536,4096
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy WCESH4Rel\LobbySP.lib ..\lib\retail	copy WCESH4Rel\LobbySP.dll ..\bin\retail	copy WCESH4Rel\LobbySP.dll c:\WCEDreamcast\release\retail\os
# End Special Build Tool

!ELSEIF  "$(CFG)" == "LSPcallback - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH4Dbg"
# PROP Intermediate_Dir "WCESH4Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
# ADD CPP /nologo /MC /W3 /Zi /Od /I "..\inc" /I "c:\WCEDremcast\inc" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
# ADD BASE RSC /l 0x411 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x411 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /dll /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 coredll.lib ..\lib\debug\LSPdebug.lib ..\lib\debug\LSPregistry.lib ..\lib\debug\LSPsend.lib ..\lib\debug\LSPmanage.lib dplayx.lib /nologo /dll /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /out:"WCESH4Dbg/LobbySP.dll" /libpath:"..\lib" /libpath:"c:\WCEDreamcast\lib\retail" /libpath:"..\..\..\DrgaonARK\lib\SH4\wince\retail" /subsystem:$(CESubsystem) /STACK:65536,4096
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy WCESH4Dbg\LobbySP.lib ..\lib\debug	copy WCESH4Dbg\LobbySP.dll ..\bin\debug	copy WCESH4Dbg\LobbySP.pdb ..\bin\debug	copy WCESH4Dbg\LobbySP.dll c:\WCEDreamcast\release\debug\os	copy WCESH4Dbg\LobbySP.pdb c:\WCEDreamcast\release\debug\os
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "LSPcallback - Win32 (WCE SH4) Release"
# Name "LSPcallback - Win32 (WCE SH4) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\LSPcallback.def
# End Source File
# Begin Source File

SOURCE=.\LSPdplay.cpp
DEP_CPP_LSPDP=\
	"..\inc\dpf.h"\
	"..\inc\dpldplay.h"\
	"..\inc\dplmess.h"\
	"..\inc\LSPdebug.h"\
	"..\inc\LSPfuncs.h"\
	"..\inc\LSPlobby.h"\
	"..\inc\memalloc.h"\
	"..\inc\SRScom.h"\
	{$(INCLUDE)}"lobbysp.h"\
	
# End Source File
# Begin Source File

SOURCE=.\LSPgroup.cpp
DEP_CPP_LSPGR=\
	"..\inc\LSPdebug.h"\
	"..\inc\LSPfuncs.h"\
	"..\inc\LSPlobby.h"\
	"..\inc\SRLmanage.h"\
	"..\inc\SRLregistry.h"\
	"..\inc\SRLsend.h"\
	"..\inc\SRScom.h"\
	{$(INCLUDE)}"lobbysp.h"\
	
# End Source File
# Begin Source File

SOURCE=.\LSPmakelist.cpp
DEP_CPP_LSPMA=\
	"..\inc\LSPlobby.h"\
	"..\inc\SRScom.h"\
	
# End Source File
# Begin Source File

SOURCE=.\LSPplayer.cpp
DEP_CPP_LSPPL=\
	"..\inc\LSPdebug.h"\
	"..\inc\LSPfuncs.h"\
	"..\inc\LSPlobby.h"\
	"..\inc\SRLmanage.h"\
	"..\inc\SRLregistry.h"\
	"..\inc\SRLsend.h"\
	"..\inc\SRScom.h"\
	{$(INCLUDE)}"lobbysp.h"\
	
# End Source File
# Begin Source File

SOURCE=.\LSPsession.cpp
DEP_CPP_LSPSE=\
	"..\inc\LSPdebug.h"\
	"..\inc\LSPfuncs.h"\
	"..\inc\LSPlobby.h"\
	"..\inc\SRLmanage.h"\
	"..\inc\SRLregistry.h"\
	"..\inc\SRLsend.h"\
	"..\inc\SRScom.h"\
	{$(INCLUDE)}"lobbysp.h"\
	
# End Source File
# End Group
# End Target
# End Project
