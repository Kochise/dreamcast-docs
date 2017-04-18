# Microsoft Developer Studio Generated NMAKE File, Based on wwwquote.dsp
!IF "$(CFG)" == ""
CFG=WWWQuote - Win32 Release
!MESSAGE No configuration specified. Defaulting to WWWQuote - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "WWWQuote - Win32 Release" && "$(CFG)" != "WWWQuote - Win32 Debug" && "$(CFG)" != "WWWQuote - Win32 Static Release" && "$(CFG)" != "WWWQuote - Win32 Static Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wwwquote.mak" CFG="WWWQuote - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WWWQuote - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WWWQuote - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WWWQuote - Win32 Static Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WWWQuote - Win32 Static Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "WWWQuote - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\wwwquote.dll"


CLEAN :
	-@erase "$(INTDIR)\queries.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WWWQuote.obj"
	-@erase "$(INTDIR)\wwwquote.pch"
	-@erase "$(INTDIR)\WWWQuote.res"
	-@erase "$(OUTDIR)\wwwquote.dll"
	-@erase "$(OUTDIR)\wwwquote.exp"
	-@erase "$(OUTDIR)\wwwquote.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\wwwquote.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WWWQuote.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wwwquote.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\wwwquote.pdb" /machine:I386 /def:".\WWWQuote.def" /out:"$(OUTDIR)\wwwquote.dll" /implib:"$(OUTDIR)\wwwquote.lib" 
DEF_FILE= \
	".\WWWQuote.def"
LINK32_OBJS= \
	"$(INTDIR)\queries.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WWWQuote.obj" \
	"$(INTDIR)\WWWQuote.res"

"$(OUTDIR)\wwwquote.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WWWQuote - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\wwwquote.dll"


CLEAN :
	-@erase "$(INTDIR)\queries.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WWWQuote.obj"
	-@erase "$(INTDIR)\wwwquote.pch"
	-@erase "$(INTDIR)\WWWQuote.res"
	-@erase "$(OUTDIR)\wwwquote.dll"
	-@erase "$(OUTDIR)\wwwquote.exp"
	-@erase "$(OUTDIR)\wwwquote.ilk"
	-@erase "$(OUTDIR)\wwwquote.lib"
	-@erase "$(OUTDIR)\wwwquote.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\wwwquote.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WWWQuote.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wwwquote.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\wwwquote.pdb" /debug /machine:I386 /def:".\WWWQuote.def" /out:"$(OUTDIR)\wwwquote.dll" /implib:"$(OUTDIR)\wwwquote.lib" 
DEF_FILE= \
	".\WWWQuote.def"
LINK32_OBJS= \
	"$(INTDIR)\queries.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WWWQuote.obj" \
	"$(INTDIR)\WWWQuote.res"

"$(OUTDIR)\wwwquote.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WWWQuote - Win32 Static Release"

OUTDIR=.\SRelease
INTDIR=.\SRelease
# Begin Custom Macros
OutDir=.\.\SRelease
# End Custom Macros

ALL : "$(OUTDIR)\wwwquote.dll"


CLEAN :
	-@erase "$(INTDIR)\queries.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WWWQuote.obj"
	-@erase "$(INTDIR)\wwwquote.pch"
	-@erase "$(INTDIR)\WWWQuote.res"
	-@erase "$(OUTDIR)\wwwquote.dll"
	-@erase "$(OUTDIR)\wwwquote.exp"
	-@erase "$(OUTDIR)\wwwquote.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\wwwquote.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WWWQuote.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wwwquote.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\wwwquote.pdb" /machine:I386 /def:".\WWWQuote.def" /out:"$(OUTDIR)\wwwquote.dll" /implib:"$(OUTDIR)\wwwquote.lib" 
DEF_FILE= \
	".\WWWQuote.def"
LINK32_OBJS= \
	"$(INTDIR)\queries.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WWWQuote.obj" \
	"$(INTDIR)\WWWQuote.res"

"$(OUTDIR)\wwwquote.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WWWQuote - Win32 Static Debug"

OUTDIR=.\SDebug
INTDIR=.\SDebug
# Begin Custom Macros
OutDir=.\.\SDebug
# End Custom Macros

ALL : "$(OUTDIR)\wwwquote.dll"


CLEAN :
	-@erase "$(INTDIR)\queries.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WWWQuote.obj"
	-@erase "$(INTDIR)\wwwquote.pch"
	-@erase "$(INTDIR)\WWWQuote.res"
	-@erase "$(OUTDIR)\wwwquote.dll"
	-@erase "$(OUTDIR)\wwwquote.exp"
	-@erase "$(OUTDIR)\wwwquote.ilk"
	-@erase "$(OUTDIR)\wwwquote.lib"
	-@erase "$(OUTDIR)\wwwquote.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\wwwquote.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WWWQuote.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wwwquote.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\wwwquote.pdb" /debug /machine:I386 /def:".\WWWQuote.def" /out:"$(OUTDIR)\wwwquote.dll" /implib:"$(OUTDIR)\wwwquote.lib" 
DEF_FILE= \
	".\WWWQuote.def"
LINK32_OBJS= \
	"$(INTDIR)\queries.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WWWQuote.obj" \
	"$(INTDIR)\WWWQuote.res"

"$(OUTDIR)\wwwquote.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("wwwquote.dep")
!INCLUDE "wwwquote.dep"
!ELSE 
!MESSAGE Warning: cannot find "wwwquote.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WWWQuote - Win32 Release" || "$(CFG)" == "WWWQuote - Win32 Debug" || "$(CFG)" == "WWWQuote - Win32 Static Release" || "$(CFG)" == "WWWQuote - Win32 Static Debug"
SOURCE=.\queries.cpp

"$(INTDIR)\queries.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wwwquote.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "WWWQuote - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\wwwquote.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wwwquote.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WWWQuote - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\wwwquote.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wwwquote.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WWWQuote - Win32 Static Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\wwwquote.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wwwquote.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WWWQuote - Win32 Static Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\wwwquote.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wwwquote.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WWWQuote.cpp

"$(INTDIR)\WWWQuote.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wwwquote.pch"


SOURCE=.\WWWQuote.rc

"$(INTDIR)\WWWQuote.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

