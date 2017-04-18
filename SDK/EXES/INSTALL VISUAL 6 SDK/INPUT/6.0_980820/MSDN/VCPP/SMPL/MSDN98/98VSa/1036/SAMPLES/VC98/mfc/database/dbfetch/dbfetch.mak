# Microsoft Developer Studio Generated NMAKE File, Based on dbfetch.dsp
!IF "$(CFG)" == ""
CFG=dbfetch - Win32 Release
!MESSAGE No configuration specified. Defaulting to dbfetch - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "dbfetch - Win32 Release" && "$(CFG)" != "dbfetch - Win32 Debug" && "$(CFG)" != "dbfetch - Win32 UNICODE debug" && "$(CFG)" != "dbfetch - Win32 UNICODE Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dbfetch.mak" CFG="dbfetch - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dbfetch - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dbfetch - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "dbfetch - Win32 UNICODE debug" (based on "Win32 (x86) Application")
!MESSAGE "dbfetch - Win32 UNICODE Release" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "dbfetch - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\dbfetch.exe"


CLEAN :
	-@erase "$(INTDIR)\bulkset.obj"
	-@erase "$(INTDIR)\datadlg.obj"
	-@erase "$(INTDIR)\dbfetch.obj"
	-@erase "$(INTDIR)\dbfetch.pch"
	-@erase "$(INTDIR)\dbfetch.res"
	-@erase "$(INTDIR)\fetchDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dbfetch.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dbfetch.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dbfetch.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbfetch.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\dbfetch.pdb" /machine:I386 /out:"$(OUTDIR)\dbfetch.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bulkset.obj" \
	"$(INTDIR)\datadlg.obj" \
	"$(INTDIR)\dbfetch.obj" \
	"$(INTDIR)\fetchDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\dbfetch.res"

"$(OUTDIR)\dbfetch.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbfetch - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\dbfetch.exe"


CLEAN :
	-@erase "$(INTDIR)\bulkset.obj"
	-@erase "$(INTDIR)\datadlg.obj"
	-@erase "$(INTDIR)\dbfetch.obj"
	-@erase "$(INTDIR)\dbfetch.pch"
	-@erase "$(INTDIR)\dbfetch.res"
	-@erase "$(INTDIR)\fetchDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\dbfetch.exe"
	-@erase "$(OUTDIR)\dbfetch.ilk"
	-@erase "$(OUTDIR)\dbfetch.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dbfetch.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dbfetch.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbfetch.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\dbfetch.pdb" /debug /machine:I386 /out:"$(OUTDIR)\dbfetch.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bulkset.obj" \
	"$(INTDIR)\datadlg.obj" \
	"$(INTDIR)\dbfetch.obj" \
	"$(INTDIR)\fetchDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\dbfetch.res"

"$(OUTDIR)\dbfetch.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbfetch - Win32 UNICODE debug"

OUTDIR=.\dbfetch_
INTDIR=.\dbfetch_
# Begin Custom Macros
OutDir=.\.\dbfetch_
# End Custom Macros

ALL : "$(OUTDIR)\dbfetch.exe"


CLEAN :
	-@erase "$(INTDIR)\bulkset.obj"
	-@erase "$(INTDIR)\datadlg.obj"
	-@erase "$(INTDIR)\dbfetch.obj"
	-@erase "$(INTDIR)\dbfetch.pch"
	-@erase "$(INTDIR)\dbfetch.res"
	-@erase "$(INTDIR)\fetchDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\dbfetch.exe"
	-@erase "$(OUTDIR)\dbfetch.ilk"
	-@erase "$(OUTDIR)\dbfetch.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\dbfetch.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dbfetch.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbfetch.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\dbfetch.pdb" /debug /machine:I386 /out:"$(OUTDIR)\dbfetch.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bulkset.obj" \
	"$(INTDIR)\datadlg.obj" \
	"$(INTDIR)\dbfetch.obj" \
	"$(INTDIR)\fetchDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\dbfetch.res"

"$(OUTDIR)\dbfetch.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbfetch - Win32 UNICODE Release"

OUTDIR=.\dbfetch0
INTDIR=.\dbfetch0
# Begin Custom Macros
OutDir=.\.\dbfetch0
# End Custom Macros

ALL : "$(OUTDIR)\dbfetch.exe"


CLEAN :
	-@erase "$(INTDIR)\bulkset.obj"
	-@erase "$(INTDIR)\datadlg.obj"
	-@erase "$(INTDIR)\dbfetch.obj"
	-@erase "$(INTDIR)\dbfetch.pch"
	-@erase "$(INTDIR)\dbfetch.res"
	-@erase "$(INTDIR)\fetchDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dbfetch.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\dbfetch.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dbfetch.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbfetch.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\dbfetch.pdb" /machine:I386 /out:"$(OUTDIR)\dbfetch.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bulkset.obj" \
	"$(INTDIR)\datadlg.obj" \
	"$(INTDIR)\dbfetch.obj" \
	"$(INTDIR)\fetchDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\dbfetch.res"

"$(OUTDIR)\dbfetch.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("dbfetch.dep")
!INCLUDE "dbfetch.dep"
!ELSE 
!MESSAGE Warning: cannot find "dbfetch.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dbfetch - Win32 Release" || "$(CFG)" == "dbfetch - Win32 Debug" || "$(CFG)" == "dbfetch - Win32 UNICODE debug" || "$(CFG)" == "dbfetch - Win32 UNICODE Release"
SOURCE=.\bulkset.cpp

"$(INTDIR)\bulkset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dbfetch.pch"


SOURCE=.\datadlg.cpp

"$(INTDIR)\datadlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dbfetch.pch"


SOURCE=.\dbfetch.cpp

"$(INTDIR)\dbfetch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dbfetch.pch"


SOURCE=.\dbfetch.rc

"$(INTDIR)\dbfetch.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\fetchDlg.cpp

"$(INTDIR)\fetchDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dbfetch.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "dbfetch - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dbfetch.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\dbfetch.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "dbfetch - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dbfetch.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\dbfetch.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "dbfetch - Win32 UNICODE debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\dbfetch.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\dbfetch.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "dbfetch - Win32 UNICODE Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\dbfetch.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\dbfetch.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

