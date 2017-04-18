/************************************************************************/
/*	Project...:	SH Runtime Library										*/
/*	Name......:	LongLongSH.c											*/
/*	Purpose...:	SH 64-bit integer arithmetic functions					*/
/*  Copyright.: Copyright © 1999 Metrowerks, Inc.						*/
/************************************************************************/

/* 
 * Emulate long long.
 *
 */

#if __SH2__ || __SH3__
#include "Mwsfpe.h"	// software fp lib
#endif

#if ( __littleendian__ )
 
typedef struct CInt64 {
	unsigned long			lo;
	long	hi;
}	CInt64;

#else

typedef struct CInt64 {
	long	hi;
	unsigned long			lo;
}	CInt64;

#endif

#if __cplusplus
extern "C" {
#endif

/* comparison operators */
#define ll_ltz(ll)		((ll).hi<0)
#define ll_gez(ll)		((ll).hi>=0)
#define ll_eqz(a)		(((a.hi) | (a.lo)) == 0)
#define ll_eq(a,b)		((a.hi == b.hi) && (a.lo == b.lo))
#define ll_ne(a,b)		!ll_eq(a,b)

#define NULL	0L

#pragma parameter gcc __rt_neg64
extern CInt64	__rt_neg64(CInt64 op);
#pragma parameter gcc __rt_inv64
extern CInt64	__rt_inv64(CInt64 op);

#pragma parameter gcc __rt_add64
extern CInt64	__rt_add64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_sub64
extern CInt64	__rt_sub64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_mul64
extern CInt64	__rt_mul64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_divu64
extern CInt64	__rt_divu64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_divs64
extern CInt64	__rt_divs64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_modu64
extern CInt64	__rt_modu64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_mods64
extern CInt64	__rt_mods64(CInt64 left,CInt64 right);

#pragma parameter gcc __rt_shl64
extern CInt64	__rt_shl64(CInt64 left,short count);
#pragma parameter gcc __rt_shru64
extern CInt64	__rt_shru64(CInt64 left,short count);
#pragma parameter gcc __rt_shrs64
extern CInt64	__rt_shrs64(CInt64 left,short count);
#pragma parameter gcc __rt_and64
extern CInt64	__rt_and64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_or64
extern CInt64	__rt_or64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_eor64
extern CInt64	__rt_eor64(CInt64 left,CInt64 right);

#pragma parameter gcc __rt_cmpu64
extern short	__rt_cmpu64(CInt64 left,CInt64 right);
#pragma parameter gcc __rt_cmps64
extern short	__rt_cmps64(CInt64 left,CInt64 right);

#pragma parameter gcc __rt_ultoi64
extern CInt64	__rt_ultoi64(unsigned long op);
#pragma parameter gcc __rt_sltoi64
extern CInt64	__rt_sltoi64(signed long op);

#if __SH2E__ || __SH4__

#pragma parameter gcc __rt_u64tofd
extern long double __rt_u64tofd(CInt64 op);
#pragma parameter gcc __rt_s64tofd
extern long double __rt_s64tofd(CInt64 op);
#pragma parameter gcc __rt_fdtou64
extern CInt64 __rt_fdtou64(long double op);
#pragma parameter gcc __rt_fdtos64
extern CInt64 __rt_fdtos64(long double op);
#pragma parameter gcc __rt_s64tof64
short double __rt_s64tof64(CInt64 op);
#pragma parameter gcc __rt_u64tof64
short double __rt_u64tof64(CInt64 op);
#pragma parameter gcc __rt_s64tof32
float __rt_s64tof32(CInt64 op);
#pragma parameter gcc __rt_u64tof32
float __rt_u64tof32(CInt64 op);
#pragma parameter gcc __rt_f64tos64
extern CInt64 __rt_f64tos64(short double op);

#else

#pragma parameter gcc __rt_s64tof64
sfpe_double __rt_s64tof64(long long op);
#pragma parameter gcc __rt_u64tof64
sfpe_double __rt_u64tof64(unsigned long long op);
#pragma parameter gcc __rt_s64tof32
sfpe_float __rt_s64tof32(long long op);
#pragma parameter gcc __rt_u64tof32
sfpe_float __rt_u64tof32(unsigned long long op);
#pragma parameter gcc __rt_f64tos64
extern long long __rt_f64tos64(sfpe_double op);
#pragma parameter gcc __rt_f64tou64
extern unsigned long long __rt_f64tou64(sfpe_double op);
#pragma parameter gcc __rt_f32tos64
extern long long __rt_f32tos64(sfpe_float op);
#pragma parameter gcc __rt_f32tou64
extern unsigned long long __rt_f32tou64(sfpe_float op);

#endif

#if __cplusplus
}
#endif


/************************************************************************/
/* Purpose..: Compute result = - op										*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_neg64
extern asm CInt64 __rt_neg64(CInt64 register op)
{
	CLRT;
#if ( __littleendian__ )
	NEGC R4,R0;
	RTS;
	NEGC R5,R1;
#else
	NEGC R5,R1;
	RTS;
	NEGC R4,R0;
#endif
}

/************************************************************************/
/* Purpose..: Compute result = ~ op										*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_inv64
extern asm CInt64 __rt_inv64(CInt64 register op)
{
	NOT R4, R0;
	RTS;
	NOT R5, R1;
}

/************************************************************************/
/* Purpose..: Compute result = left + right								*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_add64
extern CInt64 __rt_add64(CInt64 left,CInt64 right)
{
 	CInt64 result;

    int al = left.lo, ah = left.hi, bl = right.lo, bh = right.hi;
    long h = ah + bh;
    long l = al + bl;
    
    if (al < 0) {
		if (bl < 0 || l >= 0)
	    	h++;
    } else if (bl < 0 && l >= 0)
		h++;
    
    result.lo = l;
    result.hi = h;
    
    return result;
}

/************************************************************************/
/* Purpose..: Compute result = left - right								*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_sub64
extern CInt64 __rt_sub64(CInt64 left,CInt64 right)
{
	CInt64 result;

	right = __rt_neg64(right);
	
	result = __rt_add64(left, right);
    
    return result;
}

/************************************************************************/
/* Purpose..: Compute result = left * right								*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_mul64
extern CInt64 __rt_mul64(CInt64 left,CInt64 right)
{
 	CInt64 result;

   	int i;
    int neg = 0;
    CInt64 sh;
    CInt64 s;
    unsigned long m;
      
    if (ll_ltz(left))
		sh = __rt_neg64(left), neg = 1;
    else
		sh = left;
    
    s = right;
    result.hi = 0;
    result.lo = 0;
    m = sh.lo;
    
    if (sh.hi != 0) {
		
		for (i = 32; --i >= 0;) {
	    	
	    	if (m & 1)
				result = __rt_add64(result, s);
				
	    	s = __rt_shl64(s, 1);
	    	m >>= 1;
		
		}
		
		m = sh.hi;
    }
    
    while (m > 0) {
		
		if (m & 1)
			result = __rt_add64(result, s);

	    s = __rt_shl64(s, 1);
		m >>= 1;

    }
    
    if (neg)
		result = __rt_neg64(result);
    
    return result;
}

/****************************************************************/
/* Purpose..: 64-bit unsigned divide/modulo						*/
/*			  (all pointers can be aliases)						*/
/* Input....: pointer to left operand							*/
/* Input....: pointer to right operand							*/
/* Input....: pointer to divide result (or NULL)				*/
/* Input....: pointer to modulo result (or NULL)				*/
/* Returns..: ---												*/
/****************************************************************/
#pragma parameter gcc __rt_divmod64
static void __rt_divmod64(const CInt64 *left,const CInt64 *right,CInt64 *divr,CInt64 *modr)
{
	unsigned long	hihi,hilo,lohi,lolo;
	unsigned long	divhi,divlo;
	unsigned long	resulthi,resultlo;
	int				i;

	//	check for divide by zero
	if(right->hi==0 && right->lo==0) return;

	//	setup 128-bit dividend (left in low 64-bits)
	hihi=0; hilo=0; lohi=left->hi; lolo=left->lo;

	//	setup 64-bit divisor
	divhi=right->hi; divlo=right->lo;

	//	setup 64-bit division result
	resulthi=0; resultlo=0;

	//	bitwise division / modulo
	for(i=0; i<64; i++)
	{
		//	shift 128-bit dividend one bit left
		hihi<<=1;
		if(hilo&0x80000000) hihi|=1;			//	carry
		hilo<<=1;
		if(lohi&0x80000000) hilo|=1;			//	carry
		lohi<<=1;
		if(lolo&0x80000000) lohi|=1;			//	carry
		lolo<<=1;

		//	shift division result one bit left
		resulthi<<=1;
		if(resultlo&0x80000000) resulthi|=1;	//	carry
		resultlo<<=1;

		if(hihi>divhi || (hihi==divhi && hilo>=divlo))
		{	//	high 64-bit of dividend >= divisor
			CInt64 	temp;

			//	shift one into division result
			resultlo|=1;

			//	subtract divisor from high 64-bit of dividend		
			temp.hi=hihi; temp.lo=hilo;			//	copy high 64-bit of dividend into temp
			temp = __rt_sub64(temp,*right);//	subtract
			hihi=temp.hi; hilo=temp.lo;			//	copy temp into high 64-bit of dividend
		}
	}

	//	setup results
	if(divr) { divr->hi=resulthi; divr->lo=resultlo; }
	if(modr) { modr->hi=hihi; modr->lo=hilo; }	//	remainder is in high 64-bits of dividend
}

/************************************************************************/
/* Purpose..: Compute result = left / right (unsigned)					*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_divu64
extern CInt64 __rt_divu64(CInt64 left,CInt64 right)
{
	CInt64 result;

	__rt_divmod64(&left,&right,&result,NULL);
	
	return result;
}

/************************************************************************/
/* Purpose..: Compute result = left / right (signed)					*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_divs64
extern CInt64 __rt_divs64(CInt64 left,CInt64 right)
{
	CInt64 result;

	if(left.hi<0)
	{
		left = __rt_neg64(left);
		if(right.hi<0)
		{	//	left<0 / right<0
			right = __rt_neg64(right);
			__rt_divmod64(&left,&right,&result,NULL);
		}
		else
		{	//	left>=0 / right<0
			__rt_divmod64(&left,&right,&result,NULL);
			result = __rt_neg64(result);
		}
	}
	else
	{
		if(right.hi<0)
		{	//	left<0 / right>=0
			right = __rt_neg64(right);
			__rt_divmod64(&left,&right,&result,NULL);
			result = __rt_neg64(result);
		}
		else
		{	//	left>=0 / right>=0
			__rt_divmod64(&left,&right,&result,NULL);
		}
	}
	return result;
}

/************************************************************************/
/* Purpose..: Compute result = left % right (unsigned)					*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_modu64
extern CInt64 __rt_modu64(CInt64 left,CInt64 right)
{
	CInt64 result;

	__rt_divmod64(&left,&right,NULL,&result);
	
	return result;
}

/************************************************************************/
/* Purpose..: Compute result = left % right (signed)					*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_mods64
extern CInt64 __rt_mods64(CInt64 left,CInt64 right)
{
	CInt64 result;

	if(left.hi<0)
	{
		left = __rt_neg64(left);
		if(right.hi<0)
		{	//	left<0 / right<0
			right = __rt_neg64(right);
			__rt_divmod64(&left,&right,NULL,&result);
		}
		__rt_divmod64(&left,&right,NULL,&result);
		result = __rt_neg64(result);
	}
	else
	{
		if(right.hi<0)
		{	//	left<0 / right>=0
			right = __rt_neg64(right);
		}
		__rt_divmod64(&left,&right,NULL,&result);
	}
	
	return result;
}

/************************************************************************/
/* Purpose..: Compute result = left << right							*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: shift count												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_shl64
extern CInt64 __rt_shl64(CInt64 left,short count)
{
	CInt64 result;

    if (count <= 0)
    
		result = left;
    
    else if (count < 32) {
		
		result.lo = left.lo << count;
		result.hi = (left.hi << count) | ((unsigned long) left.lo >> (32 - count));
    
    } else {
		
		result.lo = 0;
		result.hi = count < 64 ? left.lo << (count - 32) : 0;
    
    }
    
    return result;
}

/************************************************************************/
/* Purpose..: Compute result = left >> right (unsigned)					*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: shift count												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_shru64
extern CInt64 __rt_shru64(CInt64 left,short count)
{
	CInt64 result;

    if (count <= 0)
	
		result = left;
    
    else if (count < 32) {
		
		result.lo = ((unsigned long) left.lo >> count) | (left.hi << (32 - count));
		result.hi = (unsigned long) left.hi >> count;
    
    } else {
		
		result.hi = 0;
		result.lo = count < 64 ? (unsigned long) left.hi >> (count - 32) : 0;
    
    }
    
    return result;
}

/************************************************************************/
/* Purpose..: Compute result = left >> right (signed)					*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: shift count												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_shrs64
extern CInt64 __rt_shrs64(CInt64 left,short count)
{
 	CInt64 result;

   if (count <= 0)

		result = left;
    
    else if (count < 32) {
	
		result.lo = ((unsigned long) left.lo >> count) | (left.hi << (32 - count));
		result.hi = left.hi >> count;
    
    } else if (count < 64) {
	
		result.hi = left.hi >> 31;
		result.lo = left.hi >> (count - 32);
    
    } else
	
		result.lo = result.hi = left.hi >> 31;

    return result;
}

/************************************************************************/
/* Purpose..: Compute result = left & right								*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_and64
extern asm CInt64 __rt_and64(CInt64 register left,CInt64 register right)
{
#if ( __littleendian__ )
    // result.hi = left.hi & right.hi;
	AND	R5,R7;
	MOV	R7,R1;
	
    // result.lo = left.lo & right.lo;
 	AND	R4,R6;
	RTS;
	MOV	R6,R0;
#else
    // result.hi = left.hi & right.hi;
 	AND	R4,R6;
	MOV	R6,R0;
	
    // result.lo = left.lo & right.lo;
	AND	R5,R7;
	RTS;
	MOV	R7,R1;
#endif
}

/************************************************************************/
/* Purpose..: Compute result = left | right								*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_or64
extern asm CInt64 __rt_or64(CInt64 register left,CInt64 register right)
{
#if ( __littleendian__ )
    // result.hi = left.hi | right.hi;
	OR	R5,R7;
	MOV	R7,R1;
	
   // result.lo = left.lo | right.lo;
 	OR	R4,R6;
	RTS;
	MOV	R6,R0;
#else
    // result.hi = left.hi | right.hi;
 	OR	R4,R6;
	MOV	R6,R0;
   // result.lo = left.lo | right.lo;
	OR	R5,R7;
	RTS;
	MOV	R7,R1;
#endif
}

/************************************************************************/
/* Purpose..: Compute result = left ^ right								*/
/* Input....: pointer to result											*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: pointer to result											*/
/************************************************************************/
#pragma parameter gcc __rt_eor64
extern asm CInt64 __rt_eor64(CInt64 register left,CInt64 register right)
{
#if ( __littleendian__ )
    // result.hi = left.hi ^ right.hi;
	XOR	R5,R7;
	MOV	R7,R1;
	
    // result.lo = left.lo ^ right.lo;
 	XOR	R4,R6;
	RTS;
	MOV	R6,R0;
#else
    // result.hi = left.hi ^ right.hi;
 	XOR	R4,R6;
	MOV	R6,R0;
	
    // result.lo = left.lo ^ right.lo;
	XOR	R5,R7;
	RTS;
	MOV	R7,R1;
#endif
}

/************************************************************************/
/* Purpose..: Compare left and right (unsigned)							*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: -1 : left < right; 0: left == right; 1: left > right		*/
/************************************************************************/
#pragma parameter gcc __rt_cmpu64
extern short asm __rt_cmpu64(CInt64 register left,CInt64 register right)
{
#if ( __littleendian__ )

	// if ((unsigned)left.hi > (unsigned)right.hi)
	//	return 1;		// greater than
	
	CMP_HI	R7,R5;
	BF	NEXT1;
	MOV	1,R0;
	RTS;
	
	// else if (left.hi == right.hi) {
	
NEXT1:
	CMP_EQ	R7,R5
	BF	NEXT2;	
		
	//	if (left.lo == right.lo)
	//		return 0;	// equal
	
	CMP_EQ	R6,R4;
	BF	NEXT3;
	RTS;
	MOV	0,R0;
			
	//	else if (left.lo > right.lo)
	//		return 1;	// greater than

NEXT3:
	CMP_HI	R6,R4;
	BF	NEXT2;
	RTS;
	MOV	1,R0;

	// }
	
	// return -1;			// less than

NEXT2:
	RTS;
	MOV	-1,R0;

#else

	// if ((unsigned)left.hi > (unsigned)right.hi)
	//	return 1;		// greater than
	
	CMP_HI	R6,R4;
	BF	NEXT1;
	MOV	1,R0;
	RTS;
	
	// else if (left.hi == right.hi) {
	
NEXT1:
	CMP_EQ	R6,R4
	BF	NEXT2;	
		
	//	if (left.lo == right.lo)
	//		return 0;	// equal
	
	CMP_EQ	R7,R5;
	BF	NEXT3;
	RTS;
	MOV	0,R0;
			
	//	else if (left.lo > right.lo)
	//		return 1;	// greater than

NEXT3:
	CMP_HI	R7,R5;
	BF	NEXT2;
	RTS;
	MOV	1,R0;

	// }
	
	// return -1;			// less than

NEXT2:
	RTS;
	MOV	-1,R0;
#endif
}

/************************************************************************/
/* Purpose..: Compare left and right (signed)							*/
/* Input....: left operand												*/
/* Input....: right operand												*/
/* Return...: -1 : left < right; 0: left == right; 1: left > right		*/
/************************************************************************/
#pragma parameter gcc __rt_cmps64
extern short asm __rt_cmps64(CInt64 register left,CInt64 register right)
{
#if ( __littleendian__ )

	// if (left.hi > right.hi)
	//	return 1;		// greater than
	
	CMP_GT	R7,R5;
	BF	NEXT1;
	RTS;
	MOV	1,R0;
	
	// else if (left.hi == right.hi) {
	
NEXT1:
	CMP_EQ	R7,R5;
	BF	NEXT2;
		
	//	if (left.lo == right.lo)
	//		return 0;	// equal
	
	CMP_EQ	R6,R4;
	BF	NEXT3;
	RTS;
	MOV	0,R0;
			
	//	else if (left.lo > right.lo)
	//		return 1;	// greater than

NEXT3:
	CMP_HI	R6,R4;
	BF	NEXT2;
	RTS;
	MOV	1,R0;

	// }
	
	// return -1;			// less than

NEXT2:
	RTS;
	MOV	-1,R0;

#else
	// if (left.hi > right.hi)
	//	return 1;		// greater than
	
	CMP_GT	R6,R4;
	BF	NEXT1;
	RTS;
	MOV	1,R0;
	
	// else if (left.hi == right.hi) {
	
NEXT1:
	CMP_EQ	R6,R4;
	BF	NEXT2;
		
	//	if (left.lo == right.lo)
	//		return 0;	// equal
	
	CMP_EQ	R7,R5;
	BF	NEXT3;
	RTS;
	MOV	0,R0;
			
	//	else if (left.lo > right.lo)
	//		return 1;	// greater than

NEXT3:
	CMP_HI	R7,R5;
	BF	NEXT2;
	RTS;
	MOV	1,R0;

	// }
	
	// return -1;			// less than

NEXT2:
	RTS;
	MOV	-1,R0;
#endif
}


/************************************************************************/
/* Purpose..: Convert 'unsigned long' to 64-bit integral				*/
/* Input....: pointer to 64-bit integral result buffer					*/
/* Input....: unsigned long to convert									*/
/* Return...: pointer to 64-bit integral result buffer					*/
/************************************************************************/
#pragma parameter gcc __rt_ultoi64
extern CInt64 asm __rt_ultoi64(unsigned long register op)
{
#if ( __littleendian__ )
    // result.lo = op;
    MOV op,R0;
    
    // result.hi = 0;
    RTS;
    MOV 0,R1;
#else
    // result.lo = op;
    MOV op,R1;
    
    // result.hi = 0;
    RTS;
    MOV 0,R0;
#endif
}

/************************************************************************/
/* Purpose..: Convert 'signed long' to 64-bit integral					*/
/* Input....: signed long to convert									*/
/* Return...: pointer to 64-bit integral result buffer					*/
/************************************************************************/
#pragma parameter gcc __rt_sltoi64
extern CInt64 asm __rt_sltoi64(signed long register op)
{
#if ( __littleendian__ )
    // result.lo = op;
	MOV op,R0
	
 	// result.hi = op < 0 ? ~0 : 0;
    CMP_PZ R4
    BT	POS
	RTS;
    MOV	-1,R1;
POS:
	RTS;
	MOV	0,R1;
#else
    // result.lo = op;
	MOV op,R1
	
 	// result.hi = op < 0 ? ~0 : 0;
    CMP_PZ R4
    BT	POS
	RTS;
    MOV	-1,R0;
POS:
	RTS;
	MOV	0,R0;
#endif
}

#if __SH2E__ || __SH4__

/************************************************************************/
/* Purpose..: Convert 'unsigned long long' to 32-bit float 				*/
/* Input....: unsigned long long to convert								*/
/* Return...: float result												*/
/************************************************************************/
#pragma parameter gcc __rt_u64tof32
extern float __rt_u64tof32(CInt64 op)
{
	long double ld;

	ld = __rt_u64tofd(op);
	return ld;
}

/************************************************************************/
/* Purpose..: Convert 'unsigned long long' to 64-bit float 				*/
/* Input....: unsigned long long to convert								*/
/* Return...: float result												*/
/************************************************************************/
#pragma parameter gcc __rt_u64tof64
extern short double __rt_u64tof64(CInt64 op)
{
	long double ld;

	ld = __rt_u64tofd(op);
	return ld;
}

/************************************************************************/
/* Purpose..: Convert 'signed long long' to 32-bit float 				*/
/* Input....: signed long long to convert								*/
/* Return...: float result												*/
/************************************************************************/
#pragma parameter gcc __rt_s64tof32
extern float __rt_s64tof32(CInt64 op)
{
	long double ld;

	ld = __rt_s64tofd(op);
	return ld;
}

/************************************************************************/
/* Purpose..: Convert 'signed long long' to 64-bit float 				*/
/* Input....: signed long long to convert								*/
/* Return...: float result												*/
/************************************************************************/
#pragma parameter gcc __rt_s64tof64
extern short double __rt_s64tof64(CInt64 op)
{
	long double ld;

	ld = __rt_s64tofd(op);
	return ld;
}

/************************************************************************/
/* Purpose..: Convert 'unsigned long long' to 64-bit float 				*/
/* Input....: unsigned long long to convert								*/
/* Return...: float result												*/
/************************************************************************/
#pragma parameter gcc __rt_u64tofd
extern long double __rt_u64tofd(CInt64 op)
{
	long double		x;
	unsigned long	b;
	int				i;

	x=0.0;
	if((b=op.hi)!=0) for(i=0; i<32; i++)
	{
		x+=x;
		if(b&0x80000000) x+=1.0;
		b<<=1;
	}
	for(i=0,b=op.lo; i<32; i++)
	{
		x+=x;
		if(b&0x80000000) x++;
		b<<=1;
	}
	return x;
}

/************************************************************************/
/* Purpose..: Convert 'signed long long' to 64-bit float 				*/
/* Input....: signed long long to convert								*/
/* Return...: float result												*/
/************************************************************************/
#pragma parameter gcc __rt_s64tofd
extern long double __rt_s64tofd(CInt64 op)
{
	long double ld;

	if(op.hi<0)
	{
		op = __rt_neg64(op);
		ld = __rt_u64tofd(op);
		return (-ld);
	}
	else 
		return __rt_u64tofd(op);
}

/************************************************************************/
/* Purpose..: Convert to 32-bit float to 'unsigned long long'			*/
/* Input....: 32-bit float												*/
/* Return...: unsigned long long										*/
/************************************************************************/
#pragma parameter gcc __rt_f32tou64
extern CInt64	__rt_f32tou64(float op)
{
	return __rt_fdtou64(op);
}

/************************************************************************/
/* Purpose..: Convert to 64-bit float to 'unsigned long long'			*/
/* Input....: 32-bit float												*/
/* Return...: signed long long											*/
/************************************************************************/
#pragma parameter gcc __rt_f64tou64
extern CInt64	__rt_f64tou64(short double op)
{
	return __rt_fdtou64(op);
}

/************************************************************************/
/* Purpose..: Convert to 32-bit float to 'signed long long'				*/
/* Input....: 32-bit float												*/
/* Return...: unsigned long long										*/
/************************************************************************/
#pragma parameter gcc __rt_f32tos64
extern CInt64 __rt_f32tos64(float op)
{
	return __rt_fdtos64(op);
}

/************************************************************************/
/* Purpose..: Convert to 64-bit float to 'signed long long'				*/
/* Input....: 32-bit float												*/
/* Return...: signed long long											*/
/************************************************************************/
#pragma parameter gcc __rt_f64tos64
extern CInt64 __rt_f64tos64(short double op)
{
	return __rt_fdtos64(op);
}

/****************************************************************/
/* Purpose..: Compute 2^n										*/
/* Input....: n [0..65]											*/
/* Returns..: 2^n												*/
/****************************************************************/
static inline float __rt_pow2SANE(short n)
{
	unsigned long	ui;

	//
	//	float: {Ê1 bit sign , 8-bit exponent , 23-bit fraction }
	//	float val = (-1)^sign * 2^(exponent-127) * (1.fraction)
	//
	if(n==0) return 1.0;
	ui=((unsigned long)(unsigned char)(n+127)<<23);	//	sign=0 , exponent=n+127 , fraction = 1.0
	return *(float *)&ui;
}

/************************************************************************/
/* Purpose..: Convert to 64-bit float to 'unsigned long long'			*/
/* Input....: 64-bit float												*/
/* Return...: unsigned long long										*/
/************************************************************************/
#pragma parameter gcc __rt_fdtou64
extern CInt64 __rt_fdtou64(long double op)
{
	float			f;
	unsigned long	hi,lo;
	int				i;
	CInt64			result;

	if(op<=0)
	{
		result.hi=0; result.lo=0;
		return result;
	}

	if(op>=__rt_pow2SANE(64))
	{
		result.hi=0xFFFFFFFF; result.lo=0xFFFFFFFF;
		return result;
	}

	for(hi=lo=0,i=63; i>=0; --i)
	{
		hi<<=1;
		if(lo&0x80000000) hi|=1;	//	carry
		lo<<=1;
		if((f=__rt_pow2SANE(i))<=op)
		{
			lo|=1; op-=f;
		}
	}
	result.hi=hi; result.lo=lo;

	return result;
}

/************************************************************************/
/* Purpose..: Convert to 64-bit float to 'signed long long'				*/
/* Input....: 64-bit float												*/
/* Return...: unsigned long long										*/
/************************************************************************/
#pragma parameter gcc __rt_fdtos64
extern CInt64 __rt_fdtos64(long double op)
{
	CInt64 ul;
	
	if(op<0)
	{
		ul = __rt_fdtou64(-op);
		return __rt_neg64(ul);
	}
	else
		return __rt_fdtou64(op);
}

#else

/************************************************************************/
/* Purpose..: Convert 'signed long long' to 64-bit float				*/
/* Input....: signed 64-bit integral 									*/
/* Return...: pointer to 64-bit float result buffer						*/
/************************************************************************/
#pragma parameter gcc __rt_s64tof64
sfpe_double __rt_s64tof64(long long op)
{
	return GLOB_NAM(d_lltod)(op);
}

/************************************************************************/
/* Purpose..: Convert 'unsigned long long' to 64-bit float				*/
/* Input....: unsigned 64-bit integral 									*/
/* Return...: pointer to 64-bit float result buffer						*/
/************************************************************************/
#pragma parameter gcc __rt_u64tof64
sfpe_double __rt_u64tof64(unsigned long long op)
{
	return GLOB_NAM(d_ulltod)(op);
}

/************************************************************************/
/* Purpose..: Convert 'signed long long' to 32-bit float				*/
/* Input....: signed 64-bit integral 									*/
/* Return...: 32-bit float												*/
/************************************************************************/
#pragma parameter gcc __rt_s64tof32
sfpe_float __rt_s64tof32(long long op)
{
	return GLOB_NAM(f_lltof)(op);
}

/************************************************************************/
/* Purpose..: Convert 'unsigned long long' to 32-bit float				*/
/* Input....: unsigned 64-bit integral 									*/
/* Return...: 32-bit float												*/
/************************************************************************/
#pragma parameter gcc __rt_u64tof32
sfpe_float __rt_u64tof32(unsigned long long op)
{
	return GLOB_NAM(f_ulltof)(op);
}

/************************************************************************/
/* Purpose..: Convert '64-bit float' to signed long long				*/
/* Input....: 64-bit float			 									*/
/* Return...: pointer to 64-bit integral result buffer					*/
/************************************************************************/
#pragma parameter gcc __rt_f64tos64
extern long long __rt_f64tos64(sfpe_double op)
{
	return GLOB_NAM(d_dtoll)(op);
}

#pragma parameter gcc __rt_f64tou64
extern unsigned long long __rt_f64tou64(sfpe_double op)
{	
	return GLOB_NAM(d_dtoull)(op);
}

#pragma parameter gcc __rt_f32tos64
extern long long __rt_f32tos64(sfpe_float op)
{
	return GLOB_NAM(f_ftoll)(op);
}

#pragma parameter gcc __rt_f32tou64
extern unsigned long long __rt_f32tou64(sfpe_float op)
{
	return GLOB_NAM(f_ftoull)(op);
}

#endif