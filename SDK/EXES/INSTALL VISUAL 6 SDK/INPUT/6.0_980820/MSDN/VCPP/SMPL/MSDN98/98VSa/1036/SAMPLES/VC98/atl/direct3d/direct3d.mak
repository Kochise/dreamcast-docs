# Microsoft Developer Studio Generated NMAKE File, Based on Direct3D.dsp
!IF "$(CFG)" == ""
CFG=Direct3D - Win32 Release
!MESSAGE No configuration specified. Defaulting to Direct3D - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Direct3D - Win32 Release" && "$(CFG)" != "Direct3D - Win32 Debug" && "$(CFG)" != "Direct3D - Win32 Unicode Release" && "$(CFG)" != "Direct3D - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Direct3D.mak" CFG="Direct3D - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Direct3D - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Direct3D - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Direct3D - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Direct3D - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "Direct3D - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Direct3D.dll" ".\.\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\D3DAtl.obj"
	-@erase "$(INTDIR)\D3DWnd.obj"
	-@erase "$(INTDIR)\Direct3D.obj"
	-@erase "$(INTDIR)\Direct3D.pch"
	-@erase "$(INTDIR)\Direct3D.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Direct3D.dll"
	-@erase "$(OUTDIR)\Direct3D.exp"
	-@erase "$(OUTDIR)\Direct3D.lib"
	-@erase ".\.\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL_" /D "ATL_MIN_CRT" /D "_ATL_APARTMENT_THREADED" /Fp"$(INTDIR)\Direct3D.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Direct3D.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Direct3D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ddraw.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Direct3D.pdb" /machine:I386 /def:".\Direct3D.def" /out:"$(OUTDIR)\Direct3D.dll" /implib:"$(OUTDIR)\Direct3D.lib" 
DEF_FILE= \
	".\Direct3D.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Direct3D.obj" \
	"$(INTDIR)\D3DWnd.obj" \
	"$(INTDIR)\D3DAtl.obj" \
	"$(INTDIR)\Direct3D.res"

"$(OUTDIR)\Direct3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\Direct3D.dll
InputPath=.\Release\Direct3D.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"
<< 
	

!ELSEIF  "$(CFG)" == "Direct3D - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Direct3D.dll" "$(OUTDIR)\Direct3D.bsc" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\D3DAtl.obj"
	-@erase "$(INTDIR)\D3DAtl.sbr"
	-@erase "$(INTDIR)\D3DWnd.obj"
	-@erase "$(INTDIR)\D3DWnd.sbr"
	-@erase "$(INTDIR)\Direct3D.obj"
	-@erase "$(INTDIR)\Direct3D.pch"
	-@erase "$(INTDIR)\Direct3D.res"
	-@erase "$(INTDIR)\Direct3D.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Direct3D.bsc"
	-@erase "$(OUTDIR)\Direct3D.dll"
	-@erase "$(OUTDIR)\Direct3D.exp"
	-@erase "$(OUTDIR)\Direct3D.ilk"
	-@erase "$(OUTDIR)\Direct3D.lib"
	-@erase "$(OUTDIR)\Direct3D.pdb"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Direct3D.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Direct3D.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Direct3D.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Direct3D.sbr" \
	"$(INTDIR)\D3DWnd.sbr" \
	"$(INTDIR)\D3DAtl.sbr"

"$(OUTDIR)\Direct3D.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ddraw.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Direct3D.pdb" /debug /machine:I386 /def:".\Direct3D.def" /out:"$(OUTDIR)\Direct3D.dll" /implib:"$(OUTDIR)\Direct3D.lib" 
DEF_FILE= \
	".\Direct3D.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Direct3D.obj" \
	"$(INTDIR)\D3DWnd.obj" \
	"$(INTDIR)\D3DAtl.obj" \
	"$(INTDIR)\Direct3D.res"

"$(OUTDIR)\Direct3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\Direct3D.dll
InputPath=.\Debug\Direct3D.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"
<< 
	

!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\Direct3D.dll" ".\.\ReleaseU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\D3DAtl.obj"
	-@erase "$(INTDIR)\D3DWnd.obj"
	-@erase "$(INTDIR)\Direct3D.obj"
	-@erase "$(INTDIR)\Direct3D.pch"
	-@erase "$(INTDIR)\Direct3D.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Direct3D.dll"
	-@erase "$(OUTDIR)\Direct3D.exp"
	-@erase "$(OUTDIR)\Direct3D.lib"
	-@erase ".\.\ReleaseU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "_UNICODE" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL_" /D "ATL_MIN_CRT" /D "_ATL_APARTMENT_THREADED" /Fp"$(INTDIR)\Direct3D.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Direct3D.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Direct3D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ddraw.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Direct3D.pdb" /machine:I386 /def:".\Direct3D.def" /out:"$(OUTDIR)\Direct3D.dll" /implib:"$(OUTDIR)\Direct3D.lib" 
DEF_FILE= \
	".\Direct3D.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Direct3D.obj" \
	"$(INTDIR)\D3DWnd.obj" \
	"$(INTDIR)\D3DAtl.obj" \
	"$(INTDIR)\Direct3D.res"

"$(OUTDIR)\Direct3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\ReleaseU
TargetPath=.\ReleaseU\Direct3D.dll
InputPath=.\ReleaseU\Direct3D.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"
<< 
	

!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\Direct3D.dll" ".\.\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\D3DAtl.obj"
	-@erase "$(INTDIR)\D3DWnd.obj"
	-@erase "$(INTDIR)\Direct3D.obj"
	-@erase "$(INTDIR)\Direct3D.pch"
	-@erase "$(INTDIR)\Direct3D.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Direct3D.dll"
	-@erase "$(OUTDIR)\Direct3D.exp"
	-@erase "$(OUTDIR)\Direct3D.ilk"
	-@erase "$(OUTDIR)\Direct3D.lib"
	-@erase "$(OUTDIR)\Direct3D.pdb"
	-@erase ".\.\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Direct3D.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Direct3D.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Direct3D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ddraw.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Direct3D.pdb" /debug /machine:I386 /def:".\Direct3D.def" /out:"$(OUTDIR)\Direct3D.dll" /implib:"$(OUTDIR)\Direct3D.lib" 
DEF_FILE= \
	".\Direct3D.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Direct3D.obj" \
	"$(INTDIR)\D3DWnd.obj" \
	"$(INTDIR)\D3DAtl.obj" \
	"$(INTDIR)\Direct3D.res"

"$(OUTDIR)\Direct3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\Direct3D.dll
InputPath=.\DebugU\Direct3D.dll
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
!IF EXISTS("Direct3D.dep")
!INCLUDE "Direct3D.dep"
!ELSE 
!MESSAGE Warning: cannot find "Direct3D.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Direct3D - Win32 Release" || "$(CFG)" == "Direct3D - Win32 Debug" || "$(CFG)" == "Direct3D - Win32 Unicode Release" || "$(CFG)" == "Direct3D - Win32 Unicode Debug"
SOURCE=.\D3DAtl.cpp

!IF  "$(CFG)" == "Direct3D - Win32 Release"


"$(INTDIR)\D3DAtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Direct3D.pch" ".\Direct3D.h"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Debug"


"$(INTDIR)\D3DAtl.obj"	"$(INTDIR)\D3DAtl.sbr" : $(SOURCE) "$(INTDIR)" ".\Direct3D.h" "$(INTDIR)\Direct3D.pch"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Release"


"$(INTDIR)\D3DAtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Direct3D.pch" ".\Direct3D.h"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Debug"


"$(INTDIR)\D3DAtl.obj" : $(SOURCE) "$(INTDIR)" ".\Direct3D.h" "$(INTDIR)\Direct3D.pch"


!ENDIF 

SOURCE=.\D3DWnd.cpp

!IF  "$(CFG)" == "Direct3D - Win32 Release"


"$(INTDIR)\D3DWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Direct3D.pch"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Debug"


"$(INTDIR)\D3DWnd.obj"	"$(INTDIR)\D3DWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Direct3D.pch"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Release"


"$(INTDIR)\D3DWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Direct3D.pch"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Debug"


"$(INTDIR)\D3DWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Direct3D.pch"


!ENDIF 

SOURCE=.\Direct3D.cpp

!IF  "$(CFG)" == "Direct3D - Win32 Release"


"$(INTDIR)\Direct3D.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Direct3D.pch" ".\Direct3D.h" ".\Direct3D_i.c"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Debug"


"$(INTDIR)\Direct3D.obj"	"$(INTDIR)\Direct3D.sbr" : $(SOURCE) "$(INTDIR)" ".\Direct3D.h" ".\Direct3D_i.c" "$(INTDIR)\Direct3D.pch"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Release"


"$(INTDIR)\Direct3D.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Direct3D.pch" ".\Direct3D.h" ".\Direct3D_i.c"


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Debug"


"$(INTDIR)\Direct3D.obj" : $(SOURCE) "$(INTDIR)" ".\Direct3D.h" ".\Direct3D_i.c" "$(INTDIR)\Direct3D.pch"


!ENDIF 

SOURCE=.\Direct3D.idl

!IF  "$(CFG)" == "Direct3D - Win32 Release"

InputPath=.\Direct3D.idl

"Direct3D.tlb"	"Direct3D.h"	"Direct3D_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h Direct3D.h /iid Direct3D_i.c Direct3D.idl
<< 
	

!ELSEIF  "$(CFG)" == "Direct3D - Win32 Debug"

InputPath=.\Direct3D.idl

"Direct3D.tlb"	"Direct3D.h"	"Direct3D_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h Direct3D.h /iid Direct3D_i.c Direct3D.idl
<< 
	

!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Release"

InputPath=.\Direct3D.idl

"Direct3D.tlb"	"Direct3D.h"	"Direct3D_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h Direct3D.h /iid Direct3D_i.c Direct3D.idl
<< 
	

!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Debug"

InputPath=.\Direct3D.idl

"Direct3D.tlb"	"Direct3D.h"	"Direct3D_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h Direct3D.h /iid Direct3D_i.c Direct3D.idl
<< 
	

!ENDIF 

SOURCE=.\Direct3D.rc

"$(INTDIR)\Direct3D.res" : $(SOURCE) "$(INTDIR)" ".\Direct3D.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Direct3D - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL_" /D "ATL_MIN_CRT" /D "_ATL_APARTMENT_THREADED" /Fp"$(INTDIR)\Direct3D.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Direct3D.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Direct3D.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Direct3D.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "_UNICODE" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL_" /D "ATL_MIN_CRT" /D "_ATL_APARTMENT_THREADED" /Fp"$(INTDIR)\Direct3D.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Direct3D.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Direct3D - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Direct3D.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Direct3D.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

