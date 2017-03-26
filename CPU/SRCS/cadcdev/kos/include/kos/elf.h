/* KallistiOS ##version##

   kos/elf.h
   Copyright (C)2000,2001,2003 Dan Potter

   $Id: elf.h,v 1.3 2003/08/02 23:08:36 bardtx Exp $

*/

#ifndef __KOS_ELF_H
#define __KOS_ELF_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <sys/queue.h>

/* ELF file header */
struct elf_hdr_t {
	unsigned char	ident[16];	/* For elf32-shl, 0x7f+"ELF"+1+1 */
	uint16		type;		/* 0x02 for ET_EXEC */
	uint16		machine;	/* 0x2a for elf32-shl */
	uint32		version;
	uint32		entry;		/* Entry point */
	uint32		phoff;		/* Program header offset */
	uint32		shoff;		/* Section header offset */
	uint32		flags;		/* Processor flags */
	uint16		ehsize;		/* ELF header size in bytes */
	uint16		phentsize;	/* Program header entry size */
	uint16		phnum;		/* Program header entry count */
	uint16		shentsize;	/* Section header entry size */
	uint16		shnum;		/* Section header entry count */
	uint16		shstrndx;	/* String table section index */
};

/* ELF architecture types */
#define EM_386		3		/* ia32 */
#define EM_SH		42		/* sh */

/* Section header types */
#define SHT_NULL	0		/* Inactive */
#define SHT_PROGBITS	1		/* Program code/data */
#define SHT_SYMTAB	2		/* Full symbol table */
#define SHT_STRTAB	3		/* String table */
#define SHT_RELA	4		/* Relocation table, with addends */
#define SHT_HASH	5		/* Sym tab hashtable */
#define SHT_DYNAMIC	6		/* Dynamic linking info */
#define SHT_NOTE	7		/* Notes */
#define SHT_NOBITS	8		/* Occupies no space in the file */
#define SHT_REL		9		/* Relocation table, no addends */
#define SHT_SHLIB	10		/* Invalid.. hehe */
#define SHT_DYNSYM	11		/* Dynamic-only sym tab */
#define SHT_LOPROC	0x70000000	/* Processor specific */
#define SHT_HIPROC	0x7fffffff
#define SHT_LOUSER	0x80000000	/* Program specific */
#define SHT_HIUSER	0xffffffff

/* Section header flags */
#define SHF_WRITE	1		/* Writable data */
#define SHF_ALLOC	2		/* Resident */
#define SHF_EXECINSTR	4		/* Executable instructions */
#define SHF_MASKPROC	0xf0000000	/* Processor specific */

/* Special section indeces */
#define SHN_UNDEF	0		/* Undefined, missing, irrelevant */
#define SHN_ABS		0xfff1		/* Absolute values */

/* Section header */
struct elf_shdr_t {
	uint32		name;		/* Index into string table */
	uint32		type;		/* See constants above */
	uint32		flags;
	uint32		addr;		/* In-memory offset */
	uint32		offset;		/* On-disk offset */
	uint32		size;		/* Size (if SHT_NOBITS, zero file len */
	uint32		link;		/* See below */
	uint32		info;		/* See below */
	uint32		addralign;	/* Alignment constraints */
	uint32		entsize;	/* Fixed-size table entry sizes */
};
/* Link and info fields:

switch (sh_type) {
	case SHT_DYNAMIC:
		link = section header index of the string table used by
			the entries in this section
		info = 0
	case SHT_HASH:
		ilnk = section header index of the string table to which
			this info applies
		info = 0
	case SHT_REL, SHT_RELA:
		link = section header index of associated symbol table
		info = section header index of section to which reloc applies
	case SHT_SYMTAB, SHT_DYNSYM:
		link = section header index of associated string table
		info = one greater than the symbol table index of the last
			local symbol (binding STB_LOCAL)
}

*/

#define STB_LOCAL	0
#define STB_GLOBAL	1
#define STB_WEAK	2

#define STT_NOTYPE	0
#define STT_OBJECT	1
#define STT_FUNC	2
#define STT_SECTION	3
#define STT_FILE	4

/* Symbol table entry */
struct elf_sym_t {
	uint32		name;		/* Index into stringtab */
	uint32		value;
	uint32		size;
	uint8		info;		/* type == info & 0x0f */
	uint8		other;		
	uint16		shndx;		/* Section index */
};
#define ELF32_ST_BIND(info)	((info) >> 4)
#define ELF32_ST_TYPE(info)	((info) & 0xf)

/* Relocation-A Entries */
struct elf_rela_t {
	uint32		offset;		/* Offset within section */
	uint32		info;		/* Symbol and type */
	int32		addend;		/* "A" constant */
};

/* Relocation Entries */
struct elf_rel_t {
	uint32		offset;		/* Offset within section */
	uint32		info;		/* Symbol and type */
};

/* Relocation-related defs */
#define R_SH_DIR32		1
#define R_386_32		1
#define R_386_PC32		2
#define ELF32_R_SYM(i) ((i) >> 8)
#define ELF32_R_TYPE(i) ((uint8)(i))


/* Kernel-specific definition of a loaded ELF binary */
struct klibrary;
typedef struct elf_prog {
	void	*data;		/* Data block containing the program */
	uint32	size;		/* Memory image size (rounded up to page size) */

	/* Library exports */
	ptr_t	lib_get_name;
	ptr_t	lib_get_version;
	ptr_t	lib_open;
	ptr_t	lib_close;

	/* Library filename */
	char	fn[256];
} elf_prog_t;

/* Load an ELF binary and return the relevant data in an elf_prog_t structure. */
int elf_load(const char *fn, struct klibrary * shell, elf_prog_t * out);

/* Free a loaded ELF program */
void elf_free(elf_prog_t *prog);

__END_DECLS

#endif	/* __OS_ELF_H */

