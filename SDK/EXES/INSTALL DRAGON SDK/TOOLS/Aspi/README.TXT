Adaptec Inc., Copyright (c) 2002

ASPI Overview
=======================================================
I  ) Operating Systems and ASPI Files Installed
II ) Changes between v 4.60 and v 4.71
III) GetASPI32Buffer Addendum
IV ) How to increase the non-paged pool size
V  ) Windows XP Support
VI ) Installation of ASPI
VII) Status Codes for ASPIINST.EXE

I. Operating System ASPI Files Installed
========================================================
Microsoft Windows NT 4.0  wnaspi32.dll, aspi32.sys
                          winaspi.dll, wowpost.exe

Microsoft Windows 2000    wnaspi32.dll, aspi32.sys
                          winaspi.dll, wowpost.exe

Microsoft Windows 98      wnaspi32.dll, apix.vxd

Microsoft Windows Me      wnaspi32.dll, apix.vxd

Microsoft Windows XP      wnaspi32.dll, aspi32.sys


II. Changes Between v 4.60 and v 4.71
=======================================================
1)   It is important the following pairs of files have matching version numbers:
     (you may not have all of these files; which files you have in your PC depends
     on which Windows platform is in your PC)

     a)   wnaspi32.dll  and  aspi32.sys
     b)   wnaspi32.dll  and  apix.vxd
     c)   winaspi.dll   and  wowpost.exe

     It is not important, for example, for wnaspi32.dll to have matching version
     number with winaspi.dll. Disregard any such error message from aspichk.exe.
     Also disregard any error message from aspichk.exe regarding files not present.

2)   Windows 2000 and Windows NT4.0 Only:
     Command tagged queueing is enabled by default in v4.71; however, this is 
     functional only if your Host Bus Adapter (HBA) supports tagged queueing.
     Check with your HBA vendor for HBA capabilities.

3)   Windows 2000 Only:
     aspi32.sys (aspi2k.sy_ before install) remains a non-Plug-and-Play driver in Windows 2000.
     Once loaded, aspi32.sys will not unload. To get aspi32.sys unloaded, delete the file 
     \winnt\system32\drivers\aspi32.sys  and reboot PC.

4)   Previous versions of aspi32.sys for Windows 2000 and XP may not return the proper 
     Maximum Number of Targets (HA_MaxTargets) in reponse to Host Adapter Inquiry
     (HA_INQUIRY). This has been corrected.

III. GetASPI32Buffer Addendum
=========================================================================
FYI

If you have experienced a failure to allocate a buffer (GetASPI32Buffer),
you may need to do one or both of the following:

1)  increase the non-paged pool size on your PC (allocate more RAM to 
    non-paged pool),
2)  physically add more RAM to your PC.
3)  decrease the buffer size requested.

The first thing to do is to increase the non-paged pool size.

IV) How to increase the non-paged pool size ?
=============================================

 1) Run  regedt32.exe ( click  Start->Run and type regedt32 ),
 2) Edit HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SessionManager\MemoryManagement\NonPagedPoolSize
    This parameter is a REG_DWORD (32 bits). 

    NOTE : If it is set to 0x00, the default minimum portion of RAM is allocated to
           non-paged pool.

 3) Set this parameter to 0xffffffff (the maximum portion of RAM is allocated to
    non-paged pool.) Reboot the PC and try the application again.

    NOTE : If GetASPI32Buffer still fails; you may not have enough
    physical RAM in the PC, and you may need to physically
    install additional RAM.

If GetASPI32Buffer now works, then gradually decrease the non-paged pool size
( by specifying the amount of RAM allocated to non-paged pool ) to optimize.

Tips
-------------------------------------------------------------
Set the NonPagedPoolSize to 0x00100000 for 1 MegaBytes;
  0x00200000 for 2 MegaBytes;  etc.

See the Microsoft Developer Network (MSDN) article Q126402 (www.microsoft.com)
for more information regarding setting the non-paged pool size.

 
V. Windows XP Support
===========================================================

Contents:
-----------------------------------------------------------
install.bat     installation batch file
reg_xp.exe      registry modification utility
aspixp.sys      32-bit ASPI driver ( v 4.71.2 )
wnaspixp.dll    32-bit ASPI DLL    ( v 4.71.2 )
aspi64.sys      64-bit ASPI driver ( v 4.70.8 )
wnaspi64.dll    64-bit ASPI DLL    ( v 4.70.8 )


VI. Installation of ASPI
============================================================
1. Run INSTALL.BAT with the target operating system
   command line option specified:

   X86  ( for Windows 98/ME/NT/2000 )
   XP32 ( for Windows XP 32-bit     )
   XP64 ( for Windows XP 64-bit     )

   e.g. "INSTALL.BAT X86"

2. INSTALL.BAT will prompt you to specify which operating
   system to install for if you did not specify one in Step 1).

   a)  If you are installing for X86 systems for either
       Windows 98/ME/NT/2000 then ASPIINST.EXE will be invoked
       and the rest of the installation process will be carried
       out.
   b)  If you are installing for X86 or Itanium systems the
       batch file will invoke REG_XP.EXE to make the necessary
       registry entries and then copy the operating system
       specific files to the appropriate location. The operating
       system path is determined by the environment variable
       %windir%.

   For Win XP 32-bit:
    ASPIXP.SYS    will be copied to %windir%\system32\drivers\ASPI32.SYS
    WNASPIXP.DLL  will be copied to %windir%\system32\WNASPI32.DLL

   For Win XP 64-bit:
    ASPI64.SYS    will be copied to %windir%\system32\drivers\ASPI32.SYS
    WNASPI64.DLL  will be copied to %windir%\system32\WNASPI32.DLL

3. Reboot the system to enable the ASPI driver.

VII) Status Codes for ASPIINST.EXE
===========================================================
The use of the C programming convention, EXIT, has been
removed completely from the source. EXIT has some
restrictions which RETURN does not.

EXIT allows for only the low order byte of the status code
to be accessible to the calling process. The status value
is available to the operating system batch command ERRORLEVEL
but is represented by one of two constants EXIT_SUCCESS (0)
or EXIT_FAILURE (1).



