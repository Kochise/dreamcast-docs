/* KallistiOS 1.2.0

   stacktrace.c
   (c)2002 Dan Potter
*/

#include <kos.h>

void func() {
	arch_stk_trace(0);
}

int main(int argc, char **argv) {
	arch_stk_trace(0);

	func();

	return 0;
}


