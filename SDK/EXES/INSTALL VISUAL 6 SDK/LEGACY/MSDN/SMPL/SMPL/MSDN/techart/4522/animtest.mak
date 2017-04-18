# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (MIPS) Application" 0x0501
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=animtest - Win32 x86 Debug
!MESSAGE No configuration specified.  Defaulting to animtest - Win32 x86 Debug.
!ENDIF 

!IF "$(CFG)" != "animtest - Win32 x86 Release" && "$(CFG)" !=\
 "animtest - Win32 x86 Debug" && "$(CFG)" !=\
 "animtest - Win32 (MIPS) MIPS Release" && "$(CFG)" !=\
 "animtest - Win32 (MIPS) MIPS Debug" && "$(CFG)" !=\
 "animtest - Win32 (ALPHA) Alpha Debug" && "$(CFG)" !=\
 "animtest - Win32 (ALPHA) Alpha Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "animtest.mak" CFG="animtest - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "animtest - Win32 x86 Release" (based on "Win32 (x86) Application")
!MESSAGE "animtest - Win32 x86 Debug" (based on "Win32 (x86) Application")
!MESSAGE "animtest - Win32 (MIPS) MIPS Release" (based on\
 "Win32 (MIPS) Application")
!MESSAGE "animtest - Win32 (MIPS) MIPS Debug" (based on\
 "Win32 (MIPS) Application")
!MESSAGE "animtest - Win32 (ALPHA) Alpha Debug" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "animtest - Win32 (ALPHA) Alpha Release" (based on\
 "Win32 (ALPHA) Application")
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
# PROP Target_Last_Scanned "animtest - Win32 x86 Debug"

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : "$(OUTDIR)\animtest.exe"

CLEAN : 
	-@erase ".\x86-r\animtest.exe"
	-@erase ".\x86-r\animtest.obj"
	-@erase ".\x86-r\animtest.pch"
	-@erase ".\x86-r\animtvw.obj"
	-@erase ".\x86-r\recorddl.obj"
	-@erase ".\x86-r\animtdoc.obj"
	-@erase ".\x86-r\stdafx.obj"
	-@erase ".\x86-r\vudlg.obj"
	-@erase ".\x86-r\mainfrm.obj"
	-@erase ".\x86-r\animtest.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/"animtest.bsc" : $(OUTDIR)  $(BSC32_SBRS)
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /Ox /I "..\animate\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /Ox /I "..\animate\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /D "_X86_" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/animtest.pch"\
 /Yu"STDAFX.H" /Fo"$(INTDIR)/" /c 
CPP_OBJS=".\x86-r/"
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
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/animtest.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/animtest.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 nafxcw.lib olecli32.lib olesvr32.lib ..\animate\lib\animater.lib winmm.lib /nologo /subsystem:windows /machine:IX86
# ADD LINK32 ..\animate\lib\x86\animater.lib winmm.lib /nologo /subsystem:windows /machine:IX86
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\animate\lib\x86\animater.lib winmm.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/animtest.pdb" /machine:IX86\
 /out:"$(OUTDIR)/animtest.exe" 
LINK32_OBJS= \
	"$(INTDIR)/animtest.obj" \
	"$(INTDIR)/animtvw.obj" \
	"$(INTDIR)/recorddl.obj" \
	"$(INTDIR)/animtdoc.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/vudlg.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/animtest.res"

"$(OUTDIR)\animtest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : "$(OUTDIR)\animtest.exe"

CLEAN : 
	-@erase ".\x86-d\vc40.pdb"
	-@erase ".\x86-d\animtest.pch"
	-@erase ".\x86-d\animtest.exe"
	-@erase ".\x86-d\mainfrm.obj"
	-@erase ".\x86-d\vudlg.obj"
	-@erase ".\x86-d\stdafx.obj"
	-@erase ".\x86-d\animtvw.obj"
	-@erase ".\x86-d\animtest.obj"
	-@erase ".\x86-d\recorddl.obj"
	-@erase ".\x86-d\animtdoc.obj"
	-@erase ".\x86-d\animtest.res"
	-@erase ".\x86-d\animtest.ilk"
	-@erase ".\x86-d\animtest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/"animtest.bsc" : $(OUTDIR)  $(BSC32_SBRS)
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\animate\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\animate\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/animtest.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=".\x86-d/"
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
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/animtest.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/animtest.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 nafxcwd.lib olecli32.lib olesvr32.lib ..\animate\lib\animated.lib winmm.lib /nologo /subsystem:windows /debug /machine:IX86
# ADD LINK32 ..\animate\lib\x86\animated.lib winmm.lib /nologo /subsystem:windows /debug /machine:IX86
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\animate\lib\x86\animated.lib winmm.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/animtest.pdb" /debug\
 /machine:IX86 /out:"$(OUTDIR)/animtest.exe" 
LINK32_OBJS= \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/vudlg.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/animtvw.obj" \
	"$(INTDIR)/animtest.obj" \
	"$(INTDIR)/recorddl.obj" \
	"$(INTDIR)/animtdoc.obj" \
	"$(INTDIR)/animtest.res"

"$(OUTDIR)\animtest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MIPS_Ret"
# PROP BASE Intermediate_Dir "MIPS_Ret"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MIPS-r"
# PROP Intermediate_Dir "MIPS-r"
OUTDIR=.\MIPS-r
INTDIR=.\MIPS-r

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CLEAN : 
	-@erase 

CLEAN : 
	-@erase 

$(OUTDIR)/"animtest.bsc" : $(OUTDIR)  $(BSC32_SBRS)
MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /I "..\animate\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /I "..\animate\include" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"animtest.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\MIPS-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"animtest.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animtest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
# ADD LINK32 ..\animate\lib\mips\animater.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
LINK32_FLAGS=..\animate\lib\mips\animater.lib winmm.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"animtest.pdb" /MACHINE:MIPS\
 /OUT:$(OUTDIR)/"animtest.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"animtest.res" \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"animtest.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"animtdoc.obj" \
	$(INTDIR)/"animtvw.obj" \
	$(INTDIR)/"vudlg.obj" \
	$(INTDIR)/"recorddl.obj"

$(OUTDIR)/"animtest.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MIPS_Deb"
# PROP BASE Intermediate_Dir "MIPS_Deb"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MIPS-d"
# PROP Intermediate_Dir "MIPS-d"
OUTDIR=.\MIPS-d
INTDIR=.\MIPS-d

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CLEAN : 
	-@erase 

CLEAN : 
	-@erase 

$(OUTDIR)/"animtest.bsc" : $(OUTDIR)  $(BSC32_SBRS)
MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /I "..\animate\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /I "..\animate\include"\
 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"animtest.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"animtest.pdb" /c 
CPP_OBJS=".\MIPS-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"animtest.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animtest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
# ADD LINK32 ..\animate\lib\mips\animated.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
LINK32_FLAGS=..\animate\lib\mips\animated.lib winmm.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"animtest.pdb" /DEBUG /MACHINE:MIPS\
 /OUT:$(OUTDIR)/"animtest.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"animtest.res" \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"animtest.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"animtdoc.obj" \
	$(INTDIR)/"animtvw.obj" \
	$(INTDIR)/"vudlg.obj" \
	$(INTDIR)/"recorddl.obj"

$(OUTDIR)/"animtest.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Alpha_De"
# PROP BASE Intermediate_Dir "Alpha_De"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Alpha-d"
# PROP Intermediate_Dir "Alpha-d"
OUTDIR=.\Alpha-d
INTDIR=.\Alpha-d

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CLEAN : 
	-@erase 

CLEAN : 
	-@erase 

$(OUTDIR)/"animtest.bsc" : $(OUTDIR)  $(BSC32_SBRS)
MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"animtest.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"animtest.pdb" /c 
CPP_OBJS=".\Alpha-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"animtest.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animtest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
# ADD LINK32 ..\animate\lib\alpha\animated.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
LINK32_FLAGS=..\animate\lib\alpha\animated.lib winmm.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"animtest.pdb" /DEBUG /MACHINE:ALPHA\
 /OUT:$(OUTDIR)/"animtest.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"animtest.res" \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"animtest.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"animtdoc.obj" \
	$(INTDIR)/"animtvw.obj" \
	$(INTDIR)/"vudlg.obj" \
	$(INTDIR)/"recorddl.obj"

$(OUTDIR)/"animtest.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Alpha_Re"
# PROP BASE Intermediate_Dir "Alpha_Re"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Alpha-r"
# PROP Intermediate_Dir "Alpha-r"
OUTDIR=.\Alpha-r
INTDIR=.\Alpha-r

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CLEAN : 
	-@erase 

CLEAN : 
	-@erase 

$(OUTDIR)/"animtest.bsc" : $(OUTDIR)  $(BSC32_SBRS)
MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp$(OUTDIR)/"animtest.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\Alpha-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"animtest.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animtest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
# ADD LINK32 ..\animate\lib\alpha\animater.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
LINK32_FLAGS=..\animate\lib\alpha\animater.lib winmm.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"animtest.pdb" /MACHINE:ALPHA\
 /OUT:$(OUTDIR)/"animtest.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"animtest.res" \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"animtest.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"animtdoc.obj" \
	$(INTDIR)/"animtvw.obj" \
	$(INTDIR)/"vudlg.obj" \
	$(INTDIR)/"recorddl.obj"

$(OUTDIR)/"animtest.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "animtest - Win32 x86 Release"
# Name "animtest - Win32 x86 Debug"
# Name "animtest - Win32 (MIPS) MIPS Release"
# Name "animtest - Win32 (MIPS) MIPS Debug"
# Name "animtest - Win32 (ALPHA) Alpha Debug"
# Name "animtest - Win32 (ALPHA) Alpha Release"

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\animtest.rc

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

DEP_RSC_ANIMT=\
	".\res\animtest.ico"\
	".\res\toolbar.bmp"\
	".\res\animtest.rc2"\
	".\res\GUICRAP.WAV"\
	

"$(INTDIR)\animtest.res" : $(SOURCE) $(DEP_RSC_ANIMT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

DEP_RSC_ANIMT=\
	".\res\animtest.ico"\
	".\res\toolbar.bmp"\
	".\res\animtest.rc2"\
	".\res\GUICRAP.WAV"\
	

"$(INTDIR)\animtest.res" : $(SOURCE) $(DEP_RSC_ANIMT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

$(INTDIR)/"animtest.res" :  $(SOURCE)  $(DEP_ANIMT) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

DEP_ANIMT=\
	".\res\animtest.ico"\
	".\res\toolbar.bmp"\
	".\res\animtest.rc2"\
	

$(INTDIR)/"animtest.res" :  $(SOURCE)  $(DEP_ANIMT) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

$(INTDIR)/"animtest.res" :  $(SOURCE)  $(DEP_ANIMT) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

DEP_ANIMT=\
	".\res\animtest.ico"\
	".\res\toolbar.bmp"\
	".\res\animtest.rc2"\
	

$(INTDIR)/"animtest.res" :  $(SOURCE)  $(DEP_ANIMT) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	
# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /Ox /I "..\animate\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /D "_X86_" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/animtest.pch"\
 /Yc"STDAFX.H" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\animtest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	
# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\animate\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/animtest.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\animtest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

DEP_STDAF=\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

DEP_STDAF=\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\animtest.cpp

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

DEP_CPP_ANIMTE=\
	".\animtdoc.h"\
	".\animtest.h"\
	".\resource.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

"$(INTDIR)\animtest.obj" : $(SOURCE) $(DEP_CPP_ANIMTE) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

DEP_CPP_ANIMTE=\
	".\animtdoc.h"\
	".\animtest.h"\
	".\resource.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

"$(INTDIR)\animtest.obj" : $(SOURCE) $(DEP_CPP_ANIMTE) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ANIMTE) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

$(INTDIR)/"animtest.obj" :  $(SOURCE)  $(DEP_ANIMTE) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

DEP_ANIMTE=\
	".\stdafx.h"\
	".\animtest.h"\
	".\mainfrm.h"\
	".\animtdoc.h"\
	".\animtvw.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"animtest.obj" :  $(SOURCE)  $(DEP_ANIMTE) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

DEP_ANIMTE=\
	".\stdafx.h"\
	".\animtest.h"\
	".\mainfrm.h"\
	".\animtdoc.h"\
	".\animtvw.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"animtest.obj" :  $(SOURCE)  $(DEP_ANIMTE) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

DEP_ANIMTE=\
	".\stdafx.h"\
	".\animtest.h"\
	".\mainfrm.h"\
	".\animtdoc.h"\
	".\animtvw.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"animtest.obj" :  $(SOURCE)  $(DEP_ANIMTE) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

DEP_CPP_MAINF=\
	".\animtest.h"\
	".\resource.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

DEP_CPP_MAINF=\
	".\animtest.h"\
	".\resource.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

DEP_MAINF=\
	".\stdafx.h"\
	".\animtest.h"\
	".\mainfrm.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

DEP_MAINF=\
	".\stdafx.h"\
	".\animtest.h"\
	".\mainfrm.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\animtdoc.cpp

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

DEP_CPP_ANIMTD=\
	".\animtdoc.h"\
	".\animtest.h"\
	".\resource.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

"$(INTDIR)\animtdoc.obj" : $(SOURCE) $(DEP_CPP_ANIMTD) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

DEP_CPP_ANIMTD=\
	".\animtdoc.h"\
	".\animtest.h"\
	".\resource.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

"$(INTDIR)\animtdoc.obj" : $(SOURCE) $(DEP_CPP_ANIMTD) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ANIMTD) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

DEP_ANIMTD=\
	".\stdafx.h"\
	".\animtest.h"\
	".\animtvw.h"\
	".\animtdoc.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"animtdoc.obj" :  $(SOURCE)  $(DEP_ANIMTD) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

$(INTDIR)/"animtdoc.obj" :  $(SOURCE)  $(DEP_ANIMTD) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

DEP_ANIMTD=\
	".\stdafx.h"\
	".\animtest.h"\
	".\animtvw.h"\
	".\animtdoc.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"animtdoc.obj" :  $(SOURCE)  $(DEP_ANIMTD) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

DEP_ANIMTD=\
	".\stdafx.h"\
	".\animtest.h"\
	".\animtvw.h"\
	".\animtdoc.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"animtdoc.obj" :  $(SOURCE)  $(DEP_ANIMTD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\animtvw.cpp

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

DEP_CPP_ANIMTV=\
	".\animtdoc.h"\
	".\animtest.h"\
	".\resource.h"\
	".\recorddl.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	".\vudlg.h"\
	

"$(INTDIR)\animtvw.obj" : $(SOURCE) $(DEP_CPP_ANIMTV) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

DEP_CPP_ANIMTV=\
	".\animtdoc.h"\
	".\animtest.h"\
	".\resource.h"\
	".\recorddl.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	".\vudlg.h"\
	

"$(INTDIR)\animtvw.obj" : $(SOURCE) $(DEP_CPP_ANIMTV) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ANIMTV) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

$(INTDIR)/"animtvw.obj" :  $(SOURCE)  $(DEP_ANIMTV) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

DEP_ANIMTV=\
	".\stdafx.h"\
	".\animtest.h"\
	".\animtdoc.h"\
	".\animtvw.h"\
	".\vudlg.h"\
	".\recorddl.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"animtvw.obj" :  $(SOURCE)  $(DEP_ANIMTV) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

$(INTDIR)/"animtvw.obj" :  $(SOURCE)  $(DEP_ANIMTV) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

DEP_ANIMTV=\
	".\stdafx.h"\
	".\animtest.h"\
	".\animtdoc.h"\
	".\animtvw.h"\
	".\vudlg.h"\
	".\recorddl.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"animtvw.obj" :  $(SOURCE)  $(DEP_ANIMTV) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vudlg.cpp

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

DEP_CPP_VUDLG=\
	".\animtest.h"\
	".\resource.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	".\vudlg.h"\
	

"$(INTDIR)\vudlg.obj" : $(SOURCE) $(DEP_CPP_VUDLG) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

DEP_CPP_VUDLG=\
	".\animtest.h"\
	".\resource.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	".\vudlg.h"\
	

"$(INTDIR)\vudlg.obj" : $(SOURCE) $(DEP_CPP_VUDLG) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_VUDLG) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

$(INTDIR)/"vudlg.obj" :  $(SOURCE)  $(DEP_VUDLG) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

DEP_VUDLG=\
	".\stdafx.h"\
	".\animtest.h"\
	".\vudlg.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"vudlg.obj" :  $(SOURCE)  $(DEP_VUDLG) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

DEP_VUDLG=\
	".\stdafx.h"\
	".\animtest.h"\
	".\vudlg.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"vudlg.obj" :  $(SOURCE)  $(DEP_VUDLG) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

DEP_VUDLG=\
	".\stdafx.h"\
	".\animtest.h"\
	".\vudlg.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"vudlg.obj" :  $(SOURCE)  $(DEP_VUDLG) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\recorddl.cpp

!IF  "$(CFG)" == "animtest - Win32 x86 Release"

DEP_CPP_RECOR=\
	".\animtest.h"\
	".\resource.h"\
	".\recorddl.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

"$(INTDIR)\recorddl.obj" : $(SOURCE) $(DEP_CPP_RECOR) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 x86 Debug"

DEP_CPP_RECOR=\
	".\animtest.h"\
	".\resource.h"\
	".\recorddl.h"\
	".\stdafx.h"\
	".\..\animate\include\animate.h"\
	

"$(INTDIR)\recorddl.obj" : $(SOURCE) $(DEP_CPP_RECOR) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_RECOR) "$(INTDIR)"\
 "$(INTDIR)\animtest.pch"


!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Release"

DEP_RECOR=\
	".\stdafx.h"\
	".\animtest.h"\
	".\recorddl.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"recorddl.obj" :  $(SOURCE)  $(DEP_RECOR) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (MIPS) MIPS Debug"

$(INTDIR)/"recorddl.obj" :  $(SOURCE)  $(DEP_RECOR) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Debug"

DEP_RECOR=\
	".\stdafx.h"\
	".\animtest.h"\
	".\recorddl.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"recorddl.obj" :  $(SOURCE)  $(DEP_RECOR) $(INTDIR)

!ELSEIF  "$(CFG)" == "animtest - Win32 (ALPHA) Alpha Release"

DEP_RECOR=\
	".\stdafx.h"\
	".\animtest.h"\
	".\recorddl.h"\
	".\..\animate\include\animate.h"\
	

$(INTDIR)/"recorddl.obj" :  $(SOURCE)  $(DEP_RECOR) $(INTDIR)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
