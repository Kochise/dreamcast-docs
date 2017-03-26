/* KallistiOS ##version##

   bincnv.c
   (c)2000 Dan Potter
  
   Test ELF to BIN convertor.. loads to VMA 0x8c010000. This is an
   exact functional duplicate of the routine in process/elf.c and is
   used for testing new changes first.

*/

static char id[] = "KOS $Id: bincnv.c,v 1.1.1.1 2001/09/26 07:05:01 bardtx Exp $";

#include <stdio.h>
#include <malloc.h>

#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned long
#define int32 long

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

int find_sym(char *name, struct elf_sym_t* table, int tablelen) {
	int i;
	for (i=0; i<tablelen; i++) {
		if (!strcmp((char*)table[i].name, name))
			return i;
	}
	return -1;
}

/* There's a lot of shit in here that's not documented or very poorly
   documented by Intel.. I hope that this works for future compilers. */
void *elf_load(FILE *f, uint32 vma, int* outsz) {
	char			*img, *imgout;
	int			sz, i, j, sect; 
	struct elf_hdr_t	*hdr;
	struct elf_shdr_t	*shdrs, *symtabhdr;
	struct elf_sym_t	*symtab;
	int			symtabsize;
	struct elf_rela_t	*reltab;
	int			reltabsize;
	char			*stringtab;

	/* Load the file */
	fseek(f, 0, SEEK_END); sz=ftell(f); fseek(f, 0, SEEK_SET);
	img = malloc(sz);
	fread(img, sz, 1, f);
	fclose(f);

	/* Header is at the front */
	hdr = (struct elf_hdr_t *)(img+0);
	if (hdr->ident[0] != 0x7f || strncmp(hdr->ident+1, "ELF", 3)) {
		printf("File is not a valid ELF file\n");
		return NULL;
	}
	if (hdr->ident[4] != 1 || hdr->ident[5] != 1) {
		printf("Invalid architecture flags in ELF file\n");
		return NULL;
	}
	if (hdr->machine != 0x2a) {
		printf("Invalid architecture %02x in ELF file\n", hdr->machine);
	}

	/* Print some debug info */
	printf("File size is %d bytes\n", sz);
	printf("	entry point	%08x\n", hdr->entry);
	printf("	ph offset	%08x\n", hdr->phoff);
	printf("	sh offset	%08x\n", hdr->shoff);
	printf("	flags		%08x\n", hdr->flags);
	printf("	ehsize		%08x\n", hdr->ehsize);
	printf("	phentsize	%08x\n", hdr->phentsize);
	printf("	phnum		%08x\n", hdr->phnum);
	printf("	shentsize	%08x\n", hdr->shentsize);
	printf("	shnum		%08x\n", hdr->shnum);
	printf("	shstrndx	%08x\n", hdr->shstrndx);

	/* Locate the string table; SH elf files ought to have
	   two string tables, one for section names and one for object
	   string names. We'll look for the latter. */
	shdrs = (struct elf_shdr_t *)(img + hdr->shoff);
	stringtab = NULL;
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].type == SHT_STRTAB
				&& i != hdr->shstrndx) {
			stringtab = (char*)(img + shdrs[i].offset);
		}
	}
	if (!stringtab) {
		printf("ELF contains no object string table\n");
		return NULL;
	}

	/* Locate the symbol table */
	symtabhdr = NULL;
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].type == SHT_SYMTAB
				|| shdrs[i].type == SHT_DYNSYM) {
			symtabhdr = shdrs+i;
			break;
		}
	}
	if (!symtabhdr) {
		printf("ELF contains no symbol table\n");
		return NULL;
	}
	symtab = (struct elf_sym_t *)(img + symtabhdr->offset);
	symtabsize = symtabhdr->size / sizeof(struct elf_sym_t);

	/* Relocate symtab entries for quick access */
	for (i=0; i<symtabsize; i++) {
		symtab[i].name = (uint32)(stringtab + symtab[i].name);
		printf("SYM: %s / %08x / %08x / %d\r\n",
			(char*)symtab[i].name, symtab[i].value,
			symtab[i].size, symtab[i].shndx);
	}

	for (i=0; i<hdr->shnum; i++) {
		printf("  Section %d: (%08x/%08x)\n", i, shdrs[i].name, shdrs[i].type);
	}

	/* Build the final memory image */
	sz = 0;
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].flags & SHF_ALLOC) {
			shdrs[i].addr = sz;
			sz += shdrs[i].size;
			if (shdrs[i].addralign && (shdrs[i].addr % shdrs[i].addralign)) {
				shdrs[i].addr =
					(shdrs[i].addr + shdrs[i].addralign)
					& ~(shdrs[i].addralign-1);
			}
		}
	}
	printf("Final image is %d bytes\n", sz);
	imgout = malloc(sz);
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].flags & SHF_ALLOC) {
			if (shdrs[i].type == SHT_NOBITS) {
				printf("%d:  setting %d bytes of zeros at %08x\n",
					i, shdrs[i].size, shdrs[i].addr);
				memset(imgout+shdrs[i].addr, 0, shdrs[i].size);
			}
			else {
				printf("%d:  copying %d bytes from %08x to %08x\n",
					i, shdrs[i].size, shdrs[i].offset, shdrs[i].addr);
				memcpy(imgout+shdrs[i].addr,
					img+shdrs[i].offset,
					shdrs[i].size);
			}
		}
	}

	/* Find the RELA section; FIXME: More than one RELA section, REL sections */
	reltab = NULL;
	/*for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].type == SHT_RELA) {
			reltab = (struct elf_rela_t *)(img + shdrs[i].offset);
			break;
		}
	}
	if (!reltab) {
		printf("ELF contains no RELA section (did you use -r?)\n");
		return NULL;
	}
	reltabsize = shdrs[i].size / sizeof(struct elf_rela_t); */

	/* Process the relocations */
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].type != SHT_RELA) continue;

		reltab = (struct elf_rela_t *)(img + shdrs[i].offset);
		reltabsize = shdrs[i].size / sizeof(struct elf_rela_t);
		sect = shdrs[i].info;
		
		printf("Relocating on section %d\r\n", sect);
		
		for (j=0; j<reltabsize; j++) {
			int sym;

			if (ELF32_R_TYPE(reltab[j].info) != R_SH_DIR32) {
				printf("ELF contains unknown RELA type %02x\r\n",
					ELF32_R_TYPE(reltab[j].info));
				return NULL;
			}

			sym = ELF32_R_SYM(reltab[j].info);
			printf("  Writing REL %08x(%08x+%08x+%08x+%08x) -> %08x\r\n",
				vma + shdrs[symtab[sym].shndx].addr + symtab[sym].value + reltab[j].addend,
				vma, shdrs[symtab[sym].shndx].addr, symtab[sym].value, reltab[j].addend,
				vma + shdrs[sect].addr + reltab[j].offset);
			*((uint32*)(imgout
				+ shdrs[sect].addr		/* assuming 1 == .text */
				+ reltab[j].offset))
				+=	  vma
					+ shdrs[symtab[sym].shndx].addr
					+ symtab[sym].value
					+ reltab[j].addend;
		}
	}

	/* Look for the kernel negotiation symbols and deal with that */
	{
		int mainsym, getsvcsym, notifysym;

		mainsym = find_sym("_ko_main", symtab, symtabsize);
		if (mainsym < 0) {
			printf("ELF contains no _ko_main\n");
			return NULL;
		}

		getsvcsym = find_sym("_ko_get_svc", symtab, symtabsize);
		if (mainsym < 0) {
			printf("ELF contains no _ko_get_svc\n");
			return NULL;
		}

		notifysym = find_sym("_ko_notify", symtab, symtabsize);
		if (notifysym < 0) {
			printf("ELF contains no _ko_notify\n");
			return NULL;
		}

		/* Patch together getsvc and notify for now */
		*((uint32*)(imgout
			+ shdrs[symtab[getsvcsym].shndx].addr
			+ symtab[getsvcsym].value))
			= vma
			+ shdrs[symtab[notifysym].shndx].addr
			+ symtab[notifysym].value;
	}

	free(img);
	*outsz = sz;
	return (void*)imgout;
}

void main(int argc, char **argv) {
	FILE *f;
	void *out;
	int sz;

	f = fopen(argv[1], "r");
	if (!f) {
		perror("Can't open input file");
		return;
	}

	out = elf_load(f, 0x8c010000, &sz);

	f = fopen(argv[2], "w");
	fwrite(out, sz, 1, f);
	fclose(f);
}

