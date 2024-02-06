SIM_DIR = $(abspath ./futurecore/sim)
VSRC_DIR = $(SIM_DIR)/vsrc

export PATH := $(PATH):$(abspath ./utils)

test:
	mill -i __.test

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(VSRC_DIR)
	mill -i __.runMain Elaborate -td $(VSRC_DIR)

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
	-rm -rf $(VSRC_DIR)
	make -C $(SIM_DIR) clean

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	make -C $(SIM_DIR) run

.PHONY: test verilog help compile bsp reformat checkformat clean sim

-include ../Makefile
