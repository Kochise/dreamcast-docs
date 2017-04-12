/*
 * input.c
 *
 * (C) 2000 Jordan DeLong
 */
#include <kos/limits.h>
#include <string.h>
#include <ctype.h>
#include "kosh.h"
#include "conio.h"
#include "input.h"
#include "chdir.h"

/* the buffer for input */
static struct {
	char text[INPUT_BUFFSIZE];
	int pos;	/* pos in the buffer, not the screen */
} input_buffer;

/* the state var */
enum {
	INPUT_PROMPT,		/* print the prompt, etc */
	INPUT_READCOMM,		/* read and edit a command line */
	INPUT_COMMAND		/* call a command based on input_buffer.text */
} input_state = INPUT_PROMPT;

/* add text to the input buff and putch it */
static void input_insertbuff(int ch) {
	int len;

	len = strlen(input_buffer.text);

	if (len >= INPUT_BUFFSIZE - 1)
		return;

	/* our str */
	memmove(&input_buffer.text[input_buffer.pos + 1], &input_buffer.text[input_buffer.pos], 
		len - input_buffer.pos + 1);
	/* the virtscr */
	if (cursor.row * NUM_COLS + cursor.col + len - input_buffer.pos + 1 
			>= NUM_COLS * NUM_ROWS)
		conio_scroll();
	memmove(&virtscr[cursor.row][cursor.col + 1], &virtscr[cursor.row][cursor.col], 
		len - input_buffer.pos + 1);
	input_buffer.text[input_buffer.pos] = ch;
	input_buffer.pos++;

	conio_putch(ch);

	return;
}

/* remove the char at input_buffer.pos from the buffer, and reflect the changes on the virtscr */
static void input_delchar_buff() {
	int len;

	len = strlen(input_buffer.text);

	if (len < 1)
		return;

	/* our str */
	memmove(&input_buffer.text[input_buffer.pos], &input_buffer.text[input_buffer.pos + 1], 
		len - input_buffer.pos + 1);
	input_buffer.text[len] = '\0';
	/* the virtscr */
	memmove(&virtscr[cursor.row][cursor.col], &virtscr[cursor.row][cursor.col + 1], 
		len - input_buffer.pos + 1);
}

/* print the prompt out, clear input buffer */
static void input_prompt() {
	input_buffer.pos = 0;
	*input_buffer.text = '\0';
	conio_putstr("$ ");
	input_state = INPUT_READCOMM;
}

/* reading commands from the prompt */
static void input_readcomm() {
	int key;

	key = kbd_get_key();

	switch (key) {
		case -1:
			return;
		case KBD_KEY_DEL << 8:
			input_delchar_buff();
			break;
		case 8:		/* backspace */
			if (input_buffer.pos > 0) {
				conio_deadvance_cursor();
				input_buffer.pos--;
				input_delchar_buff();
			}
			break;
		case '\r':
			input_state = INPUT_COMMAND;
			conio_putch('\n');
			break;
		case KBD_KEY_LEFT << 8:	/* left */
			if (input_buffer.pos > 0) {
				input_buffer.pos--;
				conio_deadvance_cursor();
			}
			break;
		case KBD_KEY_RIGHT << 8:
			if (input_buffer.pos < strlen(input_buffer.text)) {
				input_buffer.pos++;
				conio_advance_cursor();
			}
			break;
		case KBD_KEY_HOME << 8:
			for (; input_buffer.pos > 0; input_buffer.pos--)
				conio_deadvance_cursor();
			break;
		case KBD_KEY_END << 8:
			for (; input_buffer.pos < strlen(input_buffer.text); input_buffer.pos++)
				conio_advance_cursor();
			break;
		default:
			if (isascii(key))
				input_insertbuff(key);
	}
}

/* read command line, try to execute builtin commands, otherwise externals (this coming soon) */
static void input_command() {
	int argc;
	char *argv[20];		/* limit to 20 args (should be plenty) */
	char *str;
	char buff[MAX_FN_LEN];


	str = input_buffer.text;

	input_state = INPUT_PROMPT;

	/* we don't care if the user just hit enter */
	if (input_buffer.text[0] == '\0')
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
		makeabspath(buff, argv[0], MAX_FN_LEN);

		/* the builtin failed so we try an external */
		/* if (process->load_and_exec(buff, argc, argv))
			conio_printf("kosh: %s: command not found\n", buff); */
		conio_printf("Sorry, OS mode not available yet\n");
	}
}

/* our exported input function, called once per frame. */
void input_frame() {
	switch (input_state) {
		case INPUT_PROMPT:	input_prompt();		break;
		case INPUT_READCOMM:	input_readcomm();	break;
		case INPUT_COMMAND:	input_command();	break;
	}
}


