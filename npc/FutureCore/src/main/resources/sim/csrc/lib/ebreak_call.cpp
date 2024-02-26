#include <verilated.h>
#include "VFutureCore__Dpi.h"

extern VerilatedContext *contextp; // should be compiled with main.cpp

void ebreak_call() {
  contextp->gotFinish(true);
  VL_PRINTF("ebreak called! Simulation complete.\n");
}