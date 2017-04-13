# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (PPC) Application" 0x0701
# TARGTYPE "Win32 (MIPS) Application" 0x0501
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=SQLTestN - Win32 (PPC) Debug
!MESSAGE No configuration specified.  Defaulting to SQLTestN - Win32 (PPC)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "SQLTestN - Win32 Release" && "$(CFG)" !=\
 "SQLTestN - Win32 Debug" && "$(CFG)" != "SQLTestN - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "SQLTestN - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "SQLTestN - Win32 MIPS Debug" && "$(CFG)" != "SQLTestN - Win32 MIPS Release" &&\
 "$(CFG)" != "SQLTestN - Win32 (PPC) Debug" && "$(CFG)" !=\
 "SQLTestN - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SQLTestN.mak" CFG="SQLTestN - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SQLTestN - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SQLTestN - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SQLTestN - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "SQLTestN - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "SQLTestN - Win32 MIPS Debug" (based on "Win32 (MIPS) Application")
!MESSAGE "SQLTestN - Win32 MIPS Release" (based on "Win32 (MIPS) Application")
!MESSAGE "SQLTestN - Win32 (PPC) Debug" (based on "Win32 (PPC) Application")
!MESSAGE "SQLTestN - Win32 (PPC) Release" (based on "Win32 (PPC) Application")
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

!IF  "$(CFG)" == "SQLTestN - Win32 Release"

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

ALL : "$(OUTDIR)\SQLTestN.exe"

CLEAN : 
	-@erase ".\Release\SQLTestN.exe"
	-@erase ".\Release\Sqltestn.obj"
	-@erase ".\Release\Sqltestn.res"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SQLTestN.pch" /YX /Fo"$(INTDIR)/" /c 
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
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestN.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SQLTestN.pdb" /machine:I386 /out:"$(OUTDIR)/SQLTestN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestn.obj" \
	"$(INTDIR)/Sqltestn.res"

"$(OUTDIR)\SQLTestN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 Debug"

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

ALL : "$(OUTDIR)\SQLTestN.exe"

CLEAN : 
	-@erase ".\Debug\SQLTestN.exe"
	-@erase ".\Debug\Sqltestn.obj"
	-@erase ".\Debug\Sqltestn.res"
	-@erase ".\Debug\SQLTestN.ilk"
	-@erase ".\Debug\SQLTestN.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SQLTestN.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestN.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SQLTestN.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/SQLTestN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestn.obj" \
	"$(INTDIR)/Sqltestn.res"

"$(OUTDIR)\SQLTestN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SQLTestN"
# PROP BASE Intermediate_Dir "SQLTestN"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SQLTestN"
# PROP Intermediate_Dir "SQLTestN"
# PROP Target_Dir ""
OUTDIR=.\SQLTestN
INTDIR=.\SQLTestN

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLTestN.exe"

CLEAN : 
	-@erase ".\SQLTestN\vc40.pdb"
	-@erase ".\SQLTestN\SQLTestN.exe"
	-@erase ".\SQLTestN\Sqltestn.obj"
	-@erase ".\SQLTestN\Sqltestn.res"
	-@erase ".\SQLTestN\SQLTestN.ilk"
	-@erase ".\SQLTestN\SQLTestN.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SQLTestN.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\SQLTestN/
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
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestN.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SQLTestN.pdb" /debug /machine:ALPHA\
 /out:"$(OUTDIR)/SQLTestN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestn.obj" \
	"$(INTDIR)/Sqltestn.res"

"$(OUTDIR)\SQLTestN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (ALPHA) Release"

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

ALL : "$(OUTDIR)\SQLTestN.exe"

CLEAN : 
	-@erase ".\SQLTest0\SQLTestN.exe"
	-@erase ".\SQLTest0\Sqltestn.obj"
	-@erase ".\SQLTest0\Sqltestn.res"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SQLTestN.pch" /YX /Fo"$(INTDIR)/" /c 
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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestN.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SQLTestN.pdb" /machine:ALPHA /out:"$(OUTDIR)/SQLTestN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestn.obj" \
	"$(INTDIR)/Sqltestn.res"

"$(OUTDIR)\SQLTestN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 MIPS Debug"

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

ALL : "$(OUTDIR)\SQLTestN.exe"

CLEAN : 
	-@erase ".\SQLTest1\vc40.pdb"
	-@erase ".\SQLTest1\SQLTestN.exe"
	-@erase ".\SQLTest1\Sqltestn.obj"
	-@erase ".\SQLTest1\Sqltestn.res"
	-@erase ".\SQLTest1\SQLTestN.ilk"
	-@erase ".\SQLTest1\SQLTestN.pdb"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/SQLTestN.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "_DEBUG" 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:MIPS
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /debug /machine:MIPS
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SQLTestN.pdb" /debug /machine:MIPS\
 /out:"$(OUTDIR)/SQLTestN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestn.obj" \
	"$(INTDIR)/Sqltestn.res"

"$(OUTDIR)\SQLTestN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestN.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 MIPS Release"

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

ALL : "$(OUTDIR)\SQLTestN.exe"

CLEAN : 
	-@erase ".\SQLTest2\SQLTestN.exe"
	-@erase ".\SQLTest2\Sqltestn.obj"
	-@erase ".\SQLTest2\Sqltestn.res"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/SQLTestN.pch" /YX /Fo"$(INTDIR)/" /c 
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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "NDEBUG" 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:MIPS
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /machine:MIPS
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SQLTestN.pdb" /machine:MIPS /out:"$(OUTDIR)/SQLTestN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestn.obj" \
	"$(INTDIR)/Sqltestn.res"

"$(OUTDIR)\SQLTestN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestN.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (PPC) Debug"

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

ALL : "$(OUTDIR)\SQLTestN.exe"

CLEAN : 
	-@erase ".\SQLTest3\vc40.pdb"
	-@erase ".\SQLTest3\SQLTestN.exe"
	-@erase ".\SQLTest3\Sqltestn.obj"
	-@erase ".\SQLTest3\Sqltestn.res"
	-@erase ".\SQLTest3\SQLTestN.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /PPC32
# ADD MTL /nologo /D "_DEBUG" /PPC32
MTL_PROJ=/nologo /D "_DEBUG" /PPC32 
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SQLTestN.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestN.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)/SQLTestN.pdb" /debug /machine:PPC /out:"$(OUTDIR)/SQLTestN.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestn.obj" \
	"$(INTDIR)/Sqltestn.res"

"$(OUTDIR)\SQLTestN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (PPC) Release"

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

ALL : "$(OUTDIR)\SQLTestN.exe"

CLEAN : 
	-@erase ".\SQLTest4\SQLTestN.exe"
	-@erase ".\SQLTest4\Sqltestn.obj"
	-@erase ".\SQLTest4\Sqltestn.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /PPC32
# ADD MTL /nologo /D "NDEBUG" /PPC32
MTL_PROJ=/nologo /D "NDEBUG" /PPC32 
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SQLTestN.pch" /YX /Fo"$(INTDIR)/" /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLTestN.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:windows /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)/SQLTestN.pdb" /machine:PPC /out:"$(OUTDIR)/SQLTestN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqltestn.obj" \
	"$(INTDIR)/Sqltestn.res"

"$(OUTDIR)\SQLTestN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "SQLTestN - Win32 Release"
# Name "SQLTestN - Win32 Debug"
# Name "SQLTestN - Win32 (ALPHA) Debug"
# Name "SQLTestN - Win32 (ALPHA) Release"
# Name "SQLTestN - Win32 MIPS Debug"
# Name "SQLTestN - Win32 MIPS Release"
# Name "SQLTestN - Win32 (PPC) Debug"
# Name "SQLTestN - Win32 (PPC) Release"

!IF  "$(CFG)" == "SQLTestN - Win32 Release"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 Debug"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Sqltestn.c

!IF  "$(CFG)" == "SQLTestN - Win32 Release"

"$(INTDIR)\Sqltestn.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 Debug"

"$(INTDIR)\Sqltestn.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (ALPHA) Debug"

"$(INTDIR)\Sqltestn.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (ALPHA) Release"

"$(INTDIR)\Sqltestn.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 MIPS Debug"

"$(INTDIR)\Sqltestn.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 MIPS Release"

"$(INTDIR)\Sqltestn.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (PPC) Debug"

"$(INTDIR)\Sqltestn.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (PPC) Release"

"$(INTDIR)\Sqltestn.obj" : $(SOURCE) $(DEP_CPP_SQLTE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sqltestn.rc

!IF  "$(CFG)" == "SQLTestN - Win32 Release"

"$(INTDIR)\Sqltestn.res" : $(SOURCE) $(DEP_RSC_SQLTES) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SQLTestN - Win32 Debug"

"$(INTDIR)\Sqltestn.res" : $(SOURCE) $(DEP_RSC_SQLTES) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (ALPHA) Debug"

"$(INTDIR)\Sqltestn.res" : $(SOURCE) $(DEP_RSC_SQLTES) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (ALPHA) Release"

"$(INTDIR)\Sqltestn.res" : $(SOURCE) $(DEP_RSC_SQLTES) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "SQLTestN - Win32 MIPS Debug"

"$(INTDIR)\Sqltestn.res" : $(SOURCE) $(DEP_RSC_SQLTES) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "SQLTestN - Win32 MIPS Release"

"$(INTDIR)\Sqltestn.res" : $(SOURCE) $(DEP_RSC_SQLTES) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (PPC) Debug"

"$(INTDIR)\Sqltestn.res" : $(SOURCE) $(DEP_RSC_SQLTES) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "SQLTestN - Win32 (PPC) Release"

"$(INTDIR)\Sqltestn.res" : $(SOURCE) $(DEP_RSC_SQLTES) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Sqltestn.res" /d "NDEBUG" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
