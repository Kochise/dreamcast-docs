        page    ,132
        title   strnicmp - compare n chars of strings, ignore case
;***
;strnicmp.asm - compare n chars of strings, ignoring case
;
;       Copyright (c) 1986-1997, Microsoft Corporation. All rights reserved.
;
;Purpose:
;       defines _strnicmp() - Compares at most n characters of two strings,
;       without regard to case.
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
;int _strnicmp(first, last, count) - compares count char of strings, ignore case
;
;Purpose:
;       Compare the two strings for lexical order.  Stops the comparison
;       when the following occurs: (1) strings differ, (2) the end of the
;       strings is reached, or (3) count characters have been compared.
;       For the purposes of the comparison, upper case characters are
;       converted to lower case.
;
;       Algorithm:
;       int
;       _strncmpi (first, last, count)
;             char *first, *last;
;             unsigned int count;
;             {
;             int f,l;
;             int result = 0;
;
;             if (count) {
;                     do      {
;                             f = tolower(*first);
;                             l = tolower(*last);
;                             first++;
;                             last++;
;                             } while (--count && f && l && f == l);
;                     result = f - l;
;                     }
;             return(result);
;             }
;
;Entry:
;       char *first, *last - strings to compare
;       unsigned count - maximum number of characters to compare
;
;Exit:
;       returns <0 if first < last
;       returns 0 if first == last
;       returns >0 if first > last
;
;Uses:
;
;Exceptions:
;
;*******************************************************************************

        CODESEG

        public  _strnicmp
_strnicmp proc \
        uses edi esi ebx, \
        first:ptr byte, \
        last:ptr byte, \
        count:IWORD

        mov     ecx,[count]     ; cx = byte count
        or      ecx,ecx
        jz      toend           ; if count = 0, we are done

        mov     esi,[first]     ; si = first string
        mov     edi,[last]      ; di = last string

        ; test locale

        lea     eax,__lc_handle
        cmp     [eax + LC_CTYPE],_CLOCALEHANDLE

        jne     notclocale

        ; C locale

        mov     bh,'A'
        mov     bl,'Z'
        mov     dh,'a'-'A'      ; add to cap to make lower

        align   4

lupe:
        mov     ah,[esi]        ; *first

        or      ah,ah           ; see if *first is null

        mov     al,[edi]        ; *last

        jz      short eject     ;   jump if *first is null

        or      al,al           ; see if *last is null
        jz      short eject     ;   jump if so

        inc     esi             ; first++
        inc     edi             ; last++

        cmp     ah,bh           ; 'A'
        jb      short skip1

        cmp     ah,bl           ; 'Z'
        ja      short skip1

        add     ah,dh           ; make lower case

skip1:
        cmp     al,bh           ; 'A'
        jb      short skip2

        cmp     al,bl           ; 'Z'
        ja      short skip2

        add     al,dh           ; make lower case

skip2:
        cmp     ah,al           ; *first == *last ??
        jne     short differ

        dec     ecx
        jnz     short lupe

eject:
        xor     ecx,ecx
        cmp     ah,al           ; compare the (possibly) differing bytes
        je      toend           ; both zero; return 0

differ:
        mov     ecx,-1          ; assume last is bigger (* can't use 'or' *)
        jb      toend           ; last is, in fact, bigger (return -1)
        neg     ecx             ; first is bigger (return 1)

        jmp     toend

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
        mov     ebx,ecx                     ; save count in ebx
        push    _SETLOCALE_LOCK
        call    _lock
        mov     [esp],1                     ; local lock flag is 1
        mov     ecx,ebx                     ; restore count to ecx
end_lock:
endif  ; _MT

        xor     eax,eax
        xor     ebx,ebx

        align   4

lupe2:
        mov     al,[esi]        ; *first

        or      eax,eax         ; see if *first is null

        mov     bl,[edi]        ; *last

        jz      short eject2    ;   jump if *first is null

        or      ebx,ebx         ; see if *last is null
        jz      short eject2    ;   jump if so

        inc     esi
        inc     edi

        push    ecx             ; save ecx (holds count)
        push    eax
        push    ebx

        call    crt_tolower     ; convert *last

        mov     ebx,eax
        add     esp,4

        call    crt_tolower     ; convert *first

        add     esp,4

        pop     ecx             ; restore ecx (count)

        cmp     eax,ebx
        jne     short differ2

        dec     ecx
        jnz     short lupe2

eject2:
        xor     ecx,ecx
        cmp     eax,ebx
        je      short toend2

differ2:
        mov     ecx,-1
        jb      short toend2

        neg     ecx

toend2:

ifdef _MT
        pop     eax                         ; get local lock flag
        or      eax,eax                     ; lock held?
        jnz     short do_unlock             ; yes
lock    dec     __unguarded_readlc_active   ; decrement unguarded locale
                                            ; read flag
        jmp     short end_unlock
do_unlock:
        mov     ebx,ecx                     ; save return value in ebx
        push    _SETLOCALE_LOCK
        call    _unlock
        add     esp,4
        mov     ecx,ebx                     ; restore return value to ecx
end_unlock:
endif  ; _MT

toend:
        mov     eax,ecx

        ret                     ; _cdecl return

_strnicmp endp
         end
