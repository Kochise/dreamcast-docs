Console I/O Combined with GUI I/O


SUMMARY
=======

The ConGUI sample demonstrates how a standard console application can take 
advantage of some of the graphical capabilities of Windows NT.

Disclaimer:

This sample application illustrates a method by which a console application 
can utilize some (but not all) of the graphical user interface (GUI) 
capabilities of the Win32 API. It was not the original design intention of 
the Console layer of Windows NT to allow it to interact in this manner 
with the graphical API, and because of this, it is possible to run into 
problems if you try to accomplish too much.

Please use restraint in your usage of the graphical Win32 API in your 
console application. If your needs go beyond the simple methods 
illustrated here, you should probably consider designing your application 
as a full GUI application.

MORE INFORMATION
================

There are many applications that have nothing to gain by implementing full-
fledged GUI with title bars, menus, scrollable client area, and so forth. 
However, a console application can take advantage of GUI features. 

Take the example of a compiler. A compiler has no need for menus, button 
bars, or many of the other UI aspects of a standard Windows application. 
However, you may want your compiler to provide on-line assistance with the 
command-line switches that the compiler supports.

ConGUI illustrates the usage of a '/dialog' parameter, which brings up a 
dialog box that assists the user in selecting parameters for the command 
line. To provide a little more information about some of those switches,
allow the user to access a Windows help file. ConGUI shows how easy it is 
for a console application to make standard WinHelp calls to access the 
Windows help engine.

In addition, ConGUI shows how it is possible for a console application to 
figure out how it was launched. It can be useful for a text application to 
know that it was being launched into its own window, because when it closes, 
the window into which it has written all of its output is closed as well. 

Try the following methods of executing ConGUI, and notice how it behaves:

  - Double-click on the CONGUI.EXE from the File Manager or Windows 
    Explorer. 

  - Add ConGUI to a group in the Program Manager or create a short-cut, and 
    double-click on the icon.

  - From a command prompt, type: 

      CONGUI

  - From a command prompt, type: 
  
      START CONGUI

  - From a command prompt, type: 

      CONGUI > TEMP.TXT

