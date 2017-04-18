; Tab width = 4

;----------------------------------------------------------------------------
; ** Low Battery Detection and Data Save Sample 1 **
;
; Detects the low battery condition and saves essential data in flash memory
;----------------------------------------------------------------------------
; 1.01 990208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	Lc868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm

extern	_game_end			; Symbol reference to ghead.asm
extern	fm_wrt_ex, fm_vrf_ex, fm_prd_ex ; Symbol reference to ghead.asm


; **** Definition of System Constants ****************************************

							; OCR (Oscillation Control Register) settings
osc_rc		equ	04dh		;  Specifies internal RC oscillation for the system clock (1/12)
osc_rcfw	equ	0cdh		;  Specifies internal RC oscillation for the system clock (1/6)
osc_xt		equ	0efh		;  Specifies crystal oscillation for the system clock

LowBattChk	equ	06eh		; Low battery detection flag (RAM bank 0)

fmflag		equ	07ch		; Flash memory write end detection method
fmbank		equ	07dh		; Flash memory bank switching
fmadd_h		equ	07eh		; Flash memory upper address
fmadd_l		equ	07fh		; Flash memory lower address

fmbuff		equ	080h		; Start of buffer for flash memory reading/writing

; *** Data Segment ***********************************************************

		dseg				; Data segment start

r0:		ds		1			; Indirect addressing register r0
r1:		ds		1			; Indirect addressing register r1
r2:		ds		1			; Indirect addressing register r2
r3:		ds		1			; Indirect addressing register r3
		ds		12			; Other registers reserved for the system


; *** Code Segment ***********************************************************

		cseg				; Code segment start

; *-------------------------------------------------------------------------*
; * User program															*
; *-------------------------------------------------------------------------*
main:
		call	cls			; Clears the LCD display image

loop0:						; Start of test main loop

		; Application Main Processing

							; ** [M] (mode) Button Check **
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

							; ** Battery Status Check **
		call	ChkBatt		; Checks the battery status
		bz		loop0		; If acc = 0 then battery normal; loops

							; ** Low Battery Processing **
		call	prepare		; Prepares data for test save
							; In an actual application, this routine would gather the data
							; that is to be saved and then place the data
							; in the flash ROM write buffer.

		call	WriteData	; Writes the data that was prepared in the buffer (to be saved) 
							; to flash memory

finish:						; ** Application End Processing **
		jmp		_game_end	; Application end


; *-------------------------------------------------------------------------*

prepare:					; **** Preparing Data for Test Save ****
							; Prepares 128 bytes of data from 10h to 8fh in fmbuff

		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selects data RAM bank 1

		mov		#fmbuff,r0	; Moves the read/write buffer address to r0
		mov		#128,c		; Loop counter (128 times)
		mov		#010h,b		; Initial value of data to be written
loop4:
		ld		b			; Places the data in the buffer
		st		@r0			;

		inc		b			; Changes the writing test data

		inc		r0			; Increments the buffer address

		dec		c			; Decrements the loop counter
		ld		c
		bnz		loop4		; Repeats 128 times

		pop		PSW			; Pops the PSW value off of the stack

		ret					; prepare end


; *-------------------------------------------------------------------------*
; * Detecting Low Battery Status											*
; * Outputs:	acc = 0    : Battery status normal							*
; *			acc = 0ffh: Low battery											*
; *-------------------------------------------------------------------------*
ChkBatt:
		ld		P7			; Checks the status of P71
		bn		acc,1,next3 ; Branches if there is no battery

							; ** Battery Exists **
		mov		#0,acc		; acc = 0
		ret					; ChkBatt end.  acc = 0 is returned if battery exists

next3:						; ** No battery **
		mov		#0ffh,acc	; acc = 0ffh
		ret					; ChkBatt end.  acc = 0ffh is returned if battery does not exist


; *-------------------------------------------------------------------------*
; * Writing Buffer Data to Flash Memory										*
; *-------------------------------------------------------------------------*
WriteData:					; **** Writing to Flash Memory ****

		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selects data RAM bank 1

		mov		#0,fmbank	; Flash memory bank specification = 0
		mov		#high(fmarea),fmadd_h	; Writing destination address (upper)
		mov		#low(fmarea),fmadd_l	; Writing destination address (lower)
		mov		#0,fmflag	; Detects end by toggle bit method

		clr1	PSW,1		; Selects data RAM bank 0
		mov		#0ffh,acc	; Does not detect low battery (0ffh)
		st		LowBattChk	; Low battery automatic detection flag (RAM bank 0)

		pop		PSW			; Pops the PSW value off of the stack

		push	OCR			; Pushes the OCR value onto the stack
		mov		#osc_rc,OCR ; Specifies the system clock (RC)
		clr1	IE,7		; Interruption prohibited
		call	fm_wrt_ex	; BIOS "Writing to flash memory"
		set1	IE,7		; Interruption permitted
		pop		OCR			; Pops the OCR value off of the stack

		push	PSW			; Pushes the PSW value onto the stack
		clr1	PSW,1		; Selects data RAM bank 0
		mov		#0,acc		; Detects low battery (0)
		st		LowBattChk	; Low battery automatic detection flag (RAM bank 0)
		pop		PSW			; Pops the PSW value off of the stack

		ret					; WriteData end


; *-------------------------------------------------------------------------*
; * Clearing the LCD Display Image											*
; *-------------------------------------------------------------------------*
cls:
		push	OCR			; Pushes the OCR value onto the stack
		mov		#osc_rc,OCR ; Specifies the system clock *

		mov		#0,XBNK		; Specifies the display RAM bank address (BANK0)
		call	cls_s		; Clears the data in that bank

		mov		#1,XBNK		; Specifies the display RAM bank address (BANK1)
		call	cls_s		; Clears the data in that bank
		pop		OCR			; Pops the OCR value off of the stack

		ret					; cls end

cls_s:						; *** Clearing One Bank of Display RAM ***
		mov		#80h,r2		; Points the indirect addressing register at the start of display RAM
		mov		#80h,b		; Sets the number of loops in loop counter b
loop3:
		mov		#0,@r2		; Writes "0" while incrementing the address
		inc		r2			;
		dbnz	b,loop3		; Repeats until b is "0"

		ret					; cls_s end


; *-------------------------------------------------------------------------*
; * Flash Memory Area for Saving Data										*
; *-------------------------------------------------------------------------*
		org ((*-1) land 0ff80h) + 80h		; Aligns with 128-byte boundary
fmarea:
		; Allocates a 128-byte flash memory area
		db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

end
