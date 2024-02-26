#include "VFutureCore__Dpi.h"
#include <svdpi.h>
#include <verilated.h>

extern VerilatedContext *contextp; // should be compiled with main.cpp

void ebreak_call() {
  contextp->gotFinish(true);
  VL_PRINTF("ebreak called! Simulation complete.\n");
}