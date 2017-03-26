/* KallistiOS ##version##

   os/elf.h
   (c)2000-2001 Dan Potter

   $Id: elf.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $

*/

#ifndef __OS_ELF_H
#define __OS_ELF_H

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

/* Section header types */
#define SHT_NULL	0		/* Inactive */
#define SHT_PROGBITS	1		/* Program code/data */
#define SHT_SYMTAB	2		/* Full symbol table */
#define SHT_STRTAB	3		/* String table */
#define SHT_RELA	4		/* Relocation table */
#define SHT_HASH	5		/* Sym tab hashtable */
#define SHT_DYNAMIC	6		/* Dynamic linking info */
#define SHT_NOTE	7		/* Notes */
#define SHT_NOBITS	8		/* Occupies no space in the file */
#define SHT_REL		9		/* Relocation table */
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

/* Symbol table entry */
#define STN_UNDEF	0
#define STT_NOTYPE	0
#define STT_OBJECT	1
#define STT_FUNC	2
#define STT_SECTION	3
#define STT_FILE	4
struct elf_sym_t {
	uint32		name;		/* Index into stringtab */
	uint32		value;
	uint32		size;
	uint8		info;		/* type == info & 0x0f */
	uint8		other;		
	uint16		shndx;		/* Section index */
};

/* Relocation-A Entries */
#define R_SH_DIR32		1
struct elf_rela_t {
	uint32		offset;		/* Offset within section */
	uint32		info;		/* Symbol and type */
	int32		addend;		/* "A" constant */
};
#define ELF32_R_SYM(i) ((i) >> 8)
#define ELF32_R_TYPE(i) ((uint8)(i))


/* Kernel-specific definition of a loaded ELF binary */
typedef struct elf_prog {
	void	*data;		/* Data block containing the program */
	uint32	size;		/* Memory image size */
	int	argc;		/* Arguments */
	char	**argv;
	int	(*ko_main)(int argc, char **argv);	/* Program entry point */
	int	(*ko_notify)(uint32 event);		/* Event notification */
	char	fn[256];				/* Program filename */

	LIST_ENTRY(elf_prog)	pslist;
} elf_prog_t;

/* For use only for debugging */
extern LIST_HEAD(pslist, elf_prog) ps_list;

/* Load an ELF binary and return the relevant data in an elf_prog_t structure. */
elf_prog_t *elf_load(uint32 fd);

/* Free a loaded ELF program */
void elf_free(elf_prog_t *prog);

__END_DECLS

#endif	/* __OS_ELF_H */

