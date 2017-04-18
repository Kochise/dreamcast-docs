!include <win32.mak>

all: srtest.exe nullprov.dll

.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.cpp

srtest.exe: srtest.obj
    $(link) $(ldebug) -out:$*.exe $** $(conlibs) ws2_32.lib


nullprov.lib: nullprov.obj nullprov.def
    $(implib) -machine:$(CPU) -def:nullprov.def -out:nullprov.lib

nullprov.dll: nullprov.obj
    $(link) $(linkdebug) $(dlllflags) \
      $** -out:nullprov.dll -def:nullprov.def \
      $(conlibsdll) ws2_32.lib
