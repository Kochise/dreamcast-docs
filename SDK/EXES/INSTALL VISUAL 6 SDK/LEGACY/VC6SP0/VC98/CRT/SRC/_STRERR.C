/***
*_strerr.c - routine for indexing into system error list
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Returns system error message index by errno; conforms to the
*       XENIX standard, much compatibility with 1983 uniforum draft standard.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>
#include <errmsg.h>
#include <syserr.h>
#include <string.h>
#include <malloc.h>
#include <mtdll.h>
#include <dbgint.h>

/* Max length of message = user_string(94)+system_string+2 */
/* [NOTE: The mthread error message buffer is shared by both strerror
   and _strerror so must be the max length of both. */
#define _ERRMSGLEN_ 94+_SYS_MSGMAX+2

/***
*char *_strerror(message) - get system error message
*
*Purpose:
*       builds an error message consisting of the users error message
*       (the message parameter), followed by ": ", followed by the system
*       error message (index through errno), followed by a newline.  If
*       message is NULL or a null string, returns a pointer to just
*       the system error message.
*
*Entry:
*       char *message - user's message to prefix system error message
*
*Exit:
*       returns pointer to static memory containing error message.
*       returns NULL if malloc() fails in multi-thread versions.
*
*Exceptions:
*
*******************************************************************************/

char * __cdecl _strerror (
        REG1 const char *message
        )
{
#ifdef _MT

        _ptiddata ptd = _getptd();
        char *bldmsg;

#else  /* _MT */

        static char bldmsg[_ERRMSGLEN_];

#endif  /* _MT */


#ifdef _MT

        /* Use per thread buffer area (malloc space, if necessary) */
        /* [NOTE: This buffer is shared between _strerror and streror.] */

        if ( (ptd->_errmsg == NULL) && ((ptd->_errmsg =
            _malloc_crt(_ERRMSGLEN_)) == NULL) )
                    return(NULL);
        bldmsg = ptd->_errmsg;

#endif  /* _MT */

        /* Build the error message */

        bldmsg[0] = '\0';

        if (message && *message) {
                strcat( bldmsg, message );
                strcat( bldmsg, ": " );
        }

        strcat( bldmsg, _sys_err_msg( errno ) );

        return( strcat( bldmsg, "\n" ) );
}
