!include <win32.mak>

all: fontedit.exe

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $*.c

fontedit.res: fontedit.rc fontedit.h
    $(rc) -r fontedit.rc

fontedit.exe: fontedit.res \
              FONTCVT.obj FONTDLG.OBJ FONTEDIT.OBJ \
              FONTHEAD.OBJ TYPECVT.OBJ FONTLOAD.OBJ FONTCHAR.OBJ
  $(link) $(linkdebug) $(guiflags) -machine:$(CPU) -out:$*.exe $** $(guilibs)
!IF ("$(TARGETLANG)" == "LANG_JAPANESE") && ("$(OS)" == "Windows_NT")
    rlman -p 932 -n 17 1 -a $*.exe $*.tok $*.exe
!ENDIF
