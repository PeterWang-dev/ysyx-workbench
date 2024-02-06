// Generated by CIRCT firtool-1.62.0
// Standard header to adapt well known macros for register randomization.
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

module ProgramCounter(	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
  input         clock,	// <stdin>:15:11
                reset,	// <stdin>:16:11
  output [31:0] io_instAddr	// futurecore/src/main/scala/frontend/ProgramCounter.scala:10:21
);

  reg [31:0] pc;	// futurecore/src/main/scala/frontend/ProgramCounter.scala:13:26
  always @(posedge clock) begin	// <stdin>:15:11
    if (reset)	// <stdin>:15:11
      pc <= 32'h0;	// futurecore/src/main/scala/frontend/ProgramCounter.scala:13:26
    else	// <stdin>:15:11
      pc <= pc + 32'h4;	// futurecore/src/main/scala/frontend/ProgramCounter.scala:13:26, :14:12
  end // always @(posedge)
  `ifdef ENABLE_INITIAL_REG_	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
    `ifdef FIRRTL_BEFORE_INITIAL	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
      `FIRRTL_BEFORE_INITIAL	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
    `endif // FIRRTL_BEFORE_INITIAL
    initial begin	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
      automatic logic [31:0] _RANDOM[0:0];	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
      `ifdef INIT_RANDOM_PROLOG_	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
        `INIT_RANDOM_PROLOG_	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
      `endif // INIT_RANDOM_PROLOG_
      `ifdef RANDOMIZE_REG_INIT	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
        _RANDOM[/*Zero width*/ 1'b0] = `RANDOM;	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
        pc = _RANDOM[/*Zero width*/ 1'b0];	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7, :13:26
      `endif // RANDOMIZE_REG_INIT
    end // initial
    `ifdef FIRRTL_AFTER_INITIAL	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
      `FIRRTL_AFTER_INITIAL	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7
    `endif // FIRRTL_AFTER_INITIAL
  `endif // ENABLE_INITIAL_REG_
  assign io_instAddr = pc;	// futurecore/src/main/scala/frontend/ProgramCounter.scala:9:7, :13:26
endmodule

module FutureCore(	// futurecore/src/main/scala/FutureCore.scala:31:7
  input         clock,	// <stdin>:26:11
                reset,	// <stdin>:27:11
  output [31:0] io_debug_pcInstAddrOutput	// futurecore/src/main/scala/FutureCore.scala:32:14
);

  ProgramCounter pc (	// futurecore/src/main/scala/FutureCore.scala:36:18
    .clock       (clock),
    .reset       (reset),
    .io_instAddr (io_debug_pcInstAddrOutput)
  );
endmodule

