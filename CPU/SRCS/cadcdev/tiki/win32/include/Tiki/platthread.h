#pragma once

// We define these manually to avoid the massive namespace corruption
// that will result from including windows.h :(
#ifndef WINSPOOLAPI
typedef void * HANDLE;
#endif

namespace Tiki {
namespace Thread {

typedef HANDLE thread_t;
typedef HANDLE mutex_t;
typedef HANDLE cond_t;

}
}


