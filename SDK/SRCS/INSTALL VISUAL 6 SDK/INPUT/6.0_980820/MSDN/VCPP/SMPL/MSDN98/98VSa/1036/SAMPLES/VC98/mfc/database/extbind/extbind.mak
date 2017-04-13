# Microsoft Developer Studio Generated NMAKE File, Based on extbind.dsp
!IF "$(CFG)" == ""
CFG=ExtBind - Win32 Release
!MESSAGE No configuration specified. Defaulting to ExtBind - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ExtBind - Win32 Release" && "$(CFG)" != "ExtBind - Win32 Debug" && "$(CFG)" != "ExtBind - Win32 Unicode Debug" && "$(CFG)" != "ExtBind - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "extbind.mak" CFG="ExtBind - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ExtBind - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ExtBind - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ExtBind - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "ExtBind - Win32 Unicode Release" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "ExtBind - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\extbind.exe"


CLEAN :
	-@erase "$(INTDIR)\calendar.obj"
	-@erase "$(INTDIR)\extbind.obj"
	-@erase "$(INTDIR)\extbind.pch"
	-@erase "$(INTDIR)\extbind.res"
	-@erase "$(INTDIR)\modeldlg.obj"
	-@erase "$(INTDIR)\msdgrid.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\nwinddlg.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\extbind.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\extbind.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\extbind.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\extbind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\extbind.pdb" /machine:I386 /out:"$(OUTDIR)\extbind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\calendar.obj" \
	"$(INTDIR)\extbind.obj" \
	"$(INTDIR)\modeldlg.obj" \
	"$(INTDIR)\msdgrid.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\nwinddlg.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\extbind.res"

"$(OUTDIR)\extbind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ExtBind - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\extbind.exe"


CLEAN :
	-@erase "$(INTDIR)\calendar.obj"
	-@erase "$(INTDIR)\extbind.obj"
	-@erase "$(INTDIR)\extbind.pch"
	-@erase "$(INTDIR)\extbind.res"
	-@erase "$(INTDIR)\modeldlg.obj"
	-@erase "$(INTDIR)\msdgrid.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\nwinddlg.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\extbind.exe"
	-@erase "$(OUTDIR)\extbind.ilk"
	-@erase "$(OUTDIR)\extbind.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\extbind.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\extbind.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\extbind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\extbind.pdb" /debug /machine:I386 /out:"$(OUTDIR)\extbind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\calendar.obj" \
	"$(INTDIR)\extbind.obj" \
	"$(INTDIR)\modeldlg.obj" \
	"$(INTDIR)\msdgrid.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\nwinddlg.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\extbind.res"

"$(OUTDIR)\extbind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ExtBind - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\extbind.exe"


CLEAN :
	-@erase "$(INTDIR)\calendar.obj"
	-@erase "$(INTDIR)\extbind.obj"
	-@erase "$(INTDIR)\extbind.pch"
	-@erase "$(INTDIR)\extbind.res"
	-@erase "$(INTDIR)\modeldlg.obj"
	-@erase "$(INTDIR)\msdgrid.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\nwinddlg.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\extbind.exe"
	-@erase "$(OUTDIR)\extbind.ilk"
	-@erase "$(OUTDIR)\extbind.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\extbind.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\extbind.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\extbind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\extbind.pdb" /debug /machine:I386 /out:"$(OUTDIR)\extbind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\calendar.obj" \
	"$(INTDIR)\extbind.obj" \
	"$(INTDIR)\modeldlg.obj" \
	"$(INTDIR)\msdgrid.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\nwinddlg.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\extbind.res"

"$(OUTDIR)\extbind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ExtBind - Win32 Unicode Release"

OUTDIR=.\UniRel
INTDIR=.\UniRel
# Begin Custom Macros
OutDir=.\.\UniRel
# End Custom Macros

ALL : "$(OUTDIR)\extbind.exe"


CLEAN :
	-@erase "$(INTDIR)\calendar.obj"
	-@erase "$(INTDIR)\extbind.obj"
	-@erase "$(INTDIR)\extbind.pch"
	-@erase "$(INTDIR)\extbind.res"
	-@erase "$(INTDIR)\modeldlg.obj"
	-@erase "$(INTDIR)\msdgrid.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\nwinddlg.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\extbind.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\extbind.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\extbind.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\extbind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\extbind.pdb" /machine:I386 /out:"$(OUTDIR)\extbind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\calendar.obj" \
	"$(INTDIR)\extbind.obj" \
	"$(INTDIR)\modeldlg.obj" \
	"$(INTDIR)\msdgrid.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\nwinddlg.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\extbind.res"

"$(OUTDIR)\extbind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("extbind.dep")
!INCLUDE "extbind.dep"
!ELSE 
!MESSAGE Warning: cannot find "extbind.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ExtBind - Win32 Release" || "$(CFG)" == "ExtBind - Win32 Debug" || "$(CFG)" == "ExtBind - Win32 Unicode Debug" || "$(CFG)" == "ExtBind - Win32 Unicode Release"
SOURCE=.\calendar.cpp

"$(INTDIR)\calendar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\extbind.pch"


SOURCE=.\extbind.cpp

"$(INTDIR)\extbind.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\extbind.pch"


SOURCE=.\extbind.rc

"$(INTDIR)\extbind.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\modeldlg.cpp

"$(INTDIR)\modeldlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\extbind.pch"


SOURCE=.\msdgrid.cpp

"$(INTDIR)\msdgrid.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\extbind.pch"


SOURCE=.\msmask.cpp

"$(INTDIR)\msmask.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\extbind.pch"


SOURCE=.\nwinddlg.cpp

"$(INTDIR)\nwinddlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\extbind.pch"


SOURCE=.\rdc.cpp

"$(INTDIR)\rdc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\extbind.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "ExtBind - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\extbind.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\extbind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ExtBind - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\extbind.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\extbind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ExtBind - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\extbind.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\extbind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ExtBind - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\extbind.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\extbind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

