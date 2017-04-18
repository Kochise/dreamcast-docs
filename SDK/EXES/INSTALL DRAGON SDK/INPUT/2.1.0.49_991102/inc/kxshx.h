    .HEADING "Hitachi SH-3 Calling Convention Macros"
    .FORM LINES=55
;++
;
; Copyright (c) 1995-1998 Microsoft Corporation
;
; Module Name:
;
;    kxsh3.h
;
; Abstract:
;
;    This is an implementation of Appendix A of WINCE/SH3 Calling Sequence
;    Specification_.
;
;
; Environment:
;
;    Kernel mode or User mode.
;
;
;--

	.macro	START_REGION	NameBegin
	.global	\NameBegin
\NameBegin:
	.endm

	.macro	END_REGION		NameEnd
	.global	\NameEnd
\NameEnd:
	.endm

	.macro	NESTED_ENTRY	Name,Section=.text
	.section \Section,code
	.align	4
	.global	\Name
\Name:	.entry
	.endm

	.macro	PROLOG_END
	.prolog
	.endm

	.macro	LEAF_ENTRY	Name,Section=.text
	NESTED_ENTRY	\Name,\Section
	PROLOG_END
	.endm

	.macro	ALTERNATE_ENTRY	Name,Section=.text
	.global	\Name
\Name:
	.endm

	.macro	ENTRY_END	Name=
	.endf
	.endm

	.macro	EXCEPTION_HANDLER	Handler
	.pdata	\Handler
	.endm

	.macro	EXCEPTION_HANDLER_DATA	Handler,HandlerData
	.pdata	\Handler,\HandlerData
	.endm

        .macro  ERRNZ   Expr
        .aif    \Expr NE 0
        mov error,r0
        .aendi
        .endm
		
STATUS_LONGJUMP: .equ H'80000026

; Some register aliases that have documentation value.

arg1reg:    .reg    (r4)    ; first argument register
arg2reg:    .reg    (r5)    ; second argument register
arg3reg:    .reg    (r6)    ; third argument register
arg4reg:    .reg    (r7)    ; fourth argument register

; Offsets into (and length of) the jump buffer.
; Note that we currently save just about everything (though we don't
; quite go to the length of extracting the T, S, M, and Q bits from
; the status register so that we can save and restore them :-).
; Once we know for sure whether or not the compiler might ever want
; MACL, MACH, and/or PR to be callee-save, we can clean this up a
; little (if they turn out to be caller-save).

JBr8:   .equ    H'00
JBr9:   .equ    H'04
JBr10:  .equ    H'08
JBr11:  .equ    H'0C
JBr12:  .equ    H'10
JBr13:  .equ    H'14
JBfp:   .equ    H'18
JBsp:   .equ    H'1C
JBmach: .equ    H'20
JBmacl: .equ    H'24
JBpr:   .equ    H'28
JBtype: .equ    H'2C        ; has virtual frame pointer for unwind

JBLength:   .equ    H'30    ; Note: if this changes, fix setjmp.asm!!!

;  SH3 Revisions up to 7 have a bug in the handling of a TLB miss
;   when certain delayed branch/rts sequences occur.  This macro is used
;   to conditionally insert a nop between the preceeding instruction and
;   the delayed branch/rts.
    .macro  DELAYNOPBUG
    .aif _M_SH == 3 && _M_SH_REV < 8
    .aif ($ - .text) & 2
    nop
    .aendi
    .aendi
    .endm
