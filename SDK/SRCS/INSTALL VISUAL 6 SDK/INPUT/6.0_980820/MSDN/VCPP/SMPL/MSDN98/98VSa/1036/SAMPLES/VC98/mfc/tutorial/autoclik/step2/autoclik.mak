# Microsoft Developer Studio Generated NMAKE File, Based on autoclik.dsp
!IF "$(CFG)" == ""
CFG=AutoClik - Win32 Release
!MESSAGE No configuration specified. Defaulting to AutoClik - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "AutoClik - Win32 Release" && "$(CFG)" != "AutoClik - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "autoclik.mak" CFG="AutoClik - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AutoClik - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AutoClik - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "AutoClik - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\autoclik.exe" "$(OUTDIR)\autoclik.tlb"


CLEAN :
	-@erase "$(INTDIR)\aclikdoc.obj"
	-@erase "$(INTDIR)\aclikvw.obj"
	-@erase "$(INTDIR)\autoclik.obj"
	-@erase "$(INTDIR)\autoclik.pch"
	-@erase "$(INTDIR)\autoclik.res"
	-@erase "$(INTDIR)\autoclik.tlb"
	-@erase "$(INTDIR)\childfrm.obj"
	-@erase "$(INTDIR)\dialogs.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\autoclik.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\autoclik.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\autoclik.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\autoclik.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\autoclik.pdb" /machine:I386 /out:"$(OUTDIR)\autoclik.exe" 
LINK32_OBJS= \
	"$(INTDIR)\aclikdoc.obj" \
	"$(INTDIR)\aclikvw.obj" \
	"$(INTDIR)\autoclik.obj" \
	"$(INTDIR)\childfrm.obj" \
	"$(INTDIR)\dialogs.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\autoclik.res"

"$(OUTDIR)\autoclik.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AutoClik - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\autoclik.exe" "$(OUTDIR)\autoclik.tlb"


CLEAN :
	-@erase "$(INTDIR)\aclikdoc.obj"
	-@erase "$(INTDIR)\aclikvw.obj"
	-@erase "$(INTDIR)\autoclik.obj"
	-@erase "$(INTDIR)\autoclik.pch"
	-@erase "$(INTDIR)\autoclik.res"
	-@erase "$(INTDIR)\autoclik.tlb"
	-@erase "$(INTDIR)\childfrm.obj"
	-@erase "$(INTDIR)\dialogs.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\autoclik.exe"
	-@erase "$(OUTDIR)\autoclik.ilk"
	-@erase "$(OUTDIR)\autoclik.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\autoclik.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\autoclik.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\autoclik.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\autoclik.pdb" /debug /machine:I386 /out:"$(OUTDIR)\autoclik.exe" 
LINK32_OBJS= \
	"$(INTDIR)\aclikdoc.obj" \
	"$(INTDIR)\aclikvw.obj" \
	"$(INTDIR)\autoclik.obj" \
	"$(INTDIR)\childfrm.obj" \
	"$(INTDIR)\dialogs.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\autoclik.res"

"$(OUTDIR)\autoclik.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("autoclik.dep")
!INCLUDE "autoclik.dep"
!ELSE 
!MESSAGE Warning: cannot find "autoclik.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AutoClik - Win32 Release" || "$(CFG)" == "AutoClik - Win32 Debug"
SOURCE=.\aclikdoc.cpp

"$(INTDIR)\aclikdoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\autoclik.pch"


SOURCE=.\aclikvw.cpp

"$(INTDIR)\aclikvw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\autoclik.pch"


SOURCE=.\autoclik.cpp

"$(INTDIR)\autoclik.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\autoclik.pch"


SOURCE=.\autoclik.odl

!IF  "$(CFG)" == "AutoClik - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\autoclik.tlb" /mktyplib203 /win32 

"$(OUTDIR)\autoclik.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AutoClik - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\autoclik.tlb" /mktyplib203 /win32 

"$(OUTDIR)\autoclik.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\autoclik.rc

!IF  "$(CFG)" == "AutoClik - Win32 Release"


"$(INTDIR)\autoclik.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\autoclik.res" /i ".\Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "AutoClik - Win32 Debug"


"$(INTDIR)\autoclik.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\autoclik.res" /i ".\Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\childfrm.cpp

"$(INTDIR)\childfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\autoclik.pch"


SOURCE=.\dialogs.cpp

"$(INTDIR)\dialogs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\autoclik.pch"


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\autoclik.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "AutoClik - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\autoclik.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\autoclik.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AutoClik - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\autoclik.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\autoclik.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

