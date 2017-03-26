#ifndef __DCLOAD_TYPES_H__
#define __DCLOAD_TYPES_H__

/* dcload dirent */

typedef struct {
  long            d_ino;  /* inode number */
  off_t           d_off;  /* offset to the next dirent */
  unsigned short  d_reclen;/* length of this record */
  unsigned char   d_type;         /* type of file */
  char            d_name[256];    /* filename */
} dcload_dirent_t;

/* dcload stat */

typedef struct { 
  unsigned short st_dev;
  unsigned short st_ino;
  int st_mode;
  unsigned short st_nlink;
  unsigned short st_uid;
  unsigned short st_gid;
  unsigned short st_rdev;
  long st_size;
  long st_atime_priv;
  long st_spare1;
  long st_mtime_priv;
  long st_spare2;
  long st_ctime_priv;
  long st_spare3;
  long st_blksize;
  long st_blocks;
  long st_spare4[2];
} dcload_stat_t;

#endif


