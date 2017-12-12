BUILD_DIR ?= build
TARGET    ?= STM32L0X2
VERSION    = 10

STM_DIR  ?= lib/stm/
include lib/stm/init.mk

LD_LINKER_FILE = "lib/blocks/.ld/$(TARGET).ld"
include lib/stm/stm.mk
LD_FLAGS += -Wl,-Llib/blocks/.ld

INCLUDE_PATHS += lib/blocks/
INCLUDES = $(INCLUDE_PATHS:%=-I%)

C_FLAGS += $(INCLUDES)

all: $(BUILD_DIR)/fw.bin
	@echo Inserting Config
	$(shell lib/blocks/.tools/insert-conf.py -v $(VERSION) -f ./build/fw.bin -o ./build/fw.flash)
	
$(BUILD_DIR)/vendor.o: main.c
	@echo CC $@
	mkdir -p `dirname $@`
	$(CC) $(C_FLAGS) -c $< -o $@

$(BUILD_DIR)/fw.o: $(BUILD_DIR)/vendor.o
	@echo LD $@
	$(CC) $(C_FLAGS) $(LD_FLAGS) lib/blocks/platform_$(TARGET).o lib/stm/stm_$(TARGET).o $< -o build/fw.o
	
$(BUILD_DIR)/fw.bin: $(BUILD_DIR)/fw.o
	@echo objcopy
	$(PREFIX)objcopy -O binary $< $@
