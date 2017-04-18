; Tab width = 4

;----------------------------------------------------------------------------
; ** Sample **
;
;----------------------------------------------------------------------------
; 1.12 990105 SEGA Enterprises, LTD.
;----------------------------------------------------------------------------

chip	LC868700			; Specifies the chip type for the assembler
world	external			; External memory program

public	main				; Symbol referenced from ghead.asm
public	int_BaseTimer		;
public	int_P3				;
public	int_T0H				;

extern	_game_end			; Application end
extern	fm_wrt_ex, fm_vrf_ex, fm_prd_ex	; Symbol referenced to ghead.asm


; **** Definition of Macro ****************************************************

LcdAccessBegin	macro		; **** Start Access to LCD ****
		push	OCR			; Pushes the OCR value onto the stack
		mov		#osc_rc,OCR ; Specifies the system clock
		clr1	VCCR,6		; Permits CPU access to LCD RAM
		endm
		
LcdAccessEnd	macro		; **** End Access to LCD ****
		set1	VCCR,6		; Prohibits CPU access to LCD RAM
		pop		OCR			; Pops the OCR value off the stack
		endm


; **** Definition of System Constants  ****************************************

							; OCR (Oscillation Control Register) Setting
osc_rc		equ 04dh		;	Specifies internal RC oscillation for the system clock
osc_xt		equ 0efh		;	Specifies crystal oscillation for the system clock
sec_h		equ 01dh		; Second value of time buffer

LowBattChk	equ 06eh		; Low battery detection flag (RAM bank 0)

fmflag		equ 07ch		; Flash memory write end detection method
fmbank		equ 07dh		; Flash memory bank switching
fmadd_h		equ 07eh		; Flash memory upper address
fmadd_l		equ 07fh		; Flash memory lower address

fmbuff		equ 080h		; Start of buffer for flash memory reading/writing


; **** Definition of Game Constants *****************************************

mainloop	equ	1


; *** Data Segment ************************************************************

			dseg			; Data segment start

r0:			ds		1		; Indirect addressing register r0
r1:			ds		1		; Indirect addressing register r1
r2:			ds		1		; Indirect addressing register r2
r3:			ds		1		; Indirect addressing register r3
			ds		12		; Other registers

work1:		ds		1		; Work (used in put2digit)
pmwk1:		ds		1		; Used in put_mimi
pclin:		ds		1		; Used in putch
ip3wk1:		ds		1		; Used in DoHit
rnds:		ds		1		; Random seed
ms_ptr:		ds		1		; Used in ministr
ms_x:		ds		1		; Used in ministr
ms_y:		ds		1		; Used in ministr
ms_trh:		ds		1		; Used in ministr
ms_trl:		ds		1		; Used in ministr
phase:		ds		1		; Programming status
sleeping:	ds		1		; Flag for sleeping

score:		ds		1		; Score
bscore:		ds		1		; Displayed score
lefttime:	ds		1		; Remaining time
timechg:	ds		1		; Flag to change the remaining time
snding:		ds		1		; Counter while outputting sounds
btnflg:		ds		1		; Flag for button status
t0flg:		ds		1		; Flag for timer interrupt

mgrstat:	ds		4		; "mole"


; *** Code Segment ************************************************************

		cseg				; Code segment start
		
; *-------------------------------------------------------------------------*
; * User program															*
; *-------------------------------------------------------------------------*
main:
		mov		#0,sleeping		; Resets flag for sleeping
		mov		#0,phase		; Initializes game status
		clr1	P3INT,0			; P3 interruption is not permitted
		callo	SndInit			; Sound initialization

		callo	cls				; Clears the LCD display image
		set1	pcon,0			; Waits in HALT mode until the next interrupt
		callo	PutCopyright
		set1	pcon,0			; Waits in HALT mode until the next interrupt
		set1	pcon,0			;
		set1	pcon,0			;
		set1	pcon,0			;
		callo	cls				; Clears the LCD display image
		set1	pcon,0			; Waits in HALT mode until the next interrupt

splash:
		callo	cls				; Clears the LCD display image
		callo	PutSample		; Displays "SAMPLE GAME" splash
		callo	PutPushAB		; Displays "PUSH A+B"
		callo	ABWait			; Waits for [A] + [B]
		bzo		finish			; Ends if [M] is pressed or connected to main unit
		
		callo	cls				; Clears the LCD display image
		mov		#mgrstat,r1		; Initializes "mole" (clear 0)
		mov		#4,b			;
lp2:	mov		#0,@r1			;
		inc		r1				;
		dbnz	b,lp2			;
		
		ld		sec_h			; Initializes random number
		st		rnds			;
		mov		#4,pclin		; Initializes number of putch display processing line
		mov		#0,snding		; Clears counter while sound is output
		mov		#0,score		; Clears score
		mov		#0ffh,bscore	; Score being displayed

		callo	T0Mode2Init		; Initializes timer T0
		callo	PutScene1		; Initial screen
		callo	PutReady		; Displays "READY"
		callo	Eff4			; Sound effects
		callo	DelStr			; Deletes "READY"
		callo	PutGo			; Displays "GO"

		mov		#20*2,lefttime	; Remaining time 10 sec.
		mov		#0ffh,ip3wk1	; Clears specified flags
		mov		#0,timechg		; Resets time change flag
		mov		#mainloop,phase	; Main loop while playing the game
		clr1	P3INT,1			; Clears P3 interruption flag
		set1	P3INT,0			; Permits P3 interruption
		
loop0:							; *** Game Main Loop **********************

		set1	pcon,0			; Waits in HALT mode until the next event occurs

		ld		t0flg			; Slot time flag when timer interruption is made
		bz		nx6				; Go next when there is no flag
		mov		#0,t0flg		; Resets flag
		callo	DoMgr			; "mole" processing
								;
		ld		snding			;; Counter process while outputting the sound
		bz		nx4				;;
		dbnz	snding,nx4		;;
		callo	SndStop			;;
nx4:							;;
nx6:							;

		ld		btnflg			; Process (hit, etc.) is made when button is pressed
		bz		nx5				;
		callo	DoHit			; Hit process
nx5:							;

		ld		score			; Displays score when score changes
		be		bscore,nx1		;
		st		bscore			;
		callo	PutScore		;
nx1:							;

		ld		timechg			; Displays remaining time when remaining time changes
		bz		nx2				;
		ld		lefttime		;
		bne		#19*2,nx3		;; Deletes "GO" when remaining time is 19 sec.
		callo	DelStr			;;		
nx3:							;;
		callo	PutTime			;
		mov		#0,timechg		; Clears time change flag
		inc		rnds			;
nx2:							;

		bn		P3,6,finish		; If the [M] button is pressed, the application ends
		bp		P7,0,finish		; Ends when connected to the main unit
		bp		P3,7,nx7		; Sleep if [S] is pressed
		callo	sleep			;
nx7:							;

		ld		lefttime		; Loops while remaining time is left
		bnz		loop0			;
								; *********************************************

		mov		#0,phase		; Game 
		clr1	P3INT,0			; P3 interruption is not permitted
		callo	T0HStop			; Stops T0H timer
		callo	PutGameover		; Displays "GAMEOVER"
		callo	Eff1			; Sound effects

								; ** Waits until [A] or [B] is pressed **
		set1	P3INT,0			; Permits P3 interrupt
lp6:	mov		#2*60*2,lefttime ; Resets sleep timer (2 min.)
lp4:	set1	pcon,0			; Waits in HALT mode until the next interrupt
		ld		lefttime		; Checks sleep timer status
		bnz		nx9				; If the time is left till sleep, go to nx9
		callo	sleep			; Sleep
		br		lp6				; Once awaken, start over from resetting sleep timer
nx9:							;
		ld		P3				; Waits for [A] or [B] button
		bn		acc,6,finish	;; Ends when [M] is pressed
		bp		P3,7,nx8		;; Sleeps when [S] is pressed
		callo	sleep			;;
		br		lp4				;;
nx8:							;;
		bp		P7,0,finish		; Ends when connected to the main unit
		and		#%00110000		;
		be		#%00110000,lp4	;

		clr1	P3INT,0			; P3 interruption is not permitted
		bro		splash			; Returns to the start screen

finish:							; ** Application Finish Process **
		mov		#0,phase		; Game
		callo	T0HStop			; Stops T0H timer
		callo	SndStop			; Stops sound output
		jmpo	_game_end		; Application end


; *-------------------------------------------------------------------------*
; * Sleep																	*
; *-------------------------------------------------------------------------*
sleep:
		push	T0CNT			; Pushes related register onto the stack
		push	P3INT			;
		push	I01CR			;
		set1	I01CR,3			; Sets detective interruption of P70 H level
		set1	I01CR,2			;
		set1	I01CR,0			; Permits P70 interrupt
		set1	P3INT,2			; Sets P3 interrupt permission
		set1	P3INT,0			;
		clr1	T0CNT,0			; Prohibits interrupt besides the one by buttons
		clr1	T0CNT,2			;			
		mov		#0ffh,sleeping	; Sets flag of sleeping
		mov		#%01000000,VCCR	; LCD display OFF
	
sllp2:	bn		P3,7,sllp2		; Waits until [S] is released
	
								; ** Waits for [S] button in HALT mode **
		clr1	I01CR,1			;
sllp1:							;
		clr1	P3INT,1			;
		set1	pcon,0			; HALT
		bp		I01CR,1,slnx1	; Escapes if connected to the main unit
		bp		P3,7,sllp1		; Waits more if [S] is not pressed
slnx1:

		mov		#%10000000,VCCR	; LCD display ON

sllp3:	bn		P3,7,sllp3		; Waits until [S] is released

		mov		#0,sleeping		; Deletes flag of sleeping
		pop		I01CR			; Pops related register off of the stack
		pop		P3INT			;
		pop		T0CNT			;
		ret						; sleep end


; *-------------------------------------------------------------------------*
; * "mole" Process															*
; *-------------------------------------------------------------------------*
DoMgr:
		callo	rand			; Selects the position at random
		and		#3				; 0 to 3
		st		c				; Saves position in c
		mov		#mgrstat,r1		; Checks current status of the position
		add		r1				;
		st		r1				;
		ld		@r1				;
		
		be		#0,st0			; When mole is not here
		be		#1,st1			; Mole starts to appear
		be		#2,st2			; Whole mole
		be		#3,st3			; Mole returns
		be		#4,st4			; Mole being hit
		ret						; DoMgr end

st0:							; "mole" starts to appear
		inc		@r1				; Mole status
		callo	PutMgr1			; Displays character "mole" (half)
		callo	Eff3
		ret						; DoMgr end

st1:							; Whole "mole"
		inc		@r1				; Mole status
		callo	PutMgr2			; Displays character "mole" (whole)
		ret						; DoMgr end

st2:							; "mole" returns
		inc		@r1				; Mole status
		callo	PutMgr1			; Displays character "mole" (half)
		ret						; DoMgr end

st3:							; "mole" hides
st4:							; "mole" being hit and disappears
		mov		#0,@r1			; Mole status
		callo	PutNull			; Displays deleted character "mole"
		ret						; DoMgr end


; *-------------------------------------------------------------------------*
; * Hit Process																*
; *-------------------------------------------------------------------------*
DoHit:
		ld		ip3wk1				; Checks pressed flag
		bne		#0ffh,dhnx1			; If the button is continuously pressed, no process is done until it is released
		
		ld		P3					; Loads P3 status
		st		ip3wk1				; Sets flag of pressed status
		mov		#0,c
		be		#%11111011,chkmgr	; Checks [an arrow pointing left] button
		inc		c
		be		#%11110111,chkmgr	; Checks [an arrow pointing right] button
		inc		c
		be		#%11101111,chkmgr	; Checks [A] button
		inc		c
		be		#%11011111,chkmgr	; Checks [B] button
		ret							; DoHit end
		
dhnx1:	ld		P3					; Records P3 status
		st		ip3wk1				;
		bne		#0ffh,dhnx2			; Ends when pressed
		mov		#0,btnflg			; Clears button flag when released
		set1	P3INT,0				; Permits P3 interruption
dhnx2:								;
		ret							; DoHit end

chkmgr:	ld		c					; c: Position of the pressed button
		mov		#mgrstat,r1			; Checks currrent status of the position
		add		r1					;
		st		r1					;
		ld		@r1					;
		bne		#2,dxnx2			; Ends if hit is not made
		
									; Å´ Was able to hit
		mov		#4,@r1				; Sets to hit status
		callo	PutYarare			; Displays hit pattern
		callo	Eff2				; Makes hit sound
		inc		score				; Counts up the score
dxnx2:
		ret							; DoHit end


; *-------------------------------------------------------------------------*
; * Drawing of basic screen set												*
; *-------------------------------------------------------------------------*
PutScene1:
		callo	PutJimen	; Ground

										; ** "SCORE" Character Display
		mov		#low( str_score),TRL	; Character-string data address
		mov		#high(str_score),TRH	;
		mov		#0,c					; Display position (horizontal)
		mov		#0,b					; Display position (vertical)
		callo	ministr					; Displays "SCORE"

		callo	PutScore	; ** Displaying score **

							; Displays dummy 00
		mov		#5,c		; Display position (horizontal)
		mov		#0,b		; Display position (vertical)
		callo	locate		; Calculates display RAM address according to coordinates

		mov		#0,c		; Display character
		mov		#0,b		; Display character
		callo	put_mini	; Small font drawing

							; ** Initializes display of remaining time **
		mov		#5,c		; Specifies display position
		mov		#20,b		;
		callo	locate		;

		mov		#0,c		; Display character
		mov		#2,b		; Display character
		callo	put_mini	; Small font drawing

		ret					; PutScene1 end

str_score:		dc	'SCORE@\x0'


PutJimen:					; ** Ground **
		mov		#3,pclin	; Number of lines to display character

		mov		#6,c		; Number of characters in vertical direction
lp1:	push	c
		dec		c			; Converts character number counter to horizontal coordinate

		mov		#13,acc		; Ground character code
		mov		#26,b		; Vertical coordinate
		callo	putch		; Displays one character

		pop		c
		dbnz	c,lp1		; Drawing loop in horizontal direction

		ret					; PutJimen end


; *-------------------------------------------------------------------------*
; * Drawing of numbers to indicate remaining time							*
; *-------------------------------------------------------------------------*
PutTime:
		mov		#5,c		; ** Specifies Display Position **
		mov		#20,b		;
		call	locate		;

		ld		lefttime	; Remaining time (0.5 sec. count)
		clr1	PSW,7		; CY flag clear
		rorc				; Converts into 1 sec. count
		st		c			; To c
		
							; ** Devides each digits **	
		mov		#0,acc		; ac = c/10 (...b)
		mov		#10,b		;
		div					; c: tens  b: units
				
		ld		b			; b <-> c
		xch		c			;
		st		b			;
		
		call	put_mini	; Displays bc characters

		ret					; PutTime end


; *-------------------------------------------------------------------------*
; * Drawing of numbers which indicates score								*
; *-------------------------------------------------------------------------*
PutScore:
		mov		#4,c		; ** Specifies Display Position **
		mov		#0,b		;
		call	locate		;

		ld		score
		st		c			; c: Score
		
							; ** Devides each digits **
		mov		#0,acc		; ac = ac/100 (...b)
		mov		#100,b		;
		div					;
		push	c			; push hundreds

		ld		b			; ac = remainder/10 (...b)
		st		c			;
		mov		#0,acc		;
		mov		#10,b		;
		div					; c: tens  b: units
				
		ld		b			; b <-> c
		xch		c			;
		st		b			;
		
		call	put_mini	; Displays bc character (score lower 2 digits)

		mov		#3,c		; Specifies display position
		mov		#0,b		;
		call	locate		;

		pop		c			; pop hundreds
		mov		#0,b		; thousands
		call	put_mini	; Displays upper 2 digits

		ret					; PutScore end


; *-------------------------------------------------------------------------*
; * Drawing of character string by small fonts								*
; * Character string needs to be with even number of characters. Space is "@" *
; * Inputs: c: Horizontal position b: Vertical position TR: Character string *
; *-------------------------------------------------------------------------*
ministr:
		mov		#3,pclin		; Number of putch display processing line (3*2=6)
		ld		c				; Copies display specified horizontal position to ms_x
		st		ms_x			;
		ld		b				; Copies display specified horizontal position to ms_x
		st		ms_y			;
		mov		#0,ms_ptr		; Display point on character string

mslp1:							; Character string display loop
		ld		ms_x			; Fetches display position
		st		c				;
		ld		ms_y			;
		st		b				;
		callo	locate			; Calculates display RAM address according to coordinates (R2)

		ld		ms_ptr			; Fetches left side of character code
		ldc						;
		bz		msnx1			; Ends if code is 0
		sub		#'@'			; "@" code as 0
		st		b				; Stores to B
		inc		ms_ptr			; Moves pointer to character string
		ld		ms_ptr			; Fetches right side of character code
		ldc						;
		sub		#'@'			; "@" code as 0
		st		c				; Stores to C
		inc		ms_ptr			; Moves pointer to character string

		push	TRL
		push	TRH
		call	put_minic		; Small font drawing
		pop		TRH
		pop		TRL

		inc		ms_x			; Moves display position to right
		br		mslp1			; Character string display loop

msnx1:
		ret						; ministr end


; *-------------------------------------------------------------------------*
; * Simple random number													*
; * Inputs: rnds: seed														*
; * Outputs: acc,rnds: Random number										*
; *-------------------------------------------------------------------------*
rand:
		ld		rnds			; c = rnds * 111
		st		b				;
		mov		#111,c			;
		mov		#0,acc			;
		mul						;
		st		b				;
		ld		c				; c = c + 13
		add		#13				;
		st		c				;
		mov		#23,b			; b = c mod 23
		mov		#0,acc			;		
		div						;
		ld		b				; rnds = acc = b
		st		rnds			;

		ret						; rand end


; *-------------------------------------------------------------------------*
; * Deletes Characters														*
; * Inputs: b: Vertical line position c: Horizontal character position		*
  *         acc: Delete character width										*
; *-------------------------------------------------------------------------*
DelChr:
		mov		#4,pclin		; Initializes number of putch display processing line
		push	acc
		push	c
		push	b
		mov		#12,acc			; Delete character code
		call	putch			; Displays one character
		pop		b
		pop		c
		pop		acc
		inc		c
		dbnz	acc,DelChr		; Loops in width of deleted character
		
		ret						; DelChr end
		

; *-------------------------------------------------------------------------*
; * Display Character "mole"												*
; * Inputs: c: Display position (0 to 3)									*
; *-------------------------------------------------------------------------*
PutNull:
		mov		#12,acc			; Delete character code
		br		PutMgr0
PutYarare:
		mov		#15,acc			; Character code for beat up "mole"
		br		PutMgr0
PutMgr1:
		mov		#16,acc			; Character code for "mole" (half)
		br		PutMgr0
PutMgr2:
		mov		#14,acc			; Character code for "mole" (whole)
PutMgr0:
		mov		#4,pclin		; Initializes number of putch display processing line
		inc		c				; Corrects the position
		mov		#18,b			; Vertical coordinate
		call	putch			; Displays one character
		
		ret						; PutNull end


; *-------------------------------------------------------------------------*
; * Displays Character Strings in the middle of the screen					*
; *-------------------------------------------------------------------------*
		; **** Displays "(C)SEGA ENTERPRISES,LTD.,1998" ****
PutCopyright:
		mov		#low( str_sega),TRL		; Character-string data address
		mov		#high(str_sega),TRH		;
		mov		#0,c					; Display position (horizontal)
		mov		#8,b					; Display position (vertical)
		call	ministr					; Displays "(C)SEGA"

		mov		#low( str_enterprises),TRL	; Character-string data address
		mov		#high(str_enterprises),TRH	;
		mov		#0,c					; Display position (horizontal)
		mov		#16,b					; Display position (vertical)
		call	ministr					; Displays "ENTERPRISES,"

		mov		#low( str_ltd),TRL		; Character-string data address
		mov		#high(str_ltd),TRH		;
		mov		#2,c					; Display position (horizontal)
		mov		#24,b					; Display position (vertical)
		call	ministr					; Displays "LTD.,"
		
										; Displays "1998"
		mov		#4,c					; Display position (horizontal)
		mov		#24,b					; Display position (vertical)
		call	locate					; Calculates display RAM address according to coordinates

		mov		#1,b					; Display character
		mov		#9,c					; Display character
		call	put_mini				; Small font drawing

		mov		#5,c					; Display position (horizontal)
		mov		#24,b					; Display position (vertical)
		call	locate					; Calculates display RAM address according to coordinates

		mov		#9,b					; Display character
		mov		#8,c					; Display character
		call	put_mini				; Small font drawing

		ret								; PutCopyright end
		
str_sega:			dc	'\x5bC\x5cSEGA@\x0'
str_enterprises:	dc	'ENTERPRISES\x5e\x0'
str_ltd:			dc	'LTD\x5d\x0'


		; **** Displays "SAMPLE GAME" ****
PutSample:
		mov		#low( str_sample),TRL	; Character-string data address
		mov		#high(str_sample),TRH	;
		mov		#1,c					; Display position (horizontal)
		mov		#10,b					; Display position (vertical)
		call	ministr					; Displays "SAMPLE"

		mov		#low( str_game),TRL		; Character-string data address
		mov		#high(str_game),TRH		;
		mov		#3,c					; Display position (horizontal)
		mov		#16,b					; Display position (vertical)
		call	ministr					; Displays "GAME"
		
		ret								; PutSample end

str_sample:		dc	'SAMPLE\x0'
str_game:		dc	'GAME\x0'
		

		; **** Displays "READY" ****
PutReady:
		mov		#low( str_ready),TRL	; Character-string data address
		mov		#high(str_ready),TRH	;
		mov		#2,c					; Display position (horizontal)
		mov		#10,b					; Display position (vertical)
		call	ministr					; Displays "READY"

		ret								; PutReady end

str_ready:		dc	'READY@\x0'


		; **** Displays "GAMEOVER" ****
PutGameover:
		mov		#low( str_gameover),TRL	; Character-string data address
		mov		#high(str_gameover),TRH	;
		mov		#1,c					; Display position (horizontal)
		mov		#10,b					; Display position (vertical)
		call	ministr					; Displays "GAMEOVER"

		ret								; PutGameover end

str_gameover:	dc	'GAMEOVER\x0'


		; **** Displays "GO" ****
PutGo:
		mov		#low( str_go),TRL		; Character-string data address
		mov		#high(str_go),TRH		;
		mov		#2,c					; Display position (horizontal)
		mov		#10,b					; Display position (vertical)
		call	ministr					; Displays "GO"

		ret								; PutGo end

str_go:			dc	'@GO@\x0'


		; **** Displays "PUSH A+B" ****
PutPushAB:
		mov		#low( str_pushab),TRL	; Character-string data address
		mov		#high(str_pushab),TRH	;
		mov		#1,c					; Display position (horizontal)
		mov		#26,b					; Display position (vertical)
		call	ministr					; Displays "PUSH A+B"

		ret								; PutPushAB end

str_pushab:		dc	'PUSH@A\x5fB\x0'


		; **** Deletes character displayed in the middle of the screen ****
DelStr:
		mov		#1,c			; Horizontal character position
		mov		#8,b			; Vertical line position
		mov		#4,acc			; Delete width
		callo	DelChr

		ret						; DelStr end


; *-------------------------------------------------------------------------*
; * Displaying Two-digit Value												*
; * Inputs: acc: Numeric value												*
; *			  c: Horizontal position of character							*
; *			  b: Vertical position of line									*
; *-------------------------------------------------------------------------*
put2digit:
		push	b			; Pushes the coordinate data onto the stack
		push	c			;
		st		c			; Calculates each tens and units
		xor		a			; ( acc = acc/10, work1 = acc mod 10 )
		mov		#10,b		;
		div					;
		ld		b			;
		st		work1		; Saves calculated result of units in work0
		ld		c			;
		pop		c			; Returns to coordinate (c.b)
		pop		b			; 
		push	b			; Saves again
		push	c			;
		call	putch		; Displays tens
		ld		work1		; Loads units
		pop		c			; Returns to coordinate (c,b)
		pop		b			; 
		inc		c			; Displayed coordinates to the right
		call	putch		; Displays units

		ret					; put2digit end


; *-------------------------------------------------------------------------*
; * Waits until [A]+[B] is pressed											*
; * Outputs: acc=0: Either [M], [S] is pressed or connected to the main unit *
; *		   acc!=0: Normal termination										*
; *-------------------------------------------------------------------------*
ABWait:
		set1	P3INT,0				; Permits P3 interruption
		
ablp2:	mov		#2*60*2,lefttime	; Resets sleep timer (2 min.)

ablp1:	set1	pcon,0				; Waits in HALT mode until the next interrupt

		ld		lefttime			; Checks sleep timer status
		bnz		abnx3				; If time is left till sleep, abnx3
		callo	sleep				; Sleep
		br		ablp2				; Once awaken, start over from sleep timer reset
abnx3:								;

		ld		P3					; Checks button status
		bn		acc,6,abnx1			; Escape if [M] is pressed
		bp		P7,0,abnx1			; Escape if connected to the main unit
		bp		acc,7,abnx2			; Sleep if [S] is pressed
		callo	sleep				;
		br		ablp1				;
abnx2:								;
		bne		#%11001111,ablp1	; Waits until [A]+[B] is pressed
		
		clr1	P3INT,0				; P3 interruption is not permitted
		ret							; ABWait end
		
abnx1:	
		clr1	P3INT,0				; P3 interruption is not permitted
		mov		#0,acc
		ret							; ABWait end


; *-------------------------------------------------------------------------*
; * Clearing the LCD Display Image											*
; *-------------------------------------------------------------------------*
cls:
		LcdAccessBegin		; LCD access start

		mov		#0,XBNK		; Specifies the display RAM bank address (BANK0)
		call	cls_s		; Clears the data in that bank

		mov		#1,XBNK		; Specifies the display RAM bank address (BANK1)
		call	cls_s		; Clears the data in that bank

		LcdAccessEnd		; LCD access end
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
; * Inputs: acc : Character code											*
; *			  c : Horizontal position of character							*
; *		      b : Vertical position of line (even numbers only)				*
; *		  pclin : Number of display processing lines/2						*
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
		; ** Inputs: c: Horizontal position (0 to 5) b: Vertical position of line (even numbers only)
		; ** Outputs: r2: RAM address XBNK: Display RAM bank

							; *** Determining the Display RAM Bank Address ***
		ld		b			; Jump to next1 when b >= 16
		sub		#16			;
		bn		PSW,7,next1	;
		
		mov		#00h,XBNK	; Specifies the display RAM bank address (BANK0)
		br		next2
next1:
		st		b
		mov		#01h,XBNK	; Specifies the display RAM bank address (BANK1)
next2:

							; *** Calculating the RAM Address for a Specified Position on the Display ***
		ld		b			; b * 8 + c + 80h
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
		st		TRH			;

		LcdAccessBegin		; LCD access start

		ld		pclin		; Number of display processing line/2
		st		c			; Loop counter
		mov		#0,b		; Offset value for Character data loading
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
		
		LcdAccessEnd		; LCD access end

		pop		PSW			; Pops the PSW value off of the stack

		ret					; put_chara end


; *-------------------------------------------------------------------------*
; * Drawing of Small Font Character											*
; * Inputs: b: Character code in left side									*
; *		    c: Character code in right side									*
; *-------------------------------------------------------------------------*
put_minic:
		mov		#low( font_mc),TRL	; Head address of font data to TR
		mov		#high(font_mc),TRH	;

		br		put_mini0

; *-------------------------------------------------------------------------*
; * Drawing of Small Font Number											*
; * Inputs: b: Character code in left side									*
; *		    c: Character code in right side									*
; *-------------------------------------------------------------------------*
put_mini:
		mov		#low( font_m),TRL	; Head address of font data to TR
		mov		#high(font_m),TRH	;

put_mini0:
		push	PSW			; Pushes the PSW value onto the stack
		set1	PSW,1		; Selets data RAM bank 1

							; Calculates character data address (left)
		ld		b			; b = b*8
		rol					;
		rol					;
		rol					;	
		st		b			;

							; Calculates character data address (right)
		ld		c			; c = c*8
		rol					;
		rol					;
		rol					;	
		st		c			;		

		LcdAccessBegin		; LCD access start

							;-- First line
		ld		b			; Loads display data for the first line (for left)
		ldc					;
		and		#0f0h		; Use data in left side
		st		@r2			; Transfers the display data to display RAM
		
		ld		c			; Loads display data for the first line (for right)
		ldc
		and		#00fh		; Use data in right side
		or		@r2			; Data displayed on left side and OR display
		st		@r2			;

		inc		b			; Increments the load data offset by 1
		inc		c			; Increments the load data offset by 1

		ld		r2			; Adds 6 to the display RAM address
		add		#6			;
		st		r2			;

							;-- Second line
		ld		b			; Loads display data for the second line (for left)
		ldc					;
		and		#0f0h		; Use data in left side
		st		@r2			; Transfers the display data to display RAM
		
		ld		c			; Loads display data for the second line (for right)
		ldc
		and		#00fh		; Use data in right side
		or		@r2			; Data displayed on left side and OR display
		st		@r2			;

		inc		b			; Increments the load data offset by 1
		inc		c			; Increments the load data offset by 1

		ld		r2			; Adds 10 to the display RAM address
		add		#10			;
		st		r2			;

							;-- Third line
		ld		b			; Loads display data for the first line (for left)
		ldc					;
		and		#0f0h		; Use data in left side
		st		@r2			; Transfers the display data to display RAM
		
		ld		c			; Loads display data for the first line (for right)
		ldc
		and		#00fh		; Use data in right side
		or		@r2			; Data displayed on left side and OR display
		st		@r2			;

		inc		b			; Increments the load data offset by 1
		inc		c			; Increments the load data offset by 1

		ld		r2			; Adds 6 to the display RAM address
		add		#6			;
		st		r2			;

							;-- Fourth line
		ld		b			; Loads display data for the second line (for left)
		ldc					;
		and		#0f0h		; Use data in left side
		st		@r2			; Transfers the display data to display RAM
		
		ld		c			; Loads display data for the second line (for right)
		ldc
		and		#00fh		; Use data in right side
		or		@r2			; Data displayed on left side and OR display
		st		@r2			;

		inc		b			; Increments the load data offset by 1
		inc		c			; Increments the load data offset by 1

		ld		r2			; Adds 10 to the display RAM address
		add		#10			;
		st		r2			;

							;-- Fifth line
		ld		b			; Loads display data for the first line (for left)
		ldc					;
		and		#0f0h		; Use data in left side
		st		@r2			; Transfers the display data to display RAM
		
		ld		c			; Loads display data for the first line (for right)
		ldc
		and		#00fh		; Use data in right side
		or		@r2			; Data displayed on left side and OR display
		st		@r2			;

		inc		b			; Increments the load data offset by 1
		inc		c			; Increments the load data offset by 1

		ld		r2			; Adds 6 to the display RAM address
		add		#6			;
		st		r2			;
		
		LcdAccessEnd		; LCD access end

		pop		PSW			; Pops the PSW value off of the stack

		ret					; put_mini  end


; *-------------------------------------------------------------------------*
; * Sound Effects															*
; *-------------------------------------------------------------------------*
Eff1:	; **** Sound for game over ****
		mov		#16,acc				; Loop counter initial value
		
lp3:								; *** Start making sounds, approx. 342Hz ***
		mov		#0f0h,T1LR			; Cycle = 100h-0f0h = 16
		mov		#0f8h,T1LC			; L level width = 100h-0f8h = 8
		mov		#0D4h,T1CNT			; Sound output start
		
		push	acc
		call	ewait				; Waiting
		pop		acc
									; *** Start making sounds, approx. 781Hz ***
		mov		#0f9h,T1LR			; Cycle = 100h-0f9h = 7
		mov		#0fch,T1LC			; L level width = 100h-0fch = 4
		mov		#0D4h,T1CNT			; Sound output start

		push	acc
		call	ewait				; Waiting
		pop		acc
	
		dbnz	acc,lp3				; Repeat

		callo	SndStop				; Stops the sound
		
		ret							; Eff1  end

ewait:	;Waiting
ew2:	mov		#2,c
ew1:	dbnz	c,ew1
		dbnz	acc,ew2

		ret							; ewait  end


Eff2:	; **** Sound when mole is hit ****
		mov		#0e0h,T1LR			; Cycle = 100h-0e0h = 32
		mov		#0f8h,T1LC			; L level width = 100h-0f8h = 8
		mov		#0D4h,T1CNT			; Sound output start
		mov		#2,snding			; Sets counter while outputting sounds

		ret							; Eff2 end

Eff3:	; **** Sound when mole is coming out ****
		mov		#0f0h,T1LR			; Cycle = 100h-0f0h = 16
		mov		#0f8h,T1LC			; L level width = 100h-0f8h = 8
		mov		#0D4h,T1CNT			; Sound output start
		mov		#1,snding			; Sets counter while outputting sounds

		ret							; Eff3 end


Eff4:	; **** Sound when starting the game ****
		mov		#6,acc
		
lp5:	push	acc
		mov		#0e5h,T1LR			; Cycle = 100h-0e5h = 27
		mov		#0feh,T1LC			; L level width = 100h-0feh = 2
		mov		#0D4h,T1CNT			; Sound output start
		
		mov		#8,acc
		callo	bwait				; Waiting

		mov		#0f3h,T1LR			; Cycle = 100h-0f3h = 13
		mov		#0f9h,T1LC			; L level width = 100h-0f9h = 7
		mov		#0D4h,T1CNT			; Sound output start

		mov		#7,acc
		callo	bwait				; Waiting
		pop		acc
		
		dbnz	acc,lp5				; Loop

		call	SndStop				; Stops the sound
		
		ret							; Eff4 end
		
		
; *-------------------------------------------------------------------------*
; * Waiting for the sound output time										*
; * Inputs: acc: Waiting time												*
; *-------------------------------------------------------------------------*
bwait:		
		mov		#16,c
bw1:	dbnz	c,bw1
		dbnz	acc,bwait

		ret							; bwait end
		
		
; *-------------------------------------------------------------------------*
; * Initializes sound output												*
; *-------------------------------------------------------------------------*
SndInit:
		clr1	P1,7			; Sets sound output port
	
		ret						; SndInit end


; *-------------------------------------------------------------------------*
; * Sound Output Stop														*
; *-------------------------------------------------------------------------*
SndStop:
		mov		#0,T1CNT		; Sound output stop
		
		ret						; SndStop end


; *-------------------------------------------------------------------------*
; * Intialization of Timer/Counter T0										*
; *   Interruption is made every 0.15 seconds (approx.) by mode 2 (16 bit counter) *
; *-------------------------------------------------------------------------*
T0Mode2Init:
		mov		#255,T0PRR	; Sets pre-scalar value
							;   Because it is 8 bit pre-scalar
							;   Cycle = (256-255)*0.000183 = 0.000183 (sec)
		mov		#high(65536-819),T0HR ; Sets preset value (H)
		mov		#low(65536-819),T0LR  ; Sets preset value (L)
							;   In set with pre-scalar
							;   0.000183 * 819 = 0.149877 (approx. 0.15sec)
							;   Overflow occurs every 0.15 seconds
		mov		#0ffh,T0L	; Sets to overflow at the beginning
		mov		#0ffh,T0H	;
		mov		#0e4h,T0CNT	; Mode 2 (16 bit counter)
							; Interruption is made when T0H overflows
							; Starts Timer 0
	
		ret					; T0Mode2Init end


T0HStop:					; *** T0H Timer Stop ***

		clr1	T0CNT,7		; T0H counter stops
		ret


; *-------------------------------------------------------------------------*
; * Timer T0H Interrupt Handler												*
; *-------------------------------------------------------------------------*
int_T0H:					; *** T0H interrupt handler ***
		inc		t0flg		; Sets timer interrupt flag
		clr1	T0CNT,3		; Clears timer T0H interrupt factor
		reti


; *-------------------------------------------------------------------------*
; * P3 (button operation) Interrupt Handler									*
; *-------------------------------------------------------------------------*
int_P3:
		clr1	P3INT,0			; P3 interruption is not permitted
		inc		btnflg			; Sets button flag
		clr1	P3INT,1			; Clears P3 interruption flag
		reti


; *-------------------------------------------------------------------------*
; * Base Timer Interruption Handler											*
; *-------------------------------------------------------------------------*
int_BaseTimer:
		bp		sleeping,0,next6 ; Returns if sleeping
		
		push	acc				; Pushes the register that was used onto the stack
		ld		lefttime		; Remaining time
		bz		next5			; To next5 if "0"
		dec		lefttime		; Decrements the remaining time
		inc		timechg			; Sets flag to change the remaining time
next5:							;
		pop		acc				; Pops the register back off of the stack

next6:		
		ret						; (User) Interrupt processing end


; *-------------------------------------------------------------------------*
; * Character Bit Image Data												*
; *-------------------------------------------------------------------------*
fontdata:
		db	07ch, 0e6h, 0c6h, 0c6h, 0c6h, 0ceh, 07ch, 000h	;0
		db	018h, 038h, 018h, 018h, 018h, 018h, 03ch, 000h	;1
		db	07ch, 0c6h, 0c6h, 00ch, 038h, 060h, 0feh, 000h	;2
		db	07ch, 0e6h, 006h, 01ch, 006h, 0e6h, 07ch, 000h	;3
		db	00ch, 01ch, 03ch, 06ch, 0cch, 0feh, 00ch, 000h	;4
		db	0feh, 0c0h, 0fch, 006h, 006h, 0c6h, 07ch, 000h	;5
		db	01ch, 030h, 060h, 0fch, 0c6h, 0c6h, 07ch, 000h	;6
		db	0feh, 0c6h, 004h, 00ch, 018h, 018h, 038h, 000h	;7
		db	07ch, 0c6h, 0c6h, 07ch, 0c6h, 0c6h, 07ch, 000h	;8
		db	07ch, 0c6h, 0c6h, 07eh, 006h, 00ch, 078h, 000h	;9
		
		db	000h, 030h, 030h, 000h, 000h, 030h, 030h, 000h	;:
		db	000h, 000h, 000h, 000h, 000h, 060h, 060h, 000h	;.

		db	000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h	; (null)

		db	0ffh, 052h, 0a5h, 048h, 021h, 000h, 000h, 000h	; Ground

		db	%01000010	; "mole" (whole)
		db	%00111100
		db	%01011010
		db	%01011010
		db	%11111111
		db	%01100110
		db	%10111101
		db	%01011010
		
		db	%00010000	; "mole" (beat up)
		db	%00000001
		db	%10100000
		db	%00001000
		db	%01000010
		db	%10111101
		db	%01011110
		db	%11111011
		
		db	%00000000	; "mole" (half)
		db	%00000000
		db	%00000000
		db	%01000010
		db	%00111100
		db	%01111110
		db	%01011010
		db	%11111111


		; Number Small Fonts
font_m:	
		db	0eeh, 0aah, 0aah, 0aah, 0eeh, 0,0,0	; 0
		db	022h, 022h, 022h, 022h, 022h, 0,0,0	; 1
		db	0eeh, 022h, 0eeh, 088h, 0eeh, 0,0,0	; 2
		db	0eeh, 022h, 0eeh, 022h, 0eeh, 0,0,0	; 3
		db	0aah, 0aah, 0eeh, 022h, 022h, 0,0,0	; 4
		db	0eeh, 088h, 0eeh, 022h, 0eeh, 0,0,0	; 5
		db	0eeh, 088h, 0eeh, 0aah, 0eeh, 0,0,0	; 6
		db	0eeh, 0aah, 022h, 022h, 022h, 0,0,0	; 7
		db	0eeh, 0aah, 0eeh, 0aah, 0eeh, 0,0,0	; 8
		db	0eeh, 0aah, 0eeh, 022h, 0eeh, 0,0,0	; 9

		; ALphabet Character Small Fonts
font_mc:
		db	000h, 000h, 000h, 000h, 000h, 0,0,0	; 
		db	044h, 0aah, 0aah, 0eeh, 0aah, 0,0,0	; A
		db	0cch, 0aah, 0eeh, 0aah, 0cch, 0,0,0	; B
		db	0eeh, 0aah, 088h, 0aah, 0eeh, 0,0,0	; C
		db	0cch, 0aah, 0aah, 0aah, 0cch, 0,0,0	; D
		db	0eeh, 088h, 0cch, 088h, 0eeh, 0,0,0	; E
		db	0eeh, 088h, 0eeh, 088h, 088h, 0,0,0	; F
		db	066h, 088h, 0aah, 0aah, 066h, 0,0,0	; G
		db	0aah, 0aah, 0eeh, 0aah, 0aah, 0,0,0	; H
		db	0eeh, 044h, 044h, 044h, 0eeh, 0,0,0	; I
		db	0eeh, 022h, 022h, 0aah, 0cch, 0,0,0	; J
		db	0aah, 0aah, 0cch, 0aah, 0aah, 0,0,0	; K
		db	088h, 088h, 088h, 088h, 0eeh, 0,0,0	; L
		db	0aah, 0eeh, 0aah, 0aah, 0aah, 0,0,0	; M
		db	0aah, 0eeh, 0eeh, 0eeh, 0aah, 0,0,0	; N
;		db	044h, 0aah, 0aah, 0aah, 044h, 0,0,0	; O
		db	0eeh, 0aah, 0aah, 0aah, 0eeh, 0,0,0	; O
		db	0eeh, 0aah, 0eeh, 088h, 088h, 0,0,0	; P
		db	044h, 0aah, 0aah, 0cch, 066h, 0,0,0	; Q
;		db	0cch, 0aah, 0cch, 0aah, 0aah, 0,0,0	; R
		db	0eeh, 0aah, 0cch, 0aah, 0aah, 0,0,0	; R
;		db	066h, 088h, 0eeh, 022h, 0cch, 0,0,0	; S
		db	0eeh, 088h, 0eeh, 022h, 0eeh, 0,0,0	; S
		db	0eeh, 044h, 044h, 044h, 044h, 0,0,0	; T
		db	0aah, 0aah, 0aah, 0aah, 0eeh, 0,0,0	; U
		db	0aah, 0aah, 0aah, 0aah, 044h, 0,0,0	; V
		db	0aah, 0aah, 0eeh, 0eeh, 0eeh, 0,0,0	; W
		db	0aah, 0eeh, 044h, 0eeh, 0aah, 0,0,0	; X
		db	0aah, 0aah, 0eeh, 044h, 044h, 0,0,0	; Y
		db	0eeh, 022h, 044h, 088h, 0eeh, 0,0,0	; Z
		db	022h, 044h, 044h, 044h, 022h, 0,0,0	; (
		db	088h, 044h, 044h, 044h, 088h, 0,0,0	; )
		db	000h, 000h, 000h, 011h, 0AAh, 0,0,0	; .,
		db	000h, 000h, 000h, 022h, 044h, 0,0,0	; ,
		db	000h, 044h, 0eeh, 044h, 000h, 0,0,0 ; +		
