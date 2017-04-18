NAME = VDYNDEBD

# Definitions for the debug level 

DDEBUG  =-DDEBLEVEL=1 -DDEBUG
#DDEBUG  =-DDEBLEVEL=0

# Definitions for MASM 6 Assembler

ASM    = ml
AFLAGS = -coff -DBLD_COFF -DIS_32 -W2 -c -Cx -Zm -DMASM6 $(DDEBUG)
ASMENV = ML
LFLAGS = /VXD /NOD

# MASM 6 only inference rules

.asm.obj:
	set $(ASMENV)=$(AFLAGS)
	$(ASM) -Fo$*.obj $< 

all : $(NAME).VXD

OBJS = $(NAME).obj

$(NAME).obj: $(NAME).asm

$(NAME).vxd: $(NAME).def $(OBJS)
        link @<<$(NAME).lnk
$(LFLAGS) 
/OUT:$(NAME).vxd
/MAP:$(NAME).map
/DEF:$(NAME).def
$(OBJS)
<<
        mapsym -s -o $(NAME).sym $(NAME).map
