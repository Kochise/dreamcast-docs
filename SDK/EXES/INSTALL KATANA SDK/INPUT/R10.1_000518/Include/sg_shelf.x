OUTPUT_FORMAT("elf32-shl", "elf32-sh", "elf32-shl")
OUTPUT_ARCH(sh)
ENTRY(SG_SEC) /* Code entry point. */
/* SEARCH_DIR(/usr/src/dossh4elf/sh-hms-elf/lib);*/
/* Do we need any of these for elf?
   __DYNAMIC = 0;    */
SECTIONS
{
  . = 0x8c008000;
  _IP = .;
  _IP_start = . + 0x300;
  ip : { *(IP) }

  . = 0x8c010000;
  __START_DSGLH = .;
  DSGLH : { *(DSGLH) }
  __END_DSGLH = .;

  . = ALIGN(4);
  __START_DSGLE = .;
  DSGLE : { *(DSGLE) }
  __END_DSGLE = .;

  . = ALIGN(4);
  __START_DSG_INIT_ = .;
  DSG_INIT_ : { *(DSG_INIT_) }
  __END_DSG_INIT_ = .;

  . = ALIGN(4);
  __START_DSG_END_ = .;
  DSG_END_ : { *(DSG_END_) }
  __END_DSG_END_ = .;

  . = ALIGN(4);
  __START_P = .;
  P : {	*(P) }
  __END_P = .;

  . = ALIGN(4);
  __START_C = .;
  C : { *(C) }
  __END_C = .;

  . = ALIGN(32);
  __START_C32 = .;
  C32 : { *(C32) }
  __END_C32 = .;

  . = ALIGN(4);
  __START_D = .;
  D : { *(D) }
  __END_D = .;

  . = ALIGN(32);
  __START_D32 = .;
  D32 : { *(D32) }
  __END_D32 = .;

  . = ALIGN(4);
  __START_R = .;
  R : { *(R) }
  __END_R = .;

  . = ALIGN(32);
  __START_R32 = .;
  R32 : { *(R32) }
  __END_R32 = .;

  . = ALIGN(4);
  __START_PSG = .;
  PSG : { *(PSG) }
  __END_PSG = .;

  . = ALIGN(4);
  __START_CSG = .;
  CSG : { *(CSG) }
  __END_CSG = .;

  . = ALIGN(32);
  __START_CSG32 = .;
  CSG32 : { *(CSG32) }
  __END_CSG32 = .;

  . = ALIGN(4);
  __START_DSG = .;
  DSG : { *(DSG) }
  __END_DSG = .;

  . = ALIGN(32);
  __START_DSG32 = .;
  DSG32 : { *(DSG32) }
  __END_DSG32 = .;

  . = ALIGN(4);
  __START_RSG = .;
  RSG : { *(RSG) }
  __END_RSG = .;

  . = ALIGN(32);
  __START_RSG32 = .;
  RSG32 : { *(RSG32) }
  __END_RSG32 = .;

  . = ALIGN(4);
  __START_B = .;
  B : { *(B) }
  __END_B = .;

  . = ALIGN(32);
  __START_B32 = .;
  B32 : { *(B32) }
  __END_B32 = .;

  _start = start;   /* Export "start" symbol. */

  /* Middleware SOFDEC */

  . = ALIGN(32);
  __START_PSGSFD00_LCF = .;
  PSGSFD00 : { *(PSGSFD00) }
  __END_PSGSFD00_LCF = .;

  __START_PSGSFD01_LCF = .;
  PSGSFD01 : { *(PSGSFD01) }
  __END_PSGSFD01_LCF = .;

  __START_PSGSFD02_LCF = .;
  PSGSFD02 : { *(PSGSFD02) }
  __END_PSGSFD02_LCF = .;

  __START_PSGSFD03_LCF = .;
  PSGSFD03 : { *(PSGSFD03) }
  __END_PSGSFD03_LCF = .;

  __START_PSGSFD04_LCF = .;
  PSGSFD04 : { *(PSGSFD04) }
  __END_PSGSFD04_LCF = .;

  __START_PSGSFD05_LCF = .;
  PSGSFD05 : { *(PSGSFD05) }
  __END_PSGSFD05_LCF = .;

  __START_PSGSFD06_LCF = .;
  PSGSFD06 : { *(PSGSFD06) }
  __END_PSGSFD06_LCF = .;

  __START_PSGSFD07_LCF = .;
  PSGSFD07 : { *(PSGSFD07) }
  __END_PSGSFD07_LCF = .;

  __START_PSGSFD08_LCF = .;
  PSGSFD08 : { *(PSGSFD08) }
  __END_PSGSFD08_LCF = .;

  __START_PSGSFD09_LCF = .;
  PSGSFD09 : { *(PSGSFD09) }
  __END_PSGSFD09_LCF = .;

  __START_PSGSFD10_LCF = .;
  PSGSFD10 : { *(PSGSFD10) }
  __END_PSGSFD10_LCF = .;

  __START_PSGSFD11_LCF = .;
  PSGSFD11 : { *(PSGSFD11) }
  __END_PSGSFD11_LCF = .;

  __START_PSGSFD12_LCF = .;
  PSGSFD12 : { *(PSGSFD12) }
  __END_PSGSFD12_LCF = .;

  __START_PSGSFD13_LCF = .;
  PSGSFD13 : { *(PSGSFD13) }
  __END_PSGSFD13_LCF = .;

  __START_PSGSFD14_LCF = .;
  PSGSFD14 : { *(PSGSFD14) }
  __END_PSGSFD14_LCF = .;

  __START_PSGSFD15_LCF = .;
  PSGSFD15 : { *(PSGSFD15) }
  __END_PSGSFD15_LCF = .;

  __SIZE_PSGSFD00_LCF = __END_PSGSFD00_LCF - __START_PSGSFD00_LCF;
  __SIZE_PSGSFD01_LCF = __END_PSGSFD01_LCF - __START_PSGSFD01_LCF;
  __SIZE_PSGSFD02_LCF = __END_PSGSFD02_LCF - __START_PSGSFD02_LCF;
  __SIZE_PSGSFD03_LCF = __END_PSGSFD03_LCF - __START_PSGSFD03_LCF;
  __SIZE_PSGSFD04_LCF = __END_PSGSFD04_LCF - __START_PSGSFD04_LCF;
  __SIZE_PSGSFD05_LCF = __END_PSGSFD05_LCF - __START_PSGSFD05_LCF;
  __SIZE_PSGSFD06_LCF = __END_PSGSFD06_LCF - __START_PSGSFD06_LCF;
  __SIZE_PSGSFD07_LCF = __END_PSGSFD07_LCF - __START_PSGSFD07_LCF;
  __SIZE_PSGSFD08_LCF = __END_PSGSFD08_LCF - __START_PSGSFD08_LCF;
  __SIZE_PSGSFD09_LCF = __END_PSGSFD09_LCF - __START_PSGSFD09_LCF;
  __SIZE_PSGSFD10_LCF = __END_PSGSFD10_LCF - __START_PSGSFD10_LCF;
  __SIZE_PSGSFD11_LCF = __END_PSGSFD11_LCF - __START_PSGSFD11_LCF;
  __SIZE_PSGSFD12_LCF = __END_PSGSFD12_LCF - __START_PSGSFD12_LCF;
  __SIZE_PSGSFD13_LCF = __END_PSGSFD13_LCF - __START_PSGSFD13_LCF;
  __SIZE_PSGSFD14_LCF = __END_PSGSFD14_LCF - __START_PSGSFD14_LCF;
  __SIZE_PSGSFD15_LCF = __END_PSGSFD15_LCF - __START_PSGSFD15_LCF;

  /* Read-only sections, merged into text segment: */
  /*. = 0x8c010000;*/
  .interp     : { *(.interp) 	}
  .hash          : { *(.hash)		}
  .dynsym        : { *(.dynsym)		}
  .dynstr        : { *(.dynstr)		}
  .gnu.version   : { *(.gnu.version)	}
  .gnu.version_d   : { *(.gnu.version_d)	}
  .gnu.version_r   : { *(.gnu.version_r)	}
  .rel.text      :
    { *(.rel.text) *(.rel.gnu.linkonce.t*) }
  .rela.text     :
    { *(.rela.text) *(.rela.gnu.linkonce.t*) }
  .rel.data      :
    { *(.rel.data) *(.rel.gnu.linkonce.d*) }
  .rela.data     :
    { *(.rela.data) *(.rela.gnu.linkonce.d*) }
  .rel.rodata    :
    { *(.rel.rodata) *(.rel.gnu.linkonce.r*) }
  .rela.rodata   :
    { *(.rela.rodata) *(.rela.gnu.linkonce.r*) }
  .rel.got       : { *(.rel.got)		}
  .rela.got      : { *(.rela.got)		}
  .rel.ctors     : { *(.rel.ctors)	}
  .rela.ctors    : { *(.rela.ctors)	}
  .rel.dtors     : { *(.rel.dtors)	}
  .rela.dtors    : { *(.rela.dtors)	}
  .rel.init      : { *(.rel.init)	}
  .rela.init     : { *(.rela.init)	}
  .rel.fini      : { *(.rel.fini)	}
  .rela.fini     : { *(.rela.fini)	}
  .rel.bss       : { *(.rel.bss)		}
  .rela.bss      : { *(.rela.bss)		}
  .rel.plt       : { *(.rel.plt)		}
  .rela.plt      : { *(.rela.plt)		}
  .init          : { *(.init)	} =0
  .plt      : { *(.plt)	}
/* .gnu.warning sections are handled specially by elf32.em.  */
  .text      :
  {
    *(.text)
    *(.stub)
    *(.gnu.warning)
    *(.gnu.linkonce.t*)
  } =0
  _etext = .;
  PROVIDE (etext = .);
  .fini      : { *(.fini)    } =0
  .rodata    : { *(.rodata) *(.gnu.linkonce.r*) }
  .rodata1   : { *(.rodata1) }
  /* Adjust the address for the data segment.  We want to adjust up to
     the same address within the page on the next page up.  */
  . = ALIGN(128) + (. & (128 - 1));
  .data    :
  {
    *(.data)
    *(.gnu.linkonce.d*)
    CONSTRUCTORS
  }
  .data1   : { *(.data1) }
  . = ALIGN(4);
  .ctors         :
  {
    ___ctors = .;
    *(.ctors)
    ___ctors_end = .;
  }
  . = ALIGN(4);
  .dtors         :
  {
    ___dtors = .;
    *(.dtors)
    ___dtors_end = .;
  }
  .got           : { *(.got.plt) *(.got) }
  .dynamic       : { *(.dynamic) }
  /* We want the small data sections together, so single-instruction offsets
     can access them all, and initialized data all before uninitialized, so
     we can shorten the on-disk segment size.  */
  .sdata     : { *(.sdata) }
  _edata  =  .;
  PROVIDE (edata = .);
  __bss_start = .;
  .sbss      : { *(.sbss) *(.scommon) }
  .bss       :
  {
   *(.dynbss)
   *(.bss)
   *(COMMON)
  }
  _end = . ;

  . = ALIGN(4);
  __START_BSG = .;
  BSG : { *(BSG) }
  __END_BSG = .;

  . = ALIGN(32);
  __START_BSG32 = .;
  BSG32 : { *(BSG32) }
  __END_BSG32 = .;

/*  __BSG_END = . ;*/

  PROVIDE (end = .);
  /* Stabs debugging sections.  */
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

  .stack 0x8C00F3FC : { _stack = .; *(.stack) }     /* Shinobi stack after initial values pushed. */

  /* These must appear regardless of  .  */
}