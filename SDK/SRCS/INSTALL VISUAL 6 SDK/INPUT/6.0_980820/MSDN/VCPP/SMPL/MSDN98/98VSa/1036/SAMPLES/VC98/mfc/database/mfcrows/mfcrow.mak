# Microsoft Developer Studio Generated NMAKE File, Based on MFCRow.dsp
!IF "$(CFG)" == ""
CFG=MFCRow - Win32 Debug Unicode
!MESSAGE No configuration specified. Defaulting to MFCRow - Win32 Debug Unicode.
!ENDIF 

!IF "$(CFG)" != "MFCRow - Win32 Release" && "$(CFG)" != "MFCRow - Win32 Debug" && "$(CFG)" != "MFCRow - Win32 Debug Static" && "$(CFG)" != "MFCRow - Win32 Release Static" && "$(CFG)" != "MFCRow - Win32 Debug Unicode" && "$(CFG)" != "MFCRow - Win32 Release Unicode"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MFCRow.mak" CFG="MFCRow - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MFCRow - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MFCRow - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MFCRow - Win32 Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "MFCRow - Win32 Release Static" (based on "Win32 (x86) Application")
!MESSAGE "MFCRow - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE "MFCRow - Win32 Release Unicode" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "MFCRow - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MFCRow.exe"


CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MFCRow.obj"
	-@erase "$(INTDIR)\MFCRow.pch"
	-@erase "$(INTDIR)\MFCRow.res"
	-@erase "$(INTDIR)\MFCRowDoc.obj"
	-@erase "$(INTDIR)\MFCRowSet.obj"
	-@erase "$(INTDIR)\MFCRowView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MFCRow.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCRow.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCRow.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCRow.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MFCRow.pdb" /machine:I386 /force /out:"$(OUTDIR)\MFCRow.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MFCRow.obj" \
	"$(INTDIR)\MFCRowDoc.obj" \
	"$(INTDIR)\MFCRowSet.obj" \
	"$(INTDIR)\MFCRowView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MFCRow.res"

"$(OUTDIR)\MFCRow.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCRow - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MFCRow.exe"


CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MFCRow.obj"
	-@erase "$(INTDIR)\MFCRow.pch"
	-@erase "$(INTDIR)\MFCRow.res"
	-@erase "$(INTDIR)\MFCRowDoc.obj"
	-@erase "$(INTDIR)\MFCRowSet.obj"
	-@erase "$(INTDIR)\MFCRowView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MFCRow.exe"
	-@erase "$(OUTDIR)\MFCRow.ilk"
	-@erase "$(OUTDIR)\MFCRow.map"
	-@erase "$(OUTDIR)\MFCRow.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCRow.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCRow.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCRow.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MFCRow.pdb" /map:"$(INTDIR)\MFCRow.map" /debug /machine:I386 /out:"$(OUTDIR)\MFCRow.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MFCRow.obj" \
	"$(INTDIR)\MFCRowDoc.obj" \
	"$(INTDIR)\MFCRowSet.obj" \
	"$(INTDIR)\MFCRowView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MFCRow.res"

"$(OUTDIR)\MFCRow.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCRow - Win32 Debug Static"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MFCRow.exe"


CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MFCRow.obj"
	-@erase "$(INTDIR)\MFCRow.pch"
	-@erase "$(INTDIR)\MFCRow.res"
	-@erase "$(INTDIR)\MFCRowDoc.obj"
	-@erase "$(INTDIR)\MFCRowSet.obj"
	-@erase "$(INTDIR)\MFCRowView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MFCRow.exe"
	-@erase "$(OUTDIR)\MFCRow.ilk"
	-@erase "$(OUTDIR)\MFCRow.map"
	-@erase "$(OUTDIR)\MFCRow.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\MFCRow.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCRow.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCRow.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MFCRow.pdb" /map:"$(INTDIR)\MFCRow.map" /debug /machine:I386 /out:"$(OUTDIR)\MFCRow.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MFCRow.obj" \
	"$(INTDIR)\MFCRowDoc.obj" \
	"$(INTDIR)\MFCRowSet.obj" \
	"$(INTDIR)\MFCRowView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MFCRow.res"

"$(OUTDIR)\MFCRow.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCRow - Win32 Release Static"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MFCRow.exe"


CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MFCRow.obj"
	-@erase "$(INTDIR)\MFCRow.pch"
	-@erase "$(INTDIR)\MFCRow.res"
	-@erase "$(INTDIR)\MFCRowDoc.obj"
	-@erase "$(INTDIR)\MFCRowSet.obj"
	-@erase "$(INTDIR)\MFCRowView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MFCRow.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\MFCRow.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCRow.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCRow.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MFCRow.pdb" /machine:I386 /force /out:"$(OUTDIR)\MFCRow.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MFCRow.obj" \
	"$(INTDIR)\MFCRowDoc.obj" \
	"$(INTDIR)\MFCRowSet.obj" \
	"$(INTDIR)\MFCRowView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MFCRow.res"

"$(OUTDIR)\MFCRow.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCRow - Win32 Debug Unicode"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MFCRow.exe"


CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MFCRow.obj"
	-@erase "$(INTDIR)\MFCRow.pch"
	-@erase "$(INTDIR)\MFCRow.res"
	-@erase "$(INTDIR)\MFCRowDoc.obj"
	-@erase "$(INTDIR)\MFCRowSet.obj"
	-@erase "$(INTDIR)\MFCRowView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MFCRow.exe"
	-@erase "$(OUTDIR)\MFCRow.ilk"
	-@erase "$(OUTDIR)\MFCRow.map"
	-@erase "$(OUTDIR)\MFCRow.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\MFCRow.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCRow.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCRow.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MFCRow.pdb" /map:"$(INTDIR)\MFCRow.map" /debug /machine:I386 /out:"$(OUTDIR)\MFCRow.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MFCRow.obj" \
	"$(INTDIR)\MFCRowDoc.obj" \
	"$(INTDIR)\MFCRowSet.obj" \
	"$(INTDIR)\MFCRowView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MFCRow.res"

"$(OUTDIR)\MFCRow.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCRow - Win32 Release Unicode"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MFCRow.exe"


CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MFCRow.obj"
	-@erase "$(INTDIR)\MFCRow.pch"
	-@erase "$(INTDIR)\MFCRow.res"
	-@erase "$(INTDIR)\MFCRowDoc.obj"
	-@erase "$(INTDIR)\MFCRowSet.obj"
	-@erase "$(INTDIR)\MFCRowView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MFCRow.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\MFCRow.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCRow.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCRow.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MFCRow.pdb" /machine:I386 /force /out:"$(OUTDIR)\MFCRow.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MFCRow.obj" \
	"$(INTDIR)\MFCRowDoc.obj" \
	"$(INTDIR)\MFCRowSet.obj" \
	"$(INTDIR)\MFCRowView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MFCRow.res"

"$(OUTDIR)\MFCRow.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("MFCRow.dep")
!INCLUDE "MFCRow.dep"
!ELSE 
!MESSAGE Warning: cannot find "MFCRow.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MFCRow - Win32 Release" || "$(CFG)" == "MFCRow - Win32 Debug" || "$(CFG)" == "MFCRow - Win32 Debug Static" || "$(CFG)" == "MFCRow - Win32 Release Static" || "$(CFG)" == "MFCRow - Win32 Debug Unicode" || "$(CFG)" == "MFCRow - Win32 Release Unicode"
SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCRow.pch"


SOURCE=.\MFCRow.cpp

"$(INTDIR)\MFCRow.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCRow.pch"


SOURCE=.\MFCRow.rc

"$(INTDIR)\MFCRow.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MFCRowDoc.cpp

"$(INTDIR)\MFCRowDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCRow.pch"


SOURCE=.\MFCRowSet.cpp

"$(INTDIR)\MFCRowSet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCRow.pch"


SOURCE=.\MFCRowView.cpp

"$(INTDIR)\MFCRowView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCRow.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MFCRow - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCRow.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCRow.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MFCRow - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCRow.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCRow.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MFCRow - Win32 Debug Static"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\MFCRow.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCRow.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MFCRow - Win32 Release Static"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\MFCRow.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCRow.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MFCRow - Win32 Debug Unicode"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\MFCRow.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCRow.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MFCRow - Win32 Release Unicode"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\MFCRow.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCRow.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

