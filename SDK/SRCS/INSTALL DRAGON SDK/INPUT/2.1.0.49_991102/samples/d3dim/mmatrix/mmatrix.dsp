# Microsoft Developer Studio Project File - Name="mmatrix" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Application" 0x8601

CFG=mmatrix - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mmatrix.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mmatrix.mak" CFG="mmatrix - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mmatrix - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "mmatrix - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Desktop"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mmatrix - Win32 (WCE SH4) Release"

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
# ADD CPP /nologo /Qsh4r7 /Qs /W3 /WX  /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DDEBUG=1 -DDRAGON  -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /YX /Qfast /Qpartial /Qgvp /Ogityb2 /Gs /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r  /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 corelibc.lib coredll.lib commctrl.lib /nologo /machine:SH4 /nodefaultlib /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 coredll.lib corelibc.lib ddraw.lib dinput.lib dxguid.lib  floatmath.lib  /nologo /pdb:"..\..\..\release\retail\Samples/mmatrix.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/mmatrix.exe" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "mmatrix - Win32 (WCE SH4) Debug"

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
# ADD CPP /nologo /Qsh4r7 /Qs /Oi /W3 /WX /Zi /Od  /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DDEBUG=1 -DDRAGON  -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /YX /Qfast /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r  /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 corelibc.lib coredll.lib commctrl.lib /nologo /debug /machine:SH4 /nodefaultlib /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 coredll.lib corelibc.lib ddraw.lib dinput.lib dxguid.lib  floatmath.lib  /nologo /incremental:no /pdb:"..\..\..\release\debug\Samples/mmatrix.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/mmatrix.exe" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "mmatrix - Win32 (WCE SH4) Release"
# Name "mmatrix - Win32 (WCE SH4) Debug"

# Begin Source File
SOURCE=.\mmatrix.cpp
# End Source File
# Begin Source File
SOURCE=.\mmatrix.rc
# End Source File
# Begin Source File
SOURCE=.\D3DUtil.cpp
# End Source File
# Begin Source File
SOURCE=.\TxtrUtil.cpp
# End Source File
# Begin Source File
SOURCE=.\DDUtil.cpp
# End Source File
# Begin Source File
SOURCE=.\Error.cpp
# End Source File
# Begin Source File
SOURCE=.\fastmat.src
# End Source File
# Begin Source File
SOURCE=.\readme.txt
# End Source File

# Begin Source File

SOURCE=.\fastmat.src

!IF  "$(CFG)" == "mmatrix - Win32 (WCE SH4) Release"

# Begin Custom Build
TargetDir=.\WCESH4Rel
InputPath=.\fastmat.src
InputName=fastmat

"$(TargetDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	shasm -cpu=sh4 $(InputName).src -o=$(TargetDir)\$(InputName).obj

# End Custom Build

!ELSEIF  "$(CFG)" == "mmatrix - Win32 (WCE SH4) Debug"

# Begin Custom Build
TargetDir=.\WCESH4Dbg
InputPath=.\fastmat.src
InputName=fastmat

"$(TargetDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	shasm -cpu=sh4 $(InputName).src -o=$(TargetDir)\$(InputName).obj

# End Custom Build

!ENDIF 

# End Source File

# End Target
# End Project
