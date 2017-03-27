/* types.h */

#ifndef	_TYPES_H
#define	_TYPES_H

#ifndef NULL
#define NULL	((void *)0)
#endif /* NULL */

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;

typedef enum {
	FALSE	= 0,
	TRUE	= 1,
} bool;

#endif /* _TYPE_H */
