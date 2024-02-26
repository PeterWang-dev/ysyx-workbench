#include <verilated.h>

extern void ebreak_call();

extern VerilatedContext *contextp; // should be compiled with main.cpp

void ebreak_call() {
  contextp->gotFinish(true);
  VL_PRINTF("ebreak called! Simulation complete.\n");
}