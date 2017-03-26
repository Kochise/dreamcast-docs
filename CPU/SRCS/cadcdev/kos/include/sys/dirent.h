#ifndef __SYS_DIRENT_H
#define __SYS_DIRENT_H

#include <unistd.h>
#include <arch/types.h>
#include <kos/fs.h>

struct dirent {
	int	d_ino;
	off_t	d_off;
	uint16	d_reclen;
	uint8	d_type;
	char	d_name[256];
};

// In KOS, DIR* is just an fd. We'll use a real struct here anyway so we
// can store the POSIX dirent.
typedef struct {
	file_t		fd;
	struct dirent	d_ent;
} DIR;

// Standard UNIX dir functions. Not all of these are fully functional
// right now due to lack of support in KOS.

// All of these work.
DIR *opendir(const char *name);
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir);

// None of these work.
void rewinddir(DIR *dir);
int scandir(const char *dir, struct dirent ***namelist,
	int(*filter)(const struct dirent *),
	int(*compar)(const struct dirent **, const struct dirent **));
void seekdir(DIR *dir, off_t offset);
off_t telldir(DIR *dir);

#endif
                                
