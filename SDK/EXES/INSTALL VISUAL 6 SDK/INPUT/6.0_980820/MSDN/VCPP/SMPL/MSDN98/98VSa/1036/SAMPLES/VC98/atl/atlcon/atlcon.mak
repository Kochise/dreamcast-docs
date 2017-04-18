# Microsoft Developer Studio Generated NMAKE File, Based on AtlCon.dsp
!IF "$(CFG)" == ""
CFG=AtlCon - Win32 Release
!MESSAGE No configuration specified. Defaulting to AtlCon - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "AtlCon - Win32 Release" && "$(CFG)" != "AtlCon - Win32 MinCRT" && "$(CFG)" != "AtlCon - Win32 Debug" && "$(CFG)" != "AtlCon - Win32 Unicode Release" && "$(CFG)" != "AtlCon - Win32 Unicode MinCRT" && "$(CFG)" != "AtlCon - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AtlCon.mak" CFG="AtlCon - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AtlCon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AtlCon - Win32 MinCRT" (based on "Win32 (x86) Application")
!MESSAGE "AtlCon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "AtlCon - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "AtlCon - Win32 Unicode MinCRT" (based on "Win32 (x86) Application")
!MESSAGE "AtlCon - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "AtlCon - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\AtlCon.exe"


CLEAN :
	-@erase "$(INTDIR)\AtlCon.obj"
	-@erase "$(INTDIR)\AtlCon.pch"
	-@erase "$(INTDIR)\AtlCon.res"
	-@erase "$(INTDIR)\AtlCon1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlCon.exe"
	-@erase ".\AtlCon.h"
	-@erase ".\AtlCon.tlb"
	-@erase ".\AtlCon_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\AtlCon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlCon.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlCon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledlg.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\AtlCon.pdb" /machine:I386 /out:"$(OUTDIR)\AtlCon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AtlCon.obj" \
	"$(INTDIR)\AtlCon1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlCon.res"

"$(OUTDIR)\AtlCon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AtlCon - Win32 MinCRT"

OUTDIR=.\MinRel
INTDIR=.\MinRel
# Begin Custom Macros
OutDir=.\MinRel
# End Custom Macros

ALL : "$(OUTDIR)\AtlCon.exe" ".\AtlCon.tlb" ".\AtlCon.h" ".\AtlCon_i.c"


CLEAN :
	-@erase "$(INTDIR)\AtlCon.obj"
	-@erase "$(INTDIR)\AtlCon.pch"
	-@erase "$(INTDIR)\AtlCon.res"
	-@erase "$(INTDIR)\AtlCon1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlCon.exe"
	-@erase ".\AtlCon.h"
	-@erase ".\AtlCon.tlb"
	-@erase ".\AtlCon_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlCon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlCon.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlCon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledlg.lib /nologo /entry:"WinMain" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\AtlCon.pdb" /machine:I386 /out:"$(OUTDIR)\AtlCon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AtlCon.obj" \
	"$(INTDIR)\AtlCon1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlCon.res"

"$(OUTDIR)\AtlCon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AtlCon - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\AtlCon.exe" ".\AtlCon.tlb" ".\AtlCon.h" ".\AtlCon_i.c"


CLEAN :
	-@erase "$(INTDIR)\AtlCon.obj"
	-@erase "$(INTDIR)\AtlCon.pch"
	-@erase "$(INTDIR)\AtlCon.res"
	-@erase "$(INTDIR)\AtlCon1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AtlCon.exe"
	-@erase "$(OUTDIR)\AtlCon.ilk"
	-@erase "$(OUTDIR)\AtlCon.pdb"
	-@erase ".\AtlCon.h"
	-@erase ".\AtlCon.tlb"
	-@erase ".\AtlCon_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\AtlCon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlCon.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlCon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledlg.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\AtlCon.pdb" /debug /machine:I386 /out:"$(OUTDIR)\AtlCon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AtlCon.obj" \
	"$(INTDIR)\AtlCon1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlCon.res"

"$(OUTDIR)\AtlCon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\AtlCon.exe" ".\AtlCon.tlb" ".\AtlCon.h" ".\AtlCon_i.c"


CLEAN :
	-@erase "$(INTDIR)\AtlCon.obj"
	-@erase "$(INTDIR)\AtlCon.pch"
	-@erase "$(INTDIR)\AtlCon.res"
	-@erase "$(INTDIR)\AtlCon1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlCon.exe"
	-@erase ".\AtlCon.h"
	-@erase ".\AtlCon.tlb"
	-@erase ".\AtlCon_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\AtlCon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlCon.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlCon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledlg.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\AtlCon.pdb" /machine:I386 /out:"$(OUTDIR)\AtlCon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AtlCon.obj" \
	"$(INTDIR)\AtlCon1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlCon.res"

"$(OUTDIR)\AtlCon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode MinCRT"

OUTDIR=.\MinRelU
INTDIR=.\MinRelU
# Begin Custom Macros
OutDir=.\MinRelU
# End Custom Macros

ALL : "$(OUTDIR)\AtlCon.exe" ".\AtlCon.tlb" ".\AtlCon.h" ".\AtlCon_i.c"


CLEAN :
	-@erase "$(INTDIR)\AtlCon.obj"
	-@erase "$(INTDIR)\AtlCon.pch"
	-@erase "$(INTDIR)\AtlCon.res"
	-@erase "$(INTDIR)\AtlCon1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlCon.exe"
	-@erase ".\AtlCon.h"
	-@erase ".\AtlCon.tlb"
	-@erase ".\AtlCon_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlCon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlCon.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlCon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledlg.lib /nologo /entry:"wWinMain" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\AtlCon.pdb" /machine:I386 /out:"$(OUTDIR)\AtlCon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AtlCon.obj" \
	"$(INTDIR)\AtlCon1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlCon.res"

"$(OUTDIR)\AtlCon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\AtlCon.exe"


CLEAN :
	-@erase "$(INTDIR)\AtlCon.obj"
	-@erase "$(INTDIR)\AtlCon.pch"
	-@erase "$(INTDIR)\AtlCon.res"
	-@erase "$(INTDIR)\AtlCon1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AtlCon.exe"
	-@erase "$(OUTDIR)\AtlCon.ilk"
	-@erase "$(OUTDIR)\AtlCon.pdb"
	-@erase ".\AtlCon.h"
	-@erase ".\AtlCon.tlb"
	-@erase ".\AtlCon_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\AtlCon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlCon.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlCon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledlg.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\AtlCon.pdb" /debug /machine:I386 /out:"$(OUTDIR)\AtlCon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AtlCon.obj" \
	"$(INTDIR)\AtlCon1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlCon.res"

"$(OUTDIR)\AtlCon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("AtlCon.dep")
!INCLUDE "AtlCon.dep"
!ELSE 
!MESSAGE Warning: cannot find "AtlCon.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AtlCon - Win32 Release" || "$(CFG)" == "AtlCon - Win32 MinCRT" || "$(CFG)" == "AtlCon - Win32 Debug" || "$(CFG)" == "AtlCon - Win32 Unicode Release" || "$(CFG)" == "AtlCon - Win32 Unicode MinCRT" || "$(CFG)" == "AtlCon - Win32 Unicode Debug"
SOURCE=.\AtlCon.cpp

"$(INTDIR)\AtlCon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlCon.pch" ".\AtlCon.h" ".\AtlCon_i.c"


SOURCE=.\AtlCon.idl

!IF  "$(CFG)" == "AtlCon - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./AtlCon.tlb" /h "AtlCon.h" /iid "AtlCon_i.c" /win32 

".\AtlCon.tlb"	".\AtlCon.h"	".\AtlCon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 MinCRT"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./AtlCon.tlb" /h "AtlCon.h" /iid "AtlCon_i.c" /win32 

".\AtlCon.tlb"	".\AtlCon.h"	".\AtlCon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "./AtlCon.tlb" /h "AtlCon.h" /iid "AtlCon_i.c" /win32 

".\AtlCon.tlb"	".\AtlCon.h"	".\AtlCon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./AtlCon.tlb" /h "AtlCon.h" /iid "AtlCon_i.c" /win32 

".\AtlCon.tlb"	".\AtlCon.h"	".\AtlCon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode MinCRT"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./AtlCon.tlb" /h "AtlCon.h" /iid "AtlCon_i.c" /win32 

".\AtlCon.tlb"	".\AtlCon.h"	".\AtlCon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "./AtlCon.tlb" /h "AtlCon.h" /iid "AtlCon_i.c" /win32 

".\AtlCon.tlb"	".\AtlCon.h"	".\AtlCon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\AtlCon.rc

"$(INTDIR)\AtlCon.res" : $(SOURCE) "$(INTDIR)" ".\AtlCon.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\AtlCon1.cpp

"$(INTDIR)\AtlCon1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlCon.pch" ".\AtlCon.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "AtlCon - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\AtlCon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlCon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 MinCRT"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlCon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlCon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\AtlCon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlCon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\AtlCon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlCon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode MinCRT"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlCon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlCon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlCon - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\AtlCon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlCon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

