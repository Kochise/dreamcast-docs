# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release" && "$(CFG)" !=\
 "Alpha Debug" && "$(CFG)" != "Alpha Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DDEServ.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Alpha Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "Alpha Release" (based on "Win32 (ALPHA) Application")
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
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : $(OUTDIR)/"DDEServ.exe" $(OUTDIR)/"DDEServ.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"DDEServ.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DDEServ.pdb" /c 
CPP_OBJS=".\x86-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DDEServ.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DDEServ.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/"DDEServ.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"DDEServ.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"DDEServ.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"DDEServ.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"DDESvdoc.obj" \
	$(INTDIR)/"DDESvvw.obj" \
	$(INTDIR)/"DDEServ.res" \
	$(INTDIR)/"myserv.obj" \
	$(INTDIR)/"datadlg.obj" \
	$(INTDIR)/"stddde.obj"

$(OUTDIR)/"DDEServ.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/"DDEServ.exe" $(OUTDIR)/"DDEServ.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"DDEServ.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
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
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DDEServ.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DDEServ.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/"DDEServ.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"DDEServ.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"DDEServ.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"DDEServ.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"DDESvdoc.obj" \
	$(INTDIR)/"DDESvvw.obj" \
	$(INTDIR)/"DDEServ.res" \
	$(INTDIR)/"myserv.obj" \
	$(INTDIR)/"datadlg.obj" \
	$(INTDIR)/"stddde.obj"

$(OUTDIR)/"DDEServ.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/""""DDEServ.exe"""" $(OUTDIR)/""""DDEServ.bsc""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"DDEServ.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DDEServ.pdb" /c 
CPP_OBJS=".\Alpha-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"DDEServ.bsc" : $(OUTDIR)  $(BSC32_SBRS)
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DDEServ.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DDEServ.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /PDB:$(OUTDIR)/"DDEServ.pdb" /DEBUG\
 /MACHINE:ALPHA /OUT:$(OUTDIR)/"DDEServ.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"DDEServ.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"DDESvdoc.obj" \
	$(INTDIR)/"DDESvvw.obj" \
	$(INTDIR)/"DDEServ.res" \
	$(INTDIR)/"myserv.obj" \
	$(INTDIR)/"datadlg.obj" \
	$(INTDIR)/"stddde.obj"

$(OUTDIR)/"DDEServ.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/""""DDEServ.exe"""" $(OUTDIR)/""""DDEServ.bsc""""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"DDEServ.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\Alpha-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

$(OUTDIR)/"DDEServ.bsc" : $(OUTDIR)  $(BSC32_SBRS)
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DDEServ.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DDEServ.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /PDB:$(OUTDIR)/"DDEServ.pdb"\
 /MACHINE:ALPHA /OUT:$(OUTDIR)/"DDEServ.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"DDEServ.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"DDESvdoc.obj" \
	$(INTDIR)/"DDESvvw.obj" \
	$(INTDIR)/"DDEServ.res" \
	$(INTDIR)/"myserv.obj" \
	$(INTDIR)/"datadlg.obj" \
	$(INTDIR)/"stddde.obj"

$(OUTDIR)/"DDEServ.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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
 "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"DDEServ.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DDEServ.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp$(OUTDIR)/"DDEServ.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DDEServ.cpp
DEP_DDESE=\
	.\stdafx.h\
	.\DDEServ.h\
	.\mainfrm.h\
	.\DDESvdoc.h\
	.\DDESvvw.h\
	..\StdDDE\stddde.h\
	.\myserv.h\
	.\mytopic.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"DDEServ.obj" :  $(SOURCE)  $(DEP_DDESE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"DDEServ.obj" :  $(SOURCE)  $(DEP_DDESE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"DDEServ.obj" :  $(SOURCE)  $(DEP_DDESE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"DDEServ.obj" :  $(SOURCE)  $(DEP_DDESE) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\DDEServ.h\
	.\DDESvdoc.h\
	.\DDESvvw.h\
	.\datadlg.h\
	.\mainfrm.h\
	..\StdDDE\stddde.h\
	.\myserv.h\
	.\mytopic.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DDESvdoc.cpp
DEP_DDESV=\
	.\stdafx.h\
	.\DDEServ.h\
	.\DDESvdoc.h\
	..\StdDDE\stddde.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"DDESvdoc.obj" :  $(SOURCE)  $(DEP_DDESV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"DDESvdoc.obj" :  $(SOURCE)  $(DEP_DDESV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"DDESvdoc.obj" :  $(SOURCE)  $(DEP_DDESV) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"DDESvdoc.obj" :  $(SOURCE)  $(DEP_DDESV) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DDESvvw.cpp
DEP_DDESVV=\
	.\stdafx.h\
	.\DDEServ.h\
	.\DDESvdoc.h\
	.\DDESvvw.h\
	..\StdDDE\stddde.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"DDESvvw.obj" :  $(SOURCE)  $(DEP_DDESVV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"DDESvvw.obj" :  $(SOURCE)  $(DEP_DDESVV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"DDESvvw.obj" :  $(SOURCE)  $(DEP_DDESVV) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"DDESvvw.obj" :  $(SOURCE)  $(DEP_DDESVV) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DDEServ.rc
DEP_DDESER=\
	.\res\DDEServ.ico\
	.\res\toolbar.bmp\
	.\res\DDEServ.rc2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"DDEServ.res" :  $(SOURCE)  $(DEP_DDESER) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"DDEServ.res" :  $(SOURCE)  $(DEP_DDESER) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"DDEServ.res" :  $(SOURCE)  $(DEP_DDESER) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"DDEServ.res" :  $(SOURCE)  $(DEP_DDESER) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\myserv.cpp
DEP_MYSER=\
	.\stdafx.h\
	.\DDEServ.h\
	.\myserv.h\
	..\StdDDE\stddde.h\
	.\mytopic.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"myserv.obj" :  $(SOURCE)  $(DEP_MYSER) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"myserv.obj" :  $(SOURCE)  $(DEP_MYSER) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"myserv.obj" :  $(SOURCE)  $(DEP_MYSER) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"myserv.obj" :  $(SOURCE)  $(DEP_MYSER) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\datadlg.cpp
DEP_DATAD=\
	.\stdafx.h\
	.\DDEServ.h\
	.\datadlg.h\
	..\StdDDE\stddde.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"datadlg.obj" :  $(SOURCE)  $(DEP_DATAD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"datadlg.obj" :  $(SOURCE)  $(DEP_DATAD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"datadlg.obj" :  $(SOURCE)  $(DEP_DATAD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"datadlg.obj" :  $(SOURCE)  $(DEP_DATAD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\apps\DDE\StdDDE\stddde.cpp
DEP_STDDD=\
	..\StdDDE\stddde.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"stddde.obj" :  $(SOURCE)  $(DEP_STDDD) $(INTDIR)\
 $(INTDIR)/stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"stddde.obj" :  $(SOURCE)  $(DEP_STDDD) $(INTDIR)\
 $(INTDIR)/stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Debug"

!ELSEIF  "$(CFG)" == "Alpha Release"

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
