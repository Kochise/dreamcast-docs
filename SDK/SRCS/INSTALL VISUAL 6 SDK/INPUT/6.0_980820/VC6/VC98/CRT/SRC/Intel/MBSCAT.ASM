;***
;mbscat.asm - contains mbscat() and mbscpy() routines
;
;       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
;
;Purpose:
;       STRCAT concatenates (appends) a copy of the source string to the
;       end of the destination string, returning the destination string.
;
;*******************************************************************************

file    TEXTEQU <ntel\str>
path    TEXTEQU <i>

strcat  EQU <_mbscat>
strcpy  EQU <_mbscpy>

%       include &path&&file&cat.asm
