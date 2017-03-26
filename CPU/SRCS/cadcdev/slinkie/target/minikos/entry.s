! KallistiOS ##version##
!
!   arch/dreamcast/kernel/entry.s
!   (c)2000-2001 Dan Potter
!
! Assembler code for entry and exit to/from the kernel via exceptions
!

! Routine that all exception handlers jump to after setting
! an error code. Out of neccessity, all of this function is in
! assembler instead of C. Once the registers are saved, we will
! jump into a shared routine. This register save and restore code
! is mostly from my sh-stub code. For now this is pretty high overhead
! for a context switcher (or especially a timer! =) but it can
! be optimized later.

	.text
	.align		2
	.globl		_irq_srt_addr
	.globl		_irq_handle_exception
	.globl		_irq_save_regs
	.globl		_irq_force_return

! All exception vectors lead to Rome (i.e., this label).
_irq_save_regs:
! On the SH4, an exception triggers a toggle of RB in SR. So all
! the R0-R7 registers were convienently saved for us.
	mov.l		_irq_srt_addr,r0	! Grab the location of the reg store
	add		#0x20,r0	! Start at the top of the BANK regs
	stc.l		r7_bank,@-r0	! Save R7
	stc.l		r6_bank,@-r0	! Save R6
	stc.l		r5_bank,@-r0	! Save R5
	stc.l		r4_bank,@-r0	! Save R4
	stc.l		r3_bank,@-r0	! Save R3
	stc.l		r2_bank,@-r0	! Save R2
	stc.l		r1_bank,@-r0	! Save R1
	stc.l		r0_bank,@-r0	! Save R0
	
	mov.l		r8,@(0x20,r0)	! save R8
	mov.l		r9,@(0x24,r0)	! save R9
	mov.l		r10,@(0x28,r0)	! save R10
	mov.l		r11,@(0x2c,r0)	! save R11
	mov.l		r12,@(0x30,r0)	! save R12
	mov.l		r13,@(0x34,r0)	! save R13
	mov.l		r14,@(0x38,r0)	! save R14
	mov.l		r15,@(0x3c,r0)	! save R15 (SP)
	add		#0x5c,r0	! readjust register pointer
	stc.l		ssr,@-r0	! save SSR  0x58
	sts.l		macl,@-r0	! save MACL 0x54
	sts.l		mach,@-r0	! save MACH 0x50
	stc.l		vbr,@-r0	! save VBR  0x4c
	stc.l		gbr,@-r0	! save GBR  0x48
	sts.l		pr,@-r0		! save PR   0x44
	stc.l		spc,@-r0	! save PC   0x40
	
	add		#0x60,r0	! readjust register pointer
	add		#0x44,r0
	sts.l		fpul,@-r0	! save FPUL  0xe0
	sts.l		fpscr,@-r0	! save FPSCR 0xdc
	mov		#0,r2		! Set known FP flags
	lds		r2,fpscr
	fmov.s		fr15,@-r0	! save FR15  0xd8
	fmov.s		fr14,@-r0	! save FR14
	fmov.s		fr13,@-r0	! save FR13
	fmov.s		fr12,@-r0	! save FR12
	fmov.s		fr11,@-r0	! save FR11
	fmov.s		fr10,@-r0	! save FR10
	fmov.s		fr9,@-r0	! save FR9
	fmov.s		fr8,@-r0	! save FR8
	fmov.s		fr7,@-r0	! save FR7
	fmov.s		fr6,@-r0	! save FR6
	fmov.s		fr5,@-r0	! save FR5
	fmov.s		fr4,@-r0	! save FR4
	fmov.s		fr3,@-r0	! save FR3
	fmov.s		fr2,@-r0	! save FR2
	fmov.s		fr1,@-r0	! save FR1
	fmov.s		fr0,@-r0	! save FR0   0x9c
	frchg				! Second FP bank
	fmov.s		fr15,@-r0	! save FR15  0x98
	fmov.s		fr14,@-r0	! save FR14
	fmov.s		fr13,@-r0	! save FR13
	fmov.s		fr12,@-r0	! save FR12
	fmov.s		fr11,@-r0	! save FR11
	fmov.s		fr10,@-r0	! save FR10
	fmov.s		fr9,@-r0	! save FR9
	fmov.s		fr8,@-r0	! save FR8
	fmov.s		fr7,@-r0	! save FR7
	fmov.s		fr6,@-r0	! save FR6
	fmov.s		fr5,@-r0	! save FR5
	fmov.s		fr4,@-r0	! save FR4
	fmov.s		fr3,@-r0	! save FR3
	fmov.s		fr2,@-r0	! save FR2
	fmov.s		fr1,@-r0	! save FR1
	fmov.s		fr0,@-r0	! save FR0   0x5c
	frchg				! First FP bank again

	! Before we enter the main C code again, re-enable exceptions
	! (but not interrupts) so we can still debug inside handlers.
	bsr		_irq_disable
	nop

	! R4 still contains the exception code
	mov.l		hdl_except,r2	! Call handle_exception
	jmp		@r2
	nop
	
	.align 2
_irq_srt_addr:
	.long	0	! Save Regs Table -- this is an indirection
			! so we can easily swap out pointers during a
			! context switch.
hdl_except:
	.long	_irq_handle_exception


! The SH4 has very odd exception handling. Instead of having a vector
! table like a sensible processor, it has a vector code block. *sigh*
! Thus this table of assembly code. Note that we can't catch reset
! exceptions at all, but that really shouldn't matter.
	.text
	.align 2
	.globl _irq_vma_table
_irq_vma_table:
!	.rep	0x100
!	.byte	0
!	.endr
	
_vma_table_100:		! General exceptions
	nop				! Can't have a branch as the first instr
	bra	_irq_save_regs
	mov	#1,r4			! Set exception code
	
	.rep	0x300 - 6
	.byte	0
	.endr

_vma_table_400:		! TLB miss exceptions (MMU)
	nop
!	bra	tlb_miss_hnd
!	nop
	bra	_irq_save_regs
	mov	#2,r4			! Set exception code

	.rep	0x200 - 6
	.byte	0
	.endr

_vma_table_600:		! IRQs
	nop
	bra	_irq_save_regs
	mov	#3,r4			! Set exception code


! Disable interrupts, but leave exceptions enabled. Returns the old
! interrupt status.
!
! Calling this inside an exception/interrupt handler will generally not have
! any effect.
!
	.globl	_irq_disable
_irq_disable:
	mov.l	_irqd_and,r1
	mov.l	_irqd_or,r2
	stc	sr,r0
	and	r0,r1
	or	r2,r1
	ldc	r1,sr
	rts
	nop
	
	.align 2
_irqd_and:
	.long	0xefffff0f
_irqd_or:
	.long	0x000000f0


! Enable interrupts and exceptions. Returns the old interrupt status.
!
! Call this inside an exception/interrupt handler only with GREAT CARE.
!
	.globl	_irq_enable
_irq_enable:
	mov.l	_irqe_and,r1
	stc	sr,r0
	and	r0,r1
	ldc	r1,sr
	rts
	nop
	
	.align 2
_irqe_and:
	.long	0xefffff0f


! Restore interrupts to the state returned by irq_disable()
! or irq_enable().
	.globl	_irq_restore
_irq_restore:
	ldc	r4,sr
	rts
	nop

	.ident	"KOS $Id: entry.s,v 1.7 2003/07/31 00:43:53 bardtx Exp $"
