AUTOBUILD:  Performs a build of one or more workspaces at a specified time and
		date.

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.


This sample shows how to create and use add-ins. It demonstrates working
with various parts of the Developer Studio object model, placing multiple
commands into an add-in, and invoking commands from a command line.

Note: For the "Send Email" function to work, you either have to have a non-password email
account, or you need to be logged into the email account at the time AutoBuild runs.

Running the Sample

Windows NT
1.  Place the AutoBld.dll in the AddIns folder under "\Microsoft Visual Studio\Common\MSDev98"
		so it can be located by Developers Studio when it launches.
2.  Start Developer Studio, and on the Tools menu, click Customize.
3.  Choose the Add-ins and Macro Files tab, click the Browse button,
	and load the AutoBld.dll file.
	Make sure Auto Build is checked to be loaded.
	Note:  AutoBuild creates a small toolbar that is visible when you
	close the Customize dialog box.
4.  Click the Configure button on the newly created toolbar, and set your
	preferences in the AutoBuild Configuration dialog box.
5.  Exit Developers Studio to save this configuration.
6.  From Control Panel, open the Services dialog box. Find Scheduling Agent
	in the list box, and make sure its Status column indicates 'Started'
	and its Startup column indicates 'Automatic'.
	Note: If the Scheduling Agent's Status is not set to 'Started',
highlight the Scheduling Agent and click the Start button. If its
	Startup is not set to 'Automatic', click the Startup button and
	select 'Automatic' in the Startup Type field on the Service dialog
	box.
7.  From a command prompt, use the 'at' utility to set the time and date you
	wish to build your workspaces. When giving the 'at' utility a command
	line to execute, enter the following line (making sure that msdev.exe
	is on your path):

	Example:

	at 06:00 /interactive msdev.exe /EX AutoBuildTest

	This will launch Developer Studio and execute the AutoBuild command at 06:00am,
	which starts the build of your workspaces.

Windows 95 with Microsoft PLUS!
1.  Place the AutoBld.dll in the AddIns folder under Microsoft Visual Studio\Common\MSDev98
		so it can be located by Developers Studio.
2.  Start Developer Studio, and on the Tools menu, click Customize.
3.  Choose the Add-ins and Macro Files tab, click the Browse button,
	and load the AutoBld.dll file.
	Make sure Auto Build is checked to be loaded.
	Note:  AutoBuild creates a small toolbar that is visible when you
	close the Customize dialog box.
4.  Click the Configure button on the newly created toolbar, and set your
	preferences in the AutoBuild Configuration dialog box.
5.  Exit Developers Studio to save this configuration.
6.  Click the Scheduling Agent on the system tray, and add the following line
	to the list of tasks to perform:

	msdev /EX AutoBuildTest

	Note: The Scheduling Agent icon appears next to the clock.  This is
	visible in the system tray in the lower-right corner of your screen
	(on the Start taskbar).  This is only visible if you have Microsoft
	PLUS! installed.
7.  Set the time and how often you wish to execute the build.
