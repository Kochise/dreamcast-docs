
	! SH4 matrix operations
	!
	! The matrix is kept in the XMTRX register set between calls

	
	.globl _clear_matrix, _apply_matrix, _transform_coords

	.text


	! Initialize the matrix to the identity matrix
	!
	! no args
	
_clear_matrix:
	fldi0 fr0
	fldi0 fr1
	fldi1 fr2
	fldi0 fr3
	fldi0 fr4
	fldi1 fr5
	fschg
	fmov dr2,xd0
	fmov dr0,xd2
	fmov dr4,xd4
	fmov dr0,xd6
	fmov dr0,xd8
	fmov dr2,xd10
	fmov dr0,xd12
	fmov dr4,xd14
	rts
	fschg



	! Multiply another matrix to the current matrix
	!
	! r4 = pointer to the other matrix (4 * 4 floats)

_apply_matrix:
	fmov.s @r4+,fr0
	fmov.s @r4+,fr1
	fmov.s @r4+,fr2
	fmov.s @r4+,fr3
	ftrv xmtrx,fv0
	fmov.s @r4+,fr4
	fmov.s @r4+,fr5
	fmov.s @r4+,fr6
	fmov.s @r4+,fr7
	ftrv xmtrx,fv4
	fmov.s @r4+,fr8
	fmov.s @r4+,fr9
	fmov.s @r4+,fr10
	fmov.s @r4+,fr11
	ftrv xmtrx,fv8
	fmov.s @r4+,fr12
	fmov.s @r4+,fr13
	fmov.s @r4+,fr14
	fmov.s @r4+,fr15
	ftrv xmtrx,fv12
	fschg
	fmov dr0,xd0
	fmov dr2,xd2
	fmov dr4,xd4
	fmov dr6,xd6
	fmov dr8,xd8
	fmov dr10,xd10
	fmov dr12,xd12
	fmov dr14,xd14
	rts
	fschg


	! Multiply a set of 3D vectors with the matrix
	! (vectors are extended to 4D homogenous coordinates by
	!  setting W=1), and then normalize the resulting
	! vectors before storing them in the result array
	!
	! r4 = pointer to a source set of 3D vectors (n * 3 floats)
	! r5 = pointer to a destination set of 3D vectors ( - " - )
	! r6 = number of vectors to transform

_transform_coords:
	pref @r4
	mov r5,r0
	mov #4,r1
	mov r4,r3
	mov #8,r2
	add #32,r3
.loop:
	fmov.s @r4+,fr0
	fmov.s @r4+,fr1
	fmov.s @r4+,fr2
	fldi1 fr3
	pref @r3
	ftrv xmtrx,fv0
	dt r6
	fdiv fr3,fr0
	fmov.s fr0,@r0
	fdiv fr3,fr1
	fmov.s fr1,@(r0,r1)
	fdiv fr3,fr2
	add #4*3,r3
	fmov.s fr2,@(r0,r2)
	bf/s .loop
	add #4*3,r0
	rts	
	nop

	.end

