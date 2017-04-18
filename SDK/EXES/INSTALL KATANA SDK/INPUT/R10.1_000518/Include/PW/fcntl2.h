/*
 * fcntl2.h
 *
 * Stuff that should have been in fcntl.h but wasn't.
 *
 * Created 13 Nov 96 by scole
 * Copyright 1996 PlanetWeb, Inc.
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/fcntl2.h 1.10 1999-03-15 22:52:12+00 soohoo Exp $
 *
 * $Log: fcntl2.h $
 * Revision 1.10  1999-03-15 22:52:12+00  soohoo
 * Added Katana to a few defines...
 *
 * Revision 1.9  1999-03-08 16:43:48-0800  doug
 * Added WIN32.
 *
 * Revision 1.8  1999-01-13 16:19:47-0800  may
 * Update to include toshiba.
 *
 * Revision 1.7  1998-12-17 10:04:05-0800  soohoo
 * Added MediaMatics.
 *
 * Revision 1.6  1998-03-06 17:06:42-0800  scole
 * Puma fixes.
 *
 * Revision 1.5  1997-03-05 13:37:06-0800  scole
 * Fixed the PSX variety.
 *
 * Revision 1.4  1997-02-26 14:08:17-0800  scole
 * O_NDELAY is broken for 8x8.
 *
 * Revision 1.3  1997-01-15 14:11:47-0800  scole
 * PSX additions.
 *
 * Revision 1.2  1996-11-27 11:51:59-0800  scole
 * Replaced tabs with blanks for better formatting.
 *
 * Revision 1.1  1996-11-18 11:45:58-0800  scole
 * Initial revision
 *
 */
#ifndef __FCNTL2_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __FCNTL2_H__

#if __PSX__ || __MMATICS__ || __TOSHIBA__ || __WIN32__ || __KATANA__
/* PSX is missing everything! But I'm only going to put in the
 * constants that make sense for the network */
#define F_SETFL     0x01                /* Set file status flags */
#define F_GETFL     0x02                /* Get file status flags */
#if __MMATICS__ || __TOSHIBA__ || __WIN32__ || __KATANA__
#define O_NONBLOCK  0x100				/* What should this be? */
#else
#define O_NONBLOCK  FNBLOCK
#endif
#else /* __PSX__ */

#ifndef O_NONBLOCK
#if __8x8__
#define O_NONBLOCK 0x100
#elif defined(O_NDELAY)
#define O_NONBLOCK O_NDELAY
#else
#define O_NONBLOCK 0x100
#endif
#endif

#endif

#ifdef __cplusplus
}
#endif
#endif /* __FCNTL2_H__ */
    