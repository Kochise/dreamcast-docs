@cd %_flatreleasedir%
@if not exist nk.bin goto error
@dumpnk nk.bin nk.raw
@gore2 nk.raw 0winceos.bin
@goto exit
:error
@echo NK.BIN not found.  Please run "makeimg" before running "gore".
:exit
