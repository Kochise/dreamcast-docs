# Microsoft Developer Studio Generated NMAKE File, Based on pime.dsp
!IF "$(CFG)" == ""
CFG=pime - Win32 (WCE SH4) Debug
!MESSAGE No configuration specified. Defaulting to pime - Win32 (WCE SH4) Debug.
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

!IF "$(CFG)" != "pime - Win32 (WCE SH4) Release" && "$(CFG)" != "pime - Win32 (WCE SH4) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pime.mak" CFG="pime - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pime - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "pime - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
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

!IF  "$(CFG)" == "pime - Win32 (WCE SH4) Release"

OUTDIR=.\retail
INTDIR=.\retail

ALL : "..\..\..\release\retail\Samples\pime.exe"


CLEAN :
	-@erase "$(INTDIR)\imesamp.res"
 -@erase "$(INTDIR)\winmain.obj" 
 -@erase "$(INTDIR)\editbox.obj" 
 -@erase "$(INTDIR)\indicator.obj" 
 -@erase "$(INTDIR)\romakana.obj" 
 -@erase "$(INTDIR)\display.obj" 
 -@erase "$(INTDIR)\displaykwnd.obj" 
 -@erase "$(INTDIR)\displayskb.obj" 
 -@erase "$(INTDIR)\displayswnd.obj" 
 -@erase "$(INTDIR)\hiragana.obj" 
 -@erase "$(INTDIR)\imeui.obj" 
 -@erase "$(INTDIR)\input.obj" 
 -@erase "$(INTDIR)\inputkwnd.obj" 
 -@erase "$(INTDIR)\inputskb.obj" 
 -@erase "$(INTDIR)\inputswnd.obj" 
 -@erase "$(INTDIR)\katakana.obj" 
 -@erase "$(INTDIR)\kwnd.obj" 
 -@erase "$(INTDIR)\romanji.obj" 
 -@erase "$(INTDIR)\shared.obj" 
 -@erase "$(INTDIR)\softkbd.obj" 
 -@erase "$(INTDIR)\swnd.obj" 
 -@erase "$(INTDIR)\symbols.obj" 
 -@erase "$(INTDIR)\ddutil.obj"
	-@erase "..\..\..\release\retail\Samples\pime.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /W3 /WX /X  /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DDRAGON   -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /Fp"$(INTDIR)\pime.pch" /YX /Fo"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /Qpartial /Qgvp /Ogityb2 /Gs /c 
RSC_PROJ=/l 0x409 /r /x /fo"$(INTDIR)\imesamp.res"  /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG" 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib ddraw.lib dinput.lib dxguid.lib  floatmath.lib  /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\retail\Samples/pime.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/pime.exe" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\imesamp.res"	\
 "$(INTDIR)\winmain.obj" \
 "$(INTDIR)\editbox.obj" \
 "$(INTDIR)\indicator.obj" \
 "$(INTDIR)\romakana.obj" \
 "$(INTDIR)\display.obj" \
 "$(INTDIR)\displaykwnd.obj" \
 "$(INTDIR)\displayskb.obj" \
 "$(INTDIR)\displayswnd.obj" \
 "$(INTDIR)\hiragana.obj" \
 "$(INTDIR)\imeui.obj" \
 "$(INTDIR)\input.obj" \
 "$(INTDIR)\inputkwnd.obj" \
 "$(INTDIR)\inputskb.obj" \
 "$(INTDIR)\inputswnd.obj" \
 "$(INTDIR)\katakana.obj" \
 "$(INTDIR)\kwnd.obj" \
 "$(INTDIR)\romanji.obj" \
 "$(INTDIR)\shared.obj" \
 "$(INTDIR)\softkbd.obj" \
 "$(INTDIR)\swnd.obj" \
 "$(INTDIR)\symbols.obj" \
 "$(INTDIR)\ddutil.obj"

"..\..\..\release\retail\Samples\pime.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pime - Win32 (WCE SH4) Debug"

OUTDIR=.\debug
INTDIR=.\debug

ALL : "..\..\..\release\debug\Samples\pime.exe"


CLEAN :
	-@erase "$(INTDIR)\imesamp.res"
 -@erase "$(INTDIR)\winmain.obj" 
 -@erase "$(INTDIR)\editbox.obj" 
 -@erase "$(INTDIR)\indicator.obj" 
 -@erase "$(INTDIR)\romakana.obj" 
 -@erase "$(INTDIR)\display.obj" 
 -@erase "$(INTDIR)\displaykwnd.obj" 
 -@erase "$(INTDIR)\displayskb.obj" 
 -@erase "$(INTDIR)\displayswnd.obj" 
 -@erase "$(INTDIR)\hiragana.obj" 
 -@erase "$(INTDIR)\imeui.obj" 
 -@erase "$(INTDIR)\input.obj" 
 -@erase "$(INTDIR)\inputkwnd.obj" 
 -@erase "$(INTDIR)\inputskb.obj" 
 -@erase "$(INTDIR)\inputswnd.obj" 
 -@erase "$(INTDIR)\katakana.obj" 
 -@erase "$(INTDIR)\kwnd.obj" 
 -@erase "$(INTDIR)\romanji.obj" 
 -@erase "$(INTDIR)\shared.obj" 
 -@erase "$(INTDIR)\softkbd.obj" 
 -@erase "$(INTDIR)\swnd.obj" 
 -@erase "$(INTDIR)\symbols.obj" 
 -@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\release\debug\Samples\pime.exe"
	-@erase "..\..\..\release\debug\Samples\pime.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /W3 /WX /Zi /Od /X  /I "..\..\..\inc" /D "_WIN32_WCE" -DUNICODE -D_UNICODE -DUNDER_CE -D_WIN32_WCE -DWIN32 -DSTRICT -DSHx -DSH4 -D_SH3_ -DDRAGON   -DINTERNATIONAL -DUSA -DINTLMSG_CODEPAGE=1252 /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D "UNDER_CE" /D "UNICODE" /D "STRICT" /Fp"$(INTDIR)\pime.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /Qsh4r7 /Qs /Qfast /c 
RSC_PROJ=/l 0x409 /r /x /fo"$(INTDIR)\imesamp.res"  /i "..\..\..\inc"  -DUNDER_CE -DINTERNATIONAL -DUSA -l 409 -c 1252 /d "SHx" /d "SH4" /d "_SH4_" /d "UNDER_CE" /d "_WIN32_WCE" /d "UNICODE" /d "DEBUG" 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib ddraw.lib dinput.lib dxguid.lib  floatmath.lib  /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /align:"4096" /incremental:no /pdb:"..\..\..\release\debug\Samples/pime.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/pime.exe" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem) 
LINK32_OBJS= \
	"$(INTDIR)\imesamp.res"	\
 "$(INTDIR)\winmain.obj" \
 "$(INTDIR)\editbox.obj" \
 "$(INTDIR)\indicator.obj" \
 "$(INTDIR)\romakana.obj" \
 "$(INTDIR)\display.obj" \
 "$(INTDIR)\displaykwnd.obj" \
 "$(INTDIR)\displayskb.obj" \
 "$(INTDIR)\displayswnd.obj" \
 "$(INTDIR)\hiragana.obj" \
 "$(INTDIR)\imeui.obj" \
 "$(INTDIR)\input.obj" \
 "$(INTDIR)\inputkwnd.obj" \
 "$(INTDIR)\inputskb.obj" \
 "$(INTDIR)\inputswnd.obj" \
 "$(INTDIR)\katakana.obj" \
 "$(INTDIR)\kwnd.obj" \
 "$(INTDIR)\romanji.obj" \
 "$(INTDIR)\shared.obj" \
 "$(INTDIR)\softkbd.obj" \
 "$(INTDIR)\swnd.obj" \
 "$(INTDIR)\symbols.obj" \
 "$(INTDIR)\ddutil.obj"

"..\..\..\release\debug\Samples\pime.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("pime.dep")
!INCLUDE "pime.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "pime - Win32 (WCE SH4) Release" || "$(CFG)" == "pime - Win32 (WCE SH4) Debug"
SOURCE=.\imesamp.rc

"$(INTDIR)\imesamp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


"$(INTDIR)\winmain.obj" : winmain.cpp "$(INTDIR)"
"$(INTDIR)\editbox.obj" : editbox.cpp "$(INTDIR)"
"$(INTDIR)\indicator.obj" : indicator.cpp "$(INTDIR)"
"$(INTDIR)\romakana.obj" : romakana.cpp "$(INTDIR)"
"$(INTDIR)\display.obj" : display.cpp "$(INTDIR)"
"$(INTDIR)\displaykwnd.obj" : displaykwnd.cpp "$(INTDIR)"
"$(INTDIR)\displayskb.obj" : displayskb.cpp "$(INTDIR)"
"$(INTDIR)\displayswnd.obj" : displayswnd.cpp "$(INTDIR)"
"$(INTDIR)\hiragana.obj" : hiragana.cpp "$(INTDIR)"
"$(INTDIR)\imeui.obj" : imeui.cpp "$(INTDIR)"
"$(INTDIR)\input.obj" : input.cpp "$(INTDIR)"
"$(INTDIR)\inputkwnd.obj" : inputkwnd.cpp "$(INTDIR)"
"$(INTDIR)\inputskb.obj" : inputskb.cpp "$(INTDIR)"
"$(INTDIR)\inputswnd.obj" : inputswnd.cpp "$(INTDIR)"
"$(INTDIR)\katakana.obj" : katakana.cpp "$(INTDIR)"
"$(INTDIR)\kwnd.obj" : kwnd.cpp "$(INTDIR)"
"$(INTDIR)\romanji.obj" : romanji.cpp "$(INTDIR)"
"$(INTDIR)\shared.obj" : shared.cpp "$(INTDIR)"
"$(INTDIR)\softkbd.obj" : softkbd.cpp "$(INTDIR)"
"$(INTDIR)\swnd.obj" : swnd.cpp "$(INTDIR)"
"$(INTDIR)\symbols.obj" : symbols.cpp "$(INTDIR)"
"$(INTDIR)\ddutil.obj" : ddutil.cpp "$(INTDIR)"

!ENDIF
