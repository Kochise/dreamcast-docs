# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=ntddwzd - Win32 Pseudo-Debug
!MESSAGE No configuration specified.  Defaulting to ntddwzd - Win32\
 Pseudo-Debug.
!ENDIF 

!IF "$(CFG)" != "ntddwzd - Win32 Release" && "$(CFG)" !=\
 "ntddwzd - Win32 Pseudo-Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ntddwzd.mak" CFG="ntddwzd - Win32 Pseudo-Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ntddwzd - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ntddwzd - Win32 Pseudo-Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ntddwzd - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ntddwzd_"
# PROP BASE Intermediate_Dir "ntddwzd_"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "awx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ntddwzd_"
# PROP Intermediate_Dir "ntddwzd_"
# PROP Target_Dir ""
# PROP Target_Ext "awx"
OUTDIR=.\ntddwzd_
INTDIR=.\ntddwzd_

ALL : ".\ntddwzd_\ntddwzd.awx" "$(MSDevDir)\Template\$(TargetName).awx"

CLEAN : 
	-@erase ".\ntddwzd_\ntddwzd.awx"
	-@erase ".\ntddwzd_\ntddwzd.obj"
	-@erase ".\ntddwzd_\ntddwzd.pch"
	-@erase ".\ntddwzd_\StdAfx.obj"
	-@erase ".\ntddwzd_\ntddwzdAw.obj"
	-@erase ".\ntddwzd_\Debug.obj"
	-@erase ".\ntddwzd_\ntddwzd.res"
	-@erase ".\ntddwzd_\Chooser.obj"
	-@erase ".\ntddwzd_\Cstm1Dlg.obj"
	-@erase ".\ntddwzd_\Cstm2Dlg.obj"
	-@erase ".\ntddwzd_\Cstm3Dlg.obj"
	-@erase ".\ntddwzd_\ntddwzd.lib"
	-@erase ".\ntddwzd_\ntddwzd.exp"
	-@erase  "$(MSDevDir)\Template\$(TargetName).awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/ntddwzd.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ntddwzd_/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ntddwzd.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ntddwzd.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ntddwzd.pdb" /machine:I386 /out:"$(OUTDIR)/ntddwzd.awx"\
 /implib:"$(OUTDIR)/ntddwzd.lib" 
LINK32_OBJS= \
	".\ntddwzd_\ntddwzd.obj" \
	".\ntddwzd_\StdAfx.obj" \
	".\ntddwzd_\ntddwzdAw.obj" \
	".\ntddwzd_\Debug.obj" \
	".\ntddwzd_\Chooser.obj" \
	".\ntddwzd_\Cstm1Dlg.obj" \
	".\ntddwzd_\Cstm2Dlg.obj" \
	".\ntddwzd_\Cstm3Dlg.obj" \
	".\ntddwzd_\ntddwzd.res"

".\ntddwzd_\ntddwzd.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\ntddwzd_
TargetPath=.\ntddwzd_\ntddwzd.awx
TargetName=ntddwzd
InputPath=.\ntddwzd_\ntddwzd.awx
SOURCE=$(InputPath)

"$(MSDevDir)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   if not exist $(MSDevDir)\Template\nul md $(MSDevDir)\Template
   copy "$(TargetPath)" "$(MSDevDir)\Template"
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
 "$(MSDevDir)\Template"

# End Custom Build

!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "awx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Target_Ext "awx"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\Debug\ntddwzd.awx" "$(MSDevDir)\Template\$(TargetName).awx"

CLEAN : 
	-@erase ".\Debug\ntddwzd.awx"
	-@erase ".\Debug\ntddwzd.obj"
	-@erase ".\Debug\ntddwzd.pch"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\ntddwzdAw.obj"
	-@erase ".\Debug\Debug.obj"
	-@erase ".\Debug\ntddwzd.res"
	-@erase ".\Debug\Chooser.obj"
	-@erase ".\Debug\Cstm1Dlg.obj"
	-@erase ".\Debug\Cstm2Dlg.obj"
	-@erase ".\Debug\Cstm3Dlg.obj"
	-@erase ".\Debug\ntddwzd.ilk"
	-@erase ".\Debug\ntddwzd.lib"
	-@erase ".\Debug\ntddwzd.exp"
	-@erase ".\Debug\ntddwzd.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase  "$(MSDevDir)\Template\$(TargetName).awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT"\
 /Fp"$(INTDIR)/ntddwzd.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ntddwzd.res" /d "NDEBUG" /d "_PSEUDO_DEBUG" /d\
 "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ntddwzd.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ntddwzd.pdb" /debug /machine:I386 /out:"$(OUTDIR)/ntddwzd.awx"\
 /implib:"$(OUTDIR)/ntddwzd.lib" 
LINK32_OBJS= \
	".\Debug\ntddwzd.obj" \
	".\Debug\StdAfx.obj" \
	".\Debug\ntddwzdAw.obj" \
	".\Debug\Debug.obj" \
	".\Debug\Chooser.obj" \
	".\Debug\Cstm1Dlg.obj" \
	".\Debug\Cstm2Dlg.obj" \
	".\Debug\Cstm3Dlg.obj" \
	".\Debug\ntddwzd.res"

".\Debug\ntddwzd.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Debug
TargetPath=.\Debug\ntddwzd.awx
TargetName=ntddwzd
InputPath=.\Debug\ntddwzd.awx
SOURCE=$(InputPath)

"$(MSDevDir)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   if not exist $(MSDevDir)\Template\nul md $(MSDevDir)\Template
   copy "$(TargetPath)" "$(MSDevDir)\Template"
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
 "$(MSDevDir)\Template"

# End Custom Build

!ENDIF 

MTL_PROJ=/nologo /D "NDEBUG" /win32 

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

# Name "ntddwzd - Win32 Release"
# Name "ntddwzd - Win32 Pseudo-Debug"

!IF  "$(CFG)" == "ntddwzd - Win32 Release"

!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ntddwzd.cpp
DEP_CPP_NTDDW=\
	".\ntddwzd.h"\
	".\ntddwzdAw.h"\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"


".\ntddwzd_\ntddwzd.obj" : $(SOURCE) $(DEP_CPP_NTDDW) "$(INTDIR)"\
 ".\ntddwzd_\ntddwzd.pch"


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"


".\Debug\ntddwzd.obj" : $(SOURCE) $(DEP_CPP_NTDDW) "$(INTDIR)"\
 ".\Debug\ntddwzd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"

# ADD CPP /Yc"stdafx.h"

".\ntddwzd_\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/ntddwzd.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"

# ADD CPP /Yc"stdafx.h"

".\Debug\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT"\
 /Fp"$(INTDIR)/ntddwzd.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ntddwzdAw.cpp
DEP_CPP_NTDDWZ=\
	".\Chooser.h"\
	".\ntddwzd.h"\
	".\ntddwzdAw.h"\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"


".\ntddwzd_\ntddwzdAw.obj" : $(SOURCE) $(DEP_CPP_NTDDWZ) "$(INTDIR)"\
 ".\ntddwzd_\ntddwzd.pch"


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"


".\Debug\ntddwzdAw.obj" : $(SOURCE) $(DEP_CPP_NTDDWZ) "$(INTDIR)"\
 ".\Debug\ntddwzd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Debug.cpp
DEP_CPP_DEBUG=\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"


".\ntddwzd_\Debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 ".\ntddwzd_\ntddwzd.pch"


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"


".\Debug\Debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 ".\Debug\ntddwzd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ntddwzd.rc
DEP_RSC_NTDDWZD=\
	".\template\newproj.inf"\
	".\template\confirm.inf"\
	".\Template\rootdep.c"\
	".\Template\rootdep.h"\
	".\Template\root.mak"\
	".\Template\rootdep.cpp"\
	".\Template\rootdep.hpp"\
	".\Template\devext.cpp"\
	".\Template\drvclass.cpp"\
	".\Template\drvclass.h"\
	".\Template\devext.h"\
	".\Template\rootpp.mak"\
	".\Template\root.lnk"\
	".\Template\rootpp.lnk"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"


".\ntddwzd_\ntddwzd.res" : $(SOURCE) $(DEP_RSC_NTDDWZD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"


".\Debug\ntddwzd.res" : $(SOURCE) $(DEP_RSC_NTDDWZD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "ntddwzd - Win32 Release"

!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chooser.cpp
DEP_CPP_CHOOS=\
	".\Chooser.h"\
	".\Cstm1Dlg.h"\
	".\Cstm2Dlg.h"\
	".\ntddwzd.h"\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"


".\ntddwzd_\Chooser.obj" : $(SOURCE) $(DEP_CPP_CHOOS) "$(INTDIR)"\
 ".\ntddwzd_\ntddwzd.pch"


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"


".\Debug\Chooser.obj" : $(SOURCE) $(DEP_CPP_CHOOS) "$(INTDIR)"\
 ".\Debug\ntddwzd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cstm1Dlg.cpp
DEP_CPP_CSTM1=\
	".\Cstm1Dlg.h"\
	".\ntddwzd.h"\
	".\ntddwzdAw.h"\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"


".\ntddwzd_\Cstm1Dlg.obj" : $(SOURCE) $(DEP_CPP_CSTM1) "$(INTDIR)"\
 ".\ntddwzd_\ntddwzd.pch"


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"


".\Debug\Cstm1Dlg.obj" : $(SOURCE) $(DEP_CPP_CSTM1) "$(INTDIR)"\
 ".\Debug\ntddwzd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cstm2Dlg.cpp
DEP_CPP_CSTM2=\
	".\Cstm2Dlg.h"\
	".\ntddwzd.h"\
	".\ntddwzdAw.h"\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"


".\ntddwzd_\Cstm2Dlg.obj" : $(SOURCE) $(DEP_CPP_CSTM2) "$(INTDIR)"\
 ".\ntddwzd_\ntddwzd.pch"


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"


".\Debug\Cstm2Dlg.obj" : $(SOURCE) $(DEP_CPP_CSTM2) "$(INTDIR)"\
 ".\Debug\ntddwzd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cstm3Dlg.cpp
DEP_CPP_CSTM3=\
	".\ntddwzd.h"\
	".\ntddwzdAw.h"\
	".\cstm3dlg.h"\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "ntddwzd - Win32 Release"


".\ntddwzd_\Cstm3Dlg.obj" : $(SOURCE) $(DEP_CPP_CSTM3) "$(INTDIR)"\
 ".\ntddwzd_\ntddwzd.pch"


!ELSEIF  "$(CFG)" == "ntddwzd - Win32 Pseudo-Debug"


".\Debug\Cstm3Dlg.obj" : $(SOURCE) $(DEP_CPP_CSTM3) "$(INTDIR)"\
 ".\Debug\ntddwzd.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
