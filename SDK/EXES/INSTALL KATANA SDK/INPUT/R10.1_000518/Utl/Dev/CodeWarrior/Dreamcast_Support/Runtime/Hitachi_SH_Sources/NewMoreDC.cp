/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	NewMore.cp												*/
/*	Purpose...:	standard C++ library									*/
/*  Copyright.: ©Copyright 1993-99 by metrowerks inc					*/
/************************************************************************/

#include <stdlib.h>
#include <new.h>
//#include <Memory.h>
#include <CPlusLib.h>


typedef struct Handle_type {
	void *theMem;
} Handle;

// void (*new_handler)();

/************************************************************************/
/*	Purpose..: 	Allocate memory	(handle)								*/
/*	Input....:	size of memory to allocate								*/
/*	Return...:	handle to memory or 0L									*/
/************************************************************************/
void *__new_hdl(size_t size)
{
	Handle_type	*p; 
	p = (Handle_type *)malloc(sizeof(Handle_type));
	p->theMem = malloc(size);
	return (p);
}

/************************************************************************/
/*	Purpose..: 	Dispose memory (handle)									*/
/*	Input....:	handle to memory or 0L (no action if 0L)				*/
/*	Return...:	---														*/
/************************************************************************/
void __del_hdl(void *hdl)
{
	Handle_type *p=(Handle_type *)hdl;
	free(p->theMem);
	free(p);
}


/*
 *	__copy		-	copy 'size' bytes data from 'from' to 'to'
 *
 *	We return the pointer to the destination. If it is 0, no copy is performed.
 *
 */
// Already defined in CPlusLib.cp LBV
//void *__copy(char *to, char *from, size_t size)
//{
//	char *p;
//	
//	if (to && size) {
//		p = to;
//		do {
//			*p = *from;
//			++p;
//			++from;
//			--size;
//		} while (size);
//	}
//	
//	return(to);
//}
