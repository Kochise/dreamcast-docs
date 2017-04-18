; Tab width = 4

;----------------------------------------------------------------------------
; ** LCD display processing sample 1 **
;
; Transfers data to display RAM and displays a simple pattern on the display
;----------------------------------------------------------------------------
; 1.00 981208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	Lc868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm

extern	_game_end			; Application end


; **** Definition of System Constants ***************************************

							; OCR (Oscillation Control Register) settings
osc_rc		equ 081h 		; Specifies internal RC oscillation for the System clock
osc_xt		equ 082h		; Specifies crystal oscillation for the system Clock


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
		mov		#0f0h,c		; Display data
		call	matrix		; Display pattern on the LCD
		set1	PCON,0		; Enters HALT mode and waits for an interrupt.
							; HALT mode is cancelled and processing continues
							; when a base timer interrupt is generated.

		mov		#00fh,c		; The following lines display different patterns in the same manner
		call	matrix
		set1	PCON,0

		mov		#0cch,c
		call	matrix
		set1	PCON,0

		mov		#033h,c
		call	matrix
		set1	PCON,0

		mov		#055h,c
		call	matrix
		set1	PCON,0

		mov		#0aah,c
		call	matrix
		set1	PCON,0

							; ** [M] (mode) Button Check **
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		jmp		main		; Repeat

finish:						; ** Application End Processing **
		jmp		_game_end	; Application end


; *-------------------------------------------------------------------------*
; * Displays pattern on entire LCD											*
; * Input	c: Basic display pattern										*
; *-------------------------------------------------------------------------*
matrix:						; **** Draws one LCD screen ****

		push	acc			; Pushes each register onto the stack
		push	b
		push	c
		push	XBNK

xb0_a:	mov		#000h,XBNK	; Specifies the display RAM bank address (BANK0)
		mov		#080h,b

la1:	ld		c			; c: Display data
		call	line2		; 2-line display
		ld		b			; Advances address two lines ahead
		add		#010h		;
		st		b			;
		bnz		la1			; Repeats until end of bank is reached

xb1_a:	mov		#001h,XBNK	; Specifies the display RAM bank address (BANK1)
		mov		#080h,b

la2:	ld		c			; c: Display data
		call	line2		; 2-line display
		ld		b			; Advances address two lines ahead
		add		#010h		;
		st		b			;
		bnz		la2			; Repeats until end of bank is reached

		pop		XBNK		; Pops the registers from the stack
		pop		c
		pop		b
		pop		acc

		ret					; Matrix end


line2:						; **** LCD 2-line display ****

		push	acc			; Pushes each register onto the stack
		push	b			;
		push	c			;
		push	PSW			;
		push	OCR			;
		mov		#osc_rc,OCR ; Specifies the system clock
		set1	PSW,1		; Selects data RAM bank 1
		st		c			; Stores display data in c
		ld		b			; Sets the display RAM address in r2
		st		r2			;

lp1:						; **** First line display processing ****
		ld		c			; Transfers the display data to display RAM
		st		@r2			;
		inc		r2			; Advances the address to the next display position
		ld		r2
		and		#00fh		; If the display position is not at the right end of the first line...
		xor		#006h		;
		bnz		lp1			; ...repeat

		ld		c			; Inverts the bit pattern in the c register
		xor		#0ffh		;
		st		c			;

lp2:						; **** Second line display processing ****
		ld		c			; Transfers the display data to display RAM
		st		@r2			;
		inc		r2			; Advances the address to the next display position
		ld		r2			;
		and		#00fh		; If the display position is not at the right end of the second line...
		xor		#00ch		;
		bnz		lp2			; ...repeat

		pop		OCR			; Pops registers off of the stack
		pop		PSW			;
		pop		c			;
		pop		b			;
		pop		acc			;

		ret					; line2 end

		end
