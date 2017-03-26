! exception handlers
!
! a general exception handler that displays a register dump onscreen
! for general exceptions (VBR + 0x100) and TLB miss exceptions (VBR + 0x400)
!	
				
	.section .text
disp_labels:	

	! r4 -> @(0,r15) = addr of labels
	! r5 -> @(4,r15) =  number of labels
	! r6 -> @(12,r15) = starting x-position
	! r7 -> @(8,r15)=  starting y-position

	sts.l pr,@-r15
	add #-16,r15
! loop init
	mov.l r4,@(0,r15)
	mov.l r7,@(8,r15)
	mov.l r6,@(12,r15)
	mov r5,r0
disp_loop:	
! display a label
	mov.l r0,@(4,r15) 
	mov.l @(12,r15),r4
	mov.l @(8,r15),r5
	mov.l @(0,r15),r6
	mov #0xff,r7
	mov.l draw_k,r0
	mov.l @r0,r0
	jsr @r0
	nop
! increment / decrement / blahblahblah
	mov.l @(8,r15),r0
	add #24,r0
	mov.l r0,@(8,r15)
	mov.l @(0,r15),r0
	add #5,r0
	mov.l r0,@(0,r15)
	mov.l @(4,r15),r0
	dt r0
	bf disp_loop
	add #16,r15
	lds.l @r15+,pr
	rts
	nop

disp_values:
	! r4 -> @(0,r15) = addr of values
	! r5 -> @(4,r15) =  number of values
	! r6 -> @(12,r15) = starting x-position
	! r7 -> @(8,r15)=  starting y-position

	sts.l pr,@-r15
	add #-16,r15
! loop init
	mov.l r4,@(0,r15)
	mov.l r7,@(8,r15)
	mov.l r6,@(12,r15)
	mov r5,r0
val_loop:	
	mov.l r0,@(4,r15) 
	mov.l @(0,r15),r4
	mov.l @r4,r4
! convert string
	mova misc_string,r0
	mov r0,r5
	mov.l uint_to_string_k,r0
	mov.l @r0,r0
	jsr @r0
	nop
	mova misc_string,r0
	mov r0,r6
! display string	
	mov.l @(12,r15),r4
	mov.l @(8,r15),r5
	mov #0xff,r7
	mov.l draw_k,r0
	mov.l @r0,r0
	jsr @r0
	nop
! increment / decrement
	mov.l @(8,r15),r0
	add #24,r0
	mov.l r0,@(8,r15)
	mov.l @(0,r15),r0
	add #4,r0
	mov.l r0,@(0,r15)
	mov.l @(4,r15),r0
	dt r0
	bf val_loop
	add #16,r15
	lds.l @r15+,pr
	rts
	nop
		
.balign 0x100

! VBR + 0x100	
! general exceptions
general_1:
! assume the stack may be fux0red
	mov.l stack_addr,r15
! save and display registers
	add #-66,r15
	add #-66,r15
	add #-66,r15
	add #-66,r15
	sts.l pr,@-r15
	mov.l r0,@-r15
	mov.l r1,@-r15
	mova regdump,r0	
	jsr @r0
	nop
	add #12,r15
	add #66,r15
	add #66,r15
	add #66,r15
	add #66,r15
! display exception identifier string		
	mov.l expevt,r4
	mov.l @r4,r4
	mov.l exc_to_string_k,r0
	mov.l @r0,r0
	jsr @r0
	nop
	mov #0,r4
	mov #24,r5
	mov r0,r6
	mov #0xff,r7
	mov.l draw_k,r0
	mov.l @r0,r0
	jsr @r0
	nop
!	display "EXPEVT"		
	mov #0,r4
	mov #48,r5
	mova expevt_string,r0
	mov r0,r6
	mov #0xff,r7
	mov.l draw_k,r0
	mov.l @r0,r0
	jsr @r0
	nop
! convert expevt to string	
	mov.l expevt,r4
	mov.l @r4,r4
	mova misc_string,r0
	mov r0,r5
	mov.l uint_to_string_k,r0
	mov.l @r0,r0
	jsr @r0
	nop
! display expevt			
	mov #84,r4
	extu.b r4,r4
	mov #48,r5
	mova misc_string,r0
	mov r0,r6
	mov #0xff,r7
	mov.l draw_k,r0
	mov.l @r0,r0
	jsr @r0
	nop
! return to bootloader
	mov.l entry_addr,r0
	jmp @r0
	nop
.align 4
stack_addr:
	.long 0x8d000000
exc_to_string_k:
	.long 0x8c00401c
		
regdump:
! save registers for display
! caller has allocated 264 bytes on stack for regs
! caller has left r0,r1, and old pr on stack
	sts.l pr,@-r15
	mov r15,r0
	add #16,r0
! (s)pc, pr, (s)sr, gbr, vbr, dbr, mach, macl
	stc spc,r1
	mov.l r1,@r0
	add #4,r0
	mov.l @(12,r15),r1
	mov.l r1,@r0
	add #4,r0
	stc ssr,r1
	mov.l r1,@r0
	add #4,r0
	stc gbr,r1
	mov.l r1,@r0
	add #4,r0
	stc vbr,r1
	mov.l r1,@r0
	add #4,r0
	stc dbr,r1
	mov.l r1,@r0
	add #4,r0
	sts mach,r1
	mov.l r1,@r0
	add #4,r0
	sts macl,r1
	mov.l r1,@r0
	add #4,r0
! r0-r7 bank 0
	stc r0_bank,r1
	mov.l r1,@r0
	add #4,r0
	stc r1_bank,r1
	mov.l r1,@r0
	add #4,r0
	stc r2_bank,r1
	mov.l r1,@r0
	add #4,r0
	stc r3_bank,r1
	mov.l r1,@r0
	add #4,r0
	stc r4_bank,r1
	mov.l r1,@r0
	add #4,r0
	stc r5_bank,r1
	mov.l r1,@r0
	add #4,r0
	stc r6_bank,r1
	mov.l r1,@r0
	add #4,r0
	stc r7_bank,r1
	mov.l r1,@r0
	add #4,r0
! r0-r7 bank 1	
	mov.l @(8,r15),r1
	mov.l r1,@r0
	add #4,r0
	mov.l @(4,r15),r1
	mov.l r1,@r0
	add #4,r0
	mov.l r2,@r0
	add #4,r0
	mov.l r3,@r0
	add #4,r0
	mov.l r4,@r0
	add #4,r0
	mov.l r5,@r0
	add #4,r0
	mov.l r6,@r0
	add #4,r0
	mov.l r7,@r0
	add #4,r0
! r8-r14
	mov.l r8,@r0
	add #4,r0
	mov.l r9,@r0
	add #4,r0
	mov.l r10,@r0
	add #4,r0
	mov.l r11,@r0
	add #4,r0
	mov.l r12,@r0
	add #4,r0
	mov.l r13,@r0
	add #4,r0
	mov.l r14,@r0
	add #4,r0
! sgr (r15)	
	stc sgr,r1
	mov.l r1,@r0
	add #4,r0
! fpscr
	sts fpscr,r1
	mov.l r1,@r0
	add #4,r0
! set fpscr.fr = 0, to get fr0-fr15
	mov.l fpscr_val_fr,r1
	lds r1,fpscr
! fr0-fr15
	fmov.s fr0,@r0
	add #4,r0
	fmov.s fr1,@r0
	add #4,r0
	fmov.s fr2,@r0
	add #4,r0
	fmov.s fr3,@r0
	add #4,r0
	fmov.s fr4,@r0
	add #4,r0
	fmov.s fr5,@r0
	add #4,r0
	fmov.s fr6,@r0
	add #4,r0
	fmov.s fr7,@r0
	add #4,r0
	fmov.s fr8,@r0
	add #4,r0
	fmov.s fr9,@r0
	add #4,r0
	fmov.s fr10,@r0
	add #4,r0
	fmov.s fr11,@r0
	add #4,r0
	fmov.s fr12,@r0
	add #4,r0
	fmov.s fr13,@r0
	add #4,r0
	fmov.s fr14,@r0
	add #4,r0
	fmov.s fr15,@r0
	add #4,r0
! fpul
	sts fpul,r1
	mov.l r1,@r0
	add #4,r0
! set fpscr.fr = 1, to get xf0-xf15
	mov.l fpscr_val_xf,r1
	lds r1,fpscr
! xf0-xf15
	fmov.s fr0,@r0
	add #4,r0
	fmov.s fr1,@r0
	add #4,r0
	fmov.s fr2,@r0
	add #4,r0
	fmov.s fr3,@r0
	add #4,r0
	fmov.s fr4,@r0
	add #4,r0
	fmov.s fr5,@r0
	add #4,r0
	fmov.s fr6,@r0
	add #4,r0
	fmov.s fr7,@r0
	add #4,r0
	fmov.s fr8,@r0
	add #4,r0
	fmov.s fr9,@r0
	add #4,r0
	fmov.s fr10,@r0
	add #4,r0
	fmov.s fr11,@r0
	add #4,r0
	fmov.s fr12,@r0
	add #4,r0
	fmov.s fr13,@r0
	add #4,r0
	fmov.s fr14,@r0
	add #4,r0
	fmov.s fr15,@r0
	add #4,r0
! init video
	mov.l setup_video_k,r0
	mov.l @r0,r0
	mov #0,r4
	mov #0x1f,r5
	jsr @r0
	nop
! display 1st set of labels
	mov.l labels1_k,r4
	mov #16,r5
	mov #0,r6
	mov #72,r7
	mov.l disp_addr,r0
	jsr @r0
	nop
! display 2nd set of labels
	mov.l labels2_k,r4
	mov #16,r5
	mov #160,r6
	extu.b r6,r6
	mov #72,r7
	mov.l disp_addr,r0
	jsr @r0
	nop
! display 3rd set of labels
	mov.l labels3_k,r4
	mov #17,r5
	mov #160,r6
	extu.b r6,r6
	shll r6
	mov #48,r7
	mov.l disp_addr,r0
	jsr @r0
	nop
! display 4th set of labels
	mov.l labels4_k,r4
	mov #17,r5
	mov #160,r6
	extu.b r6,r6
	mov r6,r7
	shll r6
	add r7,r6
	mov #48,r7
	mov.l disp_addr,r0
	jsr @r0
	nop
! display 1st set of values
	mov r15,r0
	add #16,r0
	mov r0,r4
	mov #16,r5
	mov #52,r6
	mov #72,r7
	mov.l val_addr,r0
	jsr @r0
	nop
! display 2nd set of values
	mov r15,r0
	add #16,r0
	add #64,r0
	mov r0,r4
	mov #16,r5
	mov #52,r6
	mov #160,r7
	extu.b r7,r7
	add r7,r6
	mov #72,r7
	mov.l val_addr,r0
	jsr @r0
	nop
! display 3rd set of values
	mov r15,r0
	add #16,r0
	mov #128,r1
	extu.b r1,r1
	add r1,r0
	mov r0,r4
	mov #17,r5
	mov #52,r6
	mov #160,r7
	extu.b r7,r7
	shll r7
	add r7,r6
	mov #48,r7
	mov.l val_addr,r0
	jsr @r0
	nop
! display 4th set of values
	mov r15,r0
	add #16,r0
	mov #196,r1
	extu.b r1,r1
	add r1,r0
	mov r0,r4
	mov #17,r5
	mov #52,r6
	mov #160,r7
	extu.b r7,r7
	mov r7,r8
	shll r8
	add r8,r7
	add r7,r6
	mov #48,r7
	mov.l val_addr,r0
	jsr @r0
	nop
! return
	lds.l @r15+,pr
	rts
	nop	
.align 4
fpscr_val_fr:
	.long 0x00040001
fpscr_val_xf:
	.long 0x00240001
disp_addr:
	.long disp_labels
val_addr:
	.long disp_values
entry_addr:
	.long	0x8c004000
draw_k:
	.long	0x8c004014
uint_to_string_k:
	.long	0x8c004018
expevt:
	.long	0xff000024
labels1_k:
	.long labels1
labels2_k:
	.long labels2
labels3_k:
	.long labels3
labels4_k:
	.long labels4
setup_video_k:	
	.long 0x8c00400c
.align 2
expevt_string:
	.asciz "EXPEVT"
.align 2
misc_string:
	.asciz "DEADBEEF"

.balign 0x400

! VBR + 0x400	
general_2:
	bra general_1
	nop
.align 2
labels1:	
	.asciz "PC  "
	.asciz "PR  "
	.asciz "SR  "
	.asciz "GBR "
	.asciz "VBR "
	.asciz "DBR "
	.asciz "MACH"
	.asciz "MACL"
	.asciz "R0B0"
	.asciz "R1B0"
	.asciz "R2B0"
	.asciz "R3B0"
	.asciz "R4B0"
	.asciz "R5B0"
	.asciz "R6B0"
	.asciz "R7B0"
.align 2
labels2:	
	.asciz "R0B1"
	.asciz "R1B1"
	.asciz "R2B1"
	.asciz "R3B1"
	.asciz "R4B1"
	.asciz "R5B1"
	.asciz "R6B1"
	.asciz "R7B1"
	.asciz "R8  "
	.asciz "R9  "
	.asciz "R10 "
	.asciz "R11 "
	.asciz "R12 "
	.asciz "R13 "
	.asciz "R14 "
	.asciz "R15 "
.align 2
labels3:	
	.asciz "FPSC" ! FPSCR
	.asciz "FR0 "
	.asciz "FR1 "
	.asciz "FR2 "
	.asciz "FR3 "
	.asciz "FR4 "
	.asciz "FR5 "
	.asciz "FR6 "
	.asciz "FR7 "
	.asciz "FR8 "
	.asciz "FR9 "
	.asciz "FR10"
	.asciz "FR11"
	.asciz "FR12"
	.asciz "FR13"
	.asciz "FR14"
	.asciz "FR15"
.align 2
labels4:	
	.asciz "FPUL"
	.asciz "XF0 "
	.asciz "XF1 "
	.asciz "XF2 "
	.asciz "XF3 "
	.asciz "XF4 "
	.asciz "XF5 "
	.asciz "XF6 "
	.asciz "XF7 "
	.asciz "XF8 "
	.asciz "XF9 "
	.asciz "XF10"
	.asciz "XF11"
	.asciz "XF12"
	.asciz "XF13"
	.asciz "XF14"
	.asciz "XF15"

.balign 0x200

! VBR + 0x600
interrupt:
	rte
	nop
