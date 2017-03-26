#
# Kosh
# (c)2001 Jordan DeLong
#   

KOS_LOCAL_CFLAGS := -DSERIAL
TARGET = kosh.elf
OBJS = builtin.o chdir.o kosh.o input.o jobs.o

include $(KOS_BASE)/loadable/programs/Makefile.prefab

LIBS = -lconio

