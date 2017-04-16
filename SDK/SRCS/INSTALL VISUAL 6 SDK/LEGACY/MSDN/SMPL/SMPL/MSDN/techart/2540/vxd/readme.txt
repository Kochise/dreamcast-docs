This VxD demonstrates new features in Chicago's system architecture.
In order to utilize it, you need to run the frontend application
16bit.exe under Chicago. The frontend will dynamically load the VxD and
communicate with it.

The sample was written by Ruediger Asche for the Microsoft Developer Network 
CD and is discussed in a technical article on that CD.

You will need to add a [callback] section to your win.ini file and
add the following two entries to it:

VxDLocation=<path and file name of callback.386>
DLLLocation=<path and file name of the DLL receiver.dll>

