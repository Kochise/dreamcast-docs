
	! Dreamcast Serial example by marcus
	!
	! Set up the serial interface and
	! send some data
	!
	! To compile into SREC using GNU binutils:
	!
	! sh-elf-as -little -o serial.o serial.s
	! sh-elf-ld -EL --oformat srec -Ttext 0x8c010000 serial.o -o serial.srec


	.globl	start
	
	.text

start:
	! First, make sure to run in the P2 area
	mov.l	setup_cache_addr,r0
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop
setup_cache:
	! Now that we are in P2, it's safe
	! to enable the cache
	mov.l	ccr_addr,r0
	mov.w	ccr_data,r1
	mov.l	r1,@r0
	! After changing CCR, eight instructions
	! must be executed before it's safe to enter
	! a cached area such as P1
	mov.l	main_addr,r0	! 1
	mov	#0,r1		! 2
	nop			! 3
	nop			! 4
	nop			! 5
	nop			! 6
	nop			! 7
	nop			! 8
	jmp	@r0		! go
	mov	r1,r0

	.align	4
p2_mask:
	.long	0xa0000000
setup_cache_addr:
	.long	setup_cache
main_addr:
	.long	main
ccr_addr:
	.long	0xff00001c
ccr_data:
	.word	0x090d


	! Real program starts here.
main:
	mov.l	r14,@-r15
	sts	pr,r14

	! Setup serial port

	mov.l	baud_rate,r4
	bsr	init_serial
	nop

	! Send a greeting message

	mova	message,r0
	bsr	send_str
	mov	r0,r4

	! Make sure everything has actually been sent
	! to the port before returning

	bsr	flush
	nop

	lds	r14,pr
	rts
	mov.l	@r15+,r14


	.align	4
baud_rate:	
	.long	57600
message:
	.ascii	"Hello, world!"
	.byte	13,10,0

	.align	2


	! Initialize SCIF registers
	!
	! r4 = baudrate (must be >= 6092 bps)
init_serial:
	! Get base address of SCIF
	mov	#-24,r2
	shll16	r2
	! disable interrupts, disable transmit/receive, use internal clock
	mov	#0,r0
	mov.w	r0,@(8,r2)
	! 8N1, use PØ clock
	mov.w	r0,@r2
	! Set baudrate, N = PØ/(32*B)-1
	div0u
	mov.l	Pphi_32rds,r0
	mov	r4,r1
	shlr	r1
	add	r1,r0
	mov	#0,r1
	.rep	32
	rotcl	r0
	div1	r4,r1
	.endr
	rotcl	r0
	add	#-1,r0
	mov.b	r0,@(4,r2)
	! reset FIFOs, enable hardware flow control
	add	#8,r2
	mov	#12,r0
	mov.w	r0,@(16,r2)
	mov	#8,r0
	mov.w	r0,@(16,r2)
	! disable manual pin control
	mov	#0,r0
	mov.w	r0,@(24,r2)
	! clear status
	mov.w	@(8,r2),r0
	mov	#0x60,r0
	mov.w	r0,@(8,r2)
	mov.w	@(28,r2),r0
	mov	#0,r0
	mov.w	r0,@(28,r2)
	! enable transmit/receive
	mov	#0x30,r0
	rts
	mov.w	r0,@r2

	.align	4

Pphi_32rds:
	.long	50000000/32


	! Send a NUL-terminated string to the serial port
	!
	! r4 = string
send_str:
	mov	#-24,r2
	shll16	r2
	add	#12,r2
.ssloop1:
	mov.b	@r4+,r1
	tst	r1,r1
	bt	.endstr
	extu.b	r1,r1
.ssloop2:
	mov.w	@(4,r2),r0
	tst	#0x20,r0
	bt	.ssloop2
	mov.b	r1,@r2
	nop
	and	#0x9f,r0
	bra	.ssloop1
	mov.w	r0,@(4,r2)
.endstr:
	nop
	rts


	! Send a single character to the serial port
	!
	! r4 = character
send:
	mov	#-24,r2
	shll16	r2
	add	#12,r2
.sloop:	
	mov.w	@(4,r2),r0
	tst	#0x20,r0
	bt	.sloop
	mov.b	r4,@r2
	nop
	and	#0x9f,r0
	rts
	mov.w	r0,@(4,r2)


	! Check for serial input
	!
	! returns character or -1
recv:
	mov	#-24,r2
	shll16	r2
	add	#12,r2
	mov.w	@(16,r2),r0
	tst	#0x1f,r0
	bt	.norecv
	mov.b	@(8,r2),r0
	extu.b	r0,r1
	mov.w	@(4,r2),r0
	and	#0x6d,r0
	mov.w	r0,@(4,r2)
	rts
	mov	r1,r0
.norecv:
	rts
	mov	#-1,r0


	! Wait for serial input
	!
	! returns character
recvw:	
	sts	pr,r3
.rcvlp:	
	bsr	recv
	nop
	cmp/pz	r0
	bf	.rcvlp
	lds	r3,pr
	rts
	nop


	! Flush output FIFO
flush:
	mov	#-24,r2
	shll16	r2
	add	#12,r2
	mov.w	@(4,r2),r0
	and	#0xbf,r0
	mov.w	r0,@(4,r2)
.wflush:	
	mov.w	@(4,r2),r0
	tst	#64,r0
	bt	.wflush	
	and	#0xbf,r0
	rts
	mov.w	r0,@(4,r2)
	
	
	.end

	
