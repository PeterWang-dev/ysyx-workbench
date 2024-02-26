// Generated by CIRCT firtool-1.44.0
// Standard header to adapt well known macros to our needs.
`ifndef RANDOMIZE
  `ifdef RANDOMIZE_REG_INIT
    `define RANDOMIZE
  `endif // RANDOMIZE_REG_INIT
`endif // not def RANDOMIZE
`ifndef RANDOMIZE
  `ifdef RANDOMIZE_MEM_INIT
    `define RANDOMIZE
  `endif // RANDOMIZE_MEM_INIT
`endif // not def RANDOMIZE

// RANDOM may be set to an expression that produces a 32-bit random unsigned value.
`ifndef RANDOM
  `define RANDOM $random
`endif // not def RANDOM

// Users can define INIT_RANDOM as general code that gets injected into the
// initializer block for modules with registers.
`ifndef INIT_RANDOM
  `define INIT_RANDOM
`endif // not def INIT_RANDOM

// If using random initialization, you can also define RANDOMIZE_DELAY to
// customize the delay used, otherwise 0.002 is used.
`ifndef RANDOMIZE_DELAY
  `define RANDOMIZE_DELAY 0.002
`endif // not def RANDOMIZE_DELAY

// Define INIT_RANDOM_PROLOG_ for use in our modules below.
`ifndef INIT_RANDOM_PROLOG_
  `ifdef RANDOMIZE
    `ifdef VERILATOR
      `define INIT_RANDOM_PROLOG_ `INIT_RANDOM
    `else  // VERILATOR
      `define INIT_RANDOM_PROLOG_ `INIT_RANDOM #`RANDOMIZE_DELAY begin end
    `endif // VERILATOR
  `else  // RANDOMIZE
    `define INIT_RANDOM_PROLOG_
  `endif // RANDOMIZE
`endif // not def INIT_RANDOM_PROLOG_

// Include register initializers in init blocks unless synthesis is set
`ifndef SYNTHESIS
  `ifndef ENABLE_INITIAL_REG_
    `define ENABLE_INITIAL_REG_
  `endif // not def ENABLE_INITIAL_REG_
`endif // not def SYNTHESIS

// Include rmemory initializers in init blocks unless synthesis is set
`ifndef SYNTHESIS
  `ifndef ENABLE_INITIAL_MEM_
    `define ENABLE_INITIAL_MEM_
  `endif // not def ENABLE_INITIAL_MEM_
`endif // not def SYNTHESIS

// VCS coverage exclude_file
module regBank_combMem(	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  input  [4:0]  R0_addr,
  input         R0_en,
                R0_clk,
  input  [4:0]  R1_addr,
  input         R1_en,
                R1_clk,
  input  [4:0]  W0_addr,
  input         W0_en,
                W0_clk,
  input  [31:0] W0_data,
  output [31:0] R0_data,
                R1_data
);

  reg [31:0] Memory[0:31];	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  always @(posedge W0_clk) begin	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
    if (W0_en)	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
      Memory[W0_addr] <= W0_data;	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  end // always @(posedge)
  `ifdef ENABLE_INITIAL_MEM_	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
    reg [31:0] _RANDOM_MEM;	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
    initial begin	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
      `INIT_RANDOM_PROLOG_	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
      `ifdef RANDOMIZE_MEM_INIT	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
        for (logic [5:0] i = 6'h0; i < 6'h20; i += 6'h1) begin
          _RANDOM_MEM = `RANDOM;	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
          Memory[i[4:0]] = _RANDOM_MEM;	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
        end	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
      `endif // RANDOMIZE_MEM_INIT
    end // initial
  `endif // ENABLE_INITIAL_MEM_
  assign R0_data = R0_en ? Memory[R0_addr] : 32'bx;	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  assign R1_data = R1_en ? Memory[R1_addr] : 32'bx;	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
endmodule

module ProgramCounter(	// @[<stdin>:3:10]
  input         clock,	// @[<stdin>:4:11]
                reset,	// @[<stdin>:5:11]
  output [31:0] io_instAddr	// @[FutureCore/src/main/scala/futurecore/frontend/ProgramCounter.scala:29:21]
);

  reg [31:0] pc;	// @[FutureCore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19]
  always @(posedge clock) begin	// @[<stdin>:4:11]
    if (reset)	// @[<stdin>:4:11]
      pc <= 32'h80000000;	// @[FutureCore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19]
    else	// @[<stdin>:4:11]
      pc <= pc + 32'h4;	// @[FutureCore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19, :33:12]
  end // always @(posedge)
  `ifdef ENABLE_INITIAL_REG_	// @[<stdin>:3:10]
    `ifdef FIRRTL_BEFORE_INITIAL	// @[<stdin>:3:10]
      `FIRRTL_BEFORE_INITIAL	// @[<stdin>:3:10]
    `endif // FIRRTL_BEFORE_INITIAL
    logic [31:0] _RANDOM[0:0];	// @[<stdin>:3:10]
    initial begin	// @[<stdin>:3:10]
      `ifdef INIT_RANDOM_PROLOG_	// @[<stdin>:3:10]
        `INIT_RANDOM_PROLOG_	// @[<stdin>:3:10]
      `endif // INIT_RANDOM_PROLOG_
      `ifdef RANDOMIZE_REG_INIT	// @[<stdin>:3:10]
        _RANDOM[/*Zero width*/ 1'b0] = `RANDOM;	// @[<stdin>:3:10]
        pc = _RANDOM[/*Zero width*/ 1'b0];	// @[<stdin>:3:10, FutureCore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19]
      `endif // RANDOMIZE_REG_INIT
    end // initial
    `ifdef FIRRTL_AFTER_INITIAL	// @[<stdin>:3:10]
      `FIRRTL_AFTER_INITIAL	// @[<stdin>:3:10]
    `endif // FIRRTL_AFTER_INITIAL
  `endif // ENABLE_INITIAL_REG_
  assign io_instAddr = pc;	// @[<stdin>:3:10, FutureCore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19]
endmodule

module InstDecoder(	// @[<stdin>:15:10]
  input  [31:0] io_inst,	// @[FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:37:14]
  output [4:0]  io_rs1,	// @[FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:37:14]
                io_rs2,	// @[FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:37:14]
                io_rd,	// @[FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:37:14]
  output        io_writeEnable,	// @[FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:37:14]
                io_isImmidiate,	// @[FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:37:14]
                io_isEbreak	// @[FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:37:14]
);

  wire _GEN = io_inst[6:0] == 7'h13;	// @[FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:49:{17,25}]
  assign io_rs1 = io_inst[19:15];	// @[<stdin>:15:10, FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:39:20]
  assign io_rs2 = io_inst[24:20];	// @[<stdin>:15:10, FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:40:20]
  assign io_rd = io_inst[11:7];	// @[<stdin>:15:10, FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:41:20]
  assign io_writeEnable = _GEN;	// @[<stdin>:15:10, FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:49:25]
  assign io_isImmidiate = _GEN;	// @[<stdin>:15:10, FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:49:25]
  assign io_isEbreak = ~_GEN & io_inst[6:0] == 7'h73 & io_inst[20];	// @[<stdin>:15:10, FutureCore/src/main/scala/futurecore/frontend/InstDecoder.scala:46:18, :49:{17,25}, :55:33]
endmodule

module RegFile(	// @[<stdin>:42:10]
  input         clock,	// @[<stdin>:43:11]
  input  [4:0]  io_rs1Addr,	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
                io_rs2Addr,	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
  input         io_writeEnable,	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
  input  [4:0]  io_rdAddr,	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
  input  [31:0] io_rdData,	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
  output [31:0] io_rs1Data,	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
                io_rs2Data	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
);

  wire [31:0] _regBank_ext_R0_data;	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  wire [31:0] _regBank_ext_R1_data;	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  regBank_combMem regBank_ext (	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
    .R0_addr (io_rs1Addr),
    .R0_en   (1'h1),	// @[<stdin>:42:10]
    .R0_clk  (clock),
    .R1_addr (io_rs2Addr),
    .R1_en   (1'h1),	// @[<stdin>:42:10]
    .R1_clk  (clock),
    .W0_addr (io_rdAddr),
    .W0_en   (io_writeEnable),
    .W0_clk  (clock),
    .W0_data ((|io_rdAddr) ? io_rdData : 32'h0),	// @[FutureCore/src/main/scala/futurecore/backend/RegFile.scala:44:{33,44}]
    .R0_data (_regBank_ext_R0_data),
    .R1_data (_regBank_ext_R1_data)
  );
  assign io_rs1Data = (|io_rs1Addr) ? _regBank_ext_R0_data : 32'h0;	// @[<stdin>:42:10, FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20, :40:{20,32}, :44:33]
  assign io_rs2Data = (|io_rs2Addr) ? _regBank_ext_R1_data : 32'h0;	// @[<stdin>:42:10, FutureCore/src/main/scala/futurecore/backend/RegFile.scala:38:20, :41:{20,32}, :44:33]
endmodule

module ImmGenerator(	// @[<stdin>:63:10]
  input  [31:0] io_inst,	// @[FutureCore/src/main/scala/futurecore/backend/ImmGenerator.scala:31:16]
  output [31:0] io_immidiate	// @[FutureCore/src/main/scala/futurecore/backend/ImmGenerator.scala:31:16]
);

  assign io_immidiate = {{20{io_inst[31]}}, io_inst[31:20]};	// @[<stdin>:63:10, FutureCore/src/main/scala/futurecore/backend/ImmGenerator.scala:39:{14,19,28,39}]
endmodule

// external module EbreakCall

module Adder(	// @[<stdin>:125:10]
  input  [31:0] io_operand1,	// @[FutureCore/src/main/scala/futurecore/backend/Adder.scala:31:14]
                io_operand2,	// @[FutureCore/src/main/scala/futurecore/backend/Adder.scala:31:14]
  output [31:0] io_result	// @[FutureCore/src/main/scala/futurecore/backend/Adder.scala:31:14]
);

  assign io_result = io_operand1 + io_operand2;	// @[<stdin>:125:10, FutureCore/src/main/scala/futurecore/backend/Adder.scala:33:28]
endmodule

module FutureCore(	// @[<stdin>:134:10]
  input         clock,	// @[<stdin>:135:11]
                reset,	// @[<stdin>:136:11]
  input  [31:0] io_instIn,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
  output [31:0] io_instAddrOut,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
                io_debug_pcInstAddr,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
  output [4:0]  io_debug_instDecRs1,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
                io_debug_instDecRs2,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
                io_debug_instDecRd,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
  output        io_debug_instDecWriteEnable,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
                io_debug_instDecIsImmidiate,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
                io_debug_instDecIsEbreak,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
  output [31:0] io_debug_regFileRs1Data,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
                io_debug_regFileRs2Data,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
                io_debug_immGenImmidiate,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
                io_debug_adderResult	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:21]
);

  wire [31:0] _adder_io_result;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:56:25]
  wire [31:0] _immGen_io_immidiate;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:54:25]
  wire [31:0] _regFile_io_rs1Data;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:53:25]
  wire [31:0] _regFile_io_rs2Data;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:53:25]
  wire [4:0]  _instDec_io_rs1;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  wire [4:0]  _instDec_io_rs2;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  wire [4:0]  _instDec_io_rd;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  wire        _instDec_io_writeEnable;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  wire        _instDec_io_isImmidiate;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  wire        _instDec_io_isEbreak;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  wire [31:0] _pc_io_instAddr;	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:51:25]
  ProgramCounter pc (	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:51:25]
    .clock       (clock),
    .reset       (reset),
    .io_instAddr (_pc_io_instAddr)
  );
  InstDecoder instDec (	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
    .io_inst        (io_instIn),
    .io_rs1         (_instDec_io_rs1),
    .io_rs2         (_instDec_io_rs2),
    .io_rd          (_instDec_io_rd),
    .io_writeEnable (_instDec_io_writeEnable),
    .io_isImmidiate (_instDec_io_isImmidiate),
    .io_isEbreak    (_instDec_io_isEbreak)
  );
  RegFile regFile (	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:53:25]
    .clock          (clock),
    .io_rs1Addr     (_instDec_io_rs1),	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
    .io_rs2Addr     (_instDec_io_rs2),	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
    .io_writeEnable (_instDec_io_writeEnable),	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
    .io_rdAddr      (_instDec_io_rd),	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
    .io_rdData      (_adder_io_result),	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:56:25]
    .io_rs1Data     (_regFile_io_rs1Data),
    .io_rs2Data     (_regFile_io_rs2Data)
  );
  ImmGenerator immGen (	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:54:25]
    .io_inst      (io_instIn),
    .io_immidiate (_immGen_io_immidiate)
  );
  EbreakCall ebreakDPI (	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:55:25]
    .clock    (clock),
    .reset    (reset),
    .isEbreak (_instDec_io_isEbreak)	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  );
  Adder adder (	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:56:25]
    .io_operand1 (_regFile_io_rs1Data),	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:53:25]
    .io_operand2 (_instDec_io_isImmidiate ? _immGen_io_immidiate : _regFile_io_rs2Data),	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25, :53:25, :54:25, :70:27]
    .io_result   (_adder_io_result)
  );
  assign io_instAddrOut = _pc_io_instAddr;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:51:25]
  assign io_debug_pcInstAddr = _pc_io_instAddr;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:51:25]
  assign io_debug_instDecRs1 = _instDec_io_rs1;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  assign io_debug_instDecRs2 = _instDec_io_rs2;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  assign io_debug_instDecRd = _instDec_io_rd;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  assign io_debug_instDecWriteEnable = _instDec_io_writeEnable;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  assign io_debug_instDecIsImmidiate = _instDec_io_isImmidiate;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  assign io_debug_instDecIsEbreak = _instDec_io_isEbreak;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:52:25]
  assign io_debug_regFileRs1Data = _regFile_io_rs1Data;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:53:25]
  assign io_debug_regFileRs2Data = _regFile_io_rs2Data;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:53:25]
  assign io_debug_immGenImmidiate = _immGen_io_immidiate;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:54:25]
  assign io_debug_adderResult = _adder_io_result;	// @[<stdin>:134:10, FutureCore/src/main/scala/futurecore/FutureCore.scala:56:25]
endmodule


// ----- 8< ----- FILE "./EbreakCall.sv" ----- 8< -----

// Generated by CIRCT firtool-1.44.0
import "DPI-C" function void ebreak_call();

module EbreakCall(
    input clock,
    input reset,
    input isEbreak
);
    // initial begin
    //     if (isEbreak) begin

    //     end
    // end
    ebreak_call();
endmodule

// ----- 8< ----- FILE "firrtl_black_box_resource_files.f" ----- 8< -----
