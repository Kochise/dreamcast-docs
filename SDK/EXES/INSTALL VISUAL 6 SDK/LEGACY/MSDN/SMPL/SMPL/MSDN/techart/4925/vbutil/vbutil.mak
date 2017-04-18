# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=VBUTIL - Win32 ANSI Debug
!MESSAGE No configuration specified.  Defaulting to VBUTIL - Win32 ANSI Debug.
!ENDIF 

!IF "$(CFG)" != "VBUTIL - Win32 Unicode Debug" && "$(CFG)" !=\
 "VBUTIL - Win32 ANSI Release" && "$(CFG)" != "VBUTIL - Win32 Unicode Release"\
 && "$(CFG)" != "VBUTIL - Win32 ANSI Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "VBUTIL.MAK" CFG="VBUTIL - Win32 ANSI Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VBUTIL - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VBUTIL - Win32 ANSI Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VBUTIL - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VBUTIL - Win32 ANSI Debug" (based on\
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
# PROP Target_Last_Scanned "VBUTIL - Win32 Unicode Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Unicode Debug"
# PROP BASE Intermediate_Dir "Unicode Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode Debug"
# PROP Intermediate_Dir "Unicode Debug"
# PROP Target_Dir ""
OUTDIR=.\Unicode Debug
INTDIR=.\Unicode Debug

ALL : "..\..\windows\vbutil32.dll" "..\..\windows\VBUTIL32.tlb"

CLEAN : 
	-@erase "$(INTDIR)\Test.obj"
	-@erase "$(INTDIR)\TOOLS.obj"
	-@erase "$(INTDIR)\VBUTIL.obj"
	-@erase "$(INTDIR)\VBUTIL.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WIN32.obj"
	-@erase "$(OUTDIR)\vbutil32.exp"
	-@erase "$(OUTDIR)\vbutil32.lib"
	-@erase "$(OUTDIR)\vbutil32.pdb"
	-@erase "..\..\windows\vbutil32.dll"
	-@erase "..\..\windows\vbutil32.ilk"
	-@erase "..\..\windows\VBUTIL32.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX"vbutil.h" /c
# SUBTRACT BASE CPP /nologo /Fr
# ADD CPP /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX"vbutil.h" /c
# SUBTRACT CPP /nologo /Fr
CPP_PROJ=/MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)/VBUTIL.pch" /YX"vbutil.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=".\Unicode Debug/"
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /D "WIN32" /win32
# ADD MTL /nologo /D "_DEBUG" /D "WIN32" /win32
MTL_PROJ=/nologo /D "_DEBUG" /D "WIN32" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "WIN32"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VBUTIL.res" /d "_DEBUG" /d "WIN32" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"c:\win95/VBUTIL32.bsc"
# ADD BSC32 /nologo /o"c:\win95/VBUTIL32.bsc"
BSC32_FLAGS=/nologo /o"c:\win95/VBUTIL32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleTypeUD.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"c:\win95\vbutil32.dll"
# SUBTRACT BASE LINK32 /map /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleTypeD.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"c:\windows\vbutil32.dll"
# SUBTRACT LINK32 /map /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleTypeD.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/vbutil32.pdb" /debug\
 /machine:I386 /def:".\vbutil.def" /out:"c:\windows\vbutil32.dll"\
 /implib:"$(OUTDIR)/vbutil32.lib" 
DEF_FILE= \
	".\vbutil.def"
LINK32_OBJS= \
	"$(INTDIR)\Test.obj" \
	"$(INTDIR)\TOOLS.obj" \
	"$(INTDIR)\VBUTIL.obj" \
	"$(INTDIR)\VBUTIL.res" \
	"$(INTDIR)\WIN32.obj"

"..\..\windows\vbutil32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ANSI Release"
# PROP BASE Intermediate_Dir "ANSI Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI Release"
# PROP Intermediate_Dir "ANSI Release"
# PROP Target_Dir ""
OUTDIR=.\ANSI Release
INTDIR=.\ANSI Release

ALL : "..\..\windows\vbutil32.dll" "..\..\windows\VBUTIL32.tlb"

CLEAN : 
	-@erase "$(INTDIR)\Test.obj"
	-@erase "$(INTDIR)\TOOLS.obj"
	-@erase "$(INTDIR)\VBUTIL.obj"
	-@erase "$(INTDIR)\VBUTIL.res"
	-@erase "$(INTDIR)\WIN32.obj"
	-@erase "$(OUTDIR)\vbutil32.exp"
	-@erase "$(OUTDIR)\vbutil32.lib"
	-@erase "..\..\windows\vbutil32.dll"
	-@erase "..\..\windows\VBUTIL32.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX"vbutil.h" /c
# SUBTRACT BASE CPP /nologo /Fr
# ADD CPP /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX"vbutil.h" /c
# SUBTRACT CPP /nologo /Fr
CPP_PROJ=/MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/VBUTIL.pch" /YX"vbutil.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=".\ANSI Release/"
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /D "WIN32" /win32
# ADD MTL /nologo /D "NDEBUG" /D "WIN32" /win32
MTL_PROJ=/nologo /D "NDEBUG" /D "WIN32" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "WIN32"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VBUTIL.res" /d "NDEBUG" /d "WIN32" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"c:\win95/VBUTIL32.bsc"
# ADD BSC32 /nologo /o"c:\win95/VBUTIL32.bsc"
BSC32_FLAGS=/nologo /o"c:\win95/VBUTIL32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib oletypeu.lib OleTypeA.lib /nologo /subsystem:windows /dll /machine:I386 /out:"c:\win95\vbutil32.dll"
# SUBTRACT BASE LINK32 /map /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleType.lib /nologo /subsystem:windows /dll /machine:I386 /out:"c:\windows\vbutil32.dll"
# SUBTRACT LINK32 /map /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleType.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/vbutil32.pdb"\
 /machine:I386 /def:".\vbutil.def" /out:"c:\windows\vbutil32.dll"\
 /implib:"$(OUTDIR)/vbutil32.lib" 
DEF_FILE= \
	".\vbutil.def"
LINK32_OBJS= \
	"$(INTDIR)\Test.obj" \
	"$(INTDIR)\TOOLS.obj" \
	"$(INTDIR)\VBUTIL.obj" \
	"$(INTDIR)\VBUTIL.res" \
	"$(INTDIR)\WIN32.obj"

"..\..\windows\vbutil32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Unicode Release"
# PROP BASE Intermediate_Dir "Unicode Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode Release"
# PROP Intermediate_Dir "Unicode Release"
# PROP Target_Dir ""
OUTDIR=.\Unicode Release
INTDIR=.\Unicode Release

ALL : "..\..\windows\vbutil32.dll" "..\..\windows\VBUTIL32.tlb"

CLEAN : 
	-@erase "$(INTDIR)\Test.obj"
	-@erase "$(INTDIR)\TOOLS.obj"
	-@erase "$(INTDIR)\VBUTIL.obj"
	-@erase "$(INTDIR)\VBUTIL.res"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WIN32.obj"
	-@erase "$(OUTDIR)\vbutil32.exp"
	-@erase "$(OUTDIR)\vbutil32.lib"
	-@erase "..\..\windows\vbutil32.dll"
	-@erase "..\..\windows\VBUTIL32.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX"vbutil.h" /c
# SUBTRACT BASE CPP /nologo /Fr
# ADD CPP /MT /W3 /GX /Zi /Ow /Og /Oi /Op- /Oy /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX"vbutil.h" /c
# SUBTRACT CPP /nologo /Ox /Ot /Oa /Os /Fr
CPP_PROJ=/MT /W3 /GX /Zi /Ow /Og /Oi /Op- /Oy /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)/VBUTIL.pch" /YX"vbutil.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=".\Unicode Release/"
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /D "WIN32" /win32
# ADD MTL /nologo /D "NDEBUG" /D "WIN32" /win32
MTL_PROJ=/nologo /D "NDEBUG" /D "WIN32" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "WIN32"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VBUTIL.res" /d "NDEBUG" /d "WIN32" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"c:\win95/VBUTIL32.bsc"
# ADD BSC32 /nologo /o"c:\win95/VBUTIL32.bsc"
BSC32_FLAGS=/nologo /o"c:\win95/VBUTIL32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleTypeU.lib /nologo /subsystem:windows /dll /machine:I386 /out:"c:\win95\vbutil32.dll"
# SUBTRACT BASE LINK32 /map /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleType.lib /nologo /subsystem:windows /dll /machine:I386 /out:"c:\windows\vbutil32.dll"
# SUBTRACT LINK32 /map /debug /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleType.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/vbutil32.pdb"\
 /machine:I386 /def:".\vbutil.def" /out:"c:\windows\vbutil32.dll"\
 /implib:"$(OUTDIR)/vbutil32.lib" 
DEF_FILE= \
	".\vbutil.def"
LINK32_OBJS= \
	"$(INTDIR)\Test.obj" \
	"$(INTDIR)\TOOLS.obj" \
	"$(INTDIR)\VBUTIL.obj" \
	"$(INTDIR)\VBUTIL.res" \
	"$(INTDIR)\WIN32.obj"

"..\..\windows\vbutil32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ANSI Debug"
# PROP BASE Intermediate_Dir "ANSI Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI Debug"
# PROP Intermediate_Dir "ANSI Debug"
# PROP Target_Dir ""
OUTDIR=.\ANSI Debug
INTDIR=.\ANSI Debug

ALL : "..\..\windows\vbutil32.dll" "..\..\windows\VBUTIL32.tlb"

CLEAN : 
	-@erase "$(INTDIR)\Test.obj"
	-@erase "$(INTDIR)\TOOLS.obj"
	-@erase "$(INTDIR)\VBUTIL.obj"
	-@erase "$(INTDIR)\VBUTIL.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WIN32.obj"
	-@erase "$(OUTDIR)\vbutil32.exp"
	-@erase "$(OUTDIR)\vbutil32.lib"
	-@erase "$(OUTDIR)\vbutil32.pdb"
	-@erase "..\..\windows\vbutil32.dll"
	-@erase "..\..\windows\vbutil32.ilk"
	-@erase "..\..\windows\VBUTIL32.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX"vbutil.h" /c
# SUBTRACT BASE CPP /nologo /Fr
# ADD CPP /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX"vbutil.h" /c
# SUBTRACT CPP /nologo /Fr
CPP_PROJ=/MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/VBUTIL.pch" /YX"vbutil.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=".\ANSI Debug/"
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /D "WIN32" /win32
# ADD MTL /nologo /D "_DEBUG" /D "WIN32" /win32
MTL_PROJ=/nologo /D "_DEBUG" /D "WIN32" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "WIN32"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VBUTIL.res" /d "_DEBUG" /d "WIN32" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"c:\win95/VBUTIL32.bsc"
# ADD BSC32 /nologo /o"c:\win95/VBUTIL32.bsc"
BSC32_FLAGS=/nologo /o"c:\win95/VBUTIL32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleTypeAD.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"c:\win95\vbutil32.dll"
# SUBTRACT BASE LINK32 /map /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleTypeD.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"c:\windows\vbutil32.dll"
# SUBTRACT LINK32 /map /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib OleTypeD.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/vbutil32.pdb" /debug\
 /machine:I386 /def:".\vbutil.def" /out:"c:\windows\vbutil32.dll"\
 /implib:"$(OUTDIR)/vbutil32.lib" 
DEF_FILE= \
	".\vbutil.def"
LINK32_OBJS= \
	"$(INTDIR)\Test.obj" \
	"$(INTDIR)\TOOLS.obj" \
	"$(INTDIR)\VBUTIL.obj" \
	"$(INTDIR)\VBUTIL.res" \
	"$(INTDIR)\WIN32.obj"

"..\..\windows\vbutil32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "VBUTIL - Win32 Unicode Debug"
# Name "VBUTIL - Win32 ANSI Release"
# Name "VBUTIL - Win32 Unicode Release"
# Name "VBUTIL - Win32 ANSI Debug"

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\VBUTIL.RC

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"


"$(INTDIR)\VBUTIL.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VBUTIL.res" /i "Unicode Debug" /d "_DEBUG" /d\
 "WIN32" $(SOURCE)


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"


"$(INTDIR)\VBUTIL.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VBUTIL.res" /i "ANSI Release" /d "NDEBUG" /d\
 "WIN32" $(SOURCE)


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"


"$(INTDIR)\VBUTIL.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VBUTIL.res" /i "Unicode Release" /d "NDEBUG"\
 /d "WIN32" $(SOURCE)


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"


"$(INTDIR)\VBUTIL.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VBUTIL.res" /i "ANSI Debug" /d "_DEBUG" /d\
 "WIN32" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VBUTIL.ODL
DEP_MTL_VBUTI=\
	{$(INCLUDE)}"\OLETYPE.ODL"\
	{$(INCLUDE)}"\wintype.odl"\
	

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"

# ADD BASE MTL /tlb "c:\win95\VBUTIL32.tlb"
# SUBTRACT BASE MTL /D "WIN32"
# ADD MTL /tlb "c:\windows\VBUTIL32.tlb"
# SUBTRACT MTL /D "WIN32"

"..\..\windows\VBUTIL32.tlb" : $(SOURCE) $(DEP_MTL_VBUTI) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "c:\windows\VBUTIL32.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"

# ADD BASE MTL /tlb "c:\win95\VBUTIL32.tlb"
# SUBTRACT BASE MTL /D "WIN32"
# ADD MTL /tlb "c:\windows\VBUTIL32.tlb"
# SUBTRACT MTL /D "WIN32"

"..\..\windows\VBUTIL32.tlb" : $(SOURCE) $(DEP_MTL_VBUTI) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "c:\windows\VBUTIL32.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"

# ADD BASE MTL /tlb "c:\win95\VBUTIL32.tlb"
# SUBTRACT BASE MTL /D "WIN32"
# ADD MTL /tlb "c:\windows\VBUTIL32.tlb"
# SUBTRACT MTL /D "WIN32"

"..\..\windows\VBUTIL32.tlb" : $(SOURCE) $(DEP_MTL_VBUTI) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "c:\windows\VBUTIL32.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"

# ADD BASE MTL /tlb "c:\win95\VBUTIL32.tlb"
# SUBTRACT BASE MTL /D "WIN32"
# ADD MTL /tlb "c:\windows\VBUTIL32.tlb"
# SUBTRACT MTL /D "WIN32"

"..\..\windows\VBUTIL32.tlb" : $(SOURCE) $(DEP_MTL_VBUTI) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "c:\windows\VBUTIL32.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOOLS.cpp
DEP_CPP_TOOLS=\
	"..\..\MSDEV\INCLUDE\BString.H"\
	"..\..\MSDEV\INCLUDE\SafeArray.H"\
	".\TOOLS.H"\
	".\VBUTIL.H"\
	{$(INCLUDE)}"\OleType.H"\
	

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"


"$(INTDIR)\TOOLS.obj" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"


"$(INTDIR)\TOOLS.obj" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"


"$(INTDIR)\TOOLS.obj" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"


"$(INTDIR)\TOOLS.obj" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WIN32.cpp
DEP_CPP_WIN32=\
	"..\..\MSDEV\INCLUDE\BString.H"\
	"..\..\MSDEV\INCLUDE\SafeArray.H"\
	".\VBUTIL.H"\
	".\WIN32.H"\
	{$(INCLUDE)}"\OleType.H"\
	

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"


"$(INTDIR)\WIN32.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"


"$(INTDIR)\WIN32.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"


"$(INTDIR)\WIN32.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"


"$(INTDIR)\WIN32.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VBUTIL.cpp
DEP_CPP_VBUTIL=\
	"..\..\MSDEV\INCLUDE\BString.H"\
	"..\..\MSDEV\INCLUDE\SafeArray.H"\
	".\VBUTIL.H"\
	{$(INCLUDE)}"\OleType.H"\
	

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"


"$(INTDIR)\VBUTIL.obj" : $(SOURCE) $(DEP_CPP_VBUTIL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"


"$(INTDIR)\VBUTIL.obj" : $(SOURCE) $(DEP_CPP_VBUTIL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"


"$(INTDIR)\VBUTIL.obj" : $(SOURCE) $(DEP_CPP_VBUTIL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"


"$(INTDIR)\VBUTIL.obj" : $(SOURCE) $(DEP_CPP_VBUTIL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vbutil.def

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Test.Cpp
DEP_CPP_TEST_=\
	"..\..\MSDEV\INCLUDE\BString.H"\
	"..\..\MSDEV\INCLUDE\SafeArray.H"\
	".\TEST.H"\
	".\VBUTIL.H"\
	{$(INCLUDE)}"\OleType.H"\
	

!IF  "$(CFG)" == "VBUTIL - Win32 Unicode Debug"


"$(INTDIR)\Test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Release"


"$(INTDIR)\Test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 Unicode Release"


"$(INTDIR)\Test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VBUTIL - Win32 ANSI Debug"


"$(INTDIR)\Test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
