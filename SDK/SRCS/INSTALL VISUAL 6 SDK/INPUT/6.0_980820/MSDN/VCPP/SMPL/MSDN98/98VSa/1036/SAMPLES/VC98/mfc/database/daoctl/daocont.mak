# Microsoft Developer Studio Generated NMAKE File, Based on daocont.dsp
!IF "$(CFG)" == ""
CFG=DaoCont - Win32 Release
!MESSAGE No configuration specified. Defaulting to DaoCont - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DaoCont - Win32 Release" && "$(CFG)" != "DaoCont - Win32 Debug" && "$(CFG)" != "DaoCont - Win32 Unicode Release" && "$(CFG)" != "DaoCont - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "daocont.mak" CFG="DaoCont - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DaoCont - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DaoCont - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "DaoCont - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "DaoCont - Win32 Unicode Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "DaoCont - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\daocont.exe"


CLEAN :
	-@erase "$(INTDIR)\accpict.obj"
	-@erase "$(INTDIR)\ctrlext.obj"
	-@erase "$(INTDIR)\daocndlg.obj"
	-@erase "$(INTDIR)\daocont.obj"
	-@erase "$(INTDIR)\daocont.pch"
	-@erase "$(INTDIR)\daocont.res"
	-@erase "$(INTDIR)\daoedit.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\daocont.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daocont.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\daocont.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daocont.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\daocont.pdb" /machine:I386 /out:"$(OUTDIR)\daocont.exe" 
LINK32_OBJS= \
	"$(INTDIR)\accpict.obj" \
	"$(INTDIR)\ctrlext.obj" \
	"$(INTDIR)\daocndlg.obj" \
	"$(INTDIR)\daocont.obj" \
	"$(INTDIR)\daoedit.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\daocont.res"

"$(OUTDIR)\daocont.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DaoCont - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\daocont.exe"


CLEAN :
	-@erase "$(INTDIR)\accpict.obj"
	-@erase "$(INTDIR)\ctrlext.obj"
	-@erase "$(INTDIR)\daocndlg.obj"
	-@erase "$(INTDIR)\daocont.obj"
	-@erase "$(INTDIR)\daocont.pch"
	-@erase "$(INTDIR)\daocont.res"
	-@erase "$(INTDIR)\daoedit.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\daocont.exe"
	-@erase "$(OUTDIR)\daocont.ilk"
	-@erase "$(OUTDIR)\daocont.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daocont.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\daocont.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daocont.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\daocont.pdb" /debug /machine:I386 /out:"$(OUTDIR)\daocont.exe" 
LINK32_OBJS= \
	"$(INTDIR)\accpict.obj" \
	"$(INTDIR)\ctrlext.obj" \
	"$(INTDIR)\daocndlg.obj" \
	"$(INTDIR)\daocont.obj" \
	"$(INTDIR)\daoedit.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\daocont.res"

"$(OUTDIR)\daocont.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DaoCont - Win32 Unicode Release"

OUTDIR=.\UniRel
INTDIR=.\UniRel
# Begin Custom Macros
OutDir=.\.\UniRel
# End Custom Macros

ALL : "$(OUTDIR)\daocont.exe"


CLEAN :
	-@erase "$(INTDIR)\accpict.obj"
	-@erase "$(INTDIR)\ctrlext.obj"
	-@erase "$(INTDIR)\daocndlg.obj"
	-@erase "$(INTDIR)\daocont.obj"
	-@erase "$(INTDIR)\daocont.pch"
	-@erase "$(INTDIR)\daocont.res"
	-@erase "$(INTDIR)\daoedit.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\daocont.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\daocont.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\daocont.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daocont.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\daocont.pdb" /machine:I386 /out:"$(OUTDIR)\daocont.exe" 
LINK32_OBJS= \
	"$(INTDIR)\accpict.obj" \
	"$(INTDIR)\ctrlext.obj" \
	"$(INTDIR)\daocndlg.obj" \
	"$(INTDIR)\daocont.obj" \
	"$(INTDIR)\daoedit.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\daocont.res"

"$(OUTDIR)\daocont.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DaoCont - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\daocont.exe"


CLEAN :
	-@erase "$(INTDIR)\accpict.obj"
	-@erase "$(INTDIR)\ctrlext.obj"
	-@erase "$(INTDIR)\daocndlg.obj"
	-@erase "$(INTDIR)\daocont.obj"
	-@erase "$(INTDIR)\daocont.pch"
	-@erase "$(INTDIR)\daocont.res"
	-@erase "$(INTDIR)\daoedit.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\daocont.exe"
	-@erase "$(OUTDIR)\daocont.ilk"
	-@erase "$(OUTDIR)\daocont.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\daocont.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\daocont.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daocont.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\daocont.pdb" /debug /machine:I386 /out:"$(OUTDIR)\daocont.exe" 
LINK32_OBJS= \
	"$(INTDIR)\accpict.obj" \
	"$(INTDIR)\ctrlext.obj" \
	"$(INTDIR)\daocndlg.obj" \
	"$(INTDIR)\daocont.obj" \
	"$(INTDIR)\daoedit.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\daocont.res"

"$(OUTDIR)\daocont.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("daocont.dep")
!INCLUDE "daocont.dep"
!ELSE 
!MESSAGE Warning: cannot find "daocont.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DaoCont - Win32 Release" || "$(CFG)" == "DaoCont - Win32 Debug" || "$(CFG)" == "DaoCont - Win32 Unicode Release" || "$(CFG)" == "DaoCont - Win32 Unicode Debug"
SOURCE=.\accpict.cpp

"$(INTDIR)\accpict.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daocont.pch"


SOURCE=.\ctrlext.cpp

"$(INTDIR)\ctrlext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daocont.pch"


SOURCE=.\daocndlg.cpp

"$(INTDIR)\daocndlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daocont.pch"


SOURCE=.\daocont.cpp

"$(INTDIR)\daocont.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daocont.pch"


SOURCE=.\daocont.rc

"$(INTDIR)\daocont.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\daoedit.cpp

"$(INTDIR)\daoedit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daocont.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "DaoCont - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daocont.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\daocont.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoCont - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daocont.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\daocont.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoCont - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\daocont.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\daocont.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoCont - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\daocont.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\daocont.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

