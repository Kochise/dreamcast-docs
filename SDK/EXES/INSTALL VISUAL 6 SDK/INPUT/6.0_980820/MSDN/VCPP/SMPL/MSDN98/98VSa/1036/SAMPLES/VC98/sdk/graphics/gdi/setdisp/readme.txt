Dynamically Changing the Display Settings


The SetDisp sample creates a taskbar notification icon that you can use to
dynamically change your display settings. You can change resolution, color
depth, and refresh rate.

The core functions used are:
                                                              
   EnumDisplaySettings -- to get the display settings that are supported by
			  the video driver

   ChangeDisplaySettings -- to test and set the display  settings dynamically
			  and to update the registry with these settings

   Shell_NotifyIcon -- to create and maintain the tray icon   

   TrackPopupMenu   -- to implement the icon resolution context menu


Usage
------

To use the sample after building it with NMAKE, run SetDisp.EXE.  This will
display a dialog box with a menu of possible resolutions and a will create a
tray icon. If you right mouse click on the tray icon the dialog will get
the focus.  If you hide the dialog, you can bring it back up with this
technique.  If you left mouse click the tray icon, you will get the list of
available settings. To remove the tray icon, you must close the main dialog.

When SetDisp starts up, it enumerates all of the device modes that the current
or default display driver supports.  A #define controls filtering low frequency
refresh rates and limits the number of settings SetDisp reads in.  After
enumerating the settings, they are added to the menu. On NT, we can easily
obtain the current setting with ENUM_CURRENT_SETTINGS, so we set the check
mark on the menu and bold the setting that was in use when SetDisp was
started.

When you select a new setting, SetDisp test to be sure the DEVMODE selected
has one of the display attributes set.	All of the DEVMODEs used in SetDisp
should have these set since they came from the system.	It then tests to see if
the system believes the DEVMODE is valid. If the change requires a system
reboot, a dialog notifies the user that this is not implemented. If the screen
change can be dynamic, a resolution changed is attempted.  The user is prompted
to see if the new resolution is acceptable.  This is important since the driver
may support a setting but the monitor is not able to display it correctly.  To
ensure the user does not get stuck with a bad setting, a timer is used to
cancel the change if the user does not respond. The default time out is 10
seconds and is controlled by a #define.	If the new setting is accepted, the
registry is updated.  All of this is done using ChangeDisplaySettings.


Notes
-----

On Windows 95, you cannot use EnumDisplaySettings to get the current settings.
In this sample, this causes the check mark to not be displayed and the
current setting to not be made bold. Also on Windows 95, color depth changes 
require a reboot.

Of the possible returns from ChangeDisplaySettings, only success and a reboot
required are currently handled.	For success, a dynamic resolution change is
done.  For a reboot required change, a message is displayed indicating that
the sample does not support a reboot.

If your driver has many resolutions, the menu may not fit on some resolutions.
This could be resolved with the use of sub menus for different settings
such as color depth or frequencies.
