10/15/97
notes for
Sample files for A Web Application for Handheld Transaction Processing Client
-------------------------------------------------------------------------------------------------
Sample version 0.5

Unzip with -d parameter to place files in appropriate folders
The wincehtm folder contains sample HTML files 
The handtech folder contains files for the server application

This sample is a preliminary ASP web application that is designed for handheld WindowsCE clients. The full Helpdesk sample application (including database, COM API, e-mail, voice, and other clients) will be available on MSDN online in February 1998.


The sample files included here can be used in two ways:
-------------------------------------------------------------------------------------------------

1. Install and view HTML files on a WindowsCE computer in order to sample the type of HTML that the server application generates.

2. Install the ASP application on a computer running WindowsNT Server 4.0 and Microsoft Internet Information Server 3.0 with Microsoft Active Server Pages 1.1 in order to try the server application. This preliminary application simulates the data and transactions that will be possible when all of the components are provided with the complete application.


To view HTML files on a WindowsCE computer
-------------------------------------------------------------------------------------------------
To view these files, copy the contents of the wincehtm folder to the WindowsCE machine with the Handheld PC Explorer and execute reqs.htm.


To install the ASP application on a server
-------------------------------------------------------------------------------------------------
1. Create a virtual directory (helpdesk/handtech) using the Internet Service Manager and copy the files from the handtech folder to this directory.

2. Register handtech.dll on the server with regsvr32.exe.
 Use regsvr32 handtech.dll to register the component classes.
 Use regsvr32/u handtech.dll to unregister.

