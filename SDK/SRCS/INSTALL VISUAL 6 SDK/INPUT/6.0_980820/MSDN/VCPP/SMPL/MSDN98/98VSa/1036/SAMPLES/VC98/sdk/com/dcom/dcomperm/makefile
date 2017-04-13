!include <win32.mak>

all: dcomperm.exe

cflags = $(cflags) -DUNICODE=1 -D_UNICODE=1 -I..\include

OBJS = dcomperm.obj sdmgmt.obj wrappers.obj utils.obj aclmgmt.obj srvcmgmt.obj listacl.obj


.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.cpp

dcomperm.exe: $(OBJS)
  $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(guilibs)

clean:
    del *.obj
    del *.pch
    del *.exe

