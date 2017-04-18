# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (MIPS) Console Application" 0x0503
# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603
# TARGTYPE "Win32 (PPC) Console Application" 0x0703

!IF "$(CFG)" == ""
CFG=SQLTestC - Win32 (PPC) Debug
!MESSAGE No configuration specified.  Defaulting to SQLTestC - Win32 (PPC)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "SQLTestC - Win32 Release" && "$(CFG)" !=\
 "SQLTestC - Win32 Debug" && "$(CFG)" != "SQLTestC - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "SQLTestC - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "SQLTestC - Win32 MIPS Debug" && "$(CFG)" != "SQLTestC - Win32 MIPS Release" &&\
 "$(CFG)" != "SQLTestC - Win32 (PPC) Debug" && "$(CFG)" !=\
 "SQLTestC - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SQLTestC.mak" CFG="SQLTestC - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SQLTestC - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "SQLTestC - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "SQLTestC - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "SQLTestC - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "SQLTestC - Win32 MIPS Debug" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "SQLTestC - Win32 MIPS Release" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "SQLTestC - Win32 (PPC) Debug" (based on\
 "Win32 (PPC) Console Application")
!MESSAGE "SQLTestC - Win32 (PPC) Release" (based on\
 "Win32 (PPC) Console Application")
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
# PROP Target_Last_Scanned "SQLTestC - Win32 Release"

!IF  "$(CFG)" == "SQLTestC - Win32 Release"

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

ALL : "$(OUTDIR)\SQLTestC.exe"

CLEAN : 
	-@erase ".\Release\SQLTestC.exe"
	-@erase ".\Release\Sqltestc.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/SQLTestC.pch" /YX /Fo"$(INTDIR)/" /c 
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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestC.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/SQLTestC.pdb" /machine:I386 /out:"$(OUTDIR)/SQLTestC.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestc.obj"

"$(OUTDIR)\SQLTestC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 Debug"

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

ALL : "$(OUTDIR)\SQLTestC.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\SQLTestC.exe"
	-@erase ".\Debug\Sqltestc.obj"
	-@erase ".\Debug\SQLTestC.ilk"
	-@erase ".\Debug\SQLTestC.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/SQLTestC.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestC.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/SQLTestC.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/SQLTestC.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestc.obj"

"$(OUTDIR)\SQLTestC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SQLTestC"
# PROP BASE Intermediate_Dir "SQLTestC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SQLTestC"
# PROP Intermediate_Dir "SQLTestC"
# PROP Target_Dir ""
OUTDIR=.\SQLTestC
INTDIR=.\SQLTestC

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLTestC.exe"

CLEAN : 
	-@erase ".\SQLTestC\vc40.pdb"
	-@erase ".\SQLTestC\SQLTestC.exe"
	-@erase ".\SQLTestC\Sqltestc.obj"
	-@erase ".\SQLTestC\SQLTestC.ilk"
	-@erase ".\SQLTestC\SQLTestC.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/SQLTestC.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\SQLTestC/
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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestC.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/SQLTestC.pdb" /debug /machine:ALPHA\
 /out:"$(OUTDIR)/SQLTestC.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestc.obj"

"$(OUTDIR)\SQLTestC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SQLTest0"
# PROP BASE Intermediate_Dir "SQLTest0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SQLTest0"
# PROP Intermediate_Dir "SQLTest0"
# PROP Target_Dir ""
OUTDIR=.\SQLTest0
INTDIR=.\SQLTest0

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLTestC.exe"

CLEAN : 
	-@erase ".\SQLTest0\SQLTestC.exe"
	-@erase ".\SQLTest0\Sqltestc.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /Gt0 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/SQLTestC.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SQLTest0/
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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestC.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/SQLTestC.pdb" /machine:ALPHA /out:"$(OUTDIR)/SQLTestC.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestc.obj"

"$(OUTDIR)\SQLTestC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SQLTest1"
# PROP BASE Intermediate_Dir "SQLTest1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SQLTest1"
# PROP Intermediate_Dir "SQLTest1"
# PROP Target_Dir ""
OUTDIR=.\SQLTest1
INTDIR=.\SQLTest1

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLTestC.exe"

CLEAN : 
	-@erase ".\SQLTest1\vc40.pdb"
	-@erase ".\SQLTest1\SQLTestC.exe"
	-@erase ".\SQLTest1\Sqltestc.obj"
	-@erase ".\SQLTest1\SQLTestC.ilk"
	-@erase ".\SQLTest1\SQLTestC.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_CONSOLE" /Fp"$(INTDIR)/SQLTestC.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\SQLTest1/
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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:MIPS
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:MIPS
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/SQLTestC.pdb" /debug /machine:MIPS\
 /out:"$(OUTDIR)/SQLTestC.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestc.obj"

"$(OUTDIR)\SQLTestC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestC.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SQLTest2"
# PROP BASE Intermediate_Dir "SQLTest2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SQLTest2"
# PROP Intermediate_Dir "SQLTest2"
# PROP Target_Dir ""
OUTDIR=.\SQLTest2
INTDIR=.\SQLTest2

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLTestC.exe"

CLEAN : 
	-@erase ".\SQLTest2\SQLTestC.exe"
	-@erase ".\SQLTest2\Sqltestc.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /Gt0 /QMOb2000 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D\
 "_CONSOLE" /Fp"$(INTDIR)/SQLTestC.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SQLTest2/
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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:MIPS
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:MIPS
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/SQLTestC.pdb" /machine:MIPS /out:"$(OUTDIR)/SQLTestC.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestc.obj"

"$(OUTDIR)\SQLTestC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestC.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SQLTest3"
# PROP BASE Intermediate_Dir "SQLTest3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SQLTest3"
# PROP Intermediate_Dir "SQLTest3"
# PROP Target_Dir ""
OUTDIR=.\SQLTest3
INTDIR=.\SQLTest3

ALL : "$(OUTDIR)\SQLTestC.exe"

CLEAN : 
	-@erase ".\SQLTest3\vc40.pdb"
	-@erase ".\SQLTest3\SQLTestC.exe"
	-@erase ".\SQLTest3\Sqltestc.obj"
	-@erase ".\SQLTest3\SQLTestC.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/SQLTestC.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\SQLTest3/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestC.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/SQLTestC.pdb" /debug /machine:PPC /out:"$(OUTDIR)/SQLTestC.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestc.obj"

"$(OUTDIR)\SQLTestC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SQLTest4"
# PROP BASE Intermediate_Dir "SQLTest4"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SQLTest4"
# PROP Intermediate_Dir "SQLTest4"
# PROP Target_Dir ""
OUTDIR=.\SQLTest4
INTDIR=.\SQLTest4

ALL : "$(OUTDIR)\SQLTestC.exe"

CLEAN : 
	-@erase ".\SQLTest4\SQLTestC.exe"
	-@erase ".\SQLTest4\Sqltestc.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/SQLTestC.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SQLTest4/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestC.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/SQLTestC.pdb" /machine:PPC /out:"$(OUTDIR)/SQLTestC.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestc.obj"

"$(OUTDIR)\SQLTestC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "SQLTestC - Win32 Release"
# Name "SQLTestC - Win32 Debug"
# Name "SQLTestC - Win32 (ALPHA) Debug"
# Name "SQLTestC - Win32 (ALPHA) Release"
# Name "SQLTestC - Win32 MIPS Debug"
# Name "SQLTestC - Win32 MIPS Release"
# Name "SQLTestC - Win32 (PPC) Debug"
# Name "SQLTestC - Win32 (PPC) Release"

!IF  "$(CFG)" == "SQLTestC - Win32 Release"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 Debug"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Sqltestc.c

!IF  "$(CFG)" == "SQLTestC - Win32 Release"

"$(INTDIR)\Sqltestc.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 Debug"

"$(INTDIR)\Sqltestc.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (ALPHA) Debug"

"$(INTDIR)\Sqltestc.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (ALPHA) Release"

"$(INTDIR)\Sqltestc.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 MIPS Debug"

"$(INTDIR)\Sqltestc.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 MIPS Release"

"$(INTDIR)\Sqltestc.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (PPC) Debug"

"$(INTDIR)\Sqltestc.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SQLTestC - Win32 (PPC) Release"

"$(INTDIR)\Sqltestc.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
