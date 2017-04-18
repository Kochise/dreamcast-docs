# Microsoft Developer Studio Generated NMAKE File, Based on VCTERM.DSP
!IF "$(CFG)" == ""
CFG=vcterm - Win32 Release
!MESSAGE No configuration specified. Defaulting to vcterm - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "vcterm - Win32 Release" && "$(CFG)" != "vcterm - Win32 Debug" && "$(CFG)" != "vcterm - Win32 Unicode Debug" && "$(CFG)" != "vcterm - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCTERM.MAK" CFG="vcterm - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vcterm - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vcterm - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "vcterm - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "vcterm - Win32 Unicode Release" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "vcterm - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VCTERM.exe"


CLEAN :
	-@erase "$(INTDIR)\CanDlg.obj"
	-@erase "$(INTDIR)\commctrl.obj"
	-@erase "$(INTDIR)\InputDlg.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\setdlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\termedit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vcterm.obj"
	-@erase "$(INTDIR)\VCTERM.pch"
	-@erase "$(INTDIR)\vcterm.res"
	-@erase "$(OUTDIR)\VCTERM.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VCTERM.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vcterm.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCTERM.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\VCTERM.pdb" /machine:I386 /out:"$(OUTDIR)\VCTERM.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CanDlg.obj" \
	"$(INTDIR)\commctrl.obj" \
	"$(INTDIR)\InputDlg.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\setdlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\termedit.obj" \
	"$(INTDIR)\vcterm.obj" \
	"$(INTDIR)\vcterm.res"

"$(OUTDIR)\VCTERM.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vcterm - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VCTERM.exe"


CLEAN :
	-@erase "$(INTDIR)\CanDlg.obj"
	-@erase "$(INTDIR)\commctrl.obj"
	-@erase "$(INTDIR)\InputDlg.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\setdlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\termedit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vcterm.obj"
	-@erase "$(INTDIR)\VCTERM.pch"
	-@erase "$(INTDIR)\vcterm.res"
	-@erase "$(OUTDIR)\VCTERM.exe"
	-@erase "$(OUTDIR)\VCTERM.ilk"
	-@erase "$(OUTDIR)\VCTERM.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VCTERM.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vcterm.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCTERM.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\VCTERM.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VCTERM.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CanDlg.obj" \
	"$(INTDIR)\commctrl.obj" \
	"$(INTDIR)\InputDlg.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\setdlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\termedit.obj" \
	"$(INTDIR)\vcterm.obj" \
	"$(INTDIR)\vcterm.res"

"$(OUTDIR)\VCTERM.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vcterm - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\VCTERM.exe"


CLEAN :
	-@erase "$(INTDIR)\CanDlg.obj"
	-@erase "$(INTDIR)\commctrl.obj"
	-@erase "$(INTDIR)\InputDlg.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\setdlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\termedit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vcterm.obj"
	-@erase "$(INTDIR)\VCTERM.pch"
	-@erase "$(INTDIR)\vcterm.res"
	-@erase "$(OUTDIR)\VCTERM.exe"
	-@erase "$(OUTDIR)\VCTERM.ilk"
	-@erase "$(OUTDIR)\VCTERM.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\VCTERM.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vcterm.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCTERM.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\VCTERM.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VCTERM.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CanDlg.obj" \
	"$(INTDIR)\commctrl.obj" \
	"$(INTDIR)\InputDlg.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\setdlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\termedit.obj" \
	"$(INTDIR)\vcterm.obj" \
	"$(INTDIR)\vcterm.res"

"$(OUTDIR)\VCTERM.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vcterm - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\VCTERM.exe"


CLEAN :
	-@erase "$(INTDIR)\CanDlg.obj"
	-@erase "$(INTDIR)\commctrl.obj"
	-@erase "$(INTDIR)\InputDlg.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\setdlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\termedit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vcterm.obj"
	-@erase "$(INTDIR)\VCTERM.pch"
	-@erase "$(INTDIR)\vcterm.res"
	-@erase "$(OUTDIR)\VCTERM.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\VCTERM.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vcterm.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCTERM.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\VCTERM.pdb" /machine:I386 /out:"$(OUTDIR)\VCTERM.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CanDlg.obj" \
	"$(INTDIR)\commctrl.obj" \
	"$(INTDIR)\InputDlg.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\setdlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\termedit.obj" \
	"$(INTDIR)\vcterm.obj" \
	"$(INTDIR)\vcterm.res"

"$(OUTDIR)\VCTERM.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("VCTERM.DEP")
!INCLUDE "VCTERM.DEP"
!ELSE 
!MESSAGE Warning: cannot find "VCTERM.DEP"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vcterm - Win32 Release" || "$(CFG)" == "vcterm - Win32 Debug" || "$(CFG)" == "vcterm - Win32 Unicode Debug" || "$(CFG)" == "vcterm - Win32 Unicode Release"
SOURCE=.\CanDlg.cpp

"$(INTDIR)\CanDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCTERM.pch"


SOURCE=.\commctrl.cpp

"$(INTDIR)\commctrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCTERM.pch"


SOURCE=.\InputDlg.cpp

"$(INTDIR)\InputDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCTERM.pch"


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCTERM.pch"


SOURCE=.\setdlg.cpp

"$(INTDIR)\setdlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCTERM.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "vcterm - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VCTERM.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCTERM.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vcterm - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VCTERM.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCTERM.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vcterm - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\VCTERM.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCTERM.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vcterm - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\VCTERM.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCTERM.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\termedit.cpp

"$(INTDIR)\termedit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCTERM.pch"


SOURCE=.\vcterm.cpp

"$(INTDIR)\vcterm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCTERM.pch"


SOURCE=.\vcterm.rc

"$(INTDIR)\vcterm.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

