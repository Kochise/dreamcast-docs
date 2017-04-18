Read-me for DB-Flash V1.0  20 / 01 /99
======================================

Using DBFlash
-------------

1  Run DBFlash.
2  Browse for the Firmware files for the device that you wish to Reflash.
   If you select a Firmware file that is older than the one currently installed
   select the Reflash check-box to confirm that you want to reflash the device.
3  Click Reflash.

NOTE: The Reflash button only becomes active when you specify a device to Reflash.


DBFlash command-line options
----------------------------

/Dfilename       Specify the filename and path of the DA Firmware.
/Gfilename       Specify the filename and path of the GDM Firmware.
/Bfilename       Specify the filename and path of the Boot ROM Firmware.
/Ofilename       Specify the Output Log filename.
/F               Automatically reflash specified devices when DBFlash runs. 
/N               Show no error Dialogs.
                 Use /N with /F to run DBflash from the command-line and automatically
                 reflash specified devices. 
/?               Display help on using the command-line.

Example command-line:

dbflash /Dc:\flashes\ga4_6_0a.fsh /Gc:\flashes\gm2_5_0e.fsh /Bc:\flashes\btrf5001.bin /Oc:\dbflash\log.txt /F /N



Error messages from the return code
-----------------------------------

0        No Error - Successfully flashed.
1        Bad DA Flash Filename.
2        Bad GDM Flash Filename.
3        Bad Boot ROM Flash Filename.
4        Bad Output Log Filename.
5        Failed To Flash DA.
6        Failed To Flash GDM.
7        Failed To Flash Boot ROM.
8        Failed To Flash Boot ROM - Timed Out whilst Flashing. Probably the write protect switch is on.
9        Nothing to flash. No flash files have been defined. See switches /D /G /B.
10       DB-Flash already running.




Reflashing
----------
Reflashing takes between 20 and 60 seconds. To reflash the:
*  DA takes approximately 20 seconds.
*  GDM takes approximately 20 seconds.
*  BootRom takes approximately 60 seconds.

If you select more than one device the reflash is the longest time required by any one device.
For example, reflashing the DA and the BootRom simultaneously will take approximately 60 seconds.

NOTE: If you reflash the DA DBFlash appears to hang for 20 seconds.
This is normal and is due to the DA's flash command returning only on completion.

NOTE: Make sure that the Katana DevBox is not write protected before reflasing the BootRom.
The write protect switch is labelled SLIDE SW on the front of the Set5 Katana DevBox.
To disable write protect, face the Katana DevBox and slide the switch to your right.
After reflashing the device, return the switch to the left.

When you run DBFlash all activity is recorded in the log window and any errors are shown.
*  To write the log to a file set /Ofilename on the command-line.
