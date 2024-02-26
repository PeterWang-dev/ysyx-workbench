#include "VFutureCore.h"
#include <memory>
#include <verilated.h>
#include <verilated_vcd_c.h>

/* Test ADDI       // x0 = 0    0x000
addi x1, x0, 1000  // x1 = 1000 0x3E8
addi x2, x1, 2000  // x2 = 3000 0xBB8
addi x3, x2, -1000 // x3 = 2000 0x7D0
addi x4, x3, 2000  // x4 = 0    0x000
addi x5, x4, 1000  // x5 = 1000 0x3E8 */
uint32_t mem[100] = {0x3e800093, 0x7d008113, 0xc1810193, 0x83018213,
                     0x3e820293};

const uint32_t offset = 0x80000000;

uint32_t pmem_read(uint32_t paddr) {
  printf("pmem_read: %x, index: %lu\n", paddr,
         (paddr - offset) / sizeof(uint32_t));
  return mem[(paddr - offset) / sizeof(uint32_t)];
}

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
  top->trace(tfp, 99);
  tfp->open("logs/vlt_dump.vcd");
  // tfp->dumpvars(1, "FutureCore");

  /* Setting initial signals */
  top->clock = 0;
  top->reset = 0;
  top->io_instIn = 0;

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

      if (contextp->time() >= 10) {
        printf("paddr: %x\n", top->io_debug_pcInstAddr);
        top->io_instIn = pmem_read(top->io_debug_pcInstAddr);
      }
    }

    top->eval();
    tfp->dump(contextp->time());

    VL_PRINTF("[%" PRId64 "] clock=%x reset=%x "
              "pcInstAddr=%x instDecRs1=%x instDecRs2=%x instDecRd=%x "
              "instDecWriteEnable=%x instDecIsImmidiate=%x immGenImmidiate=%x "
              "regFileRs1Data=%x regFileRs2Data=%x adderResult=%x\n",
              contextp->time(), top->clock, top->reset,
              top->io_debug_pcInstAddr, top->io_debug_instDecRs1,
              top->io_debug_instDecRs2, top->io_debug_instDecRd,
              top->io_debug_instDecWriteEnable,
              top->io_debug_instDecIsImmidiate, top->io_debug_immGenImmidiate,
              top->io_debug_regFileRs1Data, top->io_debug_regFileRs2Data,
              top->io_debug_adderResult);
  }

  // Final model cleanup
  top->final();
  tfp->close();

// Coverage analysis (calling write only after the test is known to pass)
#if VM_COVERAGE
  Verilated::mkdir("logs");
  contextp->coveragep()->write("logs/coverage.dat");
#endif

  return 0;
}
