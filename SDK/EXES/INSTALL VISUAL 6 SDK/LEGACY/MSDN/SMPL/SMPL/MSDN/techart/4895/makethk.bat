thunk -t thk timer.thk -o thk3216.asm

ml /DIS_32 /c /W3 /nologo /coff /Fo thk32.obj thk3216.asm

ml /DIS_16 /c /W3 /nologo       /Fo thk16.obj thk3216.asm

