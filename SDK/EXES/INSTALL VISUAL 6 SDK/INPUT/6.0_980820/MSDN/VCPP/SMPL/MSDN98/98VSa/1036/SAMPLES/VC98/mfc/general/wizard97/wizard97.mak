# Microsoft Developer Studio Generated NMAKE File, Based on Wizard97.dsp
!IF "$(CFG)" == ""
CFG=Wizard97 - Win32 Debug Unicode
!MESSAGE No configuration specified. Defaulting to Wizard97 - Win32 Debug Unicode.
!ENDIF 

!IF "$(CFG)" != "Wizard97 - Win32 Release" && "$(CFG)" != "Wizard97 - Win32 Debug" && "$(CFG)" != "Wizard97 - Win32 Debug Static" && "$(CFG)" != "Wizard97 - Win32 Release Static" && "$(CFG)" != "Wizard97 - Win32 Debug Unicode" && "$(CFG)" != "Wizard97 - Win32 Release Unicode"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Wizard97.mak" CFG="Wizard97 - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Wizard97 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Wizard97 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Wizard97 - Win32 Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "Wizard97 - Win32 Release Static" (based on "Win32 (x86) Application")
!MESSAGE "Wizard97 - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE "Wizard97 - Win32 Release Unicode" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Wizard97 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Wizard97.exe"


CLEAN :
	-@erase "$(INTDIR)\Complete.obj"
	-@erase "$(INTDIR)\Int1.obj"
	-@erase "$(INTDIR)\Int2.obj"
	-@erase "$(INTDIR)\IntroPg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Wizard97.obj"
	-@erase "$(INTDIR)\Wizard97.pch"
	-@erase "$(INTDIR)\Wizard97.res"
	-@erase "$(INTDIR)\WizSheet.obj"
	-@erase "$(OUTDIR)\Wizard97.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Wizard97.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Wizard97.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Wizard97.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Wizard97.pdb" /machine:I386 /out:"$(OUTDIR)\Wizard97.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Complete.obj" \
	"$(INTDIR)\Int1.obj" \
	"$(INTDIR)\Int2.obj" \
	"$(INTDIR)\IntroPg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Wizard97.obj" \
	"$(INTDIR)\WizSheet.obj" \
	"$(INTDIR)\Wizard97.res"

"$(OUTDIR)\Wizard97.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Wizard97.exe"


CLEAN :
	-@erase "$(INTDIR)\Complete.obj"
	-@erase "$(INTDIR)\Int1.obj"
	-@erase "$(INTDIR)\Int2.obj"
	-@erase "$(INTDIR)\IntroPg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Wizard97.obj"
	-@erase "$(INTDIR)\Wizard97.pch"
	-@erase "$(INTDIR)\Wizard97.res"
	-@erase "$(INTDIR)\WizSheet.obj"
	-@erase "$(OUTDIR)\Wizard97.exe"
	-@erase "$(OUTDIR)\Wizard97.ilk"
	-@erase "$(OUTDIR)\Wizard97.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Wizard97.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Wizard97.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Wizard97.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Wizard97.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Wizard97.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Complete.obj" \
	"$(INTDIR)\Int1.obj" \
	"$(INTDIR)\Int2.obj" \
	"$(INTDIR)\IntroPg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Wizard97.obj" \
	"$(INTDIR)\WizSheet.obj" \
	"$(INTDIR)\Wizard97.res"

"$(OUTDIR)\Wizard97.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Debug Static"

OUTDIR=.\DebugStatic
INTDIR=.\DebugStatic
# Begin Custom Macros
OutDir=.\DebugStatic
# End Custom Macros

ALL : "$(OUTDIR)\Wizard97.exe"


CLEAN :
	-@erase "$(INTDIR)\Complete.obj"
	-@erase "$(INTDIR)\Int1.obj"
	-@erase "$(INTDIR)\Int2.obj"
	-@erase "$(INTDIR)\IntroPg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Wizard97.obj"
	-@erase "$(INTDIR)\Wizard97.pch"
	-@erase "$(INTDIR)\Wizard97.res"
	-@erase "$(INTDIR)\WizSheet.obj"
	-@erase "$(OUTDIR)\Wizard97.exe"
	-@erase "$(OUTDIR)\Wizard97.ilk"
	-@erase "$(OUTDIR)\Wizard97.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Wizard97.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Wizard97.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Wizard97.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Wizard97.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Wizard97.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Complete.obj" \
	"$(INTDIR)\Int1.obj" \
	"$(INTDIR)\Int2.obj" \
	"$(INTDIR)\IntroPg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Wizard97.obj" \
	"$(INTDIR)\WizSheet.obj" \
	"$(INTDIR)\Wizard97.res"

"$(OUTDIR)\Wizard97.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Release Static"

OUTDIR=.\ReleaseStatic
INTDIR=.\ReleaseStatic
# Begin Custom Macros
OutDir=.\ReleaseStatic
# End Custom Macros

ALL : "$(OUTDIR)\Wizard97.exe"


CLEAN :
	-@erase "$(INTDIR)\Complete.obj"
	-@erase "$(INTDIR)\Int1.obj"
	-@erase "$(INTDIR)\Int2.obj"
	-@erase "$(INTDIR)\IntroPg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Wizard97.obj"
	-@erase "$(INTDIR)\Wizard97.pch"
	-@erase "$(INTDIR)\Wizard97.res"
	-@erase "$(INTDIR)\WizSheet.obj"
	-@erase "$(OUTDIR)\Wizard97.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Wizard97.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Wizard97.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Wizard97.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Wizard97.pdb" /machine:I386 /out:"$(OUTDIR)\Wizard97.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Complete.obj" \
	"$(INTDIR)\Int1.obj" \
	"$(INTDIR)\Int2.obj" \
	"$(INTDIR)\IntroPg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Wizard97.obj" \
	"$(INTDIR)\WizSheet.obj" \
	"$(INTDIR)\Wizard97.res"

"$(OUTDIR)\Wizard97.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Debug Unicode"

OUTDIR=.\DebugUnicode
INTDIR=.\DebugUnicode
# Begin Custom Macros
OutDir=.\DebugUnicode
# End Custom Macros

ALL : "$(OUTDIR)\Wizard97.exe"


CLEAN :
	-@erase "$(INTDIR)\Complete.obj"
	-@erase "$(INTDIR)\Int1.obj"
	-@erase "$(INTDIR)\Int2.obj"
	-@erase "$(INTDIR)\IntroPg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Wizard97.obj"
	-@erase "$(INTDIR)\Wizard97.pch"
	-@erase "$(INTDIR)\Wizard97.res"
	-@erase "$(INTDIR)\WizSheet.obj"
	-@erase "$(OUTDIR)\Wizard97.exe"
	-@erase "$(OUTDIR)\Wizard97.ilk"
	-@erase "$(OUTDIR)\Wizard97.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\Wizard97.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Wizard97.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Wizard97.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Wizard97.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Wizard97.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Complete.obj" \
	"$(INTDIR)\Int1.obj" \
	"$(INTDIR)\Int2.obj" \
	"$(INTDIR)\IntroPg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Wizard97.obj" \
	"$(INTDIR)\WizSheet.obj" \
	"$(INTDIR)\Wizard97.res"

"$(OUTDIR)\Wizard97.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Release Unicode"

OUTDIR=.\ReleaseUnicode
INTDIR=.\ReleaseUnicode
# Begin Custom Macros
OutDir=.\ReleaseUnicode
# End Custom Macros

ALL : "$(OUTDIR)\Wizard97.exe"


CLEAN :
	-@erase "$(INTDIR)\Complete.obj"
	-@erase "$(INTDIR)\Int1.obj"
	-@erase "$(INTDIR)\Int2.obj"
	-@erase "$(INTDIR)\IntroPg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Wizard97.obj"
	-@erase "$(INTDIR)\Wizard97.pch"
	-@erase "$(INTDIR)\Wizard97.res"
	-@erase "$(INTDIR)\WizSheet.obj"
	-@erase "$(OUTDIR)\Wizard97.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\Wizard97.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Wizard97.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Wizard97.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Wizard97.pdb" /machine:I386 /out:"$(OUTDIR)\Wizard97.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Complete.obj" \
	"$(INTDIR)\Int1.obj" \
	"$(INTDIR)\Int2.obj" \
	"$(INTDIR)\IntroPg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Wizard97.obj" \
	"$(INTDIR)\WizSheet.obj" \
	"$(INTDIR)\Wizard97.res"

"$(OUTDIR)\Wizard97.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Wizard97.dep")
!INCLUDE "Wizard97.dep"
!ELSE 
!MESSAGE Warning: cannot find "Wizard97.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Wizard97 - Win32 Release" || "$(CFG)" == "Wizard97 - Win32 Debug" || "$(CFG)" == "Wizard97 - Win32 Debug Static" || "$(CFG)" == "Wizard97 - Win32 Release Static" || "$(CFG)" == "Wizard97 - Win32 Debug Unicode" || "$(CFG)" == "Wizard97 - Win32 Release Unicode"
SOURCE=.\Complete.cpp

"$(INTDIR)\Complete.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Wizard97.pch"


SOURCE=.\Int1.cpp

"$(INTDIR)\Int1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Wizard97.pch"


SOURCE=.\Int2.cpp

"$(INTDIR)\Int2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Wizard97.pch"


SOURCE=.\IntroPg.cpp

"$(INTDIR)\IntroPg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Wizard97.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Wizard97 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Wizard97.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Wizard97.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Wizard97.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Wizard97.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Debug Static"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Wizard97.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Wizard97.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Release Static"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Wizard97.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Wizard97.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Debug Unicode"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\Wizard97.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Wizard97.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Wizard97 - Win32 Release Unicode"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\Wizard97.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Wizard97.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Wizard97.cpp

"$(INTDIR)\Wizard97.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Wizard97.pch"


SOURCE=.\Wizard97.rc

"$(INTDIR)\Wizard97.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\WizSheet.cpp

"$(INTDIR)\WizSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Wizard97.pch"



!ENDIF 

