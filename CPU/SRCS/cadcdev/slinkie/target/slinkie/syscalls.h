/*

   slinkie/syscalls.h
   Copyright (C)2004 Dan Potter

*/

#ifndef __SLINKIE_SYSCALLS_H
#define __SLINKIE_SYSCALLS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

// Syscall packet types. These have to stay with the ugly dcload-ip
// names to maintain wire compatibility.
#define SC_EXIT		"DC00"
#define SC_WRITE	"DD02"
#define SC_READ		"DC03"
#define SC_OPEN		"DC04"
#define SC_CLOSE	"DC05"
#define SC_UNLINK	"DC08"
#define SC_LSEEK	"DC11"
#define SC_STAT		"DC13"
#define SC_DIROPEN	"DC16"
#define SC_DIRCLOSE	"DC17"
#define SC_DIRREAD	"DC18"
#define SC_CDFSREAD	"DC19"

__END_DECLS

#endif	/* __SLINKIE_SYSCALLS_H */

