
!include <ntwin32.mak>

PROJ = secfile.exe
DEPS = secfile.obj
LIBS_EXT =

.c.obj:
	$(cc) /YX $(cdebug) $(cflags) $(cvars) $<

$(PROJ) : $(DEPS)
	$(link) @<<
$**
-out:$@
$(conlibs)
$(conlflags)
$(ldebug)
$(LIBS_EXT)
<<

clean:
	del *.obj *.bak *.pdb *.pch *.exe *.dll *.lib *.exp
