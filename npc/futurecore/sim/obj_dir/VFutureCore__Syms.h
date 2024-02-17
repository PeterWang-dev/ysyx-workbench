// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VFUTURECORE__SYMS_H_
#define VERILATED_VFUTURECORE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VFutureCore.h"

// INCLUDE MODULE CLASSES
#include "VFutureCore___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VFutureCore__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VFutureCore* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VFutureCore___024root          TOP;

    // COVERAGE
    uint32_t __Vcoverage[70];

    // CONSTRUCTORS
    VFutureCore__Syms(VerilatedContext* contextp, const char* namep, VFutureCore* modelp);
    ~VFutureCore__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
