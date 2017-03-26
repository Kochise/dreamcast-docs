/*
 * Error codes are negative
 */
#define ERR_SYSERR   -1    /* Generic error from GDROM system       */
#define ERR_DIRERR   -2    /* Root directory not found              */
#define ERR_NOFILE   -3    /* File not found                        */
#define ERR_PARAM    -4    /* Invalid parameters passed to function */
#define ERR_NUMFILES -5    /* Max number of open files exceeded     */
#define ERR_NODISK   -6    /* No disc present                       */
#define ERR_DISKCHG  -7    /* Disc has been replaced with a new one */

/* 
 *  An open directory
 */
typedef struct {
  /* All members are private! */
  int     dd_fd;
  int     dd_loc;
  int     dd_size;
  char    *dd_buf;
} DIR;

#define MAX_OPEN_FILES 8

/*
 *  An entry in a directory
 */
typedef struct dirent {
  int      d_size;       /* size in bytes (-1 for directories) */
  char     d_name[256];  /* file name                          */
} dirent_t;

/*
 *  Flags for argument 2 to open
 */
#define O_RDONLY 0
#define O_DIR    1

/*
 *  Flags for argument 3 to lseek
 */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* Prototypes */
int open(const char *path, int oflag);
int close(int fd);
int pread(int fd, void *buf, unsigned int nbyte, unsigned int offset);
int read(int fd, void *buf, unsigned int nbyte);
long int lseek(int fd, long int offset, int whence);
DIR *opendir(const char *dirname);
int closedir(DIR *dirp);
int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **res);
struct dirent *readdir(DIR *dirp);
void cdfs_init(void);
