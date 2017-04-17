//*++
//
// Copyright (c) 1997-1998 Microsoft Corporation
//
// Module Name:
//
//  kxppc.h
//
// Abstract:
//
//  This module contains the nongenerated part of the PPC assembler
//  header file. In general, it contains processor architecture constant
//  information, however some assembler macros are also included.
//
//--*/

#ifndef _KXPPC_
#define _KXPPC_

#define ASM_ONLY




//
// Macro to generate a mask using the SPR bit definitions below
//
#define BITMASK(shift,mask)  ((mask) << (31-(shift)))


//
// Register #'s for special purpose registers
//
#define XER     1
#define DECRMEMENTER     22
#define SRR0    26
#define SRR1    27
#define SPRG0   272
#define SPRG1   273
#define SPRG2   274
#define SPRG3   275
#define TBL     284
#define TBH     285
#define PVR     287



//
// Define Machine State Register bit field offsets.
//
// MSR_BIT_POW   0x0d Power management enable         <13>
// MSR_BIT_IMPL  0x0e Implementation dependent        <14>
// MSR_BIT_ILE   0x0f Interrupt Little-Endian mode    <15>
// MSR_BIT_EE    0x10 External interrupt Enable       <16>
// MSR_BIT_PR    0x11 Problem state                   <17>
// MSR_BIT_FP    0x12 Floating Point available        <18>
// MSR_BIT_ME    0x13 Machine check Enable            <19>
// MSR_BIT_FE0   0x14 Floating point Exception mode 0 <20>
// MSR_BIT_SE    0x15 Single-step trace Enable        <21>
// MSR_BIT_BE    0x16 Branch trace Enable             <22>
// MSR_BIT_FE1   0x17 Floating point Exception mode 1 <23>
// MSR_BIT_IP    0x19 Interrupt Prefix                <25>
// MSR_BIT_IR    0x1a Instruction Relocate            <26>
// MSR_BIT_DR    0x1b Data Relocate                   <27>
// MSR_BIT_RI    0x1e Recoverable Interrupt           <30>
// MSR_BIT_LE    0x1f Little-Endian execution mode    <31>
//
#define MSR_BIT_POW   0x0d
#define MSR_BIT_IMPL  0x0e
#define MSR_BIT_ILE   0x0f
#define MSR_BIT_EE    0x10
#define MSR_BIT_PR    0x11
#define MSR_BIT_FP    0x12
#define MSR_BIT_ME    0x13
#define MSR_BIT_FE0   0x14
#define MSR_BIT_SE    0x15
#define MSR_BIT_BE    0x16
#define MSR_BIT_FE1   0x17
#define MSR_BIT_IP    0x19
#define MSR_BIT_IR    0x1a
#define MSR_BIT_DR    0x1b
#define MSR_BIT_RI    0x1e
#define MSR_BIT_LE    0x1f

#define MSR_POW   (BITMASK(MSR_BIT_POW,1))
#define MSR_IMPL  (BITMASK(MSR_BIT_IMPL,1))
#define MSR_ILE   (BITMASK(MSR_BIT_ILE,1))
#define MSR_EE    (BITMASK(MSR_BIT_EE,1))
#define MSR_PR    (BITMASK(MSR_BIT_PR,1))
#define MSR_FP    (BITMASK(MSR_BIT_FP,1))
#define MSR_ME    (BITMASK(MSR_BIT_ME,1))
#define MSR_FE0   (BITMASK(MSR_BIT_FE0,1))
#define MSR_SE    (BITMASK(MSR_BIT_SE,1))
#define MSR_BE    (BITMASK(MSR_BIT_BE,1))
#define MSR_FE1   (BITMASK(MSR_BIT_FE1,1))
#define MSR_IP    (BITMASK(MSR_BIT_IP,1))
#define MSR_IR    (BITMASK(MSR_BIT_IR,1))
#define MSR_DR    (BITMASK(MSR_BIT_DR,1))
#define MSR_RI    (BITMASK(MSR_BIT_RI,1))
#define MSR_LE    (BITMASK(MSR_BIT_LE,1))


//
// Define Processor Version Register (PVR) bit fields
//
//  PVR_BIT_Version  0x0  Processor Version  <0:15>
//  PVR_BIT_Revision 0x10 Processor Revision <16:31>
//
#define PVR_BIT_Version  0x0
#define PVR_BIT_Revision 0x10

#define PVR_Version  (BITMASK(PVR_BIT_Version, 0xFFFF))
#define PVR_Revision (BITMASK(PVR_BIT_Revision, 0xFFFF))


//
// Define Fixed Point Exception Register (XER) bit fields
//

// XER_BIT_SO    0x0  Summary Overflow <0>
// XER_BIT_OV    0x1  Overflow         <1>
// XER_BIT_CA    0x2  Carry            <2>
// XER_BIT_COMP  0x10 > Carry          <16:23>
// XER_BIT_COUNT 0x19 Carry            <25:31>

#define XER_BIT_SO    0x0
#define XER_BIT_OV    0x1
#define XER_BIT_CA    0x2
#define XER_BIT_COMP  0x10
#define XER_BIT_COUNT 0x19

#define XER_SO    (BITMASK(XER_BIT_SO, 1))
#define XER_OV    (BITMASK(XER_BIT_OV, 1))
#define XER_CA    (BITMASK(XER_BIT_CA, 1))
#define XER_COMP  (BITMASK(XER_BIT_COMP, 0xFF))
#define XER_COUNT (BITMASK(XER_BIT_COUNT, 0x7F))



//
// Define Floating Point Status/Control Register (FPSCR) bit fields
//
// FPSCR_BIT_FX        0x0  Exception summary                          <0>
// FPSCR_BIT_FEX       0x1  Enabled Exception summary                  <1>
// FPSCR_BIT_VX        0x2  Invalid operation exception summary        <2>
// FPSCR_BIT_OX        0x3  Overflow exception                         <3>
// FPSCR_BIT_UX        0x4  Underflow exception                        <4>
// FPSCR_BIT_ZX        0x5  Zero divide exception                      <5>
// FPSCR_BIT_XX        0x6  Inexact exception                          <6>
// FPSCR_BIT_VXSNAN    0x7  Invalid op exception (signalling NaN)      <7>
// FPSCR_BIT_VXISI     0x8  Invalid op exception (infinity - infinity) <8>
// FPSCR_BIT_VXIDI     0x9  Invalid op exception (infinity / infinity) <9>
// FPSCR_BIT_VXZDZ     0x0a Invalid op exception (0 / 0)               <10>
// FPSCR_BIT_VXIMZ     0x0b Invalid op exception (infinity * 0)        <11>
// FPSCR_BIT_VXVC      0x0c Invalid op exception (compare)             <12>
// FPSCR_BIT_FR        0x0d Fraction Rounded                           <13>
// FPSCR_BIT_FI        0x0e Fraction Inexact                           <14>
// FPSCR_BIT_C         0x0f Result Class descriptor                    <15>
// FPSCR_BIT_FL        0x10 Result Less than or negative               <16>
// FPSCR_BIT_FG        0x11 Result Greater than or positive            <17>
// FPSCR_BIT_FE        0x12 Result Equal or zero                       <18>
// FPSCR_BIT_FU        0x13 Result Unordered or NaN                    <19>
// FPSCR_BIT_Res1      0x14 reserved                                   <20>
// FPSCR_BIT_VXSOFT    0x15 Invalid op exception (software request)    <21>
// FPSCR_BIT_VXSQRT    0x16 Invalid op exception (square root)         <22>
// FPSCR_BIT_VXCVI     0x17 Invalid op exception (integer convert)     <23>
// FPSCR_BIT_VE        0x18 Invalid operation exception Enable         <24>
// FPSCR_BIT_OE        0x19 Overflow exception Enable                  <25>
// FPSCR_BIT_UE        0x1a Underflow exception Enable                 <26>
// FPSCR_BIT_ZE        0x1b Zero divide exception Enable               <27>
// FPSCR_BIT_XE        0x1c Inexact exception Enable                   <28>
// FPSCR_BIT_NI        0x1d Non-IEEE mode                              <29>
// FPSCR_BIT_RN        0x1e Rounding control                        <30:31>

#define FPSCR_BIT_FX        0x0
#define FPSCR_BIT_FEX       0x1
#define FPSCR_BIT_VX        0x2
#define FPSCR_BIT_OX        0x3
#define FPSCR_BIT_UX        0x4
#define FPSCR_BIT_ZX        0x5
#define FPSCR_BIT_XX        0x6
#define FPSCR_BIT_VXSNAN    0x7
#define FPSCR_BIT_VXISI     0x8
#define FPSCR_BIT_VXIDI     0x9
#define FPSCR_BIT_VXZDZ     0x0a
#define FPSCR_BIT_VXIMZ     0x0b
#define FPSCR_BIT_VXVC      0x0c
#define FPSCR_BIT_FR        0x0d
#define FPSCR_BIT_FI        0x0e
#define FPSCR_BIT_C         0x0f
#define FPSCR_BIT_FL        0x10
#define FPSCR_BIT_FG        0x11
#define FPSCR_BIT_FE        0x12
#define FPSCR_BIT_FU        0x13
#define FPSCR_BIT_Res1      0x14
#define FPSCR_BIT_VXSOFT    0x15
#define FPSCR_BIT_VXSQRT    0x16
#define FPSCR_BIT_VXCVI     0x17
#define FPSCR_BIT_VE        0x18
#define FPSCR_BIT_OE        0x19
#define FPSCR_BIT_UE        0x1a
#define FPSCR_BIT_ZE        0x1b
#define FPSCR_BIT_XE        0x1c
#define FPSCR_BIT_NI        0x1d
#define FPSCR_BIT_RN        0x1e

#define FPSCR_FX        (BITMASK(FPSCR_FX, 1))
#define FPSCR_FEX       (BITMASK(FPSCR_FEX, 1))
#define FPSCR_VX        (BITMASK(FPSCR_VX, 1))
#define FPSCR_OX        (BITMASK(FPSCR_OX, 1))
#define FPSCR_UX        (BITMASK(FPSCR_UX, 1))
#define FPSCR_ZX        (BITMASK(FPSCR_ZX, 1))
#define FPSCR_XX        (BITMASK(FPSCR_XX, 1))
#define FPSCR_VXSNAN    (BITMASK(FPSCR_VXSNAN, 1))
#define FPSCR_VXISI     (BITMASK(FPSCR_VXISI, 1))
#define FPSCR_VXIDI     (BITMASK(FPSCR_VXIDI, 1))
#define FPSCR_VXZDZ     (BITMASK(FPSCR_VXZDZ, 1))
#define FPSCR_VXIMZ     (BITMASK(FPSCR_VXIMZ, 1))
#define FPSCR_VXVC      (BITMASK(FPSCR_VXVC, 1))
#define FPSCR_FR        (BITMASK(FPSCR_FR, 1))
#define FPSCR_FI        (BITMASK(FPSCR_FI, 1))
#define FPSCR_C         (BITMASK(FPSCR_C, 1))
#define FPSCR_FL        (BITMASK(FPSCR_FL, 1))
#define FPSCR_FG        (BITMASK(FPSCR_FG, 1))
#define FPSCR_FE        (BITMASK(FPSCR_FE, 1))
#define FPSCR_FU        (BITMASK(FPSCR_FU, 1))
#define FPSCR_Res1      (BITMASK(FPSCR_Res1, 1))
#define FPSCR_VXSOFT    (BITMASK(FPSCR_VXSOFT, 1))
#define FPSCR_VXSQRT    (BITMASK(FPSCR_VXSQRT, 1))
#define FPSCR_VXCVI     (BITMASK(FPSCR_VXCVI, 1))
#define FPSCR_VE        (BITMASK(FPSCR_VE, 1))
#define FPSCR_OE        (BITMASK(FPSCR_OE, 1))
#define FPSCR_UE        (BITMASK(FPSCR_UE, 1))
#define FPSCR_ZE        (BITMASK(FPSCR_ZE, 1))
#define FPSCR_XE        (BITMASK(FPSCR_XE, 1))
#define FPSCR_NI        (BITMASK(FPSCR_NI, 1))
#define FPSCR_RN        (BITMASK(FPSCR_RN, 3))



#ifndef _KXPPC_C_HEADER_

//
// Define global definition macros.
//

//
// Define load immediate macro for 32-bit values.
//
//      reg       - Register to load with the 32-bit immediate
//      immediate - 32-bit immediate value
//
#define LWI(reg,immediate)   \
       .lwi reg, (immediate)



//
// Define macros used by procedure entry/exit macros
//
// Note that these macros are not intended to be used except in this file.
//


//
//  Alignment macro to align a constant address to the next 8 byte boundary
//   (a double word boundary)
//
#define ALIGN8(addr)  (  ((addr)+7) & ~0x7  )



//
//  __savegpr0  Used for storing no non-volatile GPRs.  Saves only the LR.
//   ...
//  __savegpr17 Used for storing 17 non-volatile GPRs.  Also saves the LR.
//
// Stores a non-volatile GPR and moves the link register into it.  Next, the
// requested number of GPRs to be saved are saved either inline or by branching
// to millicode routines.
//
// GPRs are stored relative to the caller's stack pointer when the prologue is
// entered.  Note that r1 is always aligned on an 8 byte boundary.
//

#define __savegpr0        \
    stw     r31, -4(r1)   ;\
    mflr    r31

#define __savegpr1        \
    stw     r30, -8(r1)   ;\
    mflr    r30           ;\
    stw     r31, -4(r1)

#define __savegpr2        \
    stw     r29, -12(r1)  ;\
    mflr    r29           ;\
    stw     r31,  -4(r1)  ;\
    stw     r30,  -8(r1)

#define __savegpr3        \
    stw     r28, -16(r1)  ;\
    mflr    r28           ;\
    stw     r31,  -4(r1)  ;\
    stw     r30,  -8(r1)  ;\
    stw     r29, -12(r1)

#define __savegpr4        \
    stw     r27, -20(r1)  ;\
    mflr    r27           ;\
    bl      __savegpr_28

#define __savegpr5        \
    stw     r26, -24(r1)  ;\
    mflr    r26           ;\
    bl      __savegpr_27

#define __savegpr6        \
    stw     r25, -28(r1)  ;\
    mflr    r25           ;\
    bl      __savegpr_26

#define __savegpr7        \
    stw     r24, -32(r1)  ;\
    mflr    r24           ;\
    bl      __savegpr_25

#define __savegpr8        \
    stw     r23, -36(r1)  ;\
    mflr    r23           ;\
    bl      __savegpr_24

#define __savegpr9        \
    stw     r22, -40(r1)  ;\
    mflr    r22           ;\
    bl      __savegpr_23

#define __savegpr10       \
    stw     r21, -44(r1)  ;\
    mflr    r21           ;\
    bl      __savegpr_22

#define __savegpr11       \
    stw     r20, -48(r1)  ;\
    mflr    r20           ;\
    bl      __savegpr_21

#define __savegpr12       \
    stw     r19, -52(r1)  ;\
    mflr    r19           ;\
    bl      __savegpr_20

#define __savegpr13       \
    stw     r18, -56(r1)  ;\
    mflr    r18           ;\
    bl      __savegpr_19

#define __savegpr14       \
    stw     r17, -60(r1)  ;\
    mflr    r17           ;\
    bl      __savegpr_18

#define __savegpr15       \
    stw     r16, -64(r1)  ;\
    mflr    r16           ;\
    bl      __savegpr_17

#define __savegpr16       \
    stw     r15, -68(r1)  ;\
    mflr    r15           ;\
    bl      __savegpr_16

#define __savegpr17       \
    stw     r14, -72(r1)  ;\
    mflr    r14           ;\
    bl      __savegpr_15



//
// __savefpr0  Used to save no FPRs.
//  ...
// __savefpr19 Used to save 19 FPRs.
//
//  Gprs - Number of GPRs to be saved
//
// Saves the number of FPRs specified inline or by branching to the appropriate
// millicode procedure.  The routine sets up r12 to be the base of the FPR
// save area.  FPRs must be double word aligned (on 8 byte boundaries) so
// r12 is adjusted according to the number of GPRs saved.  One word of pad may
// be inserted if an odd number of GPRs was saved.
//

#define __savefpr0(Gprs)          

#define __savefpr1(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    stfd    f31,  -8(r12)

#define __savefpr2(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    stfd    f31,  -8(r12)                    ;\
    stfd    f30, -16(r12)

#define __savefpr3(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    stfd    f31,  -8(r12)                    ;\
    stfd    f30, -16(r12)                    ;\
    stfd    f29, -24(r12)

#define __savefpr4(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_28

#define __savefpr5(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_27

#define __savefpr6(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_26

#define __savefpr7(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_25

#define __savefpr8(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_24

#define __savefpr9(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_23

#define __savefpr10(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_22

#define __savefpr11(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_21

#define __savefpr12(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_20

#define __savefpr13(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_19

#define __savefpr14(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_18

#define __savefpr15(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_17

#define __savefpr16(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_16

#define __savefpr17(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_15

#define __savefpr18(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_14

#define __savefpr19(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __savefpr_13



//
// __restgpr0  Used to restore only the GPR storing the link register.
//  ...
// __restgpr17 Used to restore 17 GPRs and the one storing the link register.
//
//
// These macros generate the end of a function's epilogue.  The link register
// is restored from the one reserved non-volatile.  Next, each of the saved off
// non-volatile GPRs, including the one in which the return address was stored
// is restored.  This restoration is done relative to r1 which was already set
// to the caller's value and is done inline or through use of the millicode
// routines.  In either case, a blr is done to return to the caller.  Note that
// the millicode routines are branched to so that the blr there will return
// program flow to the caller.
//

#define __restgpr0        \
    mtlr    r31           ;\
    lwz     r31, -4(r1)   ;\
    blr

#define __restgpr1        \
    mtlr    r30           ;\
    lwz     r30, -8(r1)   ;\
    lwz     r31, -4(r1)   ;\
    blr

#define __restgpr2        \
    mtlr    r29           ;\
    lwz     r29, -12(r1)  ;\
    lwz     r30,  -8(r1)  ;\
    lwz     r31,  -4(r1)  ;\
    blr

#define __restgpr3        \
    mtlr    r28           ;\
    lwz     r28, -16(r1)  ;\
    lwz     r29, -12(r1)  ;\
    lwz     r30,  -8(r1)  ;\
    lwz     r31,  -4(r1)  ;\
    blr

#define __restgpr4        \
    mtlr    r27           ;\
    b       __restgpr_27

#define __restgpr5        \
    mtlr    r26           ;\
    b       __restgpr_26

#define __restgpr6        \
    mtlr    r25           ;\
    b       __restgpr_25

#define __restgpr7        \
    mtlr    r24           ;\
    b       __restgpr_24

#define __restgpr8        \
    mtlr    r23           ;\
    b       __restgpr_23

#define __restgpr9        \
    mtlr    r22           ;\
    b       __restgpr_22

#define __restgpr10       \
    mtlr    r21           ;\
    b       __restgpr_21

#define __restgpr11       \
    mtlr    r20           ;\
    b       __restgpr_20

#define __restgpr12       \
    mtlr    r19           ;\
    b       __restgpr_19

#define __restgpr13       \
    mtlr    r18           ;\
    b       __restgpr_18

#define __restgpr14       \
    mtlr    r17           ;\
    b       __restgpr_17

#define __restgpr15       \
    mtlr    r16           ;\
    b       __restgpr_16

#define __restgpr16       \
    mtlr    r15           ;\
    b       __restgpr_15

#define __restgpr17       \
    mtlr    r14           ;\
    b       __restgpr_14


//
// __restfpr0  Restores no FPRs.
//  ...
// __restfpr19 Restores 19 FPRs.
//
//  Gprs - Number of GPRs saved (not including the link register).
// 
// Restore the number of FPRs specified inline or by branching to the
// appropriate millicode procedure.  Note that r1 is aligned on an 8 byte
// boundary.
//
#define __restfpr0(Gprs)

#define __restfpr1(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    lfd     f31,  -8(r12)

#define __restfpr2(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    lfd     f31,  -8(r12)                    ;\
    lfd     f30, -16(r12)

#define __restfpr3(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    lfd     f31,  -8(r12)                    ;\
    lfd     f30, -16(r12)                    ;\
    lfd     f29, -24(r12)

#define __restfpr4(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_28

#define __restfpr5(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_27

#define __restfpr6(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_26

#define __restfpr7(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_25

#define __restfpr8(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_24

#define __restfpr9(Gprs)                     \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_23

#define __restfpr10(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_22

#define __restfpr11(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_21

#define __restfpr12(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_20

#define __restfpr13(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_19

#define __restfpr14(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_18

#define __restfpr15(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_17

#define __restfpr16(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_16

#define __restfpr17(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_15

#define __restfpr18(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_14

#define __restfpr19(Gprs)                    \
    addi    r12, r1, -(ALIGN8((Gprs+1)*4))   ;\
    bl      __restfpr_13


#endif // _KXPPC_C_HEADER_


//**************************************************************************/
//
//      PPC Linkage support macros
//
//
//**************************************************************************/

//
// Offset to backchain
//
#define STK_RSP         0

//
// Size of stack header (backchain + reserved)
//
#define STK_HDR_SZ      8

//
// Offsets to function arguments pushed onto stack
//
#define STK_P0          STK_HDR_SZ
#define STK_P1          (STK_P0+4)
#define STK_P2          (STK_P0+8)
#define STK_P3          (STK_P0+12)
#define STK_P4          (STK_P0+16)
#define STK_P5          (STK_P0+20)
#define STK_P6          (STK_P0+24)
#define STK_P7          (STK_P0+28)

//
// Minimum stack frame size (function arguments, backchain, and reserved)
//
#define STK_MIN_FRAME   40


#ifndef _KXPPC_C_HEADER_

//
// The following macros are provided for assembly language programmers.
//
//
// Define procedure entry/exit macros
//
// Name  - Name of the nested procedure entry
// Fsize - Amount of local storage and additional argument passing space
//           Use 0 if no local storage or additional argument passing
//           space is needed.
// Gprs  - Number of general purpose registers to save  (max 17)
// Fprs  - Number of floating point registers to save  (max 19)
//
//
// For primary entry points (NESTED_ENTRY, LEAF_ENTRY), a function table
// entry (for debugging, exception handling) is built.
//
// For all entry points, a function descriptor is built.
//
//
// NESTED_ENTRY is used for routines that call other routines; a stack
// frame is acquired and registers are saved.
//
// LEAF_ENTRY is used for routines that do not call other routines; no stack
// frame is acquired and no registers are saved.
//
//
// NESTED_ENTRY_EX and LEAF_ENTRY_EX are used when an exception or termination
// handler is provided.
//
//
// The PROLOGUE_END macro must be coded in all routines that used NESTED_ENTRY
// or NESTED_ENTRY_EX, because the function table entry refers to the label
// that it generates.
//
// SPECIAL_ENTRY is a used for routines that function like a LEAF_ENTRY
// but require some prologue for exception handling. An example of this
// is a stack checking routine which must make a system call to get
// the TEB pointer. The efficiency of a LEAF_ENTRY is needed, but also
// parts of the NESTED_ENTRY are required for the system call.
//
// Just like the NESTED_ENTRY, SPECIAL_ENTRY requires the PROLOGUE_END
// macro.
//
// FN_TABLE, DUMMY_ENTRY, and DUMMY_EXIT are used to construct the "prologues"
// for low-level exception handling code.  These prologues are never executed,
// but are present to allow unwinding through the hand-written, low-level
// assembly code.

//
//  Register Conventions
//  ~~~~~~~~~~~~~~~~~~~~
//  r0          Temporary/scratch
//  r1          Stack Pointer
//  r2          GP (Global Pointer)
//  r3 - r10    Argument Registers
//  r11         Temporary
//  r12         Temporary (also used during prologue/epilogue)
//  r13         Reserved
//  r14 - r31   Non-volatiles
// 
//
// The following is a description of the stack layout for nested calls.  The
// same layout and process is used for all NESTED_ENTRY* macros, below.
//
// The requested number of GPRs (if any) are pushed onto the stack.  The link
// register is saved in this process in a non-volatile register.
//
// Next, the requested number of FPRs are pushed on the stack, below the
// saved GPRs.
//
// Finally, the stack pointer is updated to the new location, and the
// backchain (dynamic link to the previous stack pointer) is written in.
// Note that the stack pointer is always aligned on an 8 byte boundary.
// 
//
//                                               HIGH ADDRESS
//                                              Stack grows down
// Caller's stack pointer
//   R1 ------> | Caller's backchain                   |
//    |         +--------------------------------------+
//    |         | The first GPR is saved at -4 off the |
//    |         | caller's stack pointer.              |
//    |         |                                      |
//    |         |  Saved GPRs (if needed)              |
//    |         |                  +-------------------+
//    |         |                  |  Pad  (if needed) |
//    |         +------------------+-------------------+
//    |    r12->| r12 is used as a base into the FPR   |
//    |         | save area.  It is aligned on an 8    |
//    |         | byte boundary.  Padding (above) is   |
//    |         | inserted if necessary.               |
//    |         |                                      |
//    |         |                                      |
//    |         |  Saved FPRs (if needed)              |
//    |         |                                      |
//    |         +--------------------------------------+ <-------------------
//    |         |                                      |                   ^
//    |         |  Locals (if needed)                  |                   |
//    |         |                                      |                   |
//    |         +--------------------------------------+                 Fsize
//    |         |                                      |                   |
//    |         |  Additional Arguments (if needed)    |                   |
//    |         |                                      |                   v
//    |         +------------------+-------------------+ <-------------------
//    |         |  Parameter Wd 6  |  Parameter Wd 7   |  Argument         ^
//    |         +------------------+-------------------+   Passing Area    |
//    |         |  Parameter Wd 4  |  Parameter Wd 5   |  Wd0 = r3         |
//    |         +------------------+-------------------+   ...             |
//    |         |  Parameter Wd 2  |  Parameter Wd 3   |  Wd7 = r10        |
//    |         +------------------+-------------------+                   |
//    |         |  Parameter Wd 0  |  Parameter Wd 1   |         STK_MIN_FRAME
//    v         +------------------+-------------------+                   |
//   R1'------> |  Back chain (r1) |     Reserved      |                   v
//              +------------------+-------------------+ <-------------------
//              STACK TOP                       Stack grows down
//                                               LOW ADDRESS
//
//  R1 is always aligned on an 8 byte boundary.
//

#define NESTED_ENTRY(Name,Fsize,Gprs,Fprs)                              \
    __fntabentry(Name)                                                  ;\
    __begintext(Name)                                                   ;\
    __savegpr##Gprs                                                     ;\
    __savefpr##Fprs(Gprs)                                               ;\
    stwu    r1, -ALIGN8(STK_MIN_FRAME+((Gprs)+1)*4+(Fprs)*8+(Fsize))(r1)

#define NESTED_ENTRY_EX(Name,Fsize,Gprs,Fprs,LangHandler,Scope)         \
    __fntabentryEx(Name,LangHandler,Scope)                              ;\
    __begintext(Name)                                                   ;\
    __savegpr##Gprs                                                     ;\
    __savefpr##Fprs(Gprs)                                               ;\
    stwu    r1, -ALIGN8(STK_MIN_FRAME+((Gprs)+1)*4+(Fprs)*8+(Fsize))(r1)

#define NESTED_EXIT(Name,Fsize,Gprs,Fprs)                               \
Name##.epi:                                                              \
    addi    r1, r1, ALIGN8(STK_MIN_FRAME+((Gprs)+1)*4+(Fprs)*8+(Fsize)) ;\
    __restfpr##Fprs(Gprs)                                               ;\
    __restgpr##Gprs                                                     ;\
Name##.end:

#define PROLOGUE_END(Name)  \
Name##.body:

#define ALTERNATE_ENTRY(Name)  \
    __begintext(Name)

#define LEAF_ENTRY(Name)  \
    __begintext(Name)     ;\
Name##.body:

#define LEAF_ENTRY_EX(Name,LangHandler,Scope)   \
    __fntabentryEx(Name,LangHandler,Scope)      ;\
    __begintext(Name)                           ;\
Name##.body:

#define SPECIAL_ENTRY(Name) \
    __fntabentry(Name)      ;\
    __begintext(Name)

#define DUMMY_ENTRY(Name)  \
    __begintext(Name)

#define LEAF_EXIT(Name) \
    blr                 ;\
Name##.end:

#define ALTERNATE_EXIT(Name)  \
    blr

#define SPECIAL_EXIT(Name) \
    blr                    ;\
Name##.end:

#define DUMMY_EXIT(Name)  \
Name##.end:

#define FN_TABLE(Name)     \
    __fntabentry(Name)

#define FN_TABLE_EX(Name,ExHandler,Data)  \
    __fntabentryEx(Name,ExHandler,Data)


//
// Internal macros, used by the above (not for programmer use)
//

#define __fntabentry(Name)                        \
    .pdata                                        ;\
    .align  2                                     ;\
    .long   Name                                  ;\
    .long   ( ( ((Name##.body-Name) >> 2) |        \
             (((Name##.end-Name) >> 2) << 8) ) |   \
              (1 << 30))

#define __fntabentryEx(Name,ExHandler,Data)       \
    .pdata                                        ;\
    .align  2                                     ;\
    .long   Name                                  ;\
    .long   ( ((Name##.body-Name) >> 2) |          \
              (((Name##.end-Name) >> 2) << 8) |    \
              (1 << 31 ) | (1 << 30))             ;\
    .text                                         ;\
    .align  3                                     ;\
    .long   ExHandler                             ;\
    .long   Data

#define __begintext(Name)   \
    .text                   ;\
    .align  2               ;\
    .globl  Name            ;\
Name:

#endif // _KXPPC_C_HEADER_

#endif // _KXPPC_
