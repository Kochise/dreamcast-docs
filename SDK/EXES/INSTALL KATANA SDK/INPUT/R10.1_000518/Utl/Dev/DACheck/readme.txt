DACheck v2.0
------------

Supports new GD-M flash ROM fix for data/time stamps.



DACheck v1.3
------------

This is now using the latest version of SALSA library ( 1.23 )

Sets the GDM's Defaults on exit ( Auto-emulation OFF, Removable ON ).



DACheck v1.2
------------

On the 'Reset Options' Dialog there is new option called 'Factory Settings'. 
This option when selected will setup the DA-Board with the factory settings.

A 'Loop Test' button has been added to the right of the Test Buttons. 
This will toggle between 'One Pass' and 'Loop' test modes. 
If loop is selected it will perform the test indefinitely until Cancel Test is selected.

There is now a progress dialog when re-flashing.



Previous versions...
--------------------
Supports Katana Set 5.

Supports NTFS.

Locations where the Stub is loaded and where test programs are loaded are no longer shown.

Two options have been added on the 'Reset Options' Dialog...

1) 'Debug Stub in cacheable memory' - After a reset this will load the Debug Stub into a cacheable area of memory,
   and turns the cache on. This will increase the performance of the Stub.
   WARNING ! this option is not to be enabled on pre 'SET4 Final' Katanas. This is due to the absence of the cache 
   on these Katanas. The default option for this is DISABLED.
   This option is only available for CPU debugging.

2) 'Enable Persistent Suspend' - This option maintains 'ASE Pin Break' until suspend Acknowledged.
   This is recommended when considerable BIOS activity is present.
   The default for this option is ENABLED.


The GD-M check will now work from V1.4.0a to the current version. 
(Previous versions of DA-Check the GDM test would only work on v2.1.0a 
 because the emulation '.HCD' file format has to match the firmware version ).

During the 'GD-M TEST' there is now a test for the GD-ROM ( if it is connected ).
For this test to work you will need a 'GD-M TEST Gold-Disk'. 
This tests that the EIDE bus works with the GD switch in the 'GD-ROM' position.

This version now enables you to re-flash a DA which has pre-release firmware ( less than v0.7) on it.

The system font size problem is now fixed.

The DA.log and GDM.log files now rename the existing file to DA.old and a GDM.old.
