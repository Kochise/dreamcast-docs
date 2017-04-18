/***
*putenv.c - put an environment variable into the environment
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _putenv() - adds a new variable to environment; does not
*       change global environment, only the process' environment.
*
*******************************************************************************/

#ifdef _WIN32


#include <windows.h>
#include <cruntime.h>
#include <internal.h>
#include <mtdll.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <dbgint.h>

#ifndef CRTDLL

/*
 * Flag checked by getenv() and _putenv() to determine if the environment has
 * been initialized.
 */
extern int __env_initialized;

#endif  /* CRTDLL */

/***
*int _putenv(option) - add/replace/remove variable in environment
*
*Purpose:
*       option should be of the form "option=value".  If a string with the
*       given option part already exists, it is replaced with the given
*       string; otherwise the given string is added to the environment.
*       If the string is of the form "option=", then the string is
*       removed from the environment, if it exists.  If the string has
*       no equals sign, error is returned.
*
*Entry:
*       char *option - option string to set in the environment list.
*           should be of the form "option=value".
*
*Exit:
*       returns 0 if OK, -1 if fails.
*
*Exceptions:
*
*Warning:
*       This code will not work if variables are removed from the
*       environment by deleting them from environ[].  Use _putenv("option=")
*       to remove a variable.
*
*******************************************************************************/

#ifdef _MT

#ifdef WPRFLAG
int __cdecl _wputenv (
#else  /* WPRFLAG */
int __cdecl _putenv (
#endif  /* WPRFLAG */
        const _TSCHAR *option
        )
{
        int retval;

        _mlock(_ENV_LOCK);

#ifdef WPRFLAG
        retval = _wputenv_lk(option);
#else  /* WPRFLAG */
        retval = _putenv_lk(option);
#endif  /* WPRFLAG */

        _munlock(_ENV_LOCK);

        return retval;
}

#ifdef WPRFLAG
int __cdecl _wputenv_lk (
#else  /* WPRFLAG */
int __cdecl _putenv_lk (
#endif  /* WPRFLAG */
        const _TSCHAR *option
        )

#else  /* _MT */

#ifdef WPRFLAG
int __cdecl _wputenv (
#else  /* WPRFLAG */
int __cdecl _putenv (
#endif  /* WPRFLAG */
        const _TSCHAR *option
        )

#endif  /* _MT */

{
        int size;
        _TSCHAR * newoption;

#ifndef CRTDLL
        /*
         * Make sure the environment is initialized.
         */
        if  ( !__env_initialized )
            return -1;
#endif  /* CRTDLL */

        /*
         * At startup, we obtain the 'native' flavor of environment strings
         * from the OS. So a "main" program has _environ and a "wmain" has
         * _wenviron loaded at startup. Only when the user gets or puts the
         * 'other' flavor do we convert it.
         */

        /* copy the new environent string */
        if ( (newoption = (_TSCHAR *)_malloc_crt((_tcslen(option)+1) *
             sizeof(_TSCHAR))) == NULL )
            return -1;

        _tcscpy(newoption, option);

#ifdef WPRFLAG
        if (__crtwsetenv(newoption, 1) != 0)
            return -1;

        /* If other environment type exists, set it */
        if (_environ)
        {
            char *mboption;

            /* find out how much space is needed */
            if ( (size = WideCharToMultiByte(CP_OEMCP, 0, option, -1, NULL,
                 0, NULL, NULL)) == 0 )
                return -1;

            /* allocate space for variable */
            if ((mboption = (char *) _malloc_crt(size * sizeof(char))) == NULL)
                return -1;

            /* convert it */
            if ( WideCharToMultiByte(CP_OEMCP, 0, option, -1, mboption, size,
                 NULL, NULL) == 0 )
                return -1;

            /* set it - this is not primary call, so set primary == 0 */
            if (__crtsetenv(mboption, 0) != 0)
                return -1;
        }
#else  /* WPRFLAG */
        /* Set requested environment type, primary call */
        if (__crtsetenv(newoption, 1) != 0)
            return -1;

        /* If other environment type exists, set it */
        if (_wenviron)
        {
            wchar_t *woption;

            /* find out how much space is needed */
            if ( (size = MultiByteToWideChar(CP_OEMCP, 0, option, -1, NULL, 0))
                 == 0)
                return -1;

            /* allocate space for variable */
            if ( (woption = (wchar_t *) _malloc_crt(size * sizeof(wchar_t)))
                 == NULL )
                return -1;

            /* convert it */
            if ( MultiByteToWideChar(CP_OEMCP, 0, option, -1, woption, size)
                 == 0 )
                return -1;

            /* set it - this is not primary call, so set primary == 0 */
            if (__crtwsetenv(woption, 0) != 0)
                return -1;
        }
#endif  /* WPRFLAG */

        return 0;
}



/***
*int findenv(name, len) - [STATIC]
*
*Purpose:
*       Scan for the given string within the environment
*
*Entry:
*
*Exit:
*       Returns the offset in "environ[]" of the given variable
*       Returns the negative of the length of environ[] if not found.
*       Returns 0 if the environment is empty.
*
*       [NOTE: That a 0 return can mean that the environment is empty
*       or that the string was found as the first entry in the array.]
*
*Exceptions:
*
*******************************************************************************/

#ifdef WPRFLAG
static int __cdecl wfindenv (
#else  /* WPRFLAG */
static int __cdecl findenv (
#endif  /* WPRFLAG */
        const _TSCHAR *name,
        int len
        )
{
        _TSCHAR **env;

        for ( env = _tenviron ; *env != NULL ; env++ ) {
            /*
             * See if first len characters match, up to case
             */
            if ( _tcsnicoll(name, *env, len) == 0 )
                /*
                 * the next character of the environment string must
                 * be an '=' or a '\0'
                 */
                if ( (*env)[len] == _T('=') || (*env)[len] == _T('\0') )
                    return(env - _tenviron);
//
// We cannot break here since findenv must report the total number of strings.
//              else
//                  break;
        }

        return(-(env - _tenviron));
}


#else  /* _WIN32 */


#include <cruntime.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <internal.h>
#include <mtdll.h>
#include <memory.h>
#include <dbgint.h>

static int __cdecl findenv(const char *name, int len);

/***
*int _putenv(option) - add/replace/remove variable in environment
*
*Purpose:
*       option should be of the form "option=value".  If a string with the
*       given option part already exists, it is replaced with the given
*       string; otherwise the given string is added to the environment.
*       If the string is of the form "option=", then the string is
*       removed from the environment, if it exists.  If the string has
*       no equals sign, error is returned.
*
*Entry:
*       char *option - option string to set in the environment list.
*           should be of the form "option=value".
*
*Exit:
*       returns 0 if OK, -1 if fails.
*
*Exceptions:
*
*Warning:
*       This code will not work if variables are removed from the
*       environment by deleting them from environ[].  Use _putenv("option=")
*       to remove a variable.
*
*******************************************************************************/

#ifdef _MT

int __cdecl _putenv (
        const char *option
        )
{
        int retval;

        _mlock(_ENV_LOCK);

        retval = _putenv_lk(option);

        _munlock(_ENV_LOCK);

        return retval;
}

int __cdecl _putenv_lk (
        const char *option
        )

#else  /* _MT */

int __cdecl _putenv (
        const char *option
        )

#endif  /* _MT */

{
        char **env;
        const char *equal;
        int ix;
        int remove;     /* 1 means remove string from environment */

        /* check that the option string is valid and find the equal sign
         */
        if ( (option == NULL) || ((equal = strchr(option, '=')) == NULL) )
            return(-1);

        /* check for the special case of '=' being the very first character
         * of option. though the use of '=' in an environment variable name
         * is documented as being illegal, the 'current directory' strings
         * all look like this:
         *
         *  =<Drive Letter>:=<Drive Letter><fully qualified path>
         *
         * handle this by setting the equal pointer to point to the second
         * '=' if it exists. Otherwise, handle as before.
         */
        if ( option == equal )
            if ( (equal = strchr(option + 1, '=')) == NULL )
                equal = option;

        /* if the character following '=' is null, we are removing the
         * the environment variable. Otherwise, we are adding or updating
         * an environment variable.
         */
        remove = (*(equal + 1) == '\0');

        /* see if _environ array exists */
        if (_environ == NULL) {
            if ( remove )
                return 0;
            else {
                /* get an array and init it to NULL */
                if ( (_environ = _malloc_crt(sizeof(void *))) == NULL)
                    return -1;
                *_environ = NULL;
            }
        }

        /* init env pointer */

        env = _environ;

        /* See if the string is already in the environment */

        ix = findenv(option, equal - option);

        if ((ix >= 0) && (*env != NULL)) {
            /* String is already in the environment -- overwrite/remove it.
             */
            if (remove) {
                /* removing -- move all the later strings up */
                for ( ; env[ix] != NULL; ++ix) {
                    env[ix] = env[ix+1];
                }

                /* shrink the environment memory block
                   (ix now has number of strings, including NULL) --
                   this realloc probably can't fail, since we're
                   shrinking a mem block, but we're careful anyway. */
                if (env = (char **) _realloc_crt(env, ix * sizeof(char *)))
                    _environ = env;
            }
            else {
                /* replace the option */
                env[ix] = (char *) option;
            }
        }
        else {
            /*
             * String is NOT in the environment
             */
            if ( !remove )  {

                /*
                 * Append the string to the environ table. Note that
                 * table must be grown to do this.
                 */
                if (ix < 0)
                    ix = -ix;    /* ix = length of environ table */

                if ( (env = (char **)_realloc_crt(env, sizeof(char *) *
                    (ix + 2))) == NULL )
                    return -1;

                env[ix] = (char *)option;
                env[ix + 1] = NULL;
                _environ = env;
            }
            else
                /*
                 * We are asked to remove an environment var that
                 * isn't there...just return success
                 */
                return 0;
        }

        return 0;
}


/***
*int findenv(name, len) - [STATIC]
*
*Purpose:
*       Scan for the given string within the environment
*
*Entry:
*
*Exit:
*       Returns the offset in "environ[]" of the given variable
*       Returns the negative of the length of environ[] if not found.
*       Returns 0 if the environment is empty.
*
*       [NOTE: That a 0 return can mean that the environment is empty
*       or that the string was found as the first entry in the array.]
*
*Exceptions:
*
*******************************************************************************/

static int __cdecl findenv (
        const char *name,
        int len
        )
{
        char **env;

        for ( env = _environ ; *env != NULL ; env++ ) {
            /*
             * See if first len characters match, up to case
             */
            if ( _strnicmp(name, *env, len) == 0 )
                /*
                 * the next character of the environment string must
                 * be an '=' or a '\0'
                 */
                if ( (*env)[len] == '=' || (*env)[len] == '\0' )
                    return(env - _environ);
//
// We cannot break here since findenv must report the total number of strings.
//              else
//                  break;
        }

        return(-(env - _environ));
}



#endif  /* _WIN32 */

