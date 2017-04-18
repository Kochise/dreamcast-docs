# Microsoft Developer Studio Generated NMAKE File, Based on oldbars.dsp
!IF "$(CFG)" == ""
CFG=OldBars - Win32 Release
!MESSAGE No configuration specified. Defaulting to OldBars - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "OldBars - Win32 Release" && "$(CFG)" != "OldBars - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "oldbars.mak" CFG="OldBars - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OldBars - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OldBars - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "OldBars - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\oldbars.exe"


CLEAN :
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Oldbadoc.obj"
	-@erase "$(INTDIR)\Oldbars.obj"
	-@erase "$(INTDIR)\oldbars.pch"
	-@erase "$(INTDIR)\oldbars.res"
	-@erase "$(INTDIR)\Oldbavw.obj"
	-@erase "$(INTDIR)\Statbar.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\Toolbar.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\oldbars.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\oldbars.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\oldbars.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\oldbars.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\oldbars.pdb" /machine:I386 /out:"$(OUTDIR)\oldbars.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Oldbadoc.obj" \
	"$(INTDIR)\Oldbars.obj" \
	"$(INTDIR)\Oldbavw.obj" \
	"$(INTDIR)\Statbar.obj" \
	"$(INTDIR)\Stdafx.obj" \
	"$(INTDIR)\Toolbar.obj" \
	"$(INTDIR)\oldbars.res"

"$(OUTDIR)\oldbars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OldBars - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\oldbars.exe"


CLEAN :
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Oldbadoc.obj"
	-@erase "$(INTDIR)\Oldbars.obj"
	-@erase "$(INTDIR)\oldbars.pch"
	-@erase "$(INTDIR)\oldbars.res"
	-@erase "$(INTDIR)\Oldbavw.obj"
	-@erase "$(INTDIR)\Statbar.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\Toolbar.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\oldbars.exe"
	-@erase "$(OUTDIR)\oldbars.ilk"
	-@erase "$(OUTDIR)\oldbars.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\oldbars.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\oldbars.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\oldbars.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\oldbars.pdb" /debug /machine:I386 /out:"$(OUTDIR)\oldbars.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Oldbadoc.obj" \
	"$(INTDIR)\Oldbars.obj" \
	"$(INTDIR)\Oldbavw.obj" \
	"$(INTDIR)\Statbar.obj" \
	"$(INTDIR)\Stdafx.obj" \
	"$(INTDIR)\Toolbar.obj" \
	"$(INTDIR)\oldbars.res"

"$(OUTDIR)\oldbars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("oldbars.dep")
!INCLUDE "oldbars.dep"
!ELSE 
!MESSAGE Warning: cannot find "oldbars.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OldBars - Win32 Release" || "$(CFG)" == "OldBars - Win32 Debug"
SOURCE=.\Globals.cpp

"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oldbars.pch"


SOURCE=.\Mainfrm.cpp

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oldbars.pch"


SOURCE=.\Oldbadoc.cpp

"$(INTDIR)\Oldbadoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oldbars.pch"


SOURCE=.\Oldbars.cpp

"$(INTDIR)\Oldbars.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oldbars.pch"


SOURCE=.\oldbars.rc

"$(INTDIR)\oldbars.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Oldbavw.cpp

"$(INTDIR)\Oldbavw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oldbars.pch"


SOURCE=.\Statbar.cpp

"$(INTDIR)\Statbar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oldbars.pch"


SOURCE=.\Stdafx.cpp

!IF  "$(CFG)" == "OldBars - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\oldbars.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\oldbars.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OldBars - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\oldbars.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\oldbars.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Toolbar.cpp

"$(INTDIR)\Toolbar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oldbars.pch"



!ENDIF 

