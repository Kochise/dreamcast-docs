# Microsoft Developer Studio Generated NMAKE File, Based on mdibind.dsp
!IF "$(CFG)" == ""
CFG=MDIBind - Win32 Release
!MESSAGE No configuration specified. Defaulting to MDIBind - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "MDIBind - Win32 Release" && "$(CFG)" != "MDIBind - Win32 Debug" && "$(CFG)" != "MDIBind - Win32 Unicode Debug" && "$(CFG)" != "MDIBind - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mdibind.mak" CFG="MDIBind - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MDIBind - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MDIBind - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDIBind - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDIBind - Win32 Unicode Release" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "MDIBind - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mdibind.exe"


CLEAN :
	-@erase "$(INTDIR)\DSNDlg.obj"
	-@erase "$(INTDIR)\gridfrm.obj"
	-@erase "$(INTDIR)\gridview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\maskfrm.obj"
	-@erase "$(INTDIR)\maskview.obj"
	-@erase "$(INTDIR)\MDIBind.obj"
	-@erase "$(INTDIR)\mdibind.pch"
	-@erase "$(INTDIR)\MDIBind.res"
	-@erase "$(INTDIR)\MDIDoc.obj"
	-@erase "$(INTDIR)\msdgrid.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\RDCDlg.obj"
	-@erase "$(INTDIR)\RDCFrm.obj"
	-@erase "$(INTDIR)\RDCView.obj"
	-@erase "$(INTDIR)\rdocol.obj"
	-@erase "$(INTDIR)\rdocols.obj"
	-@erase "$(INTDIR)\rdoreslt.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mdibind.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\mdibind.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MDIBind.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mdibind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\mdibind.pdb" /machine:I386 /out:"$(OUTDIR)\mdibind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DSNDlg.obj" \
	"$(INTDIR)\gridfrm.obj" \
	"$(INTDIR)\gridview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\maskfrm.obj" \
	"$(INTDIR)\maskview.obj" \
	"$(INTDIR)\MDIBind.obj" \
	"$(INTDIR)\MDIDoc.obj" \
	"$(INTDIR)\msdgrid.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\RDCDlg.obj" \
	"$(INTDIR)\RDCFrm.obj" \
	"$(INTDIR)\RDCView.obj" \
	"$(INTDIR)\rdocol.obj" \
	"$(INTDIR)\rdocols.obj" \
	"$(INTDIR)\rdoreslt.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MDIBind.res"

"$(OUTDIR)\mdibind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MDIBind - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mdibind.exe"


CLEAN :
	-@erase "$(INTDIR)\DSNDlg.obj"
	-@erase "$(INTDIR)\gridfrm.obj"
	-@erase "$(INTDIR)\gridview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\maskfrm.obj"
	-@erase "$(INTDIR)\maskview.obj"
	-@erase "$(INTDIR)\MDIBind.obj"
	-@erase "$(INTDIR)\mdibind.pch"
	-@erase "$(INTDIR)\MDIBind.res"
	-@erase "$(INTDIR)\MDIDoc.obj"
	-@erase "$(INTDIR)\msdgrid.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\RDCDlg.obj"
	-@erase "$(INTDIR)\RDCFrm.obj"
	-@erase "$(INTDIR)\RDCView.obj"
	-@erase "$(INTDIR)\rdocol.obj"
	-@erase "$(INTDIR)\rdocols.obj"
	-@erase "$(INTDIR)\rdoreslt.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mdibind.exe"
	-@erase "$(OUTDIR)\mdibind.ilk"
	-@erase "$(OUTDIR)\mdibind.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\mdibind.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MDIBind.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mdibind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\mdibind.pdb" /debug /machine:I386 /out:"$(OUTDIR)\mdibind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DSNDlg.obj" \
	"$(INTDIR)\gridfrm.obj" \
	"$(INTDIR)\gridview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\maskfrm.obj" \
	"$(INTDIR)\maskview.obj" \
	"$(INTDIR)\MDIBind.obj" \
	"$(INTDIR)\MDIDoc.obj" \
	"$(INTDIR)\msdgrid.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\RDCDlg.obj" \
	"$(INTDIR)\RDCFrm.obj" \
	"$(INTDIR)\RDCView.obj" \
	"$(INTDIR)\rdocol.obj" \
	"$(INTDIR)\rdocols.obj" \
	"$(INTDIR)\rdoreslt.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MDIBind.res"

"$(OUTDIR)\mdibind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MDIBind - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\mdibind.exe"


CLEAN :
	-@erase "$(INTDIR)\DSNDlg.obj"
	-@erase "$(INTDIR)\gridfrm.obj"
	-@erase "$(INTDIR)\gridview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\maskfrm.obj"
	-@erase "$(INTDIR)\maskview.obj"
	-@erase "$(INTDIR)\MDIBind.obj"
	-@erase "$(INTDIR)\mdibind.pch"
	-@erase "$(INTDIR)\MDIBind.res"
	-@erase "$(INTDIR)\MDIDoc.obj"
	-@erase "$(INTDIR)\msdgrid.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\RDCDlg.obj"
	-@erase "$(INTDIR)\RDCFrm.obj"
	-@erase "$(INTDIR)\RDCView.obj"
	-@erase "$(INTDIR)\rdocol.obj"
	-@erase "$(INTDIR)\rdocols.obj"
	-@erase "$(INTDIR)\rdoreslt.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mdibind.exe"
	-@erase "$(OUTDIR)\mdibind.ilk"
	-@erase "$(OUTDIR)\mdibind.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\mdibind.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MDIBind.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mdibind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\mdibind.pdb" /debug /machine:I386 /out:"$(OUTDIR)\mdibind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DSNDlg.obj" \
	"$(INTDIR)\gridfrm.obj" \
	"$(INTDIR)\gridview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\maskfrm.obj" \
	"$(INTDIR)\maskview.obj" \
	"$(INTDIR)\MDIBind.obj" \
	"$(INTDIR)\MDIDoc.obj" \
	"$(INTDIR)\msdgrid.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\RDCDlg.obj" \
	"$(INTDIR)\RDCFrm.obj" \
	"$(INTDIR)\RDCView.obj" \
	"$(INTDIR)\rdocol.obj" \
	"$(INTDIR)\rdocols.obj" \
	"$(INTDIR)\rdoreslt.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MDIBind.res"

"$(OUTDIR)\mdibind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MDIBind - Win32 Unicode Release"

OUTDIR=.\UniRel
INTDIR=.\UniRel
# Begin Custom Macros
OutDir=.\.\UniRel
# End Custom Macros

ALL : "$(OUTDIR)\mdibind.exe"


CLEAN :
	-@erase "$(INTDIR)\DSNDlg.obj"
	-@erase "$(INTDIR)\gridfrm.obj"
	-@erase "$(INTDIR)\gridview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\maskfrm.obj"
	-@erase "$(INTDIR)\maskview.obj"
	-@erase "$(INTDIR)\MDIBind.obj"
	-@erase "$(INTDIR)\mdibind.pch"
	-@erase "$(INTDIR)\MDIBind.res"
	-@erase "$(INTDIR)\MDIDoc.obj"
	-@erase "$(INTDIR)\msdgrid.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\rdc.obj"
	-@erase "$(INTDIR)\RDCDlg.obj"
	-@erase "$(INTDIR)\RDCFrm.obj"
	-@erase "$(INTDIR)\RDCView.obj"
	-@erase "$(INTDIR)\rdocol.obj"
	-@erase "$(INTDIR)\rdocols.obj"
	-@erase "$(INTDIR)\rdoreslt.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mdibind.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\mdibind.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MDIBind.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mdibind.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\mdibind.pdb" /machine:I386 /out:"$(OUTDIR)\mdibind.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DSNDlg.obj" \
	"$(INTDIR)\gridfrm.obj" \
	"$(INTDIR)\gridview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\maskfrm.obj" \
	"$(INTDIR)\maskview.obj" \
	"$(INTDIR)\MDIBind.obj" \
	"$(INTDIR)\MDIDoc.obj" \
	"$(INTDIR)\msdgrid.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\rdc.obj" \
	"$(INTDIR)\RDCDlg.obj" \
	"$(INTDIR)\RDCFrm.obj" \
	"$(INTDIR)\RDCView.obj" \
	"$(INTDIR)\rdocol.obj" \
	"$(INTDIR)\rdocols.obj" \
	"$(INTDIR)\rdoreslt.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MDIBind.res"

"$(OUTDIR)\mdibind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("mdibind.dep")
!INCLUDE "mdibind.dep"
!ELSE 
!MESSAGE Warning: cannot find "mdibind.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MDIBind - Win32 Release" || "$(CFG)" == "MDIBind - Win32 Debug" || "$(CFG)" == "MDIBind - Win32 Unicode Debug" || "$(CFG)" == "MDIBind - Win32 Unicode Release"
SOURCE=.\DSNDlg.cpp

"$(INTDIR)\DSNDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\gridfrm.cpp

"$(INTDIR)\gridfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\gridview.cpp

"$(INTDIR)\gridview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\maskfrm.cpp

"$(INTDIR)\maskfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\maskview.cpp

"$(INTDIR)\maskview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\MDIBind.cpp

"$(INTDIR)\MDIBind.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\MDIBind.rc

"$(INTDIR)\MDIBind.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MDIDoc.cpp

"$(INTDIR)\MDIDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\msdgrid.cpp

"$(INTDIR)\msdgrid.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\msmask.cpp

"$(INTDIR)\msmask.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\rdc.cpp

"$(INTDIR)\rdc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\RDCDlg.cpp

"$(INTDIR)\RDCDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\RDCFrm.cpp

"$(INTDIR)\RDCFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\RDCView.cpp

"$(INTDIR)\RDCView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\rdocol.cpp

"$(INTDIR)\rdocol.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\rdocols.cpp

"$(INTDIR)\rdocols.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\rdoreslt.cpp

"$(INTDIR)\rdoreslt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mdibind.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MDIBind - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\mdibind.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\mdibind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MDIBind - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\mdibind.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\mdibind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MDIBind - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\mdibind.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\mdibind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MDIBind - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\mdibind.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\mdibind.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

