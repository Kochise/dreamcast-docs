; KallistiOS ##version##
;
; loader.asm
; Copyright (C)1997,2003 Dan Potter
;

;
; This file is meant to be compiled with NASM, so you'll need NASM in order
; to build KOS/ia32. NASM is GPL'd and available in all the normal places...
;


;;;;; Fake Linux zImage Header ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	; The loader will start us at 9020:0600, yet it loads us at
	; 9000:0000. So we need an 0x800 byte header, but the code itself
	; still starts at 0x600. Yet nasm will not let us be naughty and use
	; a negative origin, so we cheat a little here. This has some
	; implications below for calculated offsets in 32-bit code.
	org	0x10000-0x200

	; First a fake boot sector
	times	0x20 db 0
	dw	0xa33f		; magic
	dw	0		; command line
	times	0x1f1-0x20-2-2 db 0	; part table
	db	7		; setup sectors
	dw	0		; readonly
	dw	0		; obsolete
	dw	0
	dw	0
	dw	0		; vid mode control
	dw	0		; root dev
	dw	0xaa55		; boot magic
	
	; Now the linux kernel header
	jmp	short trampolene

	db	'HdrS'		; signature
	dw	0x0203		; version
	dw	0,0		; default_switch, SETUPSEG
	dw	0x1000		; SYSSEG
	dw	0		; kernel_version
	db	0		; loader type
	db	0		; loaded high? (e.g., bzImage)
	dw	0x8000		; setup move size
	dd	0x1000		; code start location
	dd	0		; ramdisk image
	dd	0		; ramdisk size
	dw	0,0x9020	; bootsect_helper, SETUPSEG

trampolene:
	jmp	start

	; Scoot up to the 0x800 mark
	times	0x800-($-$$) db 0
stack_top:

;;;;; Main real mode section ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
start:
	; Setup our segments
	mov	ax,cs
	mov	ds,ax
	mov	ss,ax

	; And a little stack (so we have control for pmode)
	mov	ax,stack_top
	mov	sp,ax

	; Reset text mode (let 'em know we're alive)
	mov	ah,0
	mov	al,3
	int	0x10

	; Fill in the rest of gdt_reg
	mov	ax,ds
	movzx	eax,ax
	shl	eax,4
	add	eax,dummy_dscr - 0x10000
	mov	dword [ds:gdt_reg+2],eax

	; Enable the A20 line
	call	enable_a20

	; Load the GDT
	lgdt	[ds:gdt_reg]
	mov	eax,cr0
	or	al,1
	mov	cr0,eax

	; Do a 32-bit jump into pmode code
	db	0xea
	dw	pm_start
	dw	3*8		; our pm code selector

	align	4

; Enable the A20 line
; Thanks to Charles Sandmann / DJ Delorie for this algorithm
enable_a20:
	cli

	in	al,0x92		; 0x92 PS/2 control port "A"
	or	al,2		; Set the A20 bit
	jmp	$+2		; Flush the instruction prefetch
	out	0x92,al		; Set it

	call	check_a20
	jz	a20_done

need_to_set_a20:
	call	waitkb
	mov	al,0xd1
	out	0x64,al
	call	waitkb
	mov	al,0xdf
	out	0x60,al
	call	waitkb
	mov	al,0xff
	out	0x64,al
	call	waitkb

wait_for_valid_a20:
	call	check_a20
	jnz	wait_for_valid_a20

a20_done:
	ret

; Returns z bit set if a20 enabled
check_a20:
	push	bx
	xor	ax,ax
	mov	fs,ax
	dec	ax		; AX = 0xffff
	mov	gs,ax
	xor	bx,bx

	mov	ax,[fs:bx]	; Word from 0:0 (int 0 interrupt)
	mov	dx,ax
	not	ax		; Make a different value
	xchg	ax,[gs:bx+0x10]	; Modify ffff:0010 to known different value
	xchg	cx,[fs:bx]	; Get fs:0 with a write
	cmp	dx,cx		; Compare with saved; z bit if same = a20
	mov	[gs:bx+0x10],ax	; Restore
	mov	[fs:bx],dx

	pop	bx
	ret

; Do a little delay using the KB controller
waitkb:
	xor	cx,cx
waitkb1:
	jmp	$+2
	jcxz	$+2
	in	al,0x64
	test	al,2
	loopnz	waitkb1
	ret


;;;;; Protected mode descriptor table ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	align	4

; Our GDT data
gdt_reg		dw	gdt_size
		dd	0	; Need to fill this with a linear address

dummy_dscr:		; NULL descriptor
	dw	0,0		; seg length<15:0>, base address<15:0>
	db	0		; base address<23:16>
	db	0		; segment type and flags
	db	0		; seg length<31:28>, access flags
	db	0		; base address<31:24>

; Kernel code descriptor - 4GB Code, base = 0
krn_code32_dscr:
	dw	0xffff,0
	db	0x00, 0x9a, 0xcf, 0x00

; Kernel data descriptor - 4GB Data, base = 0
krn_data32_dscr:
	dw	0xffff,0
	db	0x00, 0x92, 0xcf, 0x00

; Boot loader code descriptor - 4GB Code, base = our codeseg
code32_dscr:
	dw	0xffff,0x0200
	db	0x09, 0x9a, 0xcf, 0x00

; Boot loader data descriptor - 4GB Data, base = our codeseg
data32_dscr:
	dw	0xffff,0x0200
	db	0x09, 0x92, 0xcf, 0x00

gdt_size	equ	$-dummy_dscr


;;;;; Protected mode from here on down ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	bits	32

pm_start:
	; Clear out old real mode segments
	mov	ax,4*8		; data32_dscr
	mov	ss,ax

	mov	ax,2*8		; krn_data32_dscr
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax

	; Jump to the loaded program (at 0x10000)
	db	0xea
	dd	0x10000
	dw	1*8

; Fill to the end of 8 sectors
	times	0x1000-($-$$) db 0
