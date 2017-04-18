/***
*getenv.c - get the value of an environment variable
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines getenv() - searches the environment for a string variable
*       and returns the value of it.
*
*******************************************************************************/

#ifdef _WIN32

#include <cruntime.h>
#include <internal.h>
#include <mtdll.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#ifndef CRTDLL

/*
 * Flag checked by getenv() and _putenv() to determine if the environment has
 * been initialized.
 */
extern int __env_initialized;

#endif  /* CRTDLL */

/***
*char *getenv(option) - search environment for a string
*
*Purpose:
*       searches the environment for a string of the form "option=value",
*       if found, return value, otherwise NULL.
*
*Entry:
*       const char *option - variable to search for in environment
*
*Exit:
*       returns the value part of the environment string if found,
*       otherwise NULL
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT


#ifdef WPRFLAG
wchar_t * __cdecl _wgetenv (
#else  /* WPRFLAG */
char * __cdecl getenv (
#endif  /* WPRFLAG */
        const _TSCHAR *option
        )
{
        _TSCHAR *retval;

        _mlock(_ENV_LOCK);

#ifdef WPRFLAG
        retval = _wgetenv_lk(option);
#else  /* WPRFLAG */
        retval = _getenv_lk(option);
#endif  /* WPRFLAG */

        _munlock(_ENV_LOCK);

        return(retval);

}


#ifdef WPRFLAG
wchar_t * __cdecl _wgetenv_lk (
#else  /* WPRFLAG */
char * __cdecl _getenv_lk (
#endif  /* WPRFLAG */
        const _TSCHAR *option
        )

#else  /* _MT */

#ifdef WPRFLAG
wchar_t * __cdecl _wgetenv (
#else  /* WPRFLAG */
char * __cdecl getenv (
#endif  /* WPRFLAG */
        const _TSCHAR *option
        )

#endif  /* _MT */

{
        _TSCHAR **search = _tenviron;
        unsigned int length;

#ifndef CRTDLL
        /*
         * Make sure the environment is initialized.
         */
        if ( !__env_initialized )
            return NULL;
#endif  /* CRTDLL */

        /*
         * At startup, we obtain the 'native' flavor of environment strings
         * from the OS. So a "main" program has _environ and a "wmain" has
         * _wenviron loaded at startup. Only when the user gets or puts the
         * 'other' flavor do we convert it.
         */


#ifdef WPRFLAG
        if (!search && _environ)
        {
            /* don't have requested type, but other exists, so convert it */
            if (__mbtow_environ() != 0)
                return NULL;

            /* now requested type exists */
            search = _wenviron;
        }
#else  /* WPRFLAG */
        if (!search && _wenviron)
        {
            /* don't have requested type, but other exists, so convert it */
            if (__wtomb_environ() != 0)
                return NULL;

            /* now requested type exists */
            search = _environ;
        }
#endif  /* WPRFLAG */


        if (search && option)
        {
                length = _tcslen(option);

                /*
                ** Make sure `*search' is long enough to be a candidate
                ** (We must NOT index past the '\0' at the end of `*search'!)
                ** and that it has an equal sign (`=') in the correct spot.
                ** If both of these requirements are met, compare the strings.
                */
                while (*search)
                {
                        if (_tcslen(*search) > length && (*(*search + length)
                        == _T('=')) && (_tcsnicoll(*search, option, length) == 0)) {
                                return(*search + length + 1);
                        }

                        search++;
                }
        }

        return(NULL);
}

#else  /* _WIN32 */


#include <cruntime.h>
#include <stdlib.h>
#include <string.h>
#include <mtdll.h>
#include <dbgint.h>

/***
*char *getenv(option) - search environment for a string
*
*Purpose:
*       searches the environment for a string of the form "option=value",
*       if found, return value, otherwise NULL.
*
*Entry:
*       const char *option - variable to search for in environment
*
*Exit:
*       returns the value part of the environment string if found,
*       otherwise NULL
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT


char * __cdecl getenv (
        const char *option
        )
{
        char *retval;

        _mlock(_ENV_LOCK);

        retval = _getenv_lk(option);

        _munlock(_ENV_LOCK);

        return(retval);

}


char * __cdecl _getenv_lk (
        const char *option
        )

#else  /* _MT */

char * __cdecl getenv (
        const char *option
        )

#endif  /* _MT */
{
        char **search = _environ;
        unsigned int length;

        if (search && option)
        {

                length = strlen(option);

                /*
                ** Make sure `*search' is long enough to be a candidate
                ** (We must NOT index past the '\0' at the end of `*search'!)
                ** and that it has an equal sign (`=') in the correct spot.
                ** If both of these requirements are met, compare the strings.
                */
                while (*search)
                {
                        if (strlen(*search) > length && (*(*search + length)
                        == '=') && (_strnicmp(*search, option, length) == 0)) {
                                return(*search + length + 1);
                        }

                        search++;
                }
        }

        return(NULL);
}


/***
* void _envinit(void) - initialization routine for the env table  This code
*                                                               is here rather than crt0 so that the env malloc is
*                                                               only done if absolutely necessary.
*
*Purpose:
*       If the user has used getenv() then copy the MPW environment
*
*Entry:
*       None.
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

#include <mpw.h>
#include <fltintrn.h>

extern MPWBLOCK *_pMPWBlock;

void __cdecl _envinit (
        void
        )
{

        if (_pMPWBlock != NULL && _pMPWBlock->env != NULL)
                {
                char **ppch;
                char **ppchNew;
                char *pch;
                int cb;


                /* Calculate and allocate a block for env pointers */
                for (ppch = _pMPWBlock->env; *ppch != NULL; ppch++);
                _environ = _malloc_crt((char *)(ppch + 1) - (char *)_pMPWBlock->env);

                /* Copy the env strings */
                ppchNew = _environ;
                for (ppch = _pMPWBlock->env; *ppch != NULL; ppch++)
                        {
                        cb = strlen(*ppch) + 1;
                        *ppchNew = _malloc_crt(cb + strlen(*ppch + cb) + 1);
                        pch = *ppchNew++;
                        strcpy(pch,*ppch);
                        pch += cb - 1;
                        *pch++ = '=';
                        strcpy(pch, *ppch + cb);
                        }
                *ppchNew = NULL;
                }

}

/* define the entry in initializer table */

#pragma data_seg(".CRT$XIC")

static PFV __penvinit = _envinit;

#pragma data_seg()

#endif  /* _WIN32 */

