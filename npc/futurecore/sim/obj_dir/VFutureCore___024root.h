// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VFutureCore.h for the primary calling header

#ifndef VERILATED_VFUTURECORE___024ROOT_H_
#define VERILATED_VFUTURECORE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"


class VFutureCore__Syms;

class alignas(VL_CACHE_LINE_BYTES) VFutureCore___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    CData/*0:0*/ FutureCore__DOT____Vtogcov__clock;
    CData/*0:0*/ FutureCore__DOT____Vtogcov__reset;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
    CData/*0:0*/ __VactContinue;
    VL_OUT(io_debug_pcInstAddrOutput,31,0);
    IData/*31:0*/ FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput;
    IData/*31:0*/ FutureCore__DOT__pc__DOT__pc;
    IData/*31:0*/ FutureCore__DOT__pc__DOT____Vtogcov__pc;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    VFutureCore__Syms* const vlSymsp;

    // CONSTRUCTORS
    VFutureCore___024root(VFutureCore__Syms* symsp, const char* v__name);
    ~VFutureCore___024root();
    VL_UNCOPYABLE(VFutureCore___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


#endif  // guard
