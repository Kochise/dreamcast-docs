!include <win32.mak>

all: aniedit.exe

animsg.h animsg.rc msg00001.bin: animsg.mc
    mc -v animsg.mc

aniedit.res: animsg.rc msg00001.bin aniedit.rc
    rc $(rcflags) $(rcvars) -fo aniedit.res aniedit.rc

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

aniedit.exe: aniedit.res   \
	         aniedit.obj   \
	         anicmd.obj    \
	         anifile.obj   \
             anistr.obj
  $(link) $(linkdebug) $(guiflags) -machine:$(CPU) -out:$*.exe $** $(guilibs) advapi32.lib
!IF ("$(TARGETLANG)" == "LANG_JAPANESE") && ("$(OS)" == "Windows_NT")
    rlman -p 932 -n 17 1 -a $*.exe $*.tok $*.exe
!ENDIF
