# Microsoft Developer Studio Generated NMAKE File, Based on Donut.dsp
!IF "$(CFG)" == ""
CFG=Donut - Win32 Release
!MESSAGE No configuration specified. Defaulting to Donut - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Donut - Win32 Release" && "$(CFG)" != "Donut - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Donut.mak" CFG="Donut - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Donut - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Donut - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Donut - Win32 Release"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Donut.exe"

!ELSE 

ALL : "$(OUTDIR)\Donut.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\donut.obj"
	-@erase "$(INTDIR)\donut.res"
	-@erase "$(INTDIR)\dxa.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Donut.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\Donut.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\donut.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Donut.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib guids.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\Donut.pdb" /machine:I386 /out:"$(OUTDIR)\Donut.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\donut.obj" \
	"$(INTDIR)\donut.res" \
	"$(INTDIR)\dxa.obj"

"$(OUTDIR)\Donut.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Donut - Win32 Debug"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Donut.exe"

!ELSE 

ALL : "$(OUTDIR)\Donut.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\donut.obj"
	-@erase "$(INTDIR)\donut.res"
	-@erase "$(INTDIR)\dxa.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Donut.exe"
	-@erase "$(OUTDIR)\Donut.ilk"
	-@erase "$(OUTDIR)\Donut.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\Donut.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\donut.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Donut.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib guids.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\Donut.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Donut.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\donut.obj" \
	"$(INTDIR)\donut.res" \
	"$(INTDIR)\dxa.obj"

"$(OUTDIR)\Donut.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(CFG)" == "Donut - Win32 Release" || "$(CFG)" == "Donut - Win32 Debug"
SOURCE=.\ddutil.cpp
DEP_CPP_DDUTI=\
	".\ddutil.h"\
	

"$(INTDIR)\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"


SOURCE=.\donut.cpp
DEP_CPP_DONUT=\
	".\ddutil.h"\
	".\dxa.h"\
	{$(INCLUDE)}"ddrawex.h"\
	

"$(INTDIR)\donut.obj" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"


SOURCE=.\donut.rc
DEP_RSC_DONUT_=\
	".\DONUT.BMP"\
	

"$(INTDIR)\donut.res" : $(SOURCE) $(DEP_RSC_DONUT_) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\dxa.cpp
DEP_CPP_DXA_C=\
	".\dxa.h"\
	

"$(INTDIR)\dxa.obj" : $(SOURCE) $(DEP_CPP_DXA_C) "$(INTDIR)"



!ENDIF 
