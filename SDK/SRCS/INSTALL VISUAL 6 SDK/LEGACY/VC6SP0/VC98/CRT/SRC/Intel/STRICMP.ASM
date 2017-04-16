        page    ,132
        title   stricmp
;***
;stricmp.asm - contains case-insensitive string comparision routine
;       _stricmp/_strcmpi
;
;       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
;
;Purpose:
;       contains _stricmpi(), also known as _strcmpi()
;
;*******************************************************************************

        .xlist
        include cruntime.inc
        .list


ifdef _MT

; Def and decls necessary to assert the lock for the LC_CTYPE locale category

_SETLOCALE_LOCK EQU     19

extrn   _lock:proc
extrn   _unlock:proc

endif  ; _MT

; Defs and decl necessary to test for the C locale.

_CLOCALEHANDLE  EQU     0
LC_CTYPE        EQU     2 * 4


extrn   __lc_handle:dword

ifdef _MT
extrn   __setlc_active:dword
extrn   __unguarded_readlc_active:dword
endif  ; _MT



ifdef _MT
crt_tolower EQU _tolower_lk
else  ; _MT
crt_tolower EQU tolower
endif  ; _MT


extrn   crt_tolower:proc


page
;***
;int _stricmp(dst, src), _strcmpi(dst, src) - compare strings, ignore case
;
;Purpose:
;       _stricmp/_strcmpi perform a case-insensitive string comparision.
;       For differences, upper case letters are mapped to lower case.
;       Thus, "abc_" < "ABCD" since "_" < "d".
;
;       Algorithm:
;
;       int _strcmpi (char * dst, char * src)
;       {
;               int f,l;
;
;               do {
;                       f = tolower(*dst);
;                       l = tolower(*src);
;                       dst++;
;                       src++;
;               } while (f && f == l);
;
;               return(f - l);
;       }
;
;Entry:
;       char *dst, *src - strings to compare
;
;Exit:
;       AX = -1 if dst < src
;       AX =  0 if dst = src
;       AX = +1 if dst > src
;
;Uses:
;       CX, DX
;
;Exceptions:
;
;*******************************************************************************

        CODESEG

        public  _strcmpi        ; alternate entry point for compatibility
_strcmpi proc
_strcmpi endp

        public  _stricmp
_stricmp proc \
        uses edi esi ebx, \
        dst:ptr, \
        src:ptr

        ; load up args

        mov     esi,[src]       ; esi = src
        mov     edi,[dst]       ; edi = dst

        ; test locale

        lea     eax,__lc_handle
        cmp     [eax + LC_CTYPE],_CLOCALEHANDLE

        jne     notclocale

        ; C locale

        mov     al,-1           ; fall into loop

        align   4

chk_null:
        or      al,al
        jz      short done

        mov     al,[esi]        ; al = next source byte
        inc     esi
        mov     ah,[edi]        ; ah = next dest byte
        inc     edi

        cmp     ah,al           ; first try case-sensitive comparision
        je      short chk_null  ; match

        sub     al,'A'
        cmp     al,'Z'-'A'+1
        sbb     cl,cl
        and     cl,'a'-'A'
        add     al,cl
        add     al,'A'          ; tolower(*dst)

        xchg    ah,al           ; operations on AL are shorter than AH

        sub     al,'A'
        cmp     al,'Z'-'A'+1
        sbb     cl,cl
        and     cl,'a'-'A'
        add     al,cl
        add     al,'A'          ; tolower(*src)

        cmp     al,ah           ; inverse of above comparison -- AL & AH are swapped
        je      short chk_null

                                ; dst < src     dst > src
        sbb     al,al           ; AL=-1, CY=1   AL=0, CY=0
        sbb     al,-1           ; AL=-1         AL=1
done:
        movsx   eax,al          ; extend al to eax

        jmp     short doret

notclocale:

        ; Not the C locale. Must call tolower/_tolower_lk to convert chars
        ; to lower case.

ifdef _MT
lock    inc     __unguarded_readlc_active   ; bump unguarded locale read flag
        cmp     __setlc_active,0            ; is setlocale() active?
        jg      short do_lock               ; yes, go assert lock
        push    0                           ; local lock flag is 0
        jmp     short end_lock
do_lock:
lock    dec     __unguarded_readlc_active   ; restore flag
        push    _SETLOCALE_LOCK
        call    _lock
        mov     [esp],1                     ; local lock flag is 1
end_lock:
endif  ; _MT

        mov     eax,255
        xor     ebx,ebx

        align   4

chk_null2:
        or      al,al           ; not that if al == 0, then eax == 0!
        jz      short done2

        mov     al,[esi]        ; al = next src byte
        inc     esi
        mov     bl,[edi]        ; bl = next dst byte
        inc     edi

        cmp     al,bl           ; first try case-sensitive comparision
        je      short chk_null2 ; match

        push    eax
        push    ebx

        call    crt_tolower     ; convert dst char to lower case

        mov     ebx,eax
        add     esp,4

        call    crt_tolower     ; convert src char to lower case

        add     esp,4

        cmp     bl,al
        je      chk_null2

        sbb     eax,eax
        sbb     eax,-1

done2:

ifdef _MT
        mov     ebx,eax                     ; save return value in ebx
        pop     eax                         ; get local lock flag
        or      eax,eax                     ; lock held?
        jnz     do_unlock                   ; yes
lock    dec     __unguarded_readlc_active
        jmp     short end_unlock
do_unlock:
        push    _SETLOCALE_LOCK
        call    _unlock
        add     esp,4
end_unlock:
        mov     eax,ebx         ; recover return value
endif  ; _MT

doret:
        ret

_stricmp endp
        end
