Miscellaneous sample program -- Reboot
-----------------------------------------

* Purpose:
This small sample demonstrates how to force-reboot the Dreamcast.

It fakes a divide-by-zero exception, catches the exception, and
then calls ResetToFirmware (defined in platutil.lib and declared
in platutil.h).

The output in the debugger should look something like this:

DCTOOL: PCFS: Open: Samples\reboot.exe using Vchannel.
0x8cee620c: Exception ffffffe0 Thread=8cee620c Proc=8ce1bf1e 'reboot.exe'
0x8cee620c: AKY=00000021 PC=01db4324 RA=8c01b466 TEA=00000000
0x8cee620c: Calling exception handler @0001111c(000112f4) Frame=0c02fe78
0x8cee620c: exception dispostion = 4
Unhandled exception caught in WinMain -- rebooting

* Required Files\Parameters:
None

* This sample does not reach an exit state since the machine is rebooted
during execution