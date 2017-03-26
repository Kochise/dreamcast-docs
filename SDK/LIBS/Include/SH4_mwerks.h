/****************************************************************************
 *
 *	SH4 specific support - equivalent to _builtin_ Hitachi support routines
 *	(see machine.h in sh/include)
 *
 *****************************************************************************/

#ifndef _SH4_H
#define _SH4_H

/*****************************************************************************
 *
 *	Get status register
 *
 *****************************************************************************/

static inline unsigned int get_sr(void)
{
	register unsigned int sr = 0;

	asm
	{
		STC	SR,	sr
	};

	return sr;
}


/*****************************************************************************
 *
 *	Set status register
 *
 *****************************************************************************/
static inline void set_sr(unsigned int sr)
{
	register unsigned int value = sr;

	asm
	{
		LDC	value,	SR
	};
}



/*****************************************************************************
 *
 *	Get interrupt mask
 *
 *****************************************************************************/
static inline unsigned int get_imask(void)
{

	register unsigned int imask = 0;

	asm
	{
		STC	SR,	imask
	};


	imask = (imask >> 4) & 0x0f;

	return imask;
}



/*****************************************************************************
 *
 * Set interrupt mask
 *
 *****************************************************************************/
static inline void set_imask(int level)
{
	register unsigned int sr = 0;

	asm
	{
		STC	SR, sr
	};

	sr = (sr & 0xffffff0f) | ((level & 0x0f) << 4);

	asm
	{
		LDC	sr, SR
	};
}


/*****************************************************************************
 *
 * Set status register BL bit (interrupt block)
 *
/*****************************************************************************/
static inline void set_sr_bl(void)
{
	register unsigned int sr = 0;

	asm
	{
		STC	SR, sr
	};

	sr |= 0x10000000;

	asm
	{
		LDC	sr, SR
	};
}



/*****************************************************************************
 *
 * Clear status register BL bit (interrupt block)
 *
/*****************************************************************************/
static inline void clear_sr_bl(void)
{
	register unsigned int sr = 0;

	asm
	{
		STC	SR, sr
	};

	sr &= ~0x10000000;

	asm
	{
		LDC	sr, SR
	};
}



/*****************************************************************************
 *
 * Set r0-r7 register bank to 1
 *
 *****************************************************************************/
static inline void set_sr_rb(void)
{
	register unsigned int sr = 0;

	asm
	{
		STC	SR, sr
	};

	sr |= 0x20000000;

	asm
	{
		LDC	sr, SR
	};
}



/*****************************************************************************
 *
 * Set r0-r7 register bank to 0
 *
 *****************************************************************************/
static inline void clear_sr_rb(void)
{
	register unsigned int sr = 0;

	asm
	{
		STC	SR,	sr
	};

	sr &= ~0x20000000;

	asm
	{
		LDC	sr,	SR
	};
}


/*****************************************************************************
 *
 * Set gbr register
 *
 *****************************************************************************/

 static inline void set_gbr(register void* base)
 {
 	asm
 	{
 		MOV.L @base, R0
 		LDC   R0, GBR
 	};

 }

/*****************************************************************************
 *
 * Set vbr register
 *
 *****************************************************************************/
static inline void set_vbr(register void* base)
{
	asm
	{
		MOV.L	@base, R0
		LDC 	R0,	VBR
	};
}

/*****************************************************************************
 *
 *	fake strcmp intrinsic
 *
 *****************************************************************************/


static inline int _builtin_strcmp(const char * str1, const char * str2)
{
	const	unsigned char * p1 = (unsigned char *) str1;
	const	unsigned char * p2 = (unsigned char *) str2;
			unsigned char	c1, c2;

	while ((c1 = *p1++) == (c2 = *p2++))
		if (!c1)
			return(0);

	return(c1 - c2);
}

/*****************************************************************************
 *
 *	sleep
 *
 *****************************************************************************/
static inline void sleep(void)
{
	asm
	{
		SLEEP
	}
}

/*****************************************************************************
 *
 *	tas
 *
 *****************************************************************************/
static inline int tas(register char* addr)
{
	register unsigned int value = 0;

	asm
	{
		TAS.B	@addr
		MOVT	R4
		MOV		R4, value
	}

	return value;
}

/*****************************************************************************
 *
 * prefetch
 *
 *****************************************************************************/
static inline void prefetch(register void* p)
{
	asm
	{
		PREF @p;
	};

}

/*****************************************************************************
 *
 * macw
 *
 *****************************************************************************/
static inline int macw(register short *ptr1, register short *ptr2, register unsigned int count)
{
	register unsigned int value = 0;

	asm
	{
		STS.L	MACH,@-R15
        STS.L   MACL,@-R15

		MOV		count,R14
		MOV 	0,R0
		BRA		label
		CLRMAC
loop:
		MAC.W	@ptr1+, @ptr2+
		ADD		1,R0
label:
		CMP_GT	R0,R14
		BT		loop

		STS 	MACL, value
		LDS.L 	@R15+, MACL
		LDS.L 	@R15+, MACH
	}

	return value;
}
/*****************************************************************************
 *
 * macwl
 *
 *****************************************************************************/
static inline int macwl(register short *ptr1, register short *ptr2, register unsigned int count, register unsigned int mask)
{
	register unsigned int value = 0;

	asm
	{
		STS.L	MACH,@-R15
        STS.L   MACL,@-R15

		MOV		count,R14
		MOV 	0,R0
		BRA		label
		CLRMAC
loop:
		MAC.W	@ptr1+,@ptr2+
		ADD		mask,ptr2
		ADD		1,R0
label:
		CMP_GT	R0,R14
		BT		loop

		STS 	MACL, R0
		LDS.L 	@R15+, MACL
		LDS.L 	@R15+, MACH
	}

	return value;
}

/*	Intrinsic functions	*/

#define set_cr(cr)					   set_sr(cr)
#define get_cr()					   get_sr()
#define fabs(x)			   			   __fabs(x)
#define sqrt(x)						   __sqrt(x)
#define fabsf(x)					   __fabsf(x)
#define sqrtf(x)					   __sqrtf(x)
#define get_gbr()					   __get_gbr()
#define get_vbr()					   __get_vbr()
#define set_fpscr(cr)                  __set_fpscr(cr)
#define get_fpscr()                    __get_fpscr()
#define fipr(vec1, vec2)               __fipr(vec1, vec2)
#define ftrv(vec1, vec2)               __ftrv(vec1, vec2)
#define ftrvadd(vec1, vec2, vec3)      __ftrvadd(vec1, vec2, vec3)
#define ftrvsub(vec1, vec2, vec3)      __ftrvsub(vec1, vec2, vec3)
#define add4(vec1, vec2, vec3)         __add4(vec1, vec2, vec3)
#define sub4(vec1, vec2, vec3)         __sub4(vec1, vec2, vec3)
#define mtrx4mul(mx1, mx2)             __mtrx4mul(mx1, mx2)
#define mtrx4muladd(mx1, mx2, mx3)     __mtrx4muladd(mx1, mx2, mx3)
#define mtrx4mulsub(mx1, mx2, mx3)     __mtrx4mulsub(mx1, mx2, mx3)
#define ld_ext(mx)                     __ld_ext(mx)
#define st_ext(mx)                     __st_ext(mx)
#define gbr_read_byte(x)			   __gbr_read_byte(x)
#define gbr_read_word(x)			   __gbr_read_word(x)
#define gbr_read_long(x)			   __gbr_read_long(x)
#define gbr_write_byte(offset,data)	   __gbr_write_byte(offset,data)
#define gbr_write_word(offset,data)	   __gbr_write_word(offset,data)
#define gbr_write_long(offset,data)    __gbr_write_long(offset,data)
#define gbr_and_byte(offset,mask)	   __gbr_and_byte(offset,mask)
#define gbr_or_byte(offset,mask)	   __gbr_or_byte(offset,mask)
#define gbr_xor_byte(offset,mask)	   __gbr_xor_byte(offset,mask)
#define gbr_tst_byte(offset,mask)	   __gbr_tst_byte(offset,mask)
#define trapa(trap_no)				   __trapa(trap_no)
#define trapa_svc(n1,n2,n3,n4,n5,n6)   __trapa_svc(n1,n2,n3,n4,n5,n6)

/*  Private intrisics   */
#define fsca(rad,sinv,cosv)   __fsca(rad,sinv,cosv)
#define fsrra(v)              __fsrra(v)

/*  maps hitachi's strcpy intrinsic to ours */
#define _builtin_strcpy(s1,s2)	       __strcpy(s1,s2)

#endif	// _SH4_H