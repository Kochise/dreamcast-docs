# Microsoft Developer Studio Generated NMAKE File, Based on ActiveDoc.dsp
!IF "$(CFG)" == ""
CFG=ActiveDoc - Win32 MinSize
!MESSAGE No configuration specified. Defaulting to ActiveDoc - Win32 MinSize.
!ENDIF 

!IF "$(CFG)" != "ActiveDoc - Win32 MinSize" && "$(CFG)" != "ActiveDoc - Win32 MinDep" && "$(CFG)" != "ActiveDoc - Win32 Debug" && "$(CFG)" != "ActiveDoc - Win32 Unicode MinSize" && "$(CFG)" != "ActiveDoc - Win32 Unicode MinDep" && "$(CFG)" != "ActiveDoc - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ActiveDoc.mak" CFG="ActiveDoc - Win32 MinSize"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ActiveDoc - Win32 MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ActiveDoc - Win32 MinDep" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ActiveDoc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ActiveDoc - Win32 Unicode MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ActiveDoc - Win32 Unicode MinDep" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ActiveDoc - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ActiveDoc - Win32 MinSize"

OUTDIR=.\MinSize
INTDIR=.\MinSize
# Begin Custom Macros
OutDir=.\.\MinSize
# End Custom Macros

ALL : "$(OUTDIR)\ActiveDoc.dll" ".\.\MinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ActiveCtl.obj"
	-@erase "$(INTDIR)\ActiveDoc.obj"
	-@erase "$(INTDIR)\ActiveDoc.pch"
	-@erase "$(INTDIR)\ActiveDoc.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ActiveDoc.dll"
	-@erase "$(OUTDIR)\ActiveDoc.exp"
	-@erase "$(OUTDIR)\ActiveDoc.lib"
	-@erase ".\ActiveDoc.h"
	-@erase ".\ActiveDoc.tlb"
	-@erase ".\ActiveDoc_i.c"
	-@erase ".\.\MinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\ActiveDoc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ActiveDoc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ActiveDoc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comctl32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ActiveDoc.pdb" /machine:I386 /def:".\ActiveDoc.def" /out:"$(OUTDIR)\ActiveDoc.dll" /implib:"$(OUTDIR)\ActiveDoc.lib" 
DEF_FILE= \
	".\ActiveDoc.def"
LINK32_OBJS= \
	"$(INTDIR)\ActiveCtl.obj" \
	"$(INTDIR)\ActiveDoc.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ActiveDoc.res"

"$(OUTDIR)\ActiveDoc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinSize
TargetPath=.\MinSize\ActiveDoc.dll
InputPath=.\MinSize\ActiveDoc.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 MinDep"

OUTDIR=.\MinDep
INTDIR=.\MinDep
# Begin Custom Macros
OutDir=.\.\MinDep
# End Custom Macros

ALL : "$(OUTDIR)\ActiveDoc.dll" ".\ActiveDoc_i.c" ".\ActiveDoc.h" ".\.\MinDep\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ActiveCtl.obj"
	-@erase "$(INTDIR)\ActiveDoc.obj"
	-@erase "$(INTDIR)\ActiveDoc.pch"
	-@erase "$(INTDIR)\ActiveDoc.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ActiveDoc.dll"
	-@erase "$(OUTDIR)\ActiveDoc.exp"
	-@erase "$(OUTDIR)\ActiveDoc.lib"
	-@erase ".\ActiveDoc.h"
	-@erase ".\ActiveDoc.tlb"
	-@erase ".\ActiveDoc_i.c"
	-@erase ".\.\MinDep\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ActiveDoc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ActiveDoc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ActiveDoc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comctl32.lib /nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ActiveDoc.pdb" /machine:I386 /def:".\ActiveDoc.def" /out:"$(OUTDIR)\ActiveDoc.dll" /implib:"$(OUTDIR)\ActiveDoc.lib" 
DEF_FILE= \
	".\ActiveDoc.def"
LINK32_OBJS= \
	"$(INTDIR)\ActiveCtl.obj" \
	"$(INTDIR)\ActiveDoc.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ActiveDoc.res"

"$(OUTDIR)\ActiveDoc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinDep
TargetPath=.\MinDep\ActiveDoc.dll
InputPath=.\MinDep\ActiveDoc.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ActiveDoc.dll" "$(OUTDIR)\ActiveDoc.bsc" ".\ActiveDoc_i.c" ".\ActiveDoc.h" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ActiveCtl.obj"
	-@erase "$(INTDIR)\ActiveCtl.sbr"
	-@erase "$(INTDIR)\ActiveDoc.obj"
	-@erase "$(INTDIR)\ActiveDoc.pch"
	-@erase "$(INTDIR)\ActiveDoc.res"
	-@erase "$(INTDIR)\ActiveDoc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ActiveDoc.bsc"
	-@erase "$(OUTDIR)\ActiveDoc.dll"
	-@erase "$(OUTDIR)\ActiveDoc.exp"
	-@erase "$(OUTDIR)\ActiveDoc.ilk"
	-@erase "$(OUTDIR)\ActiveDoc.lib"
	-@erase "$(OUTDIR)\ActiveDoc.pdb"
	-@erase ".\ActiveDoc.h"
	-@erase ".\ActiveDoc.tlb"
	-@erase ".\ActiveDoc_i.c"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ActiveDoc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ActiveDoc.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ActiveDoc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ActiveCtl.sbr" \
	"$(INTDIR)\ActiveDoc.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ActiveDoc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=comctl32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ActiveDoc.pdb" /debug /machine:I386 /def:".\ActiveDoc.def" /out:"$(OUTDIR)\ActiveDoc.dll" /implib:"$(OUTDIR)\ActiveDoc.lib" 
DEF_FILE= \
	".\ActiveDoc.def"
LINK32_OBJS= \
	"$(INTDIR)\ActiveCtl.obj" \
	"$(INTDIR)\ActiveDoc.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ActiveDoc.res"

"$(OUTDIR)\ActiveDoc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\ActiveDoc.dll
InputPath=.\Debug\ActiveDoc.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinSize"

OUTDIR=.\MinSizeU
INTDIR=.\MinSizeU
# Begin Custom Macros
OutDir=.\.\MinSizeU
# End Custom Macros

ALL : "$(OUTDIR)\ActiveDoc.dll" ".\ActiveDoc_i.c" ".\ActiveDoc.h" ".\.\MinSizeU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ActiveCtl.obj"
	-@erase "$(INTDIR)\ActiveDoc.obj"
	-@erase "$(INTDIR)\ActiveDoc.pch"
	-@erase "$(INTDIR)\ActiveDoc.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ActiveDoc.dll"
	-@erase "$(OUTDIR)\ActiveDoc.exp"
	-@erase "$(OUTDIR)\ActiveDoc.lib"
	-@erase ".\ActiveDoc.h"
	-@erase ".\ActiveDoc.tlb"
	-@erase ".\ActiveDoc_i.c"
	-@erase ".\.\MinSizeU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\ActiveDoc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ActiveDoc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ActiveDoc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comctl32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ActiveDoc.pdb" /machine:I386 /def:".\ActiveDoc.def" /out:"$(OUTDIR)\ActiveDoc.dll" /implib:"$(OUTDIR)\ActiveDoc.lib" 
DEF_FILE= \
	".\ActiveDoc.def"
LINK32_OBJS= \
	"$(INTDIR)\ActiveCtl.obj" \
	"$(INTDIR)\ActiveDoc.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ActiveDoc.res"

"$(OUTDIR)\ActiveDoc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinSizeU
TargetPath=.\MinSizeU\ActiveDoc.dll
InputPath=.\MinSizeU\ActiveDoc.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinDep"

OUTDIR=.\MinDepU
INTDIR=.\MinDepU
# Begin Custom Macros
OutDir=.\.\MinDepU
# End Custom Macros

ALL : "$(OUTDIR)\ActiveDoc.dll" ".\ActiveDoc_i.c" ".\ActiveDoc.h" ".\.\MinDepU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ActiveCtl.obj"
	-@erase "$(INTDIR)\ActiveDoc.obj"
	-@erase "$(INTDIR)\ActiveDoc.pch"
	-@erase "$(INTDIR)\ActiveDoc.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ActiveDoc.dll"
	-@erase "$(OUTDIR)\ActiveDoc.exp"
	-@erase "$(OUTDIR)\ActiveDoc.lib"
	-@erase ".\ActiveDoc.h"
	-@erase ".\ActiveDoc.tlb"
	-@erase ".\ActiveDoc_i.c"
	-@erase ".\.\MinDepU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ActiveDoc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ActiveDoc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ActiveDoc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comctl32.lib /nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ActiveDoc.pdb" /machine:I386 /def:".\ActiveDoc.def" /out:"$(OUTDIR)\ActiveDoc.dll" /implib:"$(OUTDIR)\ActiveDoc.lib" 
DEF_FILE= \
	".\ActiveDoc.def"
LINK32_OBJS= \
	"$(INTDIR)\ActiveCtl.obj" \
	"$(INTDIR)\ActiveDoc.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ActiveDoc.res"

"$(OUTDIR)\ActiveDoc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinDepU
TargetPath=.\MinDepU\ActiveDoc.dll
InputPath=.\MinDepU\ActiveDoc.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ActiveDoc.dll" ".\ActiveDoc_i.c" ".\ActiveDoc.h" ".\.\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ActiveCtl.obj"
	-@erase "$(INTDIR)\ActiveDoc.obj"
	-@erase "$(INTDIR)\ActiveDoc.pch"
	-@erase "$(INTDIR)\ActiveDoc.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ActiveDoc.dll"
	-@erase "$(OUTDIR)\ActiveDoc.exp"
	-@erase "$(OUTDIR)\ActiveDoc.ilk"
	-@erase "$(OUTDIR)\ActiveDoc.lib"
	-@erase "$(OUTDIR)\ActiveDoc.pdb"
	-@erase ".\ActiveDoc.h"
	-@erase ".\ActiveDoc.tlb"
	-@erase ".\ActiveDoc_i.c"
	-@erase ".\.\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\ActiveDoc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ActiveDoc.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ActiveDoc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comctl32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ActiveDoc.pdb" /debug /machine:I386 /def:".\ActiveDoc.def" /out:"$(OUTDIR)\ActiveDoc.dll" /implib:"$(OUTDIR)\ActiveDoc.lib" 
DEF_FILE= \
	".\ActiveDoc.def"
LINK32_OBJS= \
	"$(INTDIR)\ActiveCtl.obj" \
	"$(INTDIR)\ActiveDoc.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ActiveDoc.res"

"$(OUTDIR)\ActiveDoc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\ActiveDoc.dll
InputPath=.\DebugU\ActiveDoc.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ActiveDoc.dep")
!INCLUDE "ActiveDoc.dep"
!ELSE 
!MESSAGE Warning: cannot find "ActiveDoc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ActiveDoc - Win32 MinSize" || "$(CFG)" == "ActiveDoc - Win32 MinDep" || "$(CFG)" == "ActiveDoc - Win32 Debug" || "$(CFG)" == "ActiveDoc - Win32 Unicode MinSize" || "$(CFG)" == "ActiveDoc - Win32 Unicode MinDep" || "$(CFG)" == "ActiveDoc - Win32 Unicode Debug"
SOURCE=.\ActiveCtl.cpp

!IF  "$(CFG)" == "ActiveDoc - Win32 MinSize"


"$(INTDIR)\ActiveCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch" ".\ActiveDoc.h"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 MinDep"


"$(INTDIR)\ActiveCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Debug"


"$(INTDIR)\ActiveCtl.obj"	"$(INTDIR)\ActiveCtl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinSize"


"$(INTDIR)\ActiveCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinDep"


"$(INTDIR)\ActiveCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode Debug"


"$(INTDIR)\ActiveCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ENDIF 

SOURCE=.\ActiveDoc.cpp

!IF  "$(CFG)" == "ActiveDoc - Win32 MinSize"


"$(INTDIR)\ActiveDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch" ".\ActiveDoc_i.c" ".\ActiveDoc.h"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 MinDep"


"$(INTDIR)\ActiveDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Debug"


"$(INTDIR)\ActiveDoc.obj"	"$(INTDIR)\ActiveDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinSize"


"$(INTDIR)\ActiveDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinDep"


"$(INTDIR)\ActiveDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode Debug"


"$(INTDIR)\ActiveDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ActiveDoc.pch"


!ENDIF 

SOURCE=.\ActiveDoc.idl

!IF  "$(CFG)" == "ActiveDoc - Win32 MinSize"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./ActiveDoc.tlb" /h "ActiveDoc.h" /iid "ActiveDoc_i.c" /win32 

".\ActiveDoc.tlb"	".\ActiveDoc.h"	".\ActiveDoc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 MinDep"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./ActiveDoc.tlb" /h "ActiveDoc.h" /iid "ActiveDoc_i.c" /win32 

".\ActiveDoc.tlb"	".\ActiveDoc.h"	".\ActiveDoc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "./ActiveDoc.tlb" /h "ActiveDoc.h" /iid "ActiveDoc_i.c" /win32 

".\ActiveDoc.tlb"	".\ActiveDoc.h"	".\ActiveDoc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinSize"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./ActiveDoc.tlb" /h "ActiveDoc.h" /iid "ActiveDoc_i.c" /win32 

".\ActiveDoc.tlb"	".\ActiveDoc.h"	".\ActiveDoc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinDep"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./ActiveDoc.tlb" /h "ActiveDoc.h" /iid "ActiveDoc_i.c" /win32 

".\ActiveDoc.tlb"	".\ActiveDoc.h"	".\ActiveDoc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "./ActiveDoc.tlb" /h "ActiveDoc.h" /iid "ActiveDoc_i.c" /win32 

".\ActiveDoc.tlb"	".\ActiveDoc.h"	".\ActiveDoc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ActiveDoc.rc

"$(INTDIR)\ActiveDoc.res" : $(SOURCE) "$(INTDIR)" ".\ActiveDoc.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ActiveDoc - Win32 MinSize"

CPP_SWITCHES=/nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\ActiveDoc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ActiveDoc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 MinDep"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ActiveDoc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ActiveDoc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ActiveDoc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ActiveDoc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinSize"

CPP_SWITCHES=/nologo /MD /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\ActiveDoc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ActiveDoc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode MinDep"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ActiveDoc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ActiveDoc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ActiveDoc - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\ActiveDoc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ActiveDoc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

