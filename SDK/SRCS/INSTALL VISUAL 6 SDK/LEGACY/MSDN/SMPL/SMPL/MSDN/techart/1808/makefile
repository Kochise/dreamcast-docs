!IF "$(CPU)" != ""
OS=NT
ENV=WIN32
!ELSE
OS=DOS
ENV=WIN16
!ENDIF


!include <$(OS)$(ENV).MAK>

proj = frogfly

all: $(proj).exe


# Update the resource if necessary
$(proj).res: $(proj).rc $(proj).rcv $(proj).h frog.bmp fly.bmp burger.cur
    $(rc) $(rcvars) -r -fo $(proj).res $(cvars) $(proj).rc
!IFDEF CPUTYPE
    cvtres -$(CPU) $(proj).res -o $(proj).rbj
!ENDIF


# Update the object file if necessary
$(proj).obj: $(proj).cpp $(proj).h classes.hpp
    $(cc) $(cflags) $(cvars) $(cdebug) $(proj).cpp

classes.obj: classes.cpp classes.hpp
    $(cc) $(cflags) $(cvars) $(cdebug) classes.cpp


$(proj).exe: $(proj).obj classes.obj $(proj).res $(proj).def
    $(link) $(linkdebug) $(guiflags) $(proj).obj classes.obj  $(guilibs) VERSION.LIB $(proj).rbj -out:$(proj).exe
