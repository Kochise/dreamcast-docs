Microsoft(R) ActiveX(TM) component that schedules a Broadcast Architecture show reminder

This Readme file contains the following sections:
* Summary		Briefly describes the sample
* More Information	Details how to compile and run the sample
* About SchSamp		Describes the sample in more detail.
* Using SchSamp		Explains how to use SchSamp from a Web page.

For more information about how to write applications that schedule
show reminders, see Scheduling Show Reminders in the 
Broadcast Architecture Programmer's Reference.

SUMMARY
=========
The SchSamp sample, SchSamp.dll, is an ActiveX component that 
schedules a show reminder using the IScheduledItems interface 
available from Television System Services, Tssadmin.dll. TV Viewer 
is used to display the reminder dialog box when the reminder runs.

SchSamp was developed using the Microsoft(R) Visual Basic(R) 
programming system, version 5.0, including Microsoft(R) 
Visual Basic(R) Scripting Edition (VBScript).

MORE INFORMATION
================
SchSamp must be compiled and run on a computer running 
the Microsoft(R) Windows(R) 98 operating system with 
the TV Viewer components installed. Running Windows 98 with 
TV Viewer installs and registers Television System Services 
and TV Viewer, both of which are required for SchSamp to run.

The following information describes the SchSamp sample.

To Compile SchSamp
-------------------
Open the SchSamp project file, SchSamp.vdp, in Visual Basic 5.0. 
On the File menu, click Make SchSamp.dll.

To compile the component into a .cab file for distribution 
on the Internet, use the Application Setup Wizard provided with 
Visual Basic 5.0. Click Create Internet Download Setup.

This control is unsigned. If you wish to distribute a version of 
SchSamp on the Web, you should sign the component. For instructions on 
how to sign a .cab file, see the Internet Client Software Development 
Kit (SDK).

To Set Up the Programming Environment
----------------------------------------------------
First, create a new ActiveX DLL project. Set the class to global, multiuse. 
Then set a project reference to the Microsoft Television Services, Tssadmin.dll. 
Doing this gives you access to the TelevisionServices, TaskTrigger, and 
ScheduledItems objects. If you are unable to locate Microsoft Television Services 
in References, check that the optional TV Viewer component of Windows 98 
is installed on your computer.
You must also set a reference to the Microsoft Data Access Objects (DAO) 
version 3.5 object library. Doing this enables your application to create 
the DAO workspace required by the ScheduledItems object.

To Run SchSamp
---------------
The SchSamp sample includes a version of the component that has already
been compiled into a .cab file for delivery through a Web page. The .cab 
file has not been signed, and thus in order to run the sample you must set 
security in Microsoft(R) Internet Explorer version 4.0 to allow unsigned 
controls to run.

To do this, on the View menu click Internet Options. Click the 
Security tab. Set Security settings for the appropriate zone. If you plan 
to run SchSamp from your machine, this should be the Local Intranet zone.

Once the security is properly set, open SchSamp.html with Internet Explorer 4.0.
The SchSamp component automatically downloads and installs on your computer. 
To run the script that sets the show reminder, click Schedule Reminder.

Note:  You cannot set a reminder for a show that has already occurred. 
The HTML Web currently is scripted to set a reminder for the show "Maid to Order"
on 8/5/97 at 3 P.M. If the current date is after 8/5/97, the sample does not run. 
To correct this, edit the following lines of the HTML file:

SchSamp.Episode = "Maid to Order"
SchSamp.Network = ""
SchSamp.Duration = "120"
SchSamp.ShowTime = "8/5/97 3:00:00 PM"

Change the preceding lines to reflect a future episode. 

For best results, choose an episode from the 
TV Viewer Program Guide. Doing so enables SchSamp to match the episode in 
the Guide database and obtain description and tuning information.

Note: Because SchSamp uses the IScheduledItems interface, you cannot use the 
Search page of TV Viewer to view a sample set with SchSamp. To test whether 
the reminder was set, follow the instructions detailed in SchSamp.htm.

SchSamp Files
--------------
SchSamp.html is an HTML/VBScript file uses SchSamp to set a show reminder.

SchSamp.cab contains a compiled version of SchSamp.            

SchSamp.vbp is the Visual Basic project file.

SchSamp.cls contains the Visual Basic class module

ABOUT SCHSAMP
===============
SchSamp is an ActiveX component that schedules a TV Viewer 
reminder for a broadcast show. At a specified amount of time before 
the show starts, the reminder runs, causing TV Viewer to display 
a dialog box to the user. This dialog box states that the show is about to start 
and offers the user the option to tune to that channel. This component 
can be used, for example, on an television enhancement page so 
users can schedule a reminder for next week's episode. 

Note: Reminders that are set by any means other than 
ITVViewer::SetReminder cannot be viewed from the Search page of 
TV Viewer when a user selects MyReminders from the Categories list. 
Neither does a reminder icon appear in that program's details list. 
However, TV Viewer still presents a reminder dialog box when 
the reminder runs.

USING SCHSAMP
==============
Because SchSamp is implemented as an ActiveX component, it can be called 
from a variety of programming environments, such as VBScript or 
Microsoft(R) JScript(TM) development software on a Web page, Visual Basic, 
Java, or C++. The code examples in the following topics use Web-based 
VBScript to call SchSamp.

Note: The SchSamp component is not signed. In order to run the sample, 
you must set security in your Web browser to allow unsigned controls to run. 
For more information on how to do this, see the Readme.txt file installed 
with SchSamp. For information on how to sign a component for Internet 
download, see the Internet Client SDK.

Note: The following topics describe how to create an instance of SchSamp, 
pass episode data, and set a show reminder for the specified episode.

Inserting SchSamp in a Web Page
------------------------------------------------------
You can call the SchSamp component from a Web page. To create an instance 
of the component, insert the following object tag into the HTML file:

<OBJECT ID="MySchSamp"
CLASSID="CLSID:BE521C45-08DA-11D1-98AE-080009DC95C5"
CODEBASE="SchSamp.CAB#version=1,0,0,0">
</OBJECT>
 
Set the ID parameter to specify a name for this instance of the control. In the 
preceding example, it is set to MySchSamp. The CLASSID parameter lists 
the unique identifier for the SchSamp class and must appear exactly as 
above. The CODEBASE parameter points to the .cab file that contains the 
compiled SchSamp component and its supporting files. 

Specifying Episode Data
-------------------------------
The SchSamp component contains the following properties. 

Property		Data type	Description
-----------		-------------	----------------
Episode		String		Title of the episode.
Network		String		If applicable, the network on which the episode appears.
Duration		String		Length of the episode, in minutes.
ShowTime	String		Time and date that the episode starts.
PreTime		Long		The number of minutes early that the reminder should run.

These properties store data about the episode for which you want to set a reminder. 
You must set values for them before you call SchSamp.SetReminder to schedule 
the show reminder. 

The following example uses VBScript in a Web page to set values for the 
SchSamp properties. 

<SCRIPT LANGUAGE = VBScript>
Sub SetIt_OnClick
      'set the show's properties
      SchSamp.Episode = "Maid to Order"
      SchSamp.Network = ""
      SchSamp.Duration = "120"
      SchSamp.ShowTime = "8/5/97 3:00:00 PM"
      SchSamp.PreTime = 5

      'Schedule the reminder
      SchSamp.SetReminder
End Sub
</SCRIPT>
 
Note that you cannot set a reminder for a show that has already occurred. The HTML 
file installed with SchSamp is scripted to set a reminder for the show "Maid to Order" 
on 8/5/97 at 3 P.M. If the current date is after 8/5/97, the sample does not run. 
To correct this, edit the preceding lines to reflect a future episode:

For best results, choose an episode from the TV Viewer program guide. Doing so 
enables SchSamp to match the episode in the Guide database and obtain description 
and tuning information.

Scheduling the Show Reminder
---------------------------------------
Once the properties of SchSamp are set as described in the Broadcast Architecture 
Programmer's Reference topic Specifying Episode Data, call the SchSamp.SetReminder 
method to create the show reminder. This is illustrated in the following example.

<SCRIPT LANGUAGE = VBScript>
  'Schedule the reminder
   SchSamp.SetReminder
</SCRIPT>
 


