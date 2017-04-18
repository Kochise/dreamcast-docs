; Tab width = 4

;----------------------------------------------------------------------------
; ** Serial Communications Sample 1 (Data Transmission) **
;
; ÅESends simple data through the serial communications port on a regular cycle
;----------------------------------------------------------------------------
; 1.01 990208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	LC868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm
public	int_BaseTimer		; Symbol referenced from ghead.asm

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


; *** Code Segment **********************************************************

		cseg				; Code segment start

; *-------------------------------------------------------------------------*
; * User program															*
; *-------------------------------------------------------------------------*
main:
		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selects data RAM bank 1

		call	BattChkOff	; Turns off the low battery automatic detection function

cwait:
		call	SioInit		; Serial communications initialization
		bz		start		; Starts if VM is connected

		ld		P3			; [M] button check
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		jmp		cwait		; Waits until VM is connected
start:

		set1	pcon,0		; Waits in HALT mode until next interrupt (0.5 seconds)

		mov		#0,counter	; Resets the counter value to "0"
loop0:
		ld		counter		; Loads the counter value

		call	SioSend1	; Sends one byte

		set1	pcon,0		; Waits in HALT mode until next interrupt (0.5 seconds)

							; [M] (mode) Button Check
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		jmp		loop0		; Repeat

finish:						; ** Application End Processing **
		call	SioEnd		; Serial communications end processing
		call	BattChkOn	; Turns on the low battery automatic detection function
		pop		PSW			; Pops the PSW value off of the stack
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
		bz		next2		; To next2 if connected

		mov		#0ffh,acc	; If not connected, abnormal end with acc = 0ffh
		ret					; SioInit end
next2:

							; **** Serial Communications Initialization ****
		mov		#0,SCON0	; Specifies output as 'LSB first'
		mov		#0,SCON1	; Specifies input as 'LSB first'
		mov		#0ddh,SBR	; Sets the transfer rate
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
		mov		#0,SCON1	; SCON1 = 0
		mov		#0bfh,P1FCR	; P1FCR = 0bfh
		mov		#0a4h,P1DDR	; P1DDR = 0a4h

		ret					; SioEnd end


; *-------------------------------------------------------------------------*
; * Sending 1 Byte from a Serial Port										*
; *   Inputs: acc: Transmission data										*
; *-------------------------------------------------------------------------*
SioSend1:					; **** Sending 1 Byte ****

		push	acc			; Pushes the transmission data onto the stack

sslp1:	ld		SCON0		; Waits, if the previous data is still being sent
		bp		acc,3,sslp1	;

		pop		acc			; Pops the transmission data off of the stack

		st		SBUF0		; Sets the data to be transferred
		set1	SCON0,3		; Starts sending

		ret					; SioSend1 end


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


; *-------------------------------------------------------------------------*
; * Base Timer Interrupt Handler											*
; *-------------------------------------------------------------------------*
int_BaseTimer:
		push	PSW			; Pushes the PSW value onto the stack
		push	acc

		set1	PSW,1		; Selects data RAM bank 1

		inc		counter		; Increments the counter

		ld		counter		; If the counter value is:
		bne		#100,next1	; not 100, then next1
		mov		#0,counter	; 100, then reset to '0'
next1:
		pop		acc
		pop		PSW			; Pops the PSW value off of the stack

		clr1	BTCR,1		; Clears the base timer interrupt source
		ret					; User interrupt processing end


