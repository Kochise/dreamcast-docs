# Microsoft Developer Studio Generated NMAKE File, Based on minimal.dsp
!IF "$(CFG)" == ""
CFG=minimal - Win32 Release
!MESSAGE No configuration specified. Defaulting to minimal - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "minimal - Win32 Release" && "$(CFG)" != "minimal - Win32 Debug" && "$(CFG)" != "minimal - Win32 Unicode Release" && "$(CFG)" != "minimal - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "minimal.mak" CFG="minimal - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "minimal - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "minimal - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "minimal - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "minimal - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "minimal - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\minimal.dll"


CLEAN :
	-@erase "$(INTDIR)\minimal.obj"
	-@erase "$(INTDIR)\minimal.pch"
	-@erase "$(INTDIR)\MinObj.obj"
	-@erase "$(INTDIR)\premin.obj"
	-@erase "$(OUTDIR)\minimal.dll"
	-@erase "$(OUTDIR)\minimal.exp"
	-@erase "$(OUTDIR)\minimal.lib"
	-@erase "$(OUTDIR)\minimal.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O2 /D "NDEBUG" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_NO_CONNECTION_POINTS" /Fp"$(INTDIR)\minimal.pch" /Yu"premin.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\minimal.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\minimal.pdb" /map:"$(INTDIR)\minimal.map" /machine:I386 /def:".\minimal.def" /out:"$(OUTDIR)\minimal.dll" /implib:"$(OUTDIR)\minimal.lib" /merge:.idata=.data /WS:AGGRESSIVE /FIXED 
DEF_FILE= \
	".\minimal.def"
LINK32_OBJS= \
	"$(INTDIR)\minimal.obj" \
	"$(INTDIR)\MinObj.obj" \
	"$(INTDIR)\premin.obj"

"$(OUTDIR)\minimal.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "minimal - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\minimal.dll"


CLEAN :
	-@erase "$(INTDIR)\minimal.obj"
	-@erase "$(INTDIR)\minimal.pch"
	-@erase "$(INTDIR)\MinObj.obj"
	-@erase "$(INTDIR)\premin.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\minimal.dll"
	-@erase "$(OUTDIR)\minimal.exp"
	-@erase "$(OUTDIR)\minimal.ilk"
	-@erase "$(OUTDIR)\minimal.lib"
	-@erase "$(OUTDIR)\minimal.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_NO_CONNECTION_POINTS" /Fp"$(INTDIR)\minimal.pch" /Yu"premin.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\minimal.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\minimal.pdb" /debug /machine:I386 /def:".\minimal.def" /out:"$(OUTDIR)\minimal.dll" /implib:"$(OUTDIR)\minimal.lib" 
DEF_FILE= \
	".\minimal.def"
LINK32_OBJS= \
	"$(INTDIR)\minimal.obj" \
	"$(INTDIR)\MinObj.obj" \
	"$(INTDIR)\premin.obj"

"$(OUTDIR)\minimal.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "minimal - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\minimal.dll"


CLEAN :
	-@erase "$(INTDIR)\minimal.obj"
	-@erase "$(INTDIR)\minimal.pch"
	-@erase "$(INTDIR)\MinObj.obj"
	-@erase "$(INTDIR)\premin.obj"
	-@erase "$(OUTDIR)\minimal.dll"
	-@erase "$(OUTDIR)\minimal.exp"
	-@erase "$(OUTDIR)\minimal.lib"
	-@erase "$(OUTDIR)\minimal.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O2 /D "_UNICODE" /D "NDEBUG" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_NO_CONNECTION_POINTS" /Fp"$(INTDIR)\minimal.pch" /Yu"premin.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\minimal.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\minimal.pdb" /map:"$(INTDIR)\minimal.map" /machine:I386 /def:".\minimal.def" /out:"$(OUTDIR)\minimal.dll" /implib:"$(OUTDIR)\minimal.lib" /merge:.idata=.data /WS:AGGRESSIVE /FIXED 
DEF_FILE= \
	".\minimal.def"
LINK32_OBJS= \
	"$(INTDIR)\minimal.obj" \
	"$(INTDIR)\MinObj.obj" \
	"$(INTDIR)\premin.obj"

"$(OUTDIR)\minimal.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "minimal - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\minimal.dll"


CLEAN :
	-@erase "$(INTDIR)\minimal.obj"
	-@erase "$(INTDIR)\minimal.pch"
	-@erase "$(INTDIR)\MinObj.obj"
	-@erase "$(INTDIR)\premin.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\minimal.dll"
	-@erase "$(OUTDIR)\minimal.exp"
	-@erase "$(OUTDIR)\minimal.ilk"
	-@erase "$(OUTDIR)\minimal.lib"
	-@erase "$(OUTDIR)\minimal.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_NO_CONNECTION_POINTS" /Fp"$(INTDIR)\minimal.pch" /Yu"premin.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\minimal.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\minimal.pdb" /debug /machine:I386 /def:".\minimal.def" /out:"$(OUTDIR)\minimal.dll" /implib:"$(OUTDIR)\minimal.lib" 
DEF_FILE= \
	".\minimal.def"
LINK32_OBJS= \
	"$(INTDIR)\minimal.obj" \
	"$(INTDIR)\MinObj.obj" \
	"$(INTDIR)\premin.obj"

"$(OUTDIR)\minimal.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("minimal.dep")
!INCLUDE "minimal.dep"
!ELSE 
!MESSAGE Warning: cannot find "minimal.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "minimal - Win32 Release" || "$(CFG)" == "minimal - Win32 Debug" || "$(CFG)" == "minimal - Win32 Unicode Release" || "$(CFG)" == "minimal - Win32 Unicode Debug"
SOURCE=.\minimal.cpp

"$(INTDIR)\minimal.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\minimal.pch"


SOURCE=.\MinObj.cpp

"$(INTDIR)\MinObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\minimal.pch"


SOURCE=.\premin.cpp

!IF  "$(CFG)" == "minimal - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /O2 /D "NDEBUG" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_NO_CONNECTION_POINTS" /Fp"$(INTDIR)\minimal.pch" /Yc"premin.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\premin.obj"	"$(INTDIR)\minimal.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "minimal - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_NO_CONNECTION_POINTS" /Fp"$(INTDIR)\minimal.pch" /Yc"premin.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\premin.obj"	"$(INTDIR)\minimal.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "minimal - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /O2 /D "_UNICODE" /D "NDEBUG" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_NO_CONNECTION_POINTS" /Fp"$(INTDIR)\minimal.pch" /Yc"premin.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\premin.obj"	"$(INTDIR)\minimal.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "minimal - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_NO_CONNECTION_POINTS" /Fp"$(INTDIR)\minimal.pch" /Yc"premin.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\premin.obj"	"$(INTDIR)\minimal.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

