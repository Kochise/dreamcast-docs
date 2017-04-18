# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=EnumDoc - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to EnumDoc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "EnumDoc - Win32 Release" && "$(CFG)" !=\
 "EnumDoc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Vc40.mak" CFG="EnumDoc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EnumDoc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "EnumDoc - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "EnumDoc - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "EnumDoc - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\enumdoc.exe"

CLEAN : 
	-@erase ".\WinRel\enumdoc.exe"
	-@erase ".\WinRel\DOC.OBJ"
	-@erase ".\WinRel\Vc40.pch"
	-@erase ".\WinRel\DOCENUM.OBJ"
	-@erase ".\WinRel\VIEW.OBJ"
	-@erase ".\WinRel\MAINFRM.OBJ"
	-@erase ".\WinRel\ENUMDOC.OBJ"
	-@erase ".\WinRel\STDAFX.OBJ"
	-@erase ".\WinRel\ENUMDOC.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Vc40.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ENUMDOC.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Vc40.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /machine:IX86 /out:"WinRel/enumdoc.exe"
LINK32_FLAGS=oldnames.lib /nologo /stack:0x10240 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/enumdoc.pdb" /machine:IX86\
 /out:"$(OUTDIR)/enumdoc.exe" 
LINK32_OBJS= \
	"$(INTDIR)/DOC.OBJ" \
	"$(INTDIR)/DOCENUM.OBJ" \
	"$(INTDIR)/VIEW.OBJ" \
	"$(INTDIR)/MAINFRM.OBJ" \
	"$(INTDIR)/ENUMDOC.OBJ" \
	"$(INTDIR)/STDAFX.OBJ" \
	"$(INTDIR)/ENUMDOC.res"

"$(OUTDIR)\enumdoc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "EnumDoc - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\enumdoc.exe"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\Vc40.pch"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\enumdoc.exe"
	-@erase ".\WinDebug\ENUMDOC.OBJ"
	-@erase ".\WinDebug\DOC.OBJ"
	-@erase ".\WinDebug\DOCENUM.OBJ"
	-@erase ".\WinDebug\VIEW.OBJ"
	-@erase ".\WinDebug\MAINFRM.OBJ"
	-@erase ".\WinDebug\STDAFX.OBJ"
	-@erase ".\WinDebug\ENUMDOC.res"
	-@erase ".\WinDebug\enumdoc.ilk"
	-@erase ".\WinDebug\enumdoc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Vc40.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ENUMDOC.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Vc40.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /debug /machine:IX86 /out:"WinDebug/enumdoc.exe"
LINK32_FLAGS=oldnames.lib /nologo /stack:0x10240 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/enumdoc.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)/enumdoc.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ENUMDOC.OBJ" \
	"$(INTDIR)/DOC.OBJ" \
	"$(INTDIR)/DOCENUM.OBJ" \
	"$(INTDIR)/VIEW.OBJ" \
	"$(INTDIR)/MAINFRM.OBJ" \
	"$(INTDIR)/STDAFX.OBJ" \
	"$(INTDIR)/ENUMDOC.res"

"$(OUTDIR)\enumdoc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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

################################################################################
# Begin Target

# Name "EnumDoc - Win32 Release"
# Name "EnumDoc - Win32 Debug"

!IF  "$(CFG)" == "EnumDoc - Win32 Release"

!ELSEIF  "$(CFG)" == "EnumDoc - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ENUMDOC.RC
DEP_RSC_ENUMD=\
	".\RES\ENUMDOC.ICO"\
	".\RES\DOCA.ICO"\
	".\RES\DOCB.ICO"\
	".\RES\TOOLBAR.BMP"\
	".\RES\ENUMDOC.RC2"\
	

"$(INTDIR)\ENUMDOC.res" : $(SOURCE) $(DEP_RSC_ENUMD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\STDAFX.H"\
	

!IF  "$(CFG)" == "EnumDoc - Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/Vc40.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Vc40.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "EnumDoc - Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Vc40.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Vc40.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ENUMDOC.CPP
DEP_CPP_ENUMDO=\
	".\STDAFX.H"\
	".\ENUMDOC.H"\
	".\MAINFRM.H"\
	".\DOC.H"\
	".\VIEW.H"\
	".\DOCENUM.H"\
	

"$(INTDIR)\ENUMDOC.OBJ" : $(SOURCE) $(DEP_CPP_ENUMDO) "$(INTDIR)"\
 "$(INTDIR)\Vc40.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MAINFRM.CPP
DEP_CPP_MAINF=\
	".\STDAFX.H"\
	".\ENUMDOC.H"\
	".\MAINFRM.H"\
	

"$(INTDIR)\MAINFRM.OBJ" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Vc40.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DOC.CPP
DEP_CPP_DOC_C=\
	".\STDAFX.H"\
	".\DOC.H"\
	

"$(INTDIR)\DOC.OBJ" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 "$(INTDIR)\Vc40.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\VIEW.CPP
DEP_CPP_VIEW_=\
	".\STDAFX.H"\
	".\ENUMDOC.H"\
	".\DOC.H"\
	".\VIEW.H"\
	

"$(INTDIR)\VIEW.OBJ" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 "$(INTDIR)\Vc40.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DOCENUM.CPP
DEP_CPP_DOCEN=\
	".\STDAFX.H"\
	".\DOCENUM.H"\
	

"$(INTDIR)\DOCENUM.OBJ" : $(SOURCE) $(DEP_CPP_DOCEN) "$(INTDIR)"\
 "$(INTDIR)\Vc40.pch"


# End Source File
# End Target
# End Project
################################################################################
