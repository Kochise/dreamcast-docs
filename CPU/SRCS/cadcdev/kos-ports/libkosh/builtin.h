/*
 * builtin.h - shell builtins
 *
 * (C) 2000 Jordan DeLong
 */
#ifndef _KOSH_BUILTIN_H
#define _KOSH_BUILTIN_H

/* the func */
int kosh_builtin_command(int argc, char *argv[]);

void kosh_builtins_init();
void kosh_builtins_shutdown();

#endif
		

