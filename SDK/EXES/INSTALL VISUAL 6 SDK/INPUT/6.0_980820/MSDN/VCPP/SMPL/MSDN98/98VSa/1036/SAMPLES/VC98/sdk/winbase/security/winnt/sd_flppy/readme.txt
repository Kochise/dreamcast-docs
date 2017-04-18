How to Put a DACL on Floppy Drives


SUMMARY
=======

There is no way to put a DACL on the floppy drives or on
the COM ports with REGEDT32, or using the Control Panel or other
part of the user interface. Also, there is no way to use the
Win32 API to put a DACL on the floppy drives or on the COM ports
that survives reboots.

However, the SD_FLPPY sample does put DACLs on the floppy drives or on
the COM ports that survive logoff and logon; that is, these DACLs
are on the floppy drives or on the COM ports until the next reboot.
This sample is a good starting place for anyone writing code to apply DACLs.

A version of this sample program can be installed as a service, so
that each time the machine boots up the DACLs are automatically re-applied.

This sample is not a supported utility.

MORE INFORMATION
================

There are possibly as many desired user interfaces to this sort of
functionality as there are people thinking about this, so it is
not a purpose of this sample (or the service variation of
it) to present an incredibly cool user interface to how the
DACLs get applied. A very simplistic approach is taken to the
user interface.

To run
------

Type sd_flppy to lock the \\.\A: and \\.\B: devices.

You can optionally put SD_FLPPY.EXE in the Startup group or a logon script.

Notes
-----

The version of this program that is packaged as a service is
in this same directory and is built along with SD_FLPPY.EXE by
the same makefile.

The packaged-as-a-service approach might better suit people who
need to change the DACL on the floppy drives without requiring a
reboot or logoff. After installing the FLOPLOCK service on
the machine, the client application, CHGFLPSD can be used over the
network to lock, unlock or query the floppy-locked-state of any
machine where the FLOPLOCK service is running.

So, this packaged-as-a-service approach might better suit people
that would like to be able to inquire over the net what the
DACLs are on the floppy drives of particular machines (to check
or audit them). This approach might better suit people that
would prefer that the DACLs be applied as the system boots up so
the DACLs are applied before any user has logged on at the keyboard.

The packaged-as-a-service approach is more aligned with the notion
of protecting the floppies as a resource on a particular
_machine_ (regardless of who if anyone is logged on), whereas
the SD_FLPPY approach (running an .exe at logon time) is
more along the lines of keeping a particular user from using
the floppies on any machine that that user might use. However,
once the user has logged onto the machine and locked the
floppies with SD_FLPPY the floppies will stay locked until
reboot. Of course a utility could easily be written that could
run in the startup group of a different authorized user to force the
floppies on any machine this user logs onto to be unlocked.

As noted above, the FLOPLOCK service is built by the single
makefile in this directory. FLOPLOCK.EXE is the main element of
the packaged-as-a-service version. FLOPLOCK installs as a service, using
INSTSRV.EXE. INSTSRV.EXE, as well as CHGFLPSD.EXE, is also built by the
single makefile in this directory

Run "instsrv" to get help on the switches to use when running
INSTSRV.EXE to install the service.

FLOPLOCK creates a named pipe which CHGFLPSD opens to pass
over the lock/unlock/query operations to a particular machine
running FLOPLOCK.EXE - the named pipe is at all times protected
by an Admins-only DACL

Run "chgflpsd" to get help on the switches to use when running
CHGFLPSD.EXE.
