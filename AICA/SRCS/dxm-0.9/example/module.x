SECTIONS {
	.moduledata ALIGN(32): { _module = . ; *(.data) }
}
