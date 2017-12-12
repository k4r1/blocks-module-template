BUILD_DIR  ?= build/
TARGET     ?= STM32L0X2
VERSION    ?= 1

STM_DIR    ?= lib/stm/
BLOCKS_DIR ?= lib/blocks/
include lib/stm/init.mk
include lib/blocks/init.mk

CFILES += main.c
INCLUDE_PATHS += .

include lib/stm/stm.mk
include lib/blocks/blocks.mk
