# LibS3MPlay Example (C) Josh PH3NOM Pearson 2011

OPTFLAGS=-m4-single-only

TARGET = libs3mplay.elf

OBJS = main.o

all: clean $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS) 
	kos-cc -o $(TARGET) $(OBJS)  $(DATAOBJS) $(OBJEXTRA) -ls3mplay

