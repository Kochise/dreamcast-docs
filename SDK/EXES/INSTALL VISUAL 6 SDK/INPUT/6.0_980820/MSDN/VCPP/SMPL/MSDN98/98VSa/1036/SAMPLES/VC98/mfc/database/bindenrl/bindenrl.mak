# Microsoft Developer Studio Generated NMAKE File, Based on bindenrl.dsp
!IF "$(CFG)" == ""
CFG=BindEnrl - Win32 Release
!MESSAGE No configuration specified. Defaulting to BindEnrl - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "BindEnrl - Win32 Release" && "$(CFG)" != "BindEnrl - Win32 Debug" && "$(CFG)" != "BindEnrl - Win32 Unicode Debug" && "$(CFG)" != "BindEnrl - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bindenrl.mak" CFG="BindEnrl - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BindEnrl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BindEnrl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BindEnrl - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "BindEnrl - Win32 Unicode Release" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "BindEnrl - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\bindenrl.exe"


CLEAN :
	-@erase "$(INTDIR)\BindEnrl.obj"
	-@erase "$(INTDIR)\bindenrl.pch"
	-@erase "$(INTDIR)\BindEnrl.res"
	-@erase "$(INTDIR)\CoursDlg.obj"
	-@erase "$(INTDIR)\dblist.obj"
	-@erase "$(INTDIR)\EnrolDlg.obj"
	-@erase "$(INTDIR)\InstrDlg.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\propsht.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\SectnDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StudDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\bindenrl.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bindenrl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\BindEnrl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bindenrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\bindenrl.pdb" /machine:I386 /out:"$(OUTDIR)\bindenrl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BindEnrl.obj" \
	"$(INTDIR)\CoursDlg.obj" \
	"$(INTDIR)\dblist.obj" \
	"$(INTDIR)\EnrolDlg.obj" \
	"$(INTDIR)\InstrDlg.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\propsht.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\SectnDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StudDlg.obj" \
	"$(INTDIR)\BindEnrl.res"

"$(OUTDIR)\bindenrl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "BindEnrl - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\bindenrl.exe"


CLEAN :
	-@erase "$(INTDIR)\BindEnrl.obj"
	-@erase "$(INTDIR)\bindenrl.pch"
	-@erase "$(INTDIR)\BindEnrl.res"
	-@erase "$(INTDIR)\CoursDlg.obj"
	-@erase "$(INTDIR)\dblist.obj"
	-@erase "$(INTDIR)\EnrolDlg.obj"
	-@erase "$(INTDIR)\InstrDlg.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\propsht.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\SectnDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StudDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\bindenrl.exe"
	-@erase "$(OUTDIR)\bindenrl.ilk"
	-@erase "$(OUTDIR)\bindenrl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bindenrl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\BindEnrl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bindenrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\bindenrl.pdb" /debug /machine:I386 /out:"$(OUTDIR)\bindenrl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BindEnrl.obj" \
	"$(INTDIR)\CoursDlg.obj" \
	"$(INTDIR)\dblist.obj" \
	"$(INTDIR)\EnrolDlg.obj" \
	"$(INTDIR)\InstrDlg.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\propsht.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\SectnDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StudDlg.obj" \
	"$(INTDIR)\BindEnrl.res"

"$(OUTDIR)\bindenrl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "BindEnrl - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\bindenrl.exe"


CLEAN :
	-@erase "$(INTDIR)\BindEnrl.obj"
	-@erase "$(INTDIR)\bindenrl.pch"
	-@erase "$(INTDIR)\BindEnrl.res"
	-@erase "$(INTDIR)\CoursDlg.obj"
	-@erase "$(INTDIR)\dblist.obj"
	-@erase "$(INTDIR)\EnrolDlg.obj"
	-@erase "$(INTDIR)\InstrDlg.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\propsht.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\SectnDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StudDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\bindenrl.exe"
	-@erase "$(OUTDIR)\bindenrl.ilk"
	-@erase "$(OUTDIR)\bindenrl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bindenrl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\BindEnrl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bindenrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\bindenrl.pdb" /debug /machine:I386 /out:"$(OUTDIR)\bindenrl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BindEnrl.obj" \
	"$(INTDIR)\CoursDlg.obj" \
	"$(INTDIR)\dblist.obj" \
	"$(INTDIR)\EnrolDlg.obj" \
	"$(INTDIR)\InstrDlg.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\propsht.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\SectnDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StudDlg.obj" \
	"$(INTDIR)\BindEnrl.res"

"$(OUTDIR)\bindenrl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "BindEnrl - Win32 Unicode Release"

OUTDIR=.\UniRel
INTDIR=.\UniRel
# Begin Custom Macros
OutDir=.\.\UniRel
# End Custom Macros

ALL : "$(OUTDIR)\bindenrl.exe"


CLEAN :
	-@erase "$(INTDIR)\BindEnrl.obj"
	-@erase "$(INTDIR)\bindenrl.pch"
	-@erase "$(INTDIR)\BindEnrl.res"
	-@erase "$(INTDIR)\CoursDlg.obj"
	-@erase "$(INTDIR)\dblist.obj"
	-@erase "$(INTDIR)\EnrolDlg.obj"
	-@erase "$(INTDIR)\InstrDlg.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\propsht.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\SectnDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StudDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\bindenrl.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bindenrl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\BindEnrl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bindenrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\bindenrl.pdb" /machine:I386 /out:"$(OUTDIR)\bindenrl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BindEnrl.obj" \
	"$(INTDIR)\CoursDlg.obj" \
	"$(INTDIR)\dblist.obj" \
	"$(INTDIR)\EnrolDlg.obj" \
	"$(INTDIR)\InstrDlg.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\propsht.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\SectnDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StudDlg.obj" \
	"$(INTDIR)\BindEnrl.res"

"$(OUTDIR)\bindenrl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("bindenrl.dep")
!INCLUDE "bindenrl.dep"
!ELSE 
!MESSAGE Warning: cannot find "bindenrl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "BindEnrl - Win32 Release" || "$(CFG)" == "BindEnrl - Win32 Debug" || "$(CFG)" == "BindEnrl - Win32 Unicode Debug" || "$(CFG)" == "BindEnrl - Win32 Unicode Release"
SOURCE=.\BindEnrl.cpp

"$(INTDIR)\BindEnrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\BindEnrl.rc

"$(INTDIR)\BindEnrl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CoursDlg.cpp

"$(INTDIR)\CoursDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\dblist.cpp

"$(INTDIR)\dblist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\EnrolDlg.cpp

"$(INTDIR)\EnrolDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\InstrDlg.cpp

"$(INTDIR)\InstrDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\msmask.cpp

"$(INTDIR)\msmask.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\propsht.cpp

"$(INTDIR)\propsht.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\rdc.cpp

"$(INTDIR)\rdc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\SectnDlg.cpp

"$(INTDIR)\SectnDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "BindEnrl - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bindenrl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\bindenrl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "BindEnrl - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bindenrl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\bindenrl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "BindEnrl - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bindenrl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\bindenrl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "BindEnrl - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bindenrl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\bindenrl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StudDlg.cpp

"$(INTDIR)\StudDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bindenrl.pch"



!ENDIF 

