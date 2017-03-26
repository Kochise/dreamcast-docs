/* KallistiOS 1.2.0

   elf.c
   (c)2000-2001 Dan Potter
*/

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <kos/fs.h>
#include <os/elf.h>
#include <os/process.h>

CVSID("$Id: elf.c,v 1.2 2002/01/06 00:40:33 bardtx Exp $");

/* Finds a given symbol in a relocated ELF symbol table */
static int find_sym(char *name, struct elf_sym_t* table, int tablelen) {
	int i;
	for (i=0; i<tablelen; i++) {
		if (!strcmp((char*)table[i].name, name))
			return i;
	}
	return -1;
}

/* Pass in a file descriptor from the virtual file system, and the
   result will be NULL if the file cannot be loaded, or a pointer to
   the loaded and relocated executable otherwise. The second variable
   will be set to the entry point. */
/* There's a lot of shit in here that's not documented or very poorly
   documented by Intel.. I hope that this works for future compilers. */
elf_prog_t *elf_load(uint32 fd) {
	elf_prog_t		*out;
	char			*img, *imgout;
	int			sz, i, j, sect; 
	struct elf_hdr_t	*hdr;
	struct elf_shdr_t	*shdrs, *symtabhdr;
	struct elf_sym_t	*symtab;
	int			symtabsize;
	struct elf_rela_t	*reltab;
	int			reltabsize;
	char			*stringtab;
	uint32			vma;

	/* Load the file: needs to change to just load headers */
	sz = fs_total(fd);
	/* printf("Loading ELF file of size %d\r\n", sz); */
	
	img = malloc(sz);
	if (img == NULL) {
		dbglog(DBG_ERROR, "elf_load: can't allocate %d bytes for ELF load\r\n", sz);
		fs_close(fd);
		return NULL;
	}
	fs_read(fd, img, sz);
	fs_close(fd);

	/* Header is at the front */
	hdr = (struct elf_hdr_t *)(img+0);
	if (hdr->ident[0] != 0x7f || strncmp(hdr->ident+1, "ELF", 3)) {
		dbglog(DBG_ERROR, "elf_load: file is not a valid ELF file\r\n");
		hdr->ident[4] = 0;
		dbglog(DBG_ERROR, "   hdr->ident is %d/%s\r\n", hdr->ident[0], hdr->ident+1);
		free(img);
		return NULL;
	}
	if (hdr->ident[4] != 1 || hdr->ident[5] != 1) {
		dbglog(DBG_ERROR, "elf_load: invalid architecture flags in ELF file\r\n");
		free(img);
		return NULL;
	}
	if (hdr->machine != 0x2a) {
		dbglog(DBG_ERROR, "elf_load: invalid architecture %02x in ELF file\r\n", hdr->machine);
		free(img);
		return NULL;
	}

	/* Print some debug info */
	/* printf("File size is %d bytes\r\n", sz);
	printf("	entry point	%08x\r\n", hdr->entry);
	printf("	ph offset	%08x\r\n", hdr->phoff);
	printf("	sh offset	%08x\r\n", hdr->shoff);
	printf("	flags		%08x\r\n", hdr->flags);
	printf("	ehsize		%08x\r\n", hdr->ehsize);
	printf("	phentsize	%08x\r\n", hdr->phentsize);
	printf("	phnum		%08x\r\n", hdr->phnum);
	printf("	shentsize	%08x\r\n", hdr->shentsize);
	printf("	shnum		%08x\r\n", hdr->shnum);
	printf("	shstrndx	%08x\r\n", hdr->shstrndx); */

	/* Locate the string table; SH elf files ought to have
	   two string tables, one for section names and one for object
	   string names. We'll look for the latter. */
	shdrs = (struct elf_shdr_t *)(img + hdr->shoff);
	stringtab = NULL;
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].type == SHT_STRTAB && i != hdr->shstrndx) {
			stringtab = (char*)(img + shdrs[i].offset);
		}
	}
	if (!stringtab) {
		dbglog(DBG_ERROR, "elf_load: ELF contains no object string table\r\n");
		free(img);
		return NULL;
	}

	/* Locate the symbol table */
	symtabhdr = NULL;
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].type == SHT_SYMTAB || shdrs[i].type == SHT_DYNSYM) {
			symtabhdr = shdrs+i;
			break;
		}
	}
	if (!symtabhdr) {
		dbglog(DBG_ERROR, "elf_load: ELF contains no symbol table\r\n");
		return NULL;
	}
	symtab = (struct elf_sym_t *)(img + symtabhdr->offset);
	symtabsize = symtabhdr->size / sizeof(struct elf_sym_t);

	/* Relocate symtab entries for quick access */
	for (i=0; i<symtabsize; i++)
		symtab[i].name = (uint32)(stringtab + symtab[i].name);

	/* Build the final memory image */
	sz = 0;
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].flags & SHF_ALLOC) {
			shdrs[i].addr = sz;
			sz += shdrs[i].size;
			if (shdrs[i].addralign && (shdrs[i].addr % shdrs[i].addralign)) {
				uint32 orig = shdrs[i].addr;
				shdrs[i].addr = (shdrs[i].addr + shdrs[i].addralign)
					& ~(shdrs[i].addralign-1);
				sz += shdrs[i].addr - orig;
			}
		}
	}
	/* printf("Final image is %d bytes\n", sz); */
	out = malloc(sizeof(elf_prog_t));
	if (out == NULL) {
		dbglog(DBG_ERROR, "elf_load: can't allocate %d bytes for ELF program structure\r\n",
			sizeof(elf_prog_t));
		free(img);
		return NULL;
	}
	out->data = imgout = malloc(sz);
	if (out->data == NULL) {
		dbglog(DBG_ERROR, "elf_load: can't allocate %d bytes for ELF program data\r\n", sz);
		free(out);
		free(img);
		return NULL;
	}
	out->size = sz;
	vma = (uint32)imgout;
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].flags & SHF_ALLOC) {
			if (shdrs[i].type == SHT_NOBITS) {
				/*printf("  setting %d bytes of zeros at %08x\r\n",
					shdrs[i].size, shdrs[i].addr);*/
				memset(imgout+shdrs[i].addr, 0, shdrs[i].size);
			}
			else {
				/*printf("  copying %d bytes from %08x to %08x\r\n",
					shdrs[i].size, shdrs[i].offset, shdrs[i].addr);*/
				memcpy(imgout+shdrs[i].addr,
					img+shdrs[i].offset,
					shdrs[i].size);
			}
		}
	}

	/* Process the relocations */
	reltab = NULL;
	for (i=0; i<hdr->shnum; i++) {
		if (shdrs[i].type != SHT_RELA) continue;

		reltab = (struct elf_rela_t *)(img + shdrs[i].offset);
		reltabsize = shdrs[i].size / sizeof(struct elf_rela_t);
		sect = shdrs[i].info;
		
		/* printf("Relocating on section %d\r\n", sect); */
		
		for (j=0; j<reltabsize; j++) {
			int sym;

			if (ELF32_R_TYPE(reltab[j].info) != R_SH_DIR32) {
				dbglog(DBG_ERROR, "elf_load: ELF contains unknown RELA type %02x\r\n",
					ELF32_R_TYPE(reltab[j].info));
				free(out->data);
				free(out);
				free(img);
				return NULL;
			}

			sym = ELF32_R_SYM(reltab[j].info);
			/* printf("  Writing REL %08x(%08x+%08x+%08x+%08x) -> %08x\r\n",
				vma + shdrs[symtab[sym].shndx].addr + symtab[sym].value + reltab[j].addend,
				vma, shdrs[symtab[sym].shndx].addr, symtab[sym].value, reltab[j].addend,
				vma + shdrs[sect].addr + reltab[j].offset); */
			*((uint32*)(imgout
				+ shdrs[sect].addr		/* assuming 1 == .text */
				+ reltab[j].offset))
				+=	  vma
					+ shdrs[symtab[sym].shndx].addr
					+ symtab[sym].value
					+ reltab[j].addend;
		}
	}
	if (reltab == NULL) {
		dbglog(DBG_WARNING, "elf_load warning: found no RELA sections; did you forget -r?\r\n");
	}

	/* Look for the kernel negotiation symbols and deal with that */
	{
		int mainsym, getsvcsym, notifysym;

		mainsym = find_sym("_ko_main", symtab, symtabsize);
		if (mainsym < 0) {
			dbglog(DBG_ERROR, "elf_load: ELF contains no _ko_main\r\n");
			free(out->data);
			free(out);
			free(img);
			return NULL;
		}

		getsvcsym = find_sym("_ko_get_svc", symtab, symtabsize);
		if (mainsym < 0) {
			dbglog(DBG_ERROR, "elf_load: ELF contains no _ko_get_svc\r\n");
			free(out->data);
			free(out);
			free(img);
			return NULL;
		}

		notifysym = find_sym("_ko_notify", symtab, symtabsize);
		if (notifysym < 0) {
			dbglog(DBG_ERROR, "elf_load: ELF contains no _ko_notify\r\n");
			free(out->data);
			free(out);
			free(img);
			return NULL;
		}

		out->ko_main = (int (*)(int,char**))(vma + shdrs[symtab[mainsym].shndx].addr
			+ symtab[mainsym].value);

		/* printf("Patching ko_getsvc (%08x) to ko_notify (%08x)\r\n",
			vma + shdrs[symtab[getsvcsym].shndx].addr
			+ symtab[getsvcsym].value,
			vma
			+ shdrs[symtab[notifysym].shndx].addr
			+ symtab[notifysym].value); */
		*((uint32*)(imgout
			+ shdrs[symtab[getsvcsym].shndx].addr
			+ symtab[getsvcsym].value))
			= (uint32)ps_multiplexer;
	}

	free(img);

	dbglog(DBG_DEBUG, "elf_load final ELF stats: memory image at %08x, size %08x\r\n\tentry pt %08x\r\n", out->data, out->size, out->ko_main);
	
	return out;
}

/* Free a loaded ELF program */
void elf_free(elf_prog_t *prog) {
	free(prog->data);
	free(prog);
}

