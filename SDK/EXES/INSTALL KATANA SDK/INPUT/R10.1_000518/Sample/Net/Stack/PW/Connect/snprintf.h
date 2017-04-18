/*
 * snprintf.h
 *
 * Prototype for snprintf.
 *
 * Created 8/1/96 by scole
 * Copyright 1996 PlanetWeb, Inc.
 *
 * $Header: h:/RCS/netsamp/snprintf.h 1.1 1999-03-15 14:41:20-0800 soohoo Exp $
 *
 * $Log: snprintf.h $
 * Revision 1.1  1999-03-15 14:41:20-0800  soohoo
 * Initial revision
 *
 * Revision 1.2  1999-01-13 16:53:07-0800  may
 * Added toshiba external decl.
 *
 * Revision 1.1  1998-04-07 18:38:04-0700  soohoo
 * Initial revision
 *
 * Revision 1.1  1996-08-01 15:15:31-0700  scole
 * Initial revision
 *
 */

#ifndef __SNPRINTF_H__
#define __SNPRINTF_H__

#if __TOSHIBA__
int snprintf(char *buf, size_t max, const char *format, ...);
#else
int snprintf(char *buf, size_t max, const char *format, ...) __attribute__((format (printf, 3, 4)));
#endif

#endif // __SNPRINTF_H__
