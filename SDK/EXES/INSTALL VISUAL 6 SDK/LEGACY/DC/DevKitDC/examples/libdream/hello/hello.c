/* This is the standard Hello World program; once again this is an example
   of how you can initialize a minimal amount of hardware if you
   are careful. */

#include <kos.h>

int main(int argc, char **argv) {
	/* Do partial setup (serial only) */
	dbgio_init();

	printf("Hello world!\r\n");

	return 0;
}
