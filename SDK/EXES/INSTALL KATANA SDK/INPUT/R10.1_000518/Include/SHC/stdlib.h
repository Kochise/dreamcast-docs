/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = stdlib :                                             */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/
#ifndef _STDLIB_SHC
#define _STDLIB_SHC

#include <stddef.h>

struct _DIV_T_TAG {          /* tag define for div_t   */
    int quot;                /*  quotient              */
    int rem;                 /*  remainder             */
};                           /*                        */
struct _LDIV_T_TAG {         /* tag define for ldiv_t  */
    long quot;               /*  quotient              */
    long rem;                /*  remainder             */
};                           /*                        */

typedef struct _DIV_T_TAG div_t ;
/* int quot; int rem */
typedef struct _LDIV_T_TAG ldiv_t ;
/* long quot; long rem; */

#ifndef RAND_MAX
#define RAND_MAX  32767
#endif

#ifndef ERANGE
#define ERANGE  1100
#endif

#ifndef EDOM
#define EDOM    1101
#endif

#ifndef EDIV
#define EDIV    1102
#endif

#ifndef ESTRN
#define ESTRN   1104
#endif

#ifndef ECBASE
#define ECBASE  1200
#endif

#ifndef ETLN
#define ETLN    1202
#endif

#ifndef EEXP
#define EEXP    1204
#endif

#ifndef EEXPN
#define EEXPN   1206
#endif

#ifndef EFLOATO
#define EFLOATO 1210
#endif

#ifndef EFLOATU
#define EFLOATU 1220
#endif

#ifndef EDBLO
#define EDBLO   1250
#endif

#ifndef EDBLU
#define EDBLU   1260
#endif

#ifndef ELDBLO
#define ELDBLO  1270
#endif

#ifndef ELDBLU
#define ELDBLU  1280
#endif

extern volatile int _errno;
extern const double _HUGE_VAL;
#define HUGE_VAL  _HUGE_VAL

#ifdef __cplusplus
extern "C" {
#endif
extern double atof(const char *) ;
extern int atoi(const char *) ;
extern long int atol(const char *) ;
extern double strtod(const char *, char **) ;
extern long int strtol(const char *, char **, int);
extern int rand(void) ;
extern void srand(unsigned int);
extern void *calloc(size_t, size_t);
extern void free(void *) ;
extern void *malloc(size_t);
extern void *realloc(void *, size_t) ;
extern void *bsearch(const void *, const void *, size_t, size_t,
                                  int(*)(const void*,const void*) ) ;
extern void qsort(void *, size_t, size_t,
                                  int(*)(const void*,const void*) );

extern int abs(int);
extern div_t div(int, int);
extern long int labs(long int);
extern ldiv_t ldiv(long int, long int);
#ifdef __cplusplus
}
#endif

#endif
