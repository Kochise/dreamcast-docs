!include <ntwin32.MAK>


mylibs = wsock32.lib 

lincl = -I . 

all: client.exe server.exe

# Update the object files if necessary
client.obj: client.c 
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(lincl) client.c
server.obj: server.c 
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(lincl) server.c


# Since the link line has some severe differences depending on what
# platform we are running on, we need to special case this so that
# we execute the correct commands:

client.exe: client.obj
    $(link) $(linkdebug) $(conlflags) client.obj  $(conlibs) $(mylibs) -out:client.exe
server.exe: server.obj
    $(link) $(linkdebug) $(conlflags) server.obj  $(conlibs) $(mylibs) -out:server.exe


# Clean up everything
clean :
    -del *.exe
    -del *.obj

