export PATH := $(PATH):$(abspath ./utils)

PRJ_NAME = FutureCore
SRC_DIR = $(PRJ_NAME)/src
SIM_DIR = $(SRC_DIR)/main/resources/sim

test:
	mill -i __.test

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(SIM_DIR)/vsrc
	mill -i __.runMain Elaborate -td $(SIM_DIR)/vsrc

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
