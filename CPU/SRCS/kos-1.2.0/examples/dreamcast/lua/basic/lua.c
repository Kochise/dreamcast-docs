/*
** $Id: lua.c,v 1.2 2002/06/30 06:33:38 bardtx Exp $
** Lua stand-alone interpreter
** See Copyright Notice in lua.h
*/

/* Ported to KOS conio by Dan Potter */

#include <kos.h>
#include <conio/conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #include "lua.h"

#include "luadebug.h"
#include "lualib.h" */
#include <lua/lua.h>


static lua_State *L = NULL;


#ifndef PROMPT
#define PROMPT		"> "
#endif

static void laction (int i);


static lua_Hook old_linehook = NULL;
static lua_Hook old_callhook = NULL;

int errno = 0;
int _impure_ptr = 0;

static void userinit (void) {
  lua_baselibopen(L);
  lua_iolibopen(L);
  lua_strlibopen(L);
  lua_mathlibopen(L);
  lua_dblibopen(L);
  /* add your libraries here */
}

static int ldo (int (*f)(lua_State *l, const char *), const char *name) {
  int res;
  int top = lua_gettop(L);
  res = f(L, name);  /* dostring | dofile */
  lua_settop(L, top);  /* remove eventual results */
  /* Lua gives no message in such cases, so lua.c provides one */
  if (res == LUA_ERRMEM) {
    conio_printf("lua: memory allocation error\n");
  }
  else if (res == LUA_ERRERR)
    conio_printf("lua: error in error message\n");
  return res;
}


static void print_version (void) {
  conio_printf("%.80s  %.80s\n", LUA_VERSION, LUA_COPYRIGHT);
}


static void assign (char *arg) {
  char *eq = strchr(arg, '=');
  *eq = '\0';  /* spilt `arg' in two strings (name & value) */
  lua_pushstring(L, eq+1);
  lua_setglobal(L, arg);
}


static void getargs (char *argv[]) {
  int i;
  lua_newtable(L);
  for (i=0; argv[i]; i++) {
    /* arg[i] = argv[i] */
    lua_pushnumber(L, i);
    lua_pushstring(L, argv[i]);
    lua_settable(L, -3);
  }
  /* arg.n = maximum index in table `arg' */
  lua_pushstring(L, "n");
  lua_pushnumber(L, i-1);
  lua_settable(L, -3);
}


static int l_getargs (lua_State *l) {
  char **argv = (char **)lua_touserdata(l, -1);
  getargs(argv);
  return 1;
}


/* maximum length of an input string */
#ifndef MAXINPUT
#define MAXINPUT	BUFSIZ
#endif

static void manual_input (int version, int prompt) {
  int cont = 1;
  if (version) print_version();
  while (cont) {
    char buffer[MAXINPUT];
    int i = 0;
    if (prompt) {
      const char *s;
      lua_getglobal(L, "_PROMPT");
      s = lua_tostring(L, -1);
      if (!s) s = PROMPT;
      conio_printf(s);
      lua_pop(L, 1);  /* remove global */
    }
    conio_input_getline(1, buffer, MAXINPUT);
    if (strlen(buffer)) {
    	ldo(lua_dostring, buffer);
    	lua_settop(L, 0);  /* remove eventual results */
    }
  }
  conio_printf("\n");
}

#if 0
static int handle_argv (char *argv[], struct Options *opt) {
  if (opt->stacksize > 0) argv++;  /* skip option `-s' (if present) */
  if (*argv == NULL) {  /* no more arguments? */
    if (isatty(0)) {
      manual_input(1, 1);
    }
    else
      ldo(lua_dofile, NULL);  /* executes stdin as a file */
  }
  else {  /* other arguments; loop over them */
    int i;
    for (i = 0; argv[i] != NULL; i++) {
      if (argv[i][0] != '-') {  /* not an option? */
        if (strchr(argv[i], '='))
          assign(argv[i]);
        else
          if (file_input(argv[i]) != EXIT_SUCCESS)
            return EXIT_FAILURE;  /* stop if file fails */
        }
        else switch (argv[i][1]) {  /* option */
          case 0: {
            ldo(lua_dofile, NULL);  /* executes stdin as a file */
            break;
          }
          case 'i': {
            manual_input(0, 1);
            break;
          }
          case 'q': {
            manual_input(0, 0);
            break;
          }
          case 'c': {
            opt->toclose = 1;
            break;
          }
          case 'v': {
            print_version();
            break;
          }
          case 'e': {
            i++;
            if (argv[i] == NULL) {
              print_message();
              return EXIT_FAILURE;
            }
            if (ldo(lua_dostring, argv[i]) != 0) {
              fprintf(stderr, "lua: error running argument `%.99s'\n", argv[i]);
              return EXIT_FAILURE;
            }
            break;
          }
          case 'f': {
            i++;
            if (argv[i] == NULL) {
              print_message();
              return EXIT_FAILURE;
            }
            getargs(argv+i);  /* collect remaining arguments */
            lua_setglobal(L, "arg");
            return file_input(argv[i]);  /* stop scanning arguments */
          }
          case 's': {
            fprintf(stderr, "lua: stack size (`-s') must be the first option\n");
            return EXIT_FAILURE;
          }
          default: {
            print_message();
            return EXIT_FAILURE;
          }
        }
    }
  }
  return EXIT_SUCCESS;
}
#endif

static void register_getargs (char *argv[]) {
  lua_pushuserdata(L, argv);
  lua_pushcclosure(L, l_getargs, 1);
  lua_setglobal(L, "getargs");
}


int main (int argc, char *argv[]) {
  int status;

  cont_btn_callback(0, CONT_START, (cont_btn_callback_t)arch_exit);
  pvr_init_defaults();
  conio_init(CONIO_TTY_PVR, CONIO_INPUT_LINE);

  luaB_set_fputs((void (*)(const char *))conio_printf);
  
  L = lua_open(0);  /* create state */
  if (L == NULL) {
    printf("Invalid state.. giving up\n");
    return -1;
  }
  userinit();  /* open libraries */
  register_getargs(argv);  /* create `getargs' function */
  manual_input(1, 1);
  /* status = handle_argv(argv+1, &opt); */
  lua_close(L);
  return status;
}

