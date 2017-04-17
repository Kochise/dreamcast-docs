#include "dcload-syscall.h"

int link (const char *oldpath, const char *newpath)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pclinknr, oldpath, newpath);
    else
	return -1;
}

int read (int file, char *ptr, int len)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcreadnr, file, ptr, len);
    else
	return -1;
}

int lseek (int file, int ptr, int dir)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pclseeknr, file, ptr, dir);
    else
	return -1;
}

int write ( int file, char *ptr, int len)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcwritenr, file, ptr, len);
    else
	return -1;
}

int close (int file)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcclosenr, file);
    else
	return -1;
}

int fstat (int file, struct stat *st)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcfstatnr, file, st);
    else
	return -1;
}

int open (const char *path, int flags)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcopennr, path, flags);
    else
	return -1;
}

int creat (const char *path, int mode)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pccreatnr, path, mode);
    else
	return -1;
}

int unlink (const char *path)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcunlinknr, path);
    else
	return -1;
}

void exit (int status)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	dcloadsyscall(pcexitnr);
    __exit(status);
}

int stat (const char *path, struct stat *st)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcstatnr, path, st);
    else
	return -1;
}

int chmod (const char *path, short mode)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcchmodnr, path, mode);
    else
	return -1;
}

int utime (const char *path, char *times)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcutimenr, path, times);
    else
	return -1;
}

int chdir (const char *path)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pcchdirnr, path);
    else
	return -1;
}

long time(long *t)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	return dcloadsyscall(pctimenr, t);
    else
	return -1;
}

void assign_wrkmem(unsigned char *wrkmem)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
	dcloadsyscall(pcassignwrkmem, wrkmem);
}
