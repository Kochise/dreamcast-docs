SECTIONS {
	.driverdata ALIGN(32): { _driver = . ; *(.data) }
}
