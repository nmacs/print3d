.EXPORT_ALL_VARIABLES:

#VERBOSE := 1
#V := 1
USE_VERBOSE_COMPILE := yes

ROOT         := $(CURDIR)
HOST_NCPU    := $(shell if [ -f /proc/cpuinfo ]; then n=`grep -c processor /proc/cpuinfo`; if [ $$n -gt 1 ];then expr $$n \* 2; else echo $$n; fi; else echo 1; fi)

TOOLCHAIN    := $(ROOT)/toolchain
OPENOCD_TAR  := $(TOOLCHAIN)/openocd-0.7.0.tar.bz2
OPENOCD_DIR  := $(TOOLCHAIN)/openocd-0.7.0
COMPILER_TAR := $(TOOLCHAIN)/arm-2011.09-69-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
COMPILER_DIR := $(TOOLCHAIN)/arm-2011.09
OPENOCD      := $(OPENOCD_DIR)/bin/openocd
FIRMWARE_DIR := $(ROOT)/firmware/target_stm32f1xx

TARGET_CC     := $(COMPILER_DIR)/bin/arm-none-eabi-gcc
TARGET_AR     := $(COMPILER_DIR)/bin/arm-none-eabi-ar
TARGET_RANLIB := $(COMPILER_DIR)/bin/arm-none-eabi-ranlib
TARGET_LD     := $(COMPILER_DIR)/bin/arm-none-eabi-gcc
TARGET_CP     := $(COMPILER_DIR)/bin/arm-none-eabi-objcopy
TARGET_OD     := $(COMPILER_DIR)/bin/arm-none-eabi-objdump
TARGET_SIZE   := $(COMPILER_DIR)/bin/arm-none-eabi-size

MAKEARCH      := $(MAKE) CC=$(TARGET_CC) AR=$(TARGET_AR) RANLIB=$(TARGET_RANLIB) LD=$(TARGET_LD) CP=$(TARGET_CP) OD=$(TARGET_OD) SIZE=$(TARGET_SIZE)

TAR          := tar

TOOLCHAIN_TARGETS := openocd compiler

.PHONY: all
all: $(TOOLCHAIN_TARGETS) firmware

.PHONY: firmware
firmware: $(TOOLCHAIN_TARGETS)
	$(MAKEARCH) -C $(FIRMWARE_DIR)

firmware_%: $(TOOLCHAIN_TARGETS)
	$(MAKEARCH) -C $(FIRMWARE_DIR) $@

openocd: $(OPENOCD_DIR)/.o

$(OPENOCD_DIR)/.o: $(OPENOCD_DIR)/Makefile
	$(MAKE) -C $(OPENOCD_DIR) -j$(HOST_NCPU)
	$(MAKE) -C $(OPENOCD_DIR) install
	touch $(OPENOCD_DIR)/.o

OPENOCD_CONFIGURE_PARAMS := --verbose --enable-maintainer-mode --enable-stlink --enable-verbose-usb-io \
                            --enable-verbose-usb-comms --enable-verbose --enable-verbose-jtag-io \
                            --prefix=$(OPENOCD_DIR)/bin

$(OPENOCD_DIR)/Makefile: $(OPENOCD_DIR)/.t Makefile
	cd $(OPENOCD_DIR); ./configure $(OPENOCD_CONFIGURE_PARAMS) || exit 1

$(OPENOCD_DIR)/.t:
	cd $(TOOLCHAIN); \
	$(TAR) -xf $(OPENOCD_TAR); \
	touch $(OPENOCD_DIR)/.t

.PHONY: compiler
compiler: $(COMPILER_DIR)/.t Makefile

$(COMPILER_DIR)/.t:
	cd $(TOOLCHAIN); \
	$(TAR) -xf $(COMPILER_TAR); \
	touch $(COMPILER_DIR)/.t

.PHONY: distclean
distclean:
	rm -rf $(OPENOCD_DIR)
	rm -rf $(COMPILER_DIR)

.PHONY: clean
clean:
	$(MAKEARCH) -C $(FIRMWARE_DIR) clean