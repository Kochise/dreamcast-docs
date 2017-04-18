!include <win32.mak>



!IF "$(CPU)" == "i386"
cflags = $(cflags) -Di386=1
!ELSE
!IF "$(CPU)" == "ALPHA"
cflags = $(cflags)  -DALPHA=1
!ENDIF
!ENDIF

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all: ..\bin\drwtsn32.exe

messages.h messages.rc msg00001.bin: messages.mc
    mc -v messages.mc

cflags = $(cflags) -DWIN32 -DTARGET32 -DHOST32 -DADDR_MIXED -DNT_BUILD -D_CROSS_PLATFORM_

drwatson.res: messages.rc msg00001.bin drwatson.rc
    rc -r -i .\include -fo drwatson.res drwatson.rc

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $(scall) -I..\include -I.\include -I. $*.c

OBJECTS= drwatson.res   \
         controls.obj   \
         debug.obj      \
         error.obj      \
         eventlog.obj   \
         getteb.obj     \
         log.obj        \
         module.obj     \
         notify.obj     \
         process.obj    \
         registry.obj   \
         symbols.obj    \
         ui.obj         \
         util.obj       \
         walk.obj      \
         regs.obj      \
         disasm.obj    \
         context.obj   \
         drwtsn32.obj   \
         browse.obj    \
         dump.obj

!IF "$(CPU)" == "ALPHA"
OBJECTS=$(OBJECTS) optable.obj
!ENDIF

..\bin\drwtsn32.exe: $(OBJECTS)
  @if not exist ..\bin md ..\bin > nul
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$@ \
  $** $(guilibs) imagehlp.lib winmm.lib shell32.lib \
  comdlg32.lib advapi32.lib crashlib.lib
!IF ("$(TARGETLANG)" == "LANG_JAPANESE") && ("$(OS)" == "Windows_NT")
  rlman -p 932 -n 17 1 -r $@ drwtsn32.tok $@
!ENDIF
