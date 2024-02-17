// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VFutureCore.h for the primary calling header

#include "VFutureCore__pch.h"
#include "VFutureCore__Syms.h"
#include "VFutureCore___024root.h"

void VFutureCore___024root___ctor_var_reset(VFutureCore___024root* vlSelf);

VFutureCore___024root::VFutureCore___024root(VFutureCore__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    VFutureCore___024root___ctor_var_reset(this);
}

void VFutureCore___024root___configure_coverage(VFutureCore___024root* vlSelf, bool first);

void VFutureCore___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
    VFutureCore___024root___configure_coverage(this, first);
}

VFutureCore___024root::~VFutureCore___024root() {
}

// Coverage
void VFutureCore___024root::__vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp, const char* linescovp) {
    uint32_t* count32p = countp;
    static uint32_t fake_zero_count = 0;
    if (!enable) count32p = &fake_zero_count;
    *count32p = 0;
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), VerilatedModule::name(), count32p,  "filename",filenamep,  "lineno",lineno,  "column",column,
        "hier",std::string{VerilatedModule::name()} + hierp,  "page",pagep,  "comment",commentp,  (linescovp[0] ? "linescov" : ""), linescovp);
}
