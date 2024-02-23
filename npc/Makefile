export PATH := $(PATH):$(abspath ./utils)

TOP_NAME = FutureCore
PRJ_DIR = $(shell echo $(TOP_NAME) | tr A-Z a-z)
SRC_DIR = $(PRJ_DIR)/src
SIM_DIR = $(PRJ_DIR)/sim

test:
	mill -i __.test

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(SIM_DIR)/vsrc
	mill -i __.runMain Elaborate -td $(SIM_DIR)/vsrc -O=debug

help:
	mill -i __.runMain Elaborate --help

compile:
	mill -i __.compile

bsp:
	mill -i mill.bsp.BSP/install

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

clean:
	-rm $(SIM_DIR)/vsrc/$(TOP_NAME).sv
	make -C $(SIM_DIR) clean

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	make -C $(SIM_DIR) run

.PHONY: test verilog help compile bsp reformat checkformat clean sim

-include ../Makefile
