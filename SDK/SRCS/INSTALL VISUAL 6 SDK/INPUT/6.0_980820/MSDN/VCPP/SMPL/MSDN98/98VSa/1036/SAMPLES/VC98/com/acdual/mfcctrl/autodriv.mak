# Microsoft Developer Studio Generated NMAKE File, Based on autodriv.dsp
!IF "$(CFG)" == ""
CFG=autodriv - Win32 (80x86) Debug
!MESSAGE No configuration specified.  Defaulting to autodriv - Win32 (80x86)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "autodriv - Win32 (80x86) Debug" && "$(CFG)" !=\
 "autodriv - Win32 (80x86) Release" && "$(CFG)" !=\
 "autodriv - Win32 (80x86) Unicode Debug" && "$(CFG)" !=\
 "autodriv - Win32 (80x86) Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "autodriv.mak" CFG="autodriv - Win32 (80x86) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "autodriv - Win32 (80x86) Debug" (based on "Win32 (x86) Application")
!MESSAGE "autodriv - Win32 (80x86) Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "autodriv - Win32 (80x86) Unicode Debug" (based on\
 "Win32 (x86) Application")
!MESSAGE "autodriv - Win32 (80x86) Unicode Release" (based on\
 "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "autodriv - Win32 (80x86) Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\autodriv.exe" "$(OUTDIR)\autodriv.pch"

CLEAN : 
	-@erase "$(INTDIR)\autoddlg.obj"
	-@erase "$(INTDIR)\autodriv.obj"
	-@erase "$(INTDIR)\autodriv.pch"
	-@erase "$(INTDIR)\autodriv.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\autodriv.exe"
	-@erase "$(OUTDIR)\autodriv.ilk"
	-@erase "$(OUTDIR)\autodriv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "_COM_DEBUG" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

MTL=midl.exe
MTL_PROJ=/mktyplib203 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\autodriv.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\autodriv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\autodriv.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\autodriv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\autoddlg.obj" \
	"$(INTDIR)\autodriv.obj" \
	"$(INTDIR)\autodriv.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\autodriv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\autodriv.exe"

CLEAN : 
	-@erase "$(INTDIR)\autoddlg.obj"
	-@erase "$(INTDIR)\autodriv.obj"
	-@erase "$(INTDIR)\autodriv.pch"
	-@erase "$(INTDIR)\autodriv.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\autodriv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\autodriv.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

MTL=midl.exe
MTL_PROJ=/mktyplib203 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\autodriv.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\autodriv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\autodriv.pdb" /machine:I386 /out:"$(OUTDIR)\autodriv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\autoddlg.obj" \
	"$(INTDIR)\autodriv.obj" \
	"$(INTDIR)\autodriv.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\autodriv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\autodriv.exe"

CLEAN : 
	-@erase "$(INTDIR)\autoddlg.obj"
	-@erase "$(INTDIR)\autodriv.obj"
	-@erase "$(INTDIR)\autodriv.pch"
	-@erase "$(INTDIR)\autodriv.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\autodriv.exe"
	-@erase "$(OUTDIR)\autodriv.ilk"
	-@erase "$(OUTDIR)\autodriv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\autodriv.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\UniDebug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

MTL=midl.exe
MTL_PROJ=/mktyplib203 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\autodriv.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\autodriv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\autodriv.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\autodriv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\autoddlg.obj" \
	"$(INTDIR)\autodriv.obj" \
	"$(INTDIR)\autodriv.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\autodriv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Release"

OUTDIR=.\UniRel
INTDIR=.\UniRel
# Begin Custom Macros
OutDir=.\.\UniRel
# End Custom Macros

ALL : "$(OUTDIR)\autodriv.exe"

CLEAN : 
	-@erase "$(INTDIR)\autoddlg.obj"
	-@erase "$(INTDIR)\autodriv.obj"
	-@erase "$(INTDIR)\autodriv.pch"
	-@erase "$(INTDIR)\autodriv.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\autodriv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\autodriv.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\UniRel/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

MTL=midl.exe
MTL_PROJ=/mktyplib203 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\autodriv.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\autodriv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\autodriv.pdb" /machine:I386\
 /out:"$(OUTDIR)\autodriv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\autoddlg.obj" \
	"$(INTDIR)\autodriv.obj" \
	"$(INTDIR)\autodriv.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\autodriv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "autodriv - Win32 (80x86) Debug" || "$(CFG)" ==\
 "autodriv - Win32 (80x86) Release" || "$(CFG)" ==\
 "autodriv - Win32 (80x86) Unicode Debug" || "$(CFG)" ==\
 "autodriv - Win32 (80x86) Unicode Release"
SOURCE=.\autoddlg.cpp
DEP_CPP_AUTOD=\
	".\Autoddlg.h"\
	".\Autodriv.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "autodriv - Win32 (80x86) Debug"


"$(INTDIR)\autoddlg.obj" : $(SOURCE) $(DEP_CPP_AUTOD) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Release"


"$(INTDIR)\autoddlg.obj" : $(SOURCE) $(DEP_CPP_AUTOD) "$(INTDIR)"\
 "$(INTDIR)\autodriv.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Debug"


"$(INTDIR)\autoddlg.obj" : $(SOURCE) $(DEP_CPP_AUTOD) "$(INTDIR)"\
 "$(INTDIR)\autodriv.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Release"


"$(INTDIR)\autoddlg.obj" : $(SOURCE) $(DEP_CPP_AUTOD) "$(INTDIR)"\
 "$(INTDIR)\autodriv.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\autodriv.cpp
DEP_CPP_AUTODR=\
	".\Autoddlg.h"\
	".\Autodriv.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "autodriv - Win32 (80x86) Debug"


"$(INTDIR)\autodriv.obj" : $(SOURCE) $(DEP_CPP_AUTODR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Release"


"$(INTDIR)\autodriv.obj" : $(SOURCE) $(DEP_CPP_AUTODR) "$(INTDIR)"\
 "$(INTDIR)\autodriv.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Debug"


"$(INTDIR)\autodriv.obj" : $(SOURCE) $(DEP_CPP_AUTODR) "$(INTDIR)"\
 "$(INTDIR)\autodriv.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Release"


"$(INTDIR)\autodriv.obj" : $(SOURCE) $(DEP_CPP_AUTODR) "$(INTDIR)"\
 "$(INTDIR)\autodriv.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\autodriv.rc
DEP_RSC_AUTODRI=\
	".\res\autodriv.ico"\
	".\res\autodriv.rc2"\
	".\res\icon1.ico"\
	

!IF  "$(CFG)" == "autodriv - Win32 (80x86) Debug"


"$(INTDIR)\autodriv.res" : $(SOURCE) $(DEP_RSC_AUTODRI) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Release"


"$(INTDIR)\autodriv.res" : $(SOURCE) $(DEP_RSC_AUTODRI) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Debug"


"$(INTDIR)\autodriv.res" : $(SOURCE) $(DEP_RSC_AUTODRI) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Release"


"$(INTDIR)\autodriv.res" : $(SOURCE) $(DEP_RSC_AUTODRI) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "autodriv - Win32 (80x86) Debug"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\autodriv.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "_COM_DEBUG" /Fp"$(INTDIR)\autodriv.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Release"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\autodriv.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\autodriv.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Debug"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\autodriv.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\autodriv.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "autodriv - Win32 (80x86) Unicode Release"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\autodriv.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\autodriv.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\Autoddlg.h
SOURCE=.\Autodriv.h
SOURCE=.\Stdafx.h
SOURCE=.\res\autodriv.ico
SOURCE=.\res\autodriv.rc2

!ENDIF 

