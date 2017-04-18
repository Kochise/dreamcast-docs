# Microsoft Developer Studio Generated NMAKE File, Based on odbcinfo.dsp
!IF "$(CFG)" == ""
CFG=OdbcInfo - Win32 Release
!MESSAGE No configuration specified. Defaulting to OdbcInfo - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "OdbcInfo - Win32 Release" && "$(CFG)" != "OdbcInfo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "odbcinfo.mak" CFG="OdbcInfo - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OdbcInfo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OdbcInfo - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "OdbcInfo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\odbcinfo.exe"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\DrvInfo.obj"
	-@erase "$(INTDIR)\MySheet.obj"
	-@erase "$(INTDIR)\OdbcInfo.obj"
	-@erase "$(INTDIR)\odbcinfo.pch"
	-@erase "$(INTDIR)\OdbcInfo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\odbcinfo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\odbcinfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OdbcInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\odbcinfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\odbcinfo.pdb" /machine:I386 /out:"$(OUTDIR)\odbcinfo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\DrvInfo.obj" \
	"$(INTDIR)\MySheet.obj" \
	"$(INTDIR)\OdbcInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OdbcInfo.res"

"$(OUTDIR)\odbcinfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OdbcInfo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\odbcinfo.exe" "$(OUTDIR)\odbcinfo.bsc"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\AboutDlg.sbr"
	-@erase "$(INTDIR)\catsets.obj"
	-@erase "$(INTDIR)\catsets.sbr"
	-@erase "$(INTDIR)\DrvInfo.obj"
	-@erase "$(INTDIR)\DrvInfo.sbr"
	-@erase "$(INTDIR)\MySheet.obj"
	-@erase "$(INTDIR)\MySheet.sbr"
	-@erase "$(INTDIR)\OdbcInfo.obj"
	-@erase "$(INTDIR)\odbcinfo.pch"
	-@erase "$(INTDIR)\OdbcInfo.res"
	-@erase "$(INTDIR)\OdbcInfo.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\odbcinfo.bsc"
	-@erase "$(OUTDIR)\odbcinfo.exe"
	-@erase "$(OUTDIR)\odbcinfo.ilk"
	-@erase "$(OUTDIR)\odbcinfo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\odbcinfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OdbcInfo.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\odbcinfo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AboutDlg.sbr" \
	"$(INTDIR)\catsets.sbr" \
	"$(INTDIR)\DrvInfo.sbr" \
	"$(INTDIR)\MySheet.sbr" \
	"$(INTDIR)\OdbcInfo.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\odbcinfo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\odbcinfo.pdb" /debug /machine:I386 /out:"$(OUTDIR)\odbcinfo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\catsets.obj" \
	"$(INTDIR)\DrvInfo.obj" \
	"$(INTDIR)\MySheet.obj" \
	"$(INTDIR)\OdbcInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OdbcInfo.res"

"$(OUTDIR)\odbcinfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("odbcinfo.dep")
!INCLUDE "odbcinfo.dep"
!ELSE 
!MESSAGE Warning: cannot find "odbcinfo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OdbcInfo - Win32 Release" || "$(CFG)" == "OdbcInfo - Win32 Debug"
SOURCE=.\AboutDlg.cpp

!IF  "$(CFG)" == "OdbcInfo - Win32 Release"


"$(INTDIR)\AboutDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ELSEIF  "$(CFG)" == "OdbcInfo - Win32 Debug"


"$(INTDIR)\AboutDlg.obj"	"$(INTDIR)\AboutDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ENDIF 

SOURCE=.\catsets.cpp

!IF  "$(CFG)" == "OdbcInfo - Win32 Release"


"$(INTDIR)\catsets.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ELSEIF  "$(CFG)" == "OdbcInfo - Win32 Debug"


"$(INTDIR)\catsets.obj"	"$(INTDIR)\catsets.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ENDIF 

SOURCE=.\DrvInfo.cpp

!IF  "$(CFG)" == "OdbcInfo - Win32 Release"


"$(INTDIR)\DrvInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ELSEIF  "$(CFG)" == "OdbcInfo - Win32 Debug"


"$(INTDIR)\DrvInfo.obj"	"$(INTDIR)\DrvInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ENDIF 

SOURCE=.\MySheet.cpp

!IF  "$(CFG)" == "OdbcInfo - Win32 Release"


"$(INTDIR)\MySheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ELSEIF  "$(CFG)" == "OdbcInfo - Win32 Debug"


"$(INTDIR)\MySheet.obj"	"$(INTDIR)\MySheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ENDIF 

SOURCE=.\OdbcInfo.cpp

!IF  "$(CFG)" == "OdbcInfo - Win32 Release"


"$(INTDIR)\OdbcInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ELSEIF  "$(CFG)" == "OdbcInfo - Win32 Debug"


"$(INTDIR)\OdbcInfo.obj"	"$(INTDIR)\OdbcInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\odbcinfo.pch"


!ENDIF 

SOURCE=.\OdbcInfo.rc

"$(INTDIR)\OdbcInfo.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "OdbcInfo - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\odbcinfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\odbcinfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OdbcInfo - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\odbcinfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\odbcinfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

