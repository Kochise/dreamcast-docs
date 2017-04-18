# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

!IF "$(CFG)" == ""
CFG=SmbSmp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SmbSmp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SmbSmp - Win32 Release" && "$(CFG)" != "SmbSmp - Win32 Debug"\
 && "$(CFG)" != "SmbSmp - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "SmbSmp - Win32 (ALPHA) Debug" && "$(CFG)" != "SmbSmpEx - Win32 Release" &&\
 "$(CFG)" != "SmbSmpEx - Win32 Debug" && "$(CFG)" !=\
 "SmbSmpEx - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "SmbSmpEx - Win32 (ALPHA) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SmbSmp.mak" CFG="SmbSmp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SmbSmp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "SmbSmpEx - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmpEx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmpEx - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "SmbSmpEx - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "SmbSmp - Win32 Debug"

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SmbSmp\Release"
# PROP BASE Intermediate_Dir "SmbSmp\Release"
# PROP BASE Target_Dir "SmbSmp"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SmbSmp\Release"
# PROP Intermediate_Dir "SmbSmp\Release"
# PROP Target_Dir "SmbSmp"
OUTDIR=.\SmbSmp\Release
INTDIR=.\SmbSmp\Release

ALL : "$(OUTDIR)\SmbSmp.dll"

CLEAN : 
	-@erase "$(INTDIR)\SmbSmp.obj"
	-@erase "$(INTDIR)\SmbSmp.res"
	-@erase "$(OUTDIR)\SmbSmp.dll"
	-@erase "$(OUTDIR)\SmbSmp.exp"
	-@erase "$(OUTDIR)\SmbSmp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe

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

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "SmbSmp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "SmbSmp" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)/SmbSmp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SmbSmp\Release/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SmbSmp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/SmbSmp.pdb" /machine:I386 /def:".\SmbSmp\SmbSmp.def"\
 /out:"$(OUTDIR)/SmbSmp.dll" /implib:"$(OUTDIR)/SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SmbSmp\Debug"
# PROP BASE Intermediate_Dir "SmbSmp\Debug"
# PROP BASE Target_Dir "SmbSmp"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SmbSmp\Debug"
# PROP Intermediate_Dir "SmbSmp\Debug"
# PROP Target_Dir "SmbSmp"
OUTDIR=.\SmbSmp\Debug
INTDIR=.\SmbSmp\Debug

ALL : "$(OUTDIR)\SmbSmp.dll"

CLEAN : 
	-@erase "$(INTDIR)\SmbSmp.obj"
	-@erase "$(INTDIR)\SmbSmp.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\SmbSmp.dll"
	-@erase "$(OUTDIR)\SmbSmp.exp"
	-@erase "$(OUTDIR)\SmbSmp.ilk"
	-@erase "$(OUTDIR)\SmbSmp.lib"
	-@erase "$(OUTDIR)\SmbSmp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

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

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "SmbSmp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "SmbSmp" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)/SmbSmp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\SmbSmp\Debug/
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
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SmbSmp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/SmbSmp.pdb" /debug /machine:I386 /def:".\SmbSmp\SmbSmp.def"\
 /out:"$(OUTDIR)/SmbSmp.dll" /implib:"$(OUTDIR)/SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SmbSmp\AlphaRel"
# PROP BASE Intermediate_Dir "SmbSmp\AlphaRel"
# PROP BASE Target_Dir "SmbSmp"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SmbSmp\AlphaRel"
# PROP Intermediate_Dir "SmbSmp\AlphaRel"
# PROP Target_Dir "SmbSmp"
OUTDIR=.\SmbSmp\AlphaRel
INTDIR=.\SmbSmp\AlphaRel

ALL :  "$(OUTDIR)\SmbSmp.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /YX /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /I "SmbSmp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /YX /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /I "SmbSmp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)/SmbSmp.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SmbSmp\AlphaRel/
CPP_SBRS=.\.
MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SmbSmp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /dll /machine:ALPHA
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/SmbSmp.pdb" /machine:ALPHA /def:".\SmbSmp\SmbSmp.def"\
 /out:"$(OUTDIR)/SmbSmp.dll" /implib:"$(OUTDIR)/SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SmbSmp\AlphaDbg"
# PROP BASE Intermediate_Dir "SmbSmp\AlphaDbg"
# PROP BASE Target_Dir "SmbSmp"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SmbSmp\AlphaDbg"
# PROP Intermediate_Dir "SmbSmp\AlphaDbg"
# PROP Target_Dir "SmbSmp"
OUTDIR=.\SmbSmp\AlphaDbg
INTDIR=.\SmbSmp\AlphaDbg

ALL :  "$(OUTDIR)\SmbSmp.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /YX /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /I "SmbSmp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /YX /c
CPP_PROJ=/nologo /MDd /Gt0 /W3 /GX /Zi /Od /I "SmbSmp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)/SmbSmp.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\SmbSmp\AlphaDbg/
CPP_SBRS=.\.
MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SmbSmp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:ALPHA
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/SmbSmp.pdb" /debug /machine:ALPHA /def:".\SmbSmp\SmbSmp.def"\
 /out:"$(OUTDIR)/SmbSmp.dll" /implib:"$(OUTDIR)/SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SmbSmpEx\Release"
# PROP BASE Intermediate_Dir "SmbSmpEx\Release"
# PROP BASE Target_Dir "SmbSmpEx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SmbSmpEx\Release"
# PROP Intermediate_Dir "SmbSmpEx\Release"
# PROP Target_Dir "SmbSmpEx"
OUTDIR=.\SmbSmpEx\Release
INTDIR=.\SmbSmpEx\Release

ALL : "$(OUTDIR)\SmbSmpEx.dll" ".\SmbSmpEx\ExtObjID.tlb"

CLEAN : 
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\SmbSmpEx.obj"
	-@erase "$(INTDIR)\SmbSmpEx.pch"
	-@erase "$(INTDIR)\SmbSmpEx.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\SmbSmpEx.dll"
	-@erase "$(OUTDIR)\SmbSmpEx.exp"
	-@erase "$(OUTDIR)\SmbSmpEx.lib"
	-@erase ".\SmbSmpEx\ExtObjID.h"
	-@erase ".\SmbSmpEx\ExtObjID.tlb"
	-@erase ".\SmbSmpEx\ExtObjID_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

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

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "SmbSmpEx" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "SmbSmpEx" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)/SmbSmpEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SmbSmpEx\Release/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SmbSmpEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/SmbSmpEx.pdb" /machine:I386 /def:".\SmbSmpEx\SmbSmpEx.def"\
 /out:"$(OUTDIR)/SmbSmpEx.dll" /implib:"$(OUTDIR)/SmbSmpEx.lib" 
DEF_FILE= \
	".\SmbSmpEx\SmbSmpEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\SmbSmpEx.obj" \
	"$(INTDIR)\SmbSmpEx.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SmbSmpEx\Debug"
# PROP BASE Intermediate_Dir "SmbSmpEx\Debug"
# PROP BASE Target_Dir "SmbSmpEx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SmbSmpEx\Debug"
# PROP Intermediate_Dir "SmbSmpEx\Debug"
# PROP Target_Dir "SmbSmpEx"
OUTDIR=.\SmbSmpEx\Debug
INTDIR=.\SmbSmpEx\Debug

ALL : "$(OUTDIR)\SmbSmpEx.dll" ".\SmbSmpEx\ExtObjID.tlb"

CLEAN : 
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\SmbSmpEx.obj"
	-@erase "$(INTDIR)\SmbSmpEx.pch"
	-@erase "$(INTDIR)\SmbSmpEx.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\SmbSmpEx.dll"
	-@erase "$(OUTDIR)\SmbSmpEx.exp"
	-@erase "$(OUTDIR)\SmbSmpEx.ilk"
	-@erase "$(OUTDIR)\SmbSmpEx.lib"
	-@erase "$(OUTDIR)\SmbSmpEx.pdb"
	-@erase ".\SmbSmpEx\ExtObjID.h"
	-@erase ".\SmbSmpEx\ExtObjID.tlb"
	-@erase ".\SmbSmpEx\ExtObjID_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

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

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "SmbSmpEx" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "SmbSmpEx" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)/SmbSmpEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\SmbSmpEx\Debug/
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
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SmbSmpEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/SmbSmpEx.pdb" /debug /machine:I386\
 /def:".\SmbSmpEx\SmbSmpEx.def" /out:"$(OUTDIR)/SmbSmpEx.dll"\
 /implib:"$(OUTDIR)/SmbSmpEx.lib" 
DEF_FILE= \
	".\SmbSmpEx\SmbSmpEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\SmbSmpEx.obj" \
	"$(INTDIR)\SmbSmpEx.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SmbSmpEx\AlphaRel"
# PROP BASE Intermediate_Dir "SmbSmpEx\AlphaRel"
# PROP BASE Target_Dir "SmbSmpEx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SmbSmpEx\AlphaRel"
# PROP Intermediate_Dir "SmbSmpEx\AlphaRel"
# PROP Target_Dir "SmbSmpEx"
OUTDIR=.\SmbSmpEx\AlphaRel
INTDIR=.\SmbSmpEx\AlphaRel

ALL :  "$(OUTDIR)\SmbSmpEx.dll" ".\SmbSmpEx\ExtObjID.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /I "SmbSmpEx" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /I "SmbSmpEx" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)/SmbSmpEx.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SmbSmpEx\AlphaRel/
CPP_SBRS=.\.
MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SmbSmpEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /dll /machine:ALPHA
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/SmbSmpEx.pdb" /machine:ALPHA /def:".\SmbSmpEx\SmbSmpEx.def"\
 /out:"$(OUTDIR)/SmbSmpEx.dll" /implib:"$(OUTDIR)/SmbSmpEx.lib" 
DEF_FILE= \
	".\SmbSmpEx\SmbSmpEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\SmbSmpEx.obj" \
	"$(INTDIR)\SmbSmpEx.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SmbSmpEx\AlphaDbg"
# PROP BASE Intermediate_Dir "SmbSmpEx\AlphaDbg"
# PROP BASE Target_Dir "SmbSmpEx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SmbSmpEx\AlphaDbg"
# PROP Intermediate_Dir "SmbSmpEx\AlphaDbg"
# PROP Target_Dir "SmbSmpEx"
OUTDIR=.\SmbSmpEx\AlphaDbg
INTDIR=.\SmbSmpEx\AlphaDbg

ALL :  "$(OUTDIR)\SmbSmpEx.dll" ".\SmbSmpEx\ExtObjID.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)/SmbSmpEx.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\SmbSmpEx\AlphaDbg/
CPP_SBRS=.\.
MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SmbSmpEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:ALPHA
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/SmbSmpEx.pdb" /debug /machine:ALPHA /def:".\SmbSmpEx\SmbSmpEx.def"\
 /out:"$(OUTDIR)/SmbSmpEx.dll" /implib:"$(OUTDIR)/SmbSmpEx.lib" 
DEF_FILE= \
	".\SmbSmpEx\SmbSmpEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\SmbSmpEx.obj" \
	"$(INTDIR)\SmbSmpEx.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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

!ENDIF 

################################################################################
# Begin Target

# Name "SmbSmp - Win32 Release"
# Name "SmbSmp - Win32 Debug"
# Name "SmbSmp - Win32 (ALPHA) Release"
# Name "SmbSmp - Win32 (ALPHA) Debug"

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SmbSmp\SmbSmp.c

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

DEP_CPP_SMBSM=\
	{$(INCLUDE)}"\clusapi.h"\
	{$(INCLUDE)}"\resapi.h"\
	

"$(INTDIR)\SmbSmp.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

DEP_CPP_SMBSM=\
	{$(INCLUDE)}"\clusapi.h"\
	{$(INCLUDE)}"\resapi.h"\
	

"$(INTDIR)\SmbSmp.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

"$(INTDIR)\SmbSmp.obj" : $(SOURCE) $(DEP_CPP_SMBSMP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

DEP_CPP_SMBSM=\
	".\clusapi.h"\
	".\resapi.h"\
	

"$(INTDIR)\SmbSmp.obj" : $(SOURCE) $(DEP_CPP_SMBSMP) "$(INTDIR)"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmp\SmbSmp.rc

!IF  "$(CFG)" == "SmbSmp - Win32 Release"


"$(INTDIR)\SmbSmp.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/SmbSmp.res" /i "SmbSmp" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"


"$(INTDIR)\SmbSmp.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/SmbSmp.res" /i "SmbSmp" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

"$(INTDIR)\SmbSmp.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

"$(INTDIR)\SmbSmp.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmp\SmbSmp.def

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmp\ReadMe.txt

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

!ENDIF 

# End Source File
# End Target
################################################################################
# Begin Target

# Name "SmbSmpEx - Win32 Release"
# Name "SmbSmpEx - Win32 Debug"
# Name "SmbSmpEx - Win32 (ALPHA) Release"
# Name "SmbSmpEx - Win32 (ALPHA) Debug"

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\SmbSmpEx.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_SMBSMP=\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\RegExt.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.cpp"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atliface.h"\
	{$(INCLUDE)}"\atlimpl.cpp"\
	{$(INCLUDE)}"\CluAdmEx.h"\
	{$(INCLUDE)}"\clusapi.h"\
	
NODEP_CPP_SMBSMP=\
	".\SmbSmpEx\ExtObjID.h"\
	".\SmbSmpEx\ExtObjID_i.c"\
	

"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) $(DEP_CPP_SMBSMP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h" ".\SmbSmpEx\ExtObjID_i.c"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_SMBSMP=\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\RegExt.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.cpp"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atliface.h"\
	{$(INCLUDE)}"\atlimpl.cpp"\
	{$(INCLUDE)}"\CluAdmEx.h"\
	{$(INCLUDE)}"\clusapi.h"\
	
NODEP_CPP_SMBSMP=\
	".\SmbSmpEx\ExtObjID.h"\
	".\SmbSmpEx\ExtObjID_i.c"\
	

"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) $(DEP_CPP_SMBSMP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h" ".\SmbSmpEx\ExtObjID_i.c"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) $(DEP_CPP_SMBSMPE) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h" ".\SmbSmpEx\ExtObjID_i.c"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_SMBSMP=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\atlimpl.cpp"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\RegExt.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	
NODEP_CPP_SMBSMP=\
	".\SmbSmpEx\ExtObjID.h"\
	".\SmbSmpEx\ExtObjID_i.c"\
	

"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) $(DEP_CPP_SMBSMPE) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h" ".\SmbSmpEx\ExtObjID_i.c"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\SmbSmpEx.def

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\SmbSmpEx.rc

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_RSC_SMBSMPE=\
	".\SmbSmpEx\res\SmbSmpEx.rc2"\
	

"$(INTDIR)\SmbSmpEx.res" : $(SOURCE) $(DEP_RSC_SMBSMPE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/SmbSmpEx.res" /i "SmbSmpEx" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_RSC_SMBSMPE=\
	".\SmbSmpEx\res\SmbSmpEx.rc2"\
	

"$(INTDIR)\SmbSmpEx.res" : $(SOURCE) $(DEP_RSC_SMBSMPE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/SmbSmpEx.res" /i "SmbSmpEx" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\SmbSmpEx.res" : $(SOURCE) $(DEP_RSC_SMBSMPEX) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_RSC_SMBSMPE=\
	".\SmbSmpEx\res\SmbSmpEx.rc2"\
	

"$(INTDIR)\SmbSmpEx.res" : $(SOURCE) $(DEP_RSC_SMBSMPEX) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\ExtObjID.idl

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

# Begin Custom Build - Running MIDL
InputDir=.\SmbSmpEx
InputPath=.\SmbSmpEx\ExtObjID.idl
InputName=ExtObjID

BuildCmds= \
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

# Begin Custom Build - Running MIDL
InputDir=.\SmbSmpEx
InputPath=.\SmbSmpEx\ExtObjID.idl
InputName=ExtObjID

BuildCmds= \
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

# Begin Custom Build - Running MIDL
BuildCmds=midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

BuildCmds= \
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

# Begin Custom Build - Running MIDL
BuildCmds=midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

BuildCmds= \
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\BasePage.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_BASEP=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\BasePage.inl"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	
NODEP_CPP_BASEP=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_BASEP=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\BasePage.inl"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	
NODEP_CPP_BASEP=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_BASEP=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\BasePage.inl"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	
NODEP_CPP_BASEP=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\DDxDDv.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_DDXDD=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\DDxDDv.h"\
	".\SmbSmpEx\stdafx.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_DDXDD=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\DDxDDv.h"\
	".\SmbSmpEx\stdafx.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_DDXDD=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\DDxDDv.h"\
	".\SmbSmpEx\stdafx.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\ExtObj.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_EXTOB=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\ResProp.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	
NODEP_CPP_EXTOB=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_EXTOB=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\ResProp.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	
NODEP_CPP_EXTOB=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_EXTOB=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\ResProp.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	
NODEP_CPP_EXTOB=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\PropList.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_PROPL=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_PROPL=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_PROPL=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\RegExt.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_REGEX=\
	".\SmbSmpEx\stdafx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atliface.h"\
	{$(INCLUDE)}"\clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_REGEX=\
	".\SmbSmpEx\stdafx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atliface.h"\
	{$(INCLUDE)}"\clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_REGEX=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\clusapi.h"\
	".\SmbSmpEx\RegExt.h"\
	".\SmbSmpEx\stdafx.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\ResProp.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_RESPR=\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\DDxDDv.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\ResProp.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atliface.h"\
	{$(INCLUDE)}"\CluAdmEx.h"\
	{$(INCLUDE)}"\clusapi.h"\
	
NODEP_CPP_RESPR=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_RESPR=\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\DDxDDv.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\ResProp.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atliface.h"\
	{$(INCLUDE)}"\CluAdmEx.h"\
	{$(INCLUDE)}"\clusapi.h"\
	
NODEP_CPP_RESPR=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_RESPR=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\CluAdmEx.h"\
	".\clusapi.h"\
	".\SmbSmpEx\BasePage.h"\
	".\SmbSmpEx\DDxDDv.h"\
	".\SmbSmpEx\ExtObj.h"\
	".\SmbSmpEx\PropList.h"\
	".\SmbSmpEx\ResProp.h"\
	".\SmbSmpEx\SmbSmpEx.h"\
	".\SmbSmpEx\stdafx.h"\
	
NODEP_CPP_RESPR=\
	".\SmbSmpEx\ExtObjID.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\SmbSmpEx\ExtObjID.h"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\StdAfx.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_STDAF=\
	".\SmbSmpEx\stdafx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atliface.h"\
	{$(INCLUDE)}"\clusapi.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "SmbSmpEx" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)/SmbSmpEx.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_STDAF=\
	".\SmbSmpEx\stdafx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atliface.h"\
	{$(INCLUDE)}"\clusapi.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "SmbSmpEx" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)/SmbSmpEx.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_STDAF=\
	".\atlbase.h"\
	".\atlcom.h"\
	".\SmbSmpEx\stdafx.h"\
	
# ADD CPP /Yc"stdafx.h"
BuildCmds= \
	$(CPP) /nologo /MDd /Gt0 /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)/SmbSmpEx.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmbSmpEx\ReadMe.txt

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
