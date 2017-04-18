# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=SimpleObject - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SimpleObject - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WrapUser - Win32 Release" && "$(CFG)" !=\
 "WrapUser - Win32 Debug" && "$(CFG)" != "SimpleObject - Win32 Release" &&\
 "$(CFG)" != "SimpleObject - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WrapUser.mak" CFG="SimpleObject - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WrapUser - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WrapUser - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SimpleObject - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleObject - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "SimpleObject - Win32 Debug"

!IF  "$(CFG)" == "WrapUser - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\WrapUser.exe" "$(OUTDIR)\WrapUser.tlb"

CLEAN : 
	-@erase ".\Release\WrapUser.tlb"
	-@erase ".\Release\WrapUser.exe"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\GUIDS.obj"
	-@erase ".\Release\WrapUser.pch"
	-@erase ".\Release\WrapUser.obj"
	-@erase ".\Release\WrapUserDlg.obj"
	-@erase ".\Release\WrapUser.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/WrapUser.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WrapUser.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WrapUser.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/WrapUser.pdb" /machine:I386 /out:"$(OUTDIR)/WrapUser.exe" 
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/GUIDS.obj" \
	"$(INTDIR)/WrapUser.obj" \
	"$(INTDIR)/WrapUserDlg.obj" \
	"$(INTDIR)/WrapUser.res"

"$(OUTDIR)\WrapUser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WrapUser - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\WrapUser.exe" "$(OUTDIR)\WrapUser.tlb"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\WrapUser.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\WrapUser.tlb"
	-@erase ".\Debug\WrapUser.exe"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\GUIDS.obj"
	-@erase ".\Debug\WrapUserDlg.obj"
	-@erase ".\Debug\WrapUser.obj"
	-@erase ".\Debug\WrapUser.res"
	-@erase ".\Debug\WrapUser.ilk"
	-@erase ".\Debug\WrapUser.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/WrapUser.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WrapUser.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WrapUser.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/WrapUser.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/WrapUser.exe" 
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/GUIDS.obj" \
	"$(INTDIR)/WrapUserDlg.obj" \
	"$(INTDIR)/WrapUser.obj" \
	"$(INTDIR)/WrapUser.res"

"$(OUTDIR)\WrapUser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SimpleObject - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SimpleObject\Release"
# PROP BASE Intermediate_Dir "SimpleObject\Release"
# PROP BASE Target_Dir "SimpleObject"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SimpleObject\Release"
# PROP Intermediate_Dir "SimpleObject\Release"
# PROP Target_Dir "SimpleObject"
OUTDIR=.\SimpleObject\Release
INTDIR=.\SimpleObject\Release

ALL : "$(OUTDIR)\SimpleObject.dll"

CLEAN : 
	-@erase ".\SimpleObject\Release\SimpleObject.dll"
	-@erase ".\SimpleObject\Release\GUIDS.obj"
	-@erase ".\SimpleObject\Release\SimpleObject.pch"
	-@erase ".\SimpleObject\Release\CSimpleObject.obj"
	-@erase ".\SimpleObject\Release\stdafx.obj"
	-@erase ".\SimpleObject\Release\CClassFactory.obj"
	-@erase ".\SimpleObject\Release\SimpleObject.lib"
	-@erase ".\SimpleObject\Release\SimpleObject.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SimpleObject.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SimpleObject\Release/
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
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SimpleObject.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/SimpleObject.pdb" /machine:I386\
 /def:".\SimpleObject\SimpleObject.def" /out:"$(OUTDIR)/SimpleObject.dll"\
 /implib:"$(OUTDIR)/SimpleObject.lib" 
DEF_FILE= \
	".\SimpleObject\SimpleObject.def"
LINK32_OBJS= \
	"$(INTDIR)/GUIDS.obj" \
	"$(INTDIR)/CSimpleObject.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/CClassFactory.obj"

"$(OUTDIR)\SimpleObject.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SimpleObject - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SimpleObject\Debug"
# PROP BASE Intermediate_Dir "SimpleObject\Debug"
# PROP BASE Target_Dir "SimpleObject"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SimpleObject\Debug"
# PROP Intermediate_Dir "SimpleObject\Debug"
# PROP Target_Dir "SimpleObject"
OUTDIR=.\SimpleObject\Debug
INTDIR=.\SimpleObject\Debug

ALL : "$(OUTDIR)\SimpleObject.dll"

CLEAN : 
	-@erase ".\SimpleObject\Debug\vc40.pdb"
	-@erase ".\SimpleObject\Debug\SimpleObject.pch"
	-@erase ".\SimpleObject\Debug\vc40.idb"
	-@erase ".\SimpleObject\Debug\SimpleObject.dll"
	-@erase ".\SimpleObject\Debug\stdafx.obj"
	-@erase ".\SimpleObject\Debug\CSimpleObject.obj"
	-@erase ".\SimpleObject\Debug\CClassFactory.obj"
	-@erase ".\SimpleObject\Debug\GUIDS.obj"
	-@erase ".\SimpleObject\Debug\SimpleObject.ilk"
	-@erase ".\SimpleObject\Debug\SimpleObject.lib"
	-@erase ".\SimpleObject\Debug\SimpleObject.exp"
	-@erase ".\SimpleObject\Debug\SimpleObject.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SimpleObject.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\SimpleObject\Debug/
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
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SimpleObject.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/SimpleObject.pdb" /debug /machine:I386\
 /def:".\SimpleObject\SimpleObject.def" /out:"$(OUTDIR)/SimpleObject.dll"\
 /implib:"$(OUTDIR)/SimpleObject.lib" 
DEF_FILE= \
	".\SimpleObject\SimpleObject.def"
LINK32_OBJS= \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/CSimpleObject.obj" \
	"$(INTDIR)/CClassFactory.obj" \
	"$(INTDIR)/GUIDS.obj"

"$(OUTDIR)\SimpleObject.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "WrapUser - Win32 Release"
# Name "WrapUser - Win32 Debug"

!IF  "$(CFG)" == "WrapUser - Win32 Release"

!ELSEIF  "$(CFG)" == "WrapUser - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "WrapUser - Win32 Release"

!ELSEIF  "$(CFG)" == "WrapUser - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WrapUser.cpp
DEP_CPP_WRAPU=\
	".\StdAfx.h"\
	".\WrapUser.h"\
	".\WrapUserDlg.h"\
	".\CSimpleWrap.h"\
	".\SimpleObject\GUIDS.h"\
	".\SimpleObject\ISimple.h"\
	".\CInterfaceWrap.h"\
	

"$(INTDIR)\WrapUser.obj" : $(SOURCE) $(DEP_CPP_WRAPU) "$(INTDIR)"\
 "$(INTDIR)\WrapUser.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WrapUserDlg.cpp
DEP_CPP_WRAPUS=\
	".\StdAfx.h"\
	".\WrapUser.h"\
	".\WrapUserDlg.h"\
	".\CSimpleWrap.h"\
	".\SimpleObject\GUIDS.h"\
	".\SimpleObject\ISimple.h"\
	".\CInterfaceWrap.h"\
	

"$(INTDIR)\WrapUserDlg.obj" : $(SOURCE) $(DEP_CPP_WRAPUS) "$(INTDIR)"\
 "$(INTDIR)\WrapUser.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WrapUser.odl

!IF  "$(CFG)" == "WrapUser - Win32 Release"


"$(OUTDIR)\WrapUser.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/WrapUser.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "WrapUser - Win32 Debug"


"$(OUTDIR)\WrapUser.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/WrapUser.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "WrapUser - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/WrapUser.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WrapUser.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "WrapUser - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/WrapUser.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WrapUser.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WrapUser.rc
DEP_RSC_WRAPUSE=\
	".\res\WrapUser.ico"\
	".\res\WrapUser.rc2"\
	

!IF  "$(CFG)" == "WrapUser - Win32 Release"


"$(INTDIR)\WrapUser.res" : $(SOURCE) $(DEP_RSC_WRAPUSE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/WrapUser.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "WrapUser - Win32 Debug"


"$(INTDIR)\WrapUser.res" : $(SOURCE) $(DEP_RSC_WRAPUSE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/WrapUser.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SimpleObject\GUIDS.cpp

!IF  "$(CFG)" == "WrapUser - Win32 Release"

DEP_CPP_GUIDS=\
	".\SimpleObject\stdafx.h"\
	".\SimpleObject\GUIDS.h"\
	

"$(INTDIR)\GUIDS.obj" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"\
 "$(INTDIR)\WrapUser.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WrapUser - Win32 Debug"

DEP_CPP_GUIDS=\
	".\SimpleObject\stdafx.h"\
	".\SimpleObject\GUIDS.h"\
	

"$(INTDIR)\GUIDS.obj" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"\
 "$(INTDIR)\WrapUser.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
################################################################################
# Begin Target

# Name "SimpleObject - Win32 Release"
# Name "SimpleObject - Win32 Debug"

!IF  "$(CFG)" == "SimpleObject - Win32 Release"

!ELSEIF  "$(CFG)" == "SimpleObject - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SimpleObject\stdafx.cpp
DEP_CPP_STDAFX=\
	".\SimpleObject\stdafx.h"\
	

!IF  "$(CFG)" == "SimpleObject - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SimpleObject.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAFX) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SimpleObject.pch" : $(SOURCE) $(DEP_CPP_STDAFX) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SimpleObject - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SimpleObject.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAFX) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SimpleObject.pch" : $(SOURCE) $(DEP_CPP_STDAFX) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SimpleObject\GUIDS.cpp

!IF  "$(CFG)" == "SimpleObject - Win32 Release"

DEP_CPP_GUIDS=\
	".\SimpleObject\stdafx.h"\
	".\SimpleObject\GUIDS.h"\
	

"$(INTDIR)\GUIDS.obj" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"\
 "$(INTDIR)\SimpleObject.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimpleObject - Win32 Debug"

DEP_CPP_GUIDS=\
	".\SimpleObject\stdafx.h"\
	".\SimpleObject\GUIDS.h"\
	

"$(INTDIR)\GUIDS.obj" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"\
 "$(INTDIR)\SimpleObject.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SimpleObject\CSimpleObject.cpp
DEP_CPP_CSIMP=\
	".\SimpleObject\stdafx.h"\
	".\SimpleObject\GUIDS.h"\
	".\SimpleObject\ISimple.h"\
	".\SimpleObject\CSimpleObject.h"\
	

"$(INTDIR)\CSimpleObject.obj" : $(SOURCE) $(DEP_CPP_CSIMP) "$(INTDIR)"\
 "$(INTDIR)\SimpleObject.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SimpleObject\CClassFactory.cpp

!IF  "$(CFG)" == "SimpleObject - Win32 Release"

DEP_CPP_CCLAS=\
	".\SimpleObject\stdafx.h"\
	".\SimpleObject\GUIDS.h"\
	".\SimpleObject\ISimple.h"\
	".\SimpleObject\CSimpleObject.h"\
	".\SimpleObject\CClassFactory.h"\
	

"$(INTDIR)\CClassFactory.obj" : $(SOURCE) $(DEP_CPP_CCLAS) "$(INTDIR)"\
 "$(INTDIR)\SimpleObject.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimpleObject - Win32 Debug"

DEP_CPP_CCLAS=\
	".\SimpleObject\stdafx.h"\
	".\SimpleObject\GUIDS.h"\
	".\SimpleObject\ISimple.h"\
	".\SimpleObject\CSimpleObject.h"\
	".\SimpleObject\CClassFactory.h"\
	

"$(INTDIR)\CClassFactory.obj" : $(SOURCE) $(DEP_CPP_CCLAS) "$(INTDIR)"\
 "$(INTDIR)\SimpleObject.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SimpleObject\SimpleObject.def

!IF  "$(CFG)" == "SimpleObject - Win32 Release"

!ELSEIF  "$(CFG)" == "SimpleObject - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
