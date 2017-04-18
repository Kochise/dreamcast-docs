    page 60,132
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;   ppdbg.asm
;
;   Printer port debug stuff
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

        .286

        .xlist
        include cmacros.inc                   
        .list

?PLM=1  ; pascal call convention
?WIN=1  ; Windows prolog/epilog code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;   equates
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LPT1    equ 3BCH
LPT2    equ 378H
LPT3    equ 278H

PORT    equ LPT2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;   data segment
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

sBegin DATA

sEnd DATA

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;   code segment
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

sBegin CODE

        assumes cs, CODE
        assumes ds, DATA




cProc ppdbgSet <FAR, PASCAL, PUBLIC> <si, di>

        ParmB maskbits

        cBegin

        mov dx, PORT
        mov ah, maskbits

;       pushf
;       cli             ; we want this atomic

        in al, dx
        or al, ah
        out dx, al

;       popf

        cEnd

cProc ppdbgClear <FAR, PASCAL, PUBLIC> <si, di>

        ParmB maskbits

        cBegin

        mov dx, PORT
        mov ah, maskbits
        not ah

;       pushf
;       cli             ; we want this atomic

        in al, dx
        and al, ah
        out dx, al

;       popf

        cEnd

cProc ppdbgPulse <FAR, PASCAL, PUBLIC> <si, di>

        ParmB maskbits

        cBegin

        mov dx, PORT
        mov ah, maskbits

;       pushf
;       cli             ; we want this atomic

        in al, dx
        xor al, ah
        out dx, al
        xor al, ah
        out dx, al

;       popf

        cEnd

sEnd CODE

        end
