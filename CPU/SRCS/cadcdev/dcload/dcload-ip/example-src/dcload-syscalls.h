#ifndef __DCLOAD_SYSCALLS_H__
#define __DCLOAD_SYSCALLS_H__

#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2

int link (const char *oldpath, const char *newpath);
int read (int file, char *ptr, int len);
int lseek (int file, int ptr, int dir);
int write ( int file, char *ptr, int len);
int close (int file);
int fstat (int file, struct stat *st);
int open (const char *path, int flags);
int creat (const char *path, int mode);
int unlink (const char *path);
void exit (int status);
int stat (const char *path, struct stat *st);
int chmod (const char *path, short mode);
int utime (const char *path, char *times);
int chdir (const char *path);
long time(long *t);
void assign_wrkmem(unsigned char *wrkmem);
int gethostinfo(unsigned int *ip, unsigned int *port);

#endif
