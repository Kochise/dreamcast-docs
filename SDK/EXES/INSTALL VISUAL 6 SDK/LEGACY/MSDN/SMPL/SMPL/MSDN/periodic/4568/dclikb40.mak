# Microsoft Visual C++ Generated NMAKE File, Format Version 40000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Dclikb32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dclikb32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dclikb32 - Win32 Release" && "$(CFG)" !=\
 "Dclikb32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dclikb40.mak" CFG="Dclikb32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dclikb32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Dclikb32 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Dclikb32 - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dclikb32 - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir WinRel
# PROP BASE Intermediate_Dir WinRel
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir WinRel
# PROP Intermediate_Dir WinRel
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\Dclikbar.exe" "$(OUTDIR)\Dclikb40.bsc"

CLEAN : 
	-@erase ".\WinRel\Dclikb40.bsc"
	-@erase ".\WinRel\mainfrm.sbr"
	-@erase ".\WinRel\Dclikb40.pch"
	-@erase ".\WinRel\Dclikbar.sbr"
	-@erase ".\WinRel\View.sbr"
	-@erase ".\WinRel\Doc.sbr"
	-@erase ".\WinRel\Stdafx.sbr"
	-@erase ".\WinRel\Dclikbar.exe"
	-@erase ".\WinRel\View.obj"
	-@erase ".\WinRel\Doc.obj"
	-@erase ".\WinRel\Stdafx.obj"
	-@erase ".\WinRel\mainfrm.obj"
	-@erase ".\WinRel\Dclikbar.obj"
	-@erase ".\WinRel\Dclikbar.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Dclikb40.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\WinRel/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dclikbar.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dclikb40.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/mainfrm.sbr" \
	"$(INTDIR)/Dclikbar.sbr" \
	"$(INTDIR)/View.sbr" \
	"$(INTDIR)/Doc.sbr" \
	"$(INTDIR)/Stdafx.sbr"

"$(OUTDIR)\Dclikb40.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /machine:IX86 /out:"WinRel/Dclikbar.exe"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=oldnames.lib /nologo /stack:0x10240 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Dclikbar.pdb" /machine:IX86\
 /out:"$(OUTDIR)/Dclikbar.exe" 
LINK32_OBJS= \
	"$(INTDIR)/View.obj" \
	"$(INTDIR)/Doc.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/Dclikbar.obj" \
	"$(INTDIR)/Dclikbar.res"

"$(OUTDIR)\Dclikbar.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dclikb32 - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir WinDebug
# PROP BASE Intermediate_Dir WinDebug
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir WinDebug
# PROP Intermediate_Dir WinDebug
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\Dclikbar.exe"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\Dclikb40.pch"
	-@erase ".\WinDebug\Dclikbar.exe"
	-@erase ".\WinDebug\mainfrm.obj"
	-@erase ".\WinDebug\Doc.obj"
	-@erase ".\WinDebug\View.obj"
	-@erase ".\WinDebug\Stdafx.obj"
	-@erase ".\WinDebug\Dclikbar.obj"
	-@erase ".\WinDebug\Dclikbar.res"
	-@erase ".\WinDebug\Dclikbar.ilk"
	-@erase ".\WinDebug\Dclikbar.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dclikb40.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dclikbar.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dclikb40.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /debug /machine:IX86 /out:"WinDebug/Dclikbar.exe"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=oldnames.lib /nologo /stack:0x10240 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Dclikbar.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)/Dclikbar.exe" 
LINK32_OBJS= \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/Doc.obj" \
	"$(INTDIR)/View.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Dclikbar.obj" \
	"$(INTDIR)/Dclikbar.res"

"$(OUTDIR)\Dclikbar.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Dclikb32 - Win32 Release"
# Name "Dclikb32 - Win32 Debug"

!IF  "$(CFG)" == "Dclikb32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Dclikb32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dclikbar.rc
DEP_RSC_DCLIK=\
	".\Res\App.ico"\
	".\Res\Doc.ico"\
	".\Res\Toolbar.bmp"\
	".\Res\App.rc2"\
	

"$(INTDIR)\Dclikbar.res" : $(SOURCE) $(DEP_RSC_DCLIK) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Dclikb32 - Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Dclikb40.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dclikb40.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dclikb32 - Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dclikb40.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dclikb40.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dclikbar.cpp

!IF  "$(CFG)" == "Dclikb32 - Win32 Release"

DEP_CPP_DCLIKB=\
	".\Dclikbar.h"\
	".\Doc.h"\
	".\mainfrm.h"\
	".\Stdafx.h"\
	".\View.h"\
	

"$(INTDIR)\Dclikbar.obj" : $(SOURCE) $(DEP_CPP_DCLIKB) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"

"$(INTDIR)\Dclikbar.sbr" : $(SOURCE) $(DEP_CPP_DCLIKB) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"


!ELSEIF  "$(CFG)" == "Dclikb32 - Win32 Debug"

DEP_CPP_DCLIKB=\
	".\Stdafx.h"\
	".\Dclikbar.h"\
	".\mainfrm.h"\
	".\Doc.h"\
	".\View.h"\
	

"$(INTDIR)\Dclikbar.obj" : $(SOURCE) $(DEP_CPP_DCLIKB) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_DCLIKB) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Dclikbar.h"\
	".\mainfrm.h"\
	

!IF  "$(CFG)" == "Dclikb32 - Win32 Release"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"

"$(INTDIR)\mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"


!ELSEIF  "$(CFG)" == "Dclikb32 - Win32 Debug"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doc.cpp
DEP_CPP_DOC_C=\
	".\Doc.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Dclikb32 - Win32 Release"


"$(INTDIR)\Doc.obj" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"

"$(INTDIR)\Doc.sbr" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"


!ELSEIF  "$(CFG)" == "Dclikb32 - Win32 Debug"


"$(INTDIR)\Doc.obj" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\View.cpp
DEP_CPP_VIEW_=\
	".\Doc.h"\
	".\Stdafx.h"\
	".\View.h"\
	

!IF  "$(CFG)" == "Dclikb32 - Win32 Release"


"$(INTDIR)\View.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"

"$(INTDIR)\View.sbr" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"


!ELSEIF  "$(CFG)" == "Dclikb32 - Win32 Debug"


"$(INTDIR)\View.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 "$(INTDIR)\Dclikb40.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
