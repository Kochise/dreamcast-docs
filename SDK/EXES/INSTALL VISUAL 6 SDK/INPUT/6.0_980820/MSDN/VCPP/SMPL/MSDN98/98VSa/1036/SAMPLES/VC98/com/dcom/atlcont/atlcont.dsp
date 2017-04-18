# Microsoft Developer Studio Project File - Name="AtlCont" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AtlCont - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "atlcont.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "atlcont.mak" CFG="AtlCont - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AtlCont - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AtlCont - Win32 MinCRT" (based on "Win32 (x86) Application")
!MESSAGE "AtlCont - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "AtlCont - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "AtlCont - Win32 Unicode MinCRT" (based on "Win32 (x86) Application")
!MESSAGE "AtlCont - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AtlCont - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 oledlg.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\atlcont.exe
InputPath=.\Release\atlcont.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 MinCRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\MinRel"
# PROP BASE Intermediate_Dir ".\MinRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\MinRel"
# PROP Intermediate_Dir ".\MinRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_MIN_CRT" /Fp".\Release\AtlCont.pch" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"WinMain" /subsystem:windows /machine:I386
# ADD LINK32 oledlg.lib /nologo /entry:"WinMain" /subsystem:windows /machine:I386
# SUBTRACT LINK32 /debug
# Begin Custom Build
OutDir=.\MinRel
TargetPath=.\MinRel\atlcont.exe
InputPath=.\MinRel\atlcont.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 oledlg.lib /nologo /subsystem:windows /debug /machine:I386
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\atlcont.exe
InputPath=.\Debug\atlcont.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Unicode Release"
# PROP BASE Intermediate_Dir ".\Unicode Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\ReleaseU"
# PROP Intermediate_Dir ".\ReleaseU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 oledlg.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
# Begin Custom Build
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\atlcont.exe
InputPath=.\ReleaseU\atlcont.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 Unicode MinCRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Unicode Release MinCRT"
# PROP BASE Intermediate_Dir ".\Unicode Release MinCRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\MinRelU"
# PROP Intermediate_Dir ".\MinRelU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "_ATL_MIN_CRT" /Fp".\ReleaseU\AtlCont.pch" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMain" /subsystem:windows /machine:I386
# ADD LINK32 oledlg.lib /nologo /entry:"wWinMain" /subsystem:windows /machine:I386
# Begin Custom Build
OutDir=.\MinRelU
TargetPath=.\MinRelU\atlcont.exe
InputPath=.\MinRelU\atlcont.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Unicode Debug"
# PROP BASE Intermediate_Dir ".\Unicode Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DebugU"
# PROP Intermediate_Dir ".\DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 oledlg.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
# Begin Custom Build
OutDir=.\DebugU
TargetPath=.\DebugU\atlcont.exe
InputPath=.\DebugU\atlcont.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "AtlCont - Win32 Release"
# Name "AtlCont - Win32 MinCRT"
# Name "AtlCont - Win32 Debug"
# Name "AtlCont - Win32 Unicode Release"
# Name "AtlCont - Win32 Unicode MinCRT"
# Name "AtlCont - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AtlCont.cpp
# End Source File
# Begin Source File

SOURCE=.\AtlCont.idl

!IF  "$(CFG)" == "AtlCont - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AtlCont.idl

BuildCmds= \
	midl /Oic /h AtlCont.h /iid AtlCont_i.c AtlCont.idl

"AtlCont.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 MinCRT"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AtlCont.idl

BuildCmds= \
	midl /Oic /h AtlCont.h /iid AtlCont_i.c AtlCont.idl

"AtlCont.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AtlCont.idl

BuildCmds= \
	midl /Oic /h AtlCont.h /iid AtlCont_i.c AtlCont.idl

"AtlCont.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 Unicode Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AtlCont.idl

BuildCmds= \
	midl /Oic /h AtlCont.h /iid AtlCont_i.c AtlCont.idl

"AtlCont.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 Unicode MinCRT"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AtlCont.idl

BuildCmds= \
	midl /Oic /h AtlCont.h /iid AtlCont_i.c AtlCont.idl

"AtlCont.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AtlCont - Win32 Unicode Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AtlCont.idl

BuildCmds= \
	midl /Oic /h AtlCont.h /iid AtlCont_i.c AtlCont.idl

"AtlCont.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"AtlCont_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AtlCont.rc
# End Source File
# Begin Source File

SOURCE=.\AtlCont1.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AtlCont1.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\AtlCont.rgs
# End Source File
# End Target
# End Project
