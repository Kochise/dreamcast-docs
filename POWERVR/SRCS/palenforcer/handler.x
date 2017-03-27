SECTIONS {
	.handlerdata : { _break_handler = . ; *(.data) }
}
