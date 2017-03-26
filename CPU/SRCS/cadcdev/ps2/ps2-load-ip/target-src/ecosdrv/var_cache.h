/* ps2-load-ip

   var_cache.h

   Copyright (c)1998, 1999, 2000, 2001, 2002 Red Hat, Inc.
   Copyright (2)2002 Dan Potter
   License: GPL

   $Id: var_cache.h,v 1.1 2002/10/30 05:34:12 bardtx Exp $
*/

#ifndef CYGONCE_VAR_CACHE_H
#define CYGONCE_VAR_CACHE_H

// Filched from the EE target from the Dodes eCos tree and modified for
// ps2-load-ip by Dan Potter.

#include "types.h"

#define CYGPKG_HAL_MIPS_EE
#define CYG_MACRO_START do {
#define CYG_MACRO_END } while(0)
#define cyg_uint32 uint32
#define CYG_ADDRESS uint32
#define CYG_WORD int

// $Id: var_cache.h,v 1.1 2002/10/30 05:34:12 bardtx Exp $
// This file is based on hal/mips/tx49/include/var_cache.h

/* #include <pkgconf/hal.h>
#include <cyg/infra/cyg_type.h>

#include <cyg/hal/mips-regs.h>

#include <cyg/hal/plf_cache.h> */

// Use this macro to allow the assembler to accept "cache" instructions,
// which are MIPS ISA 3. This is useful if someone is compiling
// with -mips2, but the architecture is really MIPS ISA 3.

#define _var_asm_mips_cpp_stringize( _x_ ) #_x_
#define _VAR_ASM_SET_MIPS_ISA( _isal_ ) asm volatile ( \
      ".set mips" _var_asm_mips_cpp_stringize(_isal_) )

// EmotionEngine

#ifdef CYGPKG_HAL_MIPS_EE

//-----------------------------------------------------------------------------
// Cache dimensions

#define CYGHWR_HAL_DCACHE_SIZE 8192
#define CYGHWR_HAL_ICACHE_SIZE 16384

// Data cache
#define HAL_DCACHE_SIZE                 CYGHWR_HAL_DCACHE_SIZE // size in bytes
#define HAL_DCACHE_LINE_SIZE            64      // Size of a data cache line
#define HAL_DCACHE_WAYS                 2       // Associativity of the cache


// Instruction cache
#define HAL_ICACHE_SIZE                 CYGHWR_HAL_ICACHE_SIZE // size in bytes
#define HAL_ICACHE_LINE_SIZE            64      // Size of a cache line
#define HAL_ICACHE_WAYS                 2       // Associativity of the cache

#define HAL_DCACHE_SETS (HAL_DCACHE_SIZE/(HAL_DCACHE_LINE_SIZE*HAL_DCACHE_WAYS))
#define HAL_ICACHE_SETS (HAL_ICACHE_SIZE/(HAL_ICACHE_LINE_SIZE*HAL_ICACHE_WAYS))
#define HAL_MIPS_CACHE_INSN_USES_LSB

//-----------------------------------------------------------------------------
// Cache instruction for EE.

#define _VAR_ASM_DCACHE_ALL_WAYS( _cmd_ , _addr_ )      \
    asm volatile ("sync;"                               \
                  "cache %0,0(%1);"                     \
                  "sync;"                               \
                  "cache %0,1(%1);"                     \
                  "sync;"                               \
                    : : "I" (_cmd_), "r"(_addr_))

#define _VAR_ASM_ICACHE_ALL_WAYS( _cmd_ , _addr_ )      \
    asm volatile ("sync;"                               \
                  "cache %0,0(%1);"                     \
                  "sync;"                               \
                  "cache %0,1(%1);"                     \
                  "sync;"                               \
                    : : "I" (_cmd_), "r"(_addr_))

//-----------------------------------------------------------------------------
// Cache controls

// Register $16 is Config register (controls cache state)

// Config Register fields
#define CYGARC_REG_CONFIG_ICE      0x00020000 // Instruction cache enable
#define CYGARC_REG_CONFIG_DCE      0x00010000 // Data cache enable

//-----------------------------------------------------------------------------
// Global control of data cache

// Enable the data cache
// This uses a bit in the config register, which is TX49 specific.
#define HAL_DCACHE_DISABLE_DEFINED
#define HAL_DCACHE_DISABLE()                            \
    CYG_MACRO_START                                     \
    cyg_uint32 tmp;                                     \
    asm volatile ("mfc0 %0,$16;"                        \
                  "and  %0,%0,%1;"                      \
                  "mtc0 %0,$16;"                        \
                  "sync.p;"                             \
                  : "=&r" (tmp)                         \
                  : "r" (~CYGARC_REG_CONFIG_DCE)        \
                 );                                     \
    CYG_MACRO_END

// Disable the data cache
#define HAL_DCACHE_ENABLE_DEFINED
#define HAL_DCACHE_ENABLE()                             \
    CYG_MACRO_START                                     \
    cyg_uint32 tmp;                                     \
    asm volatile ("mfc0 %0,$16;"                        \
                  "or   %0,%0,%1;"                      \
                  "mtc0 %0,$16;"                        \
                  "sync.p;"                             \
                  : "=&r" (tmp)                         \
                  : "r" (CYGARC_REG_CONFIG_DCE)         \
                 );                                     \
    CYG_MACRO_END

#define HAL_DCACHE_IS_ENABLED_DEFINED
#define HAL_DCACHE_IS_ENABLED(_state_)          \
    CYG_MACRO_START                             \
    cyg_uint32 _cstate_;                        \
    asm volatile ( "mfc0   %0,$16\n"            \
                   : "=r"(_cstate_)             \
                   );                           \
    if( _cstate_ & CYGARC_REG_CONFIG_DCE)       \
       _state_ = 1;                             \
    else                                        \
      _state_ = 0;                              \
    CYG_MACRO_END

// Synchronize the contents of the cache with memory.
// This uses the index-writeback-invalidate operation.
#define HAL_DCACHE_SYNC_DEFINED
#define HAL_DCACHE_SYNC()                                               \
    CYG_MACRO_START                                                     \
    register CYG_ADDRESS _baddr_ = 0x80000000;                          \
    register CYG_ADDRESS _addr_ = 0x80000000;                           \
    register CYG_WORD _size_ = HAL_DCACHE_SIZE/HAL_DCACHE_WAYS;         \
    _VAR_ASM_SET_MIPS_ISA(3);                                           \
    for( ; _addr_ <= _baddr_+_size_; _addr_ += HAL_DCACHE_LINE_SIZE )   \
    { _VAR_ASM_DCACHE_ALL_WAYS(0x14, _addr_); }                         \
    _VAR_ASM_SET_MIPS_ISA(0);                                           \
    CYG_MACRO_END

// Load the contents of the given address range into the data cache
// and then lock the cache so that it stays there.
// This uses the fetch-and-lock cache operation - none for EE.
#define HAL_DCACHE_LOCK_DEFINED
#define HAL_DCACHE_LOCK(_base_, _asize_)

//-----------------------------------------------------------------------------
// Data cache line control

// Write dirty cache lines to memory and invalidate the cache entries
// for the given address range.
// This uses the hit-writeback-invalidate cache operation.
#define HAL_DCACHE_FLUSH_DEFINED
#define HAL_DCACHE_FLUSH( _base_ , _asize_ )                              \
    CYG_MACRO_START                                                       \
    register CYG_ADDRESS _baddr_ = (CYG_ADDRESS)(_base_);                 \
    register CYG_ADDRESS _addr_ = (CYG_ADDRESS)(_base_);                  \
    register CYG_WORD _size_ = (_asize_);                                 \
    register CYG_WORD _state_;                                            \
    HAL_DCACHE_IS_ENABLED( _state_ );                                     \
    if( _state_ ) {                                                       \
        _VAR_ASM_SET_MIPS_ISA(3);                                         \
        for( ; _addr_ <= _baddr_+_size_; _addr_ += HAL_DCACHE_LINE_SIZE ) \
        { asm volatile ("sync.l;"                                         \
                        "cache 0x18, 0(%0);"                              \
                        "sync.l;"                                         \
                         : : "r"(_addr_)) }                               \
        _VAR_ASM_SET_MIPS_ISA(0);                                         \
    }                                                                     \
    CYG_MACRO_END

// Invalidate cache lines in the given range without writing to memory.
// This uses the hit-invalidate cache operation.
#define HAL_DCACHE_INVALIDATE_DEFINED
#define HAL_DCACHE_INVALIDATE( _base_ , _asize_ )                       \
    CYG_MACRO_START                                                     \
    register CYG_ADDRESS _baddr_ = (CYG_ADDRESS)(_base_);               \
    register CYG_ADDRESS _addr_ = (CYG_ADDRESS)(_base_);                \
    register CYG_WORD _size_ = (_asize_);                               \
    _VAR_ASM_SET_MIPS_ISA(3);                                           \
    for( ; _addr_ <= _baddr_+_size_; _addr_ += HAL_DCACHE_LINE_SIZE )   \
      { asm volatile ("sync.l;"                                         \
                      "cache 0x1a, 0(%0);"                              \
                       : : "r"(_addr_)) }                               \
    { _VAR_ASM_DCACHE_ALL_WAYS(0x1a, _addr_); }                         \
    _VAR_ASM_SET_MIPS_ISA(0);                                           \
    CYG_MACRO_END

// Write dirty cache lines to memory for the given address range.
// This uses the hit-writeback cache operation.
#define HAL_DCACHE_STORE_DEFINED
#define HAL_DCACHE_STORE( _base_ , _asize_ )                              \
    CYG_MACRO_START                                                       \
    register CYG_ADDRESS _baddr_ = (CYG_ADDRESS)(_base_);                 \
    register CYG_ADDRESS _addr_ = (CYG_ADDRESS)(_base_);                  \
    register CYG_WORD _size_ = (_asize_);                                 \
    register CYG_WORD _state_;                                            \
    HAL_DCACHE_IS_ENABLED( _state_ );                                     \
    if( _state_ ) {                                                       \
        _VAR_ASM_SET_MIPS_ISA(3);                                         \
        for( ; _addr_ <= _baddr_+_size_; _addr_ += HAL_DCACHE_LINE_SIZE ) \
        { asm volatile ("sync.l;"                                         \
                        "cache 0x1c, 0(%0);"                              \
                        "sync.l;"                                         \
                         : : "r"(_addr_)) }                               \
        _VAR_ASM_SET_MIPS_ISA(0);                                         \
    }                                                                     \
    CYG_MACRO_END

//-----------------------------------------------------------------------------
// Global control of Instruction cache

// Enable the instruction cache
#define HAL_ICACHE_DISABLE_DEFINED
#define HAL_ICACHE_DISABLE()                            \
    CYG_MACRO_START                                     \
    cyg_uint32 tmp;                                     \
    asm volatile ("mfc0 %0,$16;"                        \
                  "and  %0,%0,%1;"                      \
                  "mtc0 %0,$16;"                        \
                  "sync.p;"                             \
                  : "=&r" (tmp)                         \
                  : "r" (~CYGARC_REG_CONFIG_ICE)        \
                 );                                     \
    CYG_MACRO_END

// Disable the instruction cache
#define HAL_ICACHE_ENABLE_DEFINED
#define HAL_ICACHE_ENABLE()                             \
    CYG_MACRO_START                                     \
    cyg_uint32 tmp;                                     \
    asm volatile ("mfc0 %0,$16;"                        \
                  "or   %0,%0,%1;"                      \
                  "mtc0 %0,$16;"                        \
                  "sync.p;"                             \
                  : "=&r" (tmp)                         \
                  : "r" (CYGARC_REG_CONFIG_ICE)         \
                 );                                     \
    CYG_MACRO_END

#define HAL_ICACHE_IS_ENABLED_DEFINED
#define HAL_ICACHE_IS_ENABLED(_state_)          \
    CYG_MACRO_START                             \
    cyg_uint32 _cstate_;                        \
    asm volatile ( "mfc0   %0,$16\n"            \
                   : "=r"(_cstate_)             \
                   );                           \
    if( _cstate_ & CYGARC_REG_CONFIG_ICE)       \
       _state_ = 1;                             \
    else                                        \
      _state_ = 0;                              \
    CYG_MACRO_END

// Invalidate the entire cache
// This uses the index-invalidate cache operation.
#define HAL_ICACHE_INVALIDATE_ALL_DEFINED
#define HAL_ICACHE_INVALIDATE_ALL()                                           \
    CYG_MACRO_START                                                           \
    register CYG_ADDRESS _baddr_ = 0x00000000;                                \
    register CYG_ADDRESS _addr_ = 0x00000000;                                 \
    register CYG_WORD _size_ = HAL_ICACHE_SIZE/HAL_ICACHE_WAYS;               \
    _VAR_ASM_SET_MIPS_ISA(3);                                                 \
    for( ; _addr_ < _baddr_+_size_; _addr_ += HAL_ICACHE_LINE_SIZE )          \
    { _VAR_ASM_ICACHE_ALL_WAYS(0x07, _addr_); }                               \
    _VAR_ASM_SET_MIPS_ISA(0);                                                 \
    CYG_MACRO_END

// Load the contents of the given address range into the instruction cache
// and then lock the cache so that it stays there.
// This uses the fetch-and-lock cache operation - none for EE.
#define HAL_ICACHE_LOCK_DEFINED
#define HAL_ICACHE_LOCK(_base_, _asize_)

//-----------------------------------------------------------------------------
// Instruction cache line control

// Invalidate cache lines in the given range without writing to memory.
// This uses the hit-invalidate cache operation.
#define HAL_ICACHE_INVALIDATE_DEFINED
#define HAL_ICACHE_INVALIDATE( _base_ , _asize_ )                       \
    CYG_MACRO_START                                                     \
    register CYG_ADDRESS _baddr_ = (CYG_ADDRESS)(_base_);               \
    register CYG_ADDRESS _addr_ = (CYG_ADDRESS)(_base_);                \
    register CYG_WORD _size_ = (_asize_);                               \
    _VAR_ASM_SET_MIPS_ISA(3);                                           \
    for( ; _addr_ <= _baddr_+_size_; _addr_ += HAL_ICACHE_LINE_SIZE )   \
    { asm volatile ("sync.p;"                                           \
                    "cache 0x0b, 0(%0);"                                \
                     : : "r"(_addr_)) }                                \
    _VAR_ASM_SET_MIPS_ISA(0);                                           \
    CYG_MACRO_END

#endif // CYGPKG_HAL_MIPS_EE

// A simple, deCos-ified version to flush everything
static inline void flush_caches() {
	HAL_DCACHE_SYNC();
	HAL_ICACHE_DISABLE();
	HAL_DCACHE_DISABLE();
	HAL_DCACHE_SYNC();  
	HAL_ICACHE_INVALIDATE_ALL();
	// HAL_DCACHE_INVALIDATE_ALL();  
	HAL_ICACHE_ENABLE();
	HAL_DCACHE_ENABLE();
}

//-----------------------------------------------------------------------------
#endif // ifndef CYGONCE_VAR_CACHE_H
// End of var_cache.h
