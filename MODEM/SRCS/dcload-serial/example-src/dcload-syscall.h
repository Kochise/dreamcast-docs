#ifndef __DCLOAD_SYSCALL_H__
#define __DCLOAD_SYSCALL_H__

int dcloadsyscall(unsigned int syscall, ...);

#define pcreadnr 0
#define pcwritenr 1
#define pcopennr 2
#define pcclosenr 3
#define pccreatnr 4
#define pclinknr 5
#define pcunlinknr 6
#define pcchdirnr 7
#define pcchmodnr 8        
#define pclseeknr 9
#define pcfstatnr 10
#define pctimenr 11
#define pcstatnr 12
#define pcutimenr 13
#define pcassignwrkmem 14
#define pcexitnr 15

#define DCLOADMAGICVALUE 0xdeadbeef
#define DCLOADMAGICADDR  (unsigned int *)0x8c004004

#endif
