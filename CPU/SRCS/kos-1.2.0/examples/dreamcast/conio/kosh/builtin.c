/*
 * builtin.c - shell builtin commands
 *
 * (C) 2000 Jordan DeLong
 */

#include <kos.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <oggvorbis/sndoggvorbis.h>
#include "builtin.h"
#include "chdir.h"
#include "kosh.h"

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
	{"mkdir",	"Create a directory",			builtin_mkdir},
	{"rmdir",	"Delete a directory",			builtin_rmdir},
	{"theme",	"Change the console color theme",	builtin_theme},
	{"menu",	"Exit KOS to the DC menus",		builtin_menu},
	{"mount_romdisk", "Mount a romdisk image",		builtin_mount_romdisk},
	{"exec",	"Load and exec another DC program",	builtin_exec},
	{"romcheck",	"Report info about flash rom",		builtin_romcheck},
	{"periphs",	"Info about attached peripherals",	builtin_periphs},
	{"md",		"Dump memory as hex to the console",	builtin_md},
	{"ogg",		"OggVorbis player control",		builtin_ogg},
	{"isoreset",	"ISO Reset",				builtin_isoreset},
	{"dumpvmu",	"Dump a VMU to a file",			builtin_dumpvmu},
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

/* print command list/desc */
void builtin_help(int argc, char *argv[]) {
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
	int dcnt, fcnt;

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

	dcnt = fcnt = 0;
	while ((ent = fs_readdir(hnd)) != NULL) {
		if (lflag)
			conio_printf("%12d bytes %s\n", ent->size, ent->name);
		else
			conio_printf("%s\n", ent->name);
		if (ent->size < 0)
			dcnt++;
		else
			fcnt++;
	}
	conio_printf("Total: %d files, %d dirs\n", fcnt, dcnt);

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
		for (i=0; i<(10 - cnt); i++)
			conio_printf("   ");
		conio_deadvance_cursor();
		//cursor.col = 10 * 3 + 2;
		conio_putch('|');
		for (i = 0; i < cnt; i++) {
			// if (isprint(buff[i]))
			if (buff[i] >= ' ' && buff[i] < 127)
				conio_putch(buff[i]);
			else
				conio_putch('.');
		}
		for (i=0; i<(10 - cnt); i++)
			conio_putch(' ');
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

/* create a directory */
void builtin_mkdir(int argc, char *argv[]) {
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
void builtin_rmdir(int argc, char *argv[]) {
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
void builtin_theme(int argc, char *argv[]) {
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
void builtin_menu(int argc, char *argv[]) {
	conio_printf("bye!\n");
	arch_menu();
}

/* Mount a romdisk image */
void builtin_mount_romdisk(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];
	void * data = NULL;
	uint64 t1, t2;
	
	if (argc != 3) {
		conio_printf("usage: mount_romdisk srcimg mountpoint\n");
		return;
	}

	/* get the abs path for the dir to create */
	makeabspath(fn, argv[1], MAX_FN_LEN);

	/* Load up the romdisk image */
	t1 = timer_ms_gettime64();
	conio_printf("Loading the romdisk image...\n");
	if (fs_load(fn, &data) <= 0) {
		conio_printf("error: invalid romdisk source image '%s'\n", fn);
		if (data != NULL)
			free(data);
		return;
	}
	t2 = timer_ms_gettime64();
	conio_printf("  (elapsed time = %d ms)\n",
		(uint32)(t2 - t1));

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

/* Execute a sub-program, replacing us */
void builtin_exec(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];
	void * data = NULL;
	int size;
	
	if (argc != 2) {
		conio_printf("usage: exec <binary name>\n");
		return;
	}

	/* get the abs path for the dir to create */
	makeabspath(fn, argv[1], MAX_FN_LEN);

	/* Load up the binary */
	if ( (size = fs_load(fn, &data)) <= 0) {
		conio_printf("error: can't load binary image '%s'\n", fn);
		if (data != NULL)
			free(data);
		return;
	}

	/* Execute it */
	conio_printf("Executing...\n");
	arch_exec(data, size);

	/* We failed for some reason */
	conio_printf("Exec failed.\n");
}

static const char * langs[] = {
	"Invalid",
	"Japanese",
	"English",
	"German",
	"French",
	"Spanish",
	"Italian"
};

void builtin_romcheck(int argc, char *argv[]) {
	uint8 * buffer;
	int start, size, i;
	flashrom_syscfg_t sc;
	
	conio_printf("\nReading flash rom...\n");
	if (flashrom_info(0, &start, &size) < 0) {
		conio_printf("Couldn't get the start/size of partition 0\n");
		return;
	}

	buffer = malloc(size);
	if (flashrom_read(start, buffer, size) < 0) {
		conio_printf("Couldn't read partition 0\n");
		free(buffer);
		return;
	}

	conio_printf("Your flash header: '");
	for (i=0; i<16; i++) {
		conio_printf("%c", buffer[i]);
	}
	conio_printf("'\nAgain in hex:\n");
	for (i=0; i<16; i++) {
		conio_printf("%02x ", buffer[i]);
	}

	if (!memcmp(buffer, "00000", 5)) {
		conio_printf("This appears to be a Japanese DC.\n");
	} else if (!memcmp(buffer, "00110", 5)) {
		conio_printf("This appears to be a USA DC.\n");
	} else if (!memcmp(buffer, "00211", 5)) {
		conio_printf("This appears to be a European DC.\n");
	} else {
		conio_printf("I don't know what the region of this DC is.\n");
	}

	free(buffer);

	if (flashrom_get_syscfg(&sc) < 0) {
		conio_printf("flashrom_get_syscfg failed\n");
		return;
	}

	i = sc.language;
	if (i > FLASHROM_LANG_ITALIAN)
		i = -1;
	conio_printf("Your selected language is %s.\n", langs[i+1]);

	i = sc.audio;
	conio_printf("Your audio is set to %s.\n",
		i ? "stereo" : "mono");

	i = sc.autostart;
	conio_printf("Your auto-start is set to %s.\n",
		i ? "on" : "off");
	
	conio_printf("\nDone.\n");
}

void builtin_periphs(int argc, char *argv[]) {
	int p, u;
	maple_device_t *dev;
	conio_printf("Attached maple peripheral info:\n");

	for (p=0; p<MAPLE_PORT_COUNT; p++) {
		for (u=0; u<MAPLE_UNIT_COUNT; u++) {
			dev = maple_enum_dev(p, u);
			if (dev) {
				conio_printf("%c%c: %s (%08lx: %s)\n",
					'A' + p, '0' + u,
					dev->info.product_name,
					dev->info.functions,
					maple_pcaps(dev->info.functions));
			}
		}
	}
}

/* dump memory as hex */
void builtin_md(int argc, char *argv[]) {
	uint8 *buff;
	uint32 addr;
	int cnt;
	
	if (argc != 3) {
		conio_printf("usage: md <address> <count>\n");
		return;
	}

	addr = strtoul(argv[1], NULL, 16);
	cnt = strtol(argv[2], NULL, 10);

	conio_printf("Address %08lx, len %d\n", addr, cnt);

	/* do the hexdump */
	while (cnt > 0) {
		int i, tc;

		tc = cnt > 10 ? 10 : cnt;
		buff = (uint8 *)addr;

		for (i = 0; i < tc; i++)
			conio_printf("%02x ", buff[i]);
		for (i=0; i<(10 - tc); i++)
			conio_printf("   ");
		conio_deadvance_cursor();
		//cursor.col = 10 * 3 + 2;
		conio_putch('|');
		for (i = 0; i < tc; i++) {
			// if (isprint(buff[i]))
			if (buff[i] >= ' ' && buff[i] < 127)
				conio_putch(buff[i]);
			else
				conio_putch('.');
		}
		for (i=0; i<(10 - tc); i++)
			conio_putch(' ');
		conio_printf("|\n");

		addr += tc;
		cnt -= tc;
	}
}

static void ogg_usage() {
	conio_printf("usage: ogg start <filename>\n"
	             "       ogg stop\n");
}
static int initted = 0;
void builtin_ogg(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];

	if (argc < 2) {
		ogg_usage();
		return;
	}

	if (!strcmp(argv[1], "start")) {
		if (!initted) {
			sndoggvorbis_init();
			initted = 1;
		}

		makeabspath(fn, argv[2], MAX_FN_LEN);
		sndoggvorbis_start(fn, 1);

		conio_printf("Started.\n");
	} else if (!strcmp(argv[1], "stop")) {
		if (initted) {
			sndoggvorbis_stop();
			conio_printf("Stopped.\n");
		}
	} else {
		conio_printf("Unknown command '%s'.\n", argv[1]);
	}
}

void builtin_isoreset(int argc, char *argv[]) {
	iso_reset();
}

void builtin_dumpvmu(int argc, char *argv[]) {
	char fn[MAX_FN_LEN];
	uint8 buffer[512];
	int port, unit, i;
	maple_device_t * dev;
	file_t f;

	if (argc < 3) {
		conio_printf("usage: dumpvmu <PU> <filename>\n");
		return;
	}

	port = argv[1][0] - 'A';
	unit = argv[1][1] - '0';
	dev = maple_enum_dev(port, unit);
	if (!dev || !(dev->info.functions & MAPLE_FUNC_MEMCARD)) {
		conio_printf("No device, or device not a VMU\n");
		return;
	}

	conio_printf("dumping...\n");
	makeabspath(fn, argv[2], MAX_FN_LEN);
	f = fs_open(fn, O_WRONLY | O_TRUNC);
	for (i=0; i<256; i++) {
		if (vmu_block_read(dev, i, buffer) < 0) {
			conio_printf("Failed to read block %d\n", i);
			fs_close(f);
			return;
		}

		fs_write(f, buffer, 512);
	}
	fs_close(f);
}
