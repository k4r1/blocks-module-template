UCTARGET ?= STM32L0X2

ifeq ($(UCTARGET),STM32L0X2)
  TARGET = STM32L052xx
  FAMILY = STM32L0xx
  CFLAGS = -mcpu=cortex-m0plus -march=armv6-m -mfloat-abi=soft
else
  TARGET = STM32L476xx
  FAMILY = STM32L4xx
  CFLAGS = -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=softfp -mfpu=fpv4-sp-d16
endif

PREFIX = arm-none-eabi
BUILDDIR = build

CC = $(PREFIX)-gcc

CFLAGS += -mabi=aapcs -mthumb -mlittle-endian -mno-unaligned-access -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-builtin -w -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g3 -ggdb -std=gnu11 -pedantic -D$(TARGET) -nostartfiles -nodefaultlibs -nostdlib

LDFLAGS = -Xlinker --gc-sections -Wl,-Map,".ld/$(UCTARGET).map",-L.ld --specs=nano.specs -T ".ld/$(UCTARGET).ld"

STMINC = -Ilib/stm/ -Ilib/stm/hal/$(FAMILY)_HAL_Driver/Inc -Ilib/stm/hal/CMSIS/Device/ST/$(FAMILY)/Include/ -Ilib/stm/hal/CMSIS/Include -Istm/
BLKINC = -Ilib/blocks/

all: $(BUILDDIR)/fw.bin
	@echo Inserting Config
	$(shell .tools/insert-conf.py -c .config/config.ini -b ./build/fw.bin -o ./build/fw.flash)
	
$(BUILDDIR)/vendor.o: main.c
	@echo CC $@
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(STMINC) $(BLKINC) -c $< -o $@
	

$(BUILDDIR)/fw.o: $(BUILDDIR)/vendor.o
	@echo LD $@
	$(CC) $(CFLAGS) $(LDFLAGS) lib/blocks/platform_$(UCTARGET).o lib/stm/stm_$(UCTARGET).o $< -o build/fw.o
	
$(BUILDDIR)/fw.bin: $(BUILDDIR)/fw.o
	@echo objcopy
	$(PREFIX)-objcopy -O binary $< $@
