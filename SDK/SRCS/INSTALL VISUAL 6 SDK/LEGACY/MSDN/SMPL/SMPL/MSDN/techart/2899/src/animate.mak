# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (ALPHA) Static Library" 0x0604
# TARGTYPE "Win32 (MIPS) Static Library" 0x0504
# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=x86 Debug
!MESSAGE No configuration specified.  Defaulting to x86 Debug.
!ENDIF 

!IF "$(CFG)" != "x86 Release" && "$(CFG)" != "x86 Debug" && "$(CFG)" !=\
 "MIPS Release" && "$(CFG)" != "MIPS Debug" && "$(CFG)" != "Alpha Release" &&\
 "$(CFG)" != "Alpha Debug" && "$(CFG)" != "x86 Static Debug" && "$(CFG)" !=\
 "x86 Static Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "animate.mak" CFG="x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "x86 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "x86 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "MIPS Release" (based on "Win32 (MIPS) Static Library")
!MESSAGE "MIPS Debug" (based on "Win32 (MIPS) Static Library")
!MESSAGE "Alpha Release" (based on "Win32 (ALPHA) Static Library")
!MESSAGE "Alpha Debug" (based on "Win32 (ALPHA) Static Library")
!MESSAGE "x86 Static Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "x86 Static Release" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "x86 Static Debug"

!IF  "$(CFG)" == "x86 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : \apps\animate\lib\x86\animater.lib $(OUTDIR)/"animate.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /YX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /YX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"animate.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animate.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/"animate.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"..\lib\x86\animater.lib"
LIB32_FLAGS=/NOLOGO /OUT:"..\lib\x86\animater.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"splstno.obj" \
	$(INTDIR)/"phsprite.obj" \
	$(INTDIR)/"osbview.obj" \
	$(INTDIR)/"dibsurf.obj" \
	$(INTDIR)/"vumeter.obj" \
	$(INTDIR)/"waveidev.obj" \
	$(INTDIR)/"sprite.obj" \
	$(INTDIR)/"spritlst.obj" \
	$(INTDIR)/"mciobj.obj" \
	$(INTDIR)/"dibpal.obj" \
	$(INTDIR)/"dib.obj" \
	$(INTDIR)/"sound.obj" \
	$(INTDIR)/"wave.obj" \
	$(INTDIR)/"meter.obj" \
	$(INTDIR)/"waveodev.obj" \
	$(INTDIR)/"transbmp.obj"

\apps\animate\lib\x86\animater.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "x86 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : \apps\animate\lib\x86\animated.lib $(OUTDIR)/"animate.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /Z7 /YX /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /Z7 /YX /Od /I "..\include" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"animate.pch" /Fo$(INTDIR)/\
 /c 
CPP_OBJS=".\x86-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animate.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/"animate.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"..\lib\x86\animated.lib"
LIB32_FLAGS=/NOLOGO /OUT:"..\lib\x86\animated.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"splstno.obj" \
	$(INTDIR)/"phsprite.obj" \
	$(INTDIR)/"osbview.obj" \
	$(INTDIR)/"dibsurf.obj" \
	$(INTDIR)/"vumeter.obj" \
	$(INTDIR)/"waveidev.obj" \
	$(INTDIR)/"sprite.obj" \
	$(INTDIR)/"spritlst.obj" \
	$(INTDIR)/"mciobj.obj" \
	$(INTDIR)/"dibpal.obj" \
	$(INTDIR)/"dib.obj" \
	$(INTDIR)/"sound.obj" \
	$(INTDIR)/"wave.obj" \
	$(INTDIR)/"meter.obj" \
	$(INTDIR)/"waveodev.obj" \
	$(INTDIR)/"transbmp.obj"

\apps\animate\lib\x86\animated.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MIPS_Rel"
# PROP BASE Intermediate_Dir "MIPS_Rel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "mips-r"
# PROP Intermediate_Dir "mips-r"
OUTDIR=.\mips-r
INTDIR=.\mips-r

ALL : \animate\lib\mips\animater.lib $(OUTDIR)/""""""""animate.bsc""""""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /I "..\include" /D "WIN32"\
 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"animate.pch" /Fo$(INTDIR)/\
 /c 
CPP_OBJS=".\mips-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"animate.bsc" : $(OUTDIR)  $(BSC32_SBRS)
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animate.bsc" 
BSC32_SBRS= \
	
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"..\lib\mips\animater.lib"
LIB32_FLAGS=/NOLOGO /OUT:"..\lib\mips\animater.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"splstno.obj" \
	$(INTDIR)/"phsprite.obj" \
	$(INTDIR)/"osbview.obj" \
	$(INTDIR)/"dibsurf.obj" \
	$(INTDIR)/"vumeter.obj" \
	$(INTDIR)/"waveidev.obj" \
	$(INTDIR)/"sprite.obj" \
	$(INTDIR)/"spritlst.obj" \
	$(INTDIR)/"mciobj.obj" \
	$(INTDIR)/"dibpal.obj" \
	$(INTDIR)/"dib.obj" \
	$(INTDIR)/"sound.obj" \
	$(INTDIR)/"wave.obj" \
	$(INTDIR)/"meter.obj" \
	$(INTDIR)/"waveodev.obj" \
	$(INTDIR)/"transbmp.obj"

\animate\lib\mips\animater.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MIPS_Deb"
# PROP BASE Intermediate_Dir "MIPS_Deb"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "mips-d"
# PROP Intermediate_Dir "mips-d"
OUTDIR=.\mips-d
INTDIR=.\mips-d

ALL : \animate\lib\mips\animated.lib $(OUTDIR)/""""""""animate.bsc""""""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /Z7 /YX /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /Z7 /YX /Od /I "..\include" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"animate.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\mips-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"animate.bsc" : $(OUTDIR)  $(BSC32_SBRS)
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animate.bsc" 
BSC32_SBRS= \
	
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"..\lib\mips\animated.lib"
LIB32_FLAGS=/NOLOGO /OUT:"..\lib\mips\animated.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"splstno.obj" \
	$(INTDIR)/"phsprite.obj" \
	$(INTDIR)/"osbview.obj" \
	$(INTDIR)/"dibsurf.obj" \
	$(INTDIR)/"vumeter.obj" \
	$(INTDIR)/"waveidev.obj" \
	$(INTDIR)/"sprite.obj" \
	$(INTDIR)/"spritlst.obj" \
	$(INTDIR)/"mciobj.obj" \
	$(INTDIR)/"dibpal.obj" \
	$(INTDIR)/"dib.obj" \
	$(INTDIR)/"sound.obj" \
	$(INTDIR)/"wave.obj" \
	$(INTDIR)/"meter.obj" \
	$(INTDIR)/"waveodev.obj" \
	$(INTDIR)/"transbmp.obj"

\animate\lib\mips\animated.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Alpha Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Alpha_Re"
# PROP BASE Intermediate_Dir "Alpha_Re"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Alpha-r"
# PROP Intermediate_Dir "Alpha-r"
OUTDIR=.\Alpha-r
INTDIR=.\Alpha-r

ALL : \animate\lib\Alpha\animater.lib $(OUTDIR)/""""animate.bsc""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /YX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /YX /O2 /I "..\include" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"animate.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\Alpha-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"animate.bsc" : $(OUTDIR)  $(BSC32_SBRS)
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animate.bsc" 
BSC32_SBRS= \
	
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"..\lib\Alpha\animater.lib"
LIB32_FLAGS=/NOLOGO /OUT:"..\lib\Alpha\animater.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"splstno.obj" \
	$(INTDIR)/"phsprite.obj" \
	$(INTDIR)/"osbview.obj" \
	$(INTDIR)/"dibsurf.obj" \
	$(INTDIR)/"vumeter.obj" \
	$(INTDIR)/"waveidev.obj" \
	$(INTDIR)/"sprite.obj" \
	$(INTDIR)/"spritlst.obj" \
	$(INTDIR)/"mciobj.obj" \
	$(INTDIR)/"dibpal.obj" \
	$(INTDIR)/"dib.obj" \
	$(INTDIR)/"sound.obj" \
	$(INTDIR)/"wave.obj" \
	$(INTDIR)/"meter.obj" \
	$(INTDIR)/"waveodev.obj" \
	$(INTDIR)/"transbmp.obj"

\animate\lib\Alpha\animater.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

ALL : \animate\lib\Alpha\animated.lib $(OUTDIR)/""""animate.bsc""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /Z7 /YX /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /Z7 /YX /Od /I "..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"animate.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\Alpha-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"animate.bsc" : $(OUTDIR)  $(BSC32_SBRS)
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animate.bsc" 
BSC32_SBRS= \
	
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"..\lib\Alpha\animated.lib"
LIB32_FLAGS=/NOLOGO /OUT:"..\lib\Alpha\animated.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"splstno.obj" \
	$(INTDIR)/"phsprite.obj" \
	$(INTDIR)/"osbview.obj" \
	$(INTDIR)/"dibsurf.obj" \
	$(INTDIR)/"vumeter.obj" \
	$(INTDIR)/"waveidev.obj" \
	$(INTDIR)/"sprite.obj" \
	$(INTDIR)/"spritlst.obj" \
	$(INTDIR)/"mciobj.obj" \
	$(INTDIR)/"dibpal.obj" \
	$(INTDIR)/"dib.obj" \
	$(INTDIR)/"sound.obj" \
	$(INTDIR)/"wave.obj" \
	$(INTDIR)/"meter.obj" \
	$(INTDIR)/"waveodev.obj" \
	$(INTDIR)/"transbmp.obj"

\animate\lib\Alpha\animated.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "x86 Static Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "x86_Stat"
# PROP BASE Intermediate_Dir "x86_Stat"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-sd"
# PROP Intermediate_Dir "x86-sd"
OUTDIR=.\x86-sd
INTDIR=.\x86-sd

ALL : \apps\animate\lib\x86\animatesd.lib $(OUTDIR)/"animate.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Z7 /YX /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GX /Z7 /YX /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /Z7 /YX /Od /I "..\include" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"animate.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-sd/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animate.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/"animate.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO /OUT:"..\lib\x86\animated.lib"
# ADD LIB32 /NOLOGO /OUT:"..\lib\x86\animatesd.lib"
LIB32_FLAGS=/NOLOGO /OUT:"..\lib\x86\animatesd.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"splstno.obj" \
	$(INTDIR)/"phsprite.obj" \
	$(INTDIR)/"osbview.obj" \
	$(INTDIR)/"dibsurf.obj" \
	$(INTDIR)/"vumeter.obj" \
	$(INTDIR)/"waveidev.obj" \
	$(INTDIR)/"sprite.obj" \
	$(INTDIR)/"spritlst.obj" \
	$(INTDIR)/"mciobj.obj" \
	$(INTDIR)/"dibpal.obj" \
	$(INTDIR)/"dib.obj" \
	$(INTDIR)/"sound.obj" \
	$(INTDIR)/"wave.obj" \
	$(INTDIR)/"meter.obj" \
	$(INTDIR)/"waveodev.obj" \
	$(INTDIR)/"transbmp.obj"

\apps\animate\lib\x86\animatesd.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "x86 Static Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x86_Stat"
# PROP BASE Intermediate_Dir "x86_Stat"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-sr"
# PROP Intermediate_Dir "x86-sr"
OUTDIR=.\x86-sr
INTDIR=.\x86-sr

ALL : \apps\animate\lib\x86\animatesr.lib $(OUTDIR)/"animate.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /YX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GX /YX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /YX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"animate.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-sr/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"animate.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/"animate.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO /OUT:"..\lib\x86\animater.lib"
# ADD LIB32 /NOLOGO /OUT:"..\lib\x86\animatesr.lib"
LIB32_FLAGS=/NOLOGO /OUT:"..\lib\x86\animatesr.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"splstno.obj" \
	$(INTDIR)/"phsprite.obj" \
	$(INTDIR)/"osbview.obj" \
	$(INTDIR)/"dibsurf.obj" \
	$(INTDIR)/"vumeter.obj" \
	$(INTDIR)/"waveidev.obj" \
	$(INTDIR)/"sprite.obj" \
	$(INTDIR)/"spritlst.obj" \
	$(INTDIR)/"mciobj.obj" \
	$(INTDIR)/"dibpal.obj" \
	$(INTDIR)/"dib.obj" \
	$(INTDIR)/"sound.obj" \
	$(INTDIR)/"wave.obj" \
	$(INTDIR)/"meter.obj" \
	$(INTDIR)/"waveodev.obj" \
	$(INTDIR)/"transbmp.obj"

\apps\animate\lib\x86\animatesr.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
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

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\splstno.cpp
DEP_SPLST=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"splstno.obj" :  $(SOURCE)  $(DEP_SPLST) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"splstno.obj" :  $(SOURCE)  $(DEP_SPLST) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"splstno.obj" :  $(SOURCE)  $(DEP_SPLST) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"splstno.obj" :  $(SOURCE)  $(DEP_SPLST) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"splstno.obj" :  $(SOURCE)  $(DEP_SPLST) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"splstno.obj" :  $(SOURCE)  $(DEP_SPLST) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"splstno.obj" :  $(SOURCE)  $(DEP_SPLST) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"splstno.obj" :  $(SOURCE)  $(DEP_SPLST) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\phsprite.cpp
DEP_PHSPR=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"phsprite.obj" :  $(SOURCE)  $(DEP_PHSPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"phsprite.obj" :  $(SOURCE)  $(DEP_PHSPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"phsprite.obj" :  $(SOURCE)  $(DEP_PHSPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"phsprite.obj" :  $(SOURCE)  $(DEP_PHSPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"phsprite.obj" :  $(SOURCE)  $(DEP_PHSPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"phsprite.obj" :  $(SOURCE)  $(DEP_PHSPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"phsprite.obj" :  $(SOURCE)  $(DEP_PHSPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"phsprite.obj" :  $(SOURCE)  $(DEP_PHSPR) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\osbview.cpp
DEP_OSBVI=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"osbview.obj" :  $(SOURCE)  $(DEP_OSBVI) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"osbview.obj" :  $(SOURCE)  $(DEP_OSBVI) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"osbview.obj" :  $(SOURCE)  $(DEP_OSBVI) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"osbview.obj" :  $(SOURCE)  $(DEP_OSBVI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"osbview.obj" :  $(SOURCE)  $(DEP_OSBVI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"osbview.obj" :  $(SOURCE)  $(DEP_OSBVI) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"osbview.obj" :  $(SOURCE)  $(DEP_OSBVI) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"osbview.obj" :  $(SOURCE)  $(DEP_OSBVI) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dibsurf.cpp
DEP_DIBSU=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"dibsurf.obj" :  $(SOURCE)  $(DEP_DIBSU) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"dibsurf.obj" :  $(SOURCE)  $(DEP_DIBSU) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"dibsurf.obj" :  $(SOURCE)  $(DEP_DIBSU) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"dibsurf.obj" :  $(SOURCE)  $(DEP_DIBSU) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"dibsurf.obj" :  $(SOURCE)  $(DEP_DIBSU) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"dibsurf.obj" :  $(SOURCE)  $(DEP_DIBSU) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"dibsurf.obj" :  $(SOURCE)  $(DEP_DIBSU) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"dibsurf.obj" :  $(SOURCE)  $(DEP_DIBSU) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vumeter.cpp
DEP_VUMET=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"vumeter.obj" :  $(SOURCE)  $(DEP_VUMET) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"vumeter.obj" :  $(SOURCE)  $(DEP_VUMET) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"vumeter.obj" :  $(SOURCE)  $(DEP_VUMET) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"vumeter.obj" :  $(SOURCE)  $(DEP_VUMET) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"vumeter.obj" :  $(SOURCE)  $(DEP_VUMET) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"vumeter.obj" :  $(SOURCE)  $(DEP_VUMET) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"vumeter.obj" :  $(SOURCE)  $(DEP_VUMET) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"vumeter.obj" :  $(SOURCE)  $(DEP_VUMET) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\waveidev.cpp
DEP_WAVEI=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"waveidev.obj" :  $(SOURCE)  $(DEP_WAVEI) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"waveidev.obj" :  $(SOURCE)  $(DEP_WAVEI) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"waveidev.obj" :  $(SOURCE)  $(DEP_WAVEI) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"waveidev.obj" :  $(SOURCE)  $(DEP_WAVEI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"waveidev.obj" :  $(SOURCE)  $(DEP_WAVEI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"waveidev.obj" :  $(SOURCE)  $(DEP_WAVEI) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"waveidev.obj" :  $(SOURCE)  $(DEP_WAVEI) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"waveidev.obj" :  $(SOURCE)  $(DEP_WAVEI) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sprite.cpp
DEP_SPRIT=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"sprite.obj" :  $(SOURCE)  $(DEP_SPRIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"sprite.obj" :  $(SOURCE)  $(DEP_SPRIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"sprite.obj" :  $(SOURCE)  $(DEP_SPRIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"sprite.obj" :  $(SOURCE)  $(DEP_SPRIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"sprite.obj" :  $(SOURCE)  $(DEP_SPRIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"sprite.obj" :  $(SOURCE)  $(DEP_SPRIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"sprite.obj" :  $(SOURCE)  $(DEP_SPRIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"sprite.obj" :  $(SOURCE)  $(DEP_SPRIT) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\spritlst.cpp
DEP_SPRITL=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"spritlst.obj" :  $(SOURCE)  $(DEP_SPRITL) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"spritlst.obj" :  $(SOURCE)  $(DEP_SPRITL) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"spritlst.obj" :  $(SOURCE)  $(DEP_SPRITL) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"spritlst.obj" :  $(SOURCE)  $(DEP_SPRITL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"spritlst.obj" :  $(SOURCE)  $(DEP_SPRITL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"spritlst.obj" :  $(SOURCE)  $(DEP_SPRITL) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"spritlst.obj" :  $(SOURCE)  $(DEP_SPRITL) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"spritlst.obj" :  $(SOURCE)  $(DEP_SPRITL) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mciobj.cpp
DEP_MCIOB=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"mciobj.obj" :  $(SOURCE)  $(DEP_MCIOB) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"mciobj.obj" :  $(SOURCE)  $(DEP_MCIOB) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"mciobj.obj" :  $(SOURCE)  $(DEP_MCIOB) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"mciobj.obj" :  $(SOURCE)  $(DEP_MCIOB) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"mciobj.obj" :  $(SOURCE)  $(DEP_MCIOB) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"mciobj.obj" :  $(SOURCE)  $(DEP_MCIOB) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"mciobj.obj" :  $(SOURCE)  $(DEP_MCIOB) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"mciobj.obj" :  $(SOURCE)  $(DEP_MCIOB) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dibpal.cpp
DEP_DIBPA=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"dibpal.obj" :  $(SOURCE)  $(DEP_DIBPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"dibpal.obj" :  $(SOURCE)  $(DEP_DIBPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"dibpal.obj" :  $(SOURCE)  $(DEP_DIBPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"dibpal.obj" :  $(SOURCE)  $(DEP_DIBPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"dibpal.obj" :  $(SOURCE)  $(DEP_DIBPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"dibpal.obj" :  $(SOURCE)  $(DEP_DIBPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"dibpal.obj" :  $(SOURCE)  $(DEP_DIBPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"dibpal.obj" :  $(SOURCE)  $(DEP_DIBPA) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dib.cpp
DEP_DIB_C=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"dib.obj" :  $(SOURCE)  $(DEP_DIB_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"dib.obj" :  $(SOURCE)  $(DEP_DIB_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"dib.obj" :  $(SOURCE)  $(DEP_DIB_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"dib.obj" :  $(SOURCE)  $(DEP_DIB_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"dib.obj" :  $(SOURCE)  $(DEP_DIB_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"dib.obj" :  $(SOURCE)  $(DEP_DIB_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"dib.obj" :  $(SOURCE)  $(DEP_DIB_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"dib.obj" :  $(SOURCE)  $(DEP_DIB_C) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sound.cpp
DEP_SOUND=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"sound.obj" :  $(SOURCE)  $(DEP_SOUND) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"sound.obj" :  $(SOURCE)  $(DEP_SOUND) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"sound.obj" :  $(SOURCE)  $(DEP_SOUND) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"sound.obj" :  $(SOURCE)  $(DEP_SOUND) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"sound.obj" :  $(SOURCE)  $(DEP_SOUND) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"sound.obj" :  $(SOURCE)  $(DEP_SOUND) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"sound.obj" :  $(SOURCE)  $(DEP_SOUND) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"sound.obj" :  $(SOURCE)  $(DEP_SOUND) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wave.cpp
DEP_WAVE_=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"wave.obj" :  $(SOURCE)  $(DEP_WAVE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"wave.obj" :  $(SOURCE)  $(DEP_WAVE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"wave.obj" :  $(SOURCE)  $(DEP_WAVE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"wave.obj" :  $(SOURCE)  $(DEP_WAVE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"wave.obj" :  $(SOURCE)  $(DEP_WAVE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"wave.obj" :  $(SOURCE)  $(DEP_WAVE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"wave.obj" :  $(SOURCE)  $(DEP_WAVE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"wave.obj" :  $(SOURCE)  $(DEP_WAVE_) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\meter.cpp
DEP_METER=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"meter.obj" :  $(SOURCE)  $(DEP_METER) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"meter.obj" :  $(SOURCE)  $(DEP_METER) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"meter.obj" :  $(SOURCE)  $(DEP_METER) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"meter.obj" :  $(SOURCE)  $(DEP_METER) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"meter.obj" :  $(SOURCE)  $(DEP_METER) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"meter.obj" :  $(SOURCE)  $(DEP_METER) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"meter.obj" :  $(SOURCE)  $(DEP_METER) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"meter.obj" :  $(SOURCE)  $(DEP_METER) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\waveodev.cpp
DEP_WAVEO=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"waveodev.obj" :  $(SOURCE)  $(DEP_WAVEO) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"waveodev.obj" :  $(SOURCE)  $(DEP_WAVEO) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"waveodev.obj" :  $(SOURCE)  $(DEP_WAVEO) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"waveodev.obj" :  $(SOURCE)  $(DEP_WAVEO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"waveodev.obj" :  $(SOURCE)  $(DEP_WAVEO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"waveodev.obj" :  $(SOURCE)  $(DEP_WAVEO) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"waveodev.obj" :  $(SOURCE)  $(DEP_WAVEO) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"waveodev.obj" :  $(SOURCE)  $(DEP_WAVEO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\transbmp.cpp
DEP_TRANS=\
	.\stdafx.h\
	..\include\animate.h

!IF  "$(CFG)" == "x86 Release"

$(INTDIR)/"transbmp.obj" :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Debug"

$(INTDIR)/"transbmp.obj" :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"transbmp.obj" :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"transbmp.obj" :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"transbmp.obj" :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"transbmp.obj" :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Debug"

$(INTDIR)/"transbmp.obj" :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

!ELSEIF  "$(CFG)" == "x86 Static Release"

$(INTDIR)/"transbmp.obj" :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
