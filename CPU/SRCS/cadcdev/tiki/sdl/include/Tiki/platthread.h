/*
   Tiki

   platthread.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_PLATTHREAD_H
#define __TIKI_PLATTHREAD_H

#include <pthread.h>

namespace Tiki {
namespace Thread {

typedef ::pthread_t thread_t;
typedef ::pthread_mutex_t mutex_t;
typedef ::pthread_cond_t cond_t;

}
}

#endif	// __TIKI_PLATTHREAD_H

