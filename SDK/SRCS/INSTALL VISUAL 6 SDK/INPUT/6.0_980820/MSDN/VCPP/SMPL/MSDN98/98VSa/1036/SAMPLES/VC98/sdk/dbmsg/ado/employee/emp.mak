# Microsoft Developer Studio Generated NMAKE File, Format Version 41001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (PPC) Application" 0x0701
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=Emp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Emp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Emp - Win32 Release" && "$(CFG)" != "Emp - Win32 Debug" &&\
 "$(CFG)" != "Emp - Win32 (ALPHA) Debug" && "$(CFG)" !=\
 "Emp - Win32 (ALPHA) Release" && "$(CFG)" != "Emp - Win32 (PPC) Debug" &&\
 "$(CFG)" != "Emp - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "emp.mak" CFG="Emp - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Emp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Emp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Emp - Win32 (ALPHA) Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "Emp - Win32 (ALPHA) Release" (based on "Win32 (ALPHA) Application")
!MESSAGE "Emp - Win32 (PPC) Debug" (based on "Win32 (PPC) Application")
!MESSAGE "Emp - Win32 (PPC) Release" (based on "Win32 (PPC) Application")
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
# PROP Target_Last_Scanned "Emp - Win32 (PPC) Release"

!IF  "$(CFG)" == "Emp - Win32 Release"

# PROP BASE Use_MFC 6
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

ALL :    "$(OUTDIR)\emp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)/emp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Emp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/emp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 adoid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/emp.pdb" /machine:I386 /out:"$(OUTDIR)/emp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Emp.obj" \
	"$(INTDIR)\Emp.res" \
	"$(INTDIR)\EmpBiz.obj" \
	"$(INTDIR)\EmpDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\emp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Emp - Win32 Debug"

# PROP BASE Use_MFC 6
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

ALL :    "$(OUTDIR)\emp.exe" "$(OUTDIR)\emp.pch" "$(OUTDIR)\emp.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/emp.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Emp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/emp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Emp.sbr" \
	"$(INTDIR)\EmpBiz.sbr" \
	"$(INTDIR)\EmpDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\emp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 adoid.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"nafxcwd.lib"
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/emp.pdb" /debug /machine:I386 /nodefaultlib:"nafxcwd.lib"\
 /out:"$(OUTDIR)/emp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Emp.obj" \
	"$(INTDIR)\Emp.res" \
	"$(INTDIR)\EmpBiz.obj" \
	"$(INTDIR)\EmpDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\emp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Emp___Wi"
# PROP BASE Intermediate_Dir "Emp___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
OUTDIR=.\debug
INTDIR=.\debug

ALL :  ".\Debug\emp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CLEAN : 
	-@erase ".\Debug\emp.exe"
	-@erase ".\debug\emp.ilk"
	-@erase ".\debug\Emp.obj"
	-@erase ".\debug\emp.pdb"
	-@erase ".\debug\Emp.res"
	-@erase ".\debug\EmpBiz.obj"
	-@erase ".\debug\EmpDlg.obj"
	-@erase ".\debug\StdAfx.obj"
	-@erase ".\debug\vc40.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/emp.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\debug/
CPP_SBRS=.\.

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Emp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/emp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 adoid.lib /nologo /subsystem:windows /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/emp.pdb" /debug /machine:ALPHA /out:"$(OUTDIR)/emp.exe" 
LINK32_OBJS= \
	".\debug\Emp.obj" \
	".\debug\Emp.res" \
	".\debug\EmpBiz.obj" \
	".\debug\EmpDlg.obj" \
	".\debug\StdAfx.obj"

".\Debug\emp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Emp___W0"
# PROP BASE Intermediate_Dir "Emp___W0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Target_Dir ""
OUTDIR=.\retail
INTDIR=.\retail

ALL :  ".\retail\emp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CLEAN : 
	-@erase ".\retail\emp.exe"
	-@erase ".\retail\Emp.obj"
	-@erase ".\retail\Emp.res"
	-@erase ".\retail\EmpBiz.obj"
	-@erase ".\retail\EmpDlg.obj"
	-@erase ".\retail\StdAfx.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/emp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\retail/
CPP_SBRS=.\.

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Emp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/emp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 adoid.lib /nologo /subsystem:windows /machine:ALPHA
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/emp.pdb" /machine:ALPHA /out:"$(OUTDIR)/emp.exe" 
LINK32_OBJS= \
	".\retail\Emp.obj" \
	".\retail\Emp.res" \
	".\retail\EmpBiz.obj" \
	".\retail\EmpDlg.obj" \
	".\retail\StdAfx.obj"

".\retail\emp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Emp___Wi"
# PROP BASE Intermediate_Dir "Emp___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
OUTDIR=.\debug
INTDIR=.\debug

ALL : ".\Debug\emp.exe"

CLEAN : 
	-@erase ".\Debug\emp.exe"
	-@erase ".\Debug\Emp.obj"
	-@erase ".\Debug\emp.pdb"
	-@erase ".\Debug\Emp.res"
	-@erase ".\Debug\EmpBiz.obj"
	-@erase ".\Debug\EmpDlg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /PPC32
# ADD MTL /nologo /D "_DEBUG" /PPC32
MTL_PROJ=/nologo /D "_DEBUG" /PPC32 
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/emp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\debug/
CPP_SBRS=.\.

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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Emp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/emp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:PPC
# ADD LINK32 adoid.lib /nologo /subsystem:windows /debug /machine:PPC
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /pdb:"$(OUTDIR)/emp.pdb"\
 /debug /machine:PPC /out:"$(OUTDIR)/emp.exe" 
LINK32_OBJS= \
	".\Debug\Emp.obj" \
	".\Debug\Emp.res" \
	".\Debug\EmpBiz.obj" \
	".\Debug\EmpDlg.obj" \
	".\Debug\StdAfx.obj"

".\Debug\emp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Emp___W0"
# PROP BASE Intermediate_Dir "Emp___W0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Target_Dir ""
OUTDIR=.\retail
INTDIR=.\retail

ALL : ".\retail\emp.exe"

CLEAN : 
	-@erase ".\retail\emp.exe"
	-@erase ".\retail\Emp.obj"
	-@erase ".\retail\Emp.res"
	-@erase ".\retail\EmpBiz.obj"
	-@erase ".\retail\EmpDlg.obj"
	-@erase ".\retail\StdAfx.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /PPC32
# ADD MTL /nologo /D "NDEBUG" /PPC32
MTL_PROJ=/nologo /D "NDEBUG" /PPC32 
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/emp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\retail/
CPP_SBRS=.\.

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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Emp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/emp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:PPC
# ADD LINK32 adoid.lib /nologo /subsystem:windows /machine:PPC
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /pdb:"$(OUTDIR)/emp.pdb"\
 /machine:PPC /out:"$(OUTDIR)/emp.exe" 
LINK32_OBJS= \
	".\retail\Emp.obj" \
	".\retail\Emp.res" \
	".\retail\EmpBiz.obj" \
	".\retail\EmpDlg.obj" \
	".\retail\StdAfx.obj"

".\retail\emp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "Emp - Win32 Release"
# Name "Emp - Win32 Debug"
# Name "Emp - Win32 (ALPHA) Debug"
# Name "Emp - Win32 (ALPHA) Release"
# Name "Emp - Win32 (PPC) Debug"
# Name "Emp - Win32 (PPC) Release"

!IF  "$(CFG)" == "Emp - Win32 Release"

!ELSEIF  "$(CFG)" == "Emp - Win32 Debug"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Emp.cpp

!IF  "$(CFG)" == "Emp - Win32 Release"

"$(INTDIR)\Emp.obj" : $(SOURCE) $(DEP_CPP_EMP_C) "$(INTDIR)"\
 "$(INTDIR)\emp.pch"

!ELSEIF  "$(CFG)" == "Emp - Win32 Debug"

DEP_CPP_EMP_C=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Emp.obj" : $(SOURCE) $(DEP_CPP_EMP_C) "$(INTDIR)"

"$(INTDIR)\Emp.sbr" : $(SOURCE) $(DEP_CPP_EMP_C) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Debug"

DEP_CPP_EMP_C=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	

".\debug\Emp.obj" : $(SOURCE) $(DEP_CPP_EMP_C) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Release"

DEP_CPP_EMP_C=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	

".\retail\Emp.obj" : $(SOURCE) $(DEP_CPP_EMP_C) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Debug"

DEP_CPP_EMP_C=\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

".\Debug\Emp.obj" : $(SOURCE) $(DEP_CPP_EMP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Release"

DEP_CPP_EMP_C=\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

".\retail\Emp.obj" : $(SOURCE) $(DEP_CPP_EMP_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EmpDlg.cpp

!IF  "$(CFG)" == "Emp - Win32 Release"

"$(INTDIR)\EmpDlg.obj" : $(SOURCE) $(DEP_CPP_EMPDL) "$(INTDIR)"\
 "$(INTDIR)\emp.pch"

!ELSEIF  "$(CFG)" == "Emp - Win32 Debug"

DEP_CPP_EMPDL=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\EmpDlg.obj" : $(SOURCE) $(DEP_CPP_EMPDL) "$(INTDIR)"

"$(INTDIR)\EmpDlg.sbr" : $(SOURCE) $(DEP_CPP_EMPDL) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Debug"

DEP_CPP_EMPDL=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	

".\debug\EmpDlg.obj" : $(SOURCE) $(DEP_CPP_EMPDL) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Release"

DEP_CPP_EMPDL=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	

".\retail\EmpDlg.obj" : $(SOURCE) $(DEP_CPP_EMPDL) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Debug"

DEP_CPP_EMPDL=\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

".\Debug\EmpDlg.obj" : $(SOURCE) $(DEP_CPP_EMPDL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Release"

DEP_CPP_EMPDL=\
	".\emp.h"\
	".\empbiz.h"\
	".\empdlg.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

".\retail\EmpDlg.obj" : $(SOURCE) $(DEP_CPP_EMPDL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Emp - Win32 Release"

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\emp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Emp - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	
# ADD CPP /Yc"stdafx.h"
BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/emp.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\emp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

".\debug\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

".\retail\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

".\Debug\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

".\retail\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Emp.rc

!IF  "$(CFG)" == "Emp - Win32 Release"

"$(INTDIR)\Emp.res" : $(SOURCE) $(DEP_RSC_EMP_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Emp - Win32 Debug"

DEP_RSC_EMP_R=\
	".\res\emp.ico"\
	".\res\emp.rc2"\
	

"$(INTDIR)\Emp.res" : $(SOURCE) $(DEP_RSC_EMP_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Debug"

DEP_RSC_EMP_R=\
	".\res\emp.ico"\
	".\res\emp.rc2"\
	

".\debug\Emp.res" : $(SOURCE) $(DEP_RSC_EMP_R) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Emp.res" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Release"

DEP_RSC_EMP_R=\
	".\res\emp.ico"\
	".\res\emp.rc2"\
	

".\retail\Emp.res" : $(SOURCE) $(DEP_RSC_EMP_R) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Emp.res" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Debug"

DEP_RSC_EMP_R=\
	".\res\emp.ico"\
	".\res\emp.rc2"\
	

".\Debug\Emp.res" : $(SOURCE) $(DEP_RSC_EMP_R) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Emp.res" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Release"

DEP_RSC_EMP_R=\
	".\res\emp.ico"\
	".\res\emp.rc2"\
	

".\retail\Emp.res" : $(SOURCE) $(DEP_RSC_EMP_R) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Emp.res" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EmpBiz.cpp

!IF  "$(CFG)" == "Emp - Win32 Release"

"$(INTDIR)\EmpBiz.obj" : $(SOURCE) $(DEP_CPP_EMPBI) "$(INTDIR)"\
 "$(INTDIR)\emp.pch"

!ELSEIF  "$(CFG)" == "Emp - Win32 Debug"

DEP_CPP_EMPBI=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\stdafx.h"\
	

"$(INTDIR)\EmpBiz.obj" : $(SOURCE) $(DEP_CPP_EMPBI) "$(INTDIR)"

"$(INTDIR)\EmpBiz.sbr" : $(SOURCE) $(DEP_CPP_EMPBI) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Debug"

DEP_CPP_EMPBI=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\stdafx.h"\
	

".\debug\EmpBiz.obj" : $(SOURCE) $(DEP_CPP_EMPBI) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (ALPHA) Release"

DEP_CPP_EMPBI=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\emp.h"\
	".\empbiz.h"\
	".\stdafx.h"\
	

".\retail\EmpBiz.obj" : $(SOURCE) $(DEP_CPP_EMPBI) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Debug"

DEP_CPP_EMPBI=\
	".\emp.h"\
	".\empbiz.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

".\Debug\EmpBiz.obj" : $(SOURCE) $(DEP_CPP_EMPBI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Emp - Win32 (PPC) Release"

DEP_CPP_EMPBI=\
	".\emp.h"\
	".\empbiz.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

".\retail\EmpBiz.obj" : $(SOURCE) $(DEP_CPP_EMPBI) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
