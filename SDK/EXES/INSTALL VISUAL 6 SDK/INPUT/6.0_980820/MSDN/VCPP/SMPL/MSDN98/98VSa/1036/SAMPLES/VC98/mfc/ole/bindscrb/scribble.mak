# Microsoft Developer Studio Generated NMAKE File, Based on Scribble.dsp
!IF "$(CFG)" == ""
CFG=SCRIBBLE - Win32 (80x86) Debug
!MESSAGE No configuration specified. Defaulting to SCRIBBLE - Win32 (80x86) Debug.
!ENDIF 

!IF "$(CFG)" != "SCRIBBLE - Win32 (80x86) Debug" && "$(CFG)" != "SCRIBBLE - Win32 (80x86) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Scribble.mak" CFG="SCRIBBLE - Win32 (80x86) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SCRIBBLE - Win32 (80x86) Debug" (based on "Win32 (x86) Application")
!MESSAGE "SCRIBBLE - Win32 (80x86) Release" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "SCRIBBLE - Win32 (80x86) Debug"

OUTDIR=.\WinDebug
INTDIR=.\WinDebug
# Begin Custom Macros
OutDir=.\WinDebug
# End Custom Macros

ALL : "$(OUTDIR)\Scribble.exe"


CLEAN :
	-@erase "$(INTDIR)\IPFRAME.OBJ"
	-@erase "$(INTDIR)\MAINFRM.OBJ"
	-@erase "$(INTDIR)\PENDLG.OBJ"
	-@erase "$(INTDIR)\SCRIBBLE.OBJ"
	-@erase "$(INTDIR)\Scribble.pch"
	-@erase "$(INTDIR)\SCRIBBLE.res"
	-@erase "$(INTDIR)\SCRIBDOC.OBJ"
	-@erase "$(INTDIR)\SCRIBFRM.OBJ"
	-@erase "$(INTDIR)\SCRIBITM.OBJ"
	-@erase "$(INTDIR)\SCRIBVW.OBJ"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Scribble.exe"
	-@erase "$(OUTDIR)\Scribble.ilk"
	-@erase "$(OUTDIR)\Scribble.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Scribble.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SCRIBBLE.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Scribble.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Scribble.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Scribble.exe" 
LINK32_OBJS= \
	"$(INTDIR)\IPFRAME.OBJ" \
	"$(INTDIR)\MAINFRM.OBJ" \
	"$(INTDIR)\PENDLG.OBJ" \
	"$(INTDIR)\SCRIBBLE.OBJ" \
	"$(INTDIR)\SCRIBDOC.OBJ" \
	"$(INTDIR)\SCRIBFRM.OBJ" \
	"$(INTDIR)\SCRIBITM.OBJ" \
	"$(INTDIR)\SCRIBVW.OBJ" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\SCRIBBLE.res"

"$(OUTDIR)\Scribble.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SCRIBBLE - Win32 (80x86) Release"

OUTDIR=.\WinRel
INTDIR=.\WinRel
# Begin Custom Macros
OutDir=.\WinRel
# End Custom Macros

ALL : "$(OUTDIR)\Scribble.exe"


CLEAN :
	-@erase "$(INTDIR)\IPFRAME.OBJ"
	-@erase "$(INTDIR)\MAINFRM.OBJ"
	-@erase "$(INTDIR)\PENDLG.OBJ"
	-@erase "$(INTDIR)\SCRIBBLE.OBJ"
	-@erase "$(INTDIR)\Scribble.pch"
	-@erase "$(INTDIR)\SCRIBBLE.res"
	-@erase "$(INTDIR)\SCRIBDOC.OBJ"
	-@erase "$(INTDIR)\SCRIBFRM.OBJ"
	-@erase "$(INTDIR)\SCRIBITM.OBJ"
	-@erase "$(INTDIR)\SCRIBVW.OBJ"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Scribble.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Scribble.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SCRIBBLE.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Scribble.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Scribble.pdb" /machine:I386 /out:"$(OUTDIR)\Scribble.exe" 
LINK32_OBJS= \
	"$(INTDIR)\IPFRAME.OBJ" \
	"$(INTDIR)\MAINFRM.OBJ" \
	"$(INTDIR)\PENDLG.OBJ" \
	"$(INTDIR)\SCRIBBLE.OBJ" \
	"$(INTDIR)\SCRIBDOC.OBJ" \
	"$(INTDIR)\SCRIBFRM.OBJ" \
	"$(INTDIR)\SCRIBITM.OBJ" \
	"$(INTDIR)\SCRIBVW.OBJ" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\SCRIBBLE.res"

"$(OUTDIR)\Scribble.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

MTL_PROJ=/mktyplib203 

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Scribble.dep")
!INCLUDE "Scribble.dep"
!ELSE 
!MESSAGE Warning: cannot find "Scribble.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SCRIBBLE - Win32 (80x86) Debug" || "$(CFG)" == "SCRIBBLE - Win32 (80x86) Release"
SOURCE=.\IPFRAME.CPP

"$(INTDIR)\IPFRAME.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Scribble.pch"


SOURCE=.\MAINFRM.CPP

"$(INTDIR)\MAINFRM.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Scribble.pch"


SOURCE=.\PENDLG.CPP

"$(INTDIR)\PENDLG.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Scribble.pch"


SOURCE=.\SCRIBBLE.CPP

"$(INTDIR)\SCRIBBLE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Scribble.pch"


SOURCE=.\SCRIBBLE.RC

"$(INTDIR)\SCRIBBLE.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SCRIBDOC.CPP

"$(INTDIR)\SCRIBDOC.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Scribble.pch"


SOURCE=.\SCRIBFRM.CPP

"$(INTDIR)\SCRIBFRM.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Scribble.pch"


SOURCE=.\SCRIBITM.CPP

"$(INTDIR)\SCRIBITM.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Scribble.pch"


SOURCE=.\SCRIBVW.CPP

"$(INTDIR)\SCRIBVW.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Scribble.pch"


SOURCE=.\STDAFX.CPP

!IF  "$(CFG)" == "SCRIBBLE - Win32 (80x86) Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Scribble.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\STDAFX.OBJ"	"$(INTDIR)\Scribble.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SCRIBBLE - Win32 (80x86) Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Scribble.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\STDAFX.OBJ"	"$(INTDIR)\Scribble.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

