# Nmake macros for building Win32 applications
!include <ntwin32.mak>

# Inference Rules
.c.Obj:
    $(cc) $(cdebug) $(cflags) $*.C
.obj.exe:
    $(link) $(ldebug) -out:$*.exe $**\
      advapi32.lib user32.Lib

# Macro Defines
PROJ1=client
PROJ2=server

# Target List
All: $(PROJ1).exe $(PROJ2).exe

# Source Objects
$(PROJ1).obj: $(PROJ1).c
$(PROJ2).obj: $(PROJ2).c

# Executables
$(PROJ1).exe: $(PROJ1).obj
$(PROJ2).exe: $(PROJ2).obj

# Clean Up Everything
CleanAll: clean
    del *.Exe

# Clean Up Everything Except .exe Files
Clean:
    del *.obj
