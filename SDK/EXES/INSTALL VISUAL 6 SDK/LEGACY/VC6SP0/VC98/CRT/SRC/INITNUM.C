/***
*initnum.c - contains __init_numeric
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Contains the locale-category initialization function: __init_numeric().
*
*       Each initialization function sets up locale-specific information
*       for their category, for use by functions which are affected by
*       their locale category.
*
*       *** For internal use by setlocale() only ***
*
*******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <setlocal.h>
#include <malloc.h>
#include <nlsint.h>
#include <dbgint.h>

static void fix_grouping(
        char *grouping
        )
{
        /*
         * ANSI specifies that the fields should contain "\3" [\3\0] to indicate
         * thousands groupings (100,000,000.00 for example).
         * NT uses "3;0"; ASCII 3 instead of value 3 and the ';' is extra.
         * So here we convert the NT version to the ANSI version.
         */

        while (*grouping)
        {
            /* convert '3' to '\3' */
            if (*grouping >= '0' && *grouping <= '9')
            {
                *grouping = *grouping - '0';
                grouping++;
            }

            /* remove ';' */
            else if (*grouping == ';')
            {
                char *tmp = grouping;

                do
                    *tmp = *(tmp+1);
                while (*++tmp);
            }

            /* unknown (illegal) character, ignore */
            else
                grouping++;
        }
}

/***
*int __init_numeric() - initialization for LC_NUMERIC locale category.
*
*Purpose:
*
*Entry:
*       None.
*
*Exit:
*       0 success
*       1 fail
*
*Exceptions:
*
*******************************************************************************/

int __cdecl __init_numeric (
        void
        )
{
        static char *dec_pnt = NULL;
        static char *thous_sep = NULL;
        static char *grping = NULL;
        int ret = 0;

        /* Numeric data is country--not language--dependent.  NT work-around. */
        LCID ctryid = MAKELCID(__lc_id[LC_NUMERIC].wCountry, SORT_DEFAULT);

        if (__lc_handle[LC_NUMERIC] != _CLOCALEHANDLE)
        {
                ret |= __getlocaleinfo(LC_STR_TYPE, ctryid, LOCALE_SDECIMAL, (void *)&dec_pnt);
                ret |= __getlocaleinfo(LC_STR_TYPE, ctryid, LOCALE_STHOUSAND, (void *)&thous_sep);
                ret |= __getlocaleinfo(LC_STR_TYPE, ctryid, LOCALE_SGROUPING, (void *)&grping);
            fix_grouping(grping);

                if (ret)
                {
                        _free_crt (dec_pnt);
                        _free_crt (thous_sep);
                        _free_crt (grping);
                        dec_pnt = NULL;
                        thous_sep = NULL;
                        grping = NULL;
                        return -1;
                }

                if (__lconv->decimal_point != __lconv_static_decimal)
                {
                        _free_crt(__lconv->decimal_point);
                        _free_crt(__lconv->thousands_sep);
                        _free_crt(__lconv->grouping);
                }

                __lconv->decimal_point = dec_pnt;
                __lconv->thousands_sep = thous_sep;
                __lconv->grouping = grping;


                /* set global decimal point character */
                *__decimal_point = *__lconv->decimal_point;
                __decimal_point_length = 1;

                return 0;

        } else {
                _free_crt (dec_pnt);
                _free_crt (thous_sep);
                _free_crt (grping);
                dec_pnt = NULL;
                thous_sep = NULL;
                grping = NULL;

                /* malloc them so we can free them */
                if ((__lconv->decimal_point =
                    _malloc_crt(2)) == NULL)
                return -1;
                strcpy(__lconv->decimal_point, ".");

                if ((__lconv->thousands_sep =
                    _malloc_crt(2)) == NULL)
                return -1;
                __lconv->thousands_sep[0] = '\0';

                if ((__lconv->grouping =
                    _malloc_crt(2)) == NULL)
                return -1;
                __lconv->grouping[0] = '\0';

                /* set global decimal point character */
                *__decimal_point = *__lconv->decimal_point;
                __decimal_point_length = 1;

                return 0;
        }
}
