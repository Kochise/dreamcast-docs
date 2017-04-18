CONNECT Example
===============

Example to abstract the different initialization procedures and PPP login
for Planet Web and Access stacks.

Getting the Planet Web stack up and running...

NetUtl sends informative strings out to a dumb ASCII terminal
(HyperTerminal) running on a PC via a null terminated serial cable.
If you want output sent to the dumb terminal try the following:

-Get a serial cable and a null modem adapter
-Attach it to Set-5 and the PC
-Configure the terminal program as follows:
	BPS:			57600
	Data bits:		8
	Parity:			none
	Stop Bits:		1
	Flow Control:		Hardware
	Standard ANSI terminal settings.

You will need ISP information (telephone number, username, password).
Once the debug cable is attached, you should compile and run the code.


netUtl.c	contains the NUTransport calls that does the connection for you.
netUtl.h	please read this header file

njloop.c	ninja loop code

sample1.c	the main program flow

usrUtl.c        flash reading library code


MAKEFILE *important*

Use the additinal defines variable (EXTRA_DEFS) to specify either
KGTRN_PLANET_WEB or KGTRN_ACCESS and recompile the code.
The same program will then run on the STACK specified.


Main calls in netUtl.c are :

NUInitTransport(<isp details structure>)
	leave this blank if you want to use the internal flash ram settings

NUConnectTransport()
	call this to start the dial up etc..

NUPollTransport()
	call this every frame to find out status of connection - returns status NUSTATE.

NUDisconnectTransport()
	call this to break the line

NUKillTransport()
	call this at end of program

