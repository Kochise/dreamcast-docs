#include "sh4sim.h"

#include <stdarg.h>

#include "bfd.h"
#include "dis-asm.h"	/* Included from GDB 5.0 */

/* These are supposed to be defined in libbfd, damn it */
bfd_vma bfd_getl16(const unsigned char *bytes) {
	return ((int)bytes[0])
		| (((int)bytes[1]) << 8);
}

bfd_vma bfd_getl32(const unsigned char *bytes) {
	return ((int)bytes[0])
		| (((int)bytes[1]) << 8)
		| (((int)bytes[2]) << 16)
		| (((int)bytes[3]) << 24);
}

bfd_vma bfd_getb16(const unsigned char *bytes) { return 0; }
bfd_vma bfd_getb32(const unsigned char *bytes) { return 0; }

static char output_buffer[2048] = {0};
static int printf_to_string(int nothing, char *fmt, ...) {
	va_list		args;
	int		rv;

	va_start(args, fmt);
	rv = vsprintf(output_buffer + strlen(output_buffer), fmt, args);
	va_end(args);

	return rv;
}

/* "read memory", hehe */
static int read_mem(bfd_vma memaddr, bfd_byte *myaddr, unsigned int len,
		struct disassemble_info *info) {
	return sim_read(memaddr, len, myaddr);
}

static void mem_error(int status, bfd_vma memaddr,
		struct disassemble_info *info) {
	printf("Memory read error at %08x\n", memaddr);
}

static void print_addr(bfd_vma addr, struct disassemble_info *info) {
	printf_to_string(0, "%08x", addr);
}



static disassemble_info info;

void disasm_init() {
	INIT_DISASSEMBLE_INFO_NO_ARCH(info, stdout, (fprintf_ftype)printf_to_string);
	info.flavour = bfd_mach_sh4;
	info.mach = bfd_mach_sh4;
	info.read_memory_func = read_mem;
	info.memory_error_func = mem_error;
	info.print_address_func = print_addr;
}

char* disasm_insn(uint32 addr) {
	bfd_vma memaddr = addr;

	output_buffer[0] = '\0';
	print_insn_shl(memaddr, &info);
	return output_buffer;
}

