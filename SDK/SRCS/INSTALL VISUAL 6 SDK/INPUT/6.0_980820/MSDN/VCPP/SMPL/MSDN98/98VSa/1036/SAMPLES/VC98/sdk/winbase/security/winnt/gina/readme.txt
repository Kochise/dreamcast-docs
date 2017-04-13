Graphical Identification and Authentication DLL (GINA)


The GINA sample demonstrates the Gina-related functions.

To install the Gina DLL, copy it into %systemroot%\SYSTEM32, add
a registry value of type REG_SZ named GinaDLL under the key
\HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Winlogon,
and reboot the machine.

WARNING! - It is possible to make your machine unusable if you install a
replacement Gina and it fails. To avoid this situation, be sure that you
have a method of accessing the %systemroot%\SYSTEM32 directory independent
of the Windows NT installation you are testing on.  

If the Gina sample malfunctions, and you are not able to log on to fix
the problem, you can recover by doing one of the following:

* If the test machine is on the network and you have an account on
  another machine with Administrative privileges on the test machine,
  open the test machine registry remotely with regedt32 and delete
  the GinaDLL value.

* If the test machine is on the network, and %systemroot%\SYSTEM32 is
  available on a network share for that machine (e.g. \\<name>\c$),
  rename GINA.DLL to something else with a command like

     ren \\<name>\c$\winnt351\system32\gina.dll gina.sdk

  reboot the test machine, and delete the GinaDLL value from the registry.

* If the test machine will dual boot to another version of Windows NT
  or another operating system capable of accessing %systemroot%\system32,
  boot to that operating system, delete %systemroot%\system32\GINA.DLL,
  reboot, and delete the GinaDLL value from the registry.

For more information see GINA.HLP.
