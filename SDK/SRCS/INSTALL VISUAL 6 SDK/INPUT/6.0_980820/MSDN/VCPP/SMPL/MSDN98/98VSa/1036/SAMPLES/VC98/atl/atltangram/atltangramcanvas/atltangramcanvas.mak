# Microsoft Developer Studio Generated NMAKE File, Based on ATLTangramCanvas.dsp
!IF "$(CFG)" == ""
CFG=ATLTangramCanvas - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ATLTangramCanvas - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ATLTangramCanvas - Win32 Debug" && "$(CFG)" != "ATLTangramCanvas - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ATLTangramCanvas.mak" CFG="ATLTangramCanvas - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ATLTangramCanvas - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLTangramCanvas - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ATLTangramCanvas - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ATLTangramCanvas.dll" "$(OUTDIR)\ATLTangramCanvas.bsc" ".\Debug\regsvr32.trg"

!ELSE 

ALL : "ATLModel - Win32 Debug" "$(OUTDIR)\ATLTangramCanvas.dll" "$(OUTDIR)\ATLTangramCanvas.bsc" ".\Debug\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ATLModel - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ATLTangramCanvas.obj"
	-@erase "$(INTDIR)\ATLTangramCanvas.pch"
	-@erase "$(INTDIR)\ATLTangramCanvas.res"
	-@erase "$(INTDIR)\ATLTangramCanvas.sbr"
	-@erase "$(INTDIR)\AtlTangramCanvasImpl.obj"
	-@erase "$(INTDIR)\AtlTangramCanvasImpl.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ATLTangramCanvas.bsc"
	-@erase "$(OUTDIR)\ATLTangramCanvas.dll"
	-@erase "$(OUTDIR)\ATLTangramCanvas.exp"
	-@erase "$(OUTDIR)\ATLTangramCanvas.ilk"
	-@erase "$(OUTDIR)\ATLTangramCanvas.lib"
	-@erase "$(OUTDIR)\ATLTangramCanvas.pdb"
	-@erase ".\ATLTangramCanvas.h"
	-@erase ".\ATLTangramCanvas.tlb"
	-@erase ".\ATLTangramCanvas_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ATLTangramCanvas.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLTangramCanvas.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLTangramCanvas.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ATLTangramCanvas.sbr" \
	"$(INTDIR)\AtlTangramCanvasImpl.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ATLTangramCanvas.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ATLTangramCanvas.pdb" /debug /machine:I386 /def:".\ATLTangramCanvas.def" /out:"$(OUTDIR)\ATLTangramCanvas.dll" /implib:"$(OUTDIR)\ATLTangramCanvas.lib" /pdbtype:sept 
DEF_FILE= \
	".\ATLTangramCanvas.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLTangramCanvas.obj" \
	"$(INTDIR)\AtlTangramCanvasImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLTangramCanvas.res" \
	"..\ATLModel\Debug\ATLModel.lib"

"$(OUTDIR)\ATLTangramCanvas.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ATLTangramCanvas.dll
InputPath=.\Debug\ATLTangramCanvas.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLTangramCanvas - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ATLTangramCanvas.dll" ".\ATLTangramCanvas_i.c" ".\ATLTangramCanvas.h" ".\ATLTangramCanvas.tlb" ".\Release\regsvr32.trg"

!ELSE 

ALL : "ATLModel - Win32 Release" "$(OUTDIR)\ATLTangramCanvas.dll" ".\ATLTangramCanvas_i.c" ".\ATLTangramCanvas.h" ".\ATLTangramCanvas.tlb" ".\Release\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ATLModel - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ATLTangramCanvas.obj"
	-@erase "$(INTDIR)\ATLTangramCanvas.pch"
	-@erase "$(INTDIR)\ATLTangramCanvas.res"
	-@erase "$(INTDIR)\AtlTangramCanvasImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ATLTangramCanvas.dll"
	-@erase "$(OUTDIR)\ATLTangramCanvas.exp"
	-@erase "$(OUTDIR)\ATLTangramCanvas.lib"
	-@erase ".\ATLTangramCanvas.h"
	-@erase ".\ATLTangramCanvas.tlb"
	-@erase ".\ATLTangramCanvas_i.c"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_DLL" /Fp"$(INTDIR)\ATLTangramCanvas.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLTangramCanvas.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLTangramCanvas.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ATLTangramCanvas.pdb" /machine:I386 /def:".\ATLTangramCanvas.def" /out:"$(OUTDIR)\ATLTangramCanvas.dll" /implib:"$(OUTDIR)\ATLTangramCanvas.lib" 
DEF_FILE= \
	".\ATLTangramCanvas.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLTangramCanvas.obj" \
	"$(INTDIR)\AtlTangramCanvasImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLTangramCanvas.res" \
	"..\ATLModel\Release\ATLModel.lib"

"$(OUTDIR)\ATLTangramCanvas.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\ATLTangramCanvas.dll
InputPath=.\Release\ATLTangramCanvas.dll
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
!IF EXISTS("ATLTangramCanvas.dep")
!INCLUDE "ATLTangramCanvas.dep"
!ELSE 
!MESSAGE Warning: cannot find "ATLTangramCanvas.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ATLTangramCanvas - Win32 Debug" || "$(CFG)" == "ATLTangramCanvas - Win32 Release"
SOURCE=.\ATLTangramCanvas.cpp

!IF  "$(CFG)" == "ATLTangramCanvas - Win32 Debug"


"$(INTDIR)\ATLTangramCanvas.obj"	"$(INTDIR)\ATLTangramCanvas.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLTangramCanvas.pch" ".\ATLTangramCanvas.h" ".\ATLTangramCanvas_i.c"


!ELSEIF  "$(CFG)" == "ATLTangramCanvas - Win32 Release"


"$(INTDIR)\ATLTangramCanvas.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLTangramCanvas.pch"


!ENDIF 

SOURCE=.\ATLTangramCanvas.idl

!IF  "$(CFG)" == "ATLTangramCanvas - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\ATLTangramCanvas.tlb" /h "ATLTangramCanvas.h" /iid "ATLTangramCanvas_i.c" /o "NUL" /win32 

".\ATLTangramCanvas.tlb"	".\ATLTangramCanvas.h"	".\ATLTangramCanvas_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLTangramCanvas - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\ATLTangramCanvas.tlb" /h "ATLTangramCanvas.h" /iid "ATLTangramCanvas_i.c" /o "NUL" /win32 

".\ATLTangramCanvas.tlb"	".\ATLTangramCanvas.h"	".\ATLTangramCanvas_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ATLTangramCanvas.rc

"$(INTDIR)\ATLTangramCanvas.res" : $(SOURCE) "$(INTDIR)" ".\ATLTangramCanvas.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\AtlTangramCanvasImpl.cpp

!IF  "$(CFG)" == "ATLTangramCanvas - Win32 Debug"


"$(INTDIR)\AtlTangramCanvasImpl.obj"	"$(INTDIR)\AtlTangramCanvasImpl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLTangramCanvas.pch" ".\ATLTangramCanvas.h"


!ELSEIF  "$(CFG)" == "ATLTangramCanvas - Win32 Release"


"$(INTDIR)\AtlTangramCanvasImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLTangramCanvas.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ATLTangramCanvas - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ATLTangramCanvas.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ATLTangramCanvas.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLTangramCanvas - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_DLL" /Fp"$(INTDIR)\ATLTangramCanvas.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLTangramCanvas.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "ATLTangramCanvas - Win32 Debug"

"ATLModel - Win32 Debug" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModel"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModel.mak CFG="ATLModel - Win32 Debug" 
   cd "..\ATLTangramCanvas"

"ATLModel - Win32 DebugCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModel"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModel.mak CFG="ATLModel - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\ATLTangramCanvas"

!ELSEIF  "$(CFG)" == "ATLTangramCanvas - Win32 Release"

"ATLModel - Win32 Release" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModel"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModel.mak CFG="ATLModel - Win32 Release" 
   cd "..\ATLTangramCanvas"

"ATLModel - Win32 ReleaseCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModel"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModel.mak CFG="ATLModel - Win32 Release" RECURSE=1 CLEAN 
   cd "..\ATLTangramCanvas"

!ENDIF 


!ENDIF 

