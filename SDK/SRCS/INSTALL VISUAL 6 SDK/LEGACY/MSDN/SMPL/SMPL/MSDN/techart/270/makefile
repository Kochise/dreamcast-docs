#
#   This makefile constructs a medium model DLL
#

NAME    = PMGRPAPI
EXT     = DLL
 
!ifdef DEBUG
DDEF    = -DDEBUG
CLOPT   = -Zid -Od
MOPT    = -Zi
LOPT    = /CO/LI/MAP

!else
DDEF    =
CLOPT   = -Ows
MOPT    = 
LOPT    =
!endif

# general defines
DEF     = -DSTRICT

# tools
ASM     = masm -Mx $(MOPT) $(DDEF)
CC      = cl -nologo -c -Alnw -G2sw -Zp -W3 $(CLOPT) $(DDEF) $(DEF)
LINK    = link /NOD/NOE $(LOPT)
RC      = rc $(DDEF) $(DEF)
HC      = hc30

# object list
OBJ1 = $(NAME).obj
OBJ2 =
OBJ  = $(OBJ1) $(OBJ2)

# library list
LIBS = libw mdllcew ddeml

#inference rules
.c.obj:
    $(CC) $*.c

.asm.obj:
    $(ASM) $*;

#main target
goal: $(NAME).$(EXT) $(NAME).lib

$(NAME).$(EXT): libentry.obj $(OBJ) $(NAME).def
    $(LINK) @<<
    libentry.obj +
    $(OBJ1) +
    $(OBJ2),
    $(NAME).$(EXT),
    $(NAME).map,
    $(LIBS),
    $(NAME).def
<<

$(NAME).lib: $(NAME).def
    implib $(NAME).lib $(NAME).def

clean:
    -del *.obj
    -del $(NAME).$(EXT)
    -del *.map
    -del $(NAME).lib
