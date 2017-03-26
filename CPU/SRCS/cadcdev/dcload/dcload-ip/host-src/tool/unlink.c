#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#ifndef S_ISLNK
#ifdef S_IFLNK
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#else
#define S_ISLNK(m) 0
#define lstat stat
#endif
#endif

int
unlink_if_ordinary (const char *name)
{
  struct stat st;

  if (lstat (name, &st) == 0
      && (S_ISREG (st.st_mode) || S_ISLNK (st.st_mode)))
    return unlink (name);

  return 1;
}
