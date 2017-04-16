**************************************************************
*  SCBMOD1/2/3 Copyright 1996 Microsoft Systems Journal.     *
*  If this program works, it was written by Paul DiLascia.   *
*  If not, I don't know who wrote it.                        *
**************************************************************

SCBMOD1, SCBMOD2, and SCBMOD3 are modified versions of the MFC Scribble
program that show different ways of implementing a modified indicator
in the title bar of an MFC app. Changes are flagged "**MOD**".

-SCBMOD1 implements the indicator in the document by overriding
 CDocument::SetModifiedFlag. 

-SCBMOD2 implements the indicator in the frame by handling
 WM_IDLEUPDATEUI.

-SCBMOD3 Shows a generalized mechanism for any title bar indicator
 using ON_UPDATE_COMMAND_UI handlers. 

Have fun!
Paul DiLascia
