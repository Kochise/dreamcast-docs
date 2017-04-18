# Microsoft Developer Studio Generated NMAKE File, Based on daoview.dsp
!IF "$(CFG)" == ""
CFG=daoview - Win32 Release
!MESSAGE No configuration specified. Defaulting to daoview - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "daoview - Win32 Release" && "$(CFG)" != "daoview - Win32 Debug" && "$(CFG)" != "daoview - Win32 Unicode Release" && "$(CFG)" != "daoview - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "daoview.mak" CFG="daoview - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "daoview - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "daoview - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "daoview - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "daoview - Win32 Unicode Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "daoview - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\daoview.exe"


CLEAN :
	-@erase "$(INTDIR)\crack.obj"
	-@erase "$(INTDIR)\ctrlext.obj"
	-@erase "$(INTDIR)\daoview.obj"
	-@erase "$(INTDIR)\daoview.pch"
	-@erase "$(INTDIR)\daoview.res"
	-@erase "$(INTDIR)\daovwdoc.obj"
	-@erase "$(INTDIR)\dlgparam.obj"
	-@erase "$(INTDIR)\dlgsql.obj"
	-@erase "$(INTDIR)\dragitem.obj"
	-@erase "$(INTDIR)\listview.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\optionsd.obj"
	-@erase "$(INTDIR)\renamedl.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\daoview.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daoview.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\daoview.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daoview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\daoview.pdb" /machine:I386 /out:"$(OUTDIR)\daoview.exe" 
LINK32_OBJS= \
	"$(INTDIR)\crack.obj" \
	"$(INTDIR)\ctrlext.obj" \
	"$(INTDIR)\daoview.obj" \
	"$(INTDIR)\daovwdoc.obj" \
	"$(INTDIR)\dlgparam.obj" \
	"$(INTDIR)\dlgsql.obj" \
	"$(INTDIR)\dragitem.obj" \
	"$(INTDIR)\listview.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\optionsd.obj" \
	"$(INTDIR)\renamedl.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\daoview.res"

"$(OUTDIR)\daoview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "daoview - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\daoview.exe"


CLEAN :
	-@erase "$(INTDIR)\crack.obj"
	-@erase "$(INTDIR)\ctrlext.obj"
	-@erase "$(INTDIR)\daoview.obj"
	-@erase "$(INTDIR)\daoview.pch"
	-@erase "$(INTDIR)\daoview.res"
	-@erase "$(INTDIR)\daovwdoc.obj"
	-@erase "$(INTDIR)\dlgparam.obj"
	-@erase "$(INTDIR)\dlgsql.obj"
	-@erase "$(INTDIR)\dragitem.obj"
	-@erase "$(INTDIR)\listview.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\optionsd.obj"
	-@erase "$(INTDIR)\renamedl.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\daoview.exe"
	-@erase "$(OUTDIR)\daoview.ilk"
	-@erase "$(OUTDIR)\daoview.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daoview.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\daoview.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daoview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\daoview.pdb" /debug /machine:I386 /out:"$(OUTDIR)\daoview.exe" 
LINK32_OBJS= \
	"$(INTDIR)\crack.obj" \
	"$(INTDIR)\ctrlext.obj" \
	"$(INTDIR)\daoview.obj" \
	"$(INTDIR)\daovwdoc.obj" \
	"$(INTDIR)\dlgparam.obj" \
	"$(INTDIR)\dlgsql.obj" \
	"$(INTDIR)\dragitem.obj" \
	"$(INTDIR)\listview.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\optionsd.obj" \
	"$(INTDIR)\renamedl.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\daoview.res"

"$(OUTDIR)\daoview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "daoview - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\daoview.exe"


CLEAN :
	-@erase "$(INTDIR)\crack.obj"
	-@erase "$(INTDIR)\ctrlext.obj"
	-@erase "$(INTDIR)\daoview.obj"
	-@erase "$(INTDIR)\daoview.pch"
	-@erase "$(INTDIR)\daoview.res"
	-@erase "$(INTDIR)\daovwdoc.obj"
	-@erase "$(INTDIR)\dlgparam.obj"
	-@erase "$(INTDIR)\dlgsql.obj"
	-@erase "$(INTDIR)\dragitem.obj"
	-@erase "$(INTDIR)\listview.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\optionsd.obj"
	-@erase "$(INTDIR)\renamedl.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\daoview.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\daoview.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\daoview.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daoview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\daoview.pdb" /machine:I386 /out:"$(OUTDIR)\daoview.exe" 
LINK32_OBJS= \
	"$(INTDIR)\crack.obj" \
	"$(INTDIR)\ctrlext.obj" \
	"$(INTDIR)\daoview.obj" \
	"$(INTDIR)\daovwdoc.obj" \
	"$(INTDIR)\dlgparam.obj" \
	"$(INTDIR)\dlgsql.obj" \
	"$(INTDIR)\dragitem.obj" \
	"$(INTDIR)\listview.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\optionsd.obj" \
	"$(INTDIR)\renamedl.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\daoview.res"

"$(OUTDIR)\daoview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "daoview - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\daoview.exe"


CLEAN :
	-@erase "$(INTDIR)\crack.obj"
	-@erase "$(INTDIR)\ctrlext.obj"
	-@erase "$(INTDIR)\daoview.obj"
	-@erase "$(INTDIR)\daoview.pch"
	-@erase "$(INTDIR)\daoview.res"
	-@erase "$(INTDIR)\daovwdoc.obj"
	-@erase "$(INTDIR)\dlgparam.obj"
	-@erase "$(INTDIR)\dlgsql.obj"
	-@erase "$(INTDIR)\dragitem.obj"
	-@erase "$(INTDIR)\listview.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\optionsd.obj"
	-@erase "$(INTDIR)\renamedl.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\daoview.exe"
	-@erase "$(OUTDIR)\daoview.ilk"
	-@erase "$(OUTDIR)\daoview.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\daoview.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\daoview.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daoview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\daoview.pdb" /debug /machine:I386 /out:"$(OUTDIR)\daoview.exe" 
LINK32_OBJS= \
	"$(INTDIR)\crack.obj" \
	"$(INTDIR)\ctrlext.obj" \
	"$(INTDIR)\daoview.obj" \
	"$(INTDIR)\daovwdoc.obj" \
	"$(INTDIR)\dlgparam.obj" \
	"$(INTDIR)\dlgsql.obj" \
	"$(INTDIR)\dragitem.obj" \
	"$(INTDIR)\listview.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\optionsd.obj" \
	"$(INTDIR)\renamedl.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\daoview.res"

"$(OUTDIR)\daoview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("daoview.dep")
!INCLUDE "daoview.dep"
!ELSE 
!MESSAGE Warning: cannot find "daoview.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "daoview - Win32 Release" || "$(CFG)" == "daoview - Win32 Debug" || "$(CFG)" == "daoview - Win32 Unicode Release" || "$(CFG)" == "daoview - Win32 Unicode Debug"
SOURCE=.\crack.cpp

"$(INTDIR)\crack.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\ctrlext.cpp

"$(INTDIR)\ctrlext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\daoview.cpp

"$(INTDIR)\daoview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\daoview.rc

"$(INTDIR)\daoview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\daovwdoc.cpp

"$(INTDIR)\daovwdoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\dlgparam.cpp

"$(INTDIR)\dlgparam.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\dlgsql.cpp

"$(INTDIR)\dlgsql.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\dragitem.cpp

"$(INTDIR)\dragitem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\listview.cpp

"$(INTDIR)\listview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\optionsd.cpp

"$(INTDIR)\optionsd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\renamedl.cpp

"$(INTDIR)\renamedl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "daoview - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daoview.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\daoview.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "daoview - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daoview.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\daoview.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "daoview - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\daoview.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\daoview.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "daoview - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\daoview.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\daoview.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\treeview.cpp

"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoview.pch"



!ENDIF 

