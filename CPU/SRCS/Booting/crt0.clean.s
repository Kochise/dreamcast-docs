!----------------------------------------------------------------------------------------------
!  crt0.s - SEGA Dreamcast library for GNU/GCC - startup code
!
!  29.07.2000 Groepaz/Hitmen
!----------------------------------------------------------------------------------------------

  .section .text

	.global	start
  .global ___main

!  .global _exit
!  .global _atexit

!---------------------------------------------------------------------------------------------

start:   ! entry point

  !----------------------------------
  ! first of all, activate the cache
  !----------------------------------

  mov.l setup_cache_addr,r0               ! make sure to run in the P2 area
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop

setup_cache:

  mov.l ccr_addr,r0                       ! enable the cache
	mov.w	ccr_data,r1
	mov.l	r1,@r0

  ! After changing CCR, eight instructions must be executed before cached area can be entered

  mov.l go_addr,r0  ! 1
  nop               ! 2
  nop               ! 3
  nop               ! 4
  nop               ! 5
  nop               ! 6
  nop               ! 7
  nop               ! 8
  jmp @r0           ! go
  or  r0,r0 ! fill branch-delay slot

  ! following code is running in cached mode

go:

  mov.l stack_k,r15   ! init stackpointer

  !----------------------------------
  ! ZERO OUT BSS
  !----------------------------------

   mov.l edata_k,r0    ! addr. of end of data section
   mov.l end_k,r1      ! addr. of end of bss section
   mov #0,r2

 start_l:

   mov.l  r2,@r0
   add #4,r0
   cmp/ge  r0,r1
   bt  start_l

   mov.l set_fpscr_k, r1    ! init floating point stuff
   jsr @r1
   mov #0,r4

   lds r3,fpscr

  !----------------------------------
  ! CALL THE MAINLINE
  !----------------------------------

  mov.l start_k,r0          ! get address of function main
	jsr	@r0
  or  r0,r0                 ! fill branch-delay slot

  !----------------------------------
	! call exit
  !----------------------------------

! mov r0,r4
!
! mov.l exit_k,r0     ! get address of function exit
! jsr @r0
! or  r0,r0 ! fill branch-delay slot

  !----------------------------------
  ! reset the dc
  !----------------------------------

  mov.l reset_k,r0    ! get reset address
  jsr @r0
  or  r0,r0           ! fill branch-delay slot

!---------------------------------------------------------------------------------------------
! void __main(void) - called at the beginning of int main(void)
!---------------------------------------------------------------------------------------------
___main:
  rts
  nop

!---------------------------------------------------------------------------------------------
! void exit(int) - called at the end of int main(void)
!---------------------------------------------------------------------------------------------
!_exit:
!  rts
!  nop
!---------------------------------------------------------------------------------------------
!_atexit:
!  rts
!  nop
!---------------------------------------------------------------------------------------------

  .align  2

!---------------------------------------------------------------------------------------------
! these symbols will be resolved by the linker
!---------------------------------------------------------------------------------------------

start_k:
  .long _main    ! adress of int main(void)

!exit_k:
!  .long _exit    ! adress of void exit(int)

set_fpscr_k:
  .long ___set_fpscr  ! adress of floating point init

edata_k:              ! end of initialized data
  .long _edata

end_k:                ! end of bss area / start of heap memory
  .long _end

stack_k:
  .long _stack        ! stack top

!---------------------------------------------------------------------------------------------

reset_k:
  .long 0xa0000108    ! reset adress

setup_cache_addr:
	.long	setup_cache
go_addr:
  .long go
p2_mask:
	.long	0xa0000000
ccr_addr:
	.long	0xff00001c
ccr_data:
	.word	0x090d

!---------------------------------------------------------------------------------------------
! define a stack section
!---------------------------------------------------------------------------------------------

#ifdef __ELF__
	.section .stack,"aw"
#else
	.section .stack
#endif

!---------------------------------------------------------------------------------------------







