# Nmake macros for building Windows 32-Bit apps

SEHMAP=TRUE
!include <win32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all: ..\lib\symcvt.exp ..\bin\symcvt.dll


cflags = $(cflags) -DWIN32 -DTARGET32 -DHOST32 -DADDR_MIXED -DNT_BUILD -D_CROSS_PLATFORM_

.c.obj:
    $(cc) $(cflags) $(cvarsdll) -I..\include -I. $(scall) $(cdebug) $**

OBJS = cofftocv.obj \
       cvcommon.obj \
       file.obj     \
       symcvt.obj   \
       symtocv.obj

..\lib\symcvt.exp: $(OBJS) symcvt.def
    @if not exist ..\lib md ..\lib > nul
    $(implib) @<<
-machine:$(CPU)
-def:symcvt.def	
$(OBJS: =
)
-out:..\lib\symcvt.lib
<<NOKEEP

..\bin\symcvt.dll: ..\lib\symcvt.exp $(OBJS)
    @if not exist ..\bin md ..\bin > nul
    $(link) @<<
$(dlllflags)
-base:0x58400000
$(linkdebug)
-out:$@
$(**: =
)
$(conlibsdll: =
)
imagehlp.lib
<<NOKEEP
