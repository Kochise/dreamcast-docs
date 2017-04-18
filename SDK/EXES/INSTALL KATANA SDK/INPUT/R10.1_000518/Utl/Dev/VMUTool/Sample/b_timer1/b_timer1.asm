; Tab width = 4

;----------------------------------------------------------------------------
; ** Base Timer Interrupt Usage Sample 1 **
;
; ECounts base timer interrupts (every 0.5 seconds)
; EDisplays the counter value as a two digit decimal number on the LCD
;----------------------------------------------------------------------------
; 1.00 981208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	LC868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm
public	int_BaseTimer		; Symbol referenced from ghead.asm

extern	_game_end			; Symbol reference to ghead.asm


; **** Definition of System Constants ***************************************

							; OCR (Oscillation Control Register) settings
osc_rc		equ 081h		;  Specifies internal RC oscillation for the system clock
osc_xt		equ 082h		;  Specifies crystal oscillation for the system clock


; *** Data Segment **********************************************************

		dsezz				; Data segment start

r0:		ds		1			; Indirect addressing register r0
r1:		ds		1			; Indirect addressing register r1
r2:		ds		1			; Indirect addressing register r2
r3:		ds		1			; Indirect addressing register r3
		ds		12			; Other registers reserved for the system

counter: ds		1			; Base timer interrupt counter
work1:	ds		1			; For work (put2digit)


; *** Code Segment **********************************************************

		cseg				; Code segment start

; *-------------------------------------------------------------------------*
; * User program															*
; *-------------------------------------------------------------------------*
main:
		mov		#0,counter	; Resets the counter value

		call	cls			; Clears the LCD display image

loop0:
		mov		#2,c		; Display position (horizontal)
		mov		#1,b		; Display position (vertical)
		ld		counter		; Moves the counter value to acc
		call	put2digit	; Displays the acc value (two digits)

		set1	pcon,0		; Waits in HALT mode until the next interrupt

							; ** [M] (mode) Button Check **
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		br		loop0		; Repeat

finish:						; ** Application End Processing **
		jmp		_game_end	; Application end


; *-------------------------------------------------------------------------*
; * Displaying a Two-digit Value											*
; * Inputs: acc:	Numeric value											*
; *			  c:	Horizontal position of character						*
; *			  b:	Vertical position of character							*
; *-------------------------------------------------------------------------*
put2digit:
		push	b			; Pushes the coordinate data onto the stack
		push	c			;
		st		c			; Calculates the tens digit and the ones digit
		xor		a			; ( acc = acc/10, work1 = acc mod 10 )
		mov		#10,b		;
		div					;
		ld		b			;
		st		work1		; Stores the ones digit in work1
		ld		c			;
		pop		c			; Pops the coordinate values into (c, b)
		pop		b			;
		push	b			; Pushes the coordinates onto the stack again
		push	c			;
		call	putch		; Displays the tens digit
		ld		work1		; Loads the ones digit
		pop		c			; Pops the coordinate values into (c, b)
		pop		b			;
		inc		c			; Moves the display coordinates to the right
		call	putch		; Displays the ones digit

		ret					; put2digit end


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

cls_s:						; Clearing One Bank of Display RAM
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
		mov		#osc_rc,OCR ; Specifies the system clock

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


; *-------------------------------------------------------------------------*
; * Base Timer Interrupt Handler											*
; *-------------------------------------------------------------------------*
int_BaseTimer:
		push	acc			; Pushes the register that was used onto the stack
		inc		counter		; Increments the counter
		ld		counter		; If the counter reaches 100...
		bne		#100,next3	;
		mov		#0,counter	; Resets the counter
next3:						;
		pop		acc			; Pops the register back off of the stack

		ret					; (User) interrupt processing end


