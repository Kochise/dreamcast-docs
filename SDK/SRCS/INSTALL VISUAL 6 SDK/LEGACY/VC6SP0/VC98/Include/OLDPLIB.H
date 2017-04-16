
//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1993.
//
//  MODULE: pmacros.h
//
//  Modification History
//
//  raypa           06/24/93        Created.
//=============================================================================

#ifndef OLDPLIBINC
#define OLDPLIBINC

extern UCHAR * WINAPIV strcpy1(UCHAR * string1, UCHAR * string2);
extern UCHAR * WINAPIV itoa1(WORD num, UCHAR * string);
extern UCHAR * WINAPIV byte_flag_to_string(UCHAR byte, UCHAR mask, UCHAR * string);
extern UCHAR * WINAPIV word_flag_to_string(WORD word, WORD mask, UCHAR * string);
extern UCHAR * WINAPIV dword_flag_to_string(DWORD dword, DWORD mask, UCHAR * string);
extern void WINAPIV fm_byte_flags(LPPROPERTYINST prop);
extern void WINAPIV fm_word_flags(LPPROPERTYINST prop);
extern void WINAPIV fm_dword_flags(LPPROPERTYINST prop);
extern UCHAR * WINAPIV prop_name_equals(LPPROPERTYINST prop);
extern UCHAR * WINAPIV property_name(LPPROPERTYINST prop, UCHAR * string);
extern void WINAPIV fm_property_name(LPPROPERTYINST prop);
extern void WINAPIV fm_dword10(LPPROPERTYINST prop);
extern void WINAPIV hex_canon(UCHAR * hex, UCHAR * dest, int len);
extern void WINAPIV hex_canon2(UCHAR * hex, UCHAR * dest, int len);
extern void WINAPIV fm_dword16(LPPROPERTYINST prop);
extern void WINAPIV fm_word10(LPPROPERTYINST prop);
extern void WINAPIV fm_word16(LPPROPERTYINST prop);
extern void WINAPIV fm_byte10(LPPROPERTYINST prop);
extern void WINAPIV fm_byte16(LPPROPERTYINST prop);
extern void WINAPIV fm_swap_word10(LPPROPERTYINST prop);
extern void WINAPIV fm_swap_word16(LPPROPERTYINST prop);
extern void WINAPIV fm_swap_dword10(LPPROPERTYINST prop);
extern void WINAPIV fm_swap_dword16(LPPROPERTYINST prop);
extern void WINAPIV fm_string(LPPROPERTYINST prop);
extern void WINAPIV fm_hex_string(LPPROPERTYINST prop);
extern void WINAPIV fm_word_set(LPPROPERTYINST prop);
extern void WINAPIV fm_dword_set(LPPROPERTYINST prop);
extern void WINAPIV fm_byte_set(LPPROPERTYINST prop);
extern UCHAR * WINAPIV time_string(ULPSYSTEMTIME time, UCHAR *string);
extern void WINAPIV fm_time(LPPROPERTYINST prop);
extern void WINAPIV fm_time_ex(LPPROPERTYINST prop);
extern void WINAPIV fm_largeint16(LPPROPERTYINST prop);

#endif

