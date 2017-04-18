# Microsoft Developer Studio Generated NMAKE File, Based on smiley.dsp
!IF "$(CFG)" == ""
CFG=Smiley - Win32 Release
!MESSAGE No configuration specified. Defaulting to Smiley - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Smiley - Win32 Release" && "$(CFG)" != "Smiley - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smiley.mak" CFG="Smiley - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Smiley - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Smiley - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Smiley - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\smiley.exe"


CLEAN :
	-@erase "$(INTDIR)\smilectl.obj"
	-@erase "$(INTDIR)\smiley.obj"
	-@erase "$(INTDIR)\smiley.pch"
	-@erase "$(INTDIR)\smiley.res"
	-@erase "$(INTDIR)\smileydg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\smiley.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\smiley.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\smiley.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smiley.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\smiley.pdb" /machine:I386 /out:"$(OUTDIR)\smiley.exe" 
LINK32_OBJS= \
	"$(INTDIR)\smilectl.obj" \
	"$(INTDIR)\smiley.obj" \
	"$(INTDIR)\smileydg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\smiley.res"

"$(OUTDIR)\smiley.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Smiley - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\smiley.exe"


CLEAN :
	-@erase "$(INTDIR)\smilectl.obj"
	-@erase "$(INTDIR)\smiley.obj"
	-@erase "$(INTDIR)\smiley.pch"
	-@erase "$(INTDIR)\smiley.res"
	-@erase "$(INTDIR)\smileydg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\smiley.exe"
	-@erase "$(OUTDIR)\smiley.ilk"
	-@erase "$(OUTDIR)\smiley.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\smiley.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\smiley.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smiley.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\smiley.pdb" /debug /machine:I386 /out:"$(OUTDIR)\smiley.exe" 
LINK32_OBJS= \
	"$(INTDIR)\smilectl.obj" \
	"$(INTDIR)\smiley.obj" \
	"$(INTDIR)\smileydg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\smiley.res"

"$(OUTDIR)\smiley.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("smiley.dep")
!INCLUDE "smiley.dep"
!ELSE 
!MESSAGE Warning: cannot find "smiley.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Smiley - Win32 Release" || "$(CFG)" == "Smiley - Win32 Debug"
SOURCE=.\smilectl.cpp

"$(INTDIR)\smilectl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\smiley.pch"


SOURCE=.\smiley.cpp

"$(INTDIR)\smiley.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\smiley.pch"


SOURCE=.\smiley.rc

"$(INTDIR)\smiley.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\smileydg.cpp

"$(INTDIR)\smileydg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\smiley.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Smiley - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\smiley.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\smiley.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Smiley - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\smiley.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\smiley.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

