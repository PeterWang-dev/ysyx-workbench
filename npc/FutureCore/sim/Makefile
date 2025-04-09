# Variables Definition
TOPNAME ?= FutureCore
NPC_HOME ?=

## Source file path
VSRC_DIR = $(abspath ./vsrc)
VSRCS = $(wildcard $(VSRC_DIR)/*.sv)
# INC_PATH ?=
CSRC_DIR = $(abspath ./csrc)
LIB_DIR = $(CSRC_DIR)/lib
CSRC_DIRS = $(CSRC_DIR) $(LIB_DIR)
CSRCS = $(foreach dir, $(CSRC_DIRS), $(wildcard $(dir)/*.cpp))
# SRC_AUTO_BIND = $(abspath ./auto_bind.cpp)
# CSRCS += $(SRC_AUTO_BIND)

## Output path
OBJ_DIR = obj_dir
BIN = $(abspath ./$(TOPNAME)).out

## Compiler flags
# INCFLAGS += $(addprefix -I, $(INC_PATH))
# CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

## Verilator path and flags
VERILATOR = verilator
VERILATOR_COVERAGE = verilator_coverage
VERILATOR_FLAGS := -cc --exe --trace -MMD -MP \
					-Wall -Wno-fatal -O3 \
					--x-assign fast --x-initial fast --noassert --coverage
#					$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS))

# Build Rules
default: run

build: $(BIN)

dependencies: $(VSRCS) $(CSRCS)
	@echo
	@echo "----------- Verilating ------------"
	$(VERILATOR) $(VERILATOR_FLAGS) \
		--top-module $(TOPNAME) $^ \
		--Mdir $(OBJ_DIR) -o $(abspath $(BIN))
	@echo "-------- obj_dir Generated --------"
	@echo

run: $(BIN)
	@echo
	@echo "-------- Verilator tracing --------"
	@echo "------------ Running --------------"
	-rm -r logs
	$^ +trace
	@echo "----------- Coveraging ------------"
	-rm -r logs/annotated
	$(VERILATOR_COVERAGE) --annotate logs/annotated logs/coverage.dat
	@echo "-------------- Done ---------------"
	@echo "To see waveforms, open vlt_dump.vcd in a waveform viewer"
	@echo

verilog:
	make -C $(NPC_HOME) verilog

clean:
	-rm $(BIN)
	-rm -r $(OBJ_DIR)
	-rm -r logs

clean-verilog:
	-rm -r $(VSRC_DIR)

clean-all: clean clean-verilog

# $(BIN): $(VSRC) $(CSRCS) $(SRC_AUTO_BIND) $(NVBOARD_ARCHIVE)
$(BIN): $(VSRCS) $(CSRCS)
	@echo
	@echo "----- Verilating and Building -----"
	$(VERILATOR) --build $(VERILATOR_FLAGS) \
		--top-module $(TOPNAME) $^ \
		--Mdir $(OBJ_DIR) -o $(abspath $(BIN))
	@echo "------ Executable Generated -------"
	@echo

$(VSRC_DIR):
	$(error $(VSRC_DIR) is not found! Use 'make verilog' to generate it)

# $(SRC_AUTO_BIND): $(NXDC_FILES)
# 	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# # Include NVBoard
# include $(NVBOARD_HOME)/scripts/nvboard.mk

.PHONY: default all build dependencies run verilog clean clean-verilog clean-all