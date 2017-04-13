!include <win32.mak>

cflags = -DWINNT $(cflags) 

all: reitp.exe

reitp.obj: reitp.c
    $(cc) $(cdebug) $(cflags) $(cvars) reitp.c

frmtbar.obj: frmtbar.c
    $(cc) $(cdebug) $(cflags) $(cvars) frmtbar.c

oleutl.obj: oleutl.c
    $(cc) $(cdebug) $(cflags) $(cvars) oleutl.c

drawicon.obj: drawicon.c
    $(cc) $(cdebug) $(cflags) $(cvars) drawicon.c

olestd.obj: olestd.c
    $(cc) $(cdebug) $(cflags) $(cvars) olestd.c

reitp.res: reitp.rc reitp.h reitp.dlg
    $(rc) $(rcvars) -r -fo reitp.res reitp.rc

reitp.exe: reitp.obj reitp.res frmtbar.obj olestd.obj drawicon.obj oleutl.obj
    $(link) $(linkdebug) $(guiflags) -out:reitp.exe reitp.obj reitp.res frmtbar.obj olestd.obj drawicon.obj oleutl.obj $(olelibs) comctl32.lib shell32.lib oledlg.lib
