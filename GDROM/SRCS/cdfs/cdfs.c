#include "cdfs.h"

#ifndef NULL
#define NULL ((void*)0)
#endif


/*
 * Disc TOC (up to 99 tracks)
 */
struct TOC {
  unsigned int entry[99];
  unsigned int first, last;
  unsigned int dunno;
};


/*
 * TOC access macros
 */
/* Split TOC->entry into its components */
#define TOC_LBA(n) ((n)&0x00ffffff)
#define TOC_ADR(n) (((n)&0x0f000000)>>24)
#define TOC_CTRL(n) (((n)&0xf0000000)>>28)
/* Use TOC_TRACK() to convert TOC->first and TOC->last entry to track # */
#define TOC_TRACK(n) (((n)&0x00ff0000)>>16)


/* Static buffers.  These make most of the functions
 * non-reentrant.                                     */
static unsigned int sector_buffer[2048/4];
static unsigned int dir_buffer[2048/4];


/*
 * libc like support
 */

static int memcmp(const void *p1, const void *p2, unsigned int size)
{
  const unsigned char *m1 = p1, *m2 = p2;
  while(size--)
    if(*m1++ != *m2++)
      return m2[-1]-m1[-1];
  return 0;
}

static void *memcpy(void *p1, const void *p2, unsigned int size)
{
  unsigned char *m1 = p1;
  const unsigned char *m2 = p2;
  while(size--)
    *m1++ = *m2++;
  return p1;
}

static char *strchr0(const char *s, int c)
{
  while(*s!=c)
    if(!*s++)
      return NULL;
  return (char *)s;
}



/*
 * GDROM system access
 */

static int exec_cmd(int cmd, void *param)
{
  int status[4];
  int f, n;

  /* Submit the command to the system */
  f = gdGdcReqCmd(cmd, param);

  /* Wait for the command to complete */
  do gdGdcExecServer(); while((n = gdGdcGetCmdStat(f, status))==1);

  /* If command completed normally, return 0 */
  if(n == 2)
    return 0;

  /* Detect conditions that have special error codes */
  else switch(status[0]) {
   case 2:
     return ERR_NODISK;
   case 6:
     return ERR_DISKCHG;
   default:
     return ERR_SYSERR;
  }
}

static int init_drive()
{
  int i, r;
  unsigned int param[4];
  int cdxa;

  /*
   * Retry the init disc command a few times if it fails,
   * for example if the disc has been changed
   */
  for(i=0; i<8; i++)
    if(!(r = exec_cmd(24, NULL)))
      break;

  /* If it failed all times, give up */
  if(r)
    return r;

  /* Check type of disc */
  gdGdcGetDrvStat(param);

  /* CD/XA? */
  cdxa = (param[1] == 32);

  /* Select disc access mode */
  param[0] = 0;                   /* 0 = set, 1 = get */
  param[1] = 8192;                /* ?                */
  param[2] = (cdxa? 2048 : 1024); /* mode 1/2         */
  param[3] = 2048;                /* sector size      */
  if(gdGdcChangeDataType(param)<0)
    return ERR_SYSERR;

  /* All done */
  return 0;
}

static int read_toc(struct TOC *toc, int session)
{
  struct { int session; void *buffer; } param;
  param.session = session;
  param.buffer = toc;
  return exec_cmd(19, &param);
}

static int read_sectors(char *buf, int sec, int num)
{
  struct { int sec, num; void *buffer; int dunno; } param;
  int i;
  param.sec = sec;    /* Starting sector number */
  param.num = num;    /* Number of sectors      */
  param.buffer = buf; /* Pointer to buffer      */
  param.dunno = 0;
  return exec_cmd(16, &param);
}


/*
 * ISO9660 support functions
 */

static int ntohlp(unsigned char *ptr)
{
  /* Convert the long word pointed to by ptr from big endian */
  return (ptr[0]<<24)|(ptr[1]<<16)|(ptr[2]<<8)|ptr[3];
}

static int fncompare(const char *fn1, int fn1len, const char *fn2, int fn2len)
{
  /* Compare two filenames, disregarding verion number on fn2 if neccessary */
  while(fn2len--)
    if(!fn1len--)
      return *fn2 == ';';
    else if(*fn1++ != *fn2++)
      return 0;
  return fn1len == 0;
}


/* 
 * Low file I/O
 */


static unsigned int find_datatrack(struct TOC *toc)
{
  /* Find the last track which has a ctrl of 4.
     This method should work with multisession discs. */
  int i, first, last;
  first = TOC_TRACK(toc->first);
  last = TOC_TRACK(toc->last);
  if(first < 1 || last > 99 || first > last)
    return 0;
  for(i=last; i>=first; --i)
    if(TOC_CTRL(toc->entry[i-1])==4)
      return TOC_LBA(toc->entry[i-1]);
  return 0;
}

static int find_root(unsigned int *psec, unsigned int *plen)
{
  /* Find location and length of root directory.
     Plain ISO9660 only.                         */

  static struct TOC toc;
  int r;
  unsigned int sec;

  if((r=init_drive())!=0)
    return r;
  if((r=read_toc(&toc, 0))!=0)
    return r;
  if(!(sec = find_datatrack(&toc)))
    return ERR_DIRERR;
  if((r=read_sectors((char *)sector_buffer, sec+16, 1))!=0)
    return r;
  if(memcmp((char *)sector_buffer, "\001CD001", 6))
    return ERR_DIRERR;

  /* Need to add 150 to LBA to get physical sector number */
  *psec = ntohlp(((char *)sector_buffer)+156+6) + 150;
  *plen = ntohlp(((char *)sector_buffer)+156+14);

  return 0;
}

static int low_find(unsigned int sec, unsigned int dirlen, int isdir,
		    unsigned int *psec, unsigned int *plen,
		    const char *fname, int fnlen)
{
  /* Find a named entry in a directory */

  /* sec and dirlen points out the extent of the directory */

  /* psec and plen points to variables that will receive the extent
     of the file if found                                           */

  isdir = (isdir? 2 : 0);
  while(dirlen>0) {
    int r, i;
    unsigned char *rec = (unsigned char *)sector_buffer;
    if((r=read_sectors((char *)sector_buffer, sec, 1))!=0)
      return r;
    for(i=0; i<2048 && i<dirlen && rec[0] != 0; i += rec[0], rec += rec[0]) {
      if((rec[25]&2) == isdir && fncompare(fname, fnlen, rec+33, rec[32])) {
	/* Entry found.  Copy start sector and length.  Add 150 to LBA. */
	*psec = ntohlp(rec+6)+150;
	*plen = ntohlp(rec+14);
	return 0;
      }
    }
    /* Not found, proceed to next sector */
    sec++;
    dirlen -= (dirlen>2048? 2048 : dirlen);
  }
  /* End of directory.  Entry not found. */
  return ERR_NOFILE;
}


/* File I/O */


/* A file handle. */
static struct {
  unsigned int sec0;  /* First sector                     */
  unsigned int loc;   /* Current read position (in bytes) */
  unsigned int len;   /* Length of file (in bytes)        */
} fh[MAX_OPEN_FILES];

int open(const char *path, int oflag)
{
  int fd, r;
  unsigned int sec, len;
  char *p;

  /* Find a free file handle */
  for(fd=0; fd<MAX_OPEN_FILES; fd++)
    if(fh[fd].sec0 == 0)
      break;
  if(fd>=MAX_OPEN_FILES)
    return ERR_NUMFILES;

  /* Find the root directory */
  if((r=find_root(&sec, &len)))
    return r;

  /* If the file we want is in a subdirectory, first locate
     this subdirectory                                      */
  while((p = strchr0(path, '/'))) {
    if(p != path)
      if((r = low_find(sec, len, 1, &sec, &len, path, p-path)))
	return r;
    path = p+1;
  }

  /* Locate the file in the resulting directory */
  if(*path)
    if((r = low_find(sec, len, oflag&O_DIR, &sec, &len, path,
		     strchr0(path, '\0')-path)))
      return r;
    else ;
  else
    /* If the path ends with a slash, check that it's really
       the dir that is wanted                                */
    if(!(oflag&O_DIR))
      return ERR_NOFILE;

  /* Fill in the file handle and return the fd */
  fh[fd].sec0 = sec;
  fh[fd].loc = 0;
  fh[fd].len = len;
  return fd;
}

int close(int fd)
{
  /* Check that the fd is valid */
  if(fd<0 || fd>=MAX_OPEN_FILES)
    return ERR_PARAM;

  /* Zeroing the sector number marks the handle as unused */
  fh[fd].sec0 = 0;
  return 0;
}

int pread(int fd, void *buf, unsigned int nbyte, unsigned int offset)
{
  int r, t;

  /* Check that the fd is valid */
  if(fd<0 || fd>=MAX_OPEN_FILES || fh[fd].sec0==0)
    return ERR_PARAM;

  /* If the read position is beyond the end of the file,
     return an empty read                                */
  if(offset>=fh[fd].len)
    return 0;

  /* If the full read would span beyond the EOF, shorten the read */
  if(offset+nbyte > fh[fd].len)
    nbyte = fh[fd].len - offset;

  /* Read whole sectors directly into buf if possible */
  if(nbyte>=2048 && !(offset & 2047))
    if((r = read_sectors(buf, fh[fd].sec0 + (offset>>11), nbyte>>11)))
      return r;
    else {
      t = nbyte & ~2047;;
      buf = ((char *)buf) + t;
      offset += t;
      nbyte &= 2047;
    }
  else
    t = 0;

  /* If all data has now been read, return */
  if(!nbyte)
    return t;

  /* Need to read parts of sectors */
  if((offset & 2047)+nbyte > 2048) {
    /* If more than one sector is involved, split the read
       up and recurse                                      */
    if((r = pread(fd, buf, 2048-(offset & 2047), offset))<0)
      return r;
    else {
      t += r;
      buf = ((char *)buf) + r;
      offset += r;
      nbyte -= r;
    }
    if((r = pread(fd, buf, nbyte, offset))<0)
      return r;
    else
      t += r;
  } else {
    /* Just one sector.  Read it and copy the relevant part. */
    if((r = read_sectors((char *)sector_buffer, fh[fd].sec0+(offset>>11), 1)))
      return r;
    memcpy(buf, ((char *)sector_buffer)+(offset&2047), nbyte);
    t += nbyte;
  }
  return t;
}

int read(int fd, void *buf, unsigned int nbyte)
{
  /* Check that the fd is valid */
  if(fd<0 || fd>=MAX_OPEN_FILES || fh[fd].sec0==0)
    return ERR_PARAM;
  else {
    /* Use pread to read at the current position */
    int r = pread(fd, buf, nbyte, fh[fd].loc);
    /* Update current position */
    if(r>0)
      fh[fd].loc += r;
    return r;
  };
}

long int lseek(int fd, long int offset, int whence)
{
  /* Check that the fd is valid */
  if(fd<0 || fd>=MAX_OPEN_FILES || fh[fd].sec0==0)
    return ERR_PARAM;

  /* Update current position according to arguments */
  switch(whence) {
   case SEEK_SET:
     return fh[fd].loc = offset;
   case SEEK_CUR:
     return fh[fd].loc += offset;
   case SEEK_END:
     return fh[fd].loc = fh[fd].len + offset;
   default:
     return ERR_PARAM;
  }
}


/* Dir I/O */


/* More static buffers.
   Only one directory may be read at the same time... */
static DIR g_dir;
static struct dirent g_dirent;

DIR *opendir(const char *dirname)
{
  /* Try to open a handle for the directory */
  if((g_dir.dd_fd = open(dirname, O_DIR|O_RDONLY)))
    return NULL;

  /* Fill out the rest of the struct */
  g_dir.dd_loc = 0;
  g_dir.dd_size = 0;
  g_dir.dd_buf = (char *)dir_buffer;
  return &g_dir;
}

int closedir(DIR *dirp)
{
  /* Unallocate the dir filehandle */
  return close(dirp->dd_fd);
}

int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **res)
{
  int l, r=0;
  unsigned char *rec;

  /* Check that the DIR* is valid */
  if(dirp == NULL || dirp->dd_fd<0)
    r = ERR_PARAM;
  else {
    do {
      while(dirp->dd_loc >= dirp->dd_size ||
	    (l=dirp->dd_buf[dirp->dd_loc]) == 0 ||
	    dirp->dd_loc + l > dirp->dd_size) {
	/* Need to read more dir data */
	if((r = read(dirp->dd_fd, dirp->dd_buf, 2048))<=0) {
	  /* Read error or EOF on directory */
	  *res = NULL;
	  return (r? r : ERR_NOFILE);
	}
	/* Reset buffer read pointer */
	dirp->dd_loc = 0;
	dirp->dd_size = r;
	r = 0;
      }

      /* Found nonzero-length entry in buffer */
      rec = dirp->dd_buf+dirp->dd_loc;

      /* Move read pointer past it */
      dirp->dd_loc += l;

      /* Copy entry name to dirent */
      memcpy(entry->d_name, rec+33, rec[32]);
      entry->d_name[rec[32]] = '\0';

      /* Copy size (set to -1 for directory) */
      entry->d_size = ((rec[25]&2)? -1 : ntohlp(rec+14));

      /* Strip trailing version number from name, if present */
      if((rec = strchr0(entry->d_name, ';')))
	*rec = '\0';

      /* Keep going until we find an entry that is not the current
	 or the parent directory (see ECMA-119)                    */
    } while(entry->d_name[0]==0 || entry->d_name[0]==1);
  }

  /* Return result */
  if(r) {
    *res = NULL;
    return r;
  } else {
    *res = entry;
    return 0;
  }
}

struct dirent *readdir(DIR *dirp)
{
  struct dirent *res;
  /* Same as readdir_r, but uses static buffer */
  readdir_r(dirp, &g_dirent, &res);
  return res;
}


/* Init function */


void cdfs_init()
{
  register unsigned long p, x;

  /* Reactivate GD-ROM drive */

  *((volatile unsigned long *)0xa05f74e4) = 0x1fffff;
  for(p=0; p<0x200000/4; p++)
    x = ((volatile unsigned long *)0xa0000000)[p];

  /* Reset GD system functions */

  gdGdcInitSystem();
}
