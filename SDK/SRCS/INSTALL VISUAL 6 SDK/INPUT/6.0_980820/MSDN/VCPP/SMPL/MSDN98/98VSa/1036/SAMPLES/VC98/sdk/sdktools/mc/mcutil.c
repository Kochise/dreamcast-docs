/*++

Copyright (c) 1991-1997 Microsoft Corporation

Module Name:

    mcutil.c

Abstract:

    This file contains utility functions for the Win32 Message Compiler (MC)

--*/

#include "mc.h"


/*++

Routine Description:

    This routine simply writes/overwrites Name, ID and Value
    to a link list of NAME_INFO structures.

Arguments:

    PNAME_INFO
    Keyword such as "Facility", "Serverity", ...
    Lauguage Identifier; a combination of a Primary Language ID,
    Sublanguage ID pair such as LANG_NEUTRAL, SUBLANG_NEUTRAL
    An option value specfic to the keyword.

Return Value:

    The list PNAME_INFO

--*/

PNAME_INFO
McAddName(
    PNAME_INFO *NameListHead,
    char *Name,
    ULONG Id,
    PVOID Value
    )
{
    PNAME_INFO p;
    int n;

    while (p = *NameListHead) {
        if (!(n = stricmp( p->Name, Name ))) {
            if (p->Id != Id) {
                McInputError( "Redefining value of %s", FALSE, Name );
                }

            p->Id = Id;
            p->Value = Value;
            p->Used = FALSE;
            return( p );
            }
        else
        if (n < 0) {
            break;
            }

        NameListHead = &p->Next;
        }

    p = malloc( sizeof( *p ) + strlen( Name ) );
    p->LastId = 0;
    p->Id = Id;
    p->Value = Value;
    p->Used = FALSE;
    strcpy( p->Name, Name );
    p->Next = *NameListHead;
    *NameListHead = p;
    return( p );
}



/*++

Routine Description:

    This routine returns the NAME_INFO structure cooresponding to the
    given Keyword.

Arguments:

    PNAME_INFO
    Keyword such as "Facility", "Serverity", ...

Return Value:

    Either the NAME_INFO structure cooresponding to the keyname or NULL

--*/


PNAME_INFO
McFindName(
    PNAME_INFO NameListHead,
    char *Name
    )
{
    PNAME_INFO p;

    p = NameListHead;
    while (p) {
        if (!stricmp( p->Name, Name )) {
            p->Used = TRUE;
            break;
            }

        p = p->Next;
        }

    return( p );
}



/*++

Routine Description:

    This converts a string value to the corresponding integer value
    in the specified base.

Arguments:

    String image of an integer
    Base of resultant integer
    Pointer to a unsigned long


Return Value:

    A unsigned long

--*/

BOOLEAN
McCharToInteger(
    PCHAR String,
    int Base,
    PULONG Value
    )
{
    CHAR c;
    ULONG Result, Digit, Shift;


    c = *String;
    String = CharNext(String);
    if (!Base) {
        Base = 10;
        Shift = 0;
        if (c == '0') {
            c = *String++;
            if (c == 'x') {
                Base = 16;
                Shift = 4;
                }
            else
            if (c == 'o') {
                Base = 8;
                Shift = 3;
                }
            else
            if (c == 'b') {
                Base = 2;
                Shift = 1;
                }
            else {
                String--;
                }

            c = *String++;
            }
        }
    else {
        switch( Base ) {
            case 16:    Shift = 4;  break;
            case  8:    Shift = 3;  break;
            case  2:    Shift = 1;  break;
            case 10:    Shift = 0;  break;
            default:    return( FALSE );
            }
        }

    Result = 0;
    while (c) {
        if (c >= '0' && c <= '9') {
            Digit = c - '0';
            }
        else
        if (c >= 'A' && c <= 'F') {
            Digit = c - 'A' + 10;
            }
        else
        if (c >= 'a' && c <= 'f') {
            Digit = c - 'a' + 10;
            }
        else {
            break;
            }

        if ((int)Digit >= Base) {
            break;
            }

        if (Shift == 0) {
            Result = (Base * Result) + Digit;
            }
        else {
            Result = (Result << Shift) | Digit;
            }


        c = *String;
        String = CharNext(String);
	}

    *Value = Result;
    return( TRUE );
}

/*++

Routine Description:

    Duplicates a string

Arguments:

    A string value

Return Value:

    The duplicated string value

--*/


char *
McMakeString(
    char *String
    )
{
    char *s;

    s = malloc( strlen( String ) + 1 );
    strcpy( s, String );
    return( s );
}
