; Tab width = 4

;----------------------------------------------------------------------------
; ** Flash Memory Usage Sample 1 **
;
; This sample writes and verifies data in flash memory, and then reads and verifies the data.
; If all operations are performed correctly, the characters "SEGA" appear on the LCD.
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
osc_rc		equ	04dh		; Specifies internal RC oscillation for the system clock (1/12)
osc_rcfw	equ	0cdh		; Specifies internal RC oscillation for the system clock (1/6)
osc_xt		equ	0efh		; Specifies crystal oscillation for the system clock

LowBattChk	equ	06eh		; Low battery detection flag (RAM bank 0)

fmflag		equ	07ch		; Flash memory write end detection method
fmbank		equ	07dh		; Flash memory bank switching
fmadd_h		equ	07eh		; Flash memory upper address
fmadd_l		equ	07fh		; Flash memory lower address

fmbuff		equ	080h		; Start of buffer for flash memory reading/writing

; *** Data Segment **********************************************************

		dseg				; Data segment start

r0:		ds		1			; Indirect addressing register r0
r1:		ds		1			; Indirect addressing register r1
r2:		ds		1			; Indirect addressing register r2
r3:		ds		1			; Indirect addressing register r3
		ds		12			; Other registers reserved for the system

; *** Code Segment **********************************************************

		cseg				; Code segment start

; *-------------------------------------------------------------------------*
; * User program															*
; *-------------------------------------------------------------------------*
main:
		call	cls			; Clears the LCD display image


							; Preparing Data for the Test Write
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


							; **** Displaying "S" ****

		mov		#1,c		; Horizontal coordinate
		mov		#1,b		; Vertical coordinate
		mov		#0ah,acc	; Character code 'S'
		call	putch		; Displays a single character


							; **** Writing to Flash Memory ****

		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selects data RAM bank 1

		mov		#0,fmbank	; Flash memory bank specification = 0
		mov		#high(fmarea),fmadd_h ; Writing destination address (upper)
		mov		#low(fmarea),fmadd_l ; Writing destination address (lower)
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


							; **** Displaying "E" ****

		mov		#2,c		; Horizontal coordinate
		mov		#1,b		; Vertical coordinate
		mov		#0bh,acc	; Character code 'E'
		call	putch		; Displays a single character


							; **** Verifying Flash Memory ****

		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selects data RAM bank 1

		mov		#0,fmbank	; Flash memory bank specification = 0
		mov		#high(fmarea),fmadd_h ; Address (upper)
		mov		#low(fmarea),fmadd_l ; Address (lower)


		push	OCR			; Pushes the OCR value onto the stack
		mov		#osc_rc,OCR ; Specifies the system clock (RC)
		
		call	fm_vrf_ex	; BIOS "Verifying flash memory"
		clr1	IE,7		; Interruption prohibited
		pop		OCR			; Pops the OCR value off of the stack
		set1	IE,7		; Interruption permitted
		pop		PSW			; Pops the PSW value off of the stack

		bnz		vrt_bad		; Branches when write failed
							; Displays "G" only when successful

							; **** Displaying "G" ****

		mov		#3,c		; Horizontal coordinate
		mov		#1,b		; Vertical coordinate
		mov		#0ch,acc	; Character code 'G'
		call	putch		; Displays a single character
vrt_bad:


							; **** Reading Page Data form Flash Memory ****

		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selects data RAM bank 1

		mov		#0,fmbank	; Flash memory bank specification = 0
		mov		#high(fmarea),fmadd_h ; Address (upper)
		mov		#low(fmarea),fmadd_l ; Address (lower)

		push	OCR			; Pushes the OCR value onto the stack
		mov		#osc_rc,OCR	; Specifies the system clock (RC)
		clr1	IE,7		; Interruption prohibited
		call	fm_prd_ex	; BIOS "Reading page data from flash memory"
		set1	IE,7		; Interruption permitted
		pop		OCR			; Pops the OCR value off of the stack

		pop		PSW			; Pops the PSW value off of the stack


							; **** Verifying the data that was read ****

		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selects data RAM bank 1

		mov		#fmbuff,r0	; Moves the read/write buffer address into r0
		mov		#128,c		; Loop counter (128 times)
		mov		#010h,b		; Initial value for comparison data
loop5:
		ld		b			; Places the data in the buffer
		sub		@r0			; Compares the data
		bnz		read_bad	; If a compare error is found, ends without displaying 'A

		inc		b			; Changes the data for the write test

		inc		r0			; Increments the buffer address

		dec		c			; Decrements the loop counter
		ld		c
		bnz		loop5		; Repeats 128 times

		pop		PSW			; Pops the PSW value off of the stack


							; **** Displaying "A" ****

		mov		#4,c		; Horizontal coordinate
		mov		#1,b		; Vertical coordinate
		mov		#0dh,acc	; Character code 'A'
		call	putch		; Displays a single character


read_bad:
loop6:						; ** [M] (mode) Button Check **
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		br		loop6		; Waits until [M] button is pressed

finish:						; ** Application End Processing **
		jmp		_game_end	; Application end


; *-------------------------------------------------------------------------*
; * Clearing the LCD Display Image											*
; *-------------------------------------------------------------------------*
cls:
		push	OCR			; Pushes the OCR value onto the stack
		mov		#osc_rc,OCR ; Specifies the system clock

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
; * Displaying One Character in a Specified Position						*
; * Inputs: acc: Character code												*
; *			  c: Horizontal position of character							*
; *			  b: Vertical position of character								*
; *-------------------------------------------------------------------------*
putch:
		push	XBNK
		push	acc
		call	locate		; Calculates display RAM address according to coordinates
		pop		acc
		call	put_chara	; Displays one character
		pop		XBNK

		ret					; putch end


locate: ; **** Calculating the Display RAM Address According to the Display Position Specification ****
		; ** Inputs: c: Horizontal position (0 to 5) b: Vertical position (0 to 3)
		; ** Outputs: r2: RAM address XBNK: Display RAM bank

							; *** Determining the Display RAM Bank Address ***
		ld		b			; Jump to next1 when b >= 2
		sub		#2			;
		bn		PSW,7,next1 ;

		mov		#00h,XBNK	; Specifies the display RAM bank address (BANK0)
		br		next2
next1:
		st		b
		mov		#01h,XBNK	; Specifies the display RAM bank address (BANK1)
next2:

							; *** Calculating the RAM Address for a Specified Position on the Display ***
		ld		b			; b * 40h + c + 80h
		rol					;
		rol					;
		rol					;
		rol					;
		rol					;
		rol					;
		add		c			;
		add		#80h		;
		st		r2			; Stores the RAM address in r2

		ret					; locate end


put_chara:
		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selects data RAM bank 1

							; *** Calculating the Character Data Address ***
		rol					; (TRH,TRL) = acc*8 + fontdata
		rol					;
		rol					;
		add		#low(fontdata)	;
		st		TRL				;
		mov		#0,acc			;
		addc	#high(fontdata) ;
		st		TRH			;

		push	OCR			; Pushes the OCR value onto the stack
		mov		#osc_rc,OCR	; Specifies the system clock

		mov		#0,b		; Offset value for loading the character data
		mov		#4,c		; Loop counter
loop1:
		ld		b			; Loads the display data for the first line
		ldc					;
		inc		b			; Increments the load data offset by 1
		st		@r2			; Transfers the display data to display RAM
		ld		r2			; Adds 6 to the display RAM address
		add		#6			;
		st		r2			;

		ld		b			; Loads the display data for the second line
		ldc					;
		inc		b			; Increments the load data offset by 1
		st		@r2			; Transfers the display data to display RAM
		ld		r2			; Adds 10 to the display RAM address
		add		#10			;
		st		r2			;

		dec		c			; Decrements the loop counter
		ld		c			;
		bnz		loop1		; Repeats for 8 lines (four times)

		pop		OCR			; Pops the OCR value off of the stack
		pop		PSW			; Pops the PSW value off of the stack

		ret					; put_chara end


; *-------------------------------------------------------------------------*
; * Character Bit Image Data												*
; *-------------------------------------------------------------------------*
fontdata:
		db 07ch, 0e6h, 0c6h, 0c6h, 0c6h, 0ceh, 07ch, 000h		; '0' 00
		db 018h, 038h, 018h, 018h, 018h, 018h, 03ch, 000h		; '1' 01
		db 07ch, 0c6h, 0c6h, 00ch, 038h, 060h, 0feh, 000h		; '2' 02
		db 07ch, 0e6h, 006h, 01ch, 006h, 0e6h, 07ch, 000h		; '3' 03
		db 00ch, 01ch, 03ch, 06ch, 0cch, 0feh, 00ch, 000h		; '4' 04
		db 0feh, 0c0h, 0fch, 006h, 006h, 0c6h, 07ch, 000h		; '5' 05
		db 01ch, 030h, 060h, 0fch, 0c6h, 0c6h, 07ch, 000h		; '6' 06
		db 0feh, 0c6h, 004h, 00ch, 018h, 018h, 038h, 000h		; '7' 07
		db 07ch, 0c6h, 0c6h, 07ch, 0c6h, 0c6h, 07ch, 000h		; '8' 08
		db 07ch, 0c6h, 0c6h, 07eh, 006h, 00ch, 078h, 000h		; '9' 09

		db 07ch, 0e6h, 076h, 038h, 0dch, 0ceh, 07ch, 000h		; 'S' 0a
		db 0feh, 0c0h, 0c0h, 0f8h, 0c0h, 0c0h, 0feh, 000h		; 'E' 0b
		db 07ch, 0e6h, 0c0h, 0dch, 0c6h, 0e6h, 07ch, 000h		; 'G' 0c
		db 01eh, 036h, 066h, 0c6h, 0c6h, 0feh, 0c6h, 000h		; 'A' 0d


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
