/***
*umask.c - set file permission mask
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _umask() - sets file permission mask of current process*
*       affecting files created by creat, open, or sopen.
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <io.h>

/***
*int _umask(mode) - set the file mode mask
*
*Purpose:
*       Sets the file-permission mask of the current process* which
*       modifies the permission setting of new files created by creat,
*       open, or sopen.
*
*Entry:
*       int mode - new file permission mask
*                  may contain S_IWRITE, S_IREAD, S_IWRITE | S_IREAD.
*                  The S_IREAD bit has no effect under Win32
*
*Exit:
*       returns the previous setting of the file permission mask.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _umask (
        int mode
        )
{
        register int oldmode;           /* old umask value */

        mode &= 0x180;                  /* only user read/write permitted */
        oldmode = _umaskval;            /* remember old value */
        _umaskval = mode;               /* set new value */
        return oldmode;                 /* return old value */
}
