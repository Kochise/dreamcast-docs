! crt0.s for dcload
	
	.section .text
	.global	start
	.global _atexit
	.global _dcloadsyscall
start:
	bra	realstart
	nop

! for checking if dcload is present
	
dcloadmagic:
	.long 0xdeadbeef

! normal programs use this call
	
dcloadsyscall_k:	
	.long _dcloadsyscall
		
! exception handler uses these calls

setup_video_k:	
	.long _setup_video	
clrscr_k:
	.long _clrscr
draw_string_k:
	.long _draw_string
uint_to_string_k:
	.long _uint_to_string
exc_to_string_k:
	.long _exception_code_to_string
					
realstart:
	stc	sr,r0
	mov.l	sr_mask,r1
	and	r1,r0	
	or	#0xf0,r0	
	ldc	r0,sr
	mov.l	setup_cache_k,r0
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop
	
setup_cache:
	mov.l	ccr_addr,r0
	mov.w	ccr_data,r1
	mov.l	r1,@r0
	mov.l	start_2_k,r0
	mov	#0,r1	
	nop
	nop
	nop
	nop
	nop
	nop
	jmp	@r0
	mov	r1,r0	

start_2:
	mov.l	stack_k,r15
	! zero out bss
	mov.l	edata_k,r0
	mov.l	end_k,r1
	mov	#0,r2

start_l:
	mov.l	r2,@r0
	add	#4,r0
	cmp/ge	r0,r1
	bt	start_l

	mov.l set_fpscr_k, r1
	jsr @r1
	mov #0,r4
	lds r3,fpscr

	! call main	
	mov.l	main_k,r0
	jsr	@r0
	or	r0,r0
	! bootloader should never exit, but what the hell
	bra	realstart
	nop

_atexit:
	rts
	nop


	.align 4
sr_mask:
	.long	0xefff7fff
set_fpscr_k:
	.long	___set_fpscr
stack_k:
	.long	_stack	
edata_k:
	.long	_edata
end_k:
	.long	_end
main_k:
	.long	_main
setup_cache_k:
	.long	setup_cache
start_2_k:	
	.long	start_2	
p2_mask:
	.long	0xa0000000
ccr_addr:
	.long	0xff00001c
ccr_data:
	.word	0x090b

_dcloadsyscall:
	mov.l	dcloadmagic_k,r1
	mov.l	@r1,r1
	mov.l	correctmagic,r0
	cmp/eq	r0,r1
	bf	badsyscall
	
	mov	r4,r0
	mov	r5,r4
	mov	r6,r5
	mov	r7,r6

	mov	#20,r1
	cmp/hs	r0,r1
	bf	badsyscall

	mov.l	first_syscall,r1
	shll2	r0
	mov.l	@(r0,r1),r0
	jmp	@r0
	nop
	
badsyscall:	
	mov	#-1,r0
	rts
	nop

.align 4
dcloadmagic_k:
	.long dcloadmagic
correctmagic:
	.long 0xdeadbeef 
first_syscall:
	.long read_k
read_k:
        .long _read
write_k:
        .long _write
open_k:
        .long _open
close_k:
        .long _close
creat_k:
        .long _creat
link_k:
        .long _link
unlink_k:
        .long _unlink
chdir_k:
        .long _chdir
chmod_k:        
        .long _chmod
lseek_k:
        .long _lseek
fstat_k:
        .long _fstat
time_k:
        .long _time
stat_k:
        .long _stat
utime_k:
        .long _utime
assign_wrkmem_k:
	.long badsyscall
exit_k:
	.long _dcexit
opendir_k:
	.long _opendir
closedir_k:
	.long _closedir
readdir_k:
	.long _readdir
hostinfo_k:	
	.long _gethostinfo
gdbpacket_k:
	.long _gdbpacket
