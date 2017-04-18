; Tab width = 4

;----------------------------------------------------------------------------
; ** Serial Communications Sample 2 (Data Reception) **
;
; EDisplays a numeric value that was received from the serial communications port on the LCD
;----------------------------------------------------------------------------
; 1.01 990208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	LC868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm

extern	_game_end			; Application end


; **** Definition of System Constants ***************************************

							; OCR (Oscillation Control Register) settings
osc_rc		equ 04dh		;  Specifies internal RC oscillation for the system clock
osc_xt		equ 0efh		;  Specifies crystal oscillation for the system clock

LowBattChk	equ 06eh		; Low battery detection flag (RAM bank 0)


; *** Data Segment **********************************************************

		dseg				; Data segment start

r0:		ds		1			; Indirect addressing register r0
r1:		ds		1			; Indirect addressing register r1
r2:		ds		1			; Indirect addressing register r2
r3:		ds		1			; Indirect addressing register r3
		ds		12			; Other registers

counter: ds		1			; Counter
work1:	ds		1			; Work (used in put2digit)


; *** Code Segment **********************************************************

		cseg				; Code segment start

; *-------------------------------------------------------------------------*
; * User program															*
; *-------------------------------------------------------------------------*
main:
		call	cls			; Clears the LCD display
		call	BattChkOff	; Turns off the low battery automatic detection function

cwait:
		call	SioInit		; Serial communications initialization
		bz		start		; Starts if VM is connected

		ld		P3			; [M] button check
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		jmp		cwait		; Waits until VM is connected
start:

loop0:
		call	SioRecv1	; Receives one byte
		bnz		next4		; If there is no received data, then goes to next4

		ld		b			; Loads the received data into acc
		mov		#2,c		; Display coordinates (horizontal)
		mov		#1,b		; Display coordinates (vertical)
		call	put2digit	; Displays the two-digit value on the LCD

next4:						; ** [M] (mode) Button Check **
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		jmp		loop0		; Repeat

finish:						; ** Application End Processing **
		call	SioEnd		; Serial communications end processing
		call	BattChkOn	; Turns on the low battery automatic detection function
		jmp		_game_end	; Application end

; *-------------------------------------------------------------------------*
; * Serial Communications Initialization									*
; * Outputs:	acc = 0   : Normal end										*
; *			acc = 0ffh: VM not connected									*
; *-------------------------------------------------------------------------*
; Serial communications initialization
; This sample assumes that the system clock is in crystal mode.
SioInit:
							; **** VM Connection Check ****
		ld		P7			; Checks the connection status
		and		#%00001101	; Checks P70, P72, P73
		sub		#%00001000	; P70 = 0, P72 = 0, P73 = 1
		bz		next3		; To next3 if connected

		mov		#0ffh,acc	; If not connected, abnormal end with acc = 0ffh
		ret					; SioInit end
next3:

							; **** Serial Communications Initialization ****
		mov		#0,SCON0	; Specifies output as 'LSB first'
		mov		#0,SCON1	; Specifies input as 'LSB first'
		mov		#088h,SBR	; Sets the transfer rate
		clr1	P1,0		; Clears the P10 latch (P10/S00)
		clr1	P1,2		; Clears the P12 latch (P12/SCK0)
		clr1	P1,3		; Clears the P13 latch (P13/S01)

		mov		#%00000101,P1FCR ; Sets the pin functions
		mov		#%00000101,P1DDR ; Sets the pin functions

		mov		#0,SBUF0	; Clears the transfer buffer
		mov		#0,SBUF1	; Clears the transfer buffer

		ret					; SioInit end


; *-------------------------------------------------------------------------*
; * Serial Communications End												*
; *-------------------------------------------------------------------------*
SioEnd:						; **** Serial Communications End Processing ****

		mov		#0,SCON0	; SCON0 = 0
		mov		#0, SCON1	; SCON1 = 0
		mov		#0bfh,P1FCR	; P1FCR = 0bfh
		mov		#0a4h,P1DDR	; P1DDR = 0a4h

		ret					; SioEnd end


; *-------------------------------------------------------------------------*
; * Receiving 1 Byte from a Serial port										*
; *  Outputs: b: Received data												*
; *			 acc = 0    : Received data found								*
; *			 acc = 0ffh: Received data not found							*
; *-------------------------------------------------------------------------*
SioRecv1:					; **** Receiving 1 Byte ****
		ld		SCON1
		bp		acc,1,next5	; If received data is found, then go to next5
		bp		acc,3,next6	; If transfer is currently in progress, then go to next6

		set1	SCON1,3		; Starts transfer
next6:
		mov		#0ffh,acc	; Returns with acc = 0ffh (received data not found)
		ret					; SioRecv1 end
next5:

		ld		SBUF1		; Loads the received data
		st		b			; Copies the data into b

		clr1	SCON1,1		; Resets the transfer end flag

		mov		#0,acc		; Returns with acc = 0 (received data found)
		ret					; SioRecv1 end


; *-------------------------------------------------------------------------*
; * Displaying a two-digit value											*
; * Inputs: acc: Numeric value												*
; *			  c: Horizontal position of character							*
; *			  b: Vertical position of character								*
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


; *-------------------------------------------------------------------------*
; * Low Battery Automatic Detection Function ON								*
; *-------------------------------------------------------------------------*
BattChkOn:
		push	PSW			; Pushes the PSW value onto the stack

		clr1	PSW,1		; Selects data RAM bank 0
		mov		#0,acc		; Detects low battery (0)
		st		LowBattChk	; Low battery automatic detection flag (RAM bank 0)

		pop		PSW			; Pops the PSW value off of the stack
		ret					; BattChkOn end


; *-------------------------------------------------------------------------*
; * Low Battery Automatic Detection Function OFF							*
; *-------------------------------------------------------------------------*
BattChkOff:
		push	PSW			; Pushes the PSW value onto the stack

		clr1	PSW,1		; Selects data RAM bank 0
		mov		#0ffh,acc	; Does not detect low battery (0ffh)
		st		LowBattChk	; Low battery automatic detection flag (RAM bank 0)

		pop		PSW			; Pops the PSW value off of the stack
		ret					; BattChkOff end

