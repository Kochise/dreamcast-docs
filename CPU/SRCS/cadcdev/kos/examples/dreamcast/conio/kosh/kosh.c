/*
 * kosh.c - console shell for kallistios (A Rough version)
 *
 * (C) 2000 Jordan DeLong
 */

#include <stdio.h>
#include <kos.h>
#include <kosh/kosh.h>
#include <conio/conio.h>

// This example has been completely gutted at this point since all the
// relevant functionality is now in libconio and libkosh. But those two
// do a lot more than the original did. "Strike me down, programmer, and
// I shall only become more powerful!"
//
// ...
//

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

void test_builtin(int argc, char **argv) {
	int i;
	
	conio_printf("You passed %d args:\n", argc);
	for (i=0; i<argc; i++)
		conio_printf("%s\n", argv[i]);
}

int main(int argc, char **argv) {
	pvr_init_defaults();

	printf("kosh starting\n");

	/* initialize the conio service */
	conio_init(CONIO_TTY_PVR, CONIO_INPUT_LINE);
	// conio_init(CONIO_TTY_SERIAL, CONIO_INPUT_LINE);

	/* initialize kosh */
	kosh_init();

	/* Add a test builtin */
	kosh_builtin_add("test", "This is a test command.", test_builtin);

	/* wait for the user to exit */
	kosh_join();

	/* shutdown kosh */
	kosh_shutdown();

	/* shutdown console i/o */
	conio_shutdown();

	printf("kosh is done\n");
	return 0;
}
