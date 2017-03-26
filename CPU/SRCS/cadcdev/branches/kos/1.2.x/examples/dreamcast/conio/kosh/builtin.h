/*
 * builtin.h - shell builtins
 *
 * (C) 2000 Jordan DeLong
 */
#ifndef _KOSH_BUILTIN_H
#define _KOSH_BUILTIN_H

/* the func */
int builtin_command(int argc, char *argv[]);

/* builtin command handlers */
void builtin_help(int argc, char *argv[]);
void builtin_exit(int argc, char *argv[]);
void builtin_ls(int argc, char *argv[]);
void builtin_cd(int argc, char *argv[]);
void builtin_pwd(int argc, char *argv[]);
void builtin_clear(int argc, char *argv[]);
void builtin_echo(int argc, char *argv[]);
void builtin_cat(int argc, char *argv[]);
void builtin_hd(int argc, char *argv[]);
void builtin_md(int argc, char *argv[]);
void builtin_cp(int argc, char *argv[]);
void builtin_rm(int argc, char *argv[]);
void builtin_mkdir(int argc, char *argv[]);
void builtin_rmdir(int argc, char *argv[]);
void builtin_theme(int argc, char *argv[]);
void builtin_menu(int argc, char *argv[]);
void builtin_mount_romdisk(int argc, char *argv[]);
void builtin_exec(int argc, char *argv[]);
void builtin_romcheck(int argc, char *argv[]);
void builtin_periphs(int argc, char *argv[]);
void builtin_ogg(int argc, char *argv[]);
void builtin_isoreset(int argc, char *argv[]);
void builtin_dumpvmu(int argc, char *argv[]);

#endif
		

