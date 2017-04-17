	.section .text
	.global _cdfs_redir_enable
	.global _cdfs_redir_disable
	.global _cdfs_redir_save
.align 2
	
_cdfs_redir_save:
	mov.l cdfs_saved_k, r0
	mov.l @r0, r0
	tst r0,r0
	bf already_saved
	mov.l cdfs_entry_k, r0
	mov.l @r0,r0
	mov.l cdfs_saved_k, r1
	mov.l r0, @r1
already_saved:	
	rts
	nop
	
_cdfs_redir_disable:
	mov.l cdfs_saved_k, r0
	mov.l @r0, r0
	mov.l cdfs_entry_k, r1
	mov.l r0, @r1
	rts
	nop

_cdfs_redir_enable:
	mov.l cdfs_entry_k, r0
	mov.l cdfs_redir_k, r1
	mov.l r1, @r0
	rts
	nop
	
.align 4
cdfs_entry_k:
	.long 0x8c0000bc
cdfs_saved_k:
	.long cdfs_saved
cdfs_saved:
	.long 0
cdfs_redir_k:
	.long cdfs_redir

cdfs_redir:
	mov r7,r0
	mov #10,r1
	cmp/hs r0,r1
	bf badsyscall
	mov.l gd_first_k,r1
	shll2 r0
	mov.l @(r0,r1),r0
	jmp @r0
	nop
badsyscall:
	mov #-1,r0
	rts
	nop

gd_first_k:
	.long gdGdcReqCmd
gdGdcReqCmd:
	.long _gdGdcReqCmd
gdGdcGetCmdStat:
	.long _gdGdcGetCmdStat
gdGdcExecServer:
	.long _gdGdcExecServer
gdGdcInitSystem:
	.long _gdGdcInitSystem
gdGdcGetDrvStat:
	.long _gdGdcGetDrvStat
gdGdcG1DmaEnd:
	.long badsyscall
gdGdcReqDmaTrans:
	.long badsyscall
gdGdcCheckDmaTrans:
	.long badsyscall
gdGdcReadAbort:
	.long badsyscall
gdGdcReset:
	.long badsyscall
gdGdcChangeDataType:
	.long _gdGdcChangeDataType
