# For GNU disasm libs (libopcodes) -- correct for your setup
LO_BASE=/usr/local/sh-linux-elf/lib
LO_LIBS=-L$(LO_BASE) -lbfd -lopcodes
LO_INCS=-I/usr/local/sh-linux-elf/include


CFLAGS  = -g -O2 -Ish4sim $(LO_INCS)
LDFLAGS = -g
LIBS = -Lsh4sim -lsh4sim -lncurses $(LO_LIBS)
OBJS = main.o serial.o stubcomm.o screen.o disasm.o

all: make-sh4sim dreamice

dreamice: sh4sim/libsh4sim.a $(OBJS)
	gcc $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

make-sh4sim:
	make -C sh4sim

%.o: %.c
	gcc $(CFLAGS) $(INCS) -c $< -o $@

clean:
	make -C sh4sim clean
	-rm -f *.o *.bck *~


