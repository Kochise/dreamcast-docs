# Microsoft Developer Studio Generated NMAKE File, Based on dynabind.dsp
!IF "$(CFG)" == ""
CFG=Dynabind - Win32 Release
!MESSAGE No configuration specified. Defaulting to Dynabind - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Dynabind - Win32 Release" && "$(CFG)" != "Dynabind - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dynabind.mak" CFG="Dynabind - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dynabind - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Dynabind - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Dynabind - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\dynabind.exe"


CLEAN :
	-@erase "$(INTDIR)\addfield.obj"
	-@erase "$(INTDIR)\columnst.obj"
	-@erase "$(INTDIR)\coursset.obj"
	-@erase "$(INTDIR)\dynabind.pch"
	-@erase "$(INTDIR)\dynabind.res"
	-@erase "$(INTDIR)\enroldoc.obj"
	-@erase "$(INTDIR)\enroll.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\sectform.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dynabind.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dynabind.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dynabind.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dynabind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\dynabind.pdb" /machine:I386 /out:"$(OUTDIR)\dynabind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\addfield.obj" \
	"$(INTDIR)\columnst.obj" \
	"$(INTDIR)\coursset.obj" \
	"$(INTDIR)\enroldoc.obj" \
	"$(INTDIR)\enroll.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\sectform.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\dynabind.res"

"$(OUTDIR)\dynabind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dynabind - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\dynabind.exe"


CLEAN :
	-@erase "$(INTDIR)\addfield.obj"
	-@erase "$(INTDIR)\columnst.obj"
	-@erase "$(INTDIR)\coursset.obj"
	-@erase "$(INTDIR)\dynabind.pch"
	-@erase "$(INTDIR)\dynabind.res"
	-@erase "$(INTDIR)\enroldoc.obj"
	-@erase "$(INTDIR)\enroll.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\sectform.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\dynabind.exe"
	-@erase "$(OUTDIR)\dynabind.ilk"
	-@erase "$(OUTDIR)\dynabind.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dynabind.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dynabind.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dynabind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\dynabind.pdb" /debug /machine:I386 /out:"$(OUTDIR)\dynabind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\addfield.obj" \
	"$(INTDIR)\columnst.obj" \
	"$(INTDIR)\coursset.obj" \
	"$(INTDIR)\enroldoc.obj" \
	"$(INTDIR)\enroll.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\sectform.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\dynabind.res"

"$(OUTDIR)\dynabind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("dynabind.dep")
!INCLUDE "dynabind.dep"
!ELSE 
!MESSAGE Warning: cannot find "dynabind.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Dynabind - Win32 Release" || "$(CFG)" == "Dynabind - Win32 Debug"
SOURCE=.\addfield.cpp

"$(INTDIR)\addfield.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dynabind.pch"


SOURCE=.\columnst.cpp

"$(INTDIR)\columnst.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dynabind.pch"


SOURCE=.\coursset.cpp

"$(INTDIR)\coursset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dynabind.pch"


SOURCE=.\dynabind.rc

"$(INTDIR)\dynabind.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\enroldoc.cpp

"$(INTDIR)\enroldoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dynabind.pch"


SOURCE=.\enroll.cpp

"$(INTDIR)\enroll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dynabind.pch"


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dynabind.pch"


SOURCE=.\sectform.cpp

"$(INTDIR)\sectform.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dynabind.pch"


SOURCE=.\sectset.cpp

"$(INTDIR)\sectset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dynabind.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Dynabind - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dynabind.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\dynabind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Dynabind - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dynabind.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\dynabind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

