;++
; THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
; ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
; THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
; PARTICULAR PURPOSE.
; Copyright (c) 1995, 1996, 1997  Microsoft Corporation
;
; Module Name:
;
;    kxsh3.h
;
; Abstract:
;
;
;--



;
; This is an implementation of Appendix A of _MMOSA/SH3 Calling Sequence
; Specification_, revision 1.1 (12-20-94).
; It has been modified (1-9-95) to allow an optional section-name override
; on the *_ENTRY macros.
;
; This file is from NK
;

    .macro  ERRNZ   Expr
    .aif    \Expr NE 0
    mov error,r0
    .aendi
    .endm

     .macro    START_REGION   NameBegin
     .global   \NameBegin
\NameBegin:
     .endm

     .macro    END_REGION          NameEnd
     .global   \NameEnd
\NameEnd:
     .endm

     .macro    NESTED_ENTRY   Name,Section=.text
     .section \Section,code
     .align    4
     .global \Name
\Name:    .entry
     .endm

     .macro    PROLOG_END
     .prolog
     .endm

     .macro    LEAF_ENTRY     Name,Section=.text
     NESTED_ENTRY   \Name,\Section
     PROLOG_END
     .endm

     .macro    ALTERNATE_ENTRY     Name,Section=.text
     .global   \Name
\Name:
     .endm

     .macro    ENTRY_END Name=
     .endf
     .endm

     .macro    EXCEPTION_HANDLER   Handler
     .pdata    \Handler
     .endm

     .macro    EXCEPTION_HANDLER_DATA   Handler,HandlerData
     .pdata    \Handler,\HandlerData
     .endm

