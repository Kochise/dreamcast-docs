# Microsoft Developer Studio Generated NMAKE File, Based on tcime.dsp
!IF "$(CFG)" == ""
CFG=tcime - Win32 (WCE SH4) Debug
!MESSAGE No configuration specified. Defaulting to tcime - Win32 (WCE SH4) Debug.
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

!IF "$(CFG)" != "tcime - Win32 (WCE SH4) Release" && "$(CFG)" != "tcime - Win32 (WCE SH4) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tcime.mak" CFG="tcime - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tcime - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "tcime - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
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

!IF  "$(CFG)" == "tcime - Win32 (WCE SH4) Release"

OUTDIR=.\retail
INTDIR=.\retail

ALL : "..\..\..\release\retail\Samples\tcime.exe"


CLEAN :
	-@erase "$(INTDIR)\imesamp.res"
 -@erase "$(INTDIR)\winmain.obj" 
 -@erase "$(INTDIR)\input.obj" 
 -@erase "$(INTDIR)\ddutil.obj" 
 -@erase "$(INTDIR)\display.obj" 
 -@erase "$(INTDIR)\editbox.obj" 
 -@erase "$(INTDIR)\softkbd.obj" 
 -@erase "$(INTDIR)\readwnd.obj" 
 -@erase "$(INTDIR)\candwnd.obj" 
 -@erase "$(INTDIR)\indicate.obj" 
 -@erase "$(INTDIR)\inputskb.obj" 
 -@erase "$(INTDIR)\inputcwd.obj" 
 -@erase "$(INTDIR)\dspskb.obj" 
 -@erase "$(INTDIR)\dspcwd.obj" 
 -@erase "$(INTDIR)\phonetic.obj" 
 -@erase "$(INTDIR)\romanji.obj" 
 -@erase "$(INTDIR)\symbols.obj"
	-@erase "..\..\..\release\retail\Samples\tcime.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /W3 /WX /X /I "e:\Dragon21\public\mcpupub\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /Fp"$(INTDIR)\tcime.pch" /YX /Fo"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /Qpartial /Qgvp /Ogityb2 /Gs /c 
RSC_PROJ=/l 0x409 /r /x /fo"$(INTDIR)\imesamp.res" /i "e:\Dragon21\public\mcpupub\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG" 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tcime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib  ddraw.lib dinput.lib dxguid.lib  /nologo /entry:"WinMain" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\retail\Samples/tcime.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/tcime.exe" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\imesamp.res"	\
 "$(INTDIR)\winmain.obj" \
 "$(INTDIR)\input.obj" \
 "$(INTDIR)\ddutil.obj" \
 "$(INTDIR)\display.obj" \
 "$(INTDIR)\editbox.obj" \
 "$(INTDIR)\softkbd.obj" \
 "$(INTDIR)\readwnd.obj" \
 "$(INTDIR)\candwnd.obj" \
 "$(INTDIR)\indicate.obj" \
 "$(INTDIR)\inputskb.obj" \
 "$(INTDIR)\inputcwd.obj" \
 "$(INTDIR)\dspskb.obj" \
 "$(INTDIR)\dspcwd.obj" \
 "$(INTDIR)\phonetic.obj" \
 "$(INTDIR)\romanji.obj" \
 "$(INTDIR)\symbols.obj"

"..\..\..\release\retail\Samples\tcime.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tcime - Win32 (WCE SH4) Debug"

OUTDIR=.\debug
INTDIR=.\debug

ALL : "..\..\..\release\debug\Samples\tcime.exe"


CLEAN :
	-@erase "$(INTDIR)\imesamp.res"
 -@erase "$(INTDIR)\winmain.obj" 
 -@erase "$(INTDIR)\input.obj" 
 -@erase "$(INTDIR)\ddutil.obj" 
 -@erase "$(INTDIR)\display.obj" 
 -@erase "$(INTDIR)\editbox.obj" 
 -@erase "$(INTDIR)\softkbd.obj" 
 -@erase "$(INTDIR)\readwnd.obj" 
 -@erase "$(INTDIR)\candwnd.obj" 
 -@erase "$(INTDIR)\indicate.obj" 
 -@erase "$(INTDIR)\inputskb.obj" 
 -@erase "$(INTDIR)\inputcwd.obj" 
 -@erase "$(INTDIR)\dspskb.obj" 
 -@erase "$(INTDIR)\dspcwd.obj" 
 -@erase "$(INTDIR)\phonetic.obj" 
 -@erase "$(INTDIR)\romanji.obj" 
 -@erase "$(INTDIR)\symbols.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\release\debug\Samples\tcime.exe"
	-@erase "..\..\..\release\debug\Samples\tcime.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /W3 /WX /Zi /Od /X /I "e:\Dragon21\public\mcpupub\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\s..\..\inc" /I "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /Fp"$(INTDIR)\tcime.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /c 
RSC_PROJ=/l 0x409 /r /x /fo"$(INTDIR)\imesamp.res" /i "e:\Dragon21\public\mcpupub\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\s..\..\inc" /i "e:\Dragon21\public\DRAGONIE\cesysgen\o..\..\inc" /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "DEBUG" 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tcime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib  ddraw.lib dinput.lib dxguid.lib  /nologo /entry:"WinMain" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\debug\Samples/tcime.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/tcime.exe" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\imesamp.res"	\
 "$(INTDIR)\winmain.obj" \
 "$(INTDIR)\input.obj" \
 "$(INTDIR)\ddutil.obj" \
 "$(INTDIR)\display.obj" \
 "$(INTDIR)\editbox.obj" \
 "$(INTDIR)\softkbd.obj" \
 "$(INTDIR)\readwnd.obj" \
 "$(INTDIR)\candwnd.obj" \
 "$(INTDIR)\indicate.obj" \
 "$(INTDIR)\inputskb.obj" \
 "$(INTDIR)\inputcwd.obj" \
 "$(INTDIR)\dspskb.obj" \
 "$(INTDIR)\dspcwd.obj" \
 "$(INTDIR)\phonetic.obj" \
 "$(INTDIR)\romanji.obj" \
 "$(INTDIR)\symbols.obj"

"..\..\..\release\debug\Samples\tcime.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("tcime.dep")
!INCLUDE "tcime.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tcime - Win32 (WCE SH4) Release" || "$(CFG)" == "tcime - Win32 (WCE SH4) Debug"
SOURCE=.\imesamp.rc

"$(INTDIR)\imesamp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


"$(INTDIR)\winmain.obj" : winmain.cpp "$(INTDIR)"
"$(INTDIR)\input.obj" : input.cpp "$(INTDIR)"
"$(INTDIR)\ddutil.obj" : ddutil.cpp "$(INTDIR)"
"$(INTDIR)\display.obj" : display.cpp "$(INTDIR)"
"$(INTDIR)\editbox.obj" : editbox.cpp "$(INTDIR)"
"$(INTDIR)\softkbd.obj" : softkbd.cpp "$(INTDIR)"
"$(INTDIR)\readwnd.obj" : readwnd.cpp "$(INTDIR)"
"$(INTDIR)\candwnd.obj" : candwnd.cpp "$(INTDIR)"
"$(INTDIR)\indicate.obj" : indicate.cpp "$(INTDIR)"
"$(INTDIR)\inputskb.obj" : inputskb.cpp "$(INTDIR)"
"$(INTDIR)\inputcwd.obj" : inputcwd.cpp "$(INTDIR)"
"$(INTDIR)\dspskb.obj" : dspskb.cpp "$(INTDIR)"
"$(INTDIR)\dspcwd.obj" : dspcwd.cpp "$(INTDIR)"
"$(INTDIR)\phonetic.obj" : phonetic.cpp "$(INTDIR)"
"$(INTDIR)\romanji.obj" : romanji.cpp "$(INTDIR)"
"$(INTDIR)\symbols.obj" : symbols.cpp "$(INTDIR)"

!ENDIF
