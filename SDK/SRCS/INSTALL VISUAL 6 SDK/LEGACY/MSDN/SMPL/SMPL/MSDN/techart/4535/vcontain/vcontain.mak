# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=VContain - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to VContain - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VContain - Win32 Release" && "$(CFG)" !=\
 "VContain - Win32 Debug" && "$(CFG)" != "VContain - Win32 Release Unicode"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "VContain.mak" CFG="VContain - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VContain - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VContain - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "VContain - Win32 Release Unicode" (based on\
 "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "VContain - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VContain - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\VContain.exe"

CLEAN : 
	-@erase ".\Release\VContain.exe"
	-@erase ".\Release\SpIntDlg.obj"
	-@erase ".\Release\VContain.pch"
	-@erase ".\Release\VConCtnr.obj"
	-@erase ".\Release\VContain.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\VCErrLog.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\VConView.obj"
	-@erase ".\Release\ResltDlg.obj"
	-@erase ".\Release\Ole2ui.obj"
	-@erase ".\Release\Verify.obj"
	-@erase ".\Release\VCPrpBag.obj"
	-@erase ".\Release\VCAdvSnk.obj"
	-@erase ".\Release\VCDatObj.obj"
	-@erase ".\Release\VContDoc.obj"
	-@erase ".\Release\PreVeDlg.obj"
	-@erase ".\Release\Insertd.obj"
	-@erase ".\Release\VContain.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/VContain.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VContain.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
BSC32_FLAGS=/o"$(OUTDIR)/VContain.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/VContain.pdb" /machine:I386 /out:"$(OUTDIR)/VContain.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SpIntDlg.obj" \
	"$(INTDIR)/VConCtnr.obj" \
	"$(INTDIR)/VContain.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/VCErrLog.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/VConView.obj" \
	"$(INTDIR)/ResltDlg.obj" \
	"$(INTDIR)/Ole2ui.obj" \
	"$(INTDIR)/Verify.obj" \
	"$(INTDIR)/VCPrpBag.obj" \
	"$(INTDIR)/VCAdvSnk.obj" \
	"$(INTDIR)/VCDatObj.obj" \
	"$(INTDIR)/VContDoc.obj" \
	"$(INTDIR)/PreVeDlg.obj" \
	"$(INTDIR)/Insertd.obj" \
	"$(INTDIR)/VContain.res"

"$(OUTDIR)\VContain.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\VContain.exe" "$(OUTDIR)\VContain.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\VContain.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\VContain.bsc"
	-@erase ".\Debug\VCErrLog.sbr"
	-@erase ".\Debug\VConView.sbr"
	-@erase ".\Debug\Ole2ui.sbr"
	-@erase ".\Debug\ResltDlg.sbr"
	-@erase ".\Debug\MainFrm.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\VCPrpBag.sbr"
	-@erase ".\Debug\VCAdvSnk.sbr"
	-@erase ".\Debug\VCDatObj.sbr"
	-@erase ".\Debug\VContDoc.sbr"
	-@erase ".\Debug\PreVeDlg.sbr"
	-@erase ".\Debug\Verify.sbr"
	-@erase ".\Debug\SpIntDlg.sbr"
	-@erase ".\Debug\Insertd.sbr"
	-@erase ".\Debug\VConCtnr.sbr"
	-@erase ".\Debug\VContain.sbr"
	-@erase ".\Debug\VContain.exe"
	-@erase ".\Debug\Insertd.obj"
	-@erase ".\Debug\VConCtnr.obj"
	-@erase ".\Debug\VContain.obj"
	-@erase ".\Debug\VCErrLog.obj"
	-@erase ".\Debug\VConView.obj"
	-@erase ".\Debug\Ole2ui.obj"
	-@erase ".\Debug\ResltDlg.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\VCPrpBag.obj"
	-@erase ".\Debug\VCAdvSnk.obj"
	-@erase ".\Debug\VCDatObj.obj"
	-@erase ".\Debug\VContDoc.obj"
	-@erase ".\Debug\PreVeDlg.obj"
	-@erase ".\Debug\Verify.obj"
	-@erase ".\Debug\SpIntDlg.obj"
	-@erase ".\Debug\VContain.res"
	-@erase ".\Debug\VContain.ilk"
	-@erase ".\Debug\VContain.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/VContain.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VContain.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
BSC32_FLAGS=/o"$(OUTDIR)/VContain.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/VCErrLog.sbr" \
	"$(INTDIR)/VConView.sbr" \
	"$(INTDIR)/Ole2ui.sbr" \
	"$(INTDIR)/ResltDlg.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/VCPrpBag.sbr" \
	"$(INTDIR)/VCAdvSnk.sbr" \
	"$(INTDIR)/VCDatObj.sbr" \
	"$(INTDIR)/VContDoc.sbr" \
	"$(INTDIR)/PreVeDlg.sbr" \
	"$(INTDIR)/Verify.sbr" \
	"$(INTDIR)/SpIntDlg.sbr" \
	"$(INTDIR)/Insertd.sbr" \
	"$(INTDIR)/VConCtnr.sbr" \
	"$(INTDIR)/VContain.sbr"

"$(OUTDIR)\VContain.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/VContain.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/VContain.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Insertd.obj" \
	"$(INTDIR)/VConCtnr.obj" \
	"$(INTDIR)/VContain.obj" \
	"$(INTDIR)/VCErrLog.obj" \
	"$(INTDIR)/VConView.obj" \
	"$(INTDIR)/Ole2ui.obj" \
	"$(INTDIR)/ResltDlg.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/VCPrpBag.obj" \
	"$(INTDIR)/VCAdvSnk.obj" \
	"$(INTDIR)/VCDatObj.obj" \
	"$(INTDIR)/VContDoc.obj" \
	"$(INTDIR)/PreVeDlg.obj" \
	"$(INTDIR)/Verify.obj" \
	"$(INTDIR)/SpIntDlg.obj" \
	"$(INTDIR)/VContain.res"

"$(OUTDIR)\VContain.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VContain"
# PROP BASE Intermediate_Dir "VContain"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "VContain"
# PROP Intermediate_Dir "VContain"
# PROP Target_Dir ""
OUTDIR=.\VContain
INTDIR=.\VContain

ALL : "$(OUTDIR)\VContain.exe" "$(OUTDIR)\VContain.bsc"

CLEAN : 
	-@erase ".\VContain\VContain.bsc"
	-@erase ".\VContain\Ole2ui.sbr"
	-@erase ".\VContain\VContain.pch"
	-@erase ".\VContain\Verify.sbr"
	-@erase ".\VContain\StdAfx.sbr"
	-@erase ".\VContain\Insertd.sbr"
	-@erase ".\VContain\VConCtnr.sbr"
	-@erase ".\VContain\VContain.sbr"
	-@erase ".\VContain\VCErrLog.sbr"
	-@erase ".\VContain\VConView.sbr"
	-@erase ".\VContain\ResltDlg.sbr"
	-@erase ".\VContain\MainFrm.sbr"
	-@erase ".\VContain\VCPrpBag.sbr"
	-@erase ".\VContain\VCAdvSnk.sbr"
	-@erase ".\VContain\VCDatObj.sbr"
	-@erase ".\VContain\VContDoc.sbr"
	-@erase ".\VContain\PreVeDlg.sbr"
	-@erase ".\VContain\SpIntDlg.sbr"
	-@erase ".\VContain\VContain.exe"
	-@erase ".\VContain\PreVeDlg.obj"
	-@erase ".\VContain\SpIntDlg.obj"
	-@erase ".\VContain\Ole2ui.obj"
	-@erase ".\VContain\Verify.obj"
	-@erase ".\VContain\StdAfx.obj"
	-@erase ".\VContain\Insertd.obj"
	-@erase ".\VContain\VConCtnr.obj"
	-@erase ".\VContain\VContain.obj"
	-@erase ".\VContain\VCErrLog.obj"
	-@erase ".\VContain\VConView.obj"
	-@erase ".\VContain\ResltDlg.obj"
	-@erase ".\VContain\MainFrm.obj"
	-@erase ".\VContain\VCPrpBag.obj"
	-@erase ".\VContain\VCAdvSnk.obj"
	-@erase ".\VContain\VCDatObj.obj"
	-@erase ".\VContain\VContDoc.obj"
	-@erase ".\VContain\VContain.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D " UNICODE" /D " _UNICODE" /FR /Yu"stdafx.h" /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D " UNICODE" /D " _UNICODE" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/VContain.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\VContain/
CPP_SBRS=.\VContain/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VContain.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# SUBTRACT BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
BSC32_FLAGS=/o"$(OUTDIR)/VContain.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/Ole2ui.sbr" \
	"$(INTDIR)/Verify.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/Insertd.sbr" \
	"$(INTDIR)/VConCtnr.sbr" \
	"$(INTDIR)/VContain.sbr" \
	"$(INTDIR)/VCErrLog.sbr" \
	"$(INTDIR)/VConView.sbr" \
	"$(INTDIR)/ResltDlg.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/VCPrpBag.sbr" \
	"$(INTDIR)/VCAdvSnk.sbr" \
	"$(INTDIR)/VCDatObj.sbr" \
	"$(INTDIR)/VContDoc.sbr" \
	"$(INTDIR)/PreVeDlg.sbr" \
	"$(INTDIR)/SpIntDlg.sbr"

"$(OUTDIR)\VContain.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /force
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/VContain.pdb" /machine:I386 /out:"$(OUTDIR)/VContain.exe" 
LINK32_OBJS= \
	"$(INTDIR)/PreVeDlg.obj" \
	"$(INTDIR)/SpIntDlg.obj" \
	"$(INTDIR)/Ole2ui.obj" \
	"$(INTDIR)/Verify.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Insertd.obj" \
	"$(INTDIR)/VConCtnr.obj" \
	"$(INTDIR)/VContain.obj" \
	"$(INTDIR)/VCErrLog.obj" \
	"$(INTDIR)/VConView.obj" \
	"$(INTDIR)/ResltDlg.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/VCPrpBag.obj" \
	"$(INTDIR)/VCAdvSnk.obj" \
	"$(INTDIR)/VCDatObj.obj" \
	"$(INTDIR)/VContDoc.obj" \
	"$(INTDIR)/VContain.res"

"$(OUTDIR)\VContain.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "VContain - Win32 Release"
# Name "VContain - Win32 Debug"
# Name "VContain - Win32 Release Unicode"

!IF  "$(CFG)" == "VContain - Win32 Release"

!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "VContain - Win32 Release"

!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VContain.cpp
DEP_CPP_VCONT=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\MainFrm.h"\
	".\VContDoc.h"\
	".\vconview.h"\
	".\Verify.h"\
	".\VCDatObj.h"\
	".\VCAdvSnk.h"\
	".\ResltDlg.h"\
	".\VCPrpBag.h"\
	".\VCErrLog.h"\
	".\VConCtnr.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"


"$(INTDIR)\VContain.obj" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"


"$(INTDIR)\VContain.obj" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VContain.sbr" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"


"$(INTDIR)\VContain.obj" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VContain.sbr" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/VContain.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\VContain.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/VContain.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\VContain.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D " UNICODE" /D " _UNICODE" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/VContain.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\VContain.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "VContain - Win32 Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\VContain.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\VContain.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VContain.rc
DEP_RSC_VCONTA=\
	".\res\VContain.ico"\
	".\res\VContDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\VContain.rc2"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"


"$(INTDIR)\VContain.res" : $(SOURCE) $(DEP_RSC_VCONTA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"


"$(INTDIR)\VContain.res" : $(SOURCE) $(DEP_RSC_VCONTA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"


"$(INTDIR)\VContain.res" : $(SOURCE) $(DEP_RSC_VCONTA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Insertd.cpp

!IF  "$(CFG)" == "VContain - Win32 Release"

DEP_CPP_INSER=\
	".\Insertd.h"\
	".\Olestd.h"\
	".\StdAfx.h"\
	".\VContain.h"\
	

"$(INTDIR)\Insertd.obj" : $(SOURCE) $(DEP_CPP_INSER) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

DEP_CPP_INSER=\
	".\Insertd.h"\
	".\Olestd.h"\
	".\StdAfx.h"\
	".\VContain.h"\
	

"$(INTDIR)\Insertd.obj" : $(SOURCE) $(DEP_CPP_INSER) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\Insertd.sbr" : $(SOURCE) $(DEP_CPP_INSER) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

DEP_CPP_INSER=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\Insertd.h"\
	".\Olestd.h"\
	

"$(INTDIR)\Insertd.obj" : $(SOURCE) $(DEP_CPP_INSER) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\Insertd.sbr" : $(SOURCE) $(DEP_CPP_INSER) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ole2ui.cpp
DEP_CPP_OLE2U=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"


"$(INTDIR)\Ole2ui.obj" : $(SOURCE) $(DEP_CPP_OLE2U) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"


"$(INTDIR)\Ole2ui.obj" : $(SOURCE) $(DEP_CPP_OLE2U) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\Ole2ui.sbr" : $(SOURCE) $(DEP_CPP_OLE2U) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"


"$(INTDIR)\Ole2ui.obj" : $(SOURCE) $(DEP_CPP_OLE2U) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\Ole2ui.sbr" : $(SOURCE) $(DEP_CPP_OLE2U) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\res\VContain.ico

!IF  "$(CFG)" == "VContain - Win32 Release"

!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCDatObj.cpp

!IF  "$(CFG)" == "VContain - Win32 Release"

DEP_CPP_VCDAT=\
	".\StdAfx.h"\
	".\VCDatObj.h"\
	".\VContain.h"\
	

"$(INTDIR)\VCDatObj.obj" : $(SOURCE) $(DEP_CPP_VCDAT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

DEP_CPP_VCDAT=\
	".\StdAfx.h"\
	".\VCDatObj.h"\
	".\VContain.h"\
	

"$(INTDIR)\VCDatObj.obj" : $(SOURCE) $(DEP_CPP_VCDAT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VCDatObj.sbr" : $(SOURCE) $(DEP_CPP_VCDAT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

DEP_CPP_VCDAT=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VCDatObj.h"\
	

"$(INTDIR)\VCDatObj.obj" : $(SOURCE) $(DEP_CPP_VCDAT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VCDatObj.sbr" : $(SOURCE) $(DEP_CPP_VCDAT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCAdvSnk.cpp

!IF  "$(CFG)" == "VContain - Win32 Release"

DEP_CPP_VCADV=\
	".\StdAfx.h"\
	".\VCAdvSnk.h"\
	".\VContain.h"\
	

"$(INTDIR)\VCAdvSnk.obj" : $(SOURCE) $(DEP_CPP_VCADV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

DEP_CPP_VCADV=\
	".\StdAfx.h"\
	".\VCAdvSnk.h"\
	".\VContain.h"\
	

"$(INTDIR)\VCAdvSnk.obj" : $(SOURCE) $(DEP_CPP_VCADV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VCAdvSnk.sbr" : $(SOURCE) $(DEP_CPP_VCADV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

DEP_CPP_VCADV=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VCAdvSnk.h"\
	

"$(INTDIR)\VCAdvSnk.obj" : $(SOURCE) $(DEP_CPP_VCADV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VCAdvSnk.sbr" : $(SOURCE) $(DEP_CPP_VCADV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpIntDlg.cpp

!IF  "$(CFG)" == "VContain - Win32 Release"

DEP_CPP_SPINT=\
	".\SpIntDlg.h"\
	".\StdAfx.h"\
	".\VContain.h"\
	

"$(INTDIR)\SpIntDlg.obj" : $(SOURCE) $(DEP_CPP_SPINT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

DEP_CPP_SPINT=\
	".\SpIntDlg.h"\
	".\StdAfx.h"\
	".\VContain.h"\
	

"$(INTDIR)\SpIntDlg.obj" : $(SOURCE) $(DEP_CPP_SPINT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\SpIntDlg.sbr" : $(SOURCE) $(DEP_CPP_SPINT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

DEP_CPP_SPINT=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\SpIntDlg.h"\
	

"$(INTDIR)\SpIntDlg.obj" : $(SOURCE) $(DEP_CPP_SPINT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\SpIntDlg.sbr" : $(SOURCE) $(DEP_CPP_SPINT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ResltDlg.cpp

!IF  "$(CFG)" == "VContain - Win32 Release"

DEP_CPP_RESLT=\
	".\StdAfx.h"\
	".\PreVeDlg.h"\
	".\ResltDlg.h"\
	".\vconview.h"\
	".\Verify.h"\
	".\VCDatObj.h"\
	".\VCAdvSnk.h"\
	".\VCPrpBag.h"\
	".\VCErrLog.h"\
	".\VContDoc.h"\
	".\VConCtnr.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	
NODEP_CPP_RESLT=\
	".\CListBox"\
	".\CListCtrl"\
	

"$(INTDIR)\ResltDlg.obj" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

DEP_CPP_RESLT=\
	".\StdAfx.h"\
	".\PreVeDlg.h"\
	".\ResltDlg.h"\
	".\vconview.h"\
	".\Verify.h"\
	".\VCDatObj.h"\
	".\VCAdvSnk.h"\
	".\VCPrpBag.h"\
	".\VCErrLog.h"\
	".\VContDoc.h"\
	".\VConCtnr.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	

"$(INTDIR)\ResltDlg.obj" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\ResltDlg.sbr" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

DEP_CPP_RESLT=\
	".\StdAfx.h"\
	".\PreVeDlg.h"\
	".\ResltDlg.h"\
	".\vconview.h"\
	".\Verify.h"\
	".\VCDatObj.h"\
	".\VCAdvSnk.h"\
	".\VCPrpBag.h"\
	".\VCErrLog.h"\
	".\VContDoc.h"\
	".\VConCtnr.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	

"$(INTDIR)\ResltDlg.obj" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\ResltDlg.sbr" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PreVeDlg.cpp
DEP_CPP_PREVE=\
	".\StdAfx.h"\
	".\PreVeDlg.h"\
	".\vconview.h"\
	".\Verify.h"\
	".\VCDatObj.h"\
	".\VCAdvSnk.h"\
	".\ResltDlg.h"\
	".\VCPrpBag.h"\
	".\VCErrLog.h"\
	".\VContDoc.h"\
	".\VConCtnr.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"


"$(INTDIR)\PreVeDlg.obj" : $(SOURCE) $(DEP_CPP_PREVE) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"


"$(INTDIR)\PreVeDlg.obj" : $(SOURCE) $(DEP_CPP_PREVE) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\PreVeDlg.sbr" : $(SOURCE) $(DEP_CPP_PREVE) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"


"$(INTDIR)\PreVeDlg.obj" : $(SOURCE) $(DEP_CPP_PREVE) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\PreVeDlg.sbr" : $(SOURCE) $(DEP_CPP_PREVE) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCPrpBag.cpp
DEP_CPP_VCPRP=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VCPrpBag.h"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"


"$(INTDIR)\VCPrpBag.obj" : $(SOURCE) $(DEP_CPP_VCPRP) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"


"$(INTDIR)\VCPrpBag.obj" : $(SOURCE) $(DEP_CPP_VCPRP) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VCPrpBag.sbr" : $(SOURCE) $(DEP_CPP_VCPRP) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"


"$(INTDIR)\VCPrpBag.obj" : $(SOURCE) $(DEP_CPP_VCPRP) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VCPrpBag.sbr" : $(SOURCE) $(DEP_CPP_VCPRP) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCErrLog.cpp

!IF  "$(CFG)" == "VContain - Win32 Release"

DEP_CPP_VCERR=\
	".\StdAfx.h"\
	".\VCErrLog.h"\
	".\VContain.h"\
	

"$(INTDIR)\VCErrLog.obj" : $(SOURCE) $(DEP_CPP_VCERR) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

DEP_CPP_VCERR=\
	".\StdAfx.h"\
	".\VCErrLog.h"\
	".\VContain.h"\
	

"$(INTDIR)\VCErrLog.obj" : $(SOURCE) $(DEP_CPP_VCERR) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VCErrLog.sbr" : $(SOURCE) $(DEP_CPP_VCERR) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

DEP_CPP_VCERR=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VCErrLog.h"\
	

"$(INTDIR)\VCErrLog.obj" : $(SOURCE) $(DEP_CPP_VCERR) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VCErrLog.sbr" : $(SOURCE) $(DEP_CPP_VCERR) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VConCtnr.cpp
DEP_CPP_VCONC=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VConCtnr.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"


"$(INTDIR)\VConCtnr.obj" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"


"$(INTDIR)\VConCtnr.obj" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VConCtnr.sbr" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"


"$(INTDIR)\VConCtnr.obj" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VConCtnr.sbr" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VContDoc.cpp
DEP_CPP_VCONTD=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VContDoc.h"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"


"$(INTDIR)\VContDoc.obj" : $(SOURCE) $(DEP_CPP_VCONTD) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"


"$(INTDIR)\VContDoc.obj" : $(SOURCE) $(DEP_CPP_VCONTD) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VContDoc.sbr" : $(SOURCE) $(DEP_CPP_VCONTD) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"


"$(INTDIR)\VContDoc.obj" : $(SOURCE) $(DEP_CPP_VCONTD) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VContDoc.sbr" : $(SOURCE) $(DEP_CPP_VCONTD) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Verify.cpp
DEP_CPP_VERIF=\
	".\StdAfx.h"\
	".\Verify.h"\
	

!IF  "$(CFG)" == "VContain - Win32 Release"


"$(INTDIR)\Verify.obj" : $(SOURCE) $(DEP_CPP_VERIF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"


"$(INTDIR)\Verify.obj" : $(SOURCE) $(DEP_CPP_VERIF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\Verify.sbr" : $(SOURCE) $(DEP_CPP_VERIF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"


"$(INTDIR)\Verify.obj" : $(SOURCE) $(DEP_CPP_VERIF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\Verify.sbr" : $(SOURCE) $(DEP_CPP_VERIF) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VConView.cpp

!IF  "$(CFG)" == "VContain - Win32 Release"

DEP_CPP_VCONV=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VContDoc.h"\
	".\vconview.h"\
	".\Insertd.h"\
	".\Verify.h"\
	".\SpIntDlg.h"\
	".\PreVeDlg.h"\
	".\VConCtnr.h"\
	".\VCDatObj.h"\
	".\VCAdvSnk.h"\
	".\ResltDlg.h"\
	".\VCPrpBag.h"\
	".\VCErrLog.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	
NODEP_CPP_VCONV=\
	".\NonStandardVerification"\
	

"$(INTDIR)\VConView.obj" : $(SOURCE) $(DEP_CPP_VCONV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Debug"

DEP_CPP_VCONV=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VContDoc.h"\
	".\vconview.h"\
	".\Insertd.h"\
	".\Verify.h"\
	".\SpIntDlg.h"\
	".\PreVeDlg.h"\
	".\VConCtnr.h"\
	".\VCDatObj.h"\
	".\VCAdvSnk.h"\
	".\ResltDlg.h"\
	".\VCPrpBag.h"\
	".\VCErrLog.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	

"$(INTDIR)\VConView.obj" : $(SOURCE) $(DEP_CPP_VCONV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VConView.sbr" : $(SOURCE) $(DEP_CPP_VCONV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ELSEIF  "$(CFG)" == "VContain - Win32 Release Unicode"

DEP_CPP_VCONV=\
	".\StdAfx.h"\
	".\VContain.h"\
	".\VContDoc.h"\
	".\vconview.h"\
	".\Insertd.h"\
	".\Verify.h"\
	".\SpIntDlg.h"\
	".\PreVeDlg.h"\
	".\VConCtnr.h"\
	".\VCDatObj.h"\
	".\VCAdvSnk.h"\
	".\ResltDlg.h"\
	".\VCPrpBag.h"\
	".\VCErrLog.h"\
	{$(INCLUDE)}"\Occimpl.h"\
	

"$(INTDIR)\VConView.obj" : $(SOURCE) $(DEP_CPP_VCONV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"

"$(INTDIR)\VConView.sbr" : $(SOURCE) $(DEP_CPP_VCONV) "$(INTDIR)"\
 "$(INTDIR)\VContain.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section VContain : {3C5C4461-D266-11CE-AA09-0080C78A1D7F}
# 	2:5:Class:CVerify
# 	2:10:HeaderFile:verify.h
# 	2:8:ImplFile:verify.cpp
# End Section
################################################################################
################################################################################
# Section VContain : {0713E8A3-850A-101B-AFC0-4210102A8DA7}
# 	2:5:Class:CTree
# 	2:10:HeaderFile:tree.h
# 	2:8:ImplFile:tree.cpp
# End Section
################################################################################
################################################################################
# Section VContain : {3C5C4460-D266-11CE-AA09-0080C78A1D7F}
# 	0:8:Verify.h:D:\Drg\VContainer\VContain\Verify.h
# 	0:10:Verify.cpp:D:\Drg\VContainer\VContain\Verify.cpp
# 	2:21:DefaultSinkHeaderFile:verify.h
# 	2:16:DefaultSinkClass:CVerify
# End Section
################################################################################
################################################################################
# Section VContain : {0713E8A2-850A-101B-AFC0-4210102A8DA7}
# 	0:8:Font.cpp:D:\Drg\VContainer\VContain\Font.cpp
# 	0:9:Picture.h:D:\Drg\VContainer\VContain\Picture.h
# 	0:6:Font.h:D:\Drg\VContainer\VContain\Font.h
# 	0:6:Tree.h:D:\Drg\VContainer\VContain\Tree.h
# 	0:11:Picture.cpp:D:\Drg\VContainer\VContain\Picture.cpp
# 	0:8:Tree.cpp:D:\Drg\VContainer\VContain\Tree.cpp
# 	2:21:DefaultSinkHeaderFile:tree.h
# 	2:16:DefaultSinkClass:CTree
# End Section
################################################################################
################################################################################
# Section OLE Controls
# 	{0713E8A2-850A-101B-AFC0-4210102A8DA7}
# 	{3C5C4460-D266-11CE-AA09-0080C78A1D7F}
# End Section
################################################################################
################################################################################
# Section VContain : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
################################################################################
################################################################################
# Section VContain : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
################################################################################
