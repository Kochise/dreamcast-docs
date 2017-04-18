;
;  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
;
;  File: sclblt.asm
;
;	Assembler 3x3 -> 2x2 averaging downsampler.
;

include iammx.inc

.586
.model FLAT

CLEAR_SRC_BUFFER	equ	0
RGB555			equ	0
	

if RGB555
RMASK			equ	07c000h
GMASK			equ	03e0h
GSHIFT			equ	5 + 5 + 2
else
RMASK			equ	0f8000h
GMASK			equ	07e0h
GSHIFT			equ	5 + 6 + 2
endif
	
BMASK			equ	01fh
RBMASK			equ	(RMASK shr 4 ) or BMASK
RBMASK_GMASK_shl	equ	RBMASK or ( GMASK shl 16 )

.data
align 8

filtered_pix	dq	0
unpckd_pxls	dd	0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0

MMX_RMASK		dd	RMASK shr 4, RMASK shr 4
MMX_GMASK		dd	GMASK, GMASK
MMX_RBMASK_GMASK_shl	dd	RBMASK_GMASK_shl, RBMASK_GMASK_shl

MMX_BMASK	dd	BMASK, BMASK
MMX_RBMASK	dd	RMASK shr 4 or BMASK, RMASK shr 4 or BMASK

MMX_hi32	dq	0ffffffff00000000h
MMX_low32	dq	000000000ffffffffh

j	dd	0
k	dd	0
xincr	dd	0
yincr	dd	0
idst	dd	0


.code
sclblt1 PROC NEAR C USES eax ebx ecx edx esi edi ebp,
		dst:PTR UWORD, src:PTR UWORD,
		w:DWORD, h:DWORD,
		ss2:DWORD, ds2:DWORD
		
;		ss2:DWORD, ds2:DWORD, ss4:DWORD



;	eax	ebx	ecx	edx	esi	edi	ebp
;
;	 *	 *	 *	 *	src	 *	 k

	xor	edx,edx
	mov	esi,dword ptr [src]
	
	mov	dword ptr[j],edx
	mov	dword ptr [yincr],1
	
    outer_loop:
    	mov	dword ptr [idst],0
    	mov	eax,dword ptr[j]
	xor	edi,edi

	cmp	eax,dword ptr [h]
	jge	outer_done
	
	mov	dword ptr [xincr],1
	cmp	edi,dword ptr [w]
    inner_loop:
	
	jge	inner_done
	mov	dx,word ptr[esi + 2*edi]

	mov	ebx,edx
	mov	ecx,edx

	shl	ebx,4
	and	ecx,GMASK

if CLEAR_SRC_BUFFER
	mov	word ptr[esi + 2*edi],0
endif

	and	ebx,RMASK
	and	dl,BMASK

	shl	ecx,2
	mov	bl,dl

	mov	dx,word ptr[esi + 2*edi + 2]
	or	ebx,ecx

	mov	eax,edx
	mov	ecx,edx

	shl	eax,4
	and	ecx,GMASK

if CLEAR_SRC_BUFFER
	mov	word ptr[esi + 2*edi + 2],0
endif
	add	esi,[ss2]

	and	eax,RMASK
	and	dl,BMASK

	shl	ecx,2
	mov	al,dl

	mov	dx,word ptr[esi + 2*edi]
	or	eax,ecx

	add	ebx,eax

	mov	eax,edx
	mov	ecx,edx

if CLEAR_SRC_BUFFER
	mov	word ptr[esi + 2*edi],0
endif

	shl	eax,4
	and	ecx,GMASK

	and	eax,RMASK
	and	dl,BMASK

	shl	ecx,2
	mov	al,dl

	or	eax,ecx

	mov	dx,word ptr[esi + 2*edi + 2]
	add	ebx,eax


	mov	eax,edx
	mov	ecx,edx

	shl	eax,4
	and	ecx,GMASK

	and	eax,RMASK
	and	dl,BMASK

if CLEAR_SRC_BUFFER
	mov	word ptr[esi + 2*edi + 2],0
endif

	shl	ecx,2
	mov	al,dl

	or	eax,ecx
	mov	ecx,[xincr]
	
	add	edi,ecx
	sub	ecx,3
	
	add	ebx,eax
	neg	ecx

	mov	[xincr],ecx
	sub	esi,[ss2]

	mov	eax,ebx
	mov	edx,ebx

	shr	ebx,6
	and	eax,GMASK shl 4

	shr	eax,4
	and	ebx,RMASK shr 4

	shr	edx,2
	mov	ecx,dword ptr [dst]

	and	edx,BMASK
	or	ebx,eax
	
	mov	eax,[idst]
	inc	[idst]

	or	ebx,edx
	cmp	edi,dword ptr [w]

	mov	word ptr [ecx + 2*eax],bx
	jmp	inner_loop

    inner_done:
	mov	eax,[yincr]
	add	esi,dword ptr [ss2]
	
	add	[j],eax
	sub	eax,3
	
	neg	eax

	mov	[yincr],eax
	add	ecx,dword ptr [ds2]
	
	cmp	eax,1
	je	miss_add
	
	add	esi,dword ptr [ss2]
	
    miss_add:
	mov	dword ptr [dst],ecx
	jmp	outer_loop

    outer_done:
    	ret
	
sclblt1 ENDP
    
UNPACK_TWO_PIXELS	macro	col, row
	mov	edx,dword ptr[esi + 2*edi + col]

	mov	ebx,edx
	mov	ecx,edx

	shl	ebx,4
	and	ecx,GMASK

	and	ebx,RMASK
	and	dl,BMASK

	shl	ecx,2
	mov	bl,dl

	shr	edx,16
	or	ebx,ecx
	
	mov	dword ptr [unpckd_pxls + 2*col + 24*row],ebx
	mov	eax,edx

	shl	eax,4
	mov	ecx,edx

	and	ecx,GMASK
	and	eax,RMASK

	shl	ecx,2
	and	dl,BMASK

	mov	al,dl

	or	eax,ecx
	
	mov	dword ptr [unpckd_pxls + 2*col + 24*row + 4],eax
    endm
	
PACK_ONE_PIXEL	macro	pix, scr1, scr2
	; Pixel sum in pix: average, pack and write pixel
	
	mov	scr1,pix
	mov	scr2,pix

	shr	pix,6
	and	scr1,GMASK shl 4

	shr	scr1,4
	and	pix,RMASK shr 4

	shr	scr2,2
	;

	and	scr2,BMASK
	or	pix,scr1

	or	pix,scr2
    endm
	
FILTER_FOUR_PIXELS	macro pix, offs, scr1, scr2
       	mov	pix,dword ptr [unpckd_pxls + offs +  0]
       	mov	scr1,dword ptr [unpckd_pxls + offs +  4]
	
       	add	pix,dword ptr [unpckd_pxls + offs + 24]
       	add	scr1,dword ptr [unpckd_pxls + offs + 28]
	
	add	pix,scr1
	
      	PACK_ONE_PIXEL	pix, scr1, scr2
    endm
    

sclblt_int PROC NEAR C USES eax ebx ecx edx esi edi ebp,
		dst:PTR UWORD, src:PTR UWORD,
		w:DWORD, h:DWORD,
		ss2:DWORD, ds2:DWORD
		


;	eax	ebx	ecx	edx	esi	edi	ebp
;
;	 *	 *	 *	 *	src	 *	 k

	xor	edx,edx
	mov	esi,dword ptr [src]
	
	mov	dword ptr[j],edx
	
    outer_loop:
    	mov	dword ptr [idst],0
    	mov	eax,dword ptr[j]
	xor	edi,edi

	cmp	eax,dword ptr [h]
	jge	outer_done
	
	cmp	edi,dword ptr [w]
    inner_loop:
    	; Read and unpack three rows of 6 pixels
	
	jge	inner_done
	
    	UNPACK_TWO_PIXELS 0,0
    	UNPACK_TWO_PIXELS 4,0
    	UNPACK_TWO_PIXELS 8,0
	
	add	esi,[ss2]
    
    	UNPACK_TWO_PIXELS 0,1
    	UNPACK_TWO_PIXELS 4,1
    	UNPACK_TWO_PIXELS 8,1
	
	add	esi,[ss2]
    
    	UNPACK_TWO_PIXELS 0,2
    	UNPACK_TWO_PIXELS 4,2
    	UNPACK_TWO_PIXELS 8,2
	
	sub	esi,[ss2]
	sub	esi,[ss2]
	
	add	edi,6
	
	FILTER_FOUR_PIXELS ebx, 0, eax, edx
	FILTER_FOUR_PIXELS ecx, 4, eax, edx

	mov	eax,[idst]
	mov	edx,[dst]
	
	shl	ecx,16
	or	ebx,ecx
	
	mov	dword ptr [edx + 4*eax + 0],ebx
	
	
	FILTER_FOUR_PIXELS ebx, 12, eax, edx
	FILTER_FOUR_PIXELS ecx, 16, eax, edx

	mov	eax,[idst]
	mov	edx,[dst]
	
	shl	ecx,16
	or	ebx,ecx

	mov	dword ptr [edx + 4*eax + 4],ebx
	
	
	FILTER_FOUR_PIXELS ebx, 24, eax, edx
	FILTER_FOUR_PIXELS ecx, 28, eax, edx

	mov	eax,[idst]
	mov	edx,[dst]
	
	add	edx,dword ptr [ds2]
	
	shl	ecx,16
	or	ebx,ecx
	
	mov	dword ptr [edx + 4*eax + 0],ebx
	
	
	FILTER_FOUR_PIXELS ebx, 36, eax, edx
	FILTER_FOUR_PIXELS ecx, 40, eax, edx

	mov	eax,[idst]
	mov	edx,[dst]
	
	add	edx,dword ptr [ds2]
	
	shl	ecx,16
	or	ebx,ecx

	mov	dword ptr [edx + 4*eax + 4],ebx
	
	sub	edx,dword ptr [ds2]
	add	[idst],2
	
	cmp	edi,dword ptr [w]
	jmp	inner_loop

    inner_done:
	add	[j],3
	
	add	esi,[ss2]
	add	esi,[ss2]
	add	esi,[ss2]
	
	add	edx,dword ptr [ds2]
	add	edx,dword ptr [ds2]
	
	mov	dword ptr [dst],edx
	jmp	outer_loop

    outer_done:
    	ret
	
sclblt_int ENDP
    
    
MMX_UNPACK_TWO_PIXELS	macro	col, mmx_reg, next_mmx_reg
	
       	punpcklwd mmx_reg,mm0	; mmx_reg = pix1:pix0

	movq	mm1,mmx_reg
	pslld	mmx_reg,16

    if col ne 0
	movdt	next_mmx_reg,[esi + 2*edi + col]
    else
	add	esi,eax
    endif
       	por	mmx_reg,mm1

	pand	mmx_reg,[MMX_RBMASK_GMASK_shl]
    endm
	
MMX_PACK_TWO_PIXELS	macro	pix, scr
	; Pixel sum in pix: average and pack two pixels
	
	psrld	pix,2
	nop

	pand	pix,[MMX_RBMASK_GMASK_shl]
	nop
	
	movq	scr,pix
	psrld	pix,16
	
	por	pix,scr
	nop

       	movq	scr,pix		; pix = scr = 0,a:0,b
	psrlq	pix,32		; pix = 0,0:0,a
	
	punpcklwd pix, scr	; pix = 0,0:b,a
    endm
	
MMX_GEN_FOUR_PIXELS	macro sum1, sum2, sum3, base, indx
	
	movq	mm0,sum1	; sum1 = mm0 = b:a
	movq	mm1,sum2	; sum2 = mm1 = d:c

       	pand	mm1,[MMX_low32]	; mm1 = 0:c
	psllq	sum1,32		; sum1 = a:0
	
	punpckhdq mm0,mm0	; mm0 = b:b
	por	mm1,sum1	; mm1 = a:c
	
       	pand	sum2,[MMX_hi32]	; sum2 = d:0
	paddd	mm0,mm1		; mm0 = a+b:b+c
	
      	MMX_PACK_TWO_PIXELS mm0, mm1
	movq	mm1,sum3	; sum3 = mm1 = f:e
	
	psrlq	sum3,32		; sum3 = 0:f
	nop
	
	punpckldq mm1,mm1	; mm1 = e:e
	por	sum2,sum3	; sum2 = d:f
	
	movdf	dword ptr [base + 8*indx + 0],mm0
	paddd	mm1,sum2	; mm1 = d+e:e+f
	
      	MMX_PACK_TWO_PIXELS mm1, sum2
	pxor	mm0,mm0
	
	movdf	dword ptr [base + 8*indx + 4],mm1
    endm
    
   
; MMX version

sclblt PROC NEAR C USES eax ebx ecx edx esi edi ebp,
		dst:PTR UWORD, src:PTR UWORD,
		w:DWORD, h:DWORD,
		ss2:DWORD, ds2:DWORD
		


;	eax	ebx	ecx	edx	esi	edi	ebp
;
;	 *	 *	 *	 *	src	 *	 k

	mov	esi,dword ptr [src]
	xor	ecx,ecx			; ecx = idst
	
	mov	dword ptr[j],edx
	mov	edx,[dst]
	
    outer_loop:
    	mov	eax,dword ptr[j]
	xor	edi,edi

	cmp	eax,dword ptr [h]
	jge	outer_done
	
	cmp	edi,dword ptr [w]
	jz	inner_done
    inner_loop:
    	; Read and unpack three rows of 6 pixels
	
	movdt	mm2,[esi + 2*edi + 0]
	pxor	mm0,mm0
	
       	mov	eax,[ss2]
    	MMX_UNPACK_TWO_PIXELS 4, mm2, mm3
    	MMX_UNPACK_TWO_PIXELS 8, mm3, mm4
    	MMX_UNPACK_TWO_PIXELS 0, mm4, xxx
	
	movdt	mm5,[esi + 2*edi + 0]
    
    	MMX_UNPACK_TWO_PIXELS 4, mm5, mm6
    	MMX_UNPACK_TWO_PIXELS 8, mm6, mm7
    	MMX_UNPACK_TWO_PIXELS 0, mm7, xxx
	paddd	mm2,mm5
	
	paddd	mm3,mm6
	paddd	mm4,mm7
	
	MMX_GEN_FOUR_PIXELS mm2, mm3, mm4, edx, ecx
	
	movdt	mm2,[esi + 2*edi + 0]
    
    	MMX_UNPACK_TWO_PIXELS 4, mm2, mm3
    	MMX_UNPACK_TWO_PIXELS 8, mm3, mm4
    	MMX_UNPACK_TWO_PIXELS 0, mm4, xxx
	paddd	mm2,mm5
	
	sub	esi,eax
	paddd	mm3,mm6
	
	paddd	mm4,mm7
	sub	esi,eax
	
	sub	esi,eax
	mov	eax,dword ptr [ds2]
	
	add	edi,6
	add	edx,eax
	
	MMX_GEN_FOUR_PIXELS mm2, mm3, mm4, edx, ecx
	
	sub	edx,eax
	inc	ecx
	
	cmp	edi,dword ptr [w]
	jl	inner_loop

    inner_done:
	add	[j],3
	xor	ecx,ecx
	
	add	esi,[ss2]
	add	edx,dword ptr [ds2]
	
	add	esi,[ss2]
	add	edx,dword ptr [ds2]
	
	add	esi,[ss2]
	jmp	outer_loop

    outer_done:
    	emms
    	ret
	
sclblt ENDP
    
MEM_UNPACK_TWO_PIXELS	macro	col, row
	mov	ebx,[esi + 2*edi + col]
    endm
	
MEM_PACK_TWO_PIXELS	macro	pix
    endm
	
MEM_FILTER_EIGHT_PIXELS	macro pix, offs, scr
    endm
    
   
; Memory read/writes only version

sclblt_mem PROC NEAR C USES eax ebx ecx edx esi edi ebp,
		dst:PTR UWORD, src:PTR UWORD,
		w:DWORD, h:DWORD,
		ss2:DWORD, ds2:DWORD
		


;	eax	ebx	ecx	edx	esi	edi	ebp
;
;	 *	 *	 *	 *	src	 *	 k

	xor	edx,edx
	mov	esi,dword ptr [src]
	
	mov	dword ptr[j],edx
	
    outer_loop:
    	mov	dword ptr [idst],0
    	mov	eax,dword ptr[j]
	xor	edi,edi

	cmp	eax,dword ptr [h]
	jge	outer_done
	
	cmp	edi,dword ptr [w]
    inner_loop:
    	; Read and unpack three rows of 6 pixels
	
	jge	inner_done
	
    	MEM_UNPACK_TWO_PIXELS 0,0
    	MEM_UNPACK_TWO_PIXELS 4,0
    	MEM_UNPACK_TWO_PIXELS 8,0
	
	add	esi,[ss2]
    
    	MEM_UNPACK_TWO_PIXELS 0,1
    	MEM_UNPACK_TWO_PIXELS 4,1
    	MEM_UNPACK_TWO_PIXELS 8,1
	
	add	esi,[ss2]
    
    	MEM_UNPACK_TWO_PIXELS 0,2
    	MEM_UNPACK_TWO_PIXELS 4,2
    	MEM_UNPACK_TWO_PIXELS 8,2
	
	sub	esi,[ss2]
	sub	esi,[ss2]
	
	add	edi,6

	mov	ecx,[idst]
	mov	edx,[dst]
	
	MEM_FILTER_EIGHT_PIXELS ebx, 0, eax
	
	mov	dword ptr [edx + 4*ecx + 0],ebx
	
	
	MEM_FILTER_EIGHT_PIXELS ebx, 12, eax

	mov	dword ptr [edx + 4*ecx + 4],ebx
	
	
	add	edx,dword ptr [ds2]
	
	MEM_FILTER_EIGHT_PIXELS ebx, 24, eax
	
	mov	dword ptr [edx + 4*ecx + 0],ebx
	
	
	MEM_FILTER_EIGHT_PIXELS ebx, 36, eax

	mov	dword ptr [edx + 4*ecx + 4],ebx
	
	sub	edx,dword ptr [ds2]
	add	[idst],2
	
	cmp	edi,dword ptr [w]
	jmp	inner_loop

    inner_done:
	add	[j],3
	
	add	esi,[ss2]
	add	esi,[ss2]
	add	esi,[ss2]
	
	add	edx,dword ptr [ds2]
	add	edx,dword ptr [ds2]
	
	mov	dword ptr [dst],edx
	jmp	outer_loop

    outer_done:
    	emms
    	ret
	
sclblt_mem ENDP
    
END
    
