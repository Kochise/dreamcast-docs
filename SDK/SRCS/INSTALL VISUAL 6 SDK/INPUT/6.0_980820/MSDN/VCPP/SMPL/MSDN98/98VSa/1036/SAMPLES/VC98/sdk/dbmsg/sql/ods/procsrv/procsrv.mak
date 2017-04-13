# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (MIPS) Console Application" 0x0503
# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603
# TARGTYPE "Win32 (PPC) Console Application" 0x0703

!IF "$(CFG)" == ""
CFG=Procsrv - Win32 (PPC) Debug
!MESSAGE No configuration specified.  Defaulting to Procsrv - Win32 (PPC)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "Procsrv - Win32 Release" && "$(CFG)" !=\
 "Procsrv - Win32 Debug" && "$(CFG)" != "Service - Win32 Release" && "$(CFG)" !=\
 "Service - Win32 Debug" && "$(CFG)" != "Service - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "Service - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "Procsrv - Win32 (ALPHA) Debug" && "$(CFG)" !=\
 "Procsrv - Win32 (ALPHA) Release" && "$(CFG)" != "Procsrv - Win32 MIPS Debug"\
 && "$(CFG)" != "Procsrv - Win32 MIPS Release" && "$(CFG)" !=\
 "Service - Win32 MIPS Debug" && "$(CFG)" != "Service - Win32 MIPS Release" &&\
 "$(CFG)" != "Service - Win32 (PPC) Debug" && "$(CFG)" !=\
 "Service - Win32 (PPC) Release" && "$(CFG)" != "Procsrv - Win32 (PPC) Debug" &&\
 "$(CFG)" != "Procsrv - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Procsrv.mak" CFG="Procsrv - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Procsrv - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Procsrv - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Service - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Service - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Service - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Service - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Procsrv - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Procsrv - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Procsrv - Win32 MIPS Debug" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Procsrv - Win32 MIPS Release" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Service - Win32 MIPS Debug" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Service - Win32 MIPS Release" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Service - Win32 (PPC) Debug" (based on\
 "Win32 (PPC) Console Application")
!MESSAGE "Service - Win32 (PPC) Release" (based on\
 "Win32 (PPC) Console Application")
!MESSAGE "Procsrv - Win32 (PPC) Debug" (based on\
 "Win32 (PPC) Console Application")
!MESSAGE "Procsrv - Win32 (PPC) Release" (based on\
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
# PROP Target_Last_Scanned "Procsrv - Win32 Debug"

!IF  "$(CFG)" == "Procsrv - Win32 Release"

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

ALL : "Service - Win32 Release" "$(OUTDIR)\Procsrv.exe"

CLEAN : 
	-@erase ".\Release\Procsrv.exe"
	-@erase ".\Release\PROCSRV.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Procsrv.pch" /YX /Fo"$(INTDIR)/" /c 
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

RSC=rc.exe
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Procsrv.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Procsrv.pdb" /machine:I386 /out:"$(OUTDIR)/Procsrv.exe" 
LINK32_OBJS= \
	".\Release\PROCSRV.OBJ"

"$(OUTDIR)\Procsrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Procsrv - Win32 Debug"

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

ALL : "Service - Win32 Debug" "$(OUTDIR)\Procsrv.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Procsrv.exe"
	-@erase ".\Debug\PROCSRV.OBJ"
	-@erase ".\Debug\Procsrv.ilk"
	-@erase ".\Debug\Procsrv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Procsrv.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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

RSC=rc.exe
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Procsrv.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Procsrv.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Procsrv.exe" 
LINK32_OBJS= \
	".\Debug\PROCSRV.OBJ"

"$(OUTDIR)\Procsrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Service - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Service\Release"
# PROP BASE Intermediate_Dir "Service\Release"
# PROP BASE Target_Dir "Service"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Service\Release"
# PROP Intermediate_Dir "Service\Release"
# PROP Target_Dir "Service"
OUTDIR=.\Service\Release
INTDIR=.\Service\Release

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\Service\Release\Service.exe"
	-@erase ".\Service\Release\SERVICE.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Service.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Service\Release/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Service.pdb" /machine:I386 /out:"$(OUTDIR)/Service.exe" 
LINK32_OBJS= \
	".\Service\Release\SERVICE.OBJ"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Service - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Service\Debug"
# PROP BASE Intermediate_Dir "Service\Debug"
# PROP BASE Target_Dir "Service"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Service\Debug"
# PROP Intermediate_Dir "Service\Debug"
# PROP Target_Dir "Service"
OUTDIR=.\Service\Debug
INTDIR=.\Service\Debug

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\Service\Debug\vc40.pdb"
	-@erase ".\Service\Debug\vc40.idb"
	-@erase ".\Service\Debug\Service.exe"
	-@erase ".\Service\Debug\SERVICE.OBJ"
	-@erase ".\Service\Debug\Service.ilk"
	-@erase ".\Service\Debug\Service.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Service.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Service\Debug/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Service.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Service.exe" 
LINK32_OBJS= \
	".\Service\Debug\SERVICE.OBJ"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Service - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Service\AlphaDbg"
# PROP BASE Intermediate_Dir "Service\AlphaDbg"
# PROP BASE Target_Dir "Service"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Service\AlphaDbg"
# PROP Intermediate_Dir "Service\AlphaDbg"
# PROP Target_Dir "Service"
OUTDIR=.\Service\AlphaDbg
INTDIR=.\Service\AlphaDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\Service\AlphaDbg\vc40.pdb"
	-@erase ".\Service\AlphaDbg\Service.exe"
	-@erase ".\Service\AlphaDbg\SERVICE.OBJ"
	-@erase ".\Service\AlphaDbg\Service.ilk"
	-@erase ".\Service\AlphaDbg\Service.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Service.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Service\AlphaDbg/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Service.pdb" /debug /machine:ALPHA /out:"$(OUTDIR)/Service.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)/SERVICE.OBJ"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Service - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Service\AlphaRel"
# PROP BASE Intermediate_Dir "Service\AlphaRel"
# PROP BASE Target_Dir "Service"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Service\AlphaRel"
# PROP Intermediate_Dir "Service\AlphaRel"
# PROP Target_Dir "Service"
OUTDIR=.\Service\AlphaRel
INTDIR=.\Service\AlphaRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\Service\AlphaRel\Service.exe"
	-@erase ".\Service\AlphaRel\SERVICE.OBJ"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Service.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Service\AlphaRel/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Service.pdb" /machine:ALPHA /out:"$(OUTDIR)/Service.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SERVICE.OBJ"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Procsrv_"
# PROP BASE Intermediate_Dir "Procsrv_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Procsrv_"
# PROP Intermediate_Dir "Procsrv_"
# PROP Target_Dir ""
OUTDIR=.\Procsrv_
INTDIR=.\Procsrv_

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "Service - Win32 (ALPHA) Debug" "$(OUTDIR)\Procsrv.exe"

CLEAN : 
	-@erase ".\Procsrv_\vc40.pdb"
	-@erase ".\Procsrv_\Procsrv.exe"
	-@erase ".\Procsrv_\PROCSRV.OBJ"
	-@erase ".\Procsrv_\Procsrv.ilk"
	-@erase ".\Procsrv_\Procsrv.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Procsrv.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Procsrv_/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Procsrv.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Procsrv.pdb" /debug /machine:ALPHA /out:"$(OUTDIR)/Procsrv.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)/PROCSRV.OBJ"

"$(OUTDIR)\Procsrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Procsrv0"
# PROP BASE Intermediate_Dir "Procsrv0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Procsrv0"
# PROP Intermediate_Dir "Procsrv0"
# PROP Target_Dir ""
OUTDIR=.\Procsrv0
INTDIR=.\Procsrv0

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "Service - Win32 (ALPHA) Release" "$(OUTDIR)\Procsrv.exe"

CLEAN : 
	-@erase ".\Procsrv0\Procsrv.exe"
	-@erase ".\Procsrv0\PROCSRV.OBJ"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Procsrv.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Procsrv0/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Procsrv.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Procsrv.pdb" /machine:ALPHA /out:"$(OUTDIR)/Procsrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)/PROCSRV.OBJ"

"$(OUTDIR)\Procsrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Procsrv - Win32 MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Procsrv1"
# PROP BASE Intermediate_Dir "Procsrv1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Procsrv1"
# PROP Intermediate_Dir "Procsrv1"
# PROP Target_Dir ""
OUTDIR=.\Procsrv1
INTDIR=.\Procsrv1

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "Service - Win32 MIPS Debug" "$(OUTDIR)\Procsrv.exe"

CLEAN : 
	-@erase ".\Procsrv1\vc40.pdb"
	-@erase ".\Procsrv1\Procsrv.exe"
	-@erase ".\Procsrv1\PROCSRV.OBJ"
	-@erase ".\Procsrv1\Procsrv.ilk"
	-@erase ".\Procsrv1\Procsrv.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/Procsrv.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Procsrv1/
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /debug /machine:MIPS
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Procsrv.pdb" /debug /machine:MIPS /out:"$(OUTDIR)/Procsrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)/PROCSRV.OBJ"

"$(OUTDIR)\Procsrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Procsrv.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Procsrv - Win32 MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Procsrv2"
# PROP BASE Intermediate_Dir "Procsrv2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Procsrv2"
# PROP Intermediate_Dir "Procsrv2"
# PROP Target_Dir ""
OUTDIR=.\Procsrv2
INTDIR=.\Procsrv2

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "Service - Win32 MIPS Release" "$(OUTDIR)\Procsrv.exe"

CLEAN : 
	-@erase ".\Procsrv2\Procsrv.exe"
	-@erase ".\Procsrv2\PROCSRV.OBJ"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/Procsrv.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Procsrv2/
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /machine:MIPS
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Procsrv.pdb" /machine:MIPS /out:"$(OUTDIR)/Procsrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)/PROCSRV.OBJ"

"$(OUTDIR)\Procsrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Procsrv.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Service - Win32 MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Service\MIPS Debug"
# PROP BASE Intermediate_Dir "Service\MIPS Debug"
# PROP BASE Target_Dir "Service"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Service\MIPS Debug"
# PROP Intermediate_Dir "Service\MIPS Debug"
# PROP Target_Dir "Service"
OUTDIR=.\Service\MIPS Debug
INTDIR=.\Service\MIPS Debug

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\Service\MIPS Debug\vc40.pdb"
	-@erase ".\Service\MIPS Debug\Service.exe"
	-@erase ".\Service\MIPS Debug\SERVICE.OBJ"
	-@erase ".\Service\MIPS Debug\Service.ilk"
	-@erase ".\Service\MIPS Debug\Service.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/Service.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=".\Service\MIPS Debug/"
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /debug /machine:MIPS
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Service.pdb" /debug /machine:MIPS /out:"$(OUTDIR)/Service.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SERVICE.OBJ"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Service - Win32 MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Service\MIPS Release"
# PROP BASE Intermediate_Dir "Service\MIPS Release"
# PROP BASE Target_Dir "Service"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Service\MIPS Release"
# PROP Intermediate_Dir "Service\MIPS Release"
# PROP Target_Dir "Service"
OUTDIR=.\Service\MIPS Release
INTDIR=.\Service\MIPS Release

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\Service\MIPS Release\Service.exe"
	-@erase ".\Service\MIPS Release\SERVICE.OBJ"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/Service.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=".\Service\MIPS Release/"
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /machine:MIPS
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Service.pdb" /machine:MIPS /out:"$(OUTDIR)/Service.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SERVICE.OBJ"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Service - Win32 (PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Service\PPCDbg"
# PROP BASE Intermediate_Dir "Service\PPCDbg"
# PROP BASE Target_Dir "Service"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Service\PPCDbg"
# PROP Intermediate_Dir "Service\PPCDbg"
# PROP Target_Dir "Service"
OUTDIR=.\Service\PPCDbg
INTDIR=.\Service\PPCDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\Service\PPCDbg\vc40.pdb"
	-@erase ".\Service\PPCDbg\Service.exe"
	-@erase ".\Service\PPCDbg\SERVICE.OBJ"
	-@erase ".\Service\PPCDbg\Service.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Service.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Service\PPCDbg/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /pdb:"$(OUTDIR)/Service.pdb" /debug\
 /machine:PPC /out:"$(OUTDIR)/Service.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SERVICE.OBJ"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Service - Win32 (PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Service\PPCRel"
# PROP BASE Intermediate_Dir "Service\PPCRel"
# PROP BASE Target_Dir "Service"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Service\PPCRel"
# PROP Intermediate_Dir "Service\PPCRel"
# PROP Target_Dir "Service"
OUTDIR=.\Service\PPCRel
INTDIR=.\Service\PPCRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\Service\PPCRel\Service.exe"
	-@erase ".\Service\PPCRel\SERVICE.OBJ"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Service.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Service\PPCRel/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /pdb:"$(OUTDIR)/Service.pdb"\
 /machine:PPC /out:"$(OUTDIR)/Service.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SERVICE.OBJ"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Procsrv3"
# PROP BASE Intermediate_Dir "Procsrv3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Procsrv3"
# PROP Intermediate_Dir "Procsrv3"
# PROP Target_Dir ""
OUTDIR=.\Procsrv3
INTDIR=.\Procsrv3

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "Service - Win32 (PPC) Debug" "$(OUTDIR)\Procsrv.exe"

CLEAN : 
	-@erase ".\Procsrv3\vc40.pdb"
	-@erase ".\Procsrv3\Procsrv.exe"
	-@erase ".\Procsrv3\PROCSRV.OBJ"
	-@erase ".\Procsrv3\Procsrv.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Procsrv.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Procsrv3/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Procsrv.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/Procsrv.pdb" /debug /machine:PPC /out:"$(OUTDIR)/Procsrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)/PROCSRV.OBJ"

"$(OUTDIR)\Procsrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Procsrv4"
# PROP BASE Intermediate_Dir "Procsrv4"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Procsrv4"
# PROP Intermediate_Dir "Procsrv4"
# PROP Target_Dir ""
OUTDIR=.\Procsrv4
INTDIR=.\Procsrv4

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "Service - Win32 (PPC) Release" "$(OUTDIR)\Procsrv.exe"

CLEAN : 
	-@erase ".\Procsrv4\Procsrv.exe"
	-@erase ".\Procsrv4\PROCSRV.OBJ"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Procsrv.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Procsrv4/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Procsrv.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib /nologo /subsystem:console /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib opends60.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/Procsrv.pdb" /machine:PPC /out:"$(OUTDIR)/Procsrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)/PROCSRV.OBJ"

"$(OUTDIR)\Procsrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "Procsrv - Win32 Release"
# Name "Procsrv - Win32 Debug"
# Name "Procsrv - Win32 (ALPHA) Debug"
# Name "Procsrv - Win32 (ALPHA) Release"
# Name "Procsrv - Win32 MIPS Debug"
# Name "Procsrv - Win32 MIPS Release"
# Name "Procsrv - Win32 (PPC) Debug"
# Name "Procsrv - Win32 (PPC) Release"

!IF  "$(CFG)" == "Procsrv - Win32 Release"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 Debug"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\PROCSRV.C

!IF  "$(CFG)" == "Procsrv - Win32 Release"

"$(INTDIR)\PROCSRV.OBJ" : $(SOURCE) $(DEP_CPP_PROCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Procsrv - Win32 Debug"

"$(INTDIR)\PROCSRV.OBJ" : $(SOURCE) $(DEP_CPP_PROCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Procsrv - Win32 (ALPHA) Debug"

"$(INTDIR)\PROCSRV.OBJ" : $(SOURCE) $(DEP_CPP_PROCS) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (ALPHA) Release"

"$(INTDIR)\PROCSRV.OBJ" : $(SOURCE) $(DEP_CPP_PROCS) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 MIPS Debug"

"$(INTDIR)\PROCSRV.OBJ" : $(SOURCE) $(DEP_CPP_PROCS) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 MIPS Release"

"$(INTDIR)\PROCSRV.OBJ" : $(SOURCE) $(DEP_CPP_PROCS) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (PPC) Debug"

"$(INTDIR)\PROCSRV.OBJ" : $(SOURCE) $(DEP_CPP_PROCS) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (PPC) Release"

"$(INTDIR)\PROCSRV.OBJ" : $(SOURCE) $(DEP_CPP_PROCS) "$(INTDIR)"

!ENDIF 

# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "Service"

!IF  "$(CFG)" == "Procsrv - Win32 Release"

"Service - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Procsrv.mak CFG="Service - Win32 Release" 

!ELSEIF  "$(CFG)" == "Procsrv - Win32 Debug"

"Service - Win32 Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Procsrv.mak CFG="Service - Win32 Debug" 

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (ALPHA) Debug"

"Service - Win32 (ALPHA) Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Procsrv.mak CFG="Service - Win32 (ALPHA) Debug" 

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (ALPHA) Release"

"Service - Win32 (ALPHA) Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Procsrv.mak CFG="Service - Win32 (ALPHA) Release" 

!ELSEIF  "$(CFG)" == "Procsrv - Win32 MIPS Debug"

"Service - Win32 MIPS Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Procsrv.mak CFG="Service - Win32 MIPS Debug" 

!ELSEIF  "$(CFG)" == "Procsrv - Win32 MIPS Release"

"Service - Win32 MIPS Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Procsrv.mak CFG="Service - Win32 MIPS Release" 

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (PPC) Debug"

"Service - Win32 (PPC) Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Procsrv.mak CFG="Service - Win32 (PPC) Debug" 

!ELSEIF  "$(CFG)" == "Procsrv - Win32 (PPC) Release"

"Service - Win32 (PPC) Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Procsrv.mak CFG="Service - Win32 (PPC) Release" 

!ENDIF 

# End Project Dependency
# End Target
################################################################################
# Begin Target

# Name "Service - Win32 Release"
# Name "Service - Win32 Debug"
# Name "Service - Win32 (ALPHA) Debug"
# Name "Service - Win32 (ALPHA) Release"
# Name "Service - Win32 MIPS Debug"
# Name "Service - Win32 MIPS Release"
# Name "Service - Win32 (PPC) Debug"
# Name "Service - Win32 (PPC) Release"

!IF  "$(CFG)" == "Service - Win32 Release"

!ELSEIF  "$(CFG)" == "Service - Win32 Debug"

!ELSEIF  "$(CFG)" == "Service - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "Service - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "Service - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "Service - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "Service - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "Service - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SERVICE.C

!IF  "$(CFG)" == "Service - Win32 Release"


"$(INTDIR)\SERVICE.OBJ" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Service - Win32 Debug"


"$(INTDIR)\SERVICE.OBJ" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Service - Win32 (ALPHA) Debug"

"$(INTDIR)\SERVICE.OBJ" : $(SOURCE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Service - Win32 (ALPHA) Release"

"$(INTDIR)\SERVICE.OBJ" : $(SOURCE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Service - Win32 MIPS Debug"

"$(INTDIR)\SERVICE.OBJ" : $(SOURCE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Service - Win32 MIPS Release"

"$(INTDIR)\SERVICE.OBJ" : $(SOURCE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Service - Win32 (PPC) Debug"

"$(INTDIR)\SERVICE.OBJ" : $(SOURCE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Service - Win32 (PPC) Release"

"$(INTDIR)\SERVICE.OBJ" : $(SOURCE) "$(INTDIR)"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
