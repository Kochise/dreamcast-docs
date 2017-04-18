# Microsoft Developer Studio Generated NMAKE File, Based on ATLModel.dsp
!IF "$(CFG)" == ""
CFG=ATLModel - Win32 Release
!MESSAGE No configuration specified. Defaulting to ATLModel - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ATLModel - Win32 Debug" && "$(CFG)" != "ATLModel - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ATLModel.mak" CFG="ATLModel - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ATLModel - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLModel - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ATLModel - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ATLModel.dll" "$(OUTDIR)\ATLModel.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLModel.obj"
	-@erase "$(INTDIR)\ATLModel.pch"
	-@erase "$(INTDIR)\ATLModel.res"
	-@erase "$(INTDIR)\ATLModel.sbr"
	-@erase "$(INTDIR)\ATLTangramModel.obj"
	-@erase "$(INTDIR)\ATLTangramModel.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ATLModel.bsc"
	-@erase "$(OUTDIR)\ATLModel.dll"
	-@erase "$(OUTDIR)\ATLModel.exp"
	-@erase "$(OUTDIR)\ATLModel.ilk"
	-@erase "$(OUTDIR)\ATLModel.lib"
	-@erase "$(OUTDIR)\ATLModel.pdb"
	-@erase ".\ATLModel.h"
	-@erase ".\ATLModel.tlb"
	-@erase ".\ATLModel_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ATLModel.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLModel.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ATLModel.sbr" \
	"$(INTDIR)\ATLTangramModel.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ATLModel.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ATLModel.pdb" /debug /machine:I386 /def:".\ATLModel.def" /out:"$(OUTDIR)\ATLModel.dll" /implib:"$(OUTDIR)\ATLModel.lib" /pdbtype:sept 
DEF_FILE= \
	".\ATLModel.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLModel.obj" \
	"$(INTDIR)\ATLTangramModel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLModel.res"

"$(OUTDIR)\ATLModel.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ATLModel.dll
InputPath=.\Debug\ATLModel.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	
SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ATLModel.dll" "$(OUTDIR)\ATLModel.bsc" ".\Debug\regsvr32.trg"
   copy dlldata.c ..\ATLModelps
	copy ATLModel_i.c ..\ATLModelps
	copy ATLModel_p.c ..\ATLModelps
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ATLModel - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ATLModel.dll" ".\ATLModel_i.c" ".\ATLModel.h" ".\ATLModel.tlb" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLModel.obj"
	-@erase "$(INTDIR)\ATLModel.pch"
	-@erase "$(INTDIR)\ATLModel.res"
	-@erase "$(INTDIR)\ATLTangramModel.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ATLModel.dll"
	-@erase "$(OUTDIR)\ATLModel.exp"
	-@erase "$(OUTDIR)\ATLModel.ilk"
	-@erase "$(OUTDIR)\ATLModel.lib"
	-@erase ".\ATLModel.h"
	-@erase ".\ATLModel.tlb"
	-@erase ".\ATLModel_i.c"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /O1 /I "..\\" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\ATLModel.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLModel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ATLModel.pdb" /machine:I386 /def:".\ATLModel.def" /out:"$(OUTDIR)\ATLModel.dll" /implib:"$(OUTDIR)\ATLModel.lib" /pdbtype:sept 
DEF_FILE= \
	".\ATLModel.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLModel.obj" \
	"$(INTDIR)\ATLTangramModel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLModel.res"

"$(OUTDIR)\ATLModel.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\ATLModel.dll
InputPath=.\Release\ATLModel.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	
SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ATLModel.dll" ".\ATLModel_i.c" ".\ATLModel.h" ".\ATLModel.tlb" ".\Release\regsvr32.trg"
   copy dlldata.c ..\ATLModelps
	copy ATLModel_i.c ..\ATLModelps
	copy ATLModel_p.c ..\ATLModelps
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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

MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLModel.res" /d "_DEBUG" 

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ATLModel.dep")
!INCLUDE "ATLModel.dep"
!ELSE 
!MESSAGE Warning: cannot find "ATLModel.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ATLModel - Win32 Debug" || "$(CFG)" == "ATLModel - Win32 Release"
SOURCE=.\ATLModel.cpp

!IF  "$(CFG)" == "ATLModel - Win32 Debug"


"$(INTDIR)\ATLModel.obj"	"$(INTDIR)\ATLModel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLModel.pch" ".\ATLModel.h" ".\ATLModel_i.c"


!ELSEIF  "$(CFG)" == "ATLModel - Win32 Release"


"$(INTDIR)\ATLModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLModel.pch"


!ENDIF 

SOURCE=.\ATLModel.idl
MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\ATLModel.tlb" /h "ATLModel.h" /iid "ATLModel_i.c" /o "NUL" /win32 

".\ATLModel.tlb"	".\ATLModel.h"	".\ATLModel_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\ATLModel.rc

"$(INTDIR)\ATLModel.res" : $(SOURCE) "$(INTDIR)" ".\ATLModel.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ATLTangramModel.cpp

!IF  "$(CFG)" == "ATLModel - Win32 Debug"


"$(INTDIR)\ATLTangramModel.obj"	"$(INTDIR)\ATLTangramModel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLModel.pch" ".\ATLModel.h"


!ELSEIF  "$(CFG)" == "ATLModel - Win32 Release"


"$(INTDIR)\ATLTangramModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLModel.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ATLModel - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ATLModel.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ATLModel.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLModel - Win32 Release"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /O1 /I "..\\" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\ATLModel.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLModel.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

