TARGET = sound1
OBJECTS = ifork.obj sound1.obj 
HEADOBJ = ghead.obj 
SYSOBJ = $(TOOL86)\obj\gdummy.obj

.asm.obj:
	m86k $*

$(TARGET).eva: $(HEADOBJ) $(OBJECTS)
	l86k $(HEADOBJ) $(SYSOBJ) -C=200 $(OBJECTS),$(TARGET).eva,,,

$(TARGET).h00: $(TARGET).eva
	e2h86k $(TARGET)

$(TARGET).hex: $(TARGET).h00
	h2bin $(TARGET).h00
	
clean:
	del *.obj
	del *.hex
	del *.h00
	del *.eva
	del *.bin
