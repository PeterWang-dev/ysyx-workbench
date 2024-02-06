# Variables Definition
YSYX_HOME ?= $(abspath $(CURDIR)/../../../../../)
DLCO_ROOT = $(YSYX_HOME)/dlco-lab
TOPNAME ?=
INC_PATH ?=

## Source file path
VSRC = $(DLCO_HOME)/src/main/verilog/$(TOPNAME).sv
CSRCS = $(shell find $(abspath ./) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
SRC_AUTO_BIND = $(abspath ./auto_bind.cpp)
CSRCS += $(SRC_AUTO_BIND)

## Output file path
OUTPUT_DIR = $(abspath $(DLCO_HOME)/bin/)
OBJ_DIR = $(abspath ./obj_dir)
BIN = $(OUTPUT_DIR)/$(TOPNAME)

## Verilator path and flags
VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

## Verilator CFLAGS and LDFLAGS
INCFLAGS += $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

# Build Rules
.PHONY: default all test build run clean

default: run

all: clean test elaborate build run

test:
	cd $(DLCO_HOME) && sbt 'testOnly Sim$(TOPNAME)'

elaborate: $(VSRC)

build: $(SRC_AUTO_BIND) $(BIN)

run: $(BIN)
	@$^

clean:
	rm -f $(VSRC)
	rm -f $(SRC_AUTO_BIND)
	rm -rf $(OBJ_DIR)
	rm -f $(BIN)

# Include NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

$(VSRC): $(DLCO_HOME)/src/main/scala/$(TOPNAME).scala
	cd $(DLCO_HOME) && sbt 'runMain $(TOPNAME)'

$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

$(BIN): $(VSRC) $(CSRCS) $(SRC_AUTO_BIND) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(shell mkdir -p $(OUTPUT_DIR))
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))