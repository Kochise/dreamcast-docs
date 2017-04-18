        page    ,132
        title   memcmp - compare to blocks of memory
;***
;memcmp.asm - compare two blocks of memory
;
;       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
;
;Purpose:
;       defines memcmp() - compare two memory blocks lexically and
;       find their order.
;
;*******************************************************************************

        .xlist
        include cruntime.inc
        .list

page
;***
;int memcmp(buf1, buf2, count) - compare memory for lexical order
;
;Purpose:
;       Compares count bytes of memory starting at buf1 and buf2
;       and find if equal or which one is first in lexical order.
;
;       Algorithm:
;       int
;       memcmp (buf1, buf2, count)
;               char *buf1, *buf2;
;               unsigned count;
;       {
;               if (!count)
;                       return(0);
;               while (--count && *buf1 == *buf2)
;                       {
;                       buf1++;
;                       buf2++;
;                       }
;               return(*buf1 - *buf2);
;       }
;
;Entry:
;       char *buf1, *buf2 - pointers to memory sections to compare
;       unsigned count - length of sections to compare
;
;Exit:
;       returns -1 if buf1 < buf2
;       returns  0 if buf1 == buf2
;       returns +1 if buf1 > buf2
;
;Uses:
;
;Exceptions:
;
;*******************************************************************************

        CODESEG

        public  memcmp
memcmp  proc

        .FPO    ( 0, 3, 0, 0, 0, 0 )

        mov     eax,[esp+0ch]   ; eax = counter
        test    eax,eax         ; test if counter is zero
        jz      short retnull   ; return 0

        mov     edx,[esp+4]     ; edx = buf1
        push    esi
        push    edi
        mov     esi,edx         ; esi = buf1
        mov     edi,[esp+10h]   ; edi = buf2

; Check for dword (32 bit) alignment
        or      edx,edi
        and     edx,3           ; edx=0 iff buf1 are buf2 are aligned
        jz      short dwords

; Strings are not aligned. If the caller knows the strings (buf1 and buf2) are
; different, the function may be called with length like -1. The difference
; may be found in the last dword of aligned string, and because the other
; string is misaligned it may cause page fault. So, to be safe. the comparison
; must be done byte by byte.
        test    eax,1
        jz      short main_loop

        mov     cl,[esi]
        cmp     cl,[edi]
        jne     short not_equal
        inc     esi
        inc     edi
        dec     eax
        jz      short done      ; eax is already 0

main_loop:
        mov     cl,[esi]
        mov     dl,[edi]
        cmp     cl,dl
        jne     short not_equal

        mov     cl,[esi+1]
        mov     dl,[edi+1]
        cmp     cl,dl
        jne     short not_equal

        add     edi,2
        add     esi,2

        sub     eax,2
        jnz     short main_loop
done:
        pop     edi
        pop     esi
retnull:
        ret                     ; _cdecl return


dwords:
        mov     ecx,eax
        and     eax,3           ; eax= counter for tail loop

        shr     ecx,2
        jz      short tail_loop_start
                                ; counter was >=4 so may check one dword
        rep     cmpsd

        jz      short tail_loop_start

; in last dword was difference
        mov     ecx,[esi-4]     ; load last dword from buf1 to ecx
        mov     edx,[edi-4]     ; load last dword from buf2 to edx
        cmp     cl,dl           ; test first bytes
        jne     short difference_in_tail
        cmp     ch,dh           ; test seconds bytes
        jne     short difference_in_tail
        shr     ecx,10h
        shr     edx,10h
        cmp     cl,dl           ; test third bytes
        jne     short difference_in_tail
        cmp     ch,dh           ; they are different, but each one is bigger?
;       jmp     short difference_in_tail

difference_in_tail:
        mov     eax,0
                                ; buf1 < buf2 buf1 > buf2
not_equal:
        sbb     eax,eax         ; AX=-1, CY=1 AX=0, CY=0
        pop     edi             ; counter
        sbb     eax,-1          ; AX=-1 AX=1
        pop     esi
        ret                     ; _cdecl return

; in tail loop we test last three bytes (esi and edi are aligned on dword
; boundary)
tail_loop_start:

        test    eax,eax         ; eax is counter%4 (number of bytes for tail
                                ; loop)
        jz      short done      ; taken if there is no tail bytes
        mov     edx,[esi]       ; load dword from buf1
        mov     ecx,[edi]       ; load dword from buf2
        cmp     dl,cl           ; test first bytes
        jne     short difference_in_tail
        dec     eax             ; counter--
        jz      short tail_done
        cmp     dh,ch           ; test second bytes
        jne     short difference_in_tail
        dec     eax             ; counter--
        jz      short tail_done
        and     ecx,00ff0000h   ; test third bytes
        and     edx,00ff0000h
        cmp     edx,ecx
        jne     short difference_in_tail
        dec     eax
tail_done:
        pop     edi
        pop     esi
        ret                     ; _cdecl return

memcmp  endp
        end

