/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 3.0                        */
/* Copyright (c) 1992, 1995 Hitachi,Ltd.                */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = umachine.h :                                         */
/*   FUNC = ;                                                    */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/
#ifndef _UMACHINE_SHC
#define _UMACHINE_SHC

#define set_gbr(base)               _builtin_set_gbr(base)
#define get_gbr()                   _builtin_get_gbr()
#define gbr_read_byte(offset)       _builtin_gbr_read_byte(offset)
#define gbr_read_word(offset)       _builtin_gbr_read_word(offset)
#define gbr_read_long(offset)       _builtin_gbr_read_long(offset)
#define gbr_write_byte(offset,data) _builtin_gbr_write_byte(offset,data)
#define gbr_write_word(offset,data) _builtin_gbr_write_word(offset,data)
#define gbr_write_long(offset,data) _builtin_gbr_write_long(offset,data)
#define gbr_and_byte(offset,mask)   _builtin_gbr_and_byte(offset,mask)
#define gbr_or_byte(offset,mask)    _builtin_gbr_or_byte(offset,mask)
#define gbr_xor_byte(offset,mask)   _builtin_gbr_xor_byte(offset,mask)
#define gbr_tst_byte(offset,mask)   _builtin_gbr_tst_byte(offset,mask)
#define tas(addr)                   _builtin_tas(addr)
#define trapa(trap_no)              _builtin_trapa(trap_no)
#define macw(ptr1, ptr2, count)        _builtin_macw(ptr1, ptr2, count)
#define macwl(ptr1, ptr2, count, mask) _builtin_macwl(ptr1, ptr2, count, mask)
#define macl(ptr1, ptr2, count)        _builtin_macl(ptr1, ptr2, count)
#define macll(ptr1, ptr2, count, mask) _builtin_macll(ptr1, ptr2, count, mask)
#define trapa_svc                      _builtin_trapa_svc
#define prefetch                       _builtin_prefetch
#define set_fpscr(cr)                  _builtin_set_fpscr(cr)
#define get_fpscr()                    _builtin_get_fpscr()
#define fipr(vec1, vec2)               _builtin_fipr(vec1, vec2)
#define ftrv(vec1, vec2)               _builtin_ftrv(vec1, vec2)
#define ftrvadd(vec1, vec2, vec3)      _builtin_ftrvadd(vec1, vec2, vec3)
#define ftrvsub(vec1, vec2, vec3)      _builtin_ftrvsub(vec1, vec2, vec3)
#define mtrx4mul(mx1, mx2)             _builtin_mtrx4mul(mx1, mx2)
#define mtrx4muladd(mx1, mx2, mx3)     _builtin_mtrx4muladd(mx1, mx2, mx3)
#define mtrx4mulsub(mx1, mx2, mx3)     _builtin_mtrx4mulsub(mx1, mx2, mx3)
#define ld_ext(mx)                     _builtin_ld_ext(mx)
#define st_ext(mx)                     _builtin_st_ext(mx)
#define add4(vec1, vec2, vec3)         _builtin_add4(vec1, vec2, vec3)
#define sub4(vec1, vec2, vec3)         _builtin_sub4(vec1, vec2, vec3)

#endif