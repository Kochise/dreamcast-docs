/***
*shosintr.h - definitions and declarations for SH intrinisc library
*
*Purpose:
*       This file contains constant definitions and external subroutine
*       declarations for the SH intrinisc subroutine library.
*
****/

#ifndef _INC_SHOSINTR
#define _INC_SHOSINTR

#if defined(SH4)

#ifdef __cplusplus
extern "C" {
#endif

void __prefetch(unsigned long *addr);
void __movca(unsigned long value, unsigned long *addr);

void __ocbi(unsigned long *addr);
void __ocbp(unsigned long *addr);
void __ocbwb(unsigned long *addr);

void _Enable_BL();
void _Disable_BL();


#ifdef __cplusplus
}
#endif

#endif //defined(SH4)

#endif //_INC_SHOSINTR


