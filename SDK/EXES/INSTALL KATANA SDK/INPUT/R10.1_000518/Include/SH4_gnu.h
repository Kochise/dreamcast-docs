/*
** UMACHINE.H
**
** Hitachi SHC compatibility macros for GNU C
**
** by Toshiyasu Morita
**
** Started: 5/28/99
*/

/*
** Note:
**
** There are some extra "add" instructions in a few places
** to avoid destroying the input registers. This was done to minimize
** the number of registers required by the inline assembly fragments
** (eliminates copying of source operands to preserve values).
**
** Also, some of these macros use too many registers (fipr, etc)
** and ideally would be functions instead of inlines.
**
** These macros must be careful because the user may pass the same pointer
** twice, (e.g. fipr(ptr, ptr)) and the macros must handle them correctly.
**
** We must be careful to use "+r" with any registers which are modified
** in anyway (including pre-decrement and post-increment) because otherwise
** the compiler may use r15 for the register.
**
** We avoid the use of the "memory" clobber to avoid forcing surrounding
** code to write values to memory unnecessarily.
**
** Also, we must be careful not to evaluate the arguments twice in case
** the user has used an expression with side effects (e.g. ++foo).
**
** We avoid using fr0 in inline assembly fragments because it can cause
** problems with GCC's reload pass.
*/

#ifndef _SH4_H_
#define _SH4_H_

/********************** Patch to call IP code **********************/
typedef void (*__fptr)(void);
extern long _bss_start;
extern long _START_BSG;
static volatile long __i = 0;

static inline shinobi_workaround(void)
{
    /* First stage: After Shinobi IP code finishes, perform GCC start(). */
    if(__i == 0)
    {
        long *fill_ptr;

        /* Replace functionality of GCC start() routine.. clear BSS. */
        /* __fptr ap = (__fptr) &start; */
        /* ap(); */

        for (fill_ptr = (long *) &_bss_start; fill_ptr < (long *) &_START_BSG; fill_ptr++)
        {
            *fill_ptr = 0x0;
        }
    }
    *((long *) ((((long) &__i) & 0x0FFFFFFF) | 0xA0000000)) = __i++;
}

#define _builtin_strcpy(s1,s2)          strcpy(s1,s2)
#define _builtin_strcmp(s1,s2)          strcmp(s1,s2)

#ifndef true
#define true    (1)
#endif
#ifndef false
#define false   (0)
#endif


/********************** smachine.h **********************/
#define set_imask(value)    \
({  int imask;                                          \
    __asm__ volatile ("stc\tsr,%0" : "=r" (imask) : );  \
    imask = (imask & ~0xf0) | (value << 4);             \
    __asm__ volatile ("ldc\t%0,sr" : : "r" (imask));    \
})

#define get_imask()     \
({  int retval;                                         \
    __asm__ volatile ("stc\tsr,%0" : "=r" (retval) : ); \
    (retval >> 4) & 0xf;                                \
})

#define set_cr(value)   \
    __asm__ volatile ("ldc\t%0,sr" : : "r" (value));

#define get_cr()    \
({  int retval;                                         \
    __asm__ volatile ("stc\tsr,%0" : "=r" (retval) : ); \
    retval;                                             \
})

#define sleep() \
	__asm__ volatile ("sleep" : : : "memory");
/********************** smachine.h **********************/


/********************** umachine.h **********************/
#define set_gbr(base)   \
	__asm__ volatile ("ldc\t%0,gbr" : : "r" (base));

#define get_gbr()       \
({  int retval;                                 \
	__asm__ ("stc\tgbr,%0" : "=r" (retval) : ); \
    retval;                                     \
})

/*
** For gbr_read_byte, gbr_read_word, gbr_read_long, gbr_write_byte,
** gbr_write_word, and gbr_write_long:
**
** "offset" must be a constant integer between 0 and 255, inclusive.
*/

#define gbr_read_byte(offset)   \
({      int retval;                                                         \
	__asm__ ("mov.b\t@(%O1,gbr),%0" : "=z" (retval) : "L" (offset));        \
    retval;                                                                 \
})

#define gbr_read_word(offset)   \
({      int retval;                                                         \
	__asm__ ("mov.w\t@(%O1,gbr),%0" : "=z" (retval) : "L" (offset));        \
    retval;                                                                 \
})

#define gbr_read_long(offset)   \
({      int retval;                                                         \
	__asm__ ("mov.l\t@(%O1,gbr),%0" : "=z" (retval) : "L" (offset));        \
    retval;                                                                 \
})

#define gbr_write_byte(offset, value)   \
({      int value;                                                              \
    __asm__ volatile ("mov.b\t%0,@(%O1,gbr)" : : "z" (value), "L" (offset));    \
    value;                                                                      \
})

#define gbr_write_word(offset, value)   \
({      int value;                                                              \
    __asm__ volatile ("mov.w\t%0,@(%O1,gbr)" : : "z" (value), "L" (offset));    \
    value;                                                                      \
})

#define gbr_write_long(offset, value)   \
({      int value;                                                              \
    __asm__ volatile ("mov.l\t%0,@(%O1,gbr)" : : "z" (value), "L" (offset));    \
    value;                                                                      \
})

/*
** For gbr_and_byte, gbr_or_byte, gbr_xor_byte, and gbr_tst_byte:
**
** "value" must be a constant integer.
*/

#define gbr_and_byte(offset, value)     \
	__asm__ volatile ("and.b\t#%O1,@(%0,gbr)" : : "z" (offset), "L" (value));

#define gbr_or_byte(offset, value)      \
	__asm__ volatile ("or.b\t#%O1,@(%0,gbr)" : : "z" (offset), "L" (value));

#define gbr_xor_byte(offset, value)     \
	__asm__ volatile ("xor.b\t#%O1,@(%0,gbr)" : : "z" (offset), "L" (value));

#define gbr_tst_byte(offset, value)     \
	__asm__ volatile ("tst.b\t#%O1,@(%0,gbr)" : : "z" (offset), "L" (value));

#define tas(addr)   \
({  int retval;                                                                 \
    __asm__ volatile ("tas.b\t@%1\n\tmovt\t%0" : "=r" (retval) : "r" (addr));   \
    retval;                                                                     \
})

/*
** For trapa:
**
** "trap_no" must be a constant integer.
*/

/* The trapa service routine could modify memory, so
   "memory" must be specified for clobbers */

#define trapa(trap_no)  \
	__asm__ volatile ("trapa\t#" #trap_no : : : "memory");

extern __inline__ int macw(short *ptr1, short *ptr2, int count)

{
	int result;

	if (count) {
		__asm__ (
			"clrmac\n\t"
			".align 2\n"
			"LA%=:\n\t"
			"mac.w\t@%1+,@%2+\n\t"
			"cmp/hi\t%1,%3\n\t"
			"bt\tLA%=\n\t"
			"sts\tmacl,%0"
			: "=r" (result), "+r" (ptr1), "+r" (ptr2)
			: "r" ((short *)ptr1 + count)
			: "memory", "macl", "mach");
		return result;
	}

	return 0;
}

extern __inline__ int macwl(short *ptr1, short *ptr2, int count, int mask)

{
	int result;

	if (count) {
		__asm__ (
			"clrmac\n\t"
			".align 2\n"
			"LA%=:\n\t"
			"mac.w\t@%1+,@%2+\n\t"
			"cmp/hi\t%1,%3\n\t"
			"bt/s\tLA%=\n\t"
			"and\t%4,%2\n\t"
			"sts\tmacl,%0"
			: "=r" (result), "+r" (ptr1), "+r" (ptr2)
			: "r" ((short *)ptr1 + count), "r" (mask)
			: "memory", "macl", "mach");
		return result;
	}

	return 0;
}

extern __inline__ int macl(int *ptr1, int *ptr2, int count)

{
	int result;

	if (count) {
		__asm__ (
			"clrmac\n\t"
			".align 2\n"
			"LA%=:\n\t"
			"mac.l\t@%1+,@%2+\n\t"
			"cmp/hi\t%1,%3\n\t"
			"bt\tLA%=\n\t"
			"sts\tmacl,%0"
			: "=r" (result), "+r" (ptr1), "+r" (ptr2)
			: "r" ((int *)ptr1 + count)
			: "memory", "macl", "mach");
		return result;
	}

	return 0;
}

extern __inline__ int macll(int *ptr1, int *ptr2, int count, int mask)

{
	int result;

	if (count) {
		__asm__ (
			"clrmac\n\t"
			".align 2\n"
			"LA%=:\n\t"
			"mac.l\t@%1+,@%2+\n\t"
			"cmp/hi\t%1,%3\n\t"
			"bt/s\tLA%=\n\t"
			"and\t%4,%2\n\t"
			"sts\tmacl,%0"
			: "=r" (result), "+r" (ptr1), "+r" (ptr2)
			: "r" ((int *)ptr1 + count), "r" (mask)
			: "memory", "macl", "mach");
		return result;
	}

	return 0;
}

#define trapa_svc      error cannot make this generate code on SHC?

#define prefetch(ptr)   \
	__asm__ volatile ("pref\t@%0" : : "r" (ptr));

#define set_fpscr(cr)   \
	__asm__ volatile ("lds\t%0,fpscr" : : "r" (cr));

#define get_fpscr()     \
({  int retval;                                     \
	__asm__ ("sts\tfpscr,%0" : "=r" (retval) : );   \
    retval;                                         \
})

extern __inline__ float fipr(volatile float *vec1, float *vec2)

{
	register float fr4 asm("fr4"), fr5 asm("fr5"), fr6 asm("fr6");
	register float fr7 asm("fr7"), fr8 asm("fr8"), fr9 asm("fr9");
	register float fr10 asm("fr10"), fr11 asm("fr11");

	/* We need to expose the loads to the compiler for better optimization */

	fr4  = *vec1++;
	fr5  = *vec1++;
	fr6  = *vec1++;
	fr7  = *vec1++;
	fr8  = *vec2++;
	fr9  = *vec2++;
	fr10 = *vec2++;
	fr11 = *vec2++;

#if 1
	__asm__ volatile (
		"fipr\tfv8,fv4"
		: "+f" (fr7)
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr8), "f" (fr9),
		  "f" (fr10), "f" (fr11));
#else
	__asm__ volatile (
		"fipr\tfv8,fv4"
		: "+f" (fr7), "+f" (fr4), "+f" (fr5), "+f" (fr6)
		: "f" (fr8), "f" (fr9), "f" (fr10), "f" (fr11));
#endif

	return fr7;
}

extern __inline__ void ftrv(float *vec1, float *vec2)

{
	register float fr4 asm("fr4"), fr5 asm("fr5"), fr6 asm("fr6");
	register float fr7 asm("fr7");

	fr4 = *vec1++;
	fr5 = *vec1++;
	fr6 = *vec1++;
	fr7 = *vec1++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	vec2 += 4;

	*--vec2 = fr7;
	*--vec2 = fr6;
	*--vec2 = fr5;
	*--vec2 = fr4;
}

extern __inline__ void ftrvadd(float *vec1, float *vec2, float *vec3)

{
	register float fr4 asm("fr4"), fr5 asm("fr5"), fr6 asm("fr6");
	register float fr7 asm("fr7");
	register float temp0, temp1, temp2, temp3;

	fr4 = *vec1++;
	fr5 = *vec1++;
	fr6 = *vec1++;
	fr7 = *vec1++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	temp0 = *vec2++;
	temp1 = *vec2++;
	temp2 = *vec2++;
	temp3 = *vec2++;

	fr4 += temp0;
	fr5 += temp1;
	fr6 += temp2;
	fr7 += temp3;

	vec3 += 4;

	*--vec3 = fr7;
	*--vec3 = fr6;
	*--vec3 = fr5;
	*--vec3 = fr4;
}

extern __inline__ void ftrvsub(float *ptr1, float *ptr2, float *ptr3)

{
	register float fr4 asm("fr4"), fr5 asm("fr5"), fr6 asm("fr6");
	register float fr7 asm("fr7");
	register float temp0, temp1, temp2, temp3;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

	fr4 -= temp0;
	fr5 -= temp1;
	fr6 -= temp2;
	fr7 -= temp3;

	ptr3 += 4;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;
}

extern __inline__ void mtrx4mul(float *ptr1, float *ptr2)

{
	register float fr4 asm("fr4"), fr5 asm("fr5"), fr6 asm("fr6");
	register float fr7 asm("fr7");

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	ptr2 += 4;

	*--ptr2 = fr7;
	*--ptr2 = fr6;
	*--ptr2 = fr5;
	*--ptr2 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	ptr2 += 8;

	*--ptr2 = fr7;
	*--ptr2 = fr6;
	*--ptr2 = fr5;
	*--ptr2 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	ptr2 += 8;

	*--ptr2 = fr7;
	*--ptr2 = fr6;
	*--ptr2 = fr5;
	*--ptr2 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	ptr2 += 8;

	*--ptr2 = fr7;
	*--ptr2 = fr6;
	*--ptr2 = fr5;
	*--ptr2 = fr4;
}

extern __inline__ void mtrx4muladd(float *ptr1, float *ptr2, float *ptr3)

{
	register float fr4 asm("fr4"), fr5 asm("fr5"), fr6 asm("fr6");
	register float fr7 asm("fr7");
	register float temp0, temp1, temp2, temp3;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	fr4 += temp0;
	fr5 += temp1;
	fr6 += temp2;
	fr7 += temp3;

	ptr3 += 4;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	fr4 += temp0;
	fr5 += temp1;
	fr6 += temp2;
	fr7 += temp3;

	ptr3 += 8;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	fr4 += temp0;
	fr5 += temp1;
	fr6 += temp2;
	fr7 += temp3;

	ptr3 += 8;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	fr4 += temp0;
	fr5 += temp1;
	fr6 += temp2;
	fr7 += temp3;

	ptr3 += 8;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;
}

extern __inline__ void mtrx4mulsub(float *ptr1, float *ptr2, float *ptr3)

{
	register float fr4 asm("fr4"), fr5 asm("fr5"), fr6 asm("fr6");
	register float fr7 asm("fr7");
	register float temp0, temp1, temp2, temp3;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	fr4 -= temp0;
	fr5 -= temp1;
	fr6 -= temp2;
	fr7 -= temp3;

	ptr3 += 4;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	fr4 -= temp0;
	fr5 -= temp1;
	fr6 -= temp2;
	fr7 -= temp3;

	ptr3 += 8;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	fr4 -= temp0;
	fr5 -= temp1;
	fr6 -= temp2;
	fr7 -= temp3;

	ptr3 += 8;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;

	fr4 = *ptr1++;
	fr5 = *ptr1++;
	fr6 = *ptr1++;
	fr7 = *ptr1++;

	temp0 = *ptr2++;
	temp1 = *ptr2++;
	temp2 = *ptr2++;
	temp3 = *ptr2++;

#if 1
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		:
		: "f" (fr4), "f" (fr5), "f" (fr6), "f" (fr7));
#else
	__asm__ volatile (
		"ftrv\txmtrx,fv4"
		: "+r" (fr4), "+r" (fr5), "+r" (fr6), "+r" (fr7)
		);
#endif

	fr4 -= temp0;
	fr5 -= temp1;
	fr6 -= temp2;
	fr7 -= temp3;

	ptr3 += 8;

	*--ptr3 = fr7;
	*--ptr3 = fr6;
	*--ptr3 = fr5;
	*--ptr3 = fr4;
}

extern __inline__ void ld_ext(float *mx)

{
	__asm__ volatile (
		"frchg\n\t"
		"fmov.s\t@%0+,fr0\n\t"
		"fmov.s\t@%0+,fr1\n\t"
		"fmov.s\t@%0+,fr2\n\t"
		"fmov.s\t@%0+,fr3\n\t"
		"fmov.s\t@%0+,fr4\n\t"
		"fmov.s\t@%0+,fr5\n\t"
		"fmov.s\t@%0+,fr6\n\t"
		"fmov.s\t@%0+,fr7\n\t"
		"fmov.s\t@%0+,fr8\n\t"
		"fmov.s\t@%0+,fr9\n\t"
		"fmov.s\t@%0+,fr10\n\t"
		"fmov.s\t@%0+,fr11\n\t"
		"fmov.s\t@%0+,fr12\n\t"
		"fmov.s\t@%0+,fr13\n\t"
		"fmov.s\t@%0+,fr14\n\t"
		"fmov.s\t@%0,fr15\n\t"
		"frchg"
		: "+r" (mx)
		:
		: "memory");
}

extern __inline__ void st_ext(float *mx)

{
	__asm__ volatile (
		"frchg\n\t"
		"fmov.s\tfr15,@-%0\n\t"
		"fmov.s\tfr14,@-%0\n\t"
		"fmov.s\tfr13,@-%0\n\t"
		"fmov.s\tfr12,@-%0\n\t"
		"fmov.s\tfr11,@-%0\n\t"
		"fmov.s\tfr10,@-%0\n\t"
		"fmov.s\tfr9,@-%0\n\t"
		"fmov.s\tfr8,@-%0\n\t"
		"fmov.s\tfr7,@-%0\n\t"
		"fmov.s\tfr6,@-%0\n\t"
		"fmov.s\tfr5,@-%0\n\t"
		"fmov.s\tfr4,@-%0\n\t"
		"fmov.s\tfr3,@-%0\n\t"
		"fmov.s\tfr2,@-%0\n\t"
		"fmov.s\tfr1,@-%0\n\t"
		"fmov.s\tfr0,@-%0\n\t"
		"frchg"
		: "+r" ((char *)mx + 64)
		:
		: "memory");
}

extern __inline__ void add4(float *vec1, float *vec2, float *vec3)

{
	register float temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;

	temp0 = *vec1++;
	temp1 = *vec1++;
	temp2 = *vec1++;
	temp3 = *vec1++;

	temp4 = *vec2++;
	temp5 = *vec2++;
	temp6 = *vec2++;
	temp7 = *vec2++;

	temp0 += temp4;
	temp1 += temp5;
	temp2 += temp6;
	temp3 += temp7;

	vec3 += 4;

	*--vec3 = temp3;
	*--vec3 = temp2;
	*--vec3 = temp1;
	*--vec3 = temp0;
}

extern __inline__ void sub4(float *vec1, float *vec2, float *vec3)

{
	register float temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;

	temp0 = *vec1++;
	temp1 = *vec1++;
	temp2 = *vec1++;
	temp3 = *vec1++;

	temp4 = *vec2++;
	temp5 = *vec2++;
	temp6 = *vec2++;
	temp7 = *vec2++;

	temp0 -= temp4;
	temp1 -= temp5;
	temp2 -= temp6;
	temp3 -= temp7;

	vec3 += 4;

	*--vec3 = temp3;
	*--vec3 = temp2;
	*--vec3 = temp1;
	*--vec3 = temp0;
}
/********************** umachine.h **********************/


/********************** private.h **********************/
extern __inline__ void _builtin_fsca(int rad, float *sinv, float *cosv)
{
	register float sin asm("fr2");
	register float cos asm("fr3");
    __asm__ ("fsca\t%2,dr2"             \
            : "=f" (sin), "=f" (cos)    \
			: "y" (rad));
	*sinv = sin;
	*cosv = cos;
}

#define _builtin_fsrra(v)    \
({ float retval=(v);                                    \
    __asm__ volatile ("fsrra\t%0" : "+f" (retval) : );  \
    retval;                                             \
})

/********************** private.h **********************/

#endif  // _SH4_H