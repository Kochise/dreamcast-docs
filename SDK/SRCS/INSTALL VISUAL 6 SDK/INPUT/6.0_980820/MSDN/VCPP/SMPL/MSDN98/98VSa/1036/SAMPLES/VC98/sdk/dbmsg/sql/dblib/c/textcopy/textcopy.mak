# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (MIPS) Console Application" 0x0503
# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603
# TARGTYPE "Win32 (PPC) Console Application" 0x0703

!IF "$(CFG)" == ""
CFG=Textcopy - Win32 (PPC) Debug
!MESSAGE No configuration specified.  Defaulting to Textcopy - Win32 (PPC)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "Textcopy - Win32 Release" && "$(CFG)" !=\
 "Textcopy - Win32 Debug" && "$(CFG)" != "Textcopy - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "Textcopy - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "Textcopy - Win32 MIPS Debug" && "$(CFG)" != "Textcopy - Win32 MIPS Release" &&\
 "$(CFG)" != "Textcopy - Win32 (PPC) Debug" && "$(CFG)" !=\
 "Textcopy - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Textcopy.mak" CFG="Textcopy - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Textcopy - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "Textcopy - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Textcopy - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Textcopy - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Textcopy - Win32 MIPS Debug" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Textcopy - Win32 MIPS Release" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Textcopy - Win32 (PPC) Debug" (based on\
 "Win32 (PPC) Console Application")
!MESSAGE "Textcopy - Win32 (PPC) Release" (based on\
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
# PROP Target_Last_Scanned "Textcopy - Win32 Debug"

!IF  "$(CFG)" == "Textcopy - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Textcopy.exe"

CLEAN : 
	-@erase ".\Release\Textcopy.exe"
	-@erase ".\Release\Getopt.obj"
	-@erase ".\Release\Textcopy.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)/Textcopy.pch" /YX /Fo"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Textcopy.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 nafxcw.lib libcmt.lib ntwdblib.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=nafxcw.lib libcmt.lib ntwdblib.lib /nologo /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/Textcopy.pdb" /machine:I386\
 /out:"$(OUTDIR)/Textcopy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Getopt.obj" \
	"$(INTDIR)/Textcopy.obj"

"$(OUTDIR)\Textcopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Textcopy - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Textcopy.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Textcopy.exe"
	-@erase ".\Debug\Textcopy.obj"
	-@erase ".\Debug\Getopt.obj"
	-@erase ".\Debug\Textcopy.ilk"
	-@erase ".\Debug\Textcopy.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /D "_MBCS" /Fp"$(INTDIR)/Textcopy.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Textcopy.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 nafxcwd.lib libcmtd.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=nafxcwd.lib libcmtd.lib ntwdblib.lib /nologo /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)/Textcopy.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Textcopy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Textcopy.obj" \
	"$(INTDIR)/Getopt.obj"

"$(OUTDIR)\Textcopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Textcopy"
# PROP BASE Intermediate_Dir "Textcopy"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Textcopy"
# PROP Intermediate_Dir "Textcopy"
# PROP Target_Dir ""
OUTDIR=.\Textcopy
INTDIR=.\Textcopy

ALL : "$(OUTDIR)\Textcopy.exe"

CLEAN : 
	-@erase ".\Textcopy\vc40.pdb"
	-@erase ".\Textcopy\Textcopy.exe"
	-@erase ".\Textcopy\Textcopy.obj"
	-@erase ".\Textcopy\Getopt.obj"
	-@erase ".\Textcopy\Textcopy.ilk"
	-@erase ".\Textcopy\Textcopy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /D "_MBCS" /Fp"$(INTDIR)/Textcopy.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Textcopy/
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
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Textcopy.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 nafxcwd.lib libcmtd.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=nafxcwd.lib libcmtd.lib ntwdblib.lib /nologo /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)/Textcopy.pdb" /debug /machine:ALPHA\
 /out:"$(OUTDIR)/Textcopy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Textcopy.obj" \
	"$(INTDIR)/Getopt.obj"

"$(OUTDIR)\Textcopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Textcop0"
# PROP BASE Intermediate_Dir "Textcop0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Textcop0"
# PROP Intermediate_Dir "Textcop0"
# PROP Target_Dir ""
OUTDIR=.\Textcop0
INTDIR=.\Textcop0

ALL : "$(OUTDIR)\Textcopy.exe"

CLEAN : 
	-@erase ".\Textcop0\Textcopy.exe"
	-@erase ".\Textcop0\Getopt.obj"
	-@erase ".\Textcop0\Textcopy.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)/Textcopy.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Textcop0/
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
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Textcopy.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 nafxcw.lib libcmt.lib ntwdblib.lib /nologo /subsystem:console /machine:ALPHA
LINK32_FLAGS=nafxcw.lib libcmt.lib ntwdblib.lib /nologo /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/Textcopy.pdb" /machine:ALPHA\
 /out:"$(OUTDIR)/Textcopy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Getopt.obj" \
	"$(INTDIR)/Textcopy.obj"

"$(OUTDIR)\Textcopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Textcopy - Win32 MIPS Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Textcop1"
# PROP BASE Intermediate_Dir "Textcop1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Textcop1"
# PROP Intermediate_Dir "Textcop1"
# PROP Target_Dir ""
OUTDIR=.\Textcop1
INTDIR=.\Textcop1

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Textcopy.exe"

CLEAN : 
	-@erase ".\Textcop1\vc40.pdb"
	-@erase ".\Textcop1\Textcopy.exe"
	-@erase ".\Textcop1\Getopt.obj"
	-@erase ".\Textcop1\Textcopy.obj"
	-@erase ".\Textcop1\Textcopy.ilk"
	-@erase ".\Textcop1\Textcopy.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)/Textcopy.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Textcop1/
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
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:MIPS
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 nafxcwd.lib libcmtd.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:MIPS
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=nafxcwd.lib libcmtd.lib ntwdblib.lib /nologo /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)/Textcopy.pdb" /debug /machine:MIPS\
 /out:"$(OUTDIR)/Textcopy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Getopt.obj" \
	"$(INTDIR)/Textcopy.obj"

"$(OUTDIR)\Textcopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Textcopy.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Textcopy - Win32 MIPS Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Textcop2"
# PROP BASE Intermediate_Dir "Textcop2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Textcop2"
# PROP Intermediate_Dir "Textcop2"
# PROP Target_Dir ""
OUTDIR=.\Textcop2
INTDIR=.\Textcop2

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Textcopy.exe"

CLEAN : 
	-@erase ".\Textcop2\Textcopy.exe"
	-@erase ".\Textcop2\Getopt.obj"
	-@erase ".\Textcop2\Textcopy.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)/Textcopy.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Textcop2/
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
# ADD BASE LINK32 /nologo /subsystem:console /machine:MIPS
# ADD LINK32 nafxcw.lib libcmt.lib ntwdblib.lib /nologo /subsystem:console /machine:MIPS
LINK32_FLAGS=nafxcw.lib libcmt.lib ntwdblib.lib /nologo /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/Textcopy.pdb" /machine:MIPS\
 /out:"$(OUTDIR)/Textcopy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Getopt.obj" \
	"$(INTDIR)/Textcopy.obj"

"$(OUTDIR)\Textcopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Textcopy.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (PPC) Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Textcop3"
# PROP BASE Intermediate_Dir "Textcop3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Textcop3"
# PROP Intermediate_Dir "Textcop3"
# PROP Target_Dir ""
OUTDIR=.\Textcop3
INTDIR=.\Textcop3

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Textcopy.exe"

CLEAN : 
	-@erase ".\Textcop3\vc40.pdb"
	-@erase ".\Textcop3\Textcopy.exe"
	-@erase ".\Textcop3\Getopt.obj"
	-@erase ".\Textcop3\Textcopy.obj"
	-@erase ".\Textcop3\Textcopy.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)/Textcopy.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Textcop3/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Textcopy.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:PPC
# ADD LINK32 nafxcwd.lib libcmtd.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:PPC
LINK32_FLAGS=nafxcwd.lib libcmtd.lib ntwdblib.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/Textcopy.pdb" /debug /machine:PPC /out:"$(OUTDIR)/Textcopy.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)/Getopt.obj" \
	"$(INTDIR)/Textcopy.obj"

"$(OUTDIR)\Textcopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (PPC) Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Textcop4"
# PROP BASE Intermediate_Dir "Textcop4"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Textcop4"
# PROP Intermediate_Dir "Textcop4"
# PROP Target_Dir ""
OUTDIR=.\Textcop4
INTDIR=.\Textcop4

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Textcopy.exe"

CLEAN : 
	-@erase ".\Textcop4\Textcopy.exe"
	-@erase ".\Textcop4\Getopt.obj"
	-@erase ".\Textcop4\Textcopy.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)/Textcopy.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Textcop4/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Textcopy.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:PPC
# ADD LINK32 nafxcw.lib libcmt.lib ntwdblib.lib /nologo /subsystem:console /machine:PPC
LINK32_FLAGS=nafxcw.lib libcmt.lib ntwdblib.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/Textcopy.pdb" /machine:PPC /out:"$(OUTDIR)/Textcopy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Getopt.obj" \
	"$(INTDIR)/Textcopy.obj"

"$(OUTDIR)\Textcopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "Textcopy - Win32 Release"
# Name "Textcopy - Win32 Debug"
# Name "Textcopy - Win32 (ALPHA) Debug"
# Name "Textcopy - Win32 (ALPHA) Release"
# Name "Textcopy - Win32 MIPS Debug"
# Name "Textcopy - Win32 MIPS Release"
# Name "Textcopy - Win32 (PPC) Debug"
# Name "Textcopy - Win32 (PPC) Release"

!IF  "$(CFG)" == "Textcopy - Win32 Release"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 Debug"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Getopt.c

!IF  "$(CFG)" == "Textcopy - Win32 Release"

"$(INTDIR)\Getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 Debug"

"$(INTDIR)\Getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (ALPHA) Debug"

"$(INTDIR)\Getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Textcopy - Win32 (ALPHA) Release"

"$(INTDIR)\Getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Textcopy - Win32 MIPS Debug"

"$(INTDIR)\Getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 MIPS Release"

"$(INTDIR)\Getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (PPC) Debug"

"$(INTDIR)\Getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (PPC) Release"

"$(INTDIR)\Getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Textcopy.cpp

!IF  "$(CFG)" == "Textcopy - Win32 Release"

"$(INTDIR)\Textcopy.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 Debug"

"$(INTDIR)\Textcopy.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (ALPHA) Debug"

"$(INTDIR)\Textcopy.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Textcopy - Win32 (ALPHA) Release"

"$(INTDIR)\Textcopy.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Textcopy - Win32 MIPS Debug"

"$(INTDIR)\Textcopy.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 MIPS Release"

"$(INTDIR)\Textcopy.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (PPC) Debug"

"$(INTDIR)\Textcopy.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Textcopy - Win32 (PPC) Release"

"$(INTDIR)\Textcopy.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
