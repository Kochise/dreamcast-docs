# Microsoft Developer Studio Generated NMAKE File, Based on TVXSamp.dsp
!IF "$(CFG)" == ""
CFG=TVXSamp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TVXSamp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TVXSamp - Win32 Release" && "$(CFG)" !=\
 "TVXSamp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TVXSamp.mak" CFG="TVXSamp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TVXSamp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TVXSamp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TVXSamp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TVXSamp.exe" "$(OUTDIR)\TVXSamp.tlb"

!ELSE 

ALL : "$(OUTDIR)\TVXSamp.exe" "$(OUTDIR)\TVXSamp.tlb"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DlgProxy.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tvdisp.obj"
	-@erase "$(INTDIR)\TVXSamp.obj"
	-@erase "$(INTDIR)\TVXSamp.pch"
	-@erase "$(INTDIR)\TVXSamp.res"
	-@erase "$(INTDIR)\TVXSamp.tlb"
	-@erase "$(INTDIR)\TVXSampDlg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\TVXSamp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\TVXSamp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TVXSamp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TVXSamp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mfc42d.lib mfcs42d.lib msvcrtd.lib kernel32.lib user32.lib\
 /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\TVXSamp.pdb" /machine:I386 /out:"$(OUTDIR)\TVXSamp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DlgProxy.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tvdisp.obj" \
	"$(INTDIR)\TVXSamp.obj" \
	"$(INTDIR)\TVXSamp.res" \
	"$(INTDIR)\TVXSampDlg.obj"

"$(OUTDIR)\TVXSamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TVXSamp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TVXSamp.exe" "$(OUTDIR)\TVXSamp.tlb"

!ELSE 

ALL : "$(OUTDIR)\TVXSamp.exe" "$(OUTDIR)\TVXSamp.tlb"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DlgProxy.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tvdisp.obj"
	-@erase "$(INTDIR)\TVXSamp.obj"
	-@erase "$(INTDIR)\TVXSamp.pch"
	-@erase "$(INTDIR)\TVXSamp.res"
	-@erase "$(INTDIR)\TVXSamp.tlb"
	-@erase "$(INTDIR)\TVXSampDlg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\TVXSamp.exe"
	-@erase "$(OUTDIR)\TVXSamp.ilk"
	-@erase "$(OUTDIR)\TVXSamp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\TVXSamp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TVXSamp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TVXSamp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mfc42d.lib mfcs42d.lib msvcrtd.lib kernel32.lib user32.lib\
 /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\TVXSamp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TVXSamp.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DlgProxy.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tvdisp.obj" \
	"$(INTDIR)\TVXSamp.obj" \
	"$(INTDIR)\TVXSamp.res" \
	"$(INTDIR)\TVXSampDlg.obj"

"$(OUTDIR)\TVXSamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "TVXSamp - Win32 Release" || "$(CFG)" ==\
 "TVXSamp - Win32 Debug"
SOURCE=.\DlgProxy.cpp

!IF  "$(CFG)" == "TVXSamp - Win32 Release"

DEP_CPP_DLGPR=\
	".\DlgProxy.h"\
	".\StdAfx.h"\
	".\TVXSamp.h"\
	".\TVXSampDlg.h"\
	

"$(INTDIR)\DlgProxy.obj" : $(SOURCE) $(DEP_CPP_DLGPR) "$(INTDIR)"\
 "$(INTDIR)\TVXSamp.pch"


!ELSEIF  "$(CFG)" == "TVXSamp - Win32 Debug"

DEP_CPP_DLGPR=\
	".\DlgProxy.h"\
	".\TVXSamp.h"\
	".\TVXSampDlg.h"\
	

"$(INTDIR)\DlgProxy.obj" : $(SOURCE) $(DEP_CPP_DLGPR) "$(INTDIR)"\
 "$(INTDIR)\TVXSamp.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "TVXSamp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\TVXSamp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TVXSamp.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TVXSamp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\TVXSamp.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TVXSamp.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tvdisp.cpp

!IF  "$(CFG)" == "TVXSamp - Win32 Release"

DEP_CPP_TVDIS=\
	".\StdAfx.h"\
	".\Tvdisp.h"\
	

"$(INTDIR)\tvdisp.obj" : $(SOURCE) $(DEP_CPP_TVDIS) "$(INTDIR)"\
 "$(INTDIR)\TVXSamp.pch"


!ELSEIF  "$(CFG)" == "TVXSamp - Win32 Debug"

DEP_CPP_TVDIS=\
	".\Tvdisp.h"\
	

"$(INTDIR)\tvdisp.obj" : $(SOURCE) $(DEP_CPP_TVDIS) "$(INTDIR)"\
 "$(INTDIR)\TVXSamp.pch"


!ENDIF 

SOURCE=.\TVXSamp.cpp

!IF  "$(CFG)" == "TVXSamp - Win32 Release"

DEP_CPP_TVXSA=\
	".\StdAfx.h"\
	".\Tvdisp.h"\
	".\TVXSamp.h"\
	".\TVXSampDlg.h"\
	

"$(INTDIR)\TVXSamp.obj" : $(SOURCE) $(DEP_CPP_TVXSA) "$(INTDIR)"\
 "$(INTDIR)\TVXSamp.pch"


!ELSEIF  "$(CFG)" == "TVXSamp - Win32 Debug"

DEP_CPP_TVXSA=\
	".\Tvdisp.h"\
	".\TVXSamp.h"\
	".\TVXSampDlg.h"\
	

"$(INTDIR)\TVXSamp.obj" : $(SOURCE) $(DEP_CPP_TVXSA) "$(INTDIR)"\
 "$(INTDIR)\TVXSamp.pch"


!ENDIF 

SOURCE=.\TVXSamp.odl

!IF  "$(CFG)" == "TVXSamp - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\TVXSamp.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\TVXSamp.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TVXSamp - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\TVXSamp.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\TVXSamp.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TVXSamp.rc
DEP_RSC_TVXSAM=\
	".\res\TVXSamp.ico"\
	".\res\TVXSamp.rc2"\
	

!IF  "$(CFG)" == "TVXSamp - Win32 Release"


"$(INTDIR)\TVXSamp.res" : $(SOURCE) $(DEP_RSC_TVXSAM) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\TVXSamp.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "TVXSamp - Win32 Debug"


"$(INTDIR)\TVXSamp.res" : $(SOURCE) $(DEP_RSC_TVXSAM) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\TVXSamp.res" /i "Debug" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ENDIF 

SOURCE=.\TVXSampDlg.cpp

!IF  "$(CFG)" == "TVXSamp - Win32 Release"

DEP_CPP_TVXSAMP=\
	".\DlgProxy.h"\
	".\StdAfx.h"\
	".\Tvdisp.h"\
	".\TVXSamp.h"\
	".\TVXSampDlg.h"\
	

"$(INTDIR)\TVXSampDlg.obj" : $(SOURCE) $(DEP_CPP_TVXSAMP) "$(INTDIR)"\
 "$(INTDIR)\TVXSamp.pch"


!ELSEIF  "$(CFG)" == "TVXSamp - Win32 Debug"

DEP_CPP_TVXSAMP=\
	".\DlgProxy.h"\
	".\Tvdisp.h"\
	".\TVXSamp.h"\
	".\TVXSampDlg.h"\
	

"$(INTDIR)\TVXSampDlg.obj" : $(SOURCE) $(DEP_CPP_TVXSAMP) "$(INTDIR)"\
 "$(INTDIR)\TVXSamp.pch"


!ENDIF 


!ENDIF 

