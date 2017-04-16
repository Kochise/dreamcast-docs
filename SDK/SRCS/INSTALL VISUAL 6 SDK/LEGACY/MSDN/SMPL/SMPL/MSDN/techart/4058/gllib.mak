# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (MIPS) Dynamic-Link Library" 0x0502
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release" && "$(CFG)" !=\
 "MIPS Debug" && "$(CFG)" != "Alpha Release" && "$(CFG)" != "Alpha Debug" &&\
 "$(CFG)" != "MIPs Release" && "$(CFG)" != "Win32 Static Debug " && "$(CFG)" !=\
 "Win32 Static Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "GLlib.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MIPS Debug" (based on "Win32 (MIPS) Dynamic-Link Library")
!MESSAGE "Alpha Release" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Alpha Debug" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "MIPs Release" (based on "Win32 (MIPS) Dynamic-Link Library")
!MESSAGE "Win32 Static Debug " (based on "Win32 (x86) Static Library")
!MESSAGE "Win32 Static Release" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"

!IF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : ".\lib\x86\GLlib-d.dll" $(OUTDIR)/"GLlib.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"GLlib.pdb" /c 
CPP_OBJS=".\x86-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x0 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x0 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"GLlib.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GLlib.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"cgl.sbr" \
	$(INTDIR)/"cgl-pal.sbr" \
	$(INTDIR)/"cgl-help.sbr" \
	$(INTDIR)/"glview.sbr" \
	$(INTDIR)/"image.sbr" \
	$(INTDIR)/"GLlib.sbr"

$(OUTDIR)/"GLlib.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"GLlib.def" /IMPLIB:"GLlib.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 ..\animate\lib\x86\animated.lib opengl32.lib glu32.lib glaux.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /OUT:"lib\x86\GLlib-d.dll" /IMPLIB:"lib\x86\GLlib-d.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=..\animate\lib\x86\animated.lib opengl32.lib glu32.lib glaux.lib\
 winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"GLlib.pdb" /DEBUG /MACHINE:I386 /OUT:"lib\x86\GLlib-d.dll"\
 /IMPLIB:"lib\x86\GLlib-d.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"GLlib.res" \
	$(INTDIR)/"cgl.obj" \
	$(INTDIR)/"cgl-pal.obj" \
	$(INTDIR)/"cgl-help.obj" \
	$(INTDIR)/"glview.obj" \
	$(INTDIR)/"image.obj" \
	$(INTDIR)/"GLlib.obj"

".\lib\x86\GLlib-d.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : .\lib\x86\GLlib.dll $(OUTDIR)/"GLlib.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x0 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x0 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"GLlib.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GLlib.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"cgl.sbr" \
	$(INTDIR)/"cgl-pal.sbr" \
	$(INTDIR)/"cgl-help.sbr" \
	$(INTDIR)/"glview.sbr" \
	$(INTDIR)/"image.sbr" \
	$(INTDIR)/"GLlib.sbr"

$(OUTDIR)/"GLlib.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"GLlib.def" /IMPLIB:"GLlib.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 ..\animate\lib\x86\animater.lib opengl32.lib glu32.lib glaux.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"GLlib.def" /OUT:"lib\x86\GLlib.dll" /IMPLIB:"lib\x86\GLlib.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=..\animate\lib\x86\animater.lib opengl32.lib glu32.lib glaux.lib\
 winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"GLlib.pdb" /MACHINE:I386 /DEF:"GLlib.def"\
 /OUT:"lib\x86\GLlib.dll" /IMPLIB:"lib\x86\GLlib.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"GLlib.res" \
	$(INTDIR)/"cgl.obj" \
	$(INTDIR)/"cgl-pal.obj" \
	$(INTDIR)/"cgl-help.obj" \
	$(INTDIR)/"glview.obj" \
	$(INTDIR)/"image.obj" \
	$(INTDIR)/"GLlib.obj"

.\lib\x86\GLlib.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MIPS_Deb"
# PROP BASE Intermediate_Dir "MIPS_Deb"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MIPS-d"
# PROP Intermediate_Dir "MIPS-d"
OUTDIR=.\MIPS-d
INTDIR=.\MIPS-d

ALL : ".\lib\MIPS\GLlib-d.dll" $(OUTDIR)/""""""GLlib.bsc""""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"GLlib.pdb" /c 
CPP_OBJS=".\MIPS-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"GLlib.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GLlib.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"GLlib.sbr" \
	$(INTDIR)/"cgl.sbr" \
	$(INTDIR)/"cgl-pal.sbr" \
	$(INTDIR)/"cgl-help.sbr" \
	$(INTDIR)/"glview.sbr" \
	$(INTDIR)/"image.sbr"

$(OUTDIR)/"GLlib.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:MIPS
# ADD LINK32 winmm.lib opengl32.lib glu32.lib glaux.lib animated.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:MIPS /OUT:"lib\MIPS\GLlib-d.dll" /IMPLIB:"lib\MIPS\GLlib-d.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib opengl32.lib glu32.lib glaux.lib animated.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /PDB:$(OUTDIR)/"GLlib.pdb" /DEBUG /MACHINE:MIPS\
 /OUT:"lib\MIPS\GLlib-d.dll" /IMPLIB:"lib\MIPS\GLlib-d.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"GLlib.obj" \
	$(INTDIR)/"GLlib.res" \
	$(INTDIR)/"cgl.obj" \
	$(INTDIR)/"cgl-pal.obj" \
	$(INTDIR)/"cgl-help.obj" \
	$(INTDIR)/"glview.obj" \
	$(INTDIR)/"image.obj"

".\lib\MIPS\GLlib-d.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Alpha Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Alpha_R0"
# PROP BASE Intermediate_Dir "Alpha_R0"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Alpha-r"
# PROP Intermediate_Dir "Alpha-r"
OUTDIR=.\Alpha-r
INTDIR=.\Alpha-r

ALL : .\lib\Alpha\GLlib.dll $(OUTDIR)/"""""""GLlib.bsc"""""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXEXT" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Fo$(INTDIR)/ /c\
 
CPP_OBJS=".\Alpha-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"GLlib.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GLlib.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"GLlib.sbr" \
	$(INTDIR)/"cgl.sbr" \
	$(INTDIR)/"cgl-pal.sbr" \
	$(INTDIR)/"cgl-help.sbr" \
	$(INTDIR)/"glview.sbr" \
	$(INTDIR)/"image.sbr"

$(OUTDIR)/"GLlib.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:ALPHA
# ADD LINK32 animater.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:ALPHA /OUT:"lib/Alpha/GLlib.dll" /IMPLIB:"lib/Alpha/GLlib.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=animater.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /PDB:$(OUTDIR)/"GLlib.pdb" /MACHINE:ALPHA\
 /OUT:"lib/Alpha/GLlib.dll" /IMPLIB:"lib/Alpha/GLlib.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"GLlib.obj" \
	$(INTDIR)/"GLlib.res" \
	$(INTDIR)/"cgl.obj" \
	$(INTDIR)/"cgl-pal.obj" \
	$(INTDIR)/"cgl-help.obj" \
	$(INTDIR)/"glview.obj" \
	$(INTDIR)/"image.obj"

.\lib\Alpha\GLlib.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Alpha Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Alpha_De"
# PROP BASE Intermediate_Dir "Alpha_De"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Alpha-d"
# PROP Intermediate_Dir "Alpha-d"
OUTDIR=.\Alpha-d
INTDIR=.\Alpha-d

ALL : ".\lib\Alpha\GLlib-d.dll" $(OUTDIR)/"""""""GLlib.bsc"""""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /Zi /YX /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /Zi /YX /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"GLlib.pdb" /c 
CPP_OBJS=".\Alpha-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"GLlib.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GLlib.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"GLlib.sbr" \
	$(INTDIR)/"cgl.sbr" \
	$(INTDIR)/"cgl-pal.sbr" \
	$(INTDIR)/"cgl-help.sbr" \
	$(INTDIR)/"glview.sbr" \
	$(INTDIR)/"image.sbr"

$(OUTDIR)/"GLlib.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:ALPHA
# ADD LINK32 animated.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:ALPHA /OUT:"lib/Alpha/GLlib-d.dll" /IMPLIB:"lib/Alpha/GLlib-d.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=animated.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /PDB:$(OUTDIR)/"GLlib.pdb" /DEBUG /MACHINE:ALPHA\
 /OUT:"lib/Alpha/GLlib-d.dll" /IMPLIB:"lib/Alpha/GLlib-d.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"GLlib.obj" \
	$(INTDIR)/"GLlib.res" \
	$(INTDIR)/"cgl.obj" \
	$(INTDIR)/"cgl-pal.obj" \
	$(INTDIR)/"cgl-help.obj" \
	$(INTDIR)/"glview.obj" \
	$(INTDIR)/"image.obj"

".\lib\Alpha\GLlib-d.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPs Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MIPs_Rel"
# PROP BASE Intermediate_Dir "MIPs_Rel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MIPs-r"
# PROP Intermediate_Dir "MIPs-r"
OUTDIR=.\MIPs-r
INTDIR=.\MIPs-r

ALL : .\lib\MIPs\GLlib.dll $(OUTDIR)/""""""GLlib.bsc""""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\MIPs-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"GLlib.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GLlib.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"GLlib.sbr" \
	$(INTDIR)/"cgl.sbr" \
	$(INTDIR)/"cgl-pal.sbr" \
	$(INTDIR)/"cgl-help.sbr" \
	$(INTDIR)/"glview.sbr" \
	$(INTDIR)/"image.sbr"

$(OUTDIR)/"GLlib.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:MIPS
# ADD LINK32 winmm.lib opengl32.lib glu32.lib glaux.lib animater.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:MIPS /OUT:"lib/MIPs/GLlib.dll" /IMPLIB:"lib/MIPs/GLlib.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib opengl32.lib glu32.lib glaux.lib animater.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /PDB:$(OUTDIR)/"GLlib.pdb" /MACHINE:MIPS\
 /OUT:"lib/MIPs/GLlib.dll" /IMPLIB:"lib/MIPs/GLlib.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"GLlib.obj" \
	$(INTDIR)/"GLlib.res" \
	$(INTDIR)/"cgl.obj" \
	$(INTDIR)/"cgl-pal.obj" \
	$(INTDIR)/"cgl-help.obj" \
	$(INTDIR)/"glview.obj" \
	$(INTDIR)/"image.obj"

.\lib\MIPs\GLlib.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_St"
# PROP BASE Intermediate_Dir "Win32_St"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d-static"
# PROP Intermediate_Dir "x86-d-static"
OUTDIR=.\x86-d-static
INTDIR=.\x86-d-static

ALL : ".\lib\x86\GLlib-s-d.lib" $(OUTDIR)/"GLlib.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-d-static/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GLlib.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"cgl.sbr" \
	$(INTDIR)/"cgl-pal.sbr" \
	$(INTDIR)/"cgl-help.sbr" \
	$(INTDIR)/"glview.sbr" \
	$(INTDIR)/"image.sbr"

$(OUTDIR)/"GLlib.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"lib\x86\GLlib-s-d.lib"
LIB32_FLAGS=/NOLOGO /OUT:"lib\x86\GLlib-s-d.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"cgl.obj" \
	$(INTDIR)/"cgl-pal.obj" \
	$(INTDIR)/"cgl-help.obj" \
	$(INTDIR)/"glview.obj" \
	$(INTDIR)/"image.obj"

".\lib\x86\GLlib-s-d.lib" : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Static Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32_S0"
# PROP BASE Intermediate_Dir "Win32_S0"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r-static"
# PROP Intermediate_Dir "x86-r-static"
OUTDIR=.\x86-r-static
INTDIR=.\x86-r-static

ALL : ".\lib\x86\GLlib-s.lib" $(OUTDIR)/"GLlib.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r-static/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GLlib.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"cgl.sbr" \
	$(INTDIR)/"cgl-pal.sbr" \
	$(INTDIR)/"cgl-help.sbr" \
	$(INTDIR)/"glview.sbr" \
	$(INTDIR)/"image.sbr"

$(OUTDIR)/"GLlib.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"lib\x86\GLlib-s.lib"
LIB32_FLAGS=/NOLOGO /OUT:"lib\x86\GLlib-s.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"cgl.obj" \
	$(INTDIR)/"cgl-pal.obj" \
	$(INTDIR)/"cgl-help.obj" \
	$(INTDIR)/"glview.obj" \
	$(INTDIR)/"image.obj"

".\lib\x86\GLlib-s.lib" : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_STDAF=\
	.\stdafx.h

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"GLlib.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Static Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GLlib.rc
DEP_GLLIB=\
	.\res\GLlib.rc2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"GLlib.res" :  $(SOURCE)  $(DEP_GLLIB) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"GLlib.res" :  $(SOURCE)  $(DEP_GLLIB) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"GLlib.res" :  $(SOURCE)  $(DEP_GLLIB) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"GLlib.res" :  $(SOURCE)  $(DEP_GLLIB) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"GLlib.res" :  $(SOURCE)  $(DEP_GLLIB) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"GLlib.res" :  $(SOURCE)  $(DEP_GLLIB) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

!ELSEIF  "$(CFG)" == "Win32 Static Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\cgl.cpp
DEP_CGL_C=\
	.\stdafx.h\
	.\cgl.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\DEV\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"cgl.obj" :  $(SOURCE)  $(DEP_CGL_C) $(INTDIR) $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"cgl.obj" :  $(SOURCE)  $(DEP_CGL_C) $(INTDIR) $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"cgl.obj" :  $(SOURCE)  $(DEP_CGL_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"cgl.obj" :  $(SOURCE)  $(DEP_CGL_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"cgl.obj" :  $(SOURCE)  $(DEP_CGL_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"cgl.obj" :  $(SOURCE)  $(DEP_CGL_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

$(INTDIR)/"cgl.obj" :  $(SOURCE)  $(DEP_CGL_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Release"

$(INTDIR)/"cgl.obj" :  $(SOURCE)  $(DEP_CGL_C) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\cgl-pal.cpp"

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"cgl-pal.obj" :  $(SOURCE)  $(INTDIR) $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"cgl-pal.obj" :  $(SOURCE)  $(INTDIR) $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"cgl-pal.obj" :  $(SOURCE)  $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"cgl-pal.obj" :  $(SOURCE)  $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"cgl-pal.obj" :  $(SOURCE)  $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"cgl-pal.obj" :  $(SOURCE)  $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

$(INTDIR)/"cgl-pal.obj" :  $(SOURCE)  $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Release"

$(INTDIR)/"cgl-pal.obj" :  $(SOURCE)  $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\cgl-help.cpp"
DEP_CGL_H=\
	.\stdafx.h\
	.\cgl.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\DEV\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"cgl-help.obj" :  $(SOURCE)  $(DEP_CGL_H) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"cgl-help.obj" :  $(SOURCE)  $(DEP_CGL_H) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"cgl-help.obj" :  $(SOURCE)  $(DEP_CGL_H) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"cgl-help.obj" :  $(SOURCE)  $(DEP_CGL_H) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"cgl-help.obj" :  $(SOURCE)  $(DEP_CGL_H) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"cgl-help.obj" :  $(SOURCE)  $(DEP_CGL_H) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

$(INTDIR)/"cgl-help.obj" :  $(SOURCE)  $(DEP_CGL_H) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Release"

$(INTDIR)/"cgl-help.obj" :  $(SOURCE)  $(DEP_CGL_H) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\glview.cpp
DEP_GLVIE=\
	.\stdafx.h\
	.\cgl.h\
	.\glview.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\DEV\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"glview.obj" :  $(SOURCE)  $(DEP_GLVIE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"glview.obj" :  $(SOURCE)  $(DEP_GLVIE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"glview.obj" :  $(SOURCE)  $(DEP_GLVIE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"glview.obj" :  $(SOURCE)  $(DEP_GLVIE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"glview.obj" :  $(SOURCE)  $(DEP_GLVIE) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"glview.obj" :  $(SOURCE)  $(DEP_GLVIE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

$(INTDIR)/"glview.obj" :  $(SOURCE)  $(DEP_GLVIE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Release"

$(INTDIR)/"glview.obj" :  $(SOURCE)  $(DEP_GLVIE) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\image.cpp
DEP_IMAGE=\
	.\stdafx.h\
	.\cgl.h\
	.\image.h\
	..\animate\include\animate.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\DEV\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR) $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR) $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Static Release"

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GLlib.cpp
DEP_GLLIB_=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\DEV\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"GLlib.obj" :  $(SOURCE)  $(DEP_GLLIB_) $(INTDIR)\
 $(INTDIR)/stdafx.obj
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"GLlib.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"GLlib.obj" :  $(SOURCE)  $(DEP_GLLIB_) $(INTDIR)\
 $(INTDIR)/stdafx.obj
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"GLlib.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPS Debug"

!ELSEIF  "$(CFG)" == "Alpha Release"

!ELSEIF  "$(CFG)" == "Alpha Debug"

!ELSEIF  "$(CFG)" == "MIPs Release"

!ELSEIF  "$(CFG)" == "Win32 Static Debug "

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Win32 Static Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
