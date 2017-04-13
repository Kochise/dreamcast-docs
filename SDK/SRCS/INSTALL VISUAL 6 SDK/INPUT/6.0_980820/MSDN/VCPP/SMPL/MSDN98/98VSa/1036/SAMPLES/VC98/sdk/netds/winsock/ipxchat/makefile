# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: ipxchat.exe

# Update the resource if necessary

OBJS = ipxchat.obj about.obj dispatch.obj init.obj misc.obj winmain.obj listen.obj connect.obj

# Inference rules
.c.obj:
   $(cc) $(cflags) $(cvars) $(cdebug) $<


# Dependencies

ipxchat.obj:  ipxchat.c
about.obj:    about.c globals.h
init.obj:     init.c globals.h
dispatch.obj: dispatch.c globals.h
misc.obj:     misc.c globals.h
winmain.obj:  winmain.c globals.h
listen.obj:   listen.c globals.h
connect.obj:  connect.c globals.h


ipxchat.res: ipxchat.rc globals.h
    rc -r $(rcvars) ipxchat.rc

ipxchat.exe: $(OBJS) ipxchat.res
   $(link)                                       \
      $(linkdebug) $(guiflags)                   \
          -out:ipxchat.exe                           \
          $(OBJS)                                    \
          ipxchat.res                                \
          $(guilibs) version.lib


clean:
   del *.obj
   del *.res
   del *.bak
   del *.pdb
   del *.vcp
   del *.mdp

cleaner: clean
   del *.exe
