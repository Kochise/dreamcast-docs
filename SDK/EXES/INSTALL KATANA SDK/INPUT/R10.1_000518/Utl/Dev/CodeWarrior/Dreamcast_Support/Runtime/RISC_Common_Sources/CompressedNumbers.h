
/*
 *	CompressedNumbers.h		-	decode compressed numeric values from Exception Tables
 *
 *  Copyright © 1997 Metrowerks, Inc.  All rights reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	In order to keep the size of our C++ exception tables as small as possible,
 *	we represent all non-address numeric fields in a compressed format which
 *	lets us store most values in only 8 or 16 bits instead of 32.
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
 *	We don't compress any values (i.e. addresses) which require link-time relocation,
 *	but since they are not aligned to a 32-bit boundary in the tables, we provide
 *	another inline function for accessing them.
 *
 *	We can readily determine the number of bytes used to represent an encoded
 *	number by examining just the low 3 bits of the first byte:
 *
 *		xx0				1 byte
 *		x01				2 bytes
 *		011				3 bytes
 *		111				4 bytes
 *
 *	The inline function __SizeofNumber() defined below has a reasonably efficient
 *	implementation of this, without resorting to unnecessary loads or control-flow.
 *
 *	We leave the actual decoding of a compressed value to the target-specific
 *	portion of the exception handler, as it is most efficiently coded in assembly
 *	language on most targets.
 *
 */

#ifndef __COMPRESSEDNUMBERS_H__
#define __COMPRESSEDNUMBERS_H__


/*
 *	__SizeofNumber	-	return the # bytes used to encode the number stored at location 'p'
 *
 *	We represent the mapping
 *
 *		000		=>		1 byte
 *		001		=>		2 bytes
 *		010		=>		1 byte
 *		011		=>		3 bytes
 *		100		=>		1 byte
 *		101		=>		2 bytes
 *		110		=>		1 byte
 *		111		=>		4 bytes
 *
 *	by encoding the length array as a single 32-bit constant which we can shift and
 *	mask to extract the value corresponding to the low 3 bits of the compressed number.
 *
 */

inline int __SizeofNumber(void *p)
{
	return((0x41213121 >> (*(char *)p & 7)) & 0x0000000F);
}


/*
 *	__DecodeSignedNumber	-	decode the signed integer number stored at location 'p'
 *
 *	Decode a signed number stored in compressed format at location 'p' and return
 *	the decoded value in '*pnum'. We return the pointer to just past the end of the
 *	decoded number.
 *
 *	We declare this function 'extern' so that a target-specific implementation
 *	can be provided--on some targets we can combine the shifting and testing of the
 *	low bits if we code it in assembly-language.
 *
 */

extern char *__DecodeSignedNumber(char *p, long *pnum);


/*
 *	__DecodeUnsignedNumber	-	decode the unsigned integer number stored at location 'p'
 *
 *	Decode an unsigned number stored in compressed format at location 'p' and return
 *	the decoded value in '*pnum'. We return the pointer to just past the end of the
 *	decoded number.
 *
 *	We declare this function 'extern' so that a target-specific implementation
 *	can be provided--on some targets we can combine the shifting and testing of the
 *	low bits if we code it in assembly-language.
 *
 */

extern char *__DecodeUnsignedNumber(char *p, unsigned long *pnum);


/*
 *	__DecodeAddress			-	read a 32-bit address stored (unaligned) at location 'p'
 *
 *	We return the address in '*paddr'.
 *	
 *	Note that an address is always stored in target-endian format, so we need to take
 *	that into account here.
 *
 */

inline char *__DecodeAddress(char *p, void **paddr)
{
	unsigned long addr;
	
#if __option(little_endian)

	/*	decode 32-bit address stored unaligned in little-endian format	*/
	addr =	((unsigned char *) p)[0]			|
			(((unsigned char *) p)[1] << 8)		|
			(((unsigned char *) p)[2] << 16)	|
			(((unsigned char *) p)[3] << 24);

#else

	/*	decode 32-bit address stored unaligned in big-endian format		*/
	addr =	((unsigned char *) p)[3]			|
			(((unsigned char *) p)[2] << 8)		|
			(((unsigned char *) p)[1] << 16)	|
			(((unsigned char *) p)[0] << 24);

#endif

	*paddr = (void *) addr;
	return(p + 4);
}


#endif
