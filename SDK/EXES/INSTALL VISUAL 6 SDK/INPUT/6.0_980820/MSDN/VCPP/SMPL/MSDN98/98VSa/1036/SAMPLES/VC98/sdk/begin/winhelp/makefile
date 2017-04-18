
# Nmake macros for building Windows 32-Bit apps

APPVER=4.0
TARGETOS=WIN95

!include <win32.mak>

PROJ = sample

all: $(PROJ).hlp

# Build rule for help file
$(PROJ).hlp: $(PROJ).hpj sample6.rtf
    $(hc) $(PROJ).hpj



# Rules for cleaning out those old files
clean:
    del *.log *.hlp
