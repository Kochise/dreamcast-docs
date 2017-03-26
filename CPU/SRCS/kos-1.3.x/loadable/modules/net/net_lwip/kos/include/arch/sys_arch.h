/* KallistiOS ##version##

   kos/sys_arch.h
   Copyright (C)2003 Dan Potter
*/
      
#ifndef __SYS_ARCH_KOS_H
#define __SYS_ARCH_KOS_H

#include <time.h>
#include <kos/sem.h>
#include <kos/thread.h>

#define SYS_MBOX_NULL NULL
#define SYS_SEM_NULL NULL

typedef semaphore_t * sys_sem_t;

struct sys_mbox;
typedef struct sys_mbox * sys_mbox_t;

struct sys_thread;
typedef struct sys_thread * sys_thread_t;

typedef int sys_prot_t;

#endif /* __SYS_ARCH_KOS_H */
