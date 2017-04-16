# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=texture - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to texture - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "texture - Win32 Release" && "$(CFG)" !=\
 "texture - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "texture.mak" CFG="texture - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "texture - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "texture - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "texture - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "texture - Win32 Release"

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

ALL : "$(OUTDIR)\texture.exe"

CLEAN : 
	-@erase "$(INTDIR)\File.obj"
	-@erase "$(INTDIR)\Props.obj"
	-@erase "$(INTDIR)\rmerror.obj"
	-@erase "$(INTDIR)\Rmtex.obj"
	-@erase "$(INTDIR)\Rmtex.res"
	-@erase "$(INTDIR)\Tex1.obj"
	-@erase "$(OUTDIR)\texture.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/texture.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Rmtex.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/texture.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib dxguid.lib ddraw.lib d3drm.lib Comctl32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmm.lib dxguid.lib ddraw.lib d3drm.lib Comctl32.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/texture.pdb" /machine:I386\
 /out:"$(OUTDIR)/texture.exe" 
LINK32_OBJS= \
	"$(INTDIR)\File.obj" \
	"$(INTDIR)\Props.obj" \
	"$(INTDIR)\rmerror.obj" \
	"$(INTDIR)\Rmtex.obj" \
	"$(INTDIR)\Rmtex.res" \
	"$(INTDIR)\Tex1.obj"

"$(OUTDIR)\texture.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "texture - Win32 Debug"

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

ALL : "$(OUTDIR)\texture.exe" "$(OUTDIR)\texture.bsc"

CLEAN : 
	-@erase "$(INTDIR)\File.obj"
	-@erase "$(INTDIR)\File.sbr"
	-@erase "$(INTDIR)\Props.obj"
	-@erase "$(INTDIR)\Props.sbr"
	-@erase "$(INTDIR)\rmerror.obj"
	-@erase "$(INTDIR)\rmerror.sbr"
	-@erase "$(INTDIR)\Rmtex.obj"
	-@erase "$(INTDIR)\Rmtex.res"
	-@erase "$(INTDIR)\Rmtex.sbr"
	-@erase "$(INTDIR)\Tex1.obj"
	-@erase "$(INTDIR)\Tex1.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\texture.bsc"
	-@erase "$(OUTDIR)\texture.exe"
	-@erase "$(OUTDIR)\texture.ilk"
	-@erase "$(OUTDIR)\texture.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/texture.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Rmtex.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/texture.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\File.sbr" \
	"$(INTDIR)\Props.sbr" \
	"$(INTDIR)\rmerror.sbr" \
	"$(INTDIR)\Rmtex.sbr" \
	"$(INTDIR)\Tex1.sbr"

"$(OUTDIR)\texture.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib dxguid.lib ddraw.lib d3drm.lib Comctl32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmm.lib dxguid.lib ddraw.lib d3drm.lib Comctl32.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/texture.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/texture.exe" 
LINK32_OBJS= \
	"$(INTDIR)\File.obj" \
	"$(INTDIR)\Props.obj" \
	"$(INTDIR)\rmerror.obj" \
	"$(INTDIR)\Rmtex.obj" \
	"$(INTDIR)\Rmtex.res" \
	"$(INTDIR)\Tex1.obj"

"$(OUTDIR)\texture.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "texture - Win32 Release"
# Name "texture - Win32 Debug"

!IF  "$(CFG)" == "texture - Win32 Release"

!ELSEIF  "$(CFG)" == "texture - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\File.cpp
DEP_CPP_FILE_=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcaps.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmdef.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmobj.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dtypes.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dvec.inl"\
	".\Rmtex.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	
NODEP_CPP_FILE_=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcom.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\subwtype.h"\
	

!IF  "$(CFG)" == "texture - Win32 Release"


"$(INTDIR)\File.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "texture - Win32 Debug"


"$(INTDIR)\File.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"

"$(INTDIR)\File.sbr" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rmtex.cpp

!IF  "$(CFG)" == "texture - Win32 Release"

DEP_CPP_RMTEX=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcaps.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmdef.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmobj.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dtypes.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dvec.inl"\
	".\Props.h"\
	".\Rmdemo.h"\
	".\Rmtex.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\rmerror.h"\
	
NODEP_CPP_RMTEX=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcom.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\subwtype.h"\
	

"$(INTDIR)\Rmtex.obj" : $(SOURCE) $(DEP_CPP_RMTEX) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "texture - Win32 Debug"

DEP_CPP_RMTEX=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmdef.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmobj.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dtypes.h"\
	".\Props.h"\
	".\Rmdemo.h"\
	".\Rmtex.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\rmerror.h"\
	

"$(INTDIR)\Rmtex.obj" : $(SOURCE) $(DEP_CPP_RMTEX) "$(INTDIR)"

"$(INTDIR)\Rmtex.sbr" : $(SOURCE) $(DEP_CPP_RMTEX) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tex1.c

!IF  "$(CFG)" == "texture - Win32 Release"

DEP_CPP_TEX1_=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcaps.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmdef.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmobj.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dtypes.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dvec.inl"\
	".\Rmdemo.h"\
	".\Rmtex.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\rmerror.h"\
	
NODEP_CPP_TEX1_=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcom.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\subwtype.h"\
	

"$(INTDIR)\Tex1.obj" : $(SOURCE) $(DEP_CPP_TEX1_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "texture - Win32 Debug"

DEP_CPP_TEX1_=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcaps.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmdef.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmobj.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dtypes.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dvec.inl"\
	".\Rmdemo.h"\
	".\Rmtex.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\rmerror.h"\
	
NODEP_CPP_TEX1_=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcom.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\subwtype.h"\
	".\tSx"\
	".\tSy"\
	

"$(INTDIR)\Tex1.obj" : $(SOURCE) $(DEP_CPP_TEX1_) "$(INTDIR)"

"$(INTDIR)\Tex1.sbr" : $(SOURCE) $(DEP_CPP_TEX1_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rmtex.rc
DEP_RSC_RMTEX_=\
	".\..\misc\d3d.ico"\
	".\Props.h"\
	".\Rmtex.h"\
	

"$(INTDIR)\Rmtex.res" : $(SOURCE) $(DEP_RSC_RMTEX_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dxsdk\sdk\samples\misc\rmerror.c
DEP_CPP_RMERR=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcaps.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmdef.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmobj.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dtypes.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dvec.inl"\
	"..\misc\rmerror.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	
NODEP_CPP_RMERR=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dcom.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\subwtype.h"\
	

!IF  "$(CFG)" == "texture - Win32 Release"


"$(INTDIR)\rmerror.obj" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "texture - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\rmerror.obj" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\rmerror.sbr" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Props.c

!IF  "$(CFG)" == "texture - Win32 Release"

DEP_CPP_PROPS=\
	".\Props.h"\
	".\Rmtex.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	

"$(INTDIR)\Props.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "texture - Win32 Debug"

DEP_CPP_PROPS=\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmdef.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3drmobj.h"\
	"..\..\..\..\Dxsdk-5\sdk\inc\d3dtypes.h"\
	".\Props.h"\
	".\Rmtex.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	
NODEP_CPP_PROPS=\
	".\win"\
	

"$(INTDIR)\Props.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"

"$(INTDIR)\Props.sbr" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
