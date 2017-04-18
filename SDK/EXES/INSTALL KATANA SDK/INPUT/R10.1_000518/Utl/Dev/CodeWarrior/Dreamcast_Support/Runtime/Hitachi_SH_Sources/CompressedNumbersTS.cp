
/*
 *	CompressedNumbersTS.cp	-	Hitachi SH implementation of compressed number decoding
 *
 *  Copyright © 1999 Metrowerks, Inc.  All rights reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	If a target CPU supports a shift-right instruction that permits testing whether
 *	the shifted-out bit was a 0 or 1, then it is best to provide an assembly-language
 *	implementation of __DecodeSignedNumber() and __DecodeUnsignedNumber().
 *
 */

#include "CompressedNumbers.h"


/*
 *	__DecodeSignedNumber	-	decode the signed integer number stored at location 'p'
 *
 *	Decode a signed number stored in compressed format at location 'p' and return
 *	the decoded value in '*pnum'. We return the pointer to just past the end of the
 *	decoded number.
 *
 *	We assume that signed values outside the range -2^28 .. 2^28-1 are impossible,
 *	and we encode signed integers like this:
 *
 *		-64..63			sxxxxxx0 =>
 *						ssssssss ssssssss ssssssss ssxxxxxx
 *
 *		-2^13..2^13-1	sxxxxx01 yyyyyyyy =>
 *						ssssssss ssssssss sssxxxxx yyyyyyyy
 *
 *		-2^20..2^20-1	sxxxx011 yyyyyyyy zzzzzzzz =>
 *						ssssssss ssssxxxx yyyyyyyy zzzzzzzz
 *
 *		-2^28..2^28-1	sxxxx111 yyyyyyyy zzzzzzzz wwwwwwww =>
 *						ssssxxxx yyyyyyyy zzzzzzzz wwwwwwww
 *
 */

char *__DecodeSignedNumber(register char *p, register long *pnum)
{
	signed long x, y, z, w;

	x = ((signed char *) p)[0];
	
	if ((x & 0x01) == 0) { *pnum = (x >> 1); return(p + 1); }

	y = ((unsigned char *) p)[1];

	if ((x & 0x02) == 0) { *pnum = (((x >> 2) << 8) | y); return(p + 2); }

	z = ((unsigned char *) p)[2];

	if ((x & 0x04) == 0) { *pnum = (((x >> 3) << 16) | (y << 8) | z); return(p + 3); }

	w = ((unsigned char *) p)[3];

	*pnum = (((x >> 3) << 24) | (y << 16) | (z << 8) | w); return(p + 4);
}


/*
 *	__DecodeUnsignedNumber	-	decode the signed integer number stored at location 'p'
 *
 *	Decode an unsigned number stored in compressed format at location 'p' and return
 *	the decoded value in '*pnum'. We return the pointer to just past the end of the
 *	decoded number.
 *
 *	We assume that unsigned values outside the range 0 .. 2^29-1 are impossible,
 *	and we encode unsigned integers like this:
 *
 *		0..127			xxxxxxx0 =>
 *						00000000 00000000 00000000 0xxxxxxx
 *
 *		0..2^14-1		xxxxxx01 yyyyyyyy =>
 *						00000000 00000000 00xxxxxx yyyyyyyy
 *
 *		0..2^21-1		xxxxx011 yyyyyyyy zzzzzzzz =>
 *						00000000 000xxxxx yyyyyyyy zzzzzzzz
 *
 *		0..2^29-1		xxxxx111 yyyyyyyy zzzzzzzz wwwwwwww =>
 *						000xxxxx yyyyyyyy zzzzzzzz wwwwwwww
 *
 */

char *__DecodeUnsignedNumber(register char *p, register unsigned long *pnum)
{
	unsigned long x, y, z, w;

	x = ((unsigned char *) p)[0];
	
	if ((x & 0x01) == 0) { *pnum = (x >> 1); return(p + 1); }

	y = ((unsigned char *) p)[1];

	if ((x & 0x02) == 0) { *pnum = (((x >> 2) << 8) | y); return(p + 2); }

	z = ((unsigned char *) p)[2];

	if ((x & 0x04) == 0) { *pnum = (((x >> 3) << 16) | (y << 8) | z); return(p + 3); }

	w = ((unsigned char *) p)[3];

	*pnum = (((x >> 3) << 24) | (y << 16) | (z << 8) | w); return(p + 4);
}
