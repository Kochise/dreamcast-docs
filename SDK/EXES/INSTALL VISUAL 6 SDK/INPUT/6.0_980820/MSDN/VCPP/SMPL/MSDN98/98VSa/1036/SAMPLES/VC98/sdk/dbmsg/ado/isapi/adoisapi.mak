# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (PPC) Dynamic-Link Library" 0x0702
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

!IF "$(CFG)" == ""
CFG=adoisapi - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to adoisapi - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "adoisapi - Win32 Release" && "$(CFG)" !=\
 "adoisapi - Win32 Debug" && "$(CFG)" != "adoisapi - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "adoisapi - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "adoisapi - Win32 (PPC) Debug" && "$(CFG)" != "adoisapi - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "adoisapi.mak" CFG="adoisapi - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "adoisapi - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "adoisapi - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "adoisapi - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "adoisapi - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "adoisapi - Win32 (PPC) Debug" (based on\
 "Win32 (PPC) Dynamic-Link Library")
!MESSAGE "adoisapi - Win32 (PPC) Release" (based on\
 "Win32 (PPC) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "adoisapi - Win32 (ALPHA) Release"

!IF  "$(CFG)" == "adoisapi - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Retail"
# PROP Intermediate_Dir "Retail"
# PROP Target_Dir ""
OUTDIR=.\Retail
INTDIR=.\Retail

ALL : "$(OUTDIR)\adoisapi.dll" "$(OUTDIR)\adoisapi.bsc"

CLEAN : 
	-@erase "$(INTDIR)\adoisapi.obj"
	-@erase "$(INTDIR)\adoisapi.res"
	-@erase "$(INTDIR)\adoisapi.sbr"
	-@erase "$(OUTDIR)\adoisapi.bsc"
	-@erase "$(OUTDIR)\adoisapi.dll"
	-@erase "$(OUTDIR)\adoisapi.exp"
	-@erase "$(OUTDIR)\adoisapi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/adoisapi.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Retail/
CPP_SBRS=.\Retail/

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
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/adoisapi.res" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoisapi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\adoisapi.sbr"

"$(OUTDIR)\adoisapi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/adoisapi.pdb" /machine:I386 /def:".\adoisapi.def"\
 /out:"$(OUTDIR)/adoisapi.dll" /implib:"$(OUTDIR)/adoisapi.lib" 
DEF_FILE= \
	".\adoisapi.def"
LINK32_OBJS= \
	"$(INTDIR)\adoisapi.obj" \
	"$(INTDIR)\adoisapi.res"

"$(OUTDIR)\adoisapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoisapi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\adoisapi.dll" "$(OUTDIR)\adoisapi.bsc"

CLEAN : 
	-@erase "$(INTDIR)\adoisapi.obj"
	-@erase "$(INTDIR)\adoisapi.res"
	-@erase "$(INTDIR)\adoisapi.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\adoisapi.bsc"
	-@erase "$(OUTDIR)\adoisapi.dll"
	-@erase "$(OUTDIR)\adoisapi.exp"
	-@erase "$(OUTDIR)\adoisapi.ilk"
	-@erase "$(OUTDIR)\adoisapi.lib"
	-@erase "$(OUTDIR)\adoisapi.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/adoisapi.pch" /YX /Fo"$(INTDIR)/"\
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
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/adoisapi.res" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoisapi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\adoisapi.sbr"

"$(OUTDIR)\adoisapi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/adoisapi.pdb" /debug /machine:I386 /def:".\adoisapi.def"\
 /out:"$(OUTDIR)/adoisapi.dll" /implib:"$(OUTDIR)/adoisapi.lib" 
DEF_FILE= \
	".\adoisapi.def"
LINK32_OBJS= \
	"$(INTDIR)\adoisapi.obj" \
	"$(INTDIR)\adoisapi.res"

"$(OUTDIR)\adoisapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "adoisapi"
# PROP BASE Intermediate_Dir "adoisapi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "adoisapi"
# PROP Intermediate_Dir "adoisapi"
# PROP Target_Dir ""
OUTDIR=.\adoisapi
INTDIR=.\adoisapi

ALL :   "$(OUTDIR)\adoisapi.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/adoisapi.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\adoisapi/
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
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoisapi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/adoisapi.pdb" /debug /machine:ALPHA /def:".\adoisapi.def"\
 /out:"$(OUTDIR)/adoisapi.dll" /implib:"$(OUTDIR)/adoisapi.lib" 
DEF_FILE= \
	".\adoisapi.def"
LINK32_OBJS= \
	"$(INTDIR)\adoisapi.obj"

"$(OUTDIR)\adoisapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "daoisap0"
# PROP BASE Intermediate_Dir "daoisap0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "daoisap0"
# PROP Intermediate_Dir "daoisap0"
# PROP Target_Dir ""
OUTDIR=.\daoisap0
INTDIR=.\daoisap0

ALL :   "$(OUTDIR)\adoisapi.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/adoisapi.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\daoisap0/
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
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoisapi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/adoisapi.pdb" /machine:ALPHA /def:".\adoisapi.def"\
 /out:"$(OUTDIR)/adoisapi.dll" /implib:"$(OUTDIR)/adoisapi.lib" 
DEF_FILE= \
	".\adoisapi.def"
LINK32_OBJS= \
	"$(INTDIR)\adoisapi.obj"

"$(OUTDIR)\adoisapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "daoisap1"
# PROP BASE Intermediate_Dir "daoisap1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
OUTDIR=.\debug
INTDIR=.\debug

ALL :  "$(OUTDIR)\adoisapi.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /PPC32
# ADD MTL /nologo /D "_DEBUG" /PPC32
MTL_PROJ=/nologo /D "_DEBUG" /PPC32 
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/adoisapi.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoisapi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /dll /pdb:"$(OUTDIR)/adoisapi.pdb" /debug /machine:PPC\
 /def:".\adoisapi.def" /out:"$(OUTDIR)/adoisapi.dll"\
 /implib:"$(OUTDIR)/adoisapi.lib" 
DEF_FILE= \
	".\adoisapi.def"
LINK32_OBJS= \
	"$(INTDIR)\adoisapi.obj"

"$(OUTDIR)\adoisapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "daoisap2"
# PROP BASE Intermediate_Dir "daoisap2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Target_Dir ""
OUTDIR=.\retail
INTDIR=.\retail

ALL :  "$(OUTDIR)\adoisapi.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /PPC32
# ADD MTL /nologo /D "NDEBUG" /PPC32
MTL_PROJ=/nologo /D "NDEBUG" /PPC32 
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/adoisapi.pch" /YX /Fo"$(INTDIR)/" /c 
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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoisapi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /dll /pdb:"$(OUTDIR)/adoisapi.pdb" /machine:PPC\
 /def:".\adoisapi.def" /out:"$(OUTDIR)/adoisapi.dll"\
 /implib:"$(OUTDIR)/adoisapi.lib" 
DEF_FILE= \
	".\adoisapi.def"
LINK32_OBJS= \
	"$(INTDIR)\adoisapi.obj"

"$(OUTDIR)\adoisapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "adoisapi - Win32 Release"
# Name "adoisapi - Win32 Debug"
# Name "adoisapi - Win32 (ALPHA) Debug"
# Name "adoisapi - Win32 (ALPHA) Release"
# Name "adoisapi - Win32 (PPC) Debug"
# Name "adoisapi - Win32 (PPC) Release"

!IF  "$(CFG)" == "adoisapi - Win32 Release"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 Debug"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\adoisapi.def

!IF  "$(CFG)" == "adoisapi - Win32 Release"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 Debug"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\adoisapi.cpp

!IF  "$(CFG)" == "adoisapi - Win32 Release"


"$(INTDIR)\adoisapi.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\adoisapi.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "adoisapi - Win32 Debug"

DEP_CPP_ADOIS=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\adoisapi.obj" : $(SOURCE) $(DEP_CPP_ADOIS) "$(INTDIR)"

"$(INTDIR)\adoisapi.sbr" : $(SOURCE) $(DEP_CPP_ADOIS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Debug"

DEP_CPP_ADOIS=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	{$(INCLUDE)}"\httpext.h"\
	

"$(INTDIR)\adoisapi.obj" : $(SOURCE) $(DEP_CPP_ADOIS) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Release"

DEP_CPP_ADOIS=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	{$(INCLUDE)}"\httpext.h"\
	

"$(INTDIR)\adoisapi.obj" : $(SOURCE) $(DEP_CPP_ADOIS) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Debug"

DEP_CPP_ADOIS=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	{$(INCLUDE)}"\httpext.h"\
	

"$(INTDIR)\adoisapi.obj" : $(SOURCE) $(DEP_CPP_ADOIS) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Release"

DEP_CPP_ADOIS=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	{$(INCLUDE)}"\httpext.h"\
	

"$(INTDIR)\adoisapi.obj" : $(SOURCE) $(DEP_CPP_ADOIS) "$(INTDIR)"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\adoisapi.rc

!IF  "$(CFG)" == "adoisapi - Win32 Release"


"$(INTDIR)\adoisapi.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "adoisapi - Win32 Debug"


"$(INTDIR)\adoisapi.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "adoisapi - Win32 (PPC) Release"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
