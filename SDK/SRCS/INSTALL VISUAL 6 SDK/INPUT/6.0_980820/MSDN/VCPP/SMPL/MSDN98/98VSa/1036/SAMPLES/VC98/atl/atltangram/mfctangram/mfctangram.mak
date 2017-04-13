# Microsoft Developer Studio Generated NMAKE File, Based on MFCTangram.dsp
!IF "$(CFG)" == ""
CFG=MFCTangram - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MFCTangram - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MFCTangram - Win32 Release" && "$(CFG)" != "MFCTangram - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MFCTangram.mak" CFG="MFCTangram - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MFCTangram - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MFCTangram - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "MFCTangram - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MFCTangram.exe" "$(OUTDIR)\MFCTangram.pch"

!ELSE 

ALL : "ATLModelExe - Win32 Release" "ATLModelps - Win32 Release" "AtlGLWorld - Win32 Release" "$(OUTDIR)\MFCTangram.exe" "$(OUTDIR)\MFCTangram.pch"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"AtlGLWorld - Win32 ReleaseCLEAN" "ATLModelps - Win32 ReleaseCLEAN" "ATLModelExe - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MFCTangram.obj"
	-@erase "$(INTDIR)\MFCTangram.pch"
	-@erase "$(INTDIR)\MFCTangram.res"
	-@erase "$(INTDIR)\MFCTangramConfigDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MFCTangram.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\ATLModel" /I "..\ATLTangramCanvas" /I "..\\" /I "..\ATLGdiWorld" /I "..\ATLGLWorld" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCTangram.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCTangram.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCTangram.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MFCTangram.pdb" /machine:I386 /out:"$(OUTDIR)\MFCTangram.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MFCTangram.obj" \
	"$(INTDIR)\MFCTangramConfigDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MFCTangram.res" \
	"..\AtlGLWorld\Release\AtlGLWorld.lib"

"$(OUTDIR)\MFCTangram.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
PostBuild_Desc=Registering proxy/stub dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "ATLModelExe - Win32 Release" "ATLModelps - Win32 Release" "AtlGLWorld - Win32 Release" "$(OUTDIR)\MFCTangram.exe" "$(OUTDIR)\MFCTangram.pch"
   regsvr32 /s /c ..\atlmodelps\atlmodelps.dll
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "MFCTangram - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MFCTangram.exe" "$(OUTDIR)\MFCTangram.pch" "$(OUTDIR)\MFCTangram.bsc"

!ELSE 

ALL : "ATLModelExe - Win32 Debug" "ATLModelps - Win32 Debug" "AtlGLWorld - Win32 Debug" "$(OUTDIR)\MFCTangram.exe" "$(OUTDIR)\MFCTangram.pch" "$(OUTDIR)\MFCTangram.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"AtlGLWorld - Win32 DebugCLEAN" "ATLModelps - Win32 DebugCLEAN" "ATLModelExe - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MFCTangram.obj"
	-@erase "$(INTDIR)\MFCTangram.pch"
	-@erase "$(INTDIR)\MFCTangram.res"
	-@erase "$(INTDIR)\MFCTangram.sbr"
	-@erase "$(INTDIR)\MFCTangramConfigDlg.obj"
	-@erase "$(INTDIR)\MFCTangramConfigDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MFCTangram.bsc"
	-@erase "$(OUTDIR)\MFCTangram.exe"
	-@erase "$(OUTDIR)\MFCTangram.ilk"
	-@erase "$(OUTDIR)\MFCTangram.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\ATLModel" /I "..\ATLTangramCanvas" /I "..\\" /I "..\ATLGdiWorld" /I "..\ATLGLWorld" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MFCTangram.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCTangram.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCTangram.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MFCTangram.sbr" \
	"$(INTDIR)\MFCTangramConfigDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\MFCTangram.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MFCTangram.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MFCTangram.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MFCTangram.obj" \
	"$(INTDIR)\MFCTangramConfigDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MFCTangram.res" \
	"..\AtlGLWorld\Debug\AtlGLWorld.lib"

"$(OUTDIR)\MFCTangram.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
PostBuild_Desc=Registering proxy/stub dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "ATLModelExe - Win32 Debug" "ATLModelps - Win32 Debug" "AtlGLWorld - Win32 Debug" "$(OUTDIR)\MFCTangram.exe" "$(OUTDIR)\MFCTangram.pch" "$(OUTDIR)\MFCTangram.bsc"
   regsvr32 /s /c ..\atlmodelps\atlmodelps.dll
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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MFCTangram.dep")
!INCLUDE "MFCTangram.dep"
!ELSE 
!MESSAGE Warning: cannot find "MFCTangram.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MFCTangram - Win32 Release" || "$(CFG)" == "MFCTangram - Win32 Debug"
SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "MFCTangram - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MFCTangram - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MFCTangram.cpp

!IF  "$(CFG)" == "MFCTangram - Win32 Release"


"$(INTDIR)\MFCTangram.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MFCTangram - Win32 Debug"


"$(INTDIR)\MFCTangram.obj"	"$(INTDIR)\MFCTangram.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MFCTangram.rc

"$(INTDIR)\MFCTangram.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MFCTangramConfigDlg.cpp

!IF  "$(CFG)" == "MFCTangram - Win32 Release"


"$(INTDIR)\MFCTangramConfigDlg.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MFCTangram - Win32 Debug"


"$(INTDIR)\MFCTangramConfigDlg.obj"	"$(INTDIR)\MFCTangramConfigDlg.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MFCTangram - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\ATLModel" /I "..\ATLTangramCanvas" /I "..\\" /I "..\ATLGdiWorld" /I "..\ATLGLWorld" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCTangram.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCTangram.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MFCTangram - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\ATLModel" /I "..\ATLTangramCanvas" /I "..\\" /I "..\ATLGdiWorld" /I "..\ATLGLWorld" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MFCTangram.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\MFCTangram.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "MFCTangram - Win32 Release"

"AtlGLWorld - Win32 Release" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\AtlGLWorld"
   $(MAKE) /$(MAKEFLAGS) /F .\AtlGLWorld.mak CFG="AtlGLWorld - Win32 Release" 
   cd "..\MFCTangram"

"AtlGLWorld - Win32 ReleaseCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\AtlGLWorld"
   $(MAKE) /$(MAKEFLAGS) /F .\AtlGLWorld.mak CFG="AtlGLWorld - Win32 Release" RECURSE=1 CLEAN 
   cd "..\MFCTangram"

!ELSEIF  "$(CFG)" == "MFCTangram - Win32 Debug"

"AtlGLWorld - Win32 Debug" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\AtlGLWorld"
   $(MAKE) /$(MAKEFLAGS) /F .\AtlGLWorld.mak CFG="AtlGLWorld - Win32 Debug" 
   cd "..\MFCTangram"

"AtlGLWorld - Win32 DebugCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\AtlGLWorld"
   $(MAKE) /$(MAKEFLAGS) /F .\AtlGLWorld.mak CFG="AtlGLWorld - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\MFCTangram"

!ENDIF 

!IF  "$(CFG)" == "MFCTangram - Win32 Release"

"ATLModelps - Win32 Release" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModelps"
   NMAKE /f ATLModelps.mak
   cd "..\MFCTangram"

"ATLModelps - Win32 ReleaseCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModelps"
   cd "..\MFCTangram"

!ELSEIF  "$(CFG)" == "MFCTangram - Win32 Debug"

"ATLModelps - Win32 Debug" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModelps"
   NMAKE /f ATLModelps.mak
   cd "..\MFCTangram"

"ATLModelps - Win32 DebugCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModelps"
   cd "..\MFCTangram"

!ENDIF 

!IF  "$(CFG)" == "MFCTangram - Win32 Release"

"ATLModelExe - Win32 Release" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModel"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModelExe.mak CFG="ATLModelExe - Win32 Release" 
   cd "..\MFCTangram"

"ATLModelExe - Win32 ReleaseCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModel"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModelExe.mak CFG="ATLModelExe - Win32 Release" RECURSE=1 CLEAN 
   cd "..\MFCTangram"

!ELSEIF  "$(CFG)" == "MFCTangram - Win32 Debug"

"ATLModelExe - Win32 Debug" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModel"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModelExe.mak CFG="ATLModelExe - Win32 Debug" 
   cd "..\MFCTangram"

"ATLModelExe - Win32 DebugCLEAN" : 
   cd "\Scorpio\Samples\ATL\ATLTangram\ATLModel"
   $(MAKE) /$(MAKEFLAGS) /F .\ATLModelExe.mak CFG="ATLModelExe - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\MFCTangram"

!ENDIF 


!ENDIF 

