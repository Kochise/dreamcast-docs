# Microsoft Developer Studio Generated NMAKE File, Based on htmlsamp.dsp
!IF "$(CFG)" == ""
CFG=htmlsamp - Win32 (WCE SH4) Debug
!MESSAGE No configuration specified. Defaulting to htmlsamp - Win32 (WCE SH4) Debug.
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

!IF "$(CFG)" != "htmlsamp - Win32 (WCE SH4) Release" && "$(CFG)" != "htmlsamp - Win32 (WCE SH4) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "htmlsamp.mak" CFG="htmlsamp - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "htmlsamp - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "htmlsamp - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
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

!IF  "$(CFG)" == "htmlsamp - Win32 (WCE SH4) Release"

OUTDIR=.\retail
INTDIR=.\retail

ALL : "..\..\..\release\retail\Samples\htmlsamp.exe"


CLEAN :
	-@erase "$(INTDIR)\htmlsamp.res"
 -@erase "$(INTDIR)\alert.obj" 
 -@erase "$(INTDIR)\device.obj" 
 -@erase "$(INTDIR)\dialer.obj" 
 -@erase "$(INTDIR)\draw.obj" 
 -@erase "$(INTDIR)\gamefld.obj" 
 -@erase "$(INTDIR)\external.obj" 
 -@erase "$(INTDIR)\htmldlg.obj" 
 -@erase "$(INTDIR)\htmldoc.obj" 
 -@erase "$(INTDIR)\htmlsamp.obj" 
 -@erase "$(INTDIR)\input.obj" 
 -@erase "$(INTDIR)\memstm.obj" 
 -@erase "$(INTDIR)\sound.obj" 
 -@erase "$(INTDIR)\status.obj" 
 -@erase "$(INTDIR)\statanim.obj" 
 -@erase "$(INTDIR)\statbmp.obj" 
 -@erase "$(INTDIR)\titlebar.obj" 
 -@erase "$(INTDIR)\toolbar.obj" 
 -@erase "$(INTDIR)\window.obj" 
 -@erase "$(INTDIR)\flashapi.obj"
	-@erase "..\..\..\release\retail\Samples\htmlsamp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /W3 /WX /X /I "..\..\..\ime\tkimelib" /I "..\..\ime\tkimelib" /I "e:\Dragon21\public\mcpupub\s..\..\inc" /I "e:\Dragon21\public\dragon\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DGAME_SAMPLE -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /Fp"$(INTDIR)\htmlsamp.pch" /YX /Fo"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /Qpartial /Qgvp /Ogityb2 /Gs /c 
RSC_PROJ=/l 0x409 /r /x /fo"$(INTDIR)\htmlsamp.res" /i "..\..\..\ime\tkimelib" /i "..\..\ime\tkimelib" /i "e:\Dragon21\public\mcpupub\s..\..\inc" /i "e:\Dragon21\public\dragon\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /i "..\..\..\inc"  -DUNDER_CE -DGAME_SAMPLE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG" 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\htmlsamp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib  ole32.lib oleaut32.lib uuid.lib ddraw.lib dinput.lib dsound.lib dxguid.lib mapledev.lib mras.lib winsock.lib tkimelib.lib tankanji.lib wdm.lib  /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\retail\Samples/htmlsamp.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/htmlsamp.exe" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\htmlsamp.res"	\
 "$(INTDIR)\alert.obj" \
 "$(INTDIR)\device.obj" \
 "$(INTDIR)\dialer.obj" \
 "$(INTDIR)\draw.obj" \
 "$(INTDIR)\gamefld.obj" \
 "$(INTDIR)\external.obj" \
 "$(INTDIR)\htmldlg.obj" \
 "$(INTDIR)\htmldoc.obj" \
 "$(INTDIR)\htmlsamp.obj" \
 "$(INTDIR)\input.obj" \
 "$(INTDIR)\memstm.obj" \
 "$(INTDIR)\sound.obj" \
 "$(INTDIR)\status.obj" \
 "$(INTDIR)\statanim.obj" \
 "$(INTDIR)\statbmp.obj" \
 "$(INTDIR)\titlebar.obj" \
 "$(INTDIR)\toolbar.obj" \
 "$(INTDIR)\window.obj" \
 "$(INTDIR)\flashapi.obj"

"..\..\..\release\retail\Samples\htmlsamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "htmlsamp - Win32 (WCE SH4) Debug"

OUTDIR=.\debug
INTDIR=.\debug

ALL : "..\..\..\release\debug\Samples\htmlsamp.exe"


CLEAN :
	-@erase "$(INTDIR)\htmlsamp.res"
 -@erase "$(INTDIR)\alert.obj" 
 -@erase "$(INTDIR)\device.obj" 
 -@erase "$(INTDIR)\dialer.obj" 
 -@erase "$(INTDIR)\draw.obj" 
 -@erase "$(INTDIR)\gamefld.obj" 
 -@erase "$(INTDIR)\external.obj" 
 -@erase "$(INTDIR)\htmldlg.obj" 
 -@erase "$(INTDIR)\htmldoc.obj" 
 -@erase "$(INTDIR)\htmlsamp.obj" 
 -@erase "$(INTDIR)\input.obj" 
 -@erase "$(INTDIR)\memstm.obj" 
 -@erase "$(INTDIR)\sound.obj" 
 -@erase "$(INTDIR)\status.obj" 
 -@erase "$(INTDIR)\statanim.obj" 
 -@erase "$(INTDIR)\statbmp.obj" 
 -@erase "$(INTDIR)\titlebar.obj" 
 -@erase "$(INTDIR)\toolbar.obj" 
 -@erase "$(INTDIR)\window.obj" 
 -@erase "$(INTDIR)\flashapi.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\release\debug\Samples\htmlsamp.exe"
	-@erase "..\..\..\release\debug\Samples\htmlsamp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /W3 /WX /Zi /Od /X /I "..\..\..\ime\tkimelib" /I "..\..\ime\tkimelib" /I "e:\Dragon21\public\mcpupub\s..\..\inc" /I "e:\Dragon21\public\dragon\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DGAME_SAMPLE -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /Fp"$(INTDIR)\htmlsamp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /c 
RSC_PROJ=/l 0x409 /r /x /fo"$(INTDIR)\htmlsamp.res" /i "..\..\..\ime\tkimelib" /i "..\..\ime\tkimelib" /i "e:\Dragon21\public\mcpupub\s..\..\inc" /i "e:\Dragon21\public\dragon\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /i "..\..\..\inc"  -DUNDER_CE -DGAME_SAMPLE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "DEBUG" 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\htmlsamp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib  ole32.lib oleaut32.lib uuid.lib ddraw.lib dinput.lib dsound.lib dxguid.lib mapledev.lib mras.lib winsock.lib tkimelib.lib tankanji.lib wdm.lib  /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\debug\Samples/htmlsamp.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/htmlsamp.exe" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\htmlsamp.res"	\
 "$(INTDIR)\alert.obj" \
 "$(INTDIR)\device.obj" \
 "$(INTDIR)\dialer.obj" \
 "$(INTDIR)\draw.obj" \
 "$(INTDIR)\gamefld.obj" \
 "$(INTDIR)\external.obj" \
 "$(INTDIR)\htmldlg.obj" \
 "$(INTDIR)\htmldoc.obj" \
 "$(INTDIR)\htmlsamp.obj" \
 "$(INTDIR)\input.obj" \
 "$(INTDIR)\memstm.obj" \
 "$(INTDIR)\sound.obj" \
 "$(INTDIR)\status.obj" \
 "$(INTDIR)\statanim.obj" \
 "$(INTDIR)\statbmp.obj" \
 "$(INTDIR)\titlebar.obj" \
 "$(INTDIR)\toolbar.obj" \
 "$(INTDIR)\window.obj" \
 "$(INTDIR)\flashapi.obj"

"..\..\..\release\debug\Samples\htmlsamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("htmlsamp.dep")
!INCLUDE "htmlsamp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "htmlsamp - Win32 (WCE SH4) Release" || "$(CFG)" == "htmlsamp - Win32 (WCE SH4) Debug"
SOURCE=.\htmlsamp.rc

"$(INTDIR)\htmlsamp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


"$(INTDIR)\alert.obj" : alert.cpp "$(INTDIR)"
"$(INTDIR)\device.obj" : device.cpp "$(INTDIR)"
"$(INTDIR)\dialer.obj" : dialer.cpp "$(INTDIR)"
"$(INTDIR)\draw.obj" : draw.cpp "$(INTDIR)"
"$(INTDIR)\gamefld.obj" : gamefld.cpp "$(INTDIR)"
"$(INTDIR)\external.obj" : external.cpp "$(INTDIR)"
"$(INTDIR)\htmldlg.obj" : htmldlg.cpp "$(INTDIR)"
"$(INTDIR)\htmldoc.obj" : htmldoc.cpp "$(INTDIR)"
"$(INTDIR)\htmlsamp.obj" : htmlsamp.cpp "$(INTDIR)"
"$(INTDIR)\input.obj" : input.cpp "$(INTDIR)"
"$(INTDIR)\memstm.obj" : memstm.cpp "$(INTDIR)"
"$(INTDIR)\sound.obj" : sound.cpp "$(INTDIR)"
"$(INTDIR)\status.obj" : status.cpp "$(INTDIR)"
"$(INTDIR)\statanim.obj" : statanim.cpp "$(INTDIR)"
"$(INTDIR)\statbmp.obj" : statbmp.cpp "$(INTDIR)"
"$(INTDIR)\titlebar.obj" : titlebar.cpp "$(INTDIR)"
"$(INTDIR)\toolbar.obj" : toolbar.cpp "$(INTDIR)"
"$(INTDIR)\window.obj" : window.cpp "$(INTDIR)"
"$(INTDIR)\flashapi.obj" : flashapi.cpp "$(INTDIR)"

!ENDIF
