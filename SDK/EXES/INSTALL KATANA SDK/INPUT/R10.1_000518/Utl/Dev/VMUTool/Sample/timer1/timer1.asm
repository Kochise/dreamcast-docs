; Tab width = 4

;----------------------------------------------------------------------------
; ** Timer/Counter T0 Interrupt Usage Sample 1 **
;
; ÅEIntermittently sounds the buzzer (every two seconds)
;----------------------------------------------------------------------------
; 1.00 981208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	LC868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm
public	int_T0H				; Symbol referenced from ghead.asm

extern	_game_end			; Application end


; **** Definition of System Constants ***************************************

							; OCR (Oscillation Control Register) settings
osc_rc		equ 04dh		;  Specifies internal RC oscillation for the system clock
osc_xt		equ 0efh		;  Specifies crystal oscillation for the system clock


; *** Data Segment **********************************************************

		dseg				; Data segment start

r0:		ds		1			; Indirect addressing register r0
r1:		ds		1			; Indirect addressing register r1
r2:		ds		1			; Indirect addressing register r2
r3:		ds		1			; Indirect addressing register r3
		ds		12			; Other registers reserved for the system

counter: ds		1			; Timer interrupt counter


; *** Code Segment **********************************************************

		cseg				; Code segment start

; *-------------------------------------------------------------------------*
; * User program															*
; *-------------------------------------------------------------------------*
main:
		call	SndInit		; Sound output initialization
		call	T0Mode2Init	; Timer T0 initialization
		mov		#0,counter	; Clears counter

loop0:
		ld		counter		; Loads the counter value
		bp		acc,1,next1	; next1 if bit 0 of the counter is "1"

		call	Snd2Start	; Starts sound
		br		next2
next1:
		call	SndStop		; Stops sound
next2:
		set1	PCON,0		; HALT mode until next interrupt


							; ** [M] (mode) Button Check **
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		br		loop0		; Repeat

finish:						; ** Application End Processing **
		jmp		_game_end	; Application end


; *-------------------------------------------------------------------------*
; * Timer/Counter T0 Initialization											*
; *   Applied an interrupt about once per second in mode 2 (16-bit counter)	*
; *-------------------------------------------------------------------------*
T0Mode2Init:
		mov		#255,T0PRR	; Sets the prescaler value
							;  Since this is an 8-bit prescaler:
							;  Cycle = (256-255) * 0.000183 = 0.000183 (sec.)
		mov		#high(65536-5464),T0HR ; Sets preset value (H)
		mov		#low(65536-5464),T0LR	; Sets preset value (L)
							;  As a set with the prescaler:
							;  0.000183 * 5464 = 0.999912 (Å‚1sec)
							;  An overflow occurs about once per second
		mov		#0ffh,T0L	; Sets up an immediate initial overflow
		mov		#0ffh,T0H	;
		mov		#0e4h,T0CNT	; Mode 2 (16-bit counter)
							; Generates an interrupt according to the T0H overflow
							; T0 operation start

		ret					; T0Mode2Init end


T0HStop:					; *** T0H timer stop ***

		clr1	T0CNT,7		; T0H count operation stop
		ret


; *-------------------------------------------------------------------------*
; * Timer T0H Interrupt Handler												*
; *-------------------------------------------------------------------------*
int_T0H:					; *** T0H Interrupt Handler ***
		inc		counter

		clr1	T0CNT,3		; Clears the timer T0H interrupt source
		reti


; *-------------------------------------------------------------------------*
; * Sound Output-related Routines											*
; *-------------------------------------------------------------------------*
SndInit:					; *** Sound Output Hardware Initialization ***
		clr1	P1,7		; Sets the sound output port

		ret

Snd1Start:					; *** Start of 342Hz Tone ***
		mov		#0f0h,T1LR	; Cycles = 100h - 0f0h = 16
		mov		#0f8h,T1LC	; L level width = 100h - 0f8h = 8
		mov		#0D4h,T1CNT	; Sound output start

		ret

Snd2Start:					; *** Start of 781Hz Tone ***
		mov		#0f9h,T1LR	; Cycles = 100h - 0f9h = 7
		mov		#0fch,T1LC	; L level width = 100h - 0fch = 4
		mov		#0D4h,T1CNT	; Sound output start

		ret

SndStop:					; *** Sound Stop ***
		mov		#0,T1CNT	; Stops sound output

		ret


