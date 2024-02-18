#include "VFutureCore.h"
#include <memory>
#include <verilated.h>
#include <verilated_vcd_c.h>

double sc_time_stamp() { return 0; }

int main(int argc, char **argv) {
  Verilated::mkdir("logs"); // directory of traces

  /* Setting up simulation context */
  const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};

  contextp->debug(0);                // debug level
  contextp->randReset(2);            // reset policy
  contextp->traceEverOn(true);       // compute traced signals
  contextp->commandArgs(argc, argv); // pass arguments to Verilated code

  /* Preparing the Verilated model and the trace file pointer */
  const std::unique_ptr<VFutureCore> top{
      new VFutureCore{contextp.get(), "FutureCore"}};

  VerilatedVcdC *tfp = new VerilatedVcdC;
  tfp->open("logs/vlt_dump.vcd");

  /* Main loop of simulation */
  while (contextp->time() < 100 && !contextp->gotFinish()) {
    contextp->timeInc(1);

    top->clock = !top->clock; // Clock update

    // Postage clock update
    if (top->clock) {
      if (contextp->time() > 1 && contextp->time() < 10) {
        top->reset = 1;
      } else {
        top->reset = 0;
      }

      top->eval();
      tfp->dump(contextp->time());
    }

    VL_PRINTF("[%" PRId64 "] clock=%x reset=%x io_debug_pcInstAddrOutput=%x\n",
              contextp->time(), top->clock, top->reset,
              top->io_debug_pcInstAddrOutput);
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
