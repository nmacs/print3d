TARGETS = 

TARGETS += MAX31855.sym
TARGETS += STM32F1DISCOVERY.sym
TARGETS += A3982.sym

DJBOXSYM := $(CURDIR)/../../tools/djboxsym

all: $(TARGETS)

%.sym: %.symdef
	$(DJBOXSYM) $< > $@