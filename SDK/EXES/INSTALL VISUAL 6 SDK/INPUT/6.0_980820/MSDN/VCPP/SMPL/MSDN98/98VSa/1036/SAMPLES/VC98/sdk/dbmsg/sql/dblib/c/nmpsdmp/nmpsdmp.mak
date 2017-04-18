# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (MIPS) Console Application" 0x0503
# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603
# TARGTYPE "Win32 (PPC) Console Application" 0x0703

!IF "$(CFG)" == ""
CFG=Nmpsdmp - Win32 (PPC) Debug
!MESSAGE No configuration specified.  Defaulting to Nmpsdmp - Win32 (PPC)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "Nmpsdmp - Win32 Release" && "$(CFG)" !=\
 "Nmpsdmp - Win32 Debug" && "$(CFG)" != "Nmpsdmp - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "Nmpsdmp - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "Nmpsdmp - Win32 MIPS Debug" && "$(CFG)" != "Nmpsdmp - Win32 MIPS Release" &&\
 "$(CFG)" != "Nmpsdmp - Win32 (PPC) Debug" && "$(CFG)" !=\
 "Nmpsdmp - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Nmpsdmp.mak" CFG="Nmpsdmp - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Nmpsdmp - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Nmpsdmp - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Nmpsdmp - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Nmpsdmp - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Nmpsdmp - Win32 MIPS Debug" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Nmpsdmp - Win32 MIPS Release" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Nmpsdmp - Win32 (PPC) Debug" (based on\
 "Win32 (PPC) Console Application")
!MESSAGE "Nmpsdmp - Win32 (PPC) Release" (based on\
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
# PROP Target_Last_Scanned "Nmpsdmp - Win32 Debug"

!IF  "$(CFG)" == "Nmpsdmp - Win32 Release"

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

ALL : "$(OUTDIR)\Nmpsdmp.exe"

CLEAN : 
	-@erase ".\Release\Nmpsdmp.exe"
	-@erase ".\Release\Nmpsdmp.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Nmpsdmp.pch" /YX /Fo"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Nmpsdmp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Nmpsdmp.pdb" /machine:I386 /out:"$(OUTDIR)/Nmpsdmp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Nmpsdmp.obj"

"$(OUTDIR)\Nmpsdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 Debug"

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

ALL : "$(OUTDIR)\Nmpsdmp.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Nmpsdmp.exe"
	-@erase ".\Debug\Nmpsdmp.obj"
	-@erase ".\Debug\Nmpsdmp.ilk"
	-@erase ".\Debug\Nmpsdmp.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Nmpsdmp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Nmpsdmp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Nmpsdmp.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Nmpsdmp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Nmpsdmp.obj"

"$(OUTDIR)\Nmpsdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Nmpsdmp_"
# PROP BASE Intermediate_Dir "Nmpsdmp_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Nmpsdmp_"
# PROP Intermediate_Dir "Nmpsdmp_"
# PROP Target_Dir ""
OUTDIR=.\Nmpsdmp_
INTDIR=.\Nmpsdmp_

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Nmpsdmp.exe"

CLEAN : 
	-@erase ".\Nmpsdmp_\vc40.pdb"
	-@erase ".\Nmpsdmp_\Nmpsdmp.exe"
	-@erase ".\Nmpsdmp_\Nmpsdmp.obj"
	-@erase ".\Nmpsdmp_\Nmpsdmp.ilk"
	-@erase ".\Nmpsdmp_\Nmpsdmp.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Nmpsdmp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Nmpsdmp_/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Nmpsdmp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Nmpsdmp.pdb" /debug /machine:ALPHA /out:"$(OUTDIR)/Nmpsdmp.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)/Nmpsdmp.obj"

"$(OUTDIR)\Nmpsdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Nmpsdmp0"
# PROP BASE Intermediate_Dir "Nmpsdmp0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Nmpsdmp0"
# PROP Intermediate_Dir "Nmpsdmp0"
# PROP Target_Dir ""
OUTDIR=.\Nmpsdmp0
INTDIR=.\Nmpsdmp0

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Nmpsdmp.exe"

CLEAN : 
	-@erase ".\Nmpsdmp0\Nmpsdmp.exe"
	-@erase ".\Nmpsdmp0\Nmpsdmp.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Nmpsdmp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Nmpsdmp0/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Nmpsdmp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Nmpsdmp.pdb" /machine:ALPHA /out:"$(OUTDIR)/Nmpsdmp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Nmpsdmp.obj"

"$(OUTDIR)\Nmpsdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Nmpsdmp1"
# PROP BASE Intermediate_Dir "Nmpsdmp1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Nmpsdmp1"
# PROP Intermediate_Dir "Nmpsdmp1"
# PROP Target_Dir ""
OUTDIR=.\Nmpsdmp1
INTDIR=.\Nmpsdmp1

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Nmpsdmp.exe"

CLEAN : 
	-@erase ".\Nmpsdmp1\vc40.pdb"
	-@erase ".\Nmpsdmp1\Nmpsdmp.exe"
	-@erase ".\Nmpsdmp1\Nmpsdmp.obj"
	-@erase ".\Nmpsdmp1\Nmpsdmp.ilk"
	-@erase ".\Nmpsdmp1\Nmpsdmp.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/Nmpsdmp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Nmpsdmp1/
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
 /pdb:"$(OUTDIR)/Nmpsdmp.pdb" /debug /machine:MIPS /out:"$(OUTDIR)/Nmpsdmp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Nmpsdmp.obj"

"$(OUTDIR)\Nmpsdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Nmpsdmp.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Nmpsdmp2"
# PROP BASE Intermediate_Dir "Nmpsdmp2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Nmpsdmp2"
# PROP Intermediate_Dir "Nmpsdmp2"
# PROP Target_Dir ""
OUTDIR=.\Nmpsdmp2
INTDIR=.\Nmpsdmp2

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Nmpsdmp.exe"

CLEAN : 
	-@erase ".\Nmpsdmp2\Nmpsdmp.exe"
	-@erase ".\Nmpsdmp2\Nmpsdmp.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/Nmpsdmp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Nmpsdmp2/
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
 /pdb:"$(OUTDIR)/Nmpsdmp.pdb" /machine:MIPS /out:"$(OUTDIR)/Nmpsdmp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Nmpsdmp.obj"

"$(OUTDIR)\Nmpsdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Nmpsdmp.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Nmpsdmp3"
# PROP BASE Intermediate_Dir "Nmpsdmp3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Nmpsdmp3"
# PROP Intermediate_Dir "Nmpsdmp3"
# PROP Target_Dir ""
OUTDIR=.\Nmpsdmp3
INTDIR=.\Nmpsdmp3

ALL : "$(OUTDIR)\Nmpsdmp.exe"

CLEAN : 
	-@erase ".\Nmpsdmp3\vc40.pdb"
	-@erase ".\Nmpsdmp3\Nmpsdmp.exe"
	-@erase ".\Nmpsdmp3\Nmpsdmp.obj"
	-@erase ".\Nmpsdmp3\Nmpsdmp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Nmpsdmp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Nmpsdmp3/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Nmpsdmp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/Nmpsdmp.pdb" /debug /machine:PPC /out:"$(OUTDIR)/Nmpsdmp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Nmpsdmp.obj"

"$(OUTDIR)\Nmpsdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Nmpsdmp4"
# PROP BASE Intermediate_Dir "Nmpsdmp4"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Nmpsdmp4"
# PROP Intermediate_Dir "Nmpsdmp4"
# PROP Target_Dir ""
OUTDIR=.\Nmpsdmp4
INTDIR=.\Nmpsdmp4

ALL : "$(OUTDIR)\Nmpsdmp.exe"

CLEAN : 
	-@erase ".\Nmpsdmp4\Nmpsdmp.exe"
	-@erase ".\Nmpsdmp4\Nmpsdmp.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Nmpsdmp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Nmpsdmp4/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Nmpsdmp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/Nmpsdmp.pdb" /machine:PPC /out:"$(OUTDIR)/Nmpsdmp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Nmpsdmp.obj"

"$(OUTDIR)\Nmpsdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "Nmpsdmp - Win32 Release"
# Name "Nmpsdmp - Win32 Debug"
# Name "Nmpsdmp - Win32 (ALPHA) Debug"
# Name "Nmpsdmp - Win32 (ALPHA) Release"
# Name "Nmpsdmp - Win32 MIPS Debug"
# Name "Nmpsdmp - Win32 MIPS Release"
# Name "Nmpsdmp - Win32 (PPC) Debug"
# Name "Nmpsdmp - Win32 (PPC) Release"

!IF  "$(CFG)" == "Nmpsdmp - Win32 Release"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 Debug"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Nmpsdmp.c

!IF  "$(CFG)" == "Nmpsdmp - Win32 Release"

"$(INTDIR)\Nmpsdmp.obj" : $(SOURCE) $(DEP_CPP_NMPSD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 Debug"

"$(INTDIR)\Nmpsdmp.obj" : $(SOURCE) $(DEP_CPP_NMPSD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (ALPHA) Debug"

"$(INTDIR)\Nmpsdmp.obj" : $(SOURCE) $(DEP_CPP_NMPSD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (ALPHA) Release"

"$(INTDIR)\Nmpsdmp.obj" : $(SOURCE) $(DEP_CPP_NMPSD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 MIPS Debug"

"$(INTDIR)\Nmpsdmp.obj" : $(SOURCE) $(DEP_CPP_NMPSD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 MIPS Release"

"$(INTDIR)\Nmpsdmp.obj" : $(SOURCE) $(DEP_CPP_NMPSD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (PPC) Debug"

"$(INTDIR)\Nmpsdmp.obj" : $(SOURCE) $(DEP_CPP_NMPSD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Nmpsdmp - Win32 (PPC) Release"

"$(INTDIR)\Nmpsdmp.obj" : $(SOURCE) $(DEP_CPP_NMPSD) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
