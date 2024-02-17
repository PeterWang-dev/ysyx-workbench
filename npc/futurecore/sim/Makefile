# Variables Definition
TOPNAME ?= FutureCore

## Source file path
VSRC_DIR = $(abspath vsrc)
VSRC = $(VSRC_DIR)/$(TOPNAME).v
INC_DIR ?=
CSRC_DIR = $(abspath csrc)
CSRCS = $(wildcard $(CSRC_DIR)/*.cpp)
# SRC_AUTO_BIND = $(abspath ./auto_bind.cpp)
# CSRCS += $(SRC_AUTO_BIND)

## Output path
OBJ_DIR = obj_dir
BIN = $(abspath ./$(TOPNAME))

## Compiler flags
CXXFLAGS += -I $(INCFLAGS)
LDFLAGS +=

## Verilator path and flags
VERILATOR = verilator
VERILATOR_COVERAGE = verilator_coverage
VERILATOR_FLAGS := -cc --exe -MMD -MP \
					-O3 --x-assign fast --x-initial fast --noassert --coverage \
					$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \

# Build Rules
default: run

build: $(BIN)

run: $(BIN)
	@echo
	@echo "-------- Verilator tracing --------"
	@echo

	@echo "------------ Running --------------"
	@echo
	@rm -r logs
	@mkdir -p logs
	@$^ +trace
	@echo

	@echo "----------- Coveraging ------------"
	@echo
	@rm -rf logs/annotated
	@$(VERILATOR_COVERAGE) --annotate logs/annotated logs/coverage.dat
	@echo

	@echo "-------------- Done ---------------"
	@echo "To see waveforms, open vlt_dump.vcd in a waveform viewer"
	@echo

clean:
	-rm $(BIN)
	-rm -r $(OBJ_DIR)

# $(BIN): $(VSRC) $(CSRCS) $(SRC_AUTO_BIND) $(NVBOARD_ARCHIVE)
$(BIN): $(VSRC) $(CSRCS)
	@echo
	@echo "----- Verilating and Building -----"
	$(VERILATOR) --build $(VERILATOR_FLAGS) \
		--top-module $(TOPNAME) $^ \
		--Mdir $(OBJ_DIR) -o $(abspath $(BIN))
	@echo "------ Executable Generated -------"
	@echo

$(VSRC):
	$(error $(VSRC) is not found! Use 'make verilog' to generate it)

# $(SRC_AUTO_BIND): $(NXDC_FILES)
# 	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# # Include NVBoard
# include $(NVBOARD_HOME)/scripts/nvboard.mk

.PHONY: default all build run clean