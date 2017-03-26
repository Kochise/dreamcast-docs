	.globl _bswap16, _bswap32

	.text

	! r4 = dest

_bswap16:
	rts	
	swap.b	r4,r0

_bswap32:
	swap.b	r4,r0
	swap.w	r0,r4
	rts
	swap.b	r4,r0
	
	.end

