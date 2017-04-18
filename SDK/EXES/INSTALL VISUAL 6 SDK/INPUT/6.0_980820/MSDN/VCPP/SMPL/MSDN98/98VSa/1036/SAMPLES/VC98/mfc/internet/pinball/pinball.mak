# Microsoft Developer Studio Generated NMAKE File, Based on Pinball.dsp
!IF "$(CFG)" == ""
CFG=Pinball - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Pinball - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Pinball - Win32 Release" && "$(CFG)" != "Pinball - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Pinball.mak" CFG="Pinball - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Pinball - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Pinball - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "Pinball - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Pinball.dll"


CLEAN :
	-@erase "$(INTDIR)\Pinball.obj"
	-@erase "$(INTDIR)\Pinball.pch"
	-@erase "$(INTDIR)\Pinball.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Pinball.dll"
	-@erase "$(OUTDIR)\Pinball.exp"
	-@erase "$(OUTDIR)\Pinball.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Pinball.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Pinball.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Pinball.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Pinball.pdb" /machine:I386 /def:".\Pinball.def" /out:"$(OUTDIR)\Pinball.dll" /implib:"$(OUTDIR)\Pinball.lib" 
DEF_FILE= \
	".\Pinball.def"
LINK32_OBJS= \
	"$(INTDIR)\Pinball.obj" \
	"$(INTDIR)\Pinball.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Pinball.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Pinball - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Pinball.dll"


CLEAN :
	-@erase "$(INTDIR)\Pinball.obj"
	-@erase "$(INTDIR)\Pinball.pch"
	-@erase "$(INTDIR)\Pinball.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Pinball.dll"
	-@erase "$(OUTDIR)\Pinball.exp"
	-@erase "$(OUTDIR)\Pinball.ilk"
	-@erase "$(OUTDIR)\Pinball.lib"
	-@erase "$(OUTDIR)\Pinball.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Pinball.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ    /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Pinball.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Pinball.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Pinball.pdb" /debug /machine:I386 /def:".\Pinball.def" /out:"$(OUTDIR)\Pinball.dll" /implib:"$(OUTDIR)\Pinball.lib" /pdbtype:sept 
DEF_FILE= \
	".\Pinball.def"
LINK32_OBJS= \
	"$(INTDIR)\Pinball.obj" \
	"$(INTDIR)\Pinball.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Pinball.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Pinball.dep")
!INCLUDE "Pinball.dep"
!ELSE 
!MESSAGE Warning: cannot find "Pinball.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Pinball - Win32 Release" || "$(CFG)" == "Pinball - Win32 Debug"
SOURCE=.\Pinball.cpp

"$(INTDIR)\Pinball.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Pinball.pch"


SOURCE=.\Pinball.rc

"$(INTDIR)\Pinball.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Pinball - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Pinball.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Pinball.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Pinball - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Pinball.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ    /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Pinball.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

