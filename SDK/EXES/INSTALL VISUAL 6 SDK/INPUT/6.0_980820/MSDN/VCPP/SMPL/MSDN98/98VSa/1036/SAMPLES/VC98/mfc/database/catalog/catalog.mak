# Microsoft Developer Studio Generated NMAKE File, Based on catalog.dsp
!IF "$(CFG)" == ""
CFG=Catalog - Win32 Release
!MESSAGE No configuration specified. Defaulting to Catalog - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Catalog - Win32 Release" && "$(CFG)" != "Catalog - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "catalog.mak" CFG="Catalog - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Catalog - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Catalog - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Catalog - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\catalog.exe"


CLEAN :
	-@erase "$(INTDIR)\cataldoc.obj"
	-@erase "$(INTDIR)\catalog.obj"
	-@erase "$(INTDIR)\catalog.pch"
	-@erase "$(INTDIR)\catalog.res"
	-@erase "$(INTDIR)\catalvw.obj"
	-@erase "$(INTDIR)\columnst.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tableset.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\catalog.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\catalog.pdb" /machine:I386 /out:"$(OUTDIR)\catalog.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cataldoc.obj" \
	"$(INTDIR)\catalog.obj" \
	"$(INTDIR)\catalvw.obj" \
	"$(INTDIR)\columnst.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tableset.obj" \
	"$(INTDIR)\catalog.res"

"$(OUTDIR)\catalog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Catalog - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\catalog.exe"


CLEAN :
	-@erase "$(INTDIR)\cataldoc.obj"
	-@erase "$(INTDIR)\catalog.obj"
	-@erase "$(INTDIR)\catalog.pch"
	-@erase "$(INTDIR)\catalog.res"
	-@erase "$(INTDIR)\catalvw.obj"
	-@erase "$(INTDIR)\columnst.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tableset.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\catalog.exe"
	-@erase "$(OUTDIR)\catalog.ilk"
	-@erase "$(OUTDIR)\catalog.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\catalog.pdb" /debug /machine:I386 /out:"$(OUTDIR)\catalog.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cataldoc.obj" \
	"$(INTDIR)\catalog.obj" \
	"$(INTDIR)\catalvw.obj" \
	"$(INTDIR)\columnst.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tableset.obj" \
	"$(INTDIR)\catalog.res"

"$(OUTDIR)\catalog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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
!IF EXISTS("catalog.dep")
!INCLUDE "catalog.dep"
!ELSE 
!MESSAGE Warning: cannot find "catalog.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Catalog - Win32 Release" || "$(CFG)" == "Catalog - Win32 Debug"
SOURCE=.\cataldoc.cpp

"$(INTDIR)\cataldoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog.pch"


SOURCE=.\catalog.cpp

"$(INTDIR)\catalog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog.pch"


SOURCE=.\catalog.rc

"$(INTDIR)\catalog.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\catalvw.cpp

"$(INTDIR)\catalvw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog.pch"


SOURCE=.\columnst.cpp

"$(INTDIR)\columnst.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog.pch"


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Catalog - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Catalog - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tableset.cpp

"$(INTDIR)\tableset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog.pch"



!ENDIF 

