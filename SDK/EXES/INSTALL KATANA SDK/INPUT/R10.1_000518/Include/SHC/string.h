/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = string :                                             */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   LINK =                                                      */
/*   NOTE =                                                      */
/*          ;                                                    */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/
#ifndef _STRING_SHC
#define _STRING_SHC

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
extern void *memcpy(void *, const void *, size_t);
extern void *memmove(void *, const void *, size_t);
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char *, size_t);
extern char *strcat(char *, const char *);
extern char *strncat(char *, const char *,size_t);
extern int  memcmp(const void *, const void *,size_t);
extern int  strcmp(const char *, const char *);
extern int  strncmp(const char *, const char *, size_t);
extern void *memchr(const void *, int, size_t);
extern char *strchr(const char *, int);
extern size_t strcspn(const char *, const char *);
extern char *strpbrk(const char *, const char *);
extern char *strrchr(const char *, int);
extern size_t strspn(const char *, const char *);
extern char *strstr(const char *, const char *);
extern char *strtok(char *, const char *);
extern void *memset(void *, int, size_t);
extern char *strerror(int);
extern size_t strlen(const char *);
#ifdef __cplusplus
}
#endif

#define strcpy(s1,s2) _builtin_strcpy(s1,s2)
#define strcmp(s1,s2) _builtin_strcmp(s1,s2)

#endif