# Microsoft Developer Studio Generated NMAKE File, Based on stdreg.dsp
!IF "$(CFG)" == ""
CFG=stdreg - Win32 Release
!MESSAGE No configuration specified. Defaulting to stdreg - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "stdreg - Win32 Release" && "$(CFG)" != "stdreg - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "stdreg.mak" CFG="stdreg - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "stdreg - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "stdreg - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "stdreg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\stdreg.exe"


CLEAN :
	-@erase "$(INTDIR)\columdlg.obj"
	-@erase "$(INTDIR)\coursset.obj"
	-@erase "$(INTDIR)\dialog.obj"
	-@erase "$(INTDIR)\dsectset.obj"
	-@erase "$(INTDIR)\enrolset.obj"
	-@erase "$(INTDIR)\instrset.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdreg.obj"
	-@erase "$(INTDIR)\stdreg.pch"
	-@erase "$(INTDIR)\stdreg.res"
	-@erase "$(INTDIR)\stdset.obj"
	-@erase "$(INTDIR)\typeinfo.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\stdreg.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\stdreg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\stdreg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stdreg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\stdreg.pdb" /machine:I386 /out:"$(OUTDIR)\stdreg.exe" 
LINK32_OBJS= \
	"$(INTDIR)\columdlg.obj" \
	"$(INTDIR)\coursset.obj" \
	"$(INTDIR)\dialog.obj" \
	"$(INTDIR)\dsectset.obj" \
	"$(INTDIR)\enrolset.obj" \
	"$(INTDIR)\instrset.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\stdreg.obj" \
	"$(INTDIR)\stdset.obj" \
	"$(INTDIR)\typeinfo.obj" \
	"$(INTDIR)\stdreg.res"

"$(OUTDIR)\stdreg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\stdreg.exe"


CLEAN :
	-@erase "$(INTDIR)\columdlg.obj"
	-@erase "$(INTDIR)\coursset.obj"
	-@erase "$(INTDIR)\dialog.obj"
	-@erase "$(INTDIR)\dsectset.obj"
	-@erase "$(INTDIR)\enrolset.obj"
	-@erase "$(INTDIR)\instrset.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdreg.obj"
	-@erase "$(INTDIR)\stdreg.pch"
	-@erase "$(INTDIR)\stdreg.res"
	-@erase "$(INTDIR)\stdset.obj"
	-@erase "$(INTDIR)\typeinfo.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\stdreg.exe"
	-@erase "$(OUTDIR)\stdreg.ilk"
	-@erase "$(OUTDIR)\stdreg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\stdreg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\stdreg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stdreg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\stdreg.pdb" /debug /machine:I386 /out:"$(OUTDIR)\stdreg.exe" 
LINK32_OBJS= \
	"$(INTDIR)\columdlg.obj" \
	"$(INTDIR)\coursset.obj" \
	"$(INTDIR)\dialog.obj" \
	"$(INTDIR)\dsectset.obj" \
	"$(INTDIR)\enrolset.obj" \
	"$(INTDIR)\instrset.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\stdreg.obj" \
	"$(INTDIR)\stdset.obj" \
	"$(INTDIR)\typeinfo.obj" \
	"$(INTDIR)\stdreg.res"

"$(OUTDIR)\stdreg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("stdreg.dep")
!INCLUDE "stdreg.dep"
!ELSE 
!MESSAGE Warning: cannot find "stdreg.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "stdreg - Win32 Release" || "$(CFG)" == "stdreg - Win32 Debug"
SOURCE=.\columdlg.cpp

"$(INTDIR)\columdlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\coursset.cpp

"$(INTDIR)\coursset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\dialog.cpp

"$(INTDIR)\dialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\dsectset.cpp

"$(INTDIR)\dsectset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\enrolset.cpp

"$(INTDIR)\enrolset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\instrset.cpp

"$(INTDIR)\instrset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\sectset.cpp

"$(INTDIR)\sectset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "stdreg - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\stdreg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdreg.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\stdreg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdreg.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\stdreg.cpp

"$(INTDIR)\stdreg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\stdreg.rc

"$(INTDIR)\stdreg.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\stdset.cpp

"$(INTDIR)\stdset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"


SOURCE=.\typeinfo.cpp

"$(INTDIR)\typeinfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\stdreg.pch"



!ENDIF 

