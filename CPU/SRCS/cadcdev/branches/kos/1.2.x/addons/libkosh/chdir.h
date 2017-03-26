/*
 * chdir.h - current directory stuff
 *
 * (C) 2000 Jordan DeLong
 */
#ifndef _KOSH_CHDIR_H
#define _KOSH_CHDIR_H

#include <arch/types.h>

int makeabspath(char *buff, char *path, size_t size);
int chdir(char *dir);
char *getcwd(char *buf, size_t size);

#endif
