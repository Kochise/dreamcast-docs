# Microsoft Visual C++ Generated NMAKE File, Format Version 40000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=ShareMe - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ShareMe - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ShareMe - Win32 Release" && "$(CFG)" !=\
 "ShareMe - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ShareMe.mak" CFG="ShareMe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ShareMe - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ShareMe - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "ShareMe - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ShareMe - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir Release
# PROP BASE Intermediate_Dir Release
# PROP BASE Target_Dir
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir Release
# PROP Intermediate_Dir Release
# PROP Target_Dir
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\ShareMe.dll"

CLEAN : 
	-@erase ".\Release\ShareMe.dll"
	-@erase ".\Release\Svc.obj"
	-@erase ".\Release\SharedObj.obj"
	-@erase ".\Release\SharedPoint.obj"
	-@erase ".\Release\ShareMe.lib"
	-@erase ".\Release\ShareMe.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/ShareMe.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ShareMe.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ShareMe.pdb" /machine:I386 /def:".\ShareMe.def"\
 /out:"$(OUTDIR)/ShareMe.dll" /implib:"$(OUTDIR)/ShareMe.lib" 
DEF_FILE= \
	".\ShareMe.def"
LINK32_OBJS= \
	"$(INTDIR)/Svc.obj" \
	"$(INTDIR)/SharedObj.obj" \
	"$(INTDIR)/SharedPoint.obj"

"$(OUTDIR)\ShareMe.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ShareMe - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir Debug
# PROP BASE Intermediate_Dir Debug
# PROP BASE Target_Dir
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir Debug
# PROP Intermediate_Dir Debug
# PROP Target_Dir
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\ShareMe.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\ShareMe.dll"
	-@erase ".\Debug\Svc.obj"
	-@erase ".\Debug\SharedObj.obj"
	-@erase ".\Debug\SharedPoint.obj"
	-@erase ".\Debug\ShareMe.ilk"
	-@erase ".\Debug\ShareMe.lib"
	-@erase ".\Debug\ShareMe.exp"
	-@erase ".\Debug\ShareMe.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/ShareMe.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ShareMe.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ShareMe.pdb" /debug /machine:I386 /def:".\ShareMe.def"\
 /out:"$(OUTDIR)/ShareMe.dll" /implib:"$(OUTDIR)/ShareMe.lib" 
DEF_FILE= \
	".\ShareMe.def"
LINK32_OBJS= \
	"$(INTDIR)/Svc.obj" \
	"$(INTDIR)/SharedObj.obj" \
	"$(INTDIR)/SharedPoint.obj"

"$(OUTDIR)\ShareMe.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "ShareMe - Win32 Release"
# Name "ShareMe - Win32 Debug"

!IF  "$(CFG)" == "ShareMe - Win32 Release"

!ELSEIF  "$(CFG)" == "ShareMe - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SharedObj.cpp
DEP_CPP_SHARE=\
	".\SharedObj.h"\
	

!IF  "$(CFG)" == "ShareMe - Win32 Release"


"$(INTDIR)\SharedObj.obj" : $(SOURCE) $(DEP_CPP_SHARE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ShareMe - Win32 Debug"


"$(INTDIR)\SharedObj.obj" : $(SOURCE) $(DEP_CPP_SHARE) "$(INTDIR)"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SHARE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ShareMe.def

!IF  "$(CFG)" == "ShareMe - Win32 Release"

!ELSEIF  "$(CFG)" == "ShareMe - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Svc.cpp
DEP_CPP_SVC_C=\
	".\CF.h"\
	".\S816.h"\
	".\SharedPoint.h"\
	".\IPoint.h"\
	".\SharedObj.h"\
	

!IF  "$(CFG)" == "ShareMe - Win32 Release"


"$(INTDIR)\Svc.obj" : $(SOURCE) $(DEP_CPP_SVC_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ShareMe - Win32 Debug"


"$(INTDIR)\Svc.obj" : $(SOURCE) $(DEP_CPP_SVC_C) "$(INTDIR)"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SVC_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SharedPoint.cpp
DEP_CPP_SHARED=\
	".\SharedPoint.h"\
	".\IPoint.h"\
	".\SharedObj.h"\
	

!IF  "$(CFG)" == "ShareMe - Win32 Release"


"$(INTDIR)\SharedPoint.obj" : $(SOURCE) $(DEP_CPP_SHARED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ShareMe - Win32 Debug"


"$(INTDIR)\SharedPoint.obj" : $(SOURCE) $(DEP_CPP_SHARED) "$(INTDIR)"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SHARED) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
