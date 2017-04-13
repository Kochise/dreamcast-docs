Sample CMC Client


The CMC.Cli sample demonstrates using Common Messaging Calls (CMC) functions.

The sample is a very simple mail client. Using it is intuitive and
straightforward.

To run this application, you have to have the MAPI run-time binaries
installed on your system. For installation instructions, see the
README.WRI in the mstools\mapi\ directory.

When writing CMC applications, the addresses of all of the CMC functions
has to be obtained explicitly using GetProcAddress, as opposed to
linking with the import library for MAPI.DLL. You may wish to adapt
the function InitSimpleCMC() from CMCCLI.C for this purpose.

If sending/receiving mail is not the primary function of your application,
you can test presence of CMC in a system without incurring the high cost of
trying to load a DLL. You can test the value of the CMC variable. It is 1
if CMC is installed. The variable is located in the [mail] section of your
WIN.INI file on a 16-bit Windows system and under
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows Messaging Subsystem
in the system registry on a 32-bit Windows system. You can cut and paste
the function fCMCInstalled() from CMCCLI.C for this purpose.
