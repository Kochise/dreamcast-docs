# Microsoft Developer Studio Generated NMAKE File, Based on daotable.dsp
!IF "$(CFG)" == ""
CFG=DAOTable - Win32 Release
!MESSAGE No configuration specified. Defaulting to DAOTable - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DAOTable - Win32 Release" && "$(CFG)" != "DAOTable - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "daotable.mak" CFG="DAOTable - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DAOTable - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DAOTable - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "DAOTable - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : ".\.\Release\daotable.hlp" "$(OUTDIR)\daotable.exe"


CLEAN :
	-@erase "$(INTDIR)\AddDbDlg.obj"
	-@erase "$(INTDIR)\AddIxDlg.obj"
	-@erase "$(INTDIR)\AddQyDlg.obj"
	-@erase "$(INTDIR)\AddTbDlg.obj"
	-@erase "$(INTDIR)\DAOTable.obj"
	-@erase "$(INTDIR)\daotable.pch"
	-@erase "$(INTDIR)\DAOTable.res"
	-@erase "$(INTDIR)\DAOTDlg.obj"
	-@erase "$(INTDIR)\database.obj"
	-@erase "$(INTDIR)\field.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\ListCtrl.obj"
	-@erase "$(INTDIR)\querydef.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tabledef.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\daotable.exe"
	-@erase ".\.\Release\daotable.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daotable.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DAOTable.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daotable.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\daotable.pdb" /machine:I386 /out:"$(OUTDIR)\daotable.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AddDbDlg.obj" \
	"$(INTDIR)\AddIxDlg.obj" \
	"$(INTDIR)\AddQyDlg.obj" \
	"$(INTDIR)\AddTbDlg.obj" \
	"$(INTDIR)\DAOTable.obj" \
	"$(INTDIR)\DAOTDlg.obj" \
	"$(INTDIR)\database.obj" \
	"$(INTDIR)\field.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\ListCtrl.obj" \
	"$(INTDIR)\querydef.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tabledef.obj" \
	"$(INTDIR)\DAOTable.res"

"$(OUTDIR)\daotable.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DAOTable - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : ".\.\Debug\daotable.hlp" "$(OUTDIR)\daotable.exe"


CLEAN :
	-@erase "$(INTDIR)\AddDbDlg.obj"
	-@erase "$(INTDIR)\AddIxDlg.obj"
	-@erase "$(INTDIR)\AddQyDlg.obj"
	-@erase "$(INTDIR)\AddTbDlg.obj"
	-@erase "$(INTDIR)\DAOTable.obj"
	-@erase "$(INTDIR)\daotable.pch"
	-@erase "$(INTDIR)\DAOTable.res"
	-@erase "$(INTDIR)\DAOTDlg.obj"
	-@erase "$(INTDIR)\database.obj"
	-@erase "$(INTDIR)\field.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\ListCtrl.obj"
	-@erase "$(INTDIR)\querydef.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tabledef.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\daotable.exe"
	-@erase "$(OUTDIR)\daotable.ilk"
	-@erase "$(OUTDIR)\daotable.pdb"
	-@erase ".\.\Debug\daotable.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daotable.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DAOTable.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daotable.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\daotable.pdb" /debug /machine:I386 /out:"$(OUTDIR)\daotable.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AddDbDlg.obj" \
	"$(INTDIR)\AddIxDlg.obj" \
	"$(INTDIR)\AddQyDlg.obj" \
	"$(INTDIR)\AddTbDlg.obj" \
	"$(INTDIR)\DAOTable.obj" \
	"$(INTDIR)\DAOTDlg.obj" \
	"$(INTDIR)\database.obj" \
	"$(INTDIR)\field.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\ListCtrl.obj" \
	"$(INTDIR)\querydef.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tabledef.obj" \
	"$(INTDIR)\DAOTable.res"

"$(OUTDIR)\daotable.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("daotable.dep")
!INCLUDE "daotable.dep"
!ELSE 
!MESSAGE Warning: cannot find "daotable.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DAOTable - Win32 Release" || "$(CFG)" == "DAOTable - Win32 Debug"
SOURCE=.\AddDbDlg.cpp

"$(INTDIR)\AddDbDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\AddIxDlg.cpp

"$(INTDIR)\AddIxDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\AddQyDlg.cpp

"$(INTDIR)\AddQyDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\AddTbDlg.cpp

"$(INTDIR)\AddTbDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\DAOTable.cpp

"$(INTDIR)\DAOTable.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\hlp\DAOTable.hpj

!IF  "$(CFG)" == "DAOTable - Win32 Release"

OutDir=.\.\Release
ProjDir=.
TargetName=daotable
InputPath=.\hlp\DAOTable.hpj

"$(OutDir)\$(TargetName).hlp"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(ProjDir)\makehelp.bat"
<< 
	

!ELSEIF  "$(CFG)" == "DAOTable - Win32 Debug"

OutDir=.\.\Debug
ProjDir=.
TargetName=daotable
InputPath=.\hlp\DAOTable.hpj

"$(OutDir)\$(TargetName).hlp"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(ProjDir)\makehelp.bat"
<< 
	

!ENDIF 

SOURCE=.\DAOTable.rc

"$(INTDIR)\DAOTable.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DAOTDlg.cpp

"$(INTDIR)\DAOTDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\database.cpp

"$(INTDIR)\database.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\field.cpp

"$(INTDIR)\field.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\index.cpp

"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\ListCtrl.cpp

"$(INTDIR)\ListCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\querydef.cpp

"$(INTDIR)\querydef.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DAOTable - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daotable.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\daotable.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DAOTable - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daotable.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\daotable.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tabledef.cpp

"$(INTDIR)\tabledef.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daotable.pch"



!ENDIF 

