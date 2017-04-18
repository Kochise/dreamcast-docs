# Microsoft Developer Studio Generated NMAKE File, Based on enroll.dsp
!IF "$(CFG)" == ""
CFG=Enroll - Win32 Release
!MESSAGE No configuration specified. Defaulting to Enroll - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Enroll - Win32 Release" && "$(CFG)" != "Enroll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "enroll.mak" CFG="Enroll - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Enroll - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Enroll - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Enroll - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\enroll.exe"


CLEAN :
	-@erase "$(INTDIR)\enroldoc.obj"
	-@erase "$(INTDIR)\enroll.obj"
	-@erase "$(INTDIR)\enroll.pch"
	-@erase "$(INTDIR)\enroll.res"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\sectform.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\enroll.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\enroll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\enroll.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\enroll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\enroll.pdb" /machine:I386 /out:"$(OUTDIR)\enroll.exe" 
LINK32_OBJS= \
	"$(INTDIR)\enroldoc.obj" \
	"$(INTDIR)\enroll.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\sectform.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\enroll.res"

"$(OUTDIR)\enroll.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Enroll - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\enroll.exe"


CLEAN :
	-@erase "$(INTDIR)\enroldoc.obj"
	-@erase "$(INTDIR)\enroll.obj"
	-@erase "$(INTDIR)\enroll.pch"
	-@erase "$(INTDIR)\enroll.res"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\sectform.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\enroll.exe"
	-@erase "$(OUTDIR)\enroll.ilk"
	-@erase "$(OUTDIR)\enroll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\enroll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\enroll.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\enroll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\enroll.pdb" /debug /machine:I386 /out:"$(OUTDIR)\enroll.exe" 
LINK32_OBJS= \
	"$(INTDIR)\enroldoc.obj" \
	"$(INTDIR)\enroll.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\sectform.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\enroll.res"

"$(OUTDIR)\enroll.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("enroll.dep")
!INCLUDE "enroll.dep"
!ELSE 
!MESSAGE Warning: cannot find "enroll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Enroll - Win32 Release" || "$(CFG)" == "Enroll - Win32 Debug"
SOURCE=.\enroldoc.cpp

"$(INTDIR)\enroldoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\enroll.pch"


SOURCE=.\enroll.cpp

"$(INTDIR)\enroll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\enroll.pch"


SOURCE=.\enroll.rc

"$(INTDIR)\enroll.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\enroll.pch"


SOURCE=.\sectform.cpp

"$(INTDIR)\sectform.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\enroll.pch"


SOURCE=.\sectset.cpp

"$(INTDIR)\sectset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\enroll.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Enroll - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\enroll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\enroll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Enroll - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\enroll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\enroll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

