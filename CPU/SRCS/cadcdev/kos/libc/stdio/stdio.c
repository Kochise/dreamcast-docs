/* KallistiOS ##version##

   stdio.c
   (c)2000-2001 Tobias Gloth

*/

#include <kos/fs.h>

CVSID("$Id: stdio.c,v 1.6 2003/06/19 04:31:26 bardtx Exp $");

#define MAX_FILE 16

typedef struct _FILE_t {
	file_t file;
	uint8 used;
	uint8 owner;
	uint8 error;
	uint8 eof;
	uint8 putback;
	uint8 has_putback;
} _FILE_t;

#include <stdio.h>
#include <string.h>
#include <arch/spinlock.h>

static FILE f[MAX_FILE];
static int f_used = 0;

/* Thread mutex */
static spinlock_t mutex;

#define VALID_FILE(X) (((X) >= &f[0]) && ((X) < &f[MAX_FILE]) && ((X)->used))

static FILE *alloc_file() {
	FILE *result = 0;
	spinlock_lock(&mutex);
	if (f_used <= MAX_FILE) {
		int i;
		for (i=0; i<MAX_FILE; i++) {
			if (!f[i].used) {
				f[i].file = 0;
				f[i].used = 1;
				f[i].owner = 1;
				f[i].eof = 0;
				f[i].error = 0;
				f[i].putback = 0;
				f[i].has_putback = 0;
				result = f+i;
				f_used++;
				break;
			}
		}
	}
	spinlock_unlock(&mutex);
	return result;
}

static void release_file(FILE *file) {
	spinlock_lock(&mutex);
	if (VALID_FILE(file)) {
		file->used = 0;
		f_used--;
	}
	spinlock_unlock(&mutex);
}

static int convert_mode(const char *mode) {

	/* try to parse it corrrectly */
	int mode_r = 0, mode_a = 0, mode_w = 0, mode_b = 0, mode_p = 0;

	if (mode == (char *)0) {
		return -1;
	}
	if (*mode == 'r') {
		mode_r=1;
	} else if (*mode == 'w') {
		mode_w=1;
	} else if (*mode == 'a') {
		mode_w=1;
	} else {
		return -1;
	}
	mode++;
	if (*mode == 'b') {
		mode_b = 1;
		mode++;
	}
	if (*mode == '+') {
		mode_p = 1;
		mode++;
	}
	if ((*mode == 'b') && (mode_b == 0)) {
		mode_b = 1;
		mode++;
	} else if (*mode != '\0') {
		return -1;
	}

	if (mode_r && !mode_p) {
		return O_RDONLY;
	} else if (mode_r && mode_p) {
		return O_RDWR;
	} else if (mode_w && !mode_p) {
		return O_WRONLY | O_TRUNC;
	} else if (mode_w && mode_p) {
		return O_RDWR | O_TRUNC;
	} else if (mode_a && !mode_p) {
		return O_APPEND;
	} else if (mode_a && mode_p) {
		return O_APPEND;
	}

	return -1;
}

FILE *fopen(const char *path, const char *mode) {

	file_t file;
	int fsMode;
	FILE *result;

	fsMode = convert_mode (mode);
	if (fsMode == -1) {
		return (FILE *)0;
	}
	result = alloc_file();
	if (!result) {
		return (FILE *)0;
	}

	file = fs_open (path, fsMode);
	if (file < 0) {
		release_file(result);
		return (FILE *)0;
	}

	result->file = file;

	return result;
}

FILE *fdopen(int file, const char *mode) {

	FILE *result;

	if (file < 0) {
		return (FILE *)0;
	}
	result = alloc_file();
	if (!result) {
		return (FILE *)0;
	}

	result->file = file;
	result->owner = 1;

	return result;
}

FILE *freopen(const  char *path, const char *mode, FILE *file) {

	int fsMode;

	if (VALID_FILE(file)) {
		if (file->owner) {
			fs_close(file->file);
		}
	}

	fsMode = convert_mode (mode);
	if (fsMode == -1) {
		if (VALID_FILE(file)) {
			release_file(file);
		}
		return (FILE *)0;
	}

	if (!VALID_FILE(file)) {
		file = alloc_file();
	}
	if (!VALID_FILE(file)) {
		return (FILE *)0;
	}

	file->file = fs_open (path, fsMode);
	if (file->file == 0) {
		release_file(file);
		return (FILE *)0;
	}

	file->owner = 1;
	file->eof = 0;
	file->error = 0;
	return file;
}

int fclose(FILE *file) {
	if (!VALID_FILE(file)) {
		return EOF;
	}
	if (file->owner) {
		fs_close(file->file);
	}
	release_file (file);
	return 0;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *file) {
	size_t result = 0, to_read = size * nmemb;
	if (!VALID_FILE(file) || (to_read == 0)) {
		return 0;
	}
	if (file->has_putback) {
		unsigned char *tmp = (unsigned char *)ptr;
		*tmp = file->putback;
		ptr = tmp+1;
		file->has_putback = 0;
		result++;
		to_read--;
	}
	result += fs_read(file->file, ptr, to_read);
	result = result / size;
	if (result < 0) {
		file->error = 1;
		return 0;
	}
	if (result < nmemb) {
		file->eof = 1;
	}
	return result;
}

int fgetc(FILE *file) {
	unsigned char ch;
	if (!fread(&ch, 1, 1, file)) {
		return EOF;
	}
	return (int)ch;
}

int getc(FILE * file) {
	return fgetc(file);
}

int ungetc(int c, FILE *file) {
	if (!VALID_FILE(file) || (file->has_putback) ||
		(fs_tell(file->file) <= 0)) {
		return EOF;
	}
	file->putback = c;
	file->has_putback = 1;
	return c;
}

char *fgets(char *s, int size, FILE *file) {

	int i, ch;

	if (!VALID_FILE(file) || !s) {
		return (char *)0;
	}
	for (i=0; i<size-1; i++) {
		ch = s[i] = fgetc (file);
		if (ch == EOF) {
			break;
		}
		if (ch == '\n') {
			i++;
			break;
		}
	}
	s[i] = '\0';
	return (i == 0) ? (char *)0 : s;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *file) {
	if (!VALID_FILE(file)) {
		return 0;
	}
	if (file->has_putback) {
		fs_seek(file->file, -1, SEEK_CUR);
		file->has_putback = 0;
	}
	return fs_write(file->file, ptr, size*nmemb)/size;
}

int fputc(int ch, FILE *file) {
	unsigned char c = (unsigned char)ch;
	if (!fwrite(&c, 1, 1, file)) {
		return EOF;
	}
	return ch;
}

int puts(const char *str) {
	size_t size = str ? strlen(str) : 0;
	size_t written = printf ("%s\n", str);
	return (written == size+1) ? 0 : EOF;
}

int fputs(const char *s, FILE *file) {

	int len;

	if (!VALID_FILE(file) || !s) {
		return -1;
	}
	len = strlen(s);
	if (fs_write(file->file, s, len) != len) {
		return -1;
	}
	return 0;
}

int fflush(FILE *file) {
	if (!VALID_FILE(file)) {
		return -1;
	}
	/* I think everything is flushed anyway */
	return 0;
}

int fseek(FILE *file, long offset, int whence) {
	if (!VALID_FILE(file)) {
		return -1;
	}
	file->has_putback = 0;
	return fs_seek(file->file, offset, whence) == -1 ? -1 : 0;
}

long ftell(FILE *file) {
	if (!VALID_FILE(file)) {
		return -1;
	}
	return (long)fs_tell(file->file) - (file->has_putback ? 1 : 0);
}

void rewind(FILE *file) {
	fseek(file, 0, SEEK_SET);
}

int fgetpos(FILE *file, fpos_t *pos) {
	if (!pos || !VALID_FILE(file)) {
		return -1;
	}
	*pos = fs_tell(file->file) - (file->has_putback ? 1 : 0);
	return (*pos == -1) ? -1 : 0;
}

int fsetpos(FILE *file, const fpos_t *pos) {
	if (!pos || !VALID_FILE(file)) {
		return -1;
	}
	file->has_putback = 0;
	return fs_seek(file->file, *pos, SEEK_SET) == -1 ? -1 : 0;
}

void clearerr(FILE *file) {
	if (!VALID_FILE(file)) {
		return;
	}
	file->error = 0;
	file->eof = 0;
}

int ferror(FILE *file) {
	if (!VALID_FILE(file)) {
		return -1;
	}
	return (int)file->error;
}

int feof(FILE *file) {
	if (!VALID_FILE(file)) {
		return -1;
	}
	return (int)file->eof;
}

int fileno(FILE *file) {
	if (!VALID_FILE(file)) {
		return 0;
	}
	return file->file;
}

