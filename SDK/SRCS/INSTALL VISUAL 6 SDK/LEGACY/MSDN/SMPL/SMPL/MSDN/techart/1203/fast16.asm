    page ,132

    TITLE FAST16.ASM

; 
; This is obsolete and replaced by FAST32.ASM it is here for
; reference only
;


?PLM=1      ; PASCAL Calling convention is DEFAULT
?WIN=0      ; Windows calling convention
?DF=0       ; don't define anything

    .xlist
    include cmacros.inc
    .list

ifndef SEGNAME
    SEGNAME equ <FAST_TEXT>
endif

createSeg %SEGNAME, CodeSeg, word, public, CODE

sBegin Data
sEnd Data

sBegin CodeSeg
        assumes cs,CodeSeg
        assumes ds,nothing
        assumes es,nothing

;
; Copy a block
;

cProc CopyBlock,<FAR, PASCAL, PUBLIC>,<>

    ParmD   pDest
    ParmD   pSource
    ParmD   dwWidth
    ParmD   dwHeight
    ParmD   dwScanD
    ParmD   dwScanS
    ParmB   bTranClr

    LocalD  dwOffS
    LocalD  dwOffD

cBegin
        .386
        align   4

        push ds
        push es
        push esi
        push edi

        mov ecx, dwWidth
        jecxz copyblock_nomore  ; test for silly case

        mov edx, dwHeight       ; EDX is line counter
        mov ah, bTranClr        ; AH has transparency color

        xor esi, esi
        lds si, pSource         ; DS:[ESI] point to source
        mov dwOffS, esi         ; save offset

        xor edi, edi
        les di, pDest           ; ES:[EDI] point to dest
        mov dwOffD, edi         ; save offset

copyblock_morelines:

        and edx, edx
        jz copyblock_nomore

        mov esi, dwOffS         ; DS:[ESI] point to source
        mov edi, dwOffD         ; ES:[EDI] point to dest
        mov ecx, dwWidth        ; ECX is pixel counter

copyblock_morepixels:

        mov al, ds:[esi]
        cmp al, ah
        jz copyblock_nextpixel

        mov es:[edi], al

copyblock_nextpixel:

        inc esi
        inc edi

        dec ecx
        jnz copyblock_morepixels

        ; move on to the start of the next line

        mov esi, dwOffS
        add esi, dwScanS
        mov dwOffS, esi

        mov esi, dwOffD
        add esi, dwScanD
        mov dwOffD, esi

        dec edx                 ; line counter
        jmp copyblock_morelines

copyblock_nomore:

        pop edi
        pop esi
        pop es
        pop ds

        .286
cEnd

sEnd CodeSeg
end

