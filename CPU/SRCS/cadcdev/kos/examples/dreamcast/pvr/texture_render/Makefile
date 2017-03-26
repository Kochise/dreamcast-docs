#
# texture_render
# (c) Dan Potter
# (c) 2006 Lawrence Sebald
#   

TARGET = texture_render.bin
TARGET_ELF = texture_render.elf

OBJS = ta.o

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET_ELF) $(TARGET) $(OBJS)

rm-elf:
	-rm -f $(TARGET_ELF)
	-rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET_ELF) $(KOS_START) \
		$(OBJS) $(OBJEXTRA) $(KOS_LIBS)
	$(KOS_OBJCOPY) -R .stack -O binary $(TARGET_ELF) $(TARGET)

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS)
	$(KOS_STRIP) $(TARGET)

