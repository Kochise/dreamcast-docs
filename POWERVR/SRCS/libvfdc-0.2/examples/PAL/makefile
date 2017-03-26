######################################################################
#                       Video for DreamCast  V 0.2                   #
######################################################################
#																	 #
#																	 #
#									 Makefile (c)2003 from La Cible  #
######################################################################

# Files ---------------------------------------------------------------------------
TARGET 	= m2v.elf

OBJS 	=	m2v.o

KOS_CFLAGS+= -I../../include
KOS_LDFLAGS+= -L../../lib

# Base ----------------------------------------------------------------------------
all: 		$(TARGET)
include 	$(KOS_BASE)/Makefile.rules

# Link ----------------------------------------------------------------------------
$(TARGET): 	$(OBJS) romdisk.o 
			$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) $(OBJS) romdisk.o -lmpg $(OBJEXTRA) $(KOS_LIBS)  

# ROM Disk Creation ---------------------------------------------------------------
rd :			
			$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.img :
			$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o :	romdisk.img
			$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o
# Upload program on Dreamcast using $KOS_LOADER -----------------------------------
run: 		$(TARGET)
			dc-tool -b 115200 -x  $(TARGET)

# Miscellaneous -------------------------------------------------------------------
dist:
			rm -f $(OBJS)
			$(KOS_STRIP) $(TARGET)

bin:		$(TARGET)
			$(KOS_OBJCOPY) $(TARGET) m2v.bin

clean:		clean_elf
			-rm -f $(OBJS)

clean_elf:
			-rm -f $(TARGET) romdisk.*

#----------------------------------------------------------------------------------
