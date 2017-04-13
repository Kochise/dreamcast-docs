TARGETOS=BOTH
!include <win32.MAK>

proj = listen
mylibs = ..\..\testlib\testlib.lib

all: $(proj).exe

# Update the object files if necessary
$(proj).obj: $(proj).c
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(proj).c

# Create library if necessary.
..\testlib\testlib.lib :
  cd ..\..\testlib
  $(MAKE) /A
  cd ..\listen\block

# Since the link line has some severe differences depending on what
# platform we are running on, we need to special case this so that
# we execute the correct commands:

$(proj).exe: $(proj).obj ..\..\testlib\testlib.lib
    $(link) $(linkdebug) $(conlflags) $(proj).obj  $(conlibs) $(mylibs) -out:$(proj).exe


# Clean up everything
clean :
    -del *.exe
    -del *.obj
