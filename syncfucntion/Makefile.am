AUTOMAKE_OPTIONS = foreign

PROGRAM        := jelly_sync_input
SOURCES        := jelly_sync_input.c
ASMSOURCES     :=

OBJECTS        := $(patsubst %.c,%.o,$(SOURCES))
OBJECTS        += $(patsubst %.S,%.o,$(ASMSOURCES))

#all: $(PROGRAM).elf lst text eeprom
all-am: $(PROGRAM).hex

if WITH_AVRDUDE
#AVRDUDE_OPTS  = -U lfuse:w:0xe2:m # program CKDIV8
#AVRDUDE_OPTS  = -U lfuse:w:0x62:m # unprogram CKDIV8
upload: $(PROGRAM).hex
	$(AVRDUDE) $(AVRDUDE_PROGRAMMER) -p $(AVRDUDE_MCU) -U flash:w:$^ $(AVRDUDE_OPTS)
endif

DEPDIR   = .deps
$(eval include $(srcdir)/deps.mk)

$(DEPDIR)/%.d: %.[cS] %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -mmcu=$(MCU_TARGET) -MM -MF $@ $<
$(DEPDIR)/%.d: %.[cS]
	$(CC) $(CPPFLAGS) $(CFLAGS) -mmcu=$(MCU_TARGET) -MM -MF $@ $<

-include $(DEPS)
%.o: %.[cS] $(DEPDIR)/%.d
	$(CC) $(CPPFLAGS) $(CFLAGS) -mmcu=$(MCU_TARGET) -c -o $@ $<

$(PROGRAM).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -mmcu=$(MCU_TARGET) -Wl,-Map,$(PROGRAM).map -o $@ $^ $(LIBS)

clean:
	@rm -vrf .deps
	@rm -vrf *.o $(PROGRAM).elf *.eps *.png *.pdf *.bak
	@rm -vrf *.lst *.map $(EXTRA_CLEAN_FILES)

lst:  $(PROGRAM).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PROGRAM).hex
bin:  $(PROGRAM).bin
srec: $(PROGRAM).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PROGRAM)_eeprom.hex
ebin:  $(PROGRAM)_eeprom.bin
esrec: $(PROGRAM)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ \
	  || { echo empty $@ not generated; exit 0; }

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@ \
	  || { echo empty $@ not generated; exit 0; }

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@ \
	  || { echo empty $@ not generated; exit 0; }

EXTRA_CLEAN_FILES       = *.hex *.bin *.srec

