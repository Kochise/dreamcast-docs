all: libsh4sim.a

CFLAGS  = -g -O2 -fno-strict-aliasing
LDFLAGS = -g
LIBOBJS  = sh4sim.o exec.o debug.o
LIBOBJS += exec0000.o exec1000.o exec2000.o exec3000.o exec4000.o exec5000.o
LIBOBJS += exec6000.o exec7000.o exec8000.o exec9000.o execa000.o execb000.o
LIBOBJS += execc000.o execd000.o exece000.o execf000.o


libsh4sim.a: $(LIBOBJS)
	ar rcs $@ $^

%.o: %.c
	gcc $(CFLAGS) $(INCS) -c $< -o $@

clean:
	-rm -f *.o *.bck *~

