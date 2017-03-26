
TARGET = vq-example.elf
OBJS = vq-example.o fruit.o 

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(OBJS) fruit.vq

rm-elf:
	-rm -f $(TARGET) 

$(TARGET): $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -lgl $(KOS_LIBS) -lm

fruit.o: fruit.vq
	$(KOS_BASE)/utils/bin2o/bin2o fruit.vq fruit fruit.o

fruit.vq: fruit.jpg
	$(KOS_BASE)/utils/vqenc/vqenc -t -v fruit.jpg

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) 
	$(KOS_STRIP) $(TARGET)

