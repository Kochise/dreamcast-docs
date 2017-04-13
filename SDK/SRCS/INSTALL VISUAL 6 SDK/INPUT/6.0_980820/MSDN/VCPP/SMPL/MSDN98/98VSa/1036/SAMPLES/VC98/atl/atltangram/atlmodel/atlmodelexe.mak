# Microsoft Developer Studio Generated NMAKE File, Based on ATLModelExe.dsp
!IF "$(CFG)" == ""
CFG=ATLModelExe - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ATLModelExe - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ATLModelExe - Win32 Debug" && "$(CFG)" != "ATLModelExe - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ATLModelExe.mak" CFG="ATLModelExe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ATLModelExe - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLModelExe - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ATLModelExe - Win32 Debug"

OUTDIR=.\ATLModel
INTDIR=.\ATLModel
# Begin Custom Macros
OutDir=.\ATLModel
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\LocalDebug\ATLModelExe.exe" "$(OUTDIR)\ATLModelExe.bsc" ".\ATLModel\regsvr32.trg"

!ELSE 

ALL : "ATLModel - Win32 Debug" ".\LocalDebug\ATLModelExe.exe" "$(OUTDIR)\ATLModelExe.bsc" ".\ATLModel\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ATLModel - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ATLModel.obj"
	-@erase "$(INTDIR)\ATLModel.res"
	-@erase "$(INTDIR)\ATLModel.sbr"
	-@erase "$(INTDIR)\ATLModelExe.pch"
	-@erase "$(INTDIR)\ATLTangramModel.obj"
	-@erase "$(INTDIR)\ATLTangramModel.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ATLModelExe.bsc"
	-@erase "$(OUTDIR)\ATLModelExe.pdb"
	-@erase ".\LocalDebug\ATLModelExe.exe"
	-@erase ".\LocalDebug\ATLModelExe.ilk"
	-@erase ".\ATLModel\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LOCAL_SERVER" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ATLModelExe.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLModel.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLModelExe.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ATLModel.sbr" \
	"$(INTDIR)\ATLTangramModel.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ATLModelExe.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ATLModelExe.pdb" /debug /machine:I386 /out:"LocalDebug/ATLModelExe.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ATLModel.obj" \
	"$(INTDIR)\ATLTangramModel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLModel.res" \
	".\Debug\ATLModel.lib"

".\LocalDebug\ATLModelExe.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ATLModel
TargetPath=.\LocalDebug\ATLModelExe.exe
InputPath=.\LocalDebug\ATLModelExe.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)"  /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLModelExe - Win32 Release"

OUTDIR=.\ATLMode0
INTDIR=.\ATLMode0

!IF "$(RECURSE)" == "0" 

ALL : ".\LocalRelease\ATLModelExe.exe" ".\ATLMode0\regsvr32.trg"

!ELSE 

ALL : "ATLModel - Win32 Release" ".\LocalRelease\ATLModelExe.exe" ".\ATLMode0\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ATLModel - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ATLModel.obj"
	-@erase "$(INTDIR)\ATLModel.res"
	-@erase "$(INTDIR)\ATLModelExe.pch"
	-@erase "$(INTDIR)\ATLTangramModel.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase ".\LocalRelease\ATLModelExe.exe"
	-@erase ".\ATLMode0\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LOCAL_SERVER" /Fp"$(INTDIR)\ATLModelExe.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLModel.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLModelExe.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ATLModelExe.pdb" /machine:I386 /out:"LocalRelease/ATLModelExe.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ATLModel.obj" \
	"$(INTDIR)\ATLTangramModel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLModel.res" \
	".\Release\ATLModel.lib"

".\LocalRelease\ATLModelExe.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ATLMode0
TargetPath=.\LocalRelease\ATLModelExe.exe
InputPath=.\LocalRelease\ATLModelExe.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)"  /RegServer 
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
!IF EXISTS("ATLModelExe.dep")
!INCLUDE "ATLModelExe.dep"
!ELSE 
!MESSAGE Warning: cannot find "ATLModelExe.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ATLModelExe - Win32 Debug" || "$(CFG)" == "ATLModelExe - Win32 Release"
SOURCE=.\ATLModel.cpp

!IF  "$(CFG)" == "ATLModelExe - Win32 Debug"


"$(INTDIR)\ATLModel.obj"	"$(INTDIR)\ATLModel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLModelExe.pch"


!ELSEIF  "$(CFG)" == "ATLModelExe - Win32 Release"


"$(INTDIR)\ATLModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLModelExe.pch"


!ENDIF 

SOURCE=.\ATLModel.rc

"$(INTDIR)\ATLModel.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ATLTangramModel.cpp

!IF  "$(CFG)" == "ATLModelExe - Win32 Debug"


"$(INTDIR)\ATLTangramModel.obj"	"$(INTDIR)\ATLTangramModel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLModelExe.pch"


!ELSEIF  "$(CFG)" == "ATLModelExe - Win32 Release"


"$(INTDIR)\ATLTangramModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLModelExe.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ATLModelExe - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LOCAL_SERVER" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ATLModelExe.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ATLModelExe.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLModelExe - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LOCAL_SERVER" /Fp"$(INTDIR)\ATLModelExe.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLModelExe.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "ATLModelExe - Win32 Debug"

"ATLModel - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModel.mak CFG="ATLModel - Win32 Debug" 
   cd "."

"ATLModel - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModel.mak CFG="ATLModel - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "ATLModelExe - Win32 Release"

"ATLModel - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModel.mak CFG="ATLModel - Win32 Release" 
   cd "."

"ATLModel - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModel.mak CFG="ATLModel - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 

