#ifndef __JITTERDEFS_H__
#define __JITTERDEFS_H__

#define LARGE_NUMBER 1024
#define JITTER_TABLE_SIZE 1024
#define JITTER_MASK (JITTER_TABLE_SIZE-1)

extern int ijitter[];
extern float ujitter[];
extern float vjitter[];

#endif
