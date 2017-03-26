SH7091 Optimization Techniques
==============================

1. Samples

sample	    section
--------------------------------------------------
ex053rec   5.3   Recurrence
ex081sq3e  8.1.3 Square of 3 Edge Length
ex081outp  8.1.4 Outer Product
ex082fir   8.2   FIR Filter

.c file:   source code in C language
.src file: object code in Assembly language
.pip file: static figure of pipelining

    The .c files include both of original and
optimized codes. Please ignore lines which
correspond an assembler control instruction
(.xxx instruction) in the .pip files.


2. Compiling

shc -c=a -op=1 -speed -cpu=sh4 -fpu=single source_file.c

    A .src file is generated.


