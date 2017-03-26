.section .text
.global _dcload_lwip_syscall

.align 2

_dcload_lwip_syscall:
        mov.l   dcloadmagic_k,r1
        mov.l   @r1,r1
        mov.l   correctmagic,r0
        cmp/eq  r0,r1
        bf      badsyscall
        
        mov     r4,r0
        mov     r5,r4
        mov     r6,r5
        mov     r7,r6

        mov     #19,r1
        cmp/hs  r0,r1
        bf      badsyscall

        mov.l   first_syscall,r1
        shll2   r0
        mov.l   @(r0,r1),r0
        jmp     @r0
        nop
        
badsyscall:     
        mov     #-1,r0
        rts
        nop

.align 4
dcloadmagic:
        .long 0xdeadbeef
dcloadmagic_k:
        .long dcloadmagic
correctmagic:
        .long 0xdeadbeef 
first_syscall:
        .long read_k
read_k:
        .long _dcload_lwip_read
write_k:
        .long _dcload_lwip_write
open_k:
        .long _dcload_lwip_open
close_k:
        .long _dcload_lwip_close
creat_k:
        .long badsyscall
link_k:
        .long _dcload_lwip_link
unlink_k:
        .long _dcload_lwip_unlink
chdir_k:
        .long badsyscall
chmod_k:        
        .long badsyscall
lseek_k:
        .long _dcload_lwip_lseek
fstat_k:
        .long badsyscall
time_k:
        .long badsyscall
stat_k:
        .long _dcload_lwip_stat
utime_k:
        .long badsyscall
assign_wrkmem_k:
        .long badsyscall
exit_k:
        .long _dcload_lwip_exit
opendir_k:
        .long _dcload_lwip_opendir
closedir_k:
        .long _dcload_lwip_closedir
readdir_k:
        .long _dcload_lwip_readdir
hostinfo_k:     
        .long badsyscall

