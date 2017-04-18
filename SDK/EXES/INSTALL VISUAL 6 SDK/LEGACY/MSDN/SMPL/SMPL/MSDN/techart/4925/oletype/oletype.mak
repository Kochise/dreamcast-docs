# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=oletype - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to oletype - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "oletype - Win32 Debug" && "$(CFG)" !=\
 "oletype - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "oletype.mak" CFG="oletype - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oletype - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oletype - Win32 Release" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "oletype - Win32 Release"
CPP=cl.exe

!IF  "$(CFG)" == "oletype - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "oletype_"
# PROP BASE Intermediate_Dir "oletype_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "oletype_"
# PROP Intermediate_Dir "oletype_"
# PROP Target_Dir ""
OUTDIR=.\oletype_
INTDIR=.\oletype_

ALL : "..\..\msdev\lib\OleTypeD.Lib"

CLEAN : 
	-@erase "$(INTDIR)\BString.obj"
	-@erase "$(INTDIR)\Variant.obj"
	-@erase "..\..\msdev\lib\OleTypeD.Lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# SUBTRACT BASE CPP /YX
# ADD CPP /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /nologo /YX
CPP_PROJ=/MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\oletype_/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/oletype.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /out:"c:\msdev\lib\OleTypeAD.Lib"
# SUBTRACT BASE LIB32 /nologo
# ADD LIB32 /out:"c:\msdev\lib\OleTypeD.Lib"
# SUBTRACT LIB32 /nologo
LIB32_FLAGS=/out:"c:\msdev\lib\OleTypeD.Lib" 
LIB32_OBJS= \
	"$(INTDIR)\BString.obj" \
	"$(INTDIR)\Variant.obj"

"..\..\msdev\lib\OleTypeD.Lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "oletype - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "oletype0"
# PROP BASE Intermediate_Dir "oletype0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "oletype0"
# PROP Intermediate_Dir "oletype0"
# PROP Target_Dir ""
OUTDIR=.\oletype0
INTDIR=.\oletype0

ALL : "..\..\msdev\lib\OleType.Lib" "$(OUTDIR)\oletype.bsc"

CLEAN : 
	-@erase "$(INTDIR)\BString.obj"
	-@erase "$(INTDIR)\BString.sbr"
	-@erase "$(INTDIR)\Variant.obj"
	-@erase "$(INTDIR)\Variant.sbr"
	-@erase "$(OUTDIR)\oletype.bsc"
	-@erase "..\..\msdev\lib\OleType.Lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# SUBTRACT BASE CPP /nologo /YX
# ADD CPP /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# SUBTRACT CPP /nologo /YX
CPP_PROJ=/MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)/"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\oletype0/
CPP_SBRS=.\oletype0/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/oletype.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BString.sbr" \
	"$(INTDIR)\Variant.sbr"

"$(OUTDIR)\oletype.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /out:"c:\msdev\lib\OleTypeA.Lib"
# SUBTRACT BASE LIB32 /nologo
# ADD LIB32 /out:"c:\msdev\lib\OleType.Lib"
# SUBTRACT LIB32 /nologo
LIB32_FLAGS=/out:"c:\msdev\lib\OleType.Lib" 
LIB32_OBJS= \
	"$(INTDIR)\BString.obj" \
	"$(INTDIR)\Variant.obj"

"..\..\msdev\lib\OleType.Lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

# Name "oletype - Win32 Debug"
# Name "oletype - Win32 Release"

!IF  "$(CFG)" == "oletype - Win32 Debug"

!ELSEIF  "$(CFG)" == "oletype - Win32 Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\BString.Cpp
DEP_CPP_BSTRI=\
	{$(INCLUDE)}"\BString.H"\
	{$(INCLUDE)}"\OleType.H"\
	{$(INCLUDE)}"\SafeArray.H"\
	

!IF  "$(CFG)" == "oletype - Win32 Debug"


"$(INTDIR)\BString.obj" : $(SOURCE) $(DEP_CPP_BSTRI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "oletype - Win32 Release"


"$(INTDIR)\BString.obj" : $(SOURCE) $(DEP_CPP_BSTRI) "$(INTDIR)"

"$(INTDIR)\BString.sbr" : $(SOURCE) $(DEP_CPP_BSTRI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Variant.cpp
DEP_CPP_VARIA=\
	{$(INCLUDE)}"\BString.H"\
	{$(INCLUDE)}"\OleType.H"\
	{$(INCLUDE)}"\SafeArray.H"\
	

!IF  "$(CFG)" == "oletype - Win32 Debug"


"$(INTDIR)\Variant.obj" : $(SOURCE) $(DEP_CPP_VARIA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "oletype - Win32 Release"


"$(INTDIR)\Variant.obj" : $(SOURCE) $(DEP_CPP_VARIA) "$(INTDIR)"

"$(INTDIR)\Variant.sbr" : $(SOURCE) $(DEP_CPP_VARIA) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
