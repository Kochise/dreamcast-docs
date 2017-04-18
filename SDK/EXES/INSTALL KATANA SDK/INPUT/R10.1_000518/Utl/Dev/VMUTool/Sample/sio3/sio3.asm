; Tab width = 4

;----------------------------------------------------------------------------
; ** Serial Communications Sample 3 (Interrupt-Driven Serial Driver with Reception Buffer) **
;
; EDemonstrates the usage of a serial communications driver with a 16-byte reception buffer
; EDisplays the received data values
; ESends simple data on a regular cycle
;----------------------------------------------------------------------------
; 1.01 990208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	LC868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm
public	int_BaseTimer		; Symbol referenced from ghead.asm
public	int_SioRx			; Symbol referenced from ghead.asm

extern	_game_end			; Application end


; **** Definition of System Constants **********************************

							; OCR (Oscillation Control Register) settings
osc_rc			equ 04dh	;  Specifies internal RC oscillation for the system clock
osc_xt			equ 0efh	;  Specifies crystal oscillation for the system clock

LowBattChk		equ 06eh	; Low battery detection flag (RAM bank 0)

SioRxCueSize	equ 16		; Serial communications buffer size


; *** Data Segment *****************************************************

		dseg				; Data segment start

r0:		ds		1			; Indirect addressing register r0
r1:		ds		1			; Indirect addressing register r1
r2:		ds		1			; Indirect addressing register r2
r3:		ds		1			; Indirect addressing register r3
		ds		12			; Other registers

							; ** For Serial Driver **
SioRxCueBehind: ds	1		; Amount of received data waiting
SioRxCueRPnt:	ds	1		; Reception buffer reading point
SioRxCueWPnt:	ds	1		; Reception buffer writing point
SioRxCue:		ds	SioRxCueSize ; Reception buffer
SioOverRun:		ds	1		; Reception overrun flag

							; ** Work Areas for Usage Sample **
bcount: ds		1			; Base clock counter
work1:	ds		1			; Work 1
work2:	ds		1			; Work 2

work0:	ds		1			; Work (put2digit)


; *** Code Segment **********************************************************

		cseg				; Code segment start

; *-------------------------------------------------------------------------*
; * Serial Communications Driver Usage Sample								*
; * Sends simple data at a regular interval									*
; * Displays the received data values on the LCD							*
; *-------------------------------------------------------------------------*
main:
		mov		#0,bcount
		mov		#0,work1		; Initial value of transmission data
		clr1	P3INT,0			; Masks P3 interrupts
		call	cls				; Clears the LCD
		call	BattChkOff		; Turns off the low battery automatic detection function
		call	SioInit			; Serial communications initialization
		bnz		finish			; Ends if VM is not connected

stlp1:
								; *** Displaying If Data Has Been Received ***
		call	SioGet1			; 1-byte reception
		be		#0ffh,stnx1		; Skip if no data has been received
		bz		stnx3			; If normal received data is found, go to stnx3
error:	br		finish			; Forcibly terminate if an error is detected
stnx3:
		ld		b				; Load received data from b -> acc
		mov		#0,c			; Display coordinate (horizontal)
		mov		#0,b			; Display coordinate (vertical)
		call	put2digit		; Displays numeric value on the LCD
		br		stlp1			; Continues to repeat as long as there is received data
stnx1:							;

		set1	pcon,0			; Waits until next interrupt

								; *** Sending Simple Data at a Regular Interval ***
		ld		bcount			; Base timer counter value
		be		work2,stnx4		; Does not send if unchanged
		st		work2			; Updates work2

		ld		work1			; Loads the transmission data
		call	SioPut1			; Sends

		inc		work1			; Updates the transmission data
		ld		work1			; (Sends values form 0 to 99, in sequence)
		bne		#100,stnx2		;
		mov		#0,work1		;
stnx2:							;
stnx4:

								; ** [M] (mode) Button Check **
		ld		P3
		bn		acc,6,finish	; If the [M] button is pressed, the application ends

		jmp		stlp1			; Repeat

finish:							; ** Application End Processing **
		call	SioEnd			; Serial communications end processing
		call	BattChkOn		; Turns on the low battery automatic detection function
		jmp		_game_end		; Application end

; *=========================================================================*
; ***** Simple Serial Communications Driver								*****
; *=========================================================================*

; *-------------------------------------------------------------------------*
; * Serial communications initialization									*
; *																			*
; * This sample assumes that the system clock is in crystal mode.			*
; *-------------------------------------------------------------------------*
SioInit:
									; **** VM Connection Check ****
		ld		P7					; Checks the connection status
		and		#%00001101			; Checks P70, P72, P73
		be		#%00001000,next3	; P70 = 0, P72 = 0, P73 = 1
									; To next3 if connected
		mov		#0ffh,acc			; If not connected, abnormal end with acc = 0ffh
		ret							; SioInit end
next3:

									; **** Serial Communications Initialization ****
		mov		#0,SCON0			; Specifies output as 'LSB first'
		mov		#0,SCON1			; Specifies input as 'LSB first'
		mov		#0ddh,SBR			; Sets the transfer rate
		clr1	P1,0				; Clears the P10 latch (P10/S00)
		clr1	P1,2				; Clears the P12 latch (P12/SCK0)
		clr1	P1,3				; Clears the P13 latch (P13/S01)

		mov		#%00000101,P1FCR	; Sets the pin functions
		mov		#%00000101,P1DDR	; Sets the pin functions

		mov		#0,SBUF0			; Clears the transfer buffer
		mov		#0,SBUF1			; Clears the transfer buffer

		mov		#0,acc
		st		SioRxCueBehind		; Resets amount of received data waiting
		st		SioRxCueRPnt		; Reception buffer reading point
		st		SioRxCueWPnt		; Reception buffer writing point
		st		SioOverRun			; Resets reception overrun flag

		set1	SCON1,0				; Receiving side transfer end interrupt enable
		set1	SCON1,3				; Receiving standby

		ret							; SioInit end


; *-------------------------------------------------------------------------*
; * Serial Communications End												*
; *-------------------------------------------------------------------------*
SioEnd:								; **** Serial Communications End Processing ****

		mov		#0,SCON0			; SCON0 = 0
		mov		#0, SCON1			; SCON1 = 0
		mov		#0bfh,P1FCR			; P1FCR = 0bfh
		mov		#0a4h,P1DDR			; P1DDR = 0a4h

		ret							; SioEnd end


; *-------------------------------------------------------------------------*
; * Sending 1 Byte															*
; *																			*
; * Inputs: acc: Transmission data											*
; *-------------------------------------------------------------------------*
SioPut1:
		push	acc					; Pushes the transmission data onto the stack
splp1:	ld		SCON0				; Waits until any previous transfer is completed
		bp		acc,3,splp1			;
		pop		acc					; Pops the transmission data off of the stack

		st		SBUF0				; Sets the data to be transferred
		set1	SCON0,3				; Starts sending

		ret							; SioPut1 end


; *-------------------------------------------------------------------------*
; * Reading 1 Byte from the Reception Buffer (Asynchronous Reception)		*
; *																			*
; * Outputs: acc: 0 = Normal end											*
; *				 0ffh = No received data									*
; *				 0feh = Buffer overflow										*
; *				 0fdh = Overrun error										*
; *			   b: Received data (Valid only in the case of normal end.)		*
; *-------------------------------------------------------------------------*
SioGet1:
									; ** Waiting Data Amount check	**
		ld		SioRxCueBehind		; Waiting amount of data
		bnz		sgnx1				; When waiting amount != 0
		mov		#0ffh,acc			; When waiting amount == 0
		ret							;  Returns when acc = 0ffh (no received data)
sgnx1:
									; ** Buffer Overflow Detection **
									; SioRxCueBehind - SioRxCueSize
		be		#SioRxCueSize,sgnx3	; SioRxCueBehind == SioRxCueSize
		bp		PSW,7,sgnx3			; SioRxCueBehind < SioRxCueSize
									; SioRxCueBehind > SioRxCueSize
		mov		#0feh,acc			; When the buffer capacity has been exceeded
		ret							;  Return when acc = 0feh (buffer overflow)
sgnx3:
									; ** Overrun Error Detection **
		ld		SioOverRun			; Overrun flag
		bz		sgnx4				; Not detected
		mov		#0fdh,acc			; Detected
		ret							;  Return when acc = 0fdh (overrun error)
sgnx4:

		dec		SioRxCueBehind		; dec waiting amount

									; ** Calculating the received data reading point
		ld		SioRxCueRPnt		; r0 = SioRxCue + SioRxCueRPnt
		add		#SioRxCue ;
		st		r0					;

		inc		SioRxCueRPnt		; inc data reading point

									; ** If reading point = buffer size,
									; ** then reading point is reset to 0
		ld		SioRxCueRPnt
		bne		#SioRxCueSize,sgnx2	; When SioRxCueRPnt != SioRxCueSize
		mov		#0,SioRxCueRPnt		; When SioRxCueRPnt == SioRxCueSize
sgnx2:

		ld		@r0					; Loads the input data into acc
		st		b					; Stores the value in b
		mov		#0,acc				; acc = acc = 0 (normal end, data exists)

		ret							; SioGet1 end


; *-------------------------------------------------------------------------*
; * Reading 1 Byte from the Reception Buffer								*
; * (If there is no received data, this routine waits until data is received)*
; *																			*
; * Outputs: acc: 0 = Normal end											*
; *				  0feh = Buffer overflow									*
; *				  0fdh = Overrun error										*
; *			   b: Received data (Valid only in the case of normal end.)		*
; *-------------------------------------------------------------------------*
SioGet1W:
		call	SioGet1				; Asynchronous reception
		be		#0ffh,SioGet1W		; Waits until data is received

		ret							; SioGet1W end


; *-------------------------------------------------------------------------*
; * Getting the Amount of Data Waiting in the Reception Buffer				*
; *																			*
; * Output: acc: Amount of data (bytes)										*
; *-------------------------------------------------------------------------*
SioGetRxLen:
		ld		SioRxCueBehind		; Amount waiting

		ret							; SioGetRxLen end


; *-------------------------------------------------------------------------*
; * SIO Reception Interrupt Handler											*
; *-------------------------------------------------------------------------*
int_SioRx:
		push	acc					; Pushes the register to be used onto the stack
		push	PSW					;
		set1	PSW,1				; Selects data RAM bank 1
		push	r0					; Pushes the register onto the stack

									; ** Calculating the Writing Point **
		ld		SioRxCueWPnt		; r0 = SioRxCue + SioRxCueWPnt
		add		#SioRxCue			;
		st		r0					;

		ld		SBUF1				; Loads the received data
		st		@r0					; Writes the data to the buffer

		inc		SioRxCueWPnt		; Writing point ++

									; ** Resets the writing point once it
									; ** reaches the buffer size
		ld		SioRxCueWPnt		;
		bne		#SioRxCueSize,isnx1	;
		mov		#0,SioRxCueWPnt		;
isnx1:

		inc		SioRxCueBehind		; Data Waiting Amount ++

		clr1	SCON1,1				; Resets the transfer end flag

									; ** Checking the Overrun Error **
		bn		SCON1,6,isnx2		; If an overrun has not occurred, then isnx2
		mov		#1,SioOverRun		; If an overrun has occurred -> Sets flag
		clr1	SCON1,6				; Resets overrun flag
isnx2:

		set1	SCON1,3				; Starts the next transfer

		pop		r0					; Pops the register to be used off of the stack
		pop		PSW					;
		pop		acc					;

		reti						; int_SioRx end


; *-------------------------------------------------------------------------*
; * Displaying a Two-digit Value											*
; * Inputs: acc: Numeric value												*
; *			  c: Horizontal position of character							*
; *			  b: Vertical position of character								*
; *-------------------------------------------------------------------------*
put2digit:
		push	b			; Pushes the coordinate data onto the stack
		push	c			;
		st		c			; Calculates the tens digit and the ones digit
		xor		a			; ( acc = acc/10, work0 = acc mod 10 )
		mov		#10,b		;
		div					;
		ld		b			;
		st		work0		; Stores the ones digit in work0
		ld		c			;
		pop		c			; Pops the coordinate values into (c, b)
		pop		b			;
		push	b			; Pushes the coordinates onto the stack again
		push	c			;
		call	putch		; Displays the tens digit
		ld		work0		; Loads the ones digit
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
; *	Displaying One Character in a Specified Position						*
; *	Inputs: acc: Character code												*
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


locate:	; **** Calculating the Display RAM Address According to the Display Position Specification ****
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
		rol ;
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
		addc	#high(fontdata)	;
		st		TRH				;

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
		db 07ch, 0e6h, 0c6h, 0c6h, 0c6h, 0ceh, 07ch, 000h		; 0
		db 018h, 038h, 018h, 018h, 018h, 018h, 03ch, 000h		; 1
		db 07ch, 0c6h, 0c6h, 00ch, 038h, 060h, 0feh, 000h		; 2
		db 07ch, 0e6h, 006h, 01ch, 006h, 0e6h, 07ch, 000h		; 3
		db 00ch, 01ch, 03ch, 06ch, 0cch, 0feh, 00ch, 000h		; 4
		db 0feh, 0c0h, 0fch, 006h, 006h, 0c6h, 07ch, 000h		; 5
		db 01ch, 030h, 060h, 0fch, 0c6h, 0c6h, 07ch, 000h		; 6
		db 0feh, 0c6h, 004h, 00ch, 018h, 018h, 038h, 000h		; 7
		db 07ch, 0c6h, 0c6h, 07ch, 0c6h, 0c6h, 07ch, 000h		; 8
		db 07ch, 0c6h, 0c6h, 07eh, 006h, 00ch, 078h, 000h		; 9


; *-------------------------------------------------------------------------*
; * Low Battery Automatic Detection Function ON								*
; *-------------------------------------------------------------------------*
BattChkOn:
		push	PSW					; Pushes the PSW value onto the stack
		clr1	PSW,1				; Selects data RAM bank 0

		mov		#0,LowBattChk		; Detects low battery (0)

		pop		PSW					; Pops the PSW value off of the stack
		ret							; BattChkOn end


; *-------------------------------------------------------------------------*
; * Low Battery Automatic Detection Function OFF							*
; *-------------------------------------------------------------------------*
BattChkOff:
		push	PSW					; Pushes the PSW value onto the stack
		clr1	PSW,1				; Selects data RAM bank 0

		mov		#0ffh,LowBattChk	; Does not detect low battery (0ffh)

		pop		PSW					; Pops the PSW value off of the stack
		ret							; BattChkOff end


; *-------------------------------------------------------------------------*
; * Base Timer Interrupt Handler											*
; *-------------------------------------------------------------------------*
int_BaseTimer:
		clr1	btcr,1				; Clears the base timer interrupt source
		inc		bcount				; Counter ++
		ret							; User interrupt processing end


