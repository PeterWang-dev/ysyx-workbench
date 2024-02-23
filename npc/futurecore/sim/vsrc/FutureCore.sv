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
module regBank_combMem(	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
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

  reg [31:0] Memory[0:31];	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  always @(posedge W0_clk) begin	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
    if (W0_en)	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
      Memory[W0_addr] <= W0_data;	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  end // always @(posedge)
  `ifdef ENABLE_INITIAL_MEM_	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
    reg [31:0] _RANDOM_MEM;	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
    initial begin	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
      `INIT_RANDOM_PROLOG_	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
      `ifdef RANDOMIZE_MEM_INIT	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
        for (logic [5:0] i = 6'h0; i < 6'h20; i += 6'h1) begin
          _RANDOM_MEM = `RANDOM;	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
          Memory[i[4:0]] = _RANDOM_MEM;	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
        end	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
      `endif // RANDOMIZE_MEM_INIT
    end // initial
  `endif // ENABLE_INITIAL_MEM_
  assign R0_data = R0_en ? Memory[R0_addr] : 32'bx;	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  assign R1_data = R1_en ? Memory[R1_addr] : 32'bx;	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
endmodule

module ProgramCounter(	// @[<stdin>:3:10]
  input         clock,	// @[<stdin>:4:11]
                reset,	// @[<stdin>:5:11]
  output [31:0] io_instAddr	// @[futurecore/src/main/scala/futurecore/frontend/ProgramCounter.scala:29:21]
);

  reg [31:0] pc;	// @[futurecore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19]
  always @(posedge clock) begin	// @[<stdin>:4:11]
    if (reset)	// @[<stdin>:4:11]
      pc <= 32'h80000000;	// @[futurecore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19]
    else	// @[<stdin>:4:11]
      pc <= pc + 32'h4;	// @[futurecore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19, :33:12]
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
        pc = _RANDOM[/*Zero width*/ 1'b0];	// @[<stdin>:3:10, futurecore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19]
      `endif // RANDOMIZE_REG_INIT
    end // initial
    `ifdef FIRRTL_AFTER_INITIAL	// @[<stdin>:3:10]
      `FIRRTL_AFTER_INITIAL	// @[<stdin>:3:10]
    `endif // FIRRTL_AFTER_INITIAL
  `endif // ENABLE_INITIAL_REG_
  assign io_instAddr = pc;	// @[<stdin>:3:10, futurecore/src/main/scala/futurecore/frontend/ProgramCounter.scala:32:19]
endmodule

module InstDecoder(	// @[<stdin>:15:10]
  input  [31:0] io_inst,	// @[futurecore/src/main/scala/futurecore/frontend/InstDecoder.scala:33:14]
  output [4:0]  io_rs1,	// @[futurecore/src/main/scala/futurecore/frontend/InstDecoder.scala:33:14]
                io_rs2,	// @[futurecore/src/main/scala/futurecore/frontend/InstDecoder.scala:33:14]
                io_rd	// @[futurecore/src/main/scala/futurecore/frontend/InstDecoder.scala:33:14]
);

  assign io_rs1 = io_inst[19:15];	// @[<stdin>:15:10, futurecore/src/main/scala/futurecore/frontend/InstDecoder.scala:35:28]
  assign io_rs2 = io_inst[24:20];	// @[<stdin>:15:10, futurecore/src/main/scala/futurecore/frontend/InstDecoder.scala:36:28]
  assign io_rd = io_inst[11:7];	// @[<stdin>:15:10, futurecore/src/main/scala/futurecore/frontend/InstDecoder.scala:38:28]
endmodule

module RegFile(	// @[<stdin>:28:10]
  input         clock,	// @[<stdin>:29:11]
  input  [4:0]  io_rs1Addr,	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
                io_rs2Addr,	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
                io_rdAddr,	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
  input  [31:0] io_rdData,	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
  output [31:0] io_rs1Data,	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
                io_rs2Data	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
);

  wire [31:0] _regBank_ext_R0_data;	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  wire [31:0] _regBank_ext_R1_data;	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
  regBank_combMem regBank_ext (	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20]
    .R0_addr (io_rs1Addr),
    .R0_en   (1'h1),	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
    .R0_clk  (clock),
    .R1_addr (io_rs2Addr),
    .R1_en   (1'h1),	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
    .R1_clk  (clock),
    .W0_addr (io_rdAddr),
    .W0_en   (1'h1),	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:37:19]
    .W0_clk  (clock),
    .W0_data ((|io_rdAddr) ? io_rdData : 32'h0),	// @[futurecore/src/main/scala/futurecore/backend/RegFile.scala:44:{33,44}]
    .R0_data (_regBank_ext_R0_data),
    .R1_data (_regBank_ext_R1_data)
  );
  assign io_rs1Data = (|io_rs1Addr) ? _regBank_ext_R0_data : 32'h0;	// @[<stdin>:28:10, futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20, :40:{20,32}, :44:33]
  assign io_rs2Data = (|io_rs2Addr) ? _regBank_ext_R1_data : 32'h0;	// @[<stdin>:28:10, futurecore/src/main/scala/futurecore/backend/RegFile.scala:38:20, :41:{20,32}, :44:33]
endmodule

module Adder(	// @[<stdin>:49:10]
  input  [31:0] io_operand1,	// @[futurecore/src/main/scala/futurecore/backend/Adder.scala:31:14]
                io_operand2,	// @[futurecore/src/main/scala/futurecore/backend/Adder.scala:31:14]
  output [31:0] io_result	// @[futurecore/src/main/scala/futurecore/backend/Adder.scala:31:14]
);

  assign io_result = io_operand1 + io_operand2;	// @[<stdin>:49:10, futurecore/src/main/scala/futurecore/backend/Adder.scala:33:28]
endmodule

module FutureCore(	// @[<stdin>:58:10]
  input         clock,	// @[<stdin>:59:11]
                reset,	// @[<stdin>:60:11]
  input  [31:0] io_instIn,	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
  output [31:0] io_instAddrOut,	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
                io_debug_pcInstAddr,	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
  output [4:0]  io_debug_instDecRs1,	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
                io_debug_instDecRs2,	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
                io_debug_instDecRd,	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
  output [31:0] io_debug_regFileRs1Data,	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
                io_debug_regFileRs2Data,	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
                io_debug_adderResult	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:39:19]
);

  wire [31:0] _adder_io_result;	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:43:23]
  wire [31:0] _regFile_io_rs1Data;	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:42:23]
  wire [31:0] _regFile_io_rs2Data;	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:42:23]
  wire [4:0]  _instDec_io_rs1;	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
  wire [4:0]  _instDec_io_rs2;	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
  wire [4:0]  _instDec_io_rd;	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
  wire [31:0] _pc_io_instAddr;	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:40:23]
  ProgramCounter pc (	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:40:23]
    .clock       (clock),
    .reset       (reset),
    .io_instAddr (_pc_io_instAddr)
  );
  InstDecoder instDec (	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
    .io_inst (io_instIn),
    .io_rs1  (_instDec_io_rs1),
    .io_rs2  (_instDec_io_rs2),
    .io_rd   (_instDec_io_rd)
  );
  RegFile regFile (	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:42:23]
    .clock      (clock),
    .io_rs1Addr (_instDec_io_rs1),	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
    .io_rs2Addr (_instDec_io_rs2),	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
    .io_rdAddr  (_instDec_io_rd),	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
    .io_rdData  (_adder_io_result),	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:43:23]
    .io_rs1Data (_regFile_io_rs1Data),
    .io_rs2Data (_regFile_io_rs2Data)
  );
  Adder adder (	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:43:23]
    .io_operand1 (_regFile_io_rs1Data),	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:42:23]
    .io_operand2 (_regFile_io_rs2Data),	// @[futurecore/src/main/scala/futurecore/FutureCore.scala:42:23]
    .io_result   (_adder_io_result)
  );
  assign io_instAddrOut = _pc_io_instAddr;	// @[<stdin>:58:10, futurecore/src/main/scala/futurecore/FutureCore.scala:40:23]
  assign io_debug_pcInstAddr = _pc_io_instAddr;	// @[<stdin>:58:10, futurecore/src/main/scala/futurecore/FutureCore.scala:40:23]
  assign io_debug_instDecRs1 = _instDec_io_rs1;	// @[<stdin>:58:10, futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
  assign io_debug_instDecRs2 = _instDec_io_rs2;	// @[<stdin>:58:10, futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
  assign io_debug_instDecRd = _instDec_io_rd;	// @[<stdin>:58:10, futurecore/src/main/scala/futurecore/FutureCore.scala:41:23]
  assign io_debug_regFileRs1Data = _regFile_io_rs1Data;	// @[<stdin>:58:10, futurecore/src/main/scala/futurecore/FutureCore.scala:42:23]
  assign io_debug_regFileRs2Data = _regFile_io_rs2Data;	// @[<stdin>:58:10, futurecore/src/main/scala/futurecore/FutureCore.scala:42:23]
  assign io_debug_adderResult = _adder_io_result;	// @[<stdin>:58:10, futurecore/src/main/scala/futurecore/FutureCore.scala:43:23]
endmodule

