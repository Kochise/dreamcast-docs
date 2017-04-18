# Microsoft Developer Studio Project File - Name="DrawServ" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DrawServ - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DrawServ.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DrawServ.mak" CFG="DrawServ - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DrawServ - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DrawServ - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "DrawServ - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "DrawServ - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DrawServ - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp".\Release\predraw.pch" /YX"predraw.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /debug
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\DrawServ.exe
InputPath=.\Release\DrawServ.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /FR /Fp".\Debug\predraw.pch" /YX"predraw.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\DrawServ.exe
InputPath=.\Debug\DrawServ.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Unicode Release"
# PROP BASE Intermediate_Dir ".\Unicode Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\ReleaseU"
# PROP Intermediate_Dir ".\ReleaseU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp".\ReleaseU\predraw.pch" /YX"predraw.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
# Begin Custom Build
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\DrawServ.exe
InputPath=.\ReleaseU\DrawServ.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Unicode Debug"
# PROP BASE Intermediate_Dir ".\Unicode Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DebugU"
# PROP Intermediate_Dir ".\DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp".\DebugU\predraw.pch" /YX"predraw.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
# Begin Custom Build
OutDir=.\DebugU
TargetPath=.\DebugU\DrawServ.exe
InputPath=.\DebugU\DrawServ.exe
SOURCE="$(InputPath)"

"$(OutDir)\reg_exe.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done! 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "DrawServ - Win32 Release"
# Name "DrawServ - Win32 Debug"
# Name "DrawServ - Win32 Unicode Release"
# Name "DrawServ - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\DrawObj.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawObj.rgs
# End Source File
# Begin Source File

SOURCE=.\DrawServ.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawServ.idl

!IF  "$(CFG)" == "DrawServ - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\DrawServ.idl

BuildCmds= \
	midl DrawServ.idl

"DrawServ.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DrawServ.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DrawServ_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\DrawServ.idl

BuildCmds= \
	midl DrawServ.idl

"DrawServ.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DrawServ.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DrawServ_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\DrawServ.idl

BuildCmds= \
	midl DrawServ.idl

"DrawServ.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DrawServ.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DrawServ_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\DrawServ.idl

BuildCmds= \
	midl DrawServ.idl

"DrawServ.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DrawServ.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DrawServ_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DrawServ.rc
# End Source File
# Begin Source File

SOURCE=.\DrawServ.rgs
# End Source File
# Begin Source File

SOURCE=.\predraw.cpp

!IF  "$(CFG)" == "DrawServ - Win32 Release"

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Debug"

# ADD CPP /Yc

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CPIDServ.h
# End Source File
# Begin Source File

SOURCE=.\DrawObj.h
# End Source File
# Begin Source File

SOURCE=.\predraw.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
# Section DrawServ : {330E9E8C-DF48-11CF-8E2C-00A0C90DC94B}
# 	0:13:CPIDrawServ.h:C:\Source\DrawServ\CPIDrawServ.h
# End Section
