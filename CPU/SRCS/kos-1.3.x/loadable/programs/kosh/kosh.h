/*
 * kosh.h
 *
 * (C) 2000 Jordan DeLong
 */
#ifndef _KOSH_KOSH_H
#define _KOSH_KOSH_H

#include <kos.h>
#include <conio/conio.h>

extern volatile int kosh_exit;

void input_oneloop();
void input_exec_one(char * buff);
void input_exec_script(const char * fn);

#endif

