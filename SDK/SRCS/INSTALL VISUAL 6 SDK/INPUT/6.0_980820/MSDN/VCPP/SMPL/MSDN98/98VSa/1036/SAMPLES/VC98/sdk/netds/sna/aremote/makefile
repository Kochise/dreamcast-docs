!include <ntwin32.mak>

# APPC Remote Makefile
# produces:
#   aremote.exe - the APPC Remote program
#   arsetup.exe - setup service information for running aremote as a service

# the following environment variables should be set before using this makefile
#   ISVLIBS - points to the directory holding the SNA SDK libraries
#   ISVINCS - points to the directory holding the SNA SDK include files
#   CPU     - the CPU type (i386 or mips or alpha) being compiled for

snalibs = wappc32.lib wincsv32.lib
otherlibs = user32.lib advapi32.lib
INCLUDE = $(INCLUDE);$(ISVINCS)

all: aremote.exe arsetup.exe

##########################
# Stuff to build aremote #
##########################
aremote.exe: client.obj server.obj aremote.obj appclib.obj queue.obj
	$(link) $(linkdebug) $(conflags) -out:$*.exe $** $(conlibs) $(snalibs) $(otherlibs)

.c.obj: 
	$(cc) $(cdebug) $(cflags) $(cvars) -DUNICODE -D_UNICODE $*.c

server.c: appclib.h	aremote.h
client.c: appclib.h aremote.h
aremote.c: aremote.h
appclib.c: appclib.h queue.h
queue.c: queue.h

##########################
# Stuff to build arsetup #
##########################

# Update the resource if necessary
arsetup.res: arsetup.rc setupdlg.h
    rc -r -fo arsetup.tmp $(cvars) arsetup.rc
    cvtres -$(CPU) -o arsetup.res arsetup.tmp
    del arsetup.tmp

# Update the object file if necessary

arsetup.obj: arsetup.c arsetup.h setupdlg.h
    $(cc) $(cdebug) $(cflags) $(cvars) arsetup.c

# Update the executable file if necessary, and if so, add the resource back in.

arsetup.exe: arsetup.obj arsetup.res
    $(link) $(linkdebug) $(guiflags) -out:arsetup.exe arsetup.obj arsetup.res $(guilibs) advapi32.lib

###########################
# Remove non-source files #
###########################
clean:
    del arsetup.res
    del arsetup.exe
    del aremote.exe
    del queue.obj
    del client.obj
    del server.obj
    del aremote.obj
    del appclib.obj
    del arsetup.obj
