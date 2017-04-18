# Microsoft Developer Studio Generated NMAKE File, Based on PlayMultipleSounds.dsp
!IF "$(CFG)" == ""
CFG=PlayMultipleSounds - Win32 (WCE SH4) Debug
!MESSAGE No configuration specified. Defaulting to PlayMultipleSounds - Win32 (WCE SH4) Debug.
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

!IF "$(CFG)" != "PlayMultipleSounds - Win32 (WCE SH4) Release" && "$(CFG)" != "PlayMultipleSounds - Win32 (WCE SH4) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PlayMultipleSounds.mak" CFG="PlayMultipleSounds - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PlayMultipleSounds - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "PlayMultipleSounds - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PlayMultipleSounds - Win32 (WCE SH4) Release"

OUTDIR=.\retail
INTDIR=.\retail

ALL : "..\..\..\release\retail\Samples\PlayMultipleSounds.exe"


CLEAN :
	-@erase "$(INTDIR)\PlayMultipleSounds.res"
 -@erase "$(INTDIR)\PlayMultipleSounds.obj" 
 -@erase "$(INTDIR)\CController.obj" 
 -@erase "$(INTDIR)\DIUtil.obj" 
 -@erase "$(INTDIR)\DSUtil.obj" 
 -@erase "$(INTDIR)\Error.obj" 
 -@erase "$(INTDIR)\PlayingSoundThread.obj"
	-@erase "..\..\..\release\retail\Samples\PlayMultipleSounds.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /W3 /WX /X  /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DDRAGON   -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /Fp"$(INTDIR)\PlayMultipleSounds.pch" /YX /Fo"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /Qpartial /Qgvp /Ogityb2 /Gs /c 
RSC_PROJ=/l 0x409 /r /x /fo"$(INTDIR)\PlayMultipleSounds.res"  /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG" 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PlayMultipleSounds.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib dsound.lib ddraw.lib dinput.lib dxguid.lib  floatmath.lib  /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\retail\Samples/PlayMultipleSounds.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/PlayMultipleSounds.exe" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\PlayMultipleSounds.res"	\
 "$(INTDIR)\PlayMultipleSounds.obj" \
 "$(INTDIR)\CController.obj" \
 "$(INTDIR)\DIUtil.obj" \
 "$(INTDIR)\DSUtil.obj" \
 "$(INTDIR)\Error.obj" \
 "$(INTDIR)\PlayingSoundThread.obj"

"..\..\..\release\retail\Samples\PlayMultipleSounds.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PlayMultipleSounds - Win32 (WCE SH4) Debug"

OUTDIR=.\debug
INTDIR=.\debug

ALL : "..\..\..\release\debug\Samples\PlayMultipleSounds.exe"


CLEAN :
	-@erase "$(INTDIR)\PlayMultipleSounds.res"
 -@erase "$(INTDIR)\PlayMultipleSounds.obj" 
 -@erase "$(INTDIR)\CController.obj" 
 -@erase "$(INTDIR)\DIUtil.obj" 
 -@erase "$(INTDIR)\DSUtil.obj" 
 -@erase "$(INTDIR)\Error.obj" 
 -@erase "$(INTDIR)\PlayingSoundThread.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\release\debug\Samples\PlayMultipleSounds.exe"
	-@erase "..\..\..\release\debug\Samples\PlayMultipleSounds.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /W3 /WX /Zi /Od /X  /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DDRAGON   -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /Fp"$(INTDIR)\PlayMultipleSounds.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /c 
RSC_PROJ=/l 0x409 /r /x /fo"$(INTDIR)\PlayMultipleSounds.res"  /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "DEBUG" 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PlayMultipleSounds.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib dsound.lib ddraw.lib dinput.lib dxguid.lib  floatmath.lib  /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\debug\Samples/PlayMultipleSounds.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/PlayMultipleSounds.exe" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\PlayMultipleSounds.res"	\
 "$(INTDIR)\PlayMultipleSounds.obj" \
 "$(INTDIR)\CController.obj" \
 "$(INTDIR)\DIUtil.obj" \
 "$(INTDIR)\DSUtil.obj" \
 "$(INTDIR)\Error.obj" \
 "$(INTDIR)\PlayingSoundThread.obj"

"..\..\..\release\debug\Samples\PlayMultipleSounds.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("PlayMultipleSounds.dep")
!INCLUDE "PlayMultipleSounds.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PlayMultipleSounds - Win32 (WCE SH4) Release" || "$(CFG)" == "PlayMultipleSounds - Win32 (WCE SH4) Debug"
SOURCE=.\PlayMultipleSounds.rc

"$(INTDIR)\PlayMultipleSounds.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


"$(INTDIR)\PlayMultipleSounds.obj" : PlayMultipleSounds.cpp "$(INTDIR)"
"$(INTDIR)\CController.obj" : CController.cpp "$(INTDIR)"
"$(INTDIR)\DIUtil.obj" : DIUtil.cpp "$(INTDIR)"
"$(INTDIR)\DSUtil.obj" : DSUtil.cpp "$(INTDIR)"
"$(INTDIR)\Error.obj" : Error.cpp "$(INTDIR)"
"$(INTDIR)\PlayingSoundThread.obj" : PlayingSoundThread.cpp "$(INTDIR)"

!ENDIF
