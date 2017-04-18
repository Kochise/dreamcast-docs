#--------------------------------------------------------------------------------------------#
#  CONFIDENTIAL AND PROPRIETARY:                                                             #
#       Copyright 2000 Sega of Europe, Sega of America Dreamcast.  All rights reserved.      #
#       This sample source code is provided for demonstration purposes only.                 #
#       Use and distribution of Sega proprietary material is governed by                     #
#       developer licensing agreement.                                                       #
#--------------------------------------------------------------------------------------------#

#--------------------------------------------------------------------------------------------#
#  Name:     DC.inc                                                                          #
#  Title:    Dreamcast Makefile                                                              #
#  Author:   Thomas Szirtes / Gary Lake                                                      #
#  Modified: December 14, 1999		                                                     #
#                                                                                            #
#  Description:                                                                              #
#     Shared Makefile definitions required to build sample Dreamcast projects.               #
#                                                                                            #
#  How to use this makefile:                                                                 #
#                                                                                            #
#  Set PROJECT_SRCS to your list of source files, these can be .c, .cpp. .ic, .asm.          #
#  The makefile will choose the correct compiler and produces .objs in the /obj directory.   #
#                                                                                            #
#  If you have any extra precompiled object files list them in EXTRA_OBJS.                   #
#                                                                                            #
#  Choose the graphics library you will be linking to by setting the GFXLIB to either        #
#  NINJA, KAMUI2 or DARKNESS.  This will affect the libraries and include paths used,        #
#  and controls the initialization code in sbinit.c file.                                    #
#                                                                                            #
#  Choose between using Hitachi, GNU, and Metrowerks compilers by changing the variable      #
#  COMPILER to SHC, GNU, or MWSHC respectively.  This also affects the libs and runtimes.    #
#                                                                                            #
#  If you require any additional system libraries to be included other than SHINOBI and      #
#  the core graphics lib (like sound libraries) then list them in SYSTEM_LIBS (without	     #
#  path or extension).                                                                       #
#                                                                                            #
#  If you have any extra libraries not provided with the SDK list them in PROJECT_LIBS       #
#  together with the path and extension.                                                     #
#                                                                                            #
#  Select the output type variable OUTPUT to either BIN or ELF and you can select if         #
#  they include debug information with boolean variable DEBUG and a map file with LIST       #
#--------------------------------------------------------------------------------------------#


#--- Allow sources to be in multiple directories ---#
PROJECT_OBJS = $(addprefix $(OBJDIR)\,$(notdir $(subst \,/,$(addsuffix .obj,$(basename $(PROJECT_SRC))))))

#--- All objects to be linked - order is very important ---#
PROJECT_LNK = $(addprefix xlnk.,$(DEF_OBJS) $(DEBUG_OBJS)) $(addprefix lnk.,$(PROJECT_OBJS) $(EXTRA_OBJS))

#VPATH = $(addsuffix :,$(dir $(subst \,/,$(PROJECT_SRC))))

.SILENT :
.SUFFIXES : .c .cpp .src .S .bin .lib .elf


#--------------------------------------------------------------------------------------------#
# Global makefile definitions                                                                #
#--------------------------------------------------------------------------------------------#

TRUE		= 1
FALSE		= 0

#--- Default values ---#
ifndef OPTIMIZE
OPTIMIZE	= 1
endif
ifndef DEBUG
DEBUG		= FALSE
endif
ifndef LIST
LIST		= FALSE
endif
ifndef GFXLIB
GFXLIB		= KAMUI2
endif
ifndef COMPILER
COMPILER	= SHC
endif
ifndef OUTPUT
OUTPUT		= ELF
endif

#--- Binary files cannot contain debug info ---#
ifeq ($(OUTPUT),BIN)
DEBUG		= FALSE
endif

#--- Hitachi opt. linker option. ---#
ifndef OPT_LINK
OPT_LINK	= FALSE
endif
ifneq ($(OUTPUT),SHC)
OPT_LINK	= FALSE
endif


#--------------------------------------------------------------------------------------------#
# Build tools (compiler, linker, assembler, etc.)                                            #
#--------------------------------------------------------------------------------------------#

MAKE		= gmake.exe
DWFCONV		= dwfcnv.exe
ELFCONV		= elfcnv.exe
ELF2BIN		= elf2bin.exe

#--- Hitachi tools ---#
ifeq ($(COMPILER),SHC)
CC		= shc.exe
CPP		= shcpp.exe
ASM		= asmsh.exe
LIBR		= lbr.exe
ifeq ($(OPT_LINK),TRUE)
LINK		= optlnksh.exe	#--- Hitachi opt. linker is not currently stable
else
LINK		= lnk.exe
endif
endif

#--- GNU tools ---#
ifeq ($(COMPILER),GNU)
CC		= gcc.exe
CPP		= gcc.exe
ASM		= as.exe
LINK		= ld.exe
LIBR		= ar.exe
endif

#--- Metrowerks tools ---#
ifeq ($(COMPILER),MWERKS)
CC		= mwshc.exe
CPP		= mwshc.exe
ASM		= mwasmshx.exe
LINK		= mwldshx.exe
LIBR		= mwldshx.exe
endif


#--------------------------------------------------------------------------------------------#
# Default libraries, objects, and directory locations                                        #
#--------------------------------------------------------------------------------------------#

#--- Directory locations ---#
OUTDIR		= exe
OBJDIR		= obj

#--- Library directories ---#
ifeq ($(COMPILER),SHC)
LIBDIR		= $(KATANA_ROOT)\lib
endif
ifeq ($(COMPILER),GNU)
LIBDIR          = $(KATANA_ROOT)\lib\gnu
endif
ifeq ($(COMPILER),MWERKS)
LIBDIR          = $(KATANA_ROOT)\Lib\Mwerks
endif

#--- Include directories ---#
DEF_INCLUDE	= $(KATANA_ROOT)\include

ifndef SYSTEM_INCLUDE
SYSTEM_INCLUDE	= .
endif
ifndef PROJECT_INCLUDE
PROJECT_INCLUDE	= .
endif

#--- Default libraries and object files ---#
DEF_LIBS	= $(GFXLIB)\
		  shinobi\
		  sh4nlfzn\
		  $(GFXLIB)	# libraries specified multiple times for GNU linker

DEF_OBJS	= strt1.obj\
		  strt2.obj\
		  systemid.obj\
		  toc.obj\
		  sg_sec.obj\
		  sg_arejp.obj\
		  sg_areus.obj\
		  sg_areec.obj\
		  sg_are00.obj\
		  sg_are01.obj\
		  sg_are02.obj\
		  sg_are03.obj\
		  sg_are04.obj\
		  sg_ini.obj\
		  aip.obj\
		  zero.obj

#--- LibCross fileserver objects, for debug only ---#
ifeq ($(DEBUG),TRUE)
DEBUG_OBJS	= snasm.obj\
		  lock.obj\
		  syscalls.obj\
		  close.obj\
		  open.obj\
		  read.obj\
		  write.obj\
		  lseek.obj
else
DEBUG_OBJS	=
endif


#--------------------------------------------------------------------------------------------#
# Compiler switches                                                                          #
#--------------------------------------------------------------------------------------------#

#--- Hitachi optimization flag ---#
ifeq ($(COMPILER),SHC)
C_OPTIMIZE	= -optimize=$(OPTIMIZE)
endif

#--- GNU optimization flag ---#
ifeq ($(COMPILER),GNU)
ifeq ($(OPTIMIZE),$(TRUE))
C_OPTIMIZE	= -O2
else
C_OPTIMIZE	= 
endif
endif

#--- Metrowerks optimization flag ---#
ifeq ($(COMPILER),MWERKS)
ifeq ($(OPTIMIZE),$(FALSE))
C_OPTIMIZE	= -O$(OPTIMIZE),p\
		  -cw_inline none,noauto	# auto-inline off for optimization level 0
else
C_OPTIMIZE	= -O$(OPTIMIZE),p\
		  -cw_inline smart,auto
endif
endif

#--- Hitachi debug flags ---#
ifeq ($(COMPILER),SHC)
ifeq ($(DEBUG),TRUE)
C_DEBUG		= $(C_OPTIMIZE) -size -debug
else
C_DEBUG		= $(C_OPTIMIZE) -speed -nodebug
endif
endif

#--- GNU debug flags ---#
ifeq ($(COMPILER),GNU)
ifeq ($(DEBUG),TRUE)
C_DEBUG		= $(C_OPTIMIZE) -g
else
C_DEBUG		= $(C_OPTIMIZE)
endif
endif

#--- Metrowerks debug flags ---#
ifeq ($(COMPILER),MWERKS)
ifeq ($(DEBUG),TRUE)
C_DEBUG		= $(C_OPTIMIZE) -sym on
else
C_DEBUG		= $(C_OPTIMIZE)
endif
endif

#--- Compiler listing output (assembly) ---#
ifeq ($(LIST),TRUE)
ifeq ($(COMPILER),SHC)
C_LIST		= -list="$(OBJDIR)\$*.lst"
else
C_LIST		=
endif
else
C_LIST		=
endif

#--- Opt. linker support ---#
ifeq ($(OPT_LINK),TRUE)
C_OPT_LINK = -g
else
C_OPT_LINK =
endif


#--------------------------------------------------------------------------------------------#
# Compiler defines                                                                           #
#--------------------------------------------------------------------------------------------#

C_DEFS		= _$(GFXLIB)_ __SET4__ __SET5__ __KATANA__ _CLX_ _CLX2_ _STRICT_UNION_

#--- If building a .bin file (for shinobi_workaround) ---#
ifeq ($(COMPILER),GNU)
ifeq ($(OUTPUT),BIN)
C_EXTRA	= -D_BIN_
else
C_EXTRA =
endif
endif


#--------------------------------------------------------------------------------------------#
# Compiler options                                                                           #
#--------------------------------------------------------------------------------------------#

#--- Hitachi compiler options ---#
ifeq ($(COMPILER),SHC)
C_OPTS		= -cpu=sh4\
		  -division=cpu\
		  -endian=little\
		  -fpu=single\
		  -round=nearest\
		  -pic=0\
		  -macsave=0\
		  -string=const\
		  -comment=nonest\
		  -sjis\
		  -section=p=P,c=C,d=D,b=B\
		  -show=obj,source,expansion,w=80,l=0
endif

#--- GNU compiler options ---#
ifeq ($(COMPILER),GNU)
C_OPTS		= -mhitachi\
		  -mnomacsave\
		  -m4-single-only\
		  -ml\
		  -fno-expand-main\
		  -ffast-math
# Note: -fno-expand-main required so global constructors can be called after Shinobi initialization
endif

#--- Metrowerks compiler options ---#
ifeq ($(COMPILER),MWERKS)
C_OPTS		= -cp SH4\
		  -en little\
		  -enum int\
		  -wchar_t off\
		  -mw_fp hard\
		  -ARM off\
		  -bool off\
		  -strict off\
		  -RTTI off\
		  -relax_pointers\
		  -cpp_exceptions off\
		  -w off
endif

C_FLAGS		= $(C_OPTS) $(C_EXTRA) $(C_DEBUG) $(C_OPT_LINK) $(C_LIST)

# Note: -extra=a=800 flag has been removed from standard Hitachi compile


#--------------------------------------------------------------------------------------------#
# Assembler switches                                                                         #
#--------------------------------------------------------------------------------------------#

#--- Hitachi assembler debug flag ---#
ifeq ($(DEBUG),TRUE)
ifeq ($(COMPILER),SHC)
ASM_DEBUG	= -debug=d
else
ASM_DEBUG	=
endif
else
ASM_DEBUG	=
endif

#--- Assembler listing output ---#
ifeq ($(LIST),TRUE)

#--- Hitachi assembler listing ---#
ifeq ($(COMPILER),SHC)
ASM_LIST	= -list="$(OBJDIR)\$*.lst"
endif

#--- GNU assembler listing ---#
ifeq ($(COMPILER),GNU)
ASM_LIST	= -alh > $(OBJDIR)\\$*.lst
endif

ifeq ($(COMPILER),MWERKS)
ASM_LIST	=
endif

else
ASM_LIST	=
endif


#--------------------------------------------------------------------------------------------#
# Assembler options                                                                          #
#--------------------------------------------------------------------------------------------#

#--- Hitachi assembler options ---#
ifeq ($(COMPILER),SHC)
ASM_OPTS	= -cpu=sh4\
		  -endian=little\
		  -sjis\
		  -private
endif

#--- GNU assembler options ---#
ifeq ($(COMPILER),GNU)
ASM_OPTS	= -little
endif

#--- Metrowerks assembler options ---#
ifeq ($(COMPILER),MWERKS)
ASM_OPTS	= -little\
		  -c\
		  -proc SH4
endif

ASM_FLAGS	= $(ASM_OPTS) $(ASM_DEBUG) $(ASM_LIST)


#--------------------------------------------------------------------------------------------#
# Linker switches                                                                            #
#--------------------------------------------------------------------------------------------#

#--- Debug options ---#
ifeq ($(DEBUG),TRUE)

#--- Hitachi linker debug flag ---#
ifeq ($(COMPILER),SHC)
LINK_DEBUG	= debug
endif

#--- GNU linker debug flag ---#
ifeq ($(COMPILER),GNU)
LINK_DEBUG	=
endif

#--- Metrowerks linker debug flag ---#
ifeq ($(COMPILER),MWERKS)
LINK_DEBUG	= -sym on
endif

else
LINK_DEBUG	=
endif

#--- Linker map file output ---#
ifeq ($(LIST),TRUE)

#--- Hitachi map file support ---#
ifeq ($(COMPILER),SHC)
LINK_LIST	= print $*.map
endif

#--- GNU map file support ---#
ifeq ($(COMPILER),GNU)
LINK_LIST	= -Xlinker -Map -Xlinker $(OUTDIR)\$(PROJECT).map
endif

#--- Metrowerks map file support ---#
ifeq ($(COMPILER),MWERKS)
LINK_LIST	= -map
endif

else
LINK_LIST	=
endif

#--- Opt. linker selected ---#
ifeq ($(OPT_LINK),TRUE)
L_OPT_LINK = op speed
else
L_OPT_LINK =
endif


#--------------------------------------------------------------------------------------------#
# Linker options                                                                             #
#--------------------------------------------------------------------------------------------#

#--- Hitachi start symbol ---#
ifeq ($(COMPILER),SHC)

#--- If building a .bin file ---#
ifeq ($(OUTPUT),BIN)
ifeq ($(OPT_LINK),TRUE)
LINK_EXTRA	= entry SG_SEC
else
LINK_EXTRA	=
endif

#--- If building an .elf file ---#
else
LINK_EXTRA	= entry SG_SEC
endif
endif

ifeq ($(COMPILER),GNU)
LINK_EXTRA	=
endif

#--- Metrowerks start symbol ---#
ifeq ($(COMPILER),MWERKS)
LINK_EXTRA	= -main SG_SEC
endif

#--- Hitachi linker options ---#
ifeq ($(COMPILER),SHC)
LINK_START	= start IP(8C008000),DSGLH(8C010000)
LINK_FORM	= form a
LINK_OPTS	= align_section\
		  udfcheck\
		  elf
endif

#--- GNU linker options ---#
ifeq ($(COMPILER),GNU)
LINK_OPTS	= -Xlinker -T$(DEF_INCLUDE)\sg_shelf.x\
		  -Xlinker -L$(LIBDIR)
endif

#--- Metrowerks linker options ---#
ifeq ($(COMPILER),MWERKS)
LINK_OPTS	= -en little\
		  -msgstyle IDE\
		  -w off\
		  -nofail\
		  -search
endif

LINK_FLAGS	= $(LINK_OPTS) $(LINK_DEBUG)


#--------------------------------------------------------------------------------------------#
# Build rules                                                                                #
#--------------------------------------------------------------------------------------------#

#--------------------------------------------------------------------------------------------#
# Build C files                                                                              #
#--------------------------------------------------------------------------------------------#

$(OBJDIR)\\%.obj: %.c
	echo Compiling $<

#--- Hitachi compiler ---#
ifeq ($(COMPILER),SHC)
	echo $(C_FLAGS) -define= > "$(OBJDIR)\shc.sub"
	for %%x in ($(C_DEFS) $(EXTRA_DEFS)) do echo %%x, >> "$(OBJDIR)\shc.sub"
	echo __SHC__ -include= >> "$(OBJDIR)\shc.sub"
	for %%x in ($(PROJECT_INCLUDE) $(SYSTEM_INCLUDE)) do echo %%x, >> "$(OBJDIR)\shc.sub"
	echo $(DEF_INCLUDE) >> "$(OBJDIR)\shc.sub"
ifeq ($(OPT_LINK),TRUE)
	$(CC) $< -ob="$(OBJDIR)\$*.obj" -sub="$(OBJDIR)\shc.sub"
else
ifeq ($(DEBUG),TRUE)
	$(CC) $< -ob="$(OBJDIR)\$*.o" -sub="$(OBJDIR)\shc.sub"
	$(DWFCONV) -sysrof="$(OBJDIR)\$*.obj" "$(OBJDIR)\$*.o" > nul:
else
	$(CC) $< -ob="$(OBJDIR)\$*.obj" -sub="$(OBJDIR)\shc.sub"
endif
endif
endif

#--- GNU compiler ---#
ifeq ($(COMPILER),GNU)
	echo $(C_FLAGS) > "$(OBJDIR)\shc.sub"
	for %%x in ($(C_DEFS) $(EXTRA_DEFS)) do echo -D%%x >> "$(OBJDIR)\shc.sub"
	for %%x in ($(PROJECT_INCLUDE) $(SYSTEM_INCLUDE) $(DEF_INCLUDE)) do echo -I%%x >> "$(OBJDIR)\shc.sub"
	$(CC) -c $< -o $(OBJDIR)\\$*.obj @$(OBJDIR)\\shc.sub
endif

#--- Metrowerks compiler ---#
ifeq ($(COMPILER),MWERKS)
	echo $(C_FLAGS) > "$(OBJDIR)\shc.sub"
	for %%x in (- $(PROJECT_INCLUDE) $(SYSTEM_INCLUDE) $(DEF_INCLUDE)) do echo -I%%x >> "$(OBJDIR)\shc.sub"
	echo. > "$(OBJDIR)\prefix.h"
	for %%x in ($(C_DEFS) $(EXTRA_DEFS)) do echo #define %%x >> "$(OBJDIR)\prefix.h"
	$(CC) $< -o="$(OBJDIR)\$*.obj" -sub="$(OBJDIR)\shc.sub" -prefix "$(OBJDIR)\prefix.h"
endif


#--------------------------------------------------------------------------------------------#
# Build C++ files                                                                            #
#--------------------------------------------------------------------------------------------#

$(OBJDIR)\\%.obj: %.cpp
	echo Compiling $<

#--- Hitachi compiler ---#
ifeq ($(COMPILER),SHC)
	echo $(C_FLAGS) -define= > "$(OBJDIR)\shc.sub"
	for %%x in ($(C_DEFS) $(EXTRA_DEFS)) do echo %%x, >> "$(OBJDIR)\shc.sub"
	echo __SHC__ -include= >> "$(OBJDIR)\shc.sub"
	for %%x in ($(PROJECT_INCLUDE) $(SYSTEM_INCLUDE)) do echo %%x, >> "$(OBJDIR)\shc.sub"
	echo $(DEF_INCLUDE) >> "$(OBJDIR)\shc.sub"
ifeq ($(OPT_LINK),TRUE)
	$(CPP) $< -ob="$(OBJDIR)\$*.obj" -sub="$(OBJDIR)\shc.sub"
else
ifeq ($(DEBUG), TRUE)
	$(CPP) $< -ob="$(OBJDIR)\$*.o" -sub="$(OBJDIR)\shc.sub" -browser
	$(DWFCONV) -browser="$(OBJDIR)\cppdtb\$(*F).dtb" -sysrof="$(OBJDIR)\$*.obj" "$(OBJDIR)\$*.o" > nul:
else
	$(CPP) $< -ob="$(OBJDIR)\$*.obj" -sub="$(OBJDIR)\shc.sub"
endif
endif
endif

#--- GNU compiler ---#
ifeq ($(COMPILER),GNU)
	echo $(C_FLAGS) > "$(OBJDIR)\shc.sub"
	for %%x in ($(C_DEFS) $(EXTRA_DEFS)) do echo -D%%x >> "$(OBJDIR)\shc.sub"
	for %%x in ($(PROJECT_INCLUDE) $(SYSTEM_INCLUDE) $(DEF_INCLUDE)) do echo -I%%x >> "$(OBJDIR)\shc.sub"
	$(CPP) -c $< -o $(OBJDIR)\\$*.obj @$(OBJDIR)\\shc.sub
endif

#--- Metrowerks compiler ---#
ifeq ($(COMPILER),MWERKS)
	echo $(C_FLAGS) > "$(OBJDIR)\shc.sub"
	for %%x in (- $(PROJECT_INCLUDE) $(SYSTEM_INCLUDE) $(DEF_INCLUDE)) do echo -I%%x >> "$(OBJDIR)\shc.sub"
	echo. > "$(OBJDIR)\prefix.h"
	for %%x in ($(C_DEFS) $(EXTRA_DEFS)) do echo #define %%x >> "$(OBJDIR)\prefix.h"
	for %%x in (_Hitachi_C_ _No_Time_OS_Support _MSL_CX_LIMITED_RANGE _MSL_DLLDATA _No_Alloc_OS_Support) do echo #define %%x >> "$(OBJDIR)\prefix.h"
	echo #define NEWMODE NEWMODE_MALLOC >> "$(OBJDIR)\prefix.h"
	$(CPP) $< -o="$(OBJDIR)\$*.obj" -lang c++ -sub="$(OBJDIR)\shc.sub" -prefix "$(OBJDIR)\prefix.h"
endif


#--------------------------------------------------------------------------------------------#
# Build ASM files                                                                            #
#--------------------------------------------------------------------------------------------#

#--- Hitachi assembler ---#
ifeq ($(COMPILER),SHC)
$(OBJDIR)\\%.obj: %.src
	echo Assembling $<
	$(ASM) $< $(ASM_FLAGS) -O="$@"
endif

#--- GNU assembler ---#
ifeq ($(COMPILER),GNU)
$(OBJDIR)\\%.obj: %.S
	echo Assembling $<
	echo $(C_FLAGS) > "$(OBJDIR)\shc.sub"
	$(CC) -c $< -o $(OBJDIR)\\$*.obj @$(OBJDIR)\\shc.sub -Wa,$(ASM_LIST)
#
#	To call GNU AS directly:
#		$(ASM) $< -o $(OBJDIR)\\$*.obj $(ASM_FLAGS)
endif

#--- Metrowerks assembler ---#
ifeq ($(COMPILER),MWERKS)
$(OBJDIR)\\%.obj: %.asm
	echo Assembling $<
	$(ASM) $< $(ASM_FLAGS) -o "$@"
endif

#--- If no GNU or Metrowerks source exists, convert Hitachi assembly to ELF format ---#
ifneq ($(COMPILER),SHC)
$(OBJDIR)\\%.obj: %.src
	echo Assembling $<
	asmsh.exe $< -cpu=sh4 -endian=little -sjis -private -O="$(OBJDIR)\$*.o"
	$(ELFCONV) "$(OBJDIR)\$*.o" "$(OBJDIR)\$*.obj"
endif


#--------------------------------------------------------------------------------------------#
# Build IC files : Hitachi only
#
# Files with an .ic extension are C source files that include inline assembly.
# They are always compiled without debug information.  If you use a #pragma inline_asm
# anywhere in your code, you can rename your *.c source file to *.ac and this
# rule will be invoked.
#
#--------------------------------------------------------------------------------------------#

#--- Hitachi compiler ---#
ifeq ($(COMPILER),SHC)

$(OBJDIR)\\%.obj: %.ic
	echo Compiling $<
	echo $(C_FLAGS) -code=asmcode -define= > "$(OBJDIR)\shc.sub"
	for %%x in ($(C_DEFS) $(EXTRA_DEFS)) do echo %%x, >> "$(OBJDIR)\shc.sub"
	echo __SHC__ -include= >> "$(OBJDIR)\shc.sub"
	for %%x in ($(PROJECT_INCLUDE) $(SYSTEM_INCLUDE)) do echo %%x, >> "$(OBJDIR)\shc.sub"
	echo $(DEF_INCLUDE) >> "$(OBJDIR)\shc.sub"
	$(CC) $< -ob="$(OBJDIR)\$*.src" -sub="$(OBJDIR)\shc.sub"
	$(ASM) $(OBJDIR)\$*.src $(ASM_FLAGS) -O="$@"
endif


#--------------------------------------------------------------------------------------------#
# Link project files                                                                         #
#--------------------------------------------------------------------------------------------#

#--- Echo all object files to the linker script ---#
lnk.% :
ifeq ($(COMPILER),SHC)
ifeq ($(OUTPUT),LIB)
	echo add $* >> "$(OUTDIR)\lnk.sub"
else
	echo input $* >> "$(OUTDIR)\lnk.sub"
endif
endif
ifeq ($(COMPILER),GNU)
	echo INPUT ($*) >> "$(OUTDIR)\lnk.sub"
endif
ifeq ($(COMPILER),MWERKS)
	echo $* >> "$(OUTDIR)\lnk.sub"
endif

xlnk.% :
ifeq ($(COMPILER),SHC)
ifeq ($(OUTPUT),LIB)
	echo $* >nul:
else
	echo input $(LIBDIR)\$* >> "$(OUTDIR)\lnk.sub"
endif
endif
ifeq ($(COMPILER),GNU)
	echo INPUT ($(LIBDIR)\$*) >> "$(OUTDIR)\lnk.sub"
endif
ifeq ($(COMPILER),MWERKS)
	echo $(LIBDIR)\$*.elf >> "$(OUTDIR)\lnk.sub"
endif

#--- By default, clean out sub files needed for make and build project ---#
ifeq ($(OUTPUT),BIN)
DEFAULT : CREATE_DIR $(PROJECT_LNK) $(OUTDIR)\\$(PROJECT).bin
	echo Completed.
$(OUTDIR)\\$(PROJECT).bin : $(PROJECT_OBJS)
endif
ifeq ($(OUTPUT),ELF)
DEFAULT : CREATE_DIR $(PROJECT_LNK) $(OUTDIR)\\$(PROJECT).elf
	echo Completed.
$(OUTDIR)\\$(PROJECT).elf : $(PROJECT_OBJS)
endif
ifeq ($(OUTPUT),LIB)
DEFAULT : CREATE_DIR $(PROJECT_LNK) $(OUTDIR)\\$(PROJECT).lib
	echo Completed.
$(OUTDIR)\\$(PROJECT).lib : $(PROJECT_OBJS)
endif

#--- Hitachi link process ---#
ifeq ($(COMPILER),SHC)
ifeq ($(OUTPUT),LIB)
	-if exist "$(OUTDIR)\$(PROJECT).lib" del "$(OUTDIR)\$(PROJECT).lib"
ifeq ($(LIST),TRUE)
	echo list $(OUTDIR)\$(PROJECT).ref >> "$(OUTDIR)\lnk.sub"
endif
	echo exit >> "$(OUTDIR)\lnk.sub"
	$(LIBR) -sub="$(OUTDIR)\lnk.sub"
else
	echo $(LINK_START) >> "$(OUTDIR)\lnk.sub"
	echo $(LINK_FORM) >> "$(OUTDIR)\lnk.sub"
ifdef LINK_EXTRA
	echo $(LINK_EXTRA) >> "$(OUTDIR)\lnk.sub"
endif
ifdef LINK_LIST
	echo $(LINK_LIST) >> "$(OUTDIR)\lnk.sub"
endif
	for %%x in ($(LINK_FLAGS)) do echo %%x >> "$(OUTDIR)\lnk.sub"
ifdef PROJECT_LIBS
	for %%x in ($(PROJECT_LIBS)) do echo library %%x >> "$(OUTDIR)\lnk.sub"
endif
	for %%x in ($(SYSTEM_LIBS) $(DEF_LIBS)) do echo library $(LIBDIR)\%%x.lib >> "$(OUTDIR)\lnk.sub"
	echo output $(OUTDIR)\$(PROJECT).elf >> "$(OUTDIR)\lnk.sub"
	echo exit >> "$(OUTDIR)\lnk.sub"
ifeq ($(OPT_LINK),TRUE)
	$(LINK) -sub="$(OUTDIR)\lnk.sub"
else
	$(LINK) -noecho -sub="$(OUTDIR)\lnk.sub"
endif
endif
endif

#--- GNU link process ---#
ifeq ($(COMPILER),GNU)
	for %%x in ($(PROJECT_LIBS) $(SYSTEM_LIBS) $(PROJECT_LIBS) $(DEF_LIBS)) do echo INPUT (-l%%x) >> "$(OUTDIR)\lnk.sub"
	echo $(C_FLAGS) > "$(OUTDIR)\lnk.tmp"
	echo $(LINK_FLAGS) $(LINK_LIST) $(LINK_EXTRA) >> "$(OUTDIR)\lnk.tmp"
	$(CC) @$(OUTDIR)\\lnk.tmp -o $(OUTDIR)\\$(PROJECT).elf -Xlinker -T$(OUTDIR)\\lnk.sub 
#
#	To call GNU LD directly:
#		$(LINK) -m shlelf -EL @$(OUTDIR)\\lnk.tmp -o $(OUTDIR)\\$(PROJECT).elf -T$(OUTDIR)\\lnk.sub
#		#add libc.a, libgcc.a, and crt0.o from m4-single-only folders to complete the link

ifeq ($(DEBUG),TRUE)
ifneq ($(OUTDIR),.)
	echo Copying $(PROJECT).elf from $(OUTDIR) to current directory..
	copy "$(OUTDIR)\$(PROJECT).*" . >nul:
	echo GCC-compiled .elf files must be debugged from directory where source resides
endif
endif
endif

#--- Metrowerks link process ---#
ifeq ($(COMPILER),MWERKS)
	for %%x in ($(PROJECT_LIBS) $(SYSTEM_LIBS) $(DEF_LIBS)) do echo %%x.elf.lib >> "$(OUTDIR)\lnk.sub"
	$(LINK) "$(DEF_INCLUDE)\linker.lcf" $(LINK_FLAGS) $(LINK_EXTRA) $(LINK_LIST) -sub=$(OUTDIR)\\lnk.sub -o $(OUTDIR)\$(PROJECT).elf
endif

#--- Convert ELF to binary ---#
ifeq ($(OUTPUT),BIN)
	$(ELF2BIN) -s 8C010000 "$(OUTDIR)\$(PROJECT).elf"
endif


#--------------------------------------------------------------------------------------------#
# Makefile directives                                                                        #
#--------------------------------------------------------------------------------------------#

#--- Make all ---#
ALL : CLEAN DEFAULT

#--- Clean project files ---#
CLEAN : CLEAN_OBJ CLEAN_EXE

#--- Clean only obj files ---#
CLEAN_OBJ:
ifeq ($(OS),Windows_NT)
	-rd /s /q "$(OBJDIR)" >nul: 2>nul:
else
	-deltree /y "$(OBJDIR)" >nul:
endif
	echo Object files removed

#--- Clean only exe files ---#
CLEAN_EXE :
ifeq ($(OS),Windows_NT)
	-rd /s /q "$(OUTDIR)" >nul: 2>nul:
else
	-deltree /y "$(OUTDIR)" >nul:
endif
ifeq ($(COMPILER),GNU)
	-if exist "$(PROJECT).elf" del "$(PROJECT).elf"
endif
	echo Output files removed

#--- Create directories and sub files ---#
CREATE_DIR :
	-if not exist "$(OBJDIR)\nul" mkdir "$(OBJDIR)"
	-if not exist "$(OUTDIR)\nul" mkdir "$(OUTDIR)"
ifeq ($(OUTPUT),LIB)
	echo create $(OUTDIR)\$(PROJECT).lib > "$(OUTDIR)\lnk.sub"
else
ifeq ($(OPT_LINK),TRUE)
	echo noecho > "$(OUTDIR)\lnk.sub"
	echo $(L_OPT_LINK) >> "$(OUTDIR)\lnk.sub"
else
	echo.> "$(OUTDIR)\lnk.sub"
endif
endif

#--- Debug Makefile ---#
REPORT :
ifeq ($(COMPILER),SHC)
	echo Compiler : Hitachi
endif
ifeq ($(COMPILER),GNU)
	echo Compiler : GNU
endif
ifeq ($(COMPILER),MWERKS)
	echo Compiler : Metrowerks
endif
ifeq ($(OUTPUT),BIN)
	echo Output : Binary
else
	echo Output : Elf
endif
