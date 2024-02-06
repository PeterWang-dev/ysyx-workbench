#include "VFutureCore.h"
#include <memory>
#include <verilated.h>

double sc_time_stamp() { return 0; }

int main(int argc, char **argv) {
  Verilated::mkdir("logs");

  // Create a simulation context for current model
  const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};

  // Set context options
  contextp->debug(0);
  contextp->randReset(2);
  contextp->traceEverOn(true);
  contextp->commandArgs(argc, argv);

  // Construct the Verilated model
  const std::unique_ptr<VFutureCore> top{
      new VFutureCore{contextp.get(), "FutureCore"}};

  // Set initial signals
  top->clock = 0;
  int runing_cycles = 10;

  // Simulate until $finish
  while (runing_cycles--) {
    //   while (!contextp->gotFinish()) {
    contextp->timeInc(1); // 1 timeprecision period passes...

    // Toggle a fast (time/2 period) clock
    top->clock = !top->clock;

    // Evaluate model
    top->eval();

    // Read outputs
    // VL_PRINTF("[%" PRId64 "] clk=%x rstl=%x iquad=%" PRIx64 " -> oquad=%"
    // PRIx64
    //           " owide=%x_%08x_%08x\n",
    //           contextp->time(), top->clk, top->reset_l, top->in_quad,
    //           top->out_quad, top->out_wide[2], top->out_wide[1],
    //           top->out_wide[0]);
  }

  // Final model cleanup
  top->final();

// Coverage analysis (calling write only after the test is known to pass)
#if VM_COVERAGE
  Verilated::mkdir("logs");
  contextp->coveragep()->write("logs/coverage.dat");
#endif

  return 0;
}
