/* KallistiOS ##version##

   stdio.h
   (c)2000-2002 Dan Potter

   $Id: stdio.h,v 1.2 2002/03/15 06:45:42 bardtx Exp $

*/

#ifndef __STDIO_H
#define __STDIO_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <unistd.h>
#include <stdarg.h>
#include <kos/fs.h>

/* ANSI style wrappers for some of the fileio functions */

/* BUFSIZ for ANSI compliance; note that we actually don't have any
   sort of buffering */
#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

#ifndef EOF
#define EOF (-1)
#endif

typedef struct _FILE_t FILE;
typedef off_t fpos_t;

/* For ANSI compatability */
#define stdin ( (FILE *)1 )
#define stdout ( (FILE *)2 )
#define stderr ( (FILE *)2 )

void     clearerr(FILE *);
int      fclose(FILE *);
FILE    *fdopen(int, const char *);
int      feof(FILE *);
int      ferror(FILE *);
int      fflush(FILE *);
int      fgetc(FILE *);
int      fgetpos(FILE *, fpos_t *);
char    *fgets(char *, int, FILE *);
int      fileno(FILE *);
FILE    *fopen(const char *, const char *);
int      fprintf(FILE *, const char *, ...);
int      fputc(int, FILE *);
int      fputs(const char *, FILE *);
size_t   fread(void *, size_t, size_t, FILE *);
FILE    *freopen(const char *, const char *, FILE *);
int      fscanf(FILE *, const char *, ...);
int      fseek(FILE *, long int, int);
int      fseeko(FILE *, off_t, int);
int      fsetpos(FILE *, const fpos_t *);
long int ftell(FILE *);
off_t    ftello(FILE *);
size_t   fwrite(const void *, size_t, size_t, FILE *);
int      getc(FILE *);
int      getchar(void);
char    *gets(char *);
int      getw(FILE *);
int      pclose(FILE *);
void     perror(const char *);
FILE    *popen(const char *, const char *);
int      printf(const char *, ...);
int      putc(int, FILE *);
int      putchar(int);
int      puts(const char *);
int      putw(int, FILE *);
int      remove(const char *);
int      rename(const char *, const char *);
void     rewind(FILE *);
int      scanf(const char *, ...);
void     setbuf(FILE *, char *);
int      setvbuf(FILE *, char *, int, size_t);
int      snprintf(char *, size_t, const char *, ...);
int      sprintf(char *, const char *, ...);
int      sscanf(const char *, const char *, ...);
char    *tempnam(const char *, const char *);
FILE    *tmpfile(void);
char    *tmpnam(char *);
int      ungetc(int, FILE *);
int      vfprintf(FILE *, const char *, va_list);
int      vprintf(const char *, va_list);
int      vsnprintf(char *, size_t, const char *, va_list);
int      vsprintf(char *, const char *, va_list);

/* To make porting programs a bit easier.. WARNING: only works on GCC */
#define fprintf(BLAGH, ARGS...) printf(ARGS)

/* Kernel debugging printf; all output sent to this is filtered through
   a kernel log level check before actually being printed. This way, you
   can set the level of debug info you want to see (or want your users
   to see). */
void dbglog(int level, const char *fmt, ...) __printflike(2, 3);

/* Log levels for the above */
#define DBG_DEAD	0		/* The system is dead */
#define DBG_CRITICAL	1		/* A critical error message */
#define DBG_ERROR	2		/* A normal error message */
#define DBG_WARNING	3		/* Potential problem */
#define DBG_NOTICE	4		/* Normal but significant */
#define DBG_INFO	5		/* Informational messages */
#define DBG_DEBUG	6		/* User debug messages */
#define DBG_KDEBUG	7		/* Kernel debug messages */

/* Set debug level */
void dbglog_set_level(int level);

__END_DECLS

#endif	/* __STDIO_H */

