# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (MIPS) Dynamic-Link Library" 0x0502
# TARGTYPE "Win32 (PPC) Dynamic-Link Library" 0x0702
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

!IF "$(CFG)" == ""
CFG=xp_dblib - Win32 (PPC) Debug
!MESSAGE No configuration specified.  Defaulting to xp_dblib - Win32 (PPC)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "xp_dblib - Win32 Release" && "$(CFG)" !=\
 "xp_dblib - Win32 Debug" && "$(CFG)" != "xp_dblib - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "xp_dblib - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "xp_dblib - Win32 MIPS Debug" && "$(CFG)" != "xp_dblib - Win32 MIPS Release" &&\
 "$(CFG)" != "xp_dblib - Win32 (PPC) Debug" && "$(CFG)" !=\
 "xp_dblib - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "xp_dblib.mak" CFG="xp_dblib - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xp_dblib - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xp_dblib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xp_dblib - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "xp_dblib - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "xp_dblib - Win32 MIPS Debug" (based on\
 "Win32 (MIPS) Dynamic-Link Library")
!MESSAGE "xp_dblib - Win32 MIPS Release" (based on\
 "Win32 (MIPS) Dynamic-Link Library")
!MESSAGE "xp_dblib - Win32 (PPC) Debug" (based on\
 "Win32 (PPC) Dynamic-Link Library")
!MESSAGE "xp_dblib - Win32 (PPC) Release" (based on\
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

!IF  "$(CFG)" == "xp_dblib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp_dblib.dll"

CLEAN : 
	-@erase ".\Release\xp_dblib.dll"
	-@erase ".\Release\xp_dblib.obj"
	-@erase ".\Release\xp_dblib.lib"
	-@erase ".\Release\xp_dblib.exp"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp_dblib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=

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
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_dblib.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/xp_dblib.pdb" /machine:I386\
 /def:".\XP_DBLIB.DEF" /out:"$(OUTDIR)/xp_dblib.dll"\
 /implib:"$(OUTDIR)/xp_dblib.lib" 
DEF_FILE= \
	".\XP_DBLIB.DEF"
LINK32_OBJS= \
	"$(INTDIR)/xp_dblib.obj"

"$(OUTDIR)\xp_dblib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 Debug"

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

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp_dblib.dll"

CLEAN : 
	-@erase ".\Debug\xp_dblib.dll"
	-@erase ".\Debug\xp_dblib.obj"
	-@erase ".\Debug\xp_dblib.ilk"
	-@erase ".\Debug\xp_dblib.lib"
	-@erase ".\Debug\xp_dblib.exp"
	-@erase ".\Debug\xp_dblib.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp_dblib.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=

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
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_dblib.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/xp_dblib.pdb" /debug /machine:I386\
 /def:".\XP_DBLIB.DEF" /out:"$(OUTDIR)/xp_dblib.dll"\
 /implib:"$(OUTDIR)/xp_dblib.lib" 
DEF_FILE= \
	".\XP_DBLIB.DEF"
LINK32_OBJS= \
	"$(INTDIR)/xp_dblib.obj"

"$(OUTDIR)\xp_dblib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xp_dblib"
# PROP BASE Intermediate_Dir "xp_dblib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "xp_dblib"
# PROP Intermediate_Dir "xp_dblib"
# PROP Target_Dir ""
OUTDIR=.\xp_dblib
INTDIR=.\xp_dblib

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp_dblib.dll"

CLEAN : 
	-@erase ".\xp_dblib\vc40.pdb"
	-@erase ".\xp_dblib\xp_dblib.dll"
	-@erase ".\xp_dblib\xp_dblib.obj"
	-@erase ".\xp_dblib\xp_dblib.ilk"
	-@erase ".\xp_dblib\xp_dblib.lib"
	-@erase ".\xp_dblib\xp_dblib.exp"
	-@erase ".\xp_dblib\xp_dblib.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp_dblib.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\xp_dblib/
CPP_SBRS=

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_dblib.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib opends60.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib opends60.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/xp_dblib.pdb" /debug /machine:ALPHA\
 /def:".\XP_DBLIB.DEF" /out:"$(OUTDIR)/xp_dblib.dll"\
 /implib:"$(OUTDIR)/xp_dblib.lib" 
DEF_FILE= \
	".\XP_DBLIB.DEF"
LINK32_OBJS= \
	"$(INTDIR)/xp_dblib.obj"

"$(OUTDIR)\xp_dblib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "xp_dbli0"
# PROP BASE Intermediate_Dir "xp_dbli0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "xp_dbli0"
# PROP Intermediate_Dir "xp_dbli0"
# PROP Target_Dir ""
OUTDIR=.\xp_dbli0
INTDIR=.\xp_dbli0

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp_dblib.dll"

CLEAN : 
	-@erase ".\xp_dbli0\xp_dblib.dll"
	-@erase ".\xp_dbli0\xp_dblib.obj"
	-@erase ".\xp_dbli0\xp_dblib.lib"
	-@erase ".\xp_dbli0\xp_dblib.exp"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp_dblib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\xp_dbli0/
CPP_SBRS=

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_dblib.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib opends60.lib /nologo /subsystem:windows /dll /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib opends60.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/xp_dblib.pdb" /machine:ALPHA\
 /def:".\XP_DBLIB.DEF" /out:"$(OUTDIR)/xp_dblib.dll"\
 /implib:"$(OUTDIR)/xp_dblib.lib" 
DEF_FILE= \
	".\XP_DBLIB.DEF"
LINK32_OBJS= \
	"$(INTDIR)/xp_dblib.obj"

"$(OUTDIR)\xp_dblib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xp_dbli1"
# PROP BASE Intermediate_Dir "xp_dbli1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "xp_dbli1"
# PROP Intermediate_Dir "xp_dbli1"
# PROP Target_Dir ""
OUTDIR=.\xp_dbli1
INTDIR=.\xp_dbli1

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp_dblib.dll"

CLEAN : 
	-@erase ".\xp_dbli1\vc40.pdb"
	-@erase ".\xp_dbli1\xp_dblib.dll"
	-@erase ".\xp_dbli1\xp_dblib.obj"
	-@erase ".\xp_dbli1\xp_dblib.ilk"
	-@erase ".\xp_dbli1\xp_dblib.lib"
	-@erase ".\xp_dbli1\xp_dblib.exp"
	-@erase ".\xp_dbli1\xp_dblib.pdb"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/xp_dblib.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\xp_dbli1/
CPP_SBRS=

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

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:MIPS
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib opends60.lib /nologo /subsystem:windows /dll /debug /machine:MIPS
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib opends60.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/xp_dblib.pdb" /debug /machine:MIPS\
 /def:".\XP_DBLIB.DEF" /out:"$(OUTDIR)/xp_dblib.dll"\
 /implib:"$(OUTDIR)/xp_dblib.lib" 
DEF_FILE= \
	".\XP_DBLIB.DEF"
LINK32_OBJS= \
	"$(INTDIR)/xp_dblib.obj"

"$(OUTDIR)\xp_dblib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_dblib.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "xp_dbli2"
# PROP BASE Intermediate_Dir "xp_dbli2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "xp_dbli2"
# PROP Intermediate_Dir "xp_dbli2"
# PROP Target_Dir ""
OUTDIR=.\xp_dbli2
INTDIR=.\xp_dbli2

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp_dblib.dll"

CLEAN : 
	-@erase ".\xp_dbli2\xp_dblib.dll"
	-@erase ".\xp_dbli2\xp_dblib.obj"
	-@erase ".\xp_dbli2\xp_dblib.lib"
	-@erase ".\xp_dbli2\xp_dblib.exp"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/xp_dblib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\xp_dbli2/
CPP_SBRS=

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

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:MIPS
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib opends60.lib /nologo /subsystem:windows /dll /machine:MIPS
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib opends60.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/xp_dblib.pdb" /machine:MIPS\
 /def:".\XP_DBLIB.DEF" /out:"$(OUTDIR)/xp_dblib.dll"\
 /implib:"$(OUTDIR)/xp_dblib.lib" 
DEF_FILE= \
	".\XP_DBLIB.DEF"
LINK32_OBJS= \
	"$(INTDIR)/xp_dblib.obj"

"$(OUTDIR)\xp_dblib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_dblib.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xp_dbli3"
# PROP BASE Intermediate_Dir "xp_dbli3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "xp_dbli3"
# PROP Intermediate_Dir "xp_dbli3"
# PROP Target_Dir ""
OUTDIR=.\xp_dbli3
INTDIR=.\xp_dbli3

ALL : "$(OUTDIR)\xp_dblib.dll"

CLEAN : 
	-@erase ".\xp_dbli3\vc40.pdb"
	-@erase ".\xp_dbli3\xp_dblib.dll"
	-@erase ".\xp_dbli3\xp_dblib.obj"
	-@erase ".\xp_dbli3\xp_dblib.lib"
	-@erase ".\xp_dbli3\xp_dblib.exp"
	-@erase ".\xp_dbli3\xp_dblib.pdb"

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
 /Fp"$(INTDIR)/xp_dblib.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\xp_dbli3/
CPP_SBRS=

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
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_dblib.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:windows /dll /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:windows /dll\
 /pdb:"$(OUTDIR)/xp_dblib.pdb" /debug /machine:PPC /def:".\XP_DBLIB.DEF"\
 /out:"$(OUTDIR)/xp_dblib.dll" /implib:"$(OUTDIR)/xp_dblib.lib" 
DEF_FILE= \
	".\XP_DBLIB.DEF"
LINK32_OBJS= \
	"$(INTDIR)/xp_dblib.obj"

"$(OUTDIR)\xp_dblib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "xp_dbli4"
# PROP BASE Intermediate_Dir "xp_dbli4"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "xp_dbli4"
# PROP Intermediate_Dir "xp_dbli4"
# PROP Target_Dir ""
OUTDIR=.\xp_dbli4
INTDIR=.\xp_dbli4

ALL : "$(OUTDIR)\xp_dblib.dll"

CLEAN : 
	-@erase ".\xp_dbli4\xp_dblib.dll"
	-@erase ".\xp_dbli4\xp_dblib.obj"
	-@erase ".\xp_dbli4\xp_dblib.lib"
	-@erase ".\xp_dbli4\xp_dblib.exp"

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
 /Fp"$(INTDIR)/xp_dblib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\xp_dbli4/
CPP_SBRS=

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
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_dblib.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:windows /dll /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:windows /dll\
 /pdb:"$(OUTDIR)/xp_dblib.pdb" /machine:PPC /def:".\XP_DBLIB.DEF"\
 /out:"$(OUTDIR)/xp_dblib.dll" /implib:"$(OUTDIR)/xp_dblib.lib" 
DEF_FILE= \
	".\XP_DBLIB.DEF"
LINK32_OBJS= \
	"$(INTDIR)/xp_dblib.obj"

"$(OUTDIR)\xp_dblib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "xp_dblib - Win32 Release"
# Name "xp_dblib - Win32 Debug"
# Name "xp_dblib - Win32 (ALPHA) Debug"
# Name "xp_dblib - Win32 (ALPHA) Release"
# Name "xp_dblib - Win32 MIPS Debug"
# Name "xp_dblib - Win32 MIPS Release"
# Name "xp_dblib - Win32 (PPC) Debug"
# Name "xp_dblib - Win32 (PPC) Release"

!IF  "$(CFG)" == "xp_dblib - Win32 Release"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 Debug"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\xp_dblib.c

!IF  "$(CFG)" == "xp_dblib - Win32 Release"

"$(INTDIR)\xp_dblib.obj" : $(SOURCE) $(DEP_CPP_XP_DB) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 Debug"

"$(INTDIR)\xp_dblib.obj" : $(SOURCE) $(DEP_CPP_XP_DB) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (ALPHA) Debug"

"$(INTDIR)\xp_dblib.obj" : $(SOURCE) $(DEP_CPP_XP_DB) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (ALPHA) Release"

"$(INTDIR)\xp_dblib.obj" : $(SOURCE) $(DEP_CPP_XP_DB) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 MIPS Debug"

"$(INTDIR)\xp_dblib.obj" : $(SOURCE) $(DEP_CPP_XP_DB) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 MIPS Release"

"$(INTDIR)\xp_dblib.obj" : $(SOURCE) $(DEP_CPP_XP_DB) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (PPC) Debug"

"$(INTDIR)\xp_dblib.obj" : $(SOURCE) $(DEP_CPP_XP_DB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (PPC) Release"

"$(INTDIR)\xp_dblib.obj" : $(SOURCE) $(DEP_CPP_XP_DB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XP_DBLIB.DEF

!IF  "$(CFG)" == "xp_dblib - Win32 Release"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 Debug"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "xp_dblib - Win32 (PPC) Release"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
