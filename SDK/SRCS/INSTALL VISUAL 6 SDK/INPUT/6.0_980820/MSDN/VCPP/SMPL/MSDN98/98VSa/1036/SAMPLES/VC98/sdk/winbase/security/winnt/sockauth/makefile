
!include <win32.mak>

CPP          = $(cc)
CPPFLAGS     = $(cflags) $(cvars) $(cdebug)
LINKFLAGS    = $(linkdebug) $(conflags) /subsystem:console 

            
all: server.exe client.exe


                     
# ----------------------------------------------------------------------------
#                      L I N K / R E S   C O M M A N D S
# ----------------------------------------------------------------------------

server.exe: server.obj comm.obj security.obj collect.obj
    @echo Linking ...
     $(link) $(LINKFLAGS) $** $(conlibs) wsock32.lib -out:$@

client.exe: client.obj comm.obj security.obj collect.obj
    @echo Linking ...
     $(link) $(LINKFLAGS) $** $(conlibs) -out:$@


# ----------------------------------------------------------------------------
#                           B U I L D   R U L E S
# ----------------------------------------------------------------------------

.c.obj:
    @echo Compiling $<...
    $(CPP) $(CPPFLAGS) /c -I..\include $<


# ----------------------------------------------------------------------------
#                       D E P E N D E N C Y   R U L E S
# ----------------------------------------------------------------------------

comm.obj : comm.c comm.h

security.obj : security.c security.h collect.h

server.obj : server.c security.h comm.h

client.obj : client.c security.h comm.h

collect.obj : collect.c collect.h
