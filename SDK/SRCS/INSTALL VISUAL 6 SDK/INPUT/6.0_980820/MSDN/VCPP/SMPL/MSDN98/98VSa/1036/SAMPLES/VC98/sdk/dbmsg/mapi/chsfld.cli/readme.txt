MAPI Choose Folder Sample

Copyright (c) 1886-1996 Microsoft Corporation. All Rights Reserved.


This samples illustrates implementing a MAPI Container hierarchy viewer.
It uses standard WIN32 Tree View Control to display folder hierarchy of
a message store and to allow a user to choose a particular folder.
Chsfld32.dll exports a single entry point  HrPickFolder. Please see
chsfld.h located in common directory for the exact description of
arguments and return values.

The use of HrPickFolder is straightforward: just pass in all the required
parameters and, assuming that everything goes OK, get back pointers to
IMAPIFolder interface of the folder chosen by the user and a pointer to
IMsgStore interface of the message store that contains the folder.
There are to optional parameters. If you use them (meaning they are not
zeroes), the function will save the expand/collapse state of the dialog
at the moment the user pressed "OK". If you pass this parameter back next
time you call HrPickFolder, the dialog will restore the saved state. See
route.cli and simple.frm samples for the example on how to use the function.

If you want to use the function as is, in a separate DLL, all you need to
do is to link with chsfld32.dll either statically or dynamically and call
the function. To reuse the source code, you will have to modify it a bit.
You have to make sure that the HINSTANCE parameter that you pass to
CChsFldDlg constructor in function HrPickFolder (file chsfld.cpp) is the
handle of the executable module that contains the resources used by the
class (the dialog and the icons).
