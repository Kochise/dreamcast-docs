# Microsoft Developer Studio Generated NMAKE File, Based on AtlGLWorld.dsp
!IF "$(CFG)" == ""
CFG=AtlGLWorld - Win32 Debug
!MESSAGE No configuration specified. Defaulting to AtlGLWorld - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AtlGLWorld - Win32 Debug" && "$(CFG)" != "AtlGLWorld - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AtlGLWorld.mak" CFG="AtlGLWorld - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AtlGLWorld - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AtlGLWorld - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "AtlGLWorld - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\AtlGLWorld.dll" "$(OUTDIR)\AtlGLWorld.bsc" ".\Debug\regsvr32.trg"

!ELSE 

ALL : "ATLGdiWorld - Win32 Debug" "$(OUTDIR)\AtlGLWorld.dll" "$(OUTDIR)\AtlGLWorld.bsc" ".\Debug\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ATLGdiWorld - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AtlGLWorld.obj"
	-@erase "$(INTDIR)\AtlGLWorld.pch"
	-@erase "$(INTDIR)\AtlGLWorld.res"
	-@erase "$(INTDIR)\AtlGLWorld.sbr"
	-@erase "$(INTDIR)\AtlGLWorldImpl.obj"
	-@erase "$(INTDIR)\AtlGLWorldImpl.sbr"
	-@erase "$(INTDIR)\AtlTangramGLVisual.obj"
	-@erase "$(INTDIR)\AtlTangramGLVisual.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AtlGLWorld.bsc"
	-@erase "$(OUTDIR)\AtlGLWorld.dll"
	-@erase "$(OUTDIR)\AtlGLWorld.exp"
	-@erase "$(OUTDIR)\AtlGLWorld.ilk"
	-@erase "$(OUTDIR)\AtlGLWorld.lib"
	-@erase "$(OUTDIR)\AtlGLWorld.pdb"
	-@erase ".\AtlGLWorld.h"
	-@erase ".\AtlGLWorld.tlb"
	-@erase ".\AtlGLWorld_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\ATLModel" /I "..\ATLTangramCanvas" /I "..\\" /I "..\ATLGdiWorld" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\AtlGLWorld.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlGLWorld.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlGLWorld.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AtlGLWorld.sbr" \
	"$(INTDIR)\AtlGLWorldImpl.sbr" \
	"$(INTDIR)\AtlTangramGLVisual.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\AtlGLWorld.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\AtlGLWorld.pdb" /debug /machine:I386 /def:".\AtlGLWorld.def" /out:"$(OUTDIR)\AtlGLWorld.dll" /implib:"$(OUTDIR)\AtlGLWorld.lib" /pdbtype:sept 
DEF_FILE= \
	".\AtlGLWorld.def"
LINK32_OBJS= \
	"$(INTDIR)\AtlGLWorld.obj" \
	"$(INTDIR)\AtlGLWorldImpl.obj" \
	"$(INTDIR)\AtlTangramGLVisual.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlGLWorld.res" \
	"..\ATLGdiWorld\Debug\ATLGdiWorld.lib"

"$(OUTDIR)\AtlGLWorld.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\AtlGLWorld.dll
InputPath=.\Debug\AtlGLWorld.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AtlGLWorld - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\AtlGLWorld.dll" ".\AtlGLWorld_i.c" ".\AtlGLWorld.h" ".\AtlGLWorld.tlb" ".\Release\regsvr32.trg"

!ELSE 

ALL : "ATLGdiWorld - Win32 Release" "$(OUTDIR)\AtlGLWorld.dll" ".\AtlGLWorld_i.c" ".\AtlGLWorld.h" ".\AtlGLWorld.tlb" ".\Release\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ATLGdiWorld - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AtlGLWorld.obj"
	-@erase "$(INTDIR)\AtlGLWorld.pch"
	-@erase "$(INTDIR)\AtlGLWorld.res"
	-@erase "$(INTDIR)\AtlGLWorldImpl.obj"
	-@erase "$(INTDIR)\AtlTangramGLVisual.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlGLWorld.dll"
	-@erase "$(OUTDIR)\AtlGLWorld.exp"
	-@erase "$(OUTDIR)\AtlGLWorld.lib"
	-@erase ".\AtlGLWorld.h"
	-@erase ".\AtlGLWorld.tlb"
	-@erase ".\AtlGLWorld_i.c"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\ATLModel" /I "..\ATLTangramCanvas" /I "..\\" /I "..\ATLGdiWorld" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_DLL" /Fp"$(INTDIR)\AtlGLWorld.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlGLWorld.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlGLWorld.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\AtlGLWorld.pdb" /machine:I386 /def:".\AtlGLWorld.def" /out:"$(OUTDIR)\AtlGLWorld.dll" /implib:"$(OUTDIR)\AtlGLWorld.lib" 
DEF_FILE= \
	".\AtlGLWorld.def"
LINK32_OBJS= \
	"$(INTDIR)\AtlGLWorld.obj" \
	"$(INTDIR)\AtlGLWorldImpl.obj" \
	"$(INTDIR)\AtlTangramGLVisual.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlGLWorld.res" \
	"..\ATLGdiWorld\Release\ATLGdiWorld.lib"

"$(OUTDIR)\AtlGLWorld.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\AtlGLWorld.dll
InputPath=.\Release\AtlGLWorld.dll
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
!IF EXISTS("AtlGLWorld.dep")
!INCLUDE "AtlGLWorld.dep"
!ELSE 
!MESSAGE Warning: cannot find "AtlGLWorld.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AtlGLWorld - Win32 Debug" || "$(CFG)" == "AtlGLWorld - Win32 Release"
SOURCE=.\AtlGLWorld.cpp

!IF  "$(CFG)" == "AtlGLWorld - Win32 Debug"


"$(INTDIR)\AtlGLWorld.obj"	"$(INTDIR)\AtlGLWorld.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlGLWorld.pch" ".\AtlGLWorld.h" ".\AtlGLWorld_i.c"


!ELSEIF  "$(CFG)" == "AtlGLWorld - Win32 Release"


"$(INTDIR)\AtlGLWorld.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlGLWorld.pch"


!ENDIF 

SOURCE=.\AtlGLWorld.idl

!IF  "$(CFG)" == "AtlGLWorld - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\AtlGLWorld.tlb" /h "AtlGLWorld.h" /iid "AtlGLWorld_i.c" /o "NUL" /win32 

".\AtlGLWorld.tlb"	".\AtlGLWorld.h"	".\AtlGLWorld_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlGLWorld - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\AtlGLWorld.tlb" /h "AtlGLWorld.h" /iid "AtlGLWorld_i.c" /o "NUL" /win32 

".\AtlGLWorld.tlb"	".\AtlGLWorld.h"	".\AtlGLWorld_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\AtlGLWorld.rc

"$(INTDIR)\AtlGLWorld.res" : $(SOURCE) "$(INTDIR)" ".\AtlGLWorld.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\AtlGLWorldImpl.cpp

!IF  "$(CFG)" == "AtlGLWorld - Win32 Debug"


"$(INTDIR)\AtlGLWorldImpl.obj"	"$(INTDIR)\AtlGLWorldImpl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlGLWorld.pch" ".\AtlGLWorld.h"


!ELSEIF  "$(CFG)" == "AtlGLWorld - Win32 Release"


"$(INTDIR)\AtlGLWorldImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlGLWorld.pch"


!ENDIF 

SOURCE=.\AtlTangramGLVisual.cpp

!IF  "$(CFG)" == "AtlGLWorld - Win32 Debug"


"$(INTDIR)\AtlTangramGLVisual.obj"	"$(INTDIR)\AtlTangramGLVisual.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlGLWorld.pch" ".\AtlGLWorld.h"


!ELSEIF  "$(CFG)" == "AtlGLWorld - Win32 Release"


"$(INTDIR)\AtlTangramGLVisual.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlGLWorld.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "AtlGLWorld - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\ATLModel" /I "..\ATLTangramCanvas" /I "..\\" /I "..\ATLGdiWorld" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\AtlGLWorld.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\AtlGLWorld.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlGLWorld - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\ATLModel" /I "..\ATLTangramCanvas" /I "..\\" /I "..\ATLGdiWorld" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_DLL" /Fp"$(INTDIR)\AtlGLWorld.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlGLWorld.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "AtlGLWorld - Win32 Debug"

"ATLGdiWorld - Win32 Debug" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLGdiWorld"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLGdiWorld.mak CFG="ATLGdiWorld - Win32 Debug" 
   cd "..\AtlGLWorld"

"ATLGdiWorld - Win32 DebugCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLGdiWorld"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLGdiWorld.mak CFG="ATLGdiWorld - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\AtlGLWorld"

!ELSEIF  "$(CFG)" == "AtlGLWorld - Win32 Release"

"ATLGdiWorld - Win32 Release" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLGdiWorld"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLGdiWorld.mak CFG="ATLGdiWorld - Win32 Release" 
   cd "..\AtlGLWorld"

"ATLGdiWorld - Win32 ReleaseCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLGdiWorld"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLGdiWorld.mak CFG="ATLGdiWorld - Win32 Release" RECURSE=1 CLEAN 
   cd "..\AtlGLWorld"

!ENDIF 


!ENDIF 

