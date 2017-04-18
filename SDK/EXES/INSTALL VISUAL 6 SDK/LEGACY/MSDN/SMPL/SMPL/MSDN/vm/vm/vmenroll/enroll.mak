# Microsoft Developer Studio Generated NMAKE File, Based on enroll.dsp
!IF "$(CFG)" == ""
CFG=Enroll - Win32 Release
!MESSAGE No configuration specified.  Defaulting to Enroll - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Enroll - Win32 Release" && "$(CFG)" != "Enroll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
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
	-@erase "$(INTDIR)\addform.obj"
	-@erase "$(INTDIR)\coursset.obj"
	-@erase "$(INTDIR)\crsform.obj"
	-@erase "$(INTDIR)\enroldoc.obj"
	-@erase "$(INTDIR)\enroll.obj"
	-@erase "$(INTDIR)\enroll.pch"
	-@erase "$(INTDIR)\enroll.res"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\sectform.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(OUTDIR)\enroll.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/enroll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/enroll.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/enroll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/enroll.pdb" /machine:I386 /out:"$(OUTDIR)/enroll.exe" 
LINK32_OBJS= \
	"$(INTDIR)\addform.obj" \
	"$(INTDIR)\coursset.obj" \
	"$(INTDIR)\crsform.obj" \
	"$(INTDIR)\enroldoc.obj" \
	"$(INTDIR)\enroll.obj" \
	"$(INTDIR)\enroll.res" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\sectform.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj"

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
	-@erase "$(INTDIR)\addform.obj"
	-@erase "$(INTDIR)\coursset.obj"
	-@erase "$(INTDIR)\crsform.obj"
	-@erase "$(INTDIR)\enroldoc.obj"
	-@erase "$(INTDIR)\enroll.obj"
	-@erase "$(INTDIR)\enroll.pch"
	-@erase "$(INTDIR)\enroll.res"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\sectform.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\enroll.exe"
	-@erase "$(OUTDIR)\enroll.ilk"
	-@erase "$(OUTDIR)\enroll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/enroll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/enroll.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/enroll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/enroll.pdb" /debug /machine:I386 /out:"$(OUTDIR)/enroll.exe" 
LINK32_OBJS= \
	"$(INTDIR)\addform.obj" \
	"$(INTDIR)\coursset.obj" \
	"$(INTDIR)\crsform.obj" \
	"$(INTDIR)\enroldoc.obj" \
	"$(INTDIR)\enroll.obj" \
	"$(INTDIR)\enroll.res" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\sectform.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\enroll.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  


!IF "$(CFG)" == "Enroll - Win32 Release" || "$(CFG)" == "Enroll - Win32 Debug"
SOURCE=.\addform.cpp
DEP_CPP_ADDFO=\
	".\addform.h"\
	".\enroll.h"\
	".\stdafx.h"\
	

"$(INTDIR)\addform.obj" : $(SOURCE) $(DEP_CPP_ADDFO) "$(INTDIR)"\
 "$(INTDIR)\enroll.pch"


SOURCE=.\coursset.cpp
DEP_CPP_COURS=\
	".\coursset.h"\
	".\enroll.h"\
	".\stdafx.h"\
	

"$(INTDIR)\coursset.obj" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\enroll.pch"


SOURCE=.\crsform.cpp
DEP_CPP_CRSFO=\
	".\addform.h"\
	".\coursset.h"\
	".\crsform.h"\
	".\enroldoc.h"\
	".\enroll.h"\
	".\mainfrm.h"\
	".\sectset.h"\
	".\stdafx.h"\
	

"$(INTDIR)\crsform.obj" : $(SOURCE) $(DEP_CPP_CRSFO) "$(INTDIR)"\
 "$(INTDIR)\enroll.pch"


SOURCE=.\enroldoc.cpp
DEP_CPP_ENROL=\
	".\coursset.h"\
	".\enroldoc.h"\
	".\enroll.h"\
	".\sectset.h"\
	".\stdafx.h"\
	

"$(INTDIR)\enroldoc.obj" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\enroll.pch"


SOURCE=.\enroll.cpp
DEP_CPP_ENROLL=\
	".\addform.h"\
	".\coursset.h"\
	".\enroldoc.h"\
	".\enroll.h"\
	".\mainfrm.h"\
	".\sectform.h"\
	".\sectset.h"\
	".\stdafx.h"\
	

"$(INTDIR)\enroll.obj" : $(SOURCE) $(DEP_CPP_ENROLL) "$(INTDIR)"\
 "$(INTDIR)\enroll.pch"


SOURCE=.\enroll.rc
DEP_RSC_ENROLL_=\
	".\res\enroll.ico"\
	".\res\enroll.rc2"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\enroll.res" : $(SOURCE) $(DEP_RSC_ENROLL_) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\addform.h"\
	".\coursset.h"\
	".\crsform.h"\
	".\enroldoc.h"\
	".\enroll.h"\
	".\mainfrm.h"\
	".\sectform.h"\
	".\sectset.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\enroll.pch"


SOURCE=.\readme.txt
SOURCE=.\sectform.cpp
DEP_CPP_SECTF=\
	".\addform.h"\
	".\coursset.h"\
	".\enroldoc.h"\
	".\enroll.h"\
	".\mainfrm.h"\
	".\sectform.h"\
	".\sectset.h"\
	".\stdafx.h"\
	

"$(INTDIR)\sectform.obj" : $(SOURCE) $(DEP_CPP_SECTF) "$(INTDIR)"\
 "$(INTDIR)\enroll.pch"


SOURCE=.\sectset.cpp
DEP_CPP_SECTS=\
	".\enroll.h"\
	".\sectset.h"\
	".\stdafx.h"\
	

"$(INTDIR)\sectset.obj" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\enroll.pch"


SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Enroll - Win32 Release"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\enroll.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/enroll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Enroll - Win32 Debug"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\enroll.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/enroll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\addform.h
SOURCE=.\coursset.h
SOURCE=.\crsform.h
SOURCE=.\enroldoc.h
SOURCE=.\enroll.h
SOURCE=.\mainfrm.h
SOURCE=.\sectform.h
SOURCE=.\sectset.h
SOURCE=.\stdafx.h
SOURCE=.\res\enroll.ico
SOURCE=.\res\enroll.rc2
SOURCE=.\res\toolbar.bmp

!ENDIF 

