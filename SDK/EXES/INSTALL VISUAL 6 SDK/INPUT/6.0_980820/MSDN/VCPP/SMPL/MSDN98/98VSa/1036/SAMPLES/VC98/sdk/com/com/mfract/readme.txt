OLE COM Sample


The MFract sample uses OLE2's Component Object Model (COM) to provide a 
mechanism for implementing modular fractal engines. 

Each of MFract's fractal engines are implemented as inproc servers that 
provide a custom interface called IFractalEngine. This allows new fractal 
engines to be created for MFract without having to modify or recompile the 
application. In fact, creating a new fractal engine doesn't require that the 
programmer know anything about Mfract beyond the custom interfaces that it 
uses.

To compile
----------

MFract can be compiled as either a Unicode or ANSI application. Type 
"nmake unicode" to build a Unicode version. Type "nmake" or "nmake ansi" to 
build an ANSI version. Type "nmake clean" to remove any target files from 
the build.

To run
------

Run regedit MFract.Reg to register Mfract.
Run MFract.Exe.

