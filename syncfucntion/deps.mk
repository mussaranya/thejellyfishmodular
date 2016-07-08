ifeq (,$(filter $(MAKECMDGOALS),clean tags)) # It's a logical OR ;)
IGNORE  := $(shell mkdir -p $(DEPDIR))
DEPS    := $(patsubst %.c,$(DEPDIR)/%.d,$(SOURCES))
DEPS    += $(patsubst %.S,$(DEPDIR)/%.d,$(ASMSOURCES))
endif

