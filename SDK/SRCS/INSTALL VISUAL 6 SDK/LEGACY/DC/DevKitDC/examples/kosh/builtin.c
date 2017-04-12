/*
 * builtin.c - shell builtin commands
 *
 * (C) 2000 Jordan DeLong
 */

#include <kos.h>
#include <string.h>
#include <ctype.h>
#include "builtin.h"
#include "conio.h"
#include "chdir.h"
#include "kosh.h"
#include "draw.h"

/* table of the builtin commands, their help mesg,  and their handler funcs */
struct {
	char *command;
	char *desc;
	void (*handler)(int argc, char *argv[]);
} builtins[] = {
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
	{"theme",	"Change the console color theme",	builtin_theme},
	{"menu",	"Exit KOS to the DC menus",		builtin_menu} /*,
	{"debug",	"Trigger KOS debug function",		builtin_debug} */
};

#define NUM_BUILTINS		13

/* try to run a builtin command, return 0 if there is no such builtin */
int builtin_command(int argc, char *argv[]) {
	int i;

	for (i = 0; i < NUM_BUILTINS; i++) {
		if (strcmp(argv[0], builtins[i].command) == 0) {
			builtins[i].handler(argc, argv);
			return 1;
		}
	}

	return 0;
}

/* print command list/desc */
void builtin_help(int argc, char *argv[]) {
	int i;

	if (argc > 1) {
		for (i = 0; i < NUM_BUILTINS; i++) {
			if (strcmp(argv[1], builtins[i].command) == 0) {
				conio_printf("%s - %s\n", builtins[i].command, builtins[i].desc);
				return;
			}
		}
	} else {
		conio_printf("kosh commands:\n  ");
	
		for (i = 0; i < NUM_BUILTINS; i++) {
			conio_printf("%s ", builtins[i].command);
		}

		conio_printf("\nType 'help command' for a description.\n");
	}	
}

/* exit the shell */
void builtin_exit(int argc, char *argv[]) {
	if (argc > 1)
		conio_printf("Superfluous arguments to exit\n");
	else
		kosh_exit = 1;
}

/* list the contents of the directory */
void builtin_ls(int argc, char *argv[]) {
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
void builtin_cd(int argc, char *argv[]) {
	if (argc != 2) {
		conio_printf("usage: cd dir\n");
		return;
	}

	chdir(argv[1]);
}

/* print the current directory */
void builtin_pwd(int argc, char *argv[]) {
	char buff[MAX_FN_LEN];

	conio_printf("%s\n", getcwd(buff, MAX_FN_LEN));
}

/* clear the screen */
void builtin_clear(int argc, char *argv[]) {
	conio_clear();
	conio_gotoxy(0, 0);
}

/* echo, heh */
void builtin_echo(int argc, char *argv[]) {
	int i;

	for (i = 1; i < argc; i++)
		conio_printf("%s ", argv[i]);
	conio_printf("\n");
}

/* cat text files to the screen */
void builtin_cat(int argc, char *argv[]) {
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
void builtin_hd(int argc, char *argv[]) {
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
		cursor.col = 10 * 3 + 2;
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
void builtin_cp(int argc, char *argv[]) {
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
void builtin_rm(int argc, char *argv[]) {
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

/* change console colors */
void builtin_theme(int argc, char *argv[]) {
	if (argc != 2) {
		conio_printf("usage: theme themename\nchoices are 'matrix', 'c64' and 'plain'\n");
		return;
	}

	if (strcmp(argv[1], "matrix") == 0)
		draw_theme = THEME_MATRIX;
	else if (strcmp(argv[1], "c64") == 0)
		draw_theme = THEME_C64;
	else if (strcmp(argv[1], "plain") == 0)
		draw_theme = THEME_PLAIN;
	else 
		conio_printf("unknown theme\n");
}

/* exit to the DC menus */
void builtin_menu(int argc, char *argv[]) {
	conio_printf("bye!\n");
	(*(void(**)())0x8c0000e0)(1);
}

/* trigger KOS debug function */
/*
#include <os/abi/fundamental.h>
#include <os/abi/libk.h>
void builtin_debug(int argc, char *argv[]) {
	abi_fundamental_t *fnd;

	fnd = lib_open("fundamental");
	if (!fnd) {
		conio_printf("Can't seem to open funamental lib\n");
		return;
	}

	conio_printf("debug returns %d\n", fnd->debug(0));

	lib_close(fnd);
}
*/


