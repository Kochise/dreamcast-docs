    page ,132
    TITLE FAST32.ASM
;---------------------------------------------------------------------------;
;  FAST.ASM
;
;  32 bit asm routines for doing a "sprite" bitblt
;
;      TransCopyDIBBits - copy DIB bits with a transparent color
;      CopyDIBBits      - copy DIB bits without a transparent color
;
;---------------------------------------------------------------------------;

;
; 32 bit code segment version of FAST16.ASM
; General technology courtesy of Todd Laney
;
; NOTE! cmacro32.inc NEEDS MASM 5.1 (or compatible)
; you would think MASM 6 would be compatible but it isn't
;
    .xlist
    include cmacro32.inc
    .list

;
; NOTE!!!! because we are generating USE32 code this must NOT
; be located in a code segment with USE16 code, so we put it into
; it's own little segment....
;

ifndef SEGNAME
    SEGNAME equ <FAST_TEXT32>
endif

createSeg %SEGNAME, CodeSeg, word, use32, CODE

sBegin Data
sEnd Data

sBegin CodeSeg
        assumes cs,CodeSeg
        assumes ds,nothing
        assumes es,nothing

;-------------------------------------------------------
;
; TransCopyDIBBits
;
; Copy a block with transparency
;
;-------------------------------------------------------

cProc TransCopyDIBBits,<FAR, PASCAL, PUBLIC>,<>
        ParmD   pDest           ; dest pointer
        ParmD   pSource         ; source pointer
        ParmD   dwWidth         ; width pixels
        ParmD   dwHeight        ; height pixels
        ParmD   dwScanD         ; width bytes dest
        ParmD   dwScanS         ; width bytes source
        ParmB   bTranClr        ; transparent color
cBegin
        push ds
        push esi
        push edi

        mov ecx, dwWidth
        or ecx,ecx
        jz tcdb_nomore     ; test for silly case

        mov edx, dwHeight       ; EDX is line counter
        mov ah, bTranClr        ; AL has transparency color

        xor esi, esi
        lds si, pSource         ; DS:[ESI] point to source

        xor edi, edi
        les di, pDest           ; ES:[EDI] point to dest

        sub dwScanD,ecx         ; bias these
        sub dwScanS,ecx

        mov ebx,ecx             ; save this for later

        align 4
tcdb_morelines:
        mov ecx, ebx            ; ECX is pixel counter
        shr ecx,2
        jz  short tcdb_nextscan

;
; The idea here is to not branch very often so we unroll the loop by four
; and try to not branch when a whole run of pixels is either transparent
; or not transparent.
;
; There are two loops. One loop is for a run of pixels equal to the
; transparent color, the other is for runs of pixels we need to store.
;
; When we detect a "bad" pixel we jump to the same position in the
; other loop.
;
; Here is the loop we will stay in as long as we encounter a "transparent"
; pixel in the source.
;

        align 4
tcdb_same:
        mov al, ds:[esi]
        cmp al, ah
        jne short tcdb_diff0

tcdb_same0:
        mov al, ds:[esi+1]
        cmp al, ah
        jne short tcdb_diff1

tcdb_same1:
        mov al, ds:[esi+2]
        cmp al, ah
        jne short tcdb_diff2

tcdb_same2:
        mov al, ds:[esi+3]
        cmp al, ah
        jne short tcdb_diff3

tcdb_same3:
        add edi,4
        add esi,4
        dec ecx
        jnz short tcdb_same
        jz  short tcdb_nextscan

;
; Here is the loop we will stay in as long as 
; we encounter a "non transparent" pixel in the source.
;

        align 4
tcdb_diff:
        mov al, ds:[esi]
        cmp al, ah
        je short tcdb_same0

tcdb_diff0:
        mov es:[edi],al
        mov al, ds:[esi+1]
        cmp al, ah
        je short tcdb_same1

tcdb_diff1:
        mov es:[edi+1],al
        mov al, ds:[esi+2]
        cmp al, ah
        je short tcdb_same2

tcdb_diff2:
        mov es:[edi+2],al
        mov al, ds:[esi+3]
        cmp al, ah
        je short tcdb_same3

tcdb_diff3:
        mov es:[edi+3],al

        add edi,4
        add esi,4
        dec ecx
        jnz short tcdb_diff
        jz  short tcdb_nextscan

;
; We are at the end of a scan, check for odd leftover pixels to do
; and go to the next scan.
;

        align 4
tcdb_nextscan:
        mov ecx,ebx
        and ecx,11b
        jnz short tcdb_oddstuff
        ; move on to the start of the next line

tcdb_nextscan1:
        add esi, dwScanS
        add edi, dwScanD

        dec edx                 ; line counter
        jnz short tcdb_morelines
        jz  short tcdb_nomore

;
; If the width is not a multiple of 4 we will come here to clean up
; the last few pixels
;

tcdb_oddstuff:
        inc ecx
tcdb_oddloop:
        dec ecx
        jz  short tcdb_nextscan1
        mov al, ds:[esi]
        inc esi
        inc edi
        cmp al, ah
        je  short tcdb_oddloop
        mov es:[edi-1],al
        jmp short tcdb_oddloop

tcdb_nomore:
        pop edi
        pop esi
        pop ds
cEnd

;-----------------------------------------------------------------------------;
;
; CopyDIBBits
;
; Copy a block without transparency
;
;-----------------------------------------------------------------------------;

cProc CopyDIBBits,<FAR, PASCAL, PUBLIC>,<>
        ParmD   pDest           ; dest pointer
        ParmD   pSource         ; source pointer
        ParmD   dwWidth         ; width pixels
        ParmD   dwHeight        ; height pixels
        ParmD   dwScanD         ; width bytes dest
        ParmD   dwScanS         ; width bytes source
cBegin
        push ds
        push esi
        push edi

        mov ecx, dwWidth
        or ecx,ecx
        jz cdb_nomore     ; test for silly case

        mov edx, dwHeight       ; EDX is line counter
        or edx,edx
        jz cdb_nomore     ; test for silly case

        xor esi, esi
        lds si, pSource         ; DS:[ESI] point to source

        xor edi, edi
        les di, pDest           ; ES:[EDI] point to dest

        sub dwScanD,ecx         ; bias these
        sub dwScanS,ecx

        mov ebx,ecx
        shr ebx,2

        mov eax,ecx
        and eax,11b

        align 4
cdb_loop:
        mov ecx, ebx
        rep movs dword ptr es:[edi], dword ptr ds:[esi]
        mov ecx,eax
        rep movs byte ptr es:[edi], byte ptr ds:[esi]

        add esi, dwScanS
        add edi, dwScanD
        dec edx                 ; line counter
        jnz short cdb_loop

cdb_nomore:
        pop edi
        pop esi
        pop ds
cEnd



sEnd CodeSeg
end
