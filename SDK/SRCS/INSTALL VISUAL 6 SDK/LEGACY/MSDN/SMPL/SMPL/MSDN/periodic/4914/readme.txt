**************************************************************
*  SCRIB1/2/3 Copyright 1996 Microsoft Systems Journal.      *
*  If this program works, it was written by Paul DiLascia.   *
*  If not, I don't know who wrote it.                        *
**************************************************************

SCRIB1, SCRIB2, and SCRIB3 are modified versions of the MFC Scribble
program that show different ways of implementing a modified indicator
in the title bar of an MFC app

-SCRIB1 implements the indicator in the document by overriding
 CDocument::SetModifiedFlag. 

-SCRIB2 implements the indicator in the frame by handling
 WM_IDLEUPDATEUI.

-SCRIB3 Shows a generalized mechanism for any title bar indicator
 using ON_UPDATE_COMMAND_UI handlers. 

Have fun!
Paul DiLascia
