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

