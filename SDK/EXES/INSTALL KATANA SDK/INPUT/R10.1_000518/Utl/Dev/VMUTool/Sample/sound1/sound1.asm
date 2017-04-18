; Tab width = 4

;----------------------------------------------------------------------------
; ** Sound Usage Sample 1 **
;
; ÅEIntermittently outputs two tones (high/low)
;  (Low tone for 0.5 seconds - Silence for 0.5 seconds - High tone for 0.5
   seconds - Silence for 0.5 seconds...)
;----------------------------------------------------------------------------
; 1.00 981208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	LC868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm

extern	_game_end			; Application end


; **** Definition of System Constants ***************************************

							; OCR (Oscillation Control Register) settings
osc_rc		equ 081h		;  Specifies internal RC oscillation for the system clock
osc_xt		equ 082h		;  Specifies crystal oscillation for the system clock


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
		call	SndInit		; Sound initialization

loop0:
		call	Snd1Start	; Starts generating tone at approximately 342Hz
		set1	PCON,0		; HALT mode until base timer interrupt (0.5 seconds)

		call	SndStop		; Buzzer sound off
		set1	PCON,0		; HALT mode until base timer interrupt (0.5 seconds)

		call	Snd2Start	; Starts generating tone at approximately 781
		set1	PCON,0		; HALT mode until base timer interrupt (0.5 seconds)
		call	SndStop		; Buzzer sound off
		set1	PCON,0		; HALT mode until base timer interrupt (0.5 seconds)


							; ** [M] (mode) Button Check **
		ld		P3
		bn		acc,6,finish ; If the [M] button is pressed, the application ends

		br		loop0		; Repeat

finish:						; ** Application End Processing **
		jmp		_game_end	; Application end


; *-------------------------------------------------------------------------*
; * Sound Output-related Routines											*
; *-------------------------------------------------------------------------*
SndInit:					; *** Sound Output Hardware Initialization ***
		clr1	P1,7		; Sets the sound output port

		ret

Snd1Start:					; *** Start of 342Hz Tone ***
		mov		#0f0h,T1LR	; Cycles = 100h - 0f0h = 16
		mov		#0f8h,T1LC	; L level width = 100h - 0f8h = 8
		mov		#0D0h,T1CNT ; Sound output start

		ret

Snd2Start:					; *** Start of 781Hz Tone ***
		mov		#0f9h,T1LR	; Cycles = 100h - 0f9h = 7
		mov		#0fch,T1LC	; L level width = 100h - 0fch = 4
		mov		#0D0h,T1CNT ; Sound output start

		ret

SndStop:					; *** Sound Stop ***
		mov		#0,T1CNT	; Stops sound output

		ret

