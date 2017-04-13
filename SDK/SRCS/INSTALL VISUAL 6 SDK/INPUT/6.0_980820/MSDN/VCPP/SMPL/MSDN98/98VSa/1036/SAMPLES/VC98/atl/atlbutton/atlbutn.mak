# Microsoft Developer Studio Generated NMAKE File, Based on atlbutn.dsp
!IF "$(CFG)" == ""
CFG=atlbutn - Win32 MinSize
!MESSAGE No configuration specified. Defaulting to atlbutn - Win32 MinSize.
!ENDIF 

!IF "$(CFG)" != "atlbutn - Win32 MinSize" && "$(CFG)" != "atlbutn - Win32 MinDep" && "$(CFG)" != "atlbutn - Win32 Debug" && "$(CFG)" != "atlbutn - Win32 Unicode MinSize" && "$(CFG)" != "atlbutn - Win32 Unicode MinDep" && "$(CFG)" != "atlbutn - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "atlbutn.mak" CFG="atlbutn - Win32 MinSize"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "atlbutn - Win32 MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atlbutn - Win32 MinDep" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atlbutn - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atlbutn - Win32 Unicode MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atlbutn - Win32 Unicode MinDep" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atlbutn - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "atlbutn - Win32 MinSize"

OUTDIR=.\MinSize
INTDIR=.\MinSize
# Begin Custom Macros
OutDir=.\.\MinSize
# End Custom Macros

ALL : "$(OUTDIR)\atlbutn.dll" "$(OUTDIR)\atlbutn.bsc" ".\.\MinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atlbutn.obj"
	-@erase "$(INTDIR)\atlbutn.pch"
	-@erase "$(INTDIR)\atlbutn.res"
	-@erase "$(INTDIR)\atlbutn.sbr"
	-@erase "$(INTDIR)\AtlButton.obj"
	-@erase "$(INTDIR)\AtlButton.sbr"
	-@erase "$(INTDIR)\dibapi.obj"
	-@erase "$(INTDIR)\dibapi.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\atlbutn.bsc"
	-@erase "$(OUTDIR)\atlbutn.dll"
	-@erase "$(OUTDIR)\atlbutn.exp"
	-@erase "$(OUTDIR)\atlbutn.lib"
	-@erase ".\atlbutn.h"
	-@erase ".\atlbutn.tlb"
	-@erase ".\atlbutn_i.c"
	-@erase ".\.\MinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\atlbutn.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atlbutn.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlbutn.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\atlbutn.sbr" \
	"$(INTDIR)\AtlButton.sbr" \
	"$(INTDIR)\dibapi.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\atlbutn.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\atlbutn.pdb" /machine:I386 /def:".\atlbutn.def" /out:"$(OUTDIR)\atlbutn.dll" /implib:"$(OUTDIR)\atlbutn.lib" 
DEF_FILE= \
	".\atlbutn.def"
LINK32_OBJS= \
	"$(INTDIR)\atlbutn.obj" \
	"$(INTDIR)\AtlButton.obj" \
	"$(INTDIR)\dibapi.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atlbutn.res"

"$(OUTDIR)\atlbutn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinSize
TargetPath=.\MinSize\atlbutn.dll
InputPath=.\MinSize\atlbutn.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "atlbutn - Win32 MinDep"

OUTDIR=.\MinDep
INTDIR=.\MinDep
# Begin Custom Macros
OutDir=.\.\MinDep
# End Custom Macros

ALL : "$(OUTDIR)\atlbutn.dll" ".\atlbutn.h" ".\atlbutn_i.c" ".\.\MinDep\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atlbutn.obj"
	-@erase "$(INTDIR)\atlbutn.pch"
	-@erase "$(INTDIR)\atlbutn.res"
	-@erase "$(INTDIR)\AtlButton.obj"
	-@erase "$(INTDIR)\dibapi.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\atlbutn.dll"
	-@erase "$(OUTDIR)\atlbutn.exp"
	-@erase "$(OUTDIR)\atlbutn.lib"
	-@erase ".\atlbutn.h"
	-@erase ".\atlbutn.tlb"
	-@erase ".\atlbutn_i.c"
	-@erase ".\.\MinDep\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\atlbutn.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atlbutn.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlbutn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\atlbutn.pdb" /machine:I386 /def:".\atlbutn.def" /out:"$(OUTDIR)\atlbutn.dll" /implib:"$(OUTDIR)\atlbutn.lib" 
DEF_FILE= \
	".\atlbutn.def"
LINK32_OBJS= \
	"$(INTDIR)\atlbutn.obj" \
	"$(INTDIR)\AtlButton.obj" \
	"$(INTDIR)\dibapi.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atlbutn.res"

"$(OUTDIR)\atlbutn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinDep
TargetPath=.\MinDep\atlbutn.dll
InputPath=.\MinDep\atlbutn.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "atlbutn - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\atlbutn.dll" ".\atlbutn.h" ".\atlbutn_i.c" "$(OUTDIR)\atlbutn.bsc" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atlbutn.obj"
	-@erase "$(INTDIR)\atlbutn.pch"
	-@erase "$(INTDIR)\atlbutn.res"
	-@erase "$(INTDIR)\atlbutn.sbr"
	-@erase "$(INTDIR)\AtlButton.obj"
	-@erase "$(INTDIR)\AtlButton.sbr"
	-@erase "$(INTDIR)\dibapi.obj"
	-@erase "$(INTDIR)\dibapi.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\atlbutn.bsc"
	-@erase "$(OUTDIR)\atlbutn.dll"
	-@erase "$(OUTDIR)\atlbutn.exp"
	-@erase "$(OUTDIR)\atlbutn.ilk"
	-@erase "$(OUTDIR)\atlbutn.lib"
	-@erase "$(OUTDIR)\atlbutn.pdb"
	-@erase ".\atlbutn.h"
	-@erase ".\atlbutn.tlb"
	-@erase ".\atlbutn_i.c"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\atlbutn.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atlbutn.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlbutn.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\atlbutn.sbr" \
	"$(INTDIR)\AtlButton.sbr" \
	"$(INTDIR)\dibapi.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\atlbutn.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\atlbutn.pdb" /debug /machine:I386 /def:".\atlbutn.def" /out:"$(OUTDIR)\atlbutn.dll" /implib:"$(OUTDIR)\atlbutn.lib" 
DEF_FILE= \
	".\atlbutn.def"
LINK32_OBJS= \
	"$(INTDIR)\atlbutn.obj" \
	"$(INTDIR)\AtlButton.obj" \
	"$(INTDIR)\dibapi.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atlbutn.res"

"$(OUTDIR)\atlbutn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\atlbutn.dll
InputPath=.\Debug\atlbutn.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinSize"

OUTDIR=.\MinSizeU
INTDIR=.\MinSizeU
# Begin Custom Macros
OutDir=.\.\MinSizeU
# End Custom Macros

ALL : "$(OUTDIR)\atlbutn.dll" ".\atlbutn.h" ".\atlbutn_i.c" ".\.\MinSizeU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atlbutn.obj"
	-@erase "$(INTDIR)\atlbutn.pch"
	-@erase "$(INTDIR)\atlbutn.res"
	-@erase "$(INTDIR)\AtlButton.obj"
	-@erase "$(INTDIR)\dibapi.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\atlbutn.dll"
	-@erase "$(OUTDIR)\atlbutn.exp"
	-@erase "$(OUTDIR)\atlbutn.lib"
	-@erase ".\atlbutn.h"
	-@erase ".\atlbutn.tlb"
	-@erase ".\atlbutn_i.c"
	-@erase ".\.\MinSizeU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\atlbutn.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atlbutn.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlbutn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\atlbutn.pdb" /machine:I386 /def:".\atlbutn.def" /out:"$(OUTDIR)\atlbutn.dll" /implib:"$(OUTDIR)\atlbutn.lib" 
DEF_FILE= \
	".\atlbutn.def"
LINK32_OBJS= \
	"$(INTDIR)\atlbutn.obj" \
	"$(INTDIR)\AtlButton.obj" \
	"$(INTDIR)\dibapi.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atlbutn.res"

"$(OUTDIR)\atlbutn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinSizeU
TargetPath=.\MinSizeU\atlbutn.dll
InputPath=.\MinSizeU\atlbutn.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinDep"

OUTDIR=.\MinDepU
INTDIR=.\MinDepU
# Begin Custom Macros
OutDir=.\.\MinDepU
# End Custom Macros

ALL : "$(OUTDIR)\atlbutn.dll" ".\atlbutn.h" ".\atlbutn_i.c" ".\.\MinDepU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atlbutn.obj"
	-@erase "$(INTDIR)\atlbutn.pch"
	-@erase "$(INTDIR)\atlbutn.res"
	-@erase "$(INTDIR)\AtlButton.obj"
	-@erase "$(INTDIR)\dibapi.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\atlbutn.dll"
	-@erase "$(OUTDIR)\atlbutn.exp"
	-@erase "$(OUTDIR)\atlbutn.lib"
	-@erase ".\atlbutn.h"
	-@erase ".\atlbutn.tlb"
	-@erase ".\atlbutn_i.c"
	-@erase ".\.\MinDepU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\atlbutn.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atlbutn.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlbutn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\atlbutn.pdb" /machine:I386 /def:".\atlbutn.def" /out:"$(OUTDIR)\atlbutn.dll" /implib:"$(OUTDIR)\atlbutn.lib" 
DEF_FILE= \
	".\atlbutn.def"
LINK32_OBJS= \
	"$(INTDIR)\atlbutn.obj" \
	"$(INTDIR)\AtlButton.obj" \
	"$(INTDIR)\dibapi.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atlbutn.res"

"$(OUTDIR)\atlbutn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinDepU
TargetPath=.\MinDepU\atlbutn.dll
InputPath=.\MinDepU\atlbutn.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\atlbutn.dll" ".\atlbutn.h" ".\atlbutn_i.c" ".\.\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atlbutn.obj"
	-@erase "$(INTDIR)\atlbutn.pch"
	-@erase "$(INTDIR)\atlbutn.res"
	-@erase "$(INTDIR)\AtlButton.obj"
	-@erase "$(INTDIR)\dibapi.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\atlbutn.dll"
	-@erase "$(OUTDIR)\atlbutn.exp"
	-@erase "$(OUTDIR)\atlbutn.ilk"
	-@erase "$(OUTDIR)\atlbutn.lib"
	-@erase "$(OUTDIR)\atlbutn.pdb"
	-@erase ".\atlbutn.h"
	-@erase ".\atlbutn.tlb"
	-@erase ".\atlbutn_i.c"
	-@erase ".\.\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\atlbutn.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atlbutn.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlbutn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\atlbutn.pdb" /debug /machine:I386 /def:".\atlbutn.def" /out:"$(OUTDIR)\atlbutn.dll" /implib:"$(OUTDIR)\atlbutn.lib" 
DEF_FILE= \
	".\atlbutn.def"
LINK32_OBJS= \
	"$(INTDIR)\atlbutn.obj" \
	"$(INTDIR)\AtlButton.obj" \
	"$(INTDIR)\dibapi.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atlbutn.res"

"$(OUTDIR)\atlbutn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\atlbutn.dll
InputPath=.\DebugU\atlbutn.dll
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
!IF EXISTS("atlbutn.dep")
!INCLUDE "atlbutn.dep"
!ELSE 
!MESSAGE Warning: cannot find "atlbutn.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "atlbutn - Win32 MinSize" || "$(CFG)" == "atlbutn - Win32 MinDep" || "$(CFG)" == "atlbutn - Win32 Debug" || "$(CFG)" == "atlbutn - Win32 Unicode MinSize" || "$(CFG)" == "atlbutn - Win32 Unicode MinDep" || "$(CFG)" == "atlbutn - Win32 Unicode Debug"
SOURCE=.\atlbutn.cpp

!IF  "$(CFG)" == "atlbutn - Win32 MinSize"


"$(INTDIR)\atlbutn.obj"	"$(INTDIR)\atlbutn.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch" ".\atlbutn.h" ".\atlbutn_i.c"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 MinDep"


"$(INTDIR)\atlbutn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Debug"


"$(INTDIR)\atlbutn.obj"	"$(INTDIR)\atlbutn.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinSize"


"$(INTDIR)\atlbutn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinDep"


"$(INTDIR)\atlbutn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode Debug"


"$(INTDIR)\atlbutn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ENDIF 

SOURCE=.\atlbutn.idl

!IF  "$(CFG)" == "atlbutn - Win32 MinSize"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./atlbutn.tlb" /h "atlbutn.h" /iid "atlbutn_i.c" /win32 

".\atlbutn.tlb"	".\atlbutn.h"	".\atlbutn_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 MinDep"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./atlbutn.tlb" /h "atlbutn.h" /iid "atlbutn_i.c" /win32 

".\atlbutn.tlb"	".\atlbutn.h"	".\atlbutn_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "./atlbutn.tlb" /h "atlbutn.h" /iid "atlbutn_i.c" /win32 

".\atlbutn.tlb"	".\atlbutn.h"	".\atlbutn_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinSize"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./atlbutn.tlb" /h "atlbutn.h" /iid "atlbutn_i.c" /win32 

".\atlbutn.tlb"	".\atlbutn.h"	".\atlbutn_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinDep"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./atlbutn.tlb" /h "atlbutn.h" /iid "atlbutn_i.c" /win32 

".\atlbutn.tlb"	".\atlbutn.h"	".\atlbutn_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "./atlbutn.tlb" /h "atlbutn.h" /iid "atlbutn_i.c" /win32 

".\atlbutn.tlb"	".\atlbutn.h"	".\atlbutn_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\atlbutn.rc

"$(INTDIR)\atlbutn.res" : $(SOURCE) "$(INTDIR)" ".\atlbutn.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\AtlButton.cpp

!IF  "$(CFG)" == "atlbutn - Win32 MinSize"


"$(INTDIR)\AtlButton.obj"	"$(INTDIR)\AtlButton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch" ".\atlbutn.h"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 MinDep"


"$(INTDIR)\AtlButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Debug"


"$(INTDIR)\AtlButton.obj"	"$(INTDIR)\AtlButton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinSize"


"$(INTDIR)\AtlButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinDep"


"$(INTDIR)\AtlButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode Debug"


"$(INTDIR)\AtlButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ENDIF 

SOURCE=.\dibapi.cpp

!IF  "$(CFG)" == "atlbutn - Win32 MinSize"


"$(INTDIR)\dibapi.obj"	"$(INTDIR)\dibapi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 MinDep"


"$(INTDIR)\dibapi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Debug"


"$(INTDIR)\dibapi.obj"	"$(INTDIR)\dibapi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinSize"


"$(INTDIR)\dibapi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinDep"


"$(INTDIR)\dibapi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode Debug"


"$(INTDIR)\dibapi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlbutn.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "atlbutn - Win32 MinSize"

CPP_SWITCHES=/nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\atlbutn.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\atlbutn.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 MinDep"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\atlbutn.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\atlbutn.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\atlbutn.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\atlbutn.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinSize"

CPP_SWITCHES=/nologo /MD /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\atlbutn.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\atlbutn.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode MinDep"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\atlbutn.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\atlbutn.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atlbutn - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\atlbutn.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\atlbutn.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

