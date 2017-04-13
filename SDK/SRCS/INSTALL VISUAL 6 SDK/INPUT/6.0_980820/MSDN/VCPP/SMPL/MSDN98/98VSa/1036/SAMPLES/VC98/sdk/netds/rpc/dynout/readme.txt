DYNOUT 


The DYNOUT sample demonstrates how to allocate memory at a server for an n-byte
object and pass it back to the client as an [out]-only parameter. The client
then frees the memory. This technique allows the stub to call the server
without knowing in advance how much data will be returned.

 
FILES 
===== 
 
The directory samples\rpc\dynout contains the following files for
building the sample distributed application DYNOUT: 
 
File          Description
-------------------------
 
README.TXT    Readme file for the dynout sample 
DYNOUT.IDL    Interface definition language file 
DYNOUT.ACF    Attribute configuration file 
DYNOUTC.C     Client main program 
DYNOUTS.C     Server main program 
DYNOUTP.C     Remote procedure 
XX_MIDL.BAT   separate MIDL build file
MAKEFILE      nmake file to build 32-bit client and server applications.

NMAKE builds the executable programs DYNOUT.EXE (client) and
DYNOUTS.EXE (server).
