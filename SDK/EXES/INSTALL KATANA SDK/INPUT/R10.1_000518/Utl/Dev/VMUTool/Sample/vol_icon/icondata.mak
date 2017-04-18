TARGET = icondata
OBJECTS = icondata.obj 
HEADOBJ = 
SYSOBJ = 

.asm.obj:
	m86k $*

$(TARGET).eva: $(HEADOBJ) $(OBJECTS)
	l86k $(HEADOBJ) $(SYSOBJ) -C=000 $(OBJECTS),$(TARGET).eva,,,

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
