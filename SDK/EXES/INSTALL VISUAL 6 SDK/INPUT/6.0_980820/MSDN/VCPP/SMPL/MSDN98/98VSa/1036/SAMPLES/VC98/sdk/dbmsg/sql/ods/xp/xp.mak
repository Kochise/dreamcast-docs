# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (MIPS) Dynamic-Link Library" 0x0502
# TARGTYPE "Win32 (PPC) Dynamic-Link Library" 0x0702
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

!IF "$(CFG)" == ""
CFG=xp - Win32 (PPC) Debug
!MESSAGE No configuration specified.  Defaulting to xp - Win32 (PPC) Debug.
!ENDIF 

!IF "$(CFG)" != "xp - Win32 Release" && "$(CFG)" != "xp - Win32 Debug" &&\
 "$(CFG)" != "xp - Win32 (ALPHA) Debug" && "$(CFG)" !=\
 "xp - Win32 (ALPHA) Release" && "$(CFG)" != "xp - Win32 MIPS Debug" && "$(CFG)"\
 != "xp - Win32 MIPS Release" && "$(CFG)" != "xp - Win32 (PPC) Debug" &&\
 "$(CFG)" != "xp - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "xp.mak" CFG="xp - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xp - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "xp - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "xp - Win32 MIPS Debug" (based on "Win32 (MIPS) Dynamic-Link Library")
!MESSAGE "xp - Win32 MIPS Release" (based on\
 "Win32 (MIPS) Dynamic-Link Library")
!MESSAGE "xp - Win32 (PPC) Debug" (based on "Win32 (PPC) Dynamic-Link Library")
!MESSAGE "xp - Win32 (PPC) Release" (based on\
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
# PROP Target_Last_Scanned "xp - Win32 Debug"

!IF  "$(CFG)" == "xp - Win32 Release"

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

ALL : "$(OUTDIR)\xp.dll"

CLEAN : 
	-@erase ".\Release\xp.dll"
	-@erase ".\Release\XP.OBJ"
	-@erase ".\Release\xp.lib"
	-@erase ".\Release\xp.exp"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp.pch" /YX /Fo"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/xp.pdb" /machine:I386 /def:".\XP.DEF" /out:"$(OUTDIR)/xp.dll"\
 /implib:"$(OUTDIR)/xp.lib" 
DEF_FILE= \
	".\XP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/XP.OBJ"

"$(OUTDIR)\xp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp - Win32 Debug"

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

ALL : "$(OUTDIR)\xp.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\xp.dll"
	-@erase ".\Debug\XP.OBJ"
	-@erase ".\Debug\xp.ilk"
	-@erase ".\Debug\xp.lib"
	-@erase ".\Debug\xp.exp"
	-@erase ".\Debug\xp.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/xp.pdb" /debug /machine:I386 /def:".\XP.DEF"\
 /out:"$(OUTDIR)/xp.dll" /implib:"$(OUTDIR)/xp.lib" 
DEF_FILE= \
	".\XP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/XP.OBJ"

"$(OUTDIR)\xp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xp___Win"
# PROP BASE Intermediate_Dir "xp___Win"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "xp___Win"
# PROP Intermediate_Dir "xp___Win"
# PROP Target_Dir ""
OUTDIR=.\xp___Win
INTDIR=.\xp___Win

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp.dll"

CLEAN : 
	-@erase ".\xp___Win\vc40.pdb"
	-@erase ".\xp___Win\xp.dll"
	-@erase ".\xp___Win\XP.OBJ"
	-@erase ".\xp___Win\xp.ilk"
	-@erase ".\xp___Win\xp.lib"
	-@erase ".\xp___Win\xp.exp"
	-@erase ".\xp___Win\xp.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\xp___Win/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/xp.pdb" /debug /machine:ALPHA /def:".\XP.DEF"\
 /out:"$(OUTDIR)/xp.dll" /implib:"$(OUTDIR)/xp.lib" 
DEF_FILE= \
	".\XP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/XP.OBJ"

"$(OUTDIR)\xp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "xp___Wi0"
# PROP BASE Intermediate_Dir "xp___Wi0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "xp___Wi0"
# PROP Intermediate_Dir "xp___Wi0"
# PROP Target_Dir ""
OUTDIR=.\xp___Wi0
INTDIR=.\xp___Wi0

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp.dll"

CLEAN : 
	-@erase ".\xp___Wi0\xp.dll"
	-@erase ".\xp___Wi0\XP.OBJ"
	-@erase ".\xp___Wi0\xp.lib"
	-@erase ".\xp___Wi0\xp.exp"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\xp___Wi0/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/xp.pdb" /machine:ALPHA /def:".\XP.DEF" /out:"$(OUTDIR)/xp.dll"\
 /implib:"$(OUTDIR)/xp.lib" 
DEF_FILE= \
	".\XP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/XP.OBJ"

"$(OUTDIR)\xp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp - Win32 MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xp___Wi1"
# PROP BASE Intermediate_Dir "xp___Wi1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "xp___Wi1"
# PROP Intermediate_Dir "xp___Wi1"
# PROP Target_Dir ""
OUTDIR=.\xp___Wi1
INTDIR=.\xp___Wi1

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp.dll"

CLEAN : 
	-@erase ".\xp___Wi1\vc40.pdb"
	-@erase ".\xp___Wi1\xp.dll"
	-@erase ".\xp___Wi1\XP.OBJ"
	-@erase ".\xp___Wi1\xp.ilk"
	-@erase ".\xp___Wi1\xp.lib"
	-@erase ".\xp___Wi1\xp.exp"
	-@erase ".\xp___Wi1\xp.pdb"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/xp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\xp___Wi1/
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /debug /machine:MIPS
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/xp.pdb" /debug /machine:MIPS /def:".\XP.DEF"\
 /out:"$(OUTDIR)/xp.dll" /implib:"$(OUTDIR)/xp.lib" 
DEF_FILE= \
	".\XP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/XP.OBJ"

"$(OUTDIR)\xp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "xp - Win32 MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "xp___Wi2"
# PROP BASE Intermediate_Dir "xp___Wi2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "xp___Wi2"
# PROP Intermediate_Dir "xp___Wi2"
# PROP Target_Dir ""
OUTDIR=.\xp___Wi2
INTDIR=.\xp___Wi2

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\xp.dll"

CLEAN : 
	-@erase ".\xp___Wi2\xp.dll"
	-@erase ".\xp___Wi2\XP.OBJ"
	-@erase ".\xp___Wi2\xp.lib"
	-@erase ".\xp___Wi2\xp.exp"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/xp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\xp___Wi2/
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /machine:MIPS
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/xp.pdb" /machine:MIPS /def:".\XP.DEF" /out:"$(OUTDIR)/xp.dll"\
 /implib:"$(OUTDIR)/xp.lib" 
DEF_FILE= \
	".\XP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/XP.OBJ"

"$(OUTDIR)\xp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "xp - Win32 (PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xp___Wi3"
# PROP BASE Intermediate_Dir "xp___Wi3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "xp___Wi3"
# PROP Intermediate_Dir "xp___Wi3"
# PROP Target_Dir ""
OUTDIR=.\xp___Wi3
INTDIR=.\xp___Wi3

ALL : "$(OUTDIR)\xp.dll"

CLEAN : 
	-@erase ".\xp___Wi3\vc40.pdb"
	-@erase ".\xp___Wi3\xp.dll"
	-@erase ".\xp___Wi3\XP.OBJ"
	-@erase ".\xp___Wi3\xp.lib"
	-@erase ".\xp___Wi3\xp.exp"
	-@erase ".\xp___Wi3\xp.pdb"

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
 /Fp"$(INTDIR)/xp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\xp___Wi3/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:windows /dll\
 /pdb:"$(OUTDIR)/xp.pdb" /debug /machine:PPC /def:".\XP.DEF"\
 /out:"$(OUTDIR)/xp.dll" /implib:"$(OUTDIR)/xp.lib" 
DEF_FILE= \
	".\XP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/XP.OBJ"

"$(OUTDIR)\xp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp - Win32 (PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "xp___Wi4"
# PROP BASE Intermediate_Dir "xp___Wi4"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "xp___Wi4"
# PROP Intermediate_Dir "xp___Wi4"
# PROP Target_Dir ""
OUTDIR=.\xp___Wi4
INTDIR=.\xp___Wi4

ALL : "$(OUTDIR)\xp.dll"

CLEAN : 
	-@erase ".\xp___Wi4\xp.dll"
	-@erase ".\xp___Wi4\XP.OBJ"
	-@erase ".\xp___Wi4\xp.lib"
	-@erase ".\xp___Wi4\xp.exp"

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
 /Fp"$(INTDIR)/xp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\xp___Wi4/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:windows /dll /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:windows /dll\
 /pdb:"$(OUTDIR)/xp.pdb" /machine:PPC /def:".\XP.DEF" /out:"$(OUTDIR)/xp.dll"\
 /implib:"$(OUTDIR)/xp.lib" 
DEF_FILE= \
	".\XP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/XP.OBJ"

"$(OUTDIR)\xp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "xp - Win32 Release"
# Name "xp - Win32 Debug"
# Name "xp - Win32 (ALPHA) Debug"
# Name "xp - Win32 (ALPHA) Release"
# Name "xp - Win32 MIPS Debug"
# Name "xp - Win32 MIPS Release"
# Name "xp - Win32 (PPC) Debug"
# Name "xp - Win32 (PPC) Release"

!IF  "$(CFG)" == "xp - Win32 Release"

!ELSEIF  "$(CFG)" == "xp - Win32 Debug"

!ELSEIF  "$(CFG)" == "xp - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "xp - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "xp - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "xp - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "xp - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "xp - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\XP.C

!IF  "$(CFG)" == "xp - Win32 Release"

"$(INTDIR)\XP.OBJ" : $(SOURCE) $(DEP_CPP_XP_C0) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp - Win32 Debug"

"$(INTDIR)\XP.OBJ" : $(SOURCE) $(DEP_CPP_XP_C0) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp - Win32 (ALPHA) Debug"

"$(INTDIR)\XP.OBJ" : $(SOURCE) $(DEP_CPP_XP_C0) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp - Win32 (ALPHA) Release"

"$(INTDIR)\XP.OBJ" : $(SOURCE) $(DEP_CPP_XP_C0) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp - Win32 MIPS Debug"

"$(INTDIR)\XP.OBJ" : $(SOURCE) $(DEP_CPP_XP_C0) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp - Win32 MIPS Release"

"$(INTDIR)\XP.OBJ" : $(SOURCE) $(DEP_CPP_XP_C0) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "xp - Win32 (PPC) Debug"

"$(INTDIR)\XP.OBJ" : $(SOURCE) $(DEP_CPP_XP_C0) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "xp - Win32 (PPC) Release"

"$(INTDIR)\XP.OBJ" : $(SOURCE) $(DEP_CPP_XP_C0) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XP.DEF

!IF  "$(CFG)" == "xp - Win32 Release"

!ELSEIF  "$(CFG)" == "xp - Win32 Debug"

!ELSEIF  "$(CFG)" == "xp - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "xp - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "xp - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "xp - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "xp - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "xp - Win32 (PPC) Release"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
