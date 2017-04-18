; Tab width = 4

;----------------------------------------------------------------------------
; ** Button Status Detection Sample 1 **
;
; ÅEReads the button statuses and displays the button that is being pressed on the LCD
;----------------------------------------------------------------------------
; 1.00 981208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	LC868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm

extern	_game_end			; Symbol reference to ghead.asm


; **** Definition of System Constants ***************************************

							; OCR (Oscillation Control Register) settings
osc_rc		equ 04dh		; Specifies internal RC oscillation for the system clock
osc_xt		equ 0efh		; Specifies crystal oscillation for the system clock


; *** Data Segment **********************************************************

		dseg				; Data segment start

r0		ds		1			; Indirect addressing register r0
r1		ds		1			; Indirect addressing register r1
r2		ds		1			; Indirect addressing register r2
r3		ds		1			; Indirect addressing register r3
		ds		12			; Other registers reserved for the system

; *** Code Segment **********************************************************

		cseg				; Code segment start

; *-------------------------------------------------------------------------*
; * User program															*
; *-------------------------------------------------------------------------*
main:
		call	cls			; Clears the LCD display image

		mov		#0ffh,P3	; P3 initialization (pull-up setting)

loop0:
							; ** [A] Button Check **
		mov		#0,b
		ld		P3			; Loads the status of P3
		bp		acc,4,next3	; next3 if [A] button is being pressed
		mov		#1,b		; Display character code 'A'
next3:
		ld		b
		mov		#4,c		; Display coordinate (horizontal)
		mov		#3,b		; Display coordinate (vertical)
		call	putch		; Displays single character

							; ** [B] Button Check **
		mov		#0,b
		ld		P3
		bp		acc,5,next4	; next4 if [B] button is being pressed
		mov		#2,b		; Display character code 'B'
next4:
		ld		b
		mov		#5,c
		mov		#2,b
		call	putch

							; ** [-] Button Check **
		mov		#0,b
		ld		P3
		bp		acc,0,next5	; next5 if [-] button is being pressed
		mov		#3,b		; Display character code '-'
next5:
		ld		b
		mov		#1,c
		mov		#1,b
		call	putch

							; ** [R] Button Check **
		mov		#0,b
		ld		P3
		bp		acc,3,next6	; next6 if [R] button is being pressed
		mov		#4,b		; Display character code 'R'
next6:
		ld		b
		mov		#2,c
		mov		#2,b
		call	putch

							; ** [ÅP] Button Check **
		mov		#0,b
		ld		P3
		bp		acc,1,next7	; next7 if [ÅP] button is being pressed
		mov		#5,b		; Display character code 'ÅP'
next7:
		ld		b
		mov		#1,c
		mov		#3,b
		call	putch

							; ** [] Button Check **
		mov		#0,b
		ld		P3
		bp		acc,2,next8	; next8 if [] button is being pressed
		mov		#6,b		; Display character code ''
next8:
		ld		b
		mov		#0,c
		mov		#2,b
		call	putch

							; ** [S] Button Check **
		mov		#0,b
		ld		P3
		bp		acc,7,next9	; next9 if [S] button is being pressed
		mov		#8,b		; Display character code 'S'
next9:
		ld		b
		mov		#4,c
		mov		#1,b
		call	putch

							; ** [M] Button Check **
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		brf		loop0		; Repeat

finish:						; ** Application End Processing **
		jmp		_game_end	; Application end


; *-------------------------------------------------------------------------*
; * Clearing the LCD Display Image											*
; *-------------------------------------------------------------------------*
cls:
		push	OCR			; Pushes the OCR value onto the stack
		mov		#osc_rc,OCR	; Specifies the system clock

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
; * Inputs: acc:	Character code											*
; *			  c:	Horizontal position of character						*
; *			  b:	Vertical position of character							*
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
		bn		PSW,7,next1	;

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
		db 000h, 000h, 038h, 038h, 038h, 000h, 000h, 000h		; 'ÅE' 00
		db 01eh, 036h, 066h, 0c6h, 0c6h, 0feh, 0c6h, 000h		; 'A' 01
		db 0fch, 066h, 066h, 07ch, 066h, 066h, 0fch, 000h		; 'B' 02

		db 010h, 038h, 07ch, 0feh, 038h, 038h, 038h, 000h		; '-' 03
		db 010h, 018h, 0fch, 0feh, 0fch, 018h, 010h, 000h		; 'R' 04
		db 038h, 038h, 038h, 0feh, 07ch, 038h, 010h, 000h		; 'ÅP' 05
		db 010h, 030h, 07eh, 0feh, 07eh, 030h, 010h, 000h		; '' 06

		db 0c6h, 0eeh, 0feh, 0d6h, 0c6h, 0c6h, 0c6h, 000h		; 'M' 07
		db 07ch, 0e6h, 076h, 038h, 0dch, 0ceh, 07ch, 000h		; 'S' 08
		

