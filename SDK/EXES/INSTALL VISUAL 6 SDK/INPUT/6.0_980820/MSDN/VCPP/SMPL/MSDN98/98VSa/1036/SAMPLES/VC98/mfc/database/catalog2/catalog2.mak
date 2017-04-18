# Microsoft Developer Studio Generated NMAKE File, Based on catalog2.dsp
!IF "$(CFG)" == ""
CFG=catalog2 - Win32 Release
!MESSAGE No configuration specified. Defaulting to catalog2 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "catalog2 - Win32 Release" && "$(CFG)" != "catalog2 - Win32 Debug" && "$(CFG)" != "catalog2 - Win32 UNICODE Debug" && "$(CFG)" != "catalog2 - Win32 UNICODE Release" && "$(CFG)" != "catalog2 - Win32 DLL Debug" && "$(CFG)" != "catalog2 - Win32 DLL Release" && "$(CFG)" != "catalog2 - Win32 UNICODE DLL Debug" && "$(CFG)" != "catalog2 - Win32 UNICODE DLL Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "catalog2.mak" CFG="catalog2 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "catalog2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "catalog2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "catalog2 - Win32 UNICODE Debug" (based on "Win32 (x86) Application")
!MESSAGE "catalog2 - Win32 UNICODE Release" (based on "Win32 (x86) Application")
!MESSAGE "catalog2 - Win32 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "catalog2 - Win32 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "catalog2 - Win32 UNICODE DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "catalog2 - Win32 UNICODE DLL Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "catalog2 - Win32 Release"

OUTDIR=.\StubRel
INTDIR=.\StubRel
# Begin Custom Macros
OutDir=.\StubRel
# End Custom Macros

ALL : "$(OUTDIR)\catalog2.exe"


CLEAN :
	-@erase "$(INTDIR)\cat2doc.obj"
	-@erase "$(INTDIR)\cat2view.obj"
	-@erase "$(INTDIR)\catalog2.obj"
	-@erase "$(INTDIR)\catalog2.pch"
	-@erase "$(INTDIR)\catalog2.res"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\colpage.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\settings.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tabpage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\catalog2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog2.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\catalog2.pdb" /machine:I386 /out:"$(OUTDIR)\catalog2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cat2doc.obj" \
	"$(INTDIR)\cat2view.obj" \
	"$(INTDIR)\catalog2.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\colpage.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\settings.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tabpage.obj" \
	"$(INTDIR)\catalog2.res"

"$(OUTDIR)\catalog2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "catalog2 - Win32 Debug"

OUTDIR=.\StubDebug
INTDIR=.\StubDebug
# Begin Custom Macros
OutDir=.\StubDebug
# End Custom Macros

ALL : "$(OUTDIR)\catalog2.exe"


CLEAN :
	-@erase "$(INTDIR)\cat2doc.obj"
	-@erase "$(INTDIR)\cat2view.obj"
	-@erase "$(INTDIR)\catalog2.obj"
	-@erase "$(INTDIR)\catalog2.pch"
	-@erase "$(INTDIR)\catalog2.res"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\colpage.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\settings.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tabpage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\catalog2.exe"
	-@erase "$(OUTDIR)\catalog2.ilk"
	-@erase "$(OUTDIR)\catalog2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog2.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\catalog2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\catalog2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cat2doc.obj" \
	"$(INTDIR)\cat2view.obj" \
	"$(INTDIR)\catalog2.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\colpage.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\settings.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tabpage.obj" \
	"$(INTDIR)\catalog2.res"

"$(OUTDIR)\catalog2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "catalog2 - Win32 UNICODE Debug"

OUTDIR=.\StubUniDbg
INTDIR=.\StubUniDbg
# Begin Custom Macros
OutDir=.\StubUniDbg
# End Custom Macros

ALL : "$(OUTDIR)\catalog2.exe"


CLEAN :
	-@erase "$(INTDIR)\cat2doc.obj"
	-@erase "$(INTDIR)\cat2view.obj"
	-@erase "$(INTDIR)\catalog2.obj"
	-@erase "$(INTDIR)\catalog2.pch"
	-@erase "$(INTDIR)\catalog2.res"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\colpage.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\settings.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tabpage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\catalog2.exe"
	-@erase "$(OUTDIR)\catalog2.ilk"
	-@erase "$(OUTDIR)\catalog2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\catalog2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog2.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\catalog2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\catalog2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cat2doc.obj" \
	"$(INTDIR)\cat2view.obj" \
	"$(INTDIR)\catalog2.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\colpage.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\settings.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tabpage.obj" \
	"$(INTDIR)\catalog2.res"

"$(OUTDIR)\catalog2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "catalog2 - Win32 UNICODE Release"

OUTDIR=.\StubUniRel
INTDIR=.\StubUniRel
# Begin Custom Macros
OutDir=.\StubUniRel
# End Custom Macros

ALL : "$(OUTDIR)\catalog2.exe"


CLEAN :
	-@erase "$(INTDIR)\cat2doc.obj"
	-@erase "$(INTDIR)\cat2view.obj"
	-@erase "$(INTDIR)\catalog2.obj"
	-@erase "$(INTDIR)\catalog2.pch"
	-@erase "$(INTDIR)\catalog2.res"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\colpage.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\settings.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tabpage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\catalog2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\catalog2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog2.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\catalog2.pdb" /machine:I386 /out:"$(OUTDIR)\catalog2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cat2doc.obj" \
	"$(INTDIR)\cat2view.obj" \
	"$(INTDIR)\catalog2.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\colpage.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\settings.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tabpage.obj" \
	"$(INTDIR)\catalog2.res"

"$(OUTDIR)\catalog2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "catalog2 - Win32 DLL Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\catalog2.exe"


CLEAN :
	-@erase "$(INTDIR)\cat2doc.obj"
	-@erase "$(INTDIR)\cat2view.obj"
	-@erase "$(INTDIR)\catalog2.obj"
	-@erase "$(INTDIR)\catalog2.pch"
	-@erase "$(INTDIR)\catalog2.res"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\colpage.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\settings.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tabpage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\catalog2.exe"
	-@erase "$(OUTDIR)\catalog2.ilk"
	-@erase "$(OUTDIR)\catalog2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog2.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\catalog2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\catalog2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cat2doc.obj" \
	"$(INTDIR)\cat2view.obj" \
	"$(INTDIR)\catalog2.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\colpage.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\settings.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tabpage.obj" \
	"$(INTDIR)\catalog2.res"

"$(OUTDIR)\catalog2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "catalog2 - Win32 DLL Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\catalog2.exe"


CLEAN :
	-@erase "$(INTDIR)\cat2doc.obj"
	-@erase "$(INTDIR)\cat2view.obj"
	-@erase "$(INTDIR)\catalog2.obj"
	-@erase "$(INTDIR)\catalog2.pch"
	-@erase "$(INTDIR)\catalog2.res"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\colpage.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\settings.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tabpage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\catalog2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog2.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\catalog2.pdb" /machine:I386 /out:"$(OUTDIR)\catalog2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cat2doc.obj" \
	"$(INTDIR)\cat2view.obj" \
	"$(INTDIR)\catalog2.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\colpage.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\settings.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tabpage.obj" \
	"$(INTDIR)\catalog2.res"

"$(OUTDIR)\catalog2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "catalog2 - Win32 UNICODE DLL Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\catalog2.exe"


CLEAN :
	-@erase "$(INTDIR)\cat2doc.obj"
	-@erase "$(INTDIR)\cat2view.obj"
	-@erase "$(INTDIR)\catalog2.obj"
	-@erase "$(INTDIR)\catalog2.pch"
	-@erase "$(INTDIR)\catalog2.res"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\colpage.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\settings.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tabpage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\catalog2.exe"
	-@erase "$(OUTDIR)\catalog2.ilk"
	-@erase "$(OUTDIR)\catalog2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog2.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\catalog2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\catalog2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cat2doc.obj" \
	"$(INTDIR)\cat2view.obj" \
	"$(INTDIR)\catalog2.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\colpage.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\settings.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tabpage.obj" \
	"$(INTDIR)\catalog2.res"

"$(OUTDIR)\catalog2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "catalog2 - Win32 UNICODE DLL Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\catalog2.exe"


CLEAN :
	-@erase "$(INTDIR)\cat2doc.obj"
	-@erase "$(INTDIR)\cat2view.obj"
	-@erase "$(INTDIR)\catalog2.obj"
	-@erase "$(INTDIR)\catalog2.pch"
	-@erase "$(INTDIR)\catalog2.res"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\colpage.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\settings.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\tabpage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\catalog2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\catalog2.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\catalog2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\catalog2.pdb" /machine:I386 /out:"$(OUTDIR)\catalog2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cat2doc.obj" \
	"$(INTDIR)\cat2view.obj" \
	"$(INTDIR)\catalog2.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\colpage.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\settings.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\tabpage.obj" \
	"$(INTDIR)\catalog2.res"

"$(OUTDIR)\catalog2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("catalog2.dep")
!INCLUDE "catalog2.dep"
!ELSE 
!MESSAGE Warning: cannot find "catalog2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "catalog2 - Win32 Release" || "$(CFG)" == "catalog2 - Win32 Debug" || "$(CFG)" == "catalog2 - Win32 UNICODE Debug" || "$(CFG)" == "catalog2 - Win32 UNICODE Release" || "$(CFG)" == "catalog2 - Win32 DLL Debug" || "$(CFG)" == "catalog2 - Win32 DLL Release" || "$(CFG)" == "catalog2 - Win32 UNICODE DLL Debug" || "$(CFG)" == "catalog2 - Win32 UNICODE DLL Release"
SOURCE=.\cat2doc.cpp

"$(INTDIR)\cat2doc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog2.pch"


SOURCE=.\cat2view.cpp

"$(INTDIR)\cat2view.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog2.pch"


SOURCE=.\catalog2.cpp

"$(INTDIR)\catalog2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog2.pch"


SOURCE=.\catalog2.rc

"$(INTDIR)\catalog2.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\catsets.cpp

"$(INTDIR)\catsets.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog2.pch"


SOURCE=.\colpage.cpp

"$(INTDIR)\colpage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog2.pch"


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog2.pch"


SOURCE=.\settings.cpp

"$(INTDIR)\settings.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog2.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "catalog2 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "catalog2 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "catalog2 - Win32 UNICODE Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\catalog2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "catalog2 - Win32 UNICODE Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\catalog2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "catalog2 - Win32 DLL Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "catalog2 - Win32 DLL Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "catalog2 - Win32 UNICODE DLL Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "catalog2 - Win32 UNICODE DLL Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\catalog2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\catalog2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tabpage.cpp

"$(INTDIR)\tabpage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\catalog2.pch"



!ENDIF 

