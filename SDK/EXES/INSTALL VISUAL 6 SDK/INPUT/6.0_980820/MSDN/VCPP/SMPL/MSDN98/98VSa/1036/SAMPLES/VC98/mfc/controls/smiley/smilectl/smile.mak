# Microsoft Developer Studio Generated NMAKE File, Based on smile.dsp
!IF "$(CFG)" == ""
CFG=Smile - Win32 Static Debug Runtime
!MESSAGE No configuration specified. Defaulting to Smile - Win32 Static Debug Runtime.
!ENDIF 

!IF "$(CFG)" != "Smile - Win32 Release" && "$(CFG)" != "Smile - Win32 Debug" && "$(CFG)" != "Smile - Win32 Unicode Debug" && "$(CFG)" != "Smile - Win32 Unicode Release" && "$(CFG)" != "Smile - Win32 Static Release" && "$(CFG)" != "Smile - Win32 Static Debug" && "$(CFG)" != "Smile - Win32 Static Release Runtime" && "$(CFG)" != "Smile - Win32 Static Debug Runtime"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smile.mak" CFG="Smile - Win32 Static Debug Runtime"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Smile - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Smile - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Smile - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Smile - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Smile - Win32 Static Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Smile - Win32 Static Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Smile - Win32 Static Release Runtime" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Smile - Win32 Static Debug Runtime" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Smile - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\smile.ocx" ".\.\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Smile.obj"
	-@erase "$(INTDIR)\smile.pch"
	-@erase "$(INTDIR)\Smile.res"
	-@erase "$(INTDIR)\Smile.tlb"
	-@erase "$(INTDIR)\SmileCtl.obj"
	-@erase "$(INTDIR)\SmilePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\smile.exp"
	-@erase "$(OUTDIR)\smile.lib"
	-@erase "$(OUTDIR)\smile.ocx"
	-@erase ".\.\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\smile.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Smile.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\smile.pdb" /machine:I386 /def:".\Smile.def" /out:"$(OUTDIR)\smile.ocx" /implib:"$(OUTDIR)\smile.lib" 
DEF_FILE= \
	".\Smile.def"
LINK32_OBJS= \
	"$(INTDIR)\Smile.obj" \
	"$(INTDIR)\SmileCtl.obj" \
	"$(INTDIR)\SmilePpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Smile.res"

"$(OUTDIR)\smile.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\smile.ocx
InputPath=.\Release\smile.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Smile - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\smile.ocx" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Smile.obj"
	-@erase "$(INTDIR)\smile.pch"
	-@erase "$(INTDIR)\Smile.res"
	-@erase "$(INTDIR)\Smile.tlb"
	-@erase "$(INTDIR)\SmileCtl.obj"
	-@erase "$(INTDIR)\SmilePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\smile.exp"
	-@erase "$(OUTDIR)\smile.ilk"
	-@erase "$(OUTDIR)\smile.lib"
	-@erase "$(OUTDIR)\smile.ocx"
	-@erase "$(OUTDIR)\smile.pdb"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\smile.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Smile.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\smile.pdb" /debug /machine:I386 /def:".\Smile.def" /out:"$(OUTDIR)\smile.ocx" /implib:"$(OUTDIR)\smile.lib" 
DEF_FILE= \
	".\Smile.def"
LINK32_OBJS= \
	"$(INTDIR)\Smile.obj" \
	"$(INTDIR)\SmileCtl.obj" \
	"$(INTDIR)\SmilePpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Smile.res"

"$(OUTDIR)\smile.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\smile.ocx
InputPath=.\Debug\smile.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Smile - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\smile.ocx" ".\.\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Smile.obj"
	-@erase "$(INTDIR)\smile.pch"
	-@erase "$(INTDIR)\Smile.res"
	-@erase "$(INTDIR)\Smile.tlb"
	-@erase "$(INTDIR)\SmileCtl.obj"
	-@erase "$(INTDIR)\SmilePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\smile.exp"
	-@erase "$(OUTDIR)\smile.ilk"
	-@erase "$(OUTDIR)\smile.lib"
	-@erase "$(OUTDIR)\smile.ocx"
	-@erase "$(OUTDIR)\smile.pdb"
	-@erase ".\.\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\smile.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Smile.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\smile.pdb" /debug /machine:I386 /def:".\Smile.def" /out:"$(OUTDIR)\smile.ocx" /implib:"$(OUTDIR)\smile.lib" 
DEF_FILE= \
	".\Smile.def"
LINK32_OBJS= \
	"$(INTDIR)\Smile.obj" \
	"$(INTDIR)\SmileCtl.obj" \
	"$(INTDIR)\SmilePpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Smile.res"

"$(OUTDIR)\smile.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\smile.ocx
InputPath=.\DebugU\smile.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Smile - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\smile.ocx" ".\.\ReleaseU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Smile.obj"
	-@erase "$(INTDIR)\smile.pch"
	-@erase "$(INTDIR)\Smile.res"
	-@erase "$(INTDIR)\Smile.tlb"
	-@erase "$(INTDIR)\SmileCtl.obj"
	-@erase "$(INTDIR)\SmilePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\smile.exp"
	-@erase "$(OUTDIR)\smile.lib"
	-@erase "$(OUTDIR)\smile.ocx"
	-@erase ".\.\ReleaseU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\smile.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Smile.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\smile.pdb" /machine:I386 /def:".\Smile.def" /out:"$(OUTDIR)\smile.ocx" /implib:"$(OUTDIR)\smile.lib" 
DEF_FILE= \
	".\Smile.def"
LINK32_OBJS= \
	"$(INTDIR)\Smile.obj" \
	"$(INTDIR)\SmileCtl.obj" \
	"$(INTDIR)\SmilePpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Smile.res"

"$(OUTDIR)\smile.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\ReleaseU
TargetPath=.\ReleaseU\smile.ocx
InputPath=.\ReleaseU\smile.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Smile - Win32 Static Release"

OUTDIR=.\StaticRelease
INTDIR=.\StaticRelease
# Begin Custom Macros
OutDir=.\StaticRelease
# End Custom Macros

ALL : "$(OUTDIR)\smile.ocx" ".\StaticRelease\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Smile.obj"
	-@erase "$(INTDIR)\smile.pch"
	-@erase "$(INTDIR)\Smile.res"
	-@erase "$(INTDIR)\Smile.tlb"
	-@erase "$(INTDIR)\SmileCtl.obj"
	-@erase "$(INTDIR)\SmilePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\smile.exp"
	-@erase "$(OUTDIR)\smile.lib"
	-@erase "$(OUTDIR)\smile.map"
	-@erase "$(OUTDIR)\smile.ocx"
	-@erase ".\StaticRelease\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\smile.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Smile.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\smile.pdb" /map:"$(INTDIR)\smile.map" /machine:I386 /def:".\Smile.def" /out:"$(OUTDIR)\smile.ocx" /implib:"$(OUTDIR)\smile.lib" /opt:icf,32 
DEF_FILE= \
	".\Smile.def"
LINK32_OBJS= \
	"$(INTDIR)\Smile.obj" \
	"$(INTDIR)\SmileCtl.obj" \
	"$(INTDIR)\SmilePpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Smile.res"

"$(OUTDIR)\smile.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\StaticRelease
TargetPath=.\StaticRelease\smile.ocx
InputPath=.\StaticRelease\smile.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Smile - Win32 Static Debug"

OUTDIR=.\StaticDebug
INTDIR=.\StaticDebug
# Begin Custom Macros
OutDir=.\StaticDebug
# End Custom Macros

ALL : "$(OUTDIR)\smile.ocx" ".\StaticDebug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Smile.obj"
	-@erase "$(INTDIR)\smile.pch"
	-@erase "$(INTDIR)\Smile.res"
	-@erase "$(INTDIR)\Smile.tlb"
	-@erase "$(INTDIR)\SmileCtl.obj"
	-@erase "$(INTDIR)\SmilePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\smile.exp"
	-@erase "$(OUTDIR)\smile.ilk"
	-@erase "$(OUTDIR)\smile.lib"
	-@erase "$(OUTDIR)\smile.map"
	-@erase "$(OUTDIR)\smile.ocx"
	-@erase "$(OUTDIR)\smile.pdb"
	-@erase ".\StaticDebug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\smile.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Smile.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\smile.pdb" /map:"$(INTDIR)\smile.map" /debug /machine:I386 /def:".\Smile.def" /out:"$(OUTDIR)\smile.ocx" /implib:"$(OUTDIR)\smile.lib" 
DEF_FILE= \
	".\Smile.def"
LINK32_OBJS= \
	"$(INTDIR)\Smile.obj" \
	"$(INTDIR)\SmileCtl.obj" \
	"$(INTDIR)\SmilePpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Smile.res"

"$(OUTDIR)\smile.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\StaticDebug
TargetPath=.\StaticDebug\smile.ocx
InputPath=.\StaticDebug\smile.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Smile - Win32 Static Release Runtime"

OUTDIR=.\RuntimeRelease
INTDIR=.\RuntimeRelease
# Begin Custom Macros
OutDir=.\RuntimeRelease
# End Custom Macros

ALL : "$(OUTDIR)\smile.ocx" ".\RuntimeRelease\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Smile.obj"
	-@erase "$(INTDIR)\smile.pch"
	-@erase "$(INTDIR)\Smile.res"
	-@erase "$(INTDIR)\Smile.tlb"
	-@erase "$(INTDIR)\SmileCtl.obj"
	-@erase "$(INTDIR)\SmilePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\smile.exp"
	-@erase "$(OUTDIR)\smile.lib"
	-@erase "$(OUTDIR)\smile.map"
	-@erase "$(OUTDIR)\smile.ocx"
	-@erase ".\RuntimeRelease\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /D "_RUNTIME" /Fp"$(INTDIR)\smile.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Smile.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\smile.pdb" /map:"$(INTDIR)\smile.map" /machine:I386 /def:".\Smile.def" /out:"$(OUTDIR)\smile.ocx" /implib:"$(OUTDIR)\smile.lib" /opt:icf,32 
DEF_FILE= \
	".\Smile.def"
LINK32_OBJS= \
	"$(INTDIR)\Smile.obj" \
	"$(INTDIR)\SmileCtl.obj" \
	"$(INTDIR)\SmilePpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Smile.res"

"$(OUTDIR)\smile.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\RuntimeRelease
TargetPath=.\RuntimeRelease\smile.ocx
InputPath=.\RuntimeRelease\smile.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Smile - Win32 Static Debug Runtime"

OUTDIR=.\RuntimeDebug
INTDIR=.\RuntimeDebug
# Begin Custom Macros
OutDir=.\RuntimeDebug
# End Custom Macros

ALL : "$(OUTDIR)\smile.ocx" ".\RuntimeDebug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Smile.obj"
	-@erase "$(INTDIR)\smile.pch"
	-@erase "$(INTDIR)\Smile.res"
	-@erase "$(INTDIR)\Smile.tlb"
	-@erase "$(INTDIR)\SmileCtl.obj"
	-@erase "$(INTDIR)\SmilePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\smile.exp"
	-@erase "$(OUTDIR)\smile.ilk"
	-@erase "$(OUTDIR)\smile.lib"
	-@erase "$(OUTDIR)\smile.map"
	-@erase "$(OUTDIR)\smile.ocx"
	-@erase "$(OUTDIR)\smile.pdb"
	-@erase ".\RuntimeDebug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /D "_RUNTIME" /Fp"$(INTDIR)\smile.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Smile.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\smile.pdb" /map:"$(INTDIR)\smile.map" /debug /machine:I386 /def:".\Smile.def" /out:"$(OUTDIR)\smile.ocx" /implib:"$(OUTDIR)\smile.lib" 
DEF_FILE= \
	".\Smile.def"
LINK32_OBJS= \
	"$(INTDIR)\Smile.obj" \
	"$(INTDIR)\SmileCtl.obj" \
	"$(INTDIR)\SmilePpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Smile.res"

"$(OUTDIR)\smile.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\RuntimeDebug
TargetPath=.\RuntimeDebug\smile.ocx
InputPath=.\RuntimeDebug\smile.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("smile.dep")
!INCLUDE "smile.dep"
!ELSE 
!MESSAGE Warning: cannot find "smile.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Smile - Win32 Release" || "$(CFG)" == "Smile - Win32 Debug" || "$(CFG)" == "Smile - Win32 Unicode Debug" || "$(CFG)" == "Smile - Win32 Unicode Release" || "$(CFG)" == "Smile - Win32 Static Release" || "$(CFG)" == "Smile - Win32 Static Debug" || "$(CFG)" == "Smile - Win32 Static Release Runtime" || "$(CFG)" == "Smile - Win32 Static Debug Runtime"
SOURCE=.\Smile.cpp

"$(INTDIR)\Smile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\smile.pch"


SOURCE=.\Smile.odl

!IF  "$(CFG)" == "Smile - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\Smile.tlb" /mktyplib203 /win32 

"$(OUTDIR)\Smile.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\Smile.tlb" /mktyplib203 /win32 

"$(OUTDIR)\Smile.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\Smile.tlb" /mktyplib203 /win32 

"$(OUTDIR)\Smile.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\Smile.tlb" /mktyplib203 /win32 

"$(OUTDIR)\Smile.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\Smile.tlb" /mktyplib203 /win32 

"$(OUTDIR)\Smile.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\Smile.tlb" /mktyplib203 /win32 

"$(OUTDIR)\Smile.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Release Runtime"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\Smile.tlb" /mktyplib203 /win32 

"$(OUTDIR)\Smile.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Debug Runtime"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\Smile.tlb" /mktyplib203 /win32 

"$(OUTDIR)\Smile.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Smile.rc

!IF  "$(CFG)" == "Smile - Win32 Release"


"$(INTDIR)\Smile.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Smile.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Smile.res" /i ".\Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Smile - Win32 Debug"


"$(INTDIR)\Smile.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Smile.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Smile.res" /i ".\Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Smile - Win32 Unicode Debug"


"$(INTDIR)\Smile.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Smile.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Smile.res" /i ".\DebugU" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Smile - Win32 Unicode Release"


"$(INTDIR)\Smile.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Smile.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Smile.res" /i ".\ReleaseU" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Release"


"$(INTDIR)\Smile.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Smile.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Smile.res" /i "StaticRelease" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Debug"


"$(INTDIR)\Smile.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Smile.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Smile.res" /i "StaticDebug" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Release Runtime"


"$(INTDIR)\Smile.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Smile.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Smile.res" /i "RuntimeRelease" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Debug Runtime"


"$(INTDIR)\Smile.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Smile.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Smile.res" /i "RuntimeDebug" /d "_DEBUG" $(SOURCE)


!ENDIF 

SOURCE=.\SmileCtl.cpp

"$(INTDIR)\SmileCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\smile.pch"


SOURCE=.\SmilePpg.cpp

"$(INTDIR)\SmilePpg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\smile.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Smile - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\smile.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\smile.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\smile.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\smile.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\smile.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\smile.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\smile.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\smile.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\smile.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\smile.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\smile.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\smile.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Release Runtime"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /D "_RUNTIME" /Fp"$(INTDIR)\smile.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\smile.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smile - Win32 Static Debug Runtime"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /D "_RUNTIME" /Fp"$(INTDIR)\smile.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\smile.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

