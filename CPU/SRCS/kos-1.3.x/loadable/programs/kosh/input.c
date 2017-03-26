/*
 * input.c
 *
 * Copyright (C)2000 Jordan DeLong
 * Copyright (C)2003 Dan Potter
 */

#include <sys/process.h>
#include <errno.h>
#include "kosh.h"
#include "builtin.h"
#include "jobs.h"

/* Execute a single command input by the user or a script */
void input_exec_one(char * buff) {
	int argc;
	char *argv[20];		/* limit to 20 args (should be plenty) */
	char *str = buff;
	int i;

	/* we don't care if the user just hit enter */
	if (buff[0] == '\0')
		return;

	/* seperate the string into args */
	for (argc = 0; argc < 20;) {
		if ((argv[argc] = strsep(&str, " \t\n")) == NULL)
			break;
		if (*argv[argc] != '\0')
			argc++;
	}

	/* try to run the command as a builtin */
	if (!builtin_command(argc, argv)) {
		char afn[256];
		int bkg, i;
		kprocess_t * proc;
		job_t * j;

		makeabspath(afn, argv[0], MAX_FN_LEN);

		/* Are we backgrounding? */
		if (argc > 0 && !strcmp(argv[argc-1], "&"))
			bkg = 1;
		else
			bkg = 0;

		/* the builtin failed so we try an external */
		if (bkg)
			j = job_add(NULL);
		proc = process_vfork();
		if (bkg)
			j->proc = proc;
		if (!proc) {
			conio_printf("kosh: %s: can't vfork() -- %s\n", afn, strerror(errno));
			job_remove(NULL);
			return;
		}

		if (process_execv(afn, argc, (const char **)argv) < 0) {
			conio_printf("kosh: %s: can't exec() -- %s\n", afn, strerror(errno));
			if (bkg)
				job_remove(proc);
		} else {
			if (!bkg)
				conio_printf("kosh: %s returned %d\n", afn, process_wait(proc));
		}
	}
}

/* read command line, try to execute builtin commands, otherwise externals */
void input_oneloop() {
	char buff[256];

	/* Wait for a line of input */
	conio_printf("$ ");
	while (conio_input_getline(1000, buff, 255) < 0) {
		if (kosh_exit)
			return;
	}

#if 0
	fs_write(1, "$ ", 2);
	memset(buff, 0, 256);
	i = 0;
	while (i < 255) {
		/* Wait for input */
		if (fs_read(0, buff + i, 1) <= 0) {
			thd_sleep(1000/60);
		} else {
			/* If it was a \r, then go ahead and process */
			if (buff[i] == '\r') {
				buff[i] = 0;
				break;
			}

			i++;
		}
	}
#endif

	input_exec_one(buff);
}

/* Open the requested file and execute each command as if it was
   typed by the user. We use stdio here to get fgets(). */
void input_exec_script(const char *fn) {
	char buff[256];
	FILE *f;

	f = fopen(fn, "rb");
	if (!f) {
		printf("kosh: can't open input file '%s'\n", fn);
		return;
	}

	while (fgets(buff, 256, f)) {
		printf("%s", buff);
		if (buff[0] == '#')
			continue;
		if (buff[strlen(buff)-1] == '\n')
			buff[strlen(buff)-1] = 0;
		if (buff[strlen(buff)-1] == '\r')
			buff[strlen(buff)-1] = 0;
		input_exec_one(buff);
	}

	fclose(f);
}
