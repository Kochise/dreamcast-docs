# Microsoft Developer Studio Generated NMAKE File, Format Version 41001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (PPC) Application" 0x0701
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=GetRows - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to GetRows - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "GetRows - Win32 Release" && "$(CFG)" !=\
 "GetRows - Win32 Debug" && "$(CFG)" != "GetRows - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "GetRows - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "GetRows - Win32 (PPC) Release" && "$(CFG)" != "GetRows - Win32 (PPC) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "getrows.mak" CFG="GetRows - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GetRows - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GetRows - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "GetRows - Win32 (ALPHA) Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "GetRows - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "GetRows - Win32 (PPC) Release" (based on "Win32 (PPC) Application")
!MESSAGE "GetRows - Win32 (PPC) Debug" (based on "Win32 (PPC) Application")
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
# PROP Target_Last_Scanned "GetRows - Win32 (ALPHA) Release"

!IF  "$(CFG)" == "GetRows - Win32 Release"

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

ALL :   "$(OUTDIR)\getrows.exe" "$(OUTDIR)\getrows.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/getrows.pch" /YX\
 /Fo"$(INTDIR)/" /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GetRows.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/getrows.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\getrdlg.sbr" \
	"$(INTDIR)\getrows.sbr" \
	"$(INTDIR)\stdafx.sbr"

"$(OUTDIR)\getrows.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 adoid.lib /nologo /subsystem:windows /machine:I386 /out:"$(OUTDIR)\getrows.exe"
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/getrows.pdb" /machine:I386 /out:"$(OUTDIR)\getrows.exe"
LINK32_OBJS= \
	"$(INTDIR)\getrdlg.obj" \
	"$(INTDIR)\getrows.obj" \
	"$(INTDIR)\GetRows.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\getrows.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GetRows - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GetRows_"
# PROP BASE Intermediate_Dir "GetRows_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL :   "$(OUTDIR)\getrows.exe" "$(OUTDIR)\getrows.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Fr /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/getrows.pch"\
 /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GetRows.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/getrows.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\getrdlg.sbr" \
	"$(INTDIR)\getrows.sbr" \
	"$(INTDIR)\stdafx.sbr"

"$(OUTDIR)\getrows.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 adoid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/getrows.pdb" /debug /machine:I386 /out:"$(OUTDIR)/getrows.exe" 
LINK32_OBJS= \
	"$(INTDIR)\getrdlg.obj" \
	"$(INTDIR)\getrows.obj" \
	"$(INTDIR)\GetRows.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\getrows.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GetRows_"
# PROP BASE Intermediate_Dir "GetRows_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
OUTDIR=.\debug
INTDIR=.\debug

ALL :  "$(OUTDIR)\getrows.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/getrows.pch" /YX /Fo"$(INTDIR)/"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GetRows.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/getrows.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 adoid.lib /nologo /subsystem:windows /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/getrows.pdb" /debug /machine:ALPHA /out:"$(OUTDIR)/getrows.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\getrdlg.obj" \
	"$(INTDIR)\getrows.obj" \
	"$(INTDIR)\GetRows.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\getrows.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GetRows0"
# PROP BASE Intermediate_Dir "GetRows0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Target_Dir ""
OUTDIR=.\retail
INTDIR=.\retail

ALL :  "$(OUTDIR)\getrows.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/getrows.pch" /YX /Fo"$(INTDIR)/" /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GetRows.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/getrows.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 adoid.lib /nologo /subsystem:windows /machine:ALPHA
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/getrows.pdb" /machine:ALPHA /out:"$(OUTDIR)/getrows.exe" 
LINK32_OBJS= \
	"$(INTDIR)\getrdlg.obj" \
	"$(INTDIR)\getrows.obj" \
	"$(INTDIR)\GetRows.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\getrows.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GetRows_"
# PROP BASE Intermediate_Dir "GetRows_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "retail"
# PROP Intermediate_Dir "retail"
# PROP Target_Dir ""
OUTDIR=.\retail
INTDIR=.\retail

ALL : "$(OUTDIR)\getrows.exe"

CLEAN : 
	-@erase "$(INTDIR)\getrdlg.obj"
	-@erase "$(INTDIR)\getrows.obj"
	-@erase "$(INTDIR)\GetRows.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(OUTDIR)\getrows.exe"

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
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/getrows.pch" /YX /Fo"$(INTDIR)/" /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GetRows.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/getrows.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:PPC
# ADD LINK32 adoid.lib /nologo /subsystem:windows /machine:PPC
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /pdb:"$(OUTDIR)/getrows.pdb"\
 /machine:PPC /out:"$(OUTDIR)/getrows.exe" 
LINK32_OBJS= \
	"$(INTDIR)\getrdlg.obj" \
	"$(INTDIR)\getrows.obj" \
	"$(INTDIR)\GetRows.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\getrows.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GetRows0"
# PROP BASE Intermediate_Dir "GetRows0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
OUTDIR=.\debug
INTDIR=.\debug

ALL : "$(OUTDIR)\getrows.exe"

CLEAN : 
	-@erase "$(INTDIR)\getrdlg.obj"
	-@erase "$(INTDIR)\getrows.obj"
	-@erase "$(INTDIR)\GetRows.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\getrows.exe"
	-@erase "$(OUTDIR)\getrows.pdb"

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
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/getrows.pch" /YX /Fo"$(INTDIR)/"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GetRows.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/getrows.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:PPC
# ADD LINK32 adoid.lib /nologo /subsystem:windows /debug /machine:PPC
LINK32_FLAGS=adoid.lib /nologo /subsystem:windows /pdb:"$(OUTDIR)/getrows.pdb"\
 /debug /machine:PPC /out:"$(OUTDIR)/getrows.exe" 
LINK32_OBJS= \
	"$(INTDIR)\getrdlg.obj" \
	"$(INTDIR)\getrows.obj" \
	"$(INTDIR)\GetRows.res" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\getrows.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "GetRows - Win32 Release"
# Name "GetRows - Win32 Debug"
# Name "GetRows - Win32 (ALPHA) Debug"
# Name "GetRows - Win32 (ALPHA) Release"
# Name "GetRows - Win32 (PPC) Release"
# Name "GetRows - Win32 (PPC) Debug"

!IF  "$(CFG)" == "GetRows - Win32 Release"

!ELSEIF  "$(CFG)" == "GetRows - Win32 Debug"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Release"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\getrdlg.cpp

!IF  "$(CFG)" == "GetRows - Win32 Release"

"$(INTDIR)\getrdlg.obj" : $(SOURCE) $(DEP_CPP_GETRD) "$(INTDIR)"

"$(INTDIR)\getrdlg.sbr" : $(SOURCE) $(DEP_CPP_GETRD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 Debug"

DEP_CPP_GETRD=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	

"$(INTDIR)\getrdlg.obj" : $(SOURCE) $(DEP_CPP_GETRD) "$(INTDIR)"

"$(INTDIR)\getrdlg.sbr" : $(SOURCE) $(DEP_CPP_GETRD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Debug"

DEP_CPP_GETRD=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	

"$(INTDIR)\getrdlg.obj" : $(SOURCE) $(DEP_CPP_GETRD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Release"

DEP_CPP_GETRD=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	

"$(INTDIR)\getrdlg.obj" : $(SOURCE) $(DEP_CPP_GETRD) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Release"

DEP_CPP_GETRD=\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\getrdlg.obj" : $(SOURCE) $(DEP_CPP_GETRD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Debug"

DEP_CPP_GETRD=\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\getrdlg.obj" : $(SOURCE) $(DEP_CPP_GETRD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\getrows.cpp

!IF  "$(CFG)" == "GetRows - Win32 Release"

"$(INTDIR)\getrows.obj" : $(SOURCE) $(DEP_CPP_GETRO) "$(INTDIR)"

"$(INTDIR)\getrows.sbr" : $(SOURCE) $(DEP_CPP_GETRO) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 Debug"

DEP_CPP_GETRO=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	

"$(INTDIR)\getrows.obj" : $(SOURCE) $(DEP_CPP_GETRO) "$(INTDIR)"

"$(INTDIR)\getrows.sbr" : $(SOURCE) $(DEP_CPP_GETRO) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Debug"

DEP_CPP_GETRO=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	

"$(INTDIR)\getrows.obj" : $(SOURCE) $(DEP_CPP_GETRO) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Release"

DEP_CPP_GETRO=\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	

"$(INTDIR)\getrows.obj" : $(SOURCE) $(DEP_CPP_GETRO) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Release"

DEP_CPP_GETRO=\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\getrows.obj" : $(SOURCE) $(DEP_CPP_GETRO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Debug"

DEP_CPP_GETRO=\
	".\getrdlg.h"\
	".\getrows.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\adoid.h"\
	{$(INCLUDE)}"\adoint.h"\
	

"$(INTDIR)\getrows.obj" : $(SOURCE) $(DEP_CPP_GETRO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "GetRows - Win32 Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

"$(INTDIR)\stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

"$(INTDIR)\stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GetRows.rc

!IF  "$(CFG)" == "GetRows - Win32 Release"

"$(INTDIR)\GetRows.res" : $(SOURCE) $(DEP_RSC_GETROW) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "GetRows - Win32 Debug"

DEP_RSC_GETROW=\
	".\res\getrows.ico"\
	".\res\getrows.rc2"\
	

"$(INTDIR)\GetRows.res" : $(SOURCE) $(DEP_RSC_GETROW) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Debug"

DEP_RSC_GETROW=\
	".\res\getrows.ico"\
	".\res\getrows.rc2"\
	

"$(INTDIR)\GetRows.res" : $(SOURCE) $(DEP_RSC_GETROW) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/GetRows.res" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "GetRows - Win32 (ALPHA) Release"

DEP_RSC_GETROW=\
	".\res\getrows.ico"\
	".\res\getrows.rc2"\
	

"$(INTDIR)\GetRows.res" : $(SOURCE) $(DEP_RSC_GETROW) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/GetRows.res" /d "NDEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Release"

DEP_RSC_GETROW=\
	".\res\getrows.ico"\
	".\res\getrows.rc2"\
	

"$(INTDIR)\GetRows.res" : $(SOURCE) $(DEP_RSC_GETROW) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/GetRows.res" /d "NDEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "GetRows - Win32 (PPC) Debug"

DEP_RSC_GETROW=\
	".\res\getrows.ico"\
	".\res\getrows.rc2"\
	

"$(INTDIR)\GetRows.res" : $(SOURCE) $(DEP_RSC_GETROW) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/GetRows.res" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
