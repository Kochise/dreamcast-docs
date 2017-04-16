# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=persistant - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to persistant - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "persistant - Win32 Release" && "$(CFG)" !=\
 "persistant - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "persist.mak" CFG="persistant - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "persistant - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "persistant - Win32 Debug" (based on\
 "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "persistant - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "persistant - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\persist.exe"

CLEAN : 
	-@erase "$(INTDIR)\dynamic.obj"
	-@erase "$(INTDIR)\mfc_pers.obj"
	-@erase "$(INTDIR)\persist.obj"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(OUTDIR)\persist.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/persist.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/persist.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/persist.pdb" /machine:I386 /out:"$(OUTDIR)/persist.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dynamic.obj" \
	"$(INTDIR)\mfc_pers.obj" \
	"$(INTDIR)\persist.obj" \
	"$(INTDIR)\test.obj"

"$(OUTDIR)\persist.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "persistant - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\persist.exe" "$(OUTDIR)\persist.bsc"

CLEAN : 
	-@erase "$(INTDIR)\dynamic.obj"
	-@erase "$(INTDIR)\dynamic.sbr"
	-@erase "$(INTDIR)\mfc_pers.obj"
	-@erase "$(INTDIR)\mfc_pers.sbr"
	-@erase "$(INTDIR)\persist.obj"
	-@erase "$(INTDIR)\persist.sbr"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\test.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\persist.bsc"
	-@erase "$(OUTDIR)\persist.exe"
	-@erase "$(OUTDIR)\persist.ilk"
	-@erase "$(OUTDIR)\persist.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /FR"$(INTDIR)/" /Fp"$(INTDIR)/persist.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/persist.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dynamic.sbr" \
	"$(INTDIR)\mfc_pers.sbr" \
	"$(INTDIR)\persist.sbr" \
	"$(INTDIR)\test.sbr"

"$(OUTDIR)\persist.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/persist.pdb" /debug /machine:I386 /out:"$(OUTDIR)/persist.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dynamic.obj" \
	"$(INTDIR)\mfc_pers.obj" \
	"$(INTDIR)\persist.obj" \
	"$(INTDIR)\test.obj"

"$(OUTDIR)\persist.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "persistant - Win32 Release"
# Name "persistant - Win32 Debug"

!IF  "$(CFG)" == "persistant - Win32 Release"

!ELSEIF  "$(CFG)" == "persistant - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\dynamic.cpp
DEP_CPP_DYNAM=\
	".\dynamic.h"\
	

!IF  "$(CFG)" == "persistant - Win32 Release"


"$(INTDIR)\dynamic.obj" : $(SOURCE) $(DEP_CPP_DYNAM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "persistant - Win32 Debug"


"$(INTDIR)\dynamic.obj" : $(SOURCE) $(DEP_CPP_DYNAM) "$(INTDIR)"

"$(INTDIR)\dynamic.sbr" : $(SOURCE) $(DEP_CPP_DYNAM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\test.cpp

!IF  "$(CFG)" == "persistant - Win32 Release"

DEP_CPP_TEST_=\
	".\dynamic.h"\
	".\persist.h"\
	

"$(INTDIR)\test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "persistant - Win32 Debug"

DEP_CPP_TEST_=\
	".\dynamic.h"\
	".\persist.h"\
	

"$(INTDIR)\test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"

"$(INTDIR)\test.sbr" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\persist.cpp

!IF  "$(CFG)" == "persistant - Win32 Release"

DEP_CPP_PERSI=\
	".\dynamic.h"\
	".\persist.h"\
	

"$(INTDIR)\persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "persistant - Win32 Debug"

DEP_CPP_PERSI=\
	".\dynamic.h"\
	".\persist.h"\
	

"$(INTDIR)\persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"

"$(INTDIR)\persist.sbr" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mfc_pers.cpp
DEP_CPP_MFC_P=\
	".\dynamic.h"\
	".\mfc_pers.h"\
	".\persist.h"\
	

!IF  "$(CFG)" == "persistant - Win32 Release"


"$(INTDIR)\mfc_pers.obj" : $(SOURCE) $(DEP_CPP_MFC_P) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "persistant - Win32 Debug"


"$(INTDIR)\mfc_pers.obj" : $(SOURCE) $(DEP_CPP_MFC_P) "$(INTDIR)"

"$(INTDIR)\mfc_pers.sbr" : $(SOURCE) $(DEP_CPP_MFC_P) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
