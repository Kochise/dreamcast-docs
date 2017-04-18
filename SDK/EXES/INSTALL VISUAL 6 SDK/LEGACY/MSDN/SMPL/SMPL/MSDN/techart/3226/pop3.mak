# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (MIPS) Application" 0x0501
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release" && "$(CFG)" !=\
 "MIPS Release" && "$(CFG)" != "MIPS Debug" && "$(CFG)" != "Alpha Release" &&\
 "$(CFG)" != "Alpha Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "POP3.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MIPS Release" (based on "Win32 (MIPS) Application")
!MESSAGE "MIPS Debug" (based on "Win32 (MIPS) Application")
!MESSAGE "Alpha Release" (based on "Win32 (ALPHA) Application")
!MESSAGE "Alpha Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"

!IF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : $(OUTDIR)/"pop3.scr" $(OUTDIR)/"POP3.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /Fp$(OUTDIR)/"POP3.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"POP3.pdb" /c 
CPP_OBJS=".\x86-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"POP3.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"POP3.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/"POP3.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 winmm.lib animated.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386 /OUT:"x86-d/pop3.scr"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib animated.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"POP3.pdb" /DEBUG /MACHINE:I386 /OUT:"x86-d/pop3.scr" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"STDAFX.OBJ" \
	$(INTDIR)/"POP3.OBJ" \
	$(INTDIR)/"POP3.res" \
	$(INTDIR)/"MYWND.OBJ" \
	$(INTDIR)/"SAVEWND.OBJ" \
	$(INTDIR)/"ANIMWND.OBJ" \
	$(INTDIR)/"CONFIGDL.OBJ"

$(OUTDIR)/"pop3.scr" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : $(OUTDIR)/"pop3.scr" $(OUTDIR)/"POP3.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"POP3.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"POP3.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"POP3.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/"POP3.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 winmm.lib animater.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes /MACHINE:I386 /OUT:"x86-r/pop3.scr"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib animater.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"POP3.pdb" /MACHINE:I386 /OUT:"x86-r/pop3.scr" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"STDAFX.OBJ" \
	$(INTDIR)/"POP3.OBJ" \
	$(INTDIR)/"POP3.res" \
	$(INTDIR)/"MYWND.OBJ" \
	$(INTDIR)/"SAVEWND.OBJ" \
	$(INTDIR)/"ANIMWND.OBJ" \
	$(INTDIR)/"CONFIGDL.OBJ"

$(OUTDIR)/"pop3.scr" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MIPS_Rel"
# PROP BASE Intermediate_Dir "MIPS_Rel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MIPS-r"
# PROP Intermediate_Dir "MIPS-r"
OUTDIR=.\MIPS-r
INTDIR=.\MIPS-r

ALL : $(OUTDIR)/""pop3.scr"" $(OUTDIR)/""pop3.bsc""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"pop3.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\MIPS-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"pop3.bsc" : $(OUTDIR)  $(BSC32_SBRS)
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"pop3.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"pop3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
# ADD LINK32 winmm.lib animater.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS /OUT:"MIPS-r/pop3.scr"
LINK32_FLAGS=winmm.lib animater.lib /NOLOGO /SUBSYSTEM:windows\
 /PDB:$(OUTDIR)/"pop3.pdb" /MACHINE:MIPS /OUT:"MIPS-r/pop3.scr" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"pop3.obj" \
	$(INTDIR)/"pop3.res" \
	$(INTDIR)/"mywnd.obj" \
	$(INTDIR)/"savewnd.obj" \
	$(INTDIR)/"animwnd.obj" \
	$(INTDIR)/"configdl.obj"

$(OUTDIR)/"pop3.scr" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPS Debug"

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

ALL : $(OUTDIR)/""pop3.exe"" $(OUTDIR)/""pop3.bsc""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"pop3.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"pop3.pdb" /c 
CPP_OBJS=".\MIPS-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"pop3.bsc" : $(OUTDIR)  $(BSC32_SBRS)
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"pop3.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"pop3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
# ADD LINK32 winmm.lib animated.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
LINK32_FLAGS=winmm.lib animated.lib /NOLOGO /SUBSYSTEM:windows\
 /PDB:$(OUTDIR)/"pop3.pdb" /DEBUG /MACHINE:MIPS /OUT:$(OUTDIR)/"pop3.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"pop3.obj" \
	$(INTDIR)/"pop3.res" \
	$(INTDIR)/"mywnd.obj" \
	$(INTDIR)/"savewnd.obj" \
	$(INTDIR)/"animwnd.obj" \
	$(INTDIR)/"configdl.obj"

$(OUTDIR)/"pop3.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Alpha Release"

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

ALL : $(OUTDIR)/"""pop3.scr""" $(OUTDIR)/"""pop3.bsc"""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp$(OUTDIR)/"pop3.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\Alpha-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"pop3.bsc" : $(OUTDIR)  $(BSC32_SBRS)
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"pop3.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"pop3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
# ADD LINK32 winmm.lib animater.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA /OUT:"Alpha-r/pop3.scr"
LINK32_FLAGS=winmm.lib animater.lib /NOLOGO /SUBSYSTEM:windows\
 /PDB:$(OUTDIR)/"pop3.pdb" /MACHINE:ALPHA /OUT:"Alpha-r/pop3.scr" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"pop3.obj" \
	$(INTDIR)/"pop3.res" \
	$(INTDIR)/"mywnd.obj" \
	$(INTDIR)/"savewnd.obj" \
	$(INTDIR)/"animwnd.obj" \
	$(INTDIR)/"configdl.obj"

$(OUTDIR)/"pop3.scr" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Alpha Debug"

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

ALL : $(OUTDIR)/"""pop3.scr""" $(OUTDIR)/"""pop3.bsc"""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp$(OUTDIR)/"pop3.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"pop3.pdb" /c 
CPP_OBJS=".\Alpha-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"pop3.bsc" : $(OUTDIR)  $(BSC32_SBRS)
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"pop3.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"pop3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
# ADD LINK32 winmm.lib animated.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA /OUT:"Alpha-d/pop3.scr"
LINK32_FLAGS=winmm.lib animated.lib /NOLOGO /SUBSYSTEM:windows\
 /PDB:$(OUTDIR)/"pop3.pdb" /DEBUG /MACHINE:ALPHA /OUT:"Alpha-d/pop3.scr" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"pop3.obj" \
	$(INTDIR)/"pop3.res" \
	$(INTDIR)/"mywnd.obj" \
	$(INTDIR)/"savewnd.obj" \
	$(INTDIR)/"animwnd.obj" \
	$(INTDIR)/"configdl.obj"

$(OUTDIR)/"pop3.scr" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_STDAF=\
	.\STDAFX.H\
	\build4cd.11\animate\include\animate.h

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"STDAFX.OBJ" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /Fp$(OUTDIR)/"POP3.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"POP3.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"STDAFX.OBJ" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"POP3.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\POP3.CPP
DEP_POP3_=\
	.\STDAFX.H\
	.\POP3.H\
	.\CONFIGDL.H\
	.\MYWND.H\
	\build4cd.11\animate\include\animate.h\
	.\ANIMWND.H\
	.\SAVEWND.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"POP3.OBJ" :  $(SOURCE)  $(DEP_POP3_) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"POP3.OBJ" :  $(SOURCE)  $(DEP_POP3_) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"pop3.obj" :  $(SOURCE)  $(DEP_POP3_) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"pop3.obj" :  $(SOURCE)  $(DEP_POP3_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"pop3.obj" :  $(SOURCE)  $(DEP_POP3_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"pop3.obj" :  $(SOURCE)  $(DEP_POP3_) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\POP3.RC
DEP_POP3_R=\
	.\RES\CURSOR1.CUR\
	.\RES\POP3.RC2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"POP3.res" :  $(SOURCE)  $(DEP_POP3_R) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"POP3.res" :  $(SOURCE)  $(DEP_POP3_R) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"pop3.res" :  $(SOURCE)  $(DEP_POP3_R) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"pop3.res" :  $(SOURCE)  $(DEP_POP3_R) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"pop3.res" :  $(SOURCE)  $(DEP_POP3_R) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"pop3.res" :  $(SOURCE)  $(DEP_POP3_R) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MYWND.CPP
DEP_MYWND=\
	.\STDAFX.H\
	.\POP3.H\
	.\MYWND.H\
	\build4cd.11\animate\include\animate.h\
	.\ANIMWND.H\
	.\SAVEWND.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"MYWND.OBJ" :  $(SOURCE)  $(DEP_MYWND) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"MYWND.OBJ" :  $(SOURCE)  $(DEP_MYWND) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"mywnd.obj" :  $(SOURCE)  $(DEP_MYWND) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"mywnd.obj" :  $(SOURCE)  $(DEP_MYWND) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"mywnd.obj" :  $(SOURCE)  $(DEP_MYWND) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"mywnd.obj" :  $(SOURCE)  $(DEP_MYWND) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SAVEWND.CPP
DEP_SAVEW=\
	.\STDAFX.H\
	.\SAVEWND.H\
	\build4cd.11\animate\include\animate.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"SAVEWND.OBJ" :  $(SOURCE)  $(DEP_SAVEW) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"SAVEWND.OBJ" :  $(SOURCE)  $(DEP_SAVEW) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"savewnd.obj" :  $(SOURCE)  $(DEP_SAVEW) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"savewnd.obj" :  $(SOURCE)  $(DEP_SAVEW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"savewnd.obj" :  $(SOURCE)  $(DEP_SAVEW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"savewnd.obj" :  $(SOURCE)  $(DEP_SAVEW) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ANIMWND.CPP
DEP_ANIMW=\
	.\STDAFX.H\
	.\ANIMWND.H\
	\build4cd.11\animate\include\animate.h\
	.\SAVEWND.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"ANIMWND.OBJ" :  $(SOURCE)  $(DEP_ANIMW) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"ANIMWND.OBJ" :  $(SOURCE)  $(DEP_ANIMW) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"animwnd.obj" :  $(SOURCE)  $(DEP_ANIMW) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"animwnd.obj" :  $(SOURCE)  $(DEP_ANIMW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"animwnd.obj" :  $(SOURCE)  $(DEP_ANIMW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"animwnd.obj" :  $(SOURCE)  $(DEP_ANIMW) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CONFIGDL.CPP
DEP_CONFI=\
	.\STDAFX.H\
	.\POP3.H\
	.\CONFIGDL.H\
	\build4cd.11\animate\include\animate.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"CONFIGDL.OBJ" :  $(SOURCE)  $(DEP_CONFI) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"CONFIGDL.OBJ" :  $(SOURCE)  $(DEP_CONFI) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "MIPS Release"

$(INTDIR)/"configdl.obj" :  $(SOURCE)  $(DEP_CONFI) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPS Debug"

$(INTDIR)/"configdl.obj" :  $(SOURCE)  $(DEP_CONFI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"configdl.obj" :  $(SOURCE)  $(DEP_CONFI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"configdl.obj" :  $(SOURCE)  $(DEP_CONFI) $(INTDIR)

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
