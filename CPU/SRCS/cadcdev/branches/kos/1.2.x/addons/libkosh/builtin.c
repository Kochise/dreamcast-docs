/*
 * builtin.c - shell builtin commands
 *
 * (C) 2000 Jordan DeLong
 */

#include <kos.h>
#include <string.h>
#include <ctype.h>
#include "builtin.h"
#include "chdir.h"
#include "kosh.h"

typedef struct {
	const char *command;
	const char *desc;
	void (*handler)(int argc, char *argv[]);
} builtin_t;

extern builtin_t builtins[];

/* print command list/desc */
static void builtin_help(int argc, char *argv[]) {
	int i;

	if (argc > 1) {
		for (i = 0; builtins[i].command != NULL; i++) {
			if (strcmp(argv[1], builtins[i].command) == 0) {
				conio_printf("%s - %s\n", builtins[i].command, builtins[i].desc);
				return;
			}
		}
	} else {
		conio_printf("kosh commands:\n  ");
	
		for (i = 0; builtins[i].command != NULL; i++) {
			conio_printf("%s ", builtins[i].command);
		}

		conio_printf("\nType 'help command' for a description.\n");
	}	
}

/* exit the shell */
static void builtin_exit(int argc, char *argv[]) {
	if (argc > 1)
		conio_printf("Superfluous arguments to exit\n");
	else
		kosh_exit = 1;
}

/* list the contents of the directory */
static void builtin_ls(int argc, char *argv[]) {
	dirent_t *ent;
	uint32 hnd;
	char dir[MAX_FN_LEN];
	int lflag;

	lflag = 0;

	if (argc > 1) {
		if (strcmp(argv[1], "-l") == 0)
			lflag = 1;
	}

	getcwd(dir, MAX_FN_LEN);

	conio_printf("Reading %s\n", dir);

	hnd = fs_open(dir, O_RDONLY | O_DIR);
	if (!hnd) {
		conio_printf("Error opening %s\n", dir);
		return;
	}

	while ((ent = fs_readdir(hnd)) != NULL) {
		if (lflag)
			conio_printf("%12d bytes %s\n", ent->size, ent->name);
		else
			conio_printf("%s\n", ent->name);
	}

	fs_close(hnd);
}

/* change the current directory */
static void builtin_cd(int argc, char *argv[]) {
	if (argc != 2) {
		conio_printf("usage: cd dir\n");
		return;
	}

	chdir(argv[1]);
}

/* print the current directory */
static void builtin_pwd(int argc, char *argv[]) {
	char buff[MAX_FN_LEN];

	conio_printf("%s\n", getcwd(buff, MAX_FN_LEN));
}

/* clear the screen */
static void builtin_clear(int argc, char *argv[]) {
	conio_clear();
	conio_gotoxy(0, 0);
}

/* echo, heh */
static void builtin_echo(int argc, char *argv[]) {
	int i;

	for (i = 1; i < argc; i++)
		conio_printf("%s ", argv[i]);
	conio_printf("\n");
}

/* cat text files to the screen */
static void builtin_cat(int argc, char *argv[]) {
	uint32 hnd;
	char buff[256];
	char fn[MAX_FN_LEN];
	int cnt;

	if (argc != 2) {
		conio_printf("usage: cat filename\n");
		return;
	}

	/* the the abs path */
	makeabspath(fn, argv[1], MAX_FN_LEN);

	hnd = fs_open(fn, O_RDONLY);
	if (!hnd) {
		conio_printf("Error opening %s\n", fn);
		return;
	}

	while ((cnt = fs_read(hnd, buff, 256)) != 0) {
		int i;

		for (i = 0; i < cnt; i++) {
			if (buff[i] == '\r') {
				if (buff[i + 1] != '\0')
					break;
				if (buff[++i] != '\n')
					conio_putch('\r');
			}
			if (isascii(buff[i]))
				conio_putch(buff[i]);
		}
	}

	fs_close(hnd);
}

/* dump files as hex */
static void builtin_hd(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];
	char buff[10];
	uint32 hnd;
	int cnt;
	
	if (argc != 2) {
		conio_printf("usage: hd file\n");
		return;
	}

	makeabspath(fn, argv[1], MAX_FN_LEN);

	hnd = fs_open(fn, O_RDONLY);
	if (!hnd) {
		conio_printf("Error opening %s\n", fn);
		return;
	}

	/* do the hexdump */
	while ((cnt = fs_read(hnd, buff, 10)) != 0) {
		int i;
		
		for (i = 0; i < cnt; i++)
			conio_printf("%02x ", (unsigned char) buff[i]);
		conio_deadvance_cursor();
		//cursor.col = 10 * 3 + 2;
		conio_putch('|');
		for (i = 0; i < cnt; i++) {
			if (isprint(buff[i]))
				conio_putch(buff[i]);
			else
				conio_putch('.');
		}
		conio_printf("|\n");
	}

	fs_close(hnd);
}

/* copy files */
static void builtin_cp(int argc, char *argv[]) {
	char buff[256];
	char srcfn[MAX_FN_LEN];
	char destfn[MAX_FN_LEN];
	uint32 src;
	uint32 dest;
	int cnt;

	if (argc != 3) {
		conio_printf("usage: cp src dest\n");
		return;
	}

	/* get abs paths */
	makeabspath(srcfn, argv[1], MAX_FN_LEN);
	makeabspath(destfn, argv[2], MAX_FN_LEN);

	src = fs_open(srcfn, O_RDONLY);
	if (!src) { conio_printf("Error opening %s\n", srcfn); return; }

	dest = fs_open(destfn, O_WRONLY);
	if (!dest) { conio_printf("Error opening %s\n", destfn); fs_close(src); return; }

	while ((cnt = fs_read(src, buff, 256)) != 0)
		fs_write(dest, buff, cnt);

	fs_close(src);
	fs_close(dest);
}

/* unlink files */
static void builtin_rm(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];

	if (argc != 2) {
		conio_printf("usage: rm file\n");
		return;
	}

	/* get the abs path for the fn to rem */
	makeabspath(fn, argv[1], MAX_FN_LEN);

	if (fs_unlink(fn) != 0)
		conio_printf("Error unlinking %s.\n", fn);
}

/* create a directory */
static void builtin_mkdir(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];
	
	if (argc != 2) {
		conio_printf("usage: mkdir dirname\n");
		return;
	}

	/* get the abs path for the dir to create */
	makeabspath(fn, argv[1], MAX_FN_LEN);

	if (fs_mkdir(fn) != 0)
		conio_printf("Error making directory %s.\n", fn);
}

/* delete a directory */
static void builtin_rmdir(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];
	
	if (argc != 2) {
		conio_printf("usage: rmdir dirname\n");
		return;
	}

	/* get the abs path for the dir to delete */
	makeabspath(fn, argv[1], MAX_FN_LEN);

	if (fs_rmdir(fn) != 0)
		conio_printf("Error deleting directory %s.\n", fn);
}

/* change console colors */
static void builtin_theme(int argc, char *argv[]) {
	if (argc != 2) {
		conio_printf("usage: theme themename\nchoices are 'matrix', 'c64' and 'plain'\n");
		return;
	}

	if (strcmp(argv[1], "matrix") == 0)
		conio_set_theme(CONIO_THEME_MATRIX);
	else if (strcmp(argv[1], "c64") == 0)
		conio_set_theme(CONIO_THEME_C64);
	else if (strcmp(argv[1], "plain") == 0)
		conio_set_theme(CONIO_THEME_PLAIN);
	else 
		conio_printf("unknown theme\n");
}

/* exit to the DC menus */
static void builtin_menu(int argc, char *argv[]) {
	conio_printf("bye!\n");
	arch_menu();
}

/* Mount a romdisk image */
static void builtin_mount_romdisk(int argc, char *argv[]) {
	void * data;
	
	if (argc != 3) {
		conio_printf("usage: mount_romdisk srcimg mountpoint\n");
		return;
	}

	/* Load up the romdisk image */
	conio_printf("Loading the romdisk image...\n");
	if (fs_load(argv[1], &data) <= 0) {
		conio_printf("error: invalid romdisk source image\n");
		if (data != NULL)
			free(data);
		return;
	}

	/* Attempt to mount it */
	conio_printf("Mounting on %s...\n", argv[2]);
	if (fs_romdisk_mount(argv[2], (const uint8 *)data, 1) < 0) {
		conio_printf("error: can't mount romdisk image\n");
		free(data);
		return;
	}

	conio_printf("Success!\n");
	return;
}

/* Print out a list of running threads */
static void builtin_threads(int argc, char *argv[]) {
	kthread_t * cur;

	thd_pslist(conio_printf);
}

/* Print out memory usage statistics */
static void builtin_mstats(int argc, char *argv[]) {
	struct mallinfo mi = mallinfo();
	
	conio_printf("Memory usage:\n");
	conio_printf("  Max system bytes = %10lu\n",
		(unsigned long)(mi.usmblks));
	conio_printf("  System bytes = %10lu\n",
		(unsigned long)(mi.arena + mi.hblkhd));
	conio_printf("  In use bytes = %10lu\n",
		(unsigned long)(mi.uordblks + mi.hblkhd));
	conio_printf("  Current sbrk = %08lx\n",
		(unsigned long)(sbrk(0)));
}

/* Kill the whole KOS program */
static void builtin_die(int argc, char *argv[]) {
	conio_printf("Goodbye cruel world...\n");
	arch_exit();
}

#ifdef _arch_dreamcast
/* Do a screen dump -- note, won't always work 100% due to threading stuff */
static void builtin_sshot(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];

	if (argc != 2) {
		conio_printf("usage: sshot outfile.ppm\n");
		return;
	}
	
	/* get the abs path for the dir to create */
	makeabspath(fn, argv[1], MAX_FN_LEN);

	conio_printf("Doing a screen shot to %s\n", fn);
	vid_screen_shot(fn);
	conio_printf("Done!\n");
}
#endif


/* table of the builtin commands, their help mesg,  and their handler funcs */
builtin_t builtins[] = {
	{"help",	"Hmm...",				builtin_help},
	{"exit", 	"Exit kosh",				builtin_exit},
	{"ls", 		"List contents of directories",		builtin_ls},
	{"cd",		"Change directory",			builtin_cd},
	{"pwd",		"Print the current directory",		builtin_pwd},
	{"clear",	"Clear the screen",			builtin_clear},
	{"echo",	"Echo text to the console",		builtin_echo},
	{"cat",		"Display text files to the console",	builtin_cat},
	{"hd",		"Dump files as hex to the console",	builtin_hd},
	{"cp",		"Copy files",				builtin_cp},
	{"rm",		"Remove files",				builtin_rm},
	{"mkdir",	"Create a directory",			builtin_mkdir},
	{"rmdir",	"Delete a directory",			builtin_rmdir},
	{"theme",	"Change the console color theme",	builtin_theme},
	{"menu",	"Exit KOS to the DC menus",		builtin_menu},
	{"mount_romdisk", "Mount a romdisk image",		builtin_mount_romdisk},
	{"threads",	"Get a list of running threads",	builtin_threads},
	{"mstats",	"Get memory statistics",		builtin_mstats},
	{"die",		"Call arch_exit()",			builtin_die},
#ifdef _arch_dreamcast
	{"sshot",	"Make a screen shot",			builtin_sshot},
#endif
	{ NULL,		NULL,					NULL }
};

/* try to run a builtin command, return 0 if there is no such builtin */
int builtin_command(int argc, char *argv[]) {
	int i;

	for (i = 0; builtins[i].command != NULL; i++) {
		if (strcmp(argv[0], builtins[i].command) == 0) {
			builtins[i].handler(argc, argv);
			return 1;
		}
	}

	return 0;
}


