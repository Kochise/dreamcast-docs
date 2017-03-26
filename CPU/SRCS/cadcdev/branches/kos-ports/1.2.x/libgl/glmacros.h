/* GL for KOS ##version##

   glmacros.c
   (c)2001 Paul Boese

   $Id: glmacros.h,v 1.5 2002/06/28 04:57:31 axlen Exp $
*/

#ifndef __GL_GLMACROS_H
#define __GL_GLMACROS_H


#define ABS(n) ( (n)<(0.0f) ? (-n):(n) )
#define NEG(n) ( (n)>(0.0f) ? (-n):(n) )
#define CLAMP01(x) ( (x)<(0.0f) ? ((0.0f)) : ((x)>(1.0f) ? ((1.0f)) : (x)) )

/* Clamp X to [MIN,MAX]: */
#define CLAMP( X, MIN, MAX )  ( (X)<(MIN) ? (MIN) : ((X)>(MAX) ? (MAX) : (X)) )

#endif /* __GL_GLMACROS_H */
