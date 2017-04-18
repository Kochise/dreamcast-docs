# Microsoft Developer Studio Generated NMAKE File, Format Version 41001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (PPC) Application" 0x0701
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=adoread - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to adoread - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "adoread - Win32 Release" && "$(CFG)" !=\
 "adoread - Win32 Debug" && "$(CFG)" != "adoread - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "adoread - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "adoread - Win32 (PPC) Debug" && "$(CFG)" != "adoread - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "adoread.mak" CFG="adoread - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "adoread - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "adoread - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "adoread - Win32 (ALPHA) Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "adoread - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "adoread - Win32 (PPC) Debug" (based on "Win32 (PPC) Application")
!MESSAGE "adoread - Win32 (PPC) Release" (based on "Win32 (PPC) Application")
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
# PROP Target_Last_Scanned "adoread - Win32 (ALPHA) Release"

!IF  "$(CFG)" == "adoread - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL :    ".\Retail\adoread.exe" "$(OUTDIR)\adoread.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/adoread.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/

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
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/adoread.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoread.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\adorddlg.sbr" \
	"$(INTDIR)\adoread.sbr" \
	"$(INTDIR)\stdafx.sbr"

"$(OUTDIR)\adoread.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib adoid.lib /nologo /entry:"" /subsystem:windows /machine:I386 /out:"Retail/adoread.exe"
LINK32_FLAGS=winmm.lib adoid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/adoread.pdb" /machine:I386 /out:"Retail/adoread.exe" 
LINK32_OBJS= \
	"$(INTDIR)\adorddlg.obj" \
	"$(INTDIR)\adoread.obj" \
	"$(INTDIR)\adoread.res" \
	"$(INTDIR)\stdafx.obj"

".\Retail\adoread.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoread - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL :    "$(OUTDIR)\adoread.exe" "$(OUTDIR)\adoread.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Fr /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/adoread.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/adoread.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoread.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\adorddlg.sbr" \
	"$(INTDIR)\adoread.sbr" \
	"$(INTDIR)\stdafx.sbr"

"$(OUTDIR)\adoread.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib adoid.lib /nologo /entry:"" /subsystem:windows /debug /machine:I386
LINK32_FLAGS=winmm.lib adoid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/adoread.pdb" /debug /machine:I386 /out:"$(OUTDIR)/adoread.exe" 
LINK32_OBJS= \
	"$(INTDIR)\adorddlg.obj" \
	"$(INTDIR)\adoread.obj" \
	"$(INTDIR)\adoread.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\adoread.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "adoread_"
# PROP BASE Intermediate_Dir "adoread_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
OUTDIR=.\debug
INTDIR=.\debug

ALL :  "$(OUTDIR)\adoread.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/adoread.pch" /YX /Fo"$(INTDIR)/"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/adoread.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoread.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 adoid.lib winmm.lib /nologo /subsystem:windows /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=adoid.lib winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/adoread.pdb" /debug /machine:ALPHA /out:"$(OUTDIR)/adoread.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\adorddlg.obj" \
	"$(INTDIR)\adoread.obj" \
	"$(INTDIR)\adoread.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\adoread.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "adoread0"
# PROP BASE Intermediate_Dir "adoread0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Target_Dir ""
OUTDIR=.\retail
INTDIR=.\retail

ALL :  "$(OUTDIR)\adoread.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/adoread.pch" /YX /Fo"$(INTDIR)/" /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/adoread.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoread.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 adoid.lib winmm.lib /nologo /subsystem:windows /machine:ALPHA
LINK32_FLAGS=adoid.lib winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/adoread.pdb" /machine:ALPHA /out:"$(OUTDIR)/adoread.exe" 
LINK32_OBJS= \
	"$(INTDIR)\adorddlg.obj" \
	"$(INTDIR)\adoread.obj" \
	"$(INTDIR)\adoread.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\adoread.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "adoread_"
# PROP BASE Intermediate_Dir "adoread_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
OUTDIR=.\debug
INTDIR=.\debug

ALL : "$(OUTDIR)\adoread.exe"

CLEAN : 
	-@erase "$(INTDIR)\adorddlg.obj"
	-@erase "$(INTDIR)\adoread.obj"
	-@erase "$(INTDIR)\adoread.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\adoread.exe"
	-@erase "$(OUTDIR)\adoread.pdb"

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
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/adoread.pch" /YX /Fo"$(INTDIR)/"\
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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/adoread.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoread.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:PPC
# ADD LINK32 adoid.lib winmm.lib /nologo /subsystem:windows /debug /machine:PPC
LINK32_FLAGS=adoid.lib winmm.lib /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)/adoread.pdb" /debug /machine:PPC /out:"$(OUTDIR)/adoread.exe" 
LINK32_OBJS= \
	"$(INTDIR)\adorddlg.obj" \
	"$(INTDIR)\adoread.obj" \
	"$(INTDIR)\adoread.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\adoread.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "adoread0"
# PROP BASE Intermediate_Dir "adoread0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Target_Dir ""
OUTDIR=.\retail
INTDIR=.\retail

ALL : "$(OUTDIR)\adoread.exe"

CLEAN : 
	-@erase "$(INTDIR)\adorddlg.obj"
	-@erase "$(INTDIR)\adoread.obj"
	-@erase "$(INTDIR)\adoread.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(OUTDIR)\adoread.exe"

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
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/adoread.pch" /YX /Fo"$(INTDIR)/" /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/adoread.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adoread.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:PPC
# ADD LINK32 adoid.lib winmm.lib /nologo /subsystem:windows /machine:PPC
LINK32_FLAGS=adoid.lib winmm.lib /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)/adoread.pdb" /machine:PPC /out:"$(OUTDIR)/adoread.exe" 
LINK32_OBJS= \
	"$(INTDIR)\adorddlg.obj" \
	"$(INTDIR)\adoread.obj" \
	"$(INTDIR)\adoread.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\adoread.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "adoread - Win32 Release"
# Name "adoread - Win32 Debug"
# Name "adoread - Win32 (ALPHA) Debug"
# Name "adoread - Win32 (ALPHA) Release"
# Name "adoread - Win32 (PPC) Debug"
# Name "adoread - Win32 (PPC) Release"

!IF  "$(CFG)" == "adoread - Win32 Release"

!ELSEIF  "$(CFG)" == "adoread - Win32 Debug"

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "adoread - Win32 Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

"$(INTDIR)\stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

"$(INTDIR)\stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\adoread.cpp

!IF  "$(CFG)" == "adoread - Win32 Release"

"$(INTDIR)\adoread.obj" : $(SOURCE) $(DEP_CPP_ADORE) "$(INTDIR)"

"$(INTDIR)\adoread.sbr" : $(SOURCE) $(DEP_CPP_ADORE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 Debug"

DEP_CPP_ADORE=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	

"$(INTDIR)\adoread.obj" : $(SOURCE) $(DEP_CPP_ADORE) "$(INTDIR)"

"$(INTDIR)\adoread.sbr" : $(SOURCE) $(DEP_CPP_ADORE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Debug"

DEP_CPP_ADORE=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	

"$(INTDIR)\adoread.obj" : $(SOURCE) $(DEP_CPP_ADORE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Release"

DEP_CPP_ADORE=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	

"$(INTDIR)\adoread.obj" : $(SOURCE) $(DEP_CPP_ADORE) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Debug"

DEP_CPP_ADORE=\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\adoread.obj" : $(SOURCE) $(DEP_CPP_ADORE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Release"

DEP_CPP_ADORE=\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\adoread.obj" : $(SOURCE) $(DEP_CPP_ADORE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\adorddlg.cpp

!IF  "$(CFG)" == "adoread - Win32 Release"

"$(INTDIR)\adorddlg.obj" : $(SOURCE) $(DEP_CPP_ADORD) "$(INTDIR)"

"$(INTDIR)\adorddlg.sbr" : $(SOURCE) $(DEP_CPP_ADORD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 Debug"

DEP_CPP_ADORD=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	

"$(INTDIR)\adorddlg.obj" : $(SOURCE) $(DEP_CPP_ADORD) "$(INTDIR)"

"$(INTDIR)\adorddlg.sbr" : $(SOURCE) $(DEP_CPP_ADORD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Debug"

DEP_CPP_ADORD=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	

"$(INTDIR)\adorddlg.obj" : $(SOURCE) $(DEP_CPP_ADORD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Release"

DEP_CPP_ADORD=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	

"$(INTDIR)\adorddlg.obj" : $(SOURCE) $(DEP_CPP_ADORD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Debug"

DEP_CPP_ADORD=\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\adorddlg.obj" : $(SOURCE) $(DEP_CPP_ADORD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Release"

DEP_CPP_ADORD=\
	".\adorddlg.h"\
	".\adoread.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\adorddlg.obj" : $(SOURCE) $(DEP_CPP_ADORD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\adoread.rc

!IF  "$(CFG)" == "adoread - Win32 Release"

"$(INTDIR)\adoread.res" : $(SOURCE) $(DEP_RSC_ADOREA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "adoread - Win32 Debug"

DEP_RSC_ADOREA=\
	".\res\adoread.ico"\
	".\res\adoread.rc2"\
	

"$(INTDIR)\adoread.res" : $(SOURCE) $(DEP_RSC_ADOREA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Debug"

DEP_RSC_ADOREA=\
	".\res\adoread.ico"\
	".\res\adoread.rc2"\
	

"$(INTDIR)\adoread.res" : $(SOURCE) $(DEP_RSC_ADOREA) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/adoread.res" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "adoread - Win32 (ALPHA) Release"

DEP_RSC_ADOREA=\
	".\res\adoread.ico"\
	".\res\adoread.rc2"\
	

"$(INTDIR)\adoread.res" : $(SOURCE) $(DEP_RSC_ADOREA) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/adoread.res" /d "NDEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Debug"

DEP_RSC_ADOREA=\
	".\res\adoread.ico"\
	".\res\adoread.rc2"\
	

"$(INTDIR)\adoread.res" : $(SOURCE) $(DEP_RSC_ADOREA) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/adoread.res" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "adoread - Win32 (PPC) Release"

DEP_RSC_ADOREA=\
	".\res\adoread.ico"\
	".\res\adoread.rc2"\
	

"$(INTDIR)\adoread.res" : $(SOURCE) $(DEP_RSC_ADOREA) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/adoread.res" /d "NDEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
