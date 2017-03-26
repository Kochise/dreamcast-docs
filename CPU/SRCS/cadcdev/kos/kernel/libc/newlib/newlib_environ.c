/* KallistiOS ##version##

   newlib_environ.c
   Copyright (C)2004 Dan Potter

*/

char * __env[1] = { 0 };
char **environ = __env;
