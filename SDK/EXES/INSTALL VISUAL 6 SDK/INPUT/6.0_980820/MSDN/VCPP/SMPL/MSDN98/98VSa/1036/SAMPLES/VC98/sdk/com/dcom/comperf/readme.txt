COM Performance Sample

PURPOSE:
This is the reference performance sample for COM/DCOM run on local
and remote machines. This program is both a client and a server.
It launches as a client by default, registering its executable as a
server with COM and creating other instances of itself on a remote and
local machine to be servers. A single command-line argument is allowed
for a remote server name. Performance numbers in calls/sec are output
in tabular form. Tests COM and IDispatch method calls with two security
levels: default/min and full. Use DCOMCNFG to set default security to
Authn Lvl to NONE for best comparison. Parameter sizes are varied to see
effect on security levels(~4/50/4k bytes). Uses psperf.dll MIDL generated
proxy/stub implementation. Put psperf.dll in same dir as this exe on
all machines. Run exe on each machine to automatically register class code
and proxy/stub dll. You can then run on either machine and pass a remote
machine name (DNS or IP address) as single cmd-line parameter. 

Instructions:
	Install on one or more machines as described above. Run on command-
	line as "comperf".
	A single command-line argument is allowed for a remote server name.
 	E.g. "comperf MyComputer" or "comperf 123.44.44.234" using IP address.
	This sample may be compiled as UNICODE or ANSI

Usage: COMPERF [machine name | IP address | /? | -?]
Where:
	/?				Displays help screen
	machine name	Name of remote machine
	IP address		IP address of remote machine
