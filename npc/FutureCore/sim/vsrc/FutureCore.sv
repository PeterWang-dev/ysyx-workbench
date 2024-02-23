// Generated by CIRCT firtool-1.44.0
// Standard header to adapt well known macros to our needs.
`ifndef RANDOMIZE
  `ifdef RANDOMIZE_REG_INIT
    `define RANDOMIZE
  `endif // RANDOMIZE_REG_INIT
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

module FutureCore(	// @[<stdin>:115:10]
  input         clock,	// @[<stdin>:116:11]
                reset,	// @[<stdin>:117:11]
  input  [31:0] io_instIn,	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:49:19]
  output [31:0] io_instAddrOut	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:49:19]
);

  ProgramCounter pc (	// @[FutureCore/src/main/scala/futurecore/FutureCore.scala:50:23]
    .clock       (clock),
    .reset       (reset),
    .io_instAddr (io_instAddrOut)
  );
endmodule

