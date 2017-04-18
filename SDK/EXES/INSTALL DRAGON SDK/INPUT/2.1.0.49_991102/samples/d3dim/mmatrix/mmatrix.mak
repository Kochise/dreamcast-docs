# Microsoft Developer Studio Generated NMAKE File, Based on mmatrix.dsp
!IF "$(CFG)" == ""
CFG=mmatrix - Win32 (WCE SH4) Debug
!MESSAGE No configuration specified. Defaulting to mmatrix - Win32 (WCE SH4) Debug.
!ENDIF 

!IF "$(CESubsystem)" == ""
CESubsystem=windowsce,2.0
!MESSAGE Variable CESubsystem not specified. Defaulting to windowsce,2.0
!ENDIF 

!IF "$(CEVersion)" == ""
CEVersion=200
!MESSAGE Variable CEVersion not specified. Defaulting to 200
!ENDIF 

!IF "$(CEConfigName)" == ""
CEConfigName=H/PC Ver. 2.00
!MESSAGE Variable CEConfigName not specified.  Defaulting to H/PC Ver. 2.00
!ENDIF 

!IF $(CEVersion) < 201
CECrt=L
CECrtDebug=Ld
CECrtMT=T
CECrtMTDebug=Td
CENoDefaultLib=corelibc.lib
CEx86Corelibc= 
!ELSE 
CECrt=C
CECrtDebug=C
CECrtMT=C
CECrtMTDebug=C
CENoDefaultLib=libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib
CEx86Corelibc=corelibc.lib
!ENDIF 

!IF "$(CFG)" != "mmatrix - Win32 (WCE SH4) Release" && "$(CFG)" != "mmatrix - Win32 (WCE SH4) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mmatrix.mak" CFG="mmatrix - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mmatrix - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "mmatrix - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "mmatrix - Win32 (WCE SH4) Release"

OUTDIR=.\retail
INTDIR=.\retail

ALL : "..\..\..\release\retail\Samples\mmatrix.exe"


CLEAN :
	-@erase "$(INTDIR)\d3dmath.obj"
	-@erase "$(INTDIR)\D3DUtil.obj"
	-@erase "$(INTDIR)\DDUtil.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\mmatrix.obj"
	-@erase "$(INTDIR)\mmatrix.res"
	-@erase "$(INTDIR)\TxtrUtil.obj"
	-@erase "..\..\..\release\retail\Samples\mmatrix.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=shcl.exe
CPP_PROJ=/nologo /W3 /WX /I "..\..\..\inc" /D "_WIN32_WCE" /D "UNICODE" /D "_UNICODE" /D "UNDER_CE" /D "WIN32" /D "STRICT" /D "SHx" /D "SH4" /D "_SH3_" /D DEBUG=1 /D "DRAGON" /D "INTERNATIONAL" /D "USA" /D INTLMSG_CODEPAGE=1252 /D "NDEBUG" /D "_SH4_" /Fp"$(INTDIR)\mmatrix.pch" /YX /Fo"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /Qpartial /Qgvp /Ogityb2 /Gs /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x199 /r /fo"$(INTDIR)\mmatrix.res" /i "..\..\..\inc" /d "UNDER_CE" /d "INTERNATIONAL" /d "USA" /d "SHx" /d "SH4" /d "_SH4_" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG" -c 1252 
MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mmatrix.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib ddraw.lib dinput.lib dxguid.lib floatmath.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\retail\Samples/mmatrix.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/mmatrix.exe" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\mmatrix.obj" \
	"$(INTDIR)\D3DUtil.obj" \
	"$(INTDIR)\TxtrUtil.obj" \
	"$(INTDIR)\DDUtil.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\mmatrix.res" \
	"..\..\..\release\retail\Samples\fastmat.obj" \
	"$(INTDIR)\d3dmath.obj"

"..\..\..\release\retail\Samples\mmatrix.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mmatrix - Win32 (WCE SH4) Debug"

OUTDIR=.\debug
INTDIR=.\debug

ALL : "..\..\..\release\debug\Samples\mmatrix.exe"


CLEAN :
	-@erase "$(INTDIR)\d3dmath.obj"
	-@erase "$(INTDIR)\D3DUtil.obj"
	-@erase "$(INTDIR)\DDUtil.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\mmatrix.obj"
	-@erase "$(INTDIR)\mmatrix.res"
	-@erase "$(INTDIR)\TxtrUtil.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\release\debug\Samples\mmatrix.exe"
	-@erase "..\..\..\release\debug\Samples\mmatrix.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=shcl.exe
CPP_PROJ=/nologo /W3 /WX /Zi /Od /I "..\..\..\inc" /D "_WIN32_WCE" /D "UNICODE" /D "_UNICODE" /D "UNDER_CE" /D "WIN32" /D "STRICT" /D "SHx" /D "SH4" /D "_SH3_" /D DEBUG=1 /D "DRAGON" /D "INTERNATIONAL" /D "USA" /D INTLMSG_CODEPAGE=1252 /D "DEBUG" /D "_SH4_" /Fp"$(INTDIR)\mmatrix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x199 /r /fo"$(INTDIR)\mmatrix.res" /i "..\..\..\inc" /d "UNDER_CE" /d "INTERNATIONAL" /d "USA" /d "SHx" /d "SH4" /d "_SH4_" /d "_WIN32_WCE" /d "UNICODE" /d "DEBUG" -c 1252 
MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mmatrix.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib ddraw.lib dinput.lib dxguid.lib floatmath.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\debug\Samples/mmatrix.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/mmatrix.exe" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\mmatrix.obj" \
	"$(INTDIR)\D3DUtil.obj" \
	"$(INTDIR)\TxtrUtil.obj" \
	"$(INTDIR)\DDUtil.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\mmatrix.res" \
	"..\..\..\release\debug\Samples\fastmat.obj" \
	"$(INTDIR)\d3dmath.obj"

"..\..\..\release\debug\Samples\mmatrix.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mmatrix.dep")
!INCLUDE "mmatrix.dep"
!ELSE 
!MESSAGE Warning: cannot find "mmatrix.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mmatrix - Win32 (WCE SH4) Release" || "$(CFG)" == "mmatrix - Win32 (WCE SH4) Debug"
SOURCE=.\d3dmath.cpp

"$(INTDIR)\d3dmath.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\D3DUtil.cpp

"$(INTDIR)\D3DUtil.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DDUtil.cpp

"$(INTDIR)\DDUtil.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Error.cpp

"$(INTDIR)\Error.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\fastmat.src

!IF  "$(CFG)" == "mmatrix - Win32 (WCE SH4) Release"

TargetDir=\dragon21\public\DRAGON\sdkship\release\retail\Samples
InputPath=.\fastmat.src
InputName=fastmat

"..\..\..\release\retail\Samples\fastmat.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	shasm -cpu=sh4 $(InputName).src -o=$(TargetDir)\$(InputName).obj
<< 
	

!ELSEIF  "$(CFG)" == "mmatrix - Win32 (WCE SH4) Debug"

TargetDir=\dragon21\public\DRAGON\sdkship\release\debug\Samples
InputPath=.\fastmat.src
InputName=fastmat

"..\..\..\release\debug\Samples\fastmat.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	shasm -cpu=sh4 $(InputName).src -o=$(TargetDir)\$(InputName).obj
<< 
	

!ENDIF 

SOURCE=.\mmatrix.cpp

"$(INTDIR)\mmatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mmatrix.rc

"$(INTDIR)\mmatrix.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\TxtrUtil.cpp

"$(INTDIR)\TxtrUtil.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

