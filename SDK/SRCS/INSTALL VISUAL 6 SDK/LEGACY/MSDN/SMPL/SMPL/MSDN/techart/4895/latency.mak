# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Thk3216 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Thk3216 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Latency - Win32 Release" && "$(CFG)" !=\
 "Latency - Win32 Debug" && "$(CFG)" != "Timer32 - Win32 Release" && "$(CFG)" !=\
 "Timer32 - Win32 Debug" && "$(CFG)" != "Thk3216 - Win32 Release" && "$(CFG)" !=\
 "Thk3216 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Latency.mak" CFG="Thk3216 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Latency - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Latency - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Timer32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Timer32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Thk3216 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Thk3216 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Thk3216 - Win32 Debug"

!IF  "$(CFG)" == "Latency - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\Release

ALL : "Thk3216 - Win32 Release" "Timer32 - Win32 Release"\
 "$(OUTDIR)\Latency.exe"

CLEAN : 
	-@erase ".\Latency.exe"
	-@erase ".\Release\latency.obj"
	-@erase ".\Release\latency.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Latency.pch" /YX /Fo"$(INTDIR)/" /c 
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
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/latency.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Latency.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 user32.lib gdi32.lib version.lib winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=user32.lib gdi32.lib version.lib winmm.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Latency.pdb" /machine:I386\
 /out:"$(OUTDIR)/Latency.exe" 
LINK32_OBJS= \
	"$(INTDIR)/latency.obj" \
	"$(INTDIR)/latency.res" \
	".\Timer32.lib" \
	".\Thk3216.lib"

"$(OUTDIR)\Latency.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Latency - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\Debug

ALL : "Thk3216 - Win32 Debug" "Timer32 - Win32 Debug" "$(OUTDIR)\Latency.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Latency.exe"
	-@erase ".\Debug\latency.obj"
	-@erase ".\Debug\latency.res"
	-@erase ".\Latency.ilk"
	-@erase ".\Latency.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Latency.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/latency.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Latency.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 user32.lib gdi32.lib version.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=user32.lib gdi32.lib version.lib winmm.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/Latency.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/Latency.exe" 
LINK32_OBJS= \
	"$(INTDIR)/latency.obj" \
	"$(INTDIR)/latency.res" \
	".\Timer32.lib" \
	".\Thk3216.lib"

"$(OUTDIR)\Latency.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Timer32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Timer32\Release"
# PROP BASE Intermediate_Dir "Timer32\Release"
# PROP BASE Target_Dir "Timer32"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "Timer32\Release"
# PROP Target_Dir "Timer32"
OUTDIR=.\.
INTDIR=.\Timer32\Release

ALL : "$(OUTDIR)\Timer32.dll"

CLEAN : 
	-@erase ".\Timer32.dll"
	-@erase ".\Timer32\Release\timer32.obj"
	-@erase ".\Timer32.lib"
	-@erase ".\Timer32.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Timer32.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Timer32\Release/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Timer32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=user32.lib winmm.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Timer32.pdb" /machine:I386\
 /out:"$(OUTDIR)/Timer32.dll" /implib:"$(OUTDIR)/Timer32.lib" 
LINK32_OBJS= \
	"$(INTDIR)/timer32.obj"

"$(OUTDIR)\Timer32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Timer32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Timer32\Debug"
# PROP BASE Intermediate_Dir "Timer32\Debug"
# PROP BASE Target_Dir "Timer32"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "Timer32\Debug"
# PROP Target_Dir "Timer32"
OUTDIR=.\.
INTDIR=.\Timer32\Debug

ALL : "$(OUTDIR)\Timer32.dll"

CLEAN : 
	-@erase ".\Timer32\Debug\vc40.pdb"
	-@erase ".\Timer32\Debug\vc40.idb"
	-@erase ".\Timer32.dll"
	-@erase ".\Timer32\Debug\timer32.obj"
	-@erase ".\Timer32.ilk"
	-@erase ".\Timer32.lib"
	-@erase ".\Timer32.exp"
	-@erase ".\Timer32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Timer32.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Timer32\Debug/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Timer32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 user32.lib winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=user32.lib winmm.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/Timer32.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Timer32.dll" /implib:"$(OUTDIR)/Timer32.lib" 
LINK32_OBJS= \
	"$(INTDIR)/timer32.obj"

"$(OUTDIR)\Timer32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Thk3216 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Thk3216\Release"
# PROP BASE Intermediate_Dir "Thk3216\Release"
# PROP BASE Target_Dir "Thk3216"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "Thk3216\Release"
# PROP Target_Dir "Thk3216"
OUTDIR=.\.
INTDIR=.\Thk3216\Release

ALL : "$(OUTDIR)\Thk3216.dll"

CLEAN : 
	-@erase ".\Thk3216.dll"
	-@erase ".\Thk3216\Release\thk3216.obj"
	-@erase ".\Thk3216.lib"
	-@erase ".\Thk3216.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Thk3216.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Thk3216\Release/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Thk3216.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 thunk32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=thunk32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Thk3216.pdb" /machine:I386 /def:".\thk3216.def"\
 /out:"$(OUTDIR)/Thk3216.dll" /implib:"$(OUTDIR)/Thk3216.lib" 
DEF_FILE= \
	".\thk3216.def"
LINK32_OBJS= \
	".\thk32.obj" \
	"$(INTDIR)/thk3216.obj"

"$(OUTDIR)\Thk3216.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Thk3216 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Thk3216\Debug"
# PROP BASE Intermediate_Dir "Thk3216\Debug"
# PROP BASE Target_Dir "Thk3216"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "Thk3216\Debug"
# PROP Target_Dir "Thk3216"
OUTDIR=.\.
INTDIR=.\Thk3216\Debug

ALL : "$(OUTDIR)\Thk3216.dll"

CLEAN : 
	-@erase ".\Thk3216\Debug\vc40.pdb"
	-@erase ".\Thk3216\Debug\vc40.idb"
	-@erase ".\Thk3216.dll"
	-@erase ".\Thk3216\Debug\thk3216.obj"
	-@erase ".\Thk3216.ilk"
	-@erase ".\Thk3216.lib"
	-@erase ".\Thk3216.exp"
	-@erase ".\Thk3216.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Thk3216.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Thk3216\Debug/
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Thk3216.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 thunk32.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=thunk32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Thk3216.pdb" /debug /machine:I386 /def:".\thk3216.def"\
 /out:"$(OUTDIR)/Thk3216.dll" /implib:"$(OUTDIR)/Thk3216.lib" 
DEF_FILE= \
	".\thk3216.def"
LINK32_OBJS= \
	".\thk32.obj" \
	"$(INTDIR)/thk3216.obj"

"$(OUTDIR)\Thk3216.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "Latency - Win32 Release"
# Name "Latency - Win32 Debug"

!IF  "$(CFG)" == "Latency - Win32 Release"

!ELSEIF  "$(CFG)" == "Latency - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\latency.rc
DEP_RSC_LATEN=\
	".\LATENCY.ICO"\
	".\SMALL.ICO"\
	".\Latency.h"\
	

"$(INTDIR)\latency.res" : $(SOURCE) $(DEP_RSC_LATEN) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\latency.c
DEP_CPP_LATENC=\
	".\Latency.h"\
	".\Timer.h"\
	".\Timer32.h"\
	

"$(INTDIR)\latency.obj" : $(SOURCE) $(DEP_CPP_LATENC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "Timer32"

!IF  "$(CFG)" == "Latency - Win32 Release"

"Timer32 - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Latency.mak CFG="Timer32 - Win32 Release" 

!ELSEIF  "$(CFG)" == "Latency - Win32 Debug"

"Timer32 - Win32 Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Latency.mak CFG="Timer32 - Win32 Debug" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Project Dependency

# Project_Dep_Name "Thk3216"

!IF  "$(CFG)" == "Latency - Win32 Release"

"Thk3216 - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Latency.mak CFG="Thk3216 - Win32 Release" 

!ELSEIF  "$(CFG)" == "Latency - Win32 Debug"

"Thk3216 - Win32 Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F .\Latency.mak CFG="Thk3216 - Win32 Debug" 

!ENDIF 

# End Project Dependency
# End Target
################################################################################
# Begin Target

# Name "Timer32 - Win32 Release"
# Name "Timer32 - Win32 Debug"

!IF  "$(CFG)" == "Timer32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Timer32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\timer32.c

!IF  "$(CFG)" == "Timer32 - Win32 Release"

DEP_CPP_TIMER=\
	".\Debug.h"\
	".\Timer.h"\
	".\Timer32.h"\
	

"$(INTDIR)\timer32.obj" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Timer32 - Win32 Debug"

DEP_CPP_TIMER=\
	".\Debug.h"\
	".\Timer.h"\
	".\Timer32.h"\
	

"$(INTDIR)\timer32.obj" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
################################################################################
# Begin Target

# Name "Thk3216 - Win32 Release"
# Name "Thk3216 - Win32 Debug"

!IF  "$(CFG)" == "Thk3216 - Win32 Release"

!ELSEIF  "$(CFG)" == "Thk3216 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\thk3216.c
DEP_CPP_THK32=\
	".\Debug.h"\
	".\Thk3216.h"\
	

"$(INTDIR)\thk3216.obj" : $(SOURCE) $(DEP_CPP_THK32) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\thk32.obj

!IF  "$(CFG)" == "Thk3216 - Win32 Release"

!ELSEIF  "$(CFG)" == "Thk3216 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\thk3216.def

!IF  "$(CFG)" == "Thk3216 - Win32 Release"

!ELSEIF  "$(CFG)" == "Thk3216 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
