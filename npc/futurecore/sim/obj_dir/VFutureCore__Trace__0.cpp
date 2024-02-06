// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VFutureCore__Syms.h"


void VFutureCore___024root__trace_chg_0_sub_0(VFutureCore___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void VFutureCore___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_chg_0\n"); );
    // Init
    VFutureCore___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFutureCore___024root*>(voidSelf);
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    VFutureCore___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void VFutureCore___024root__trace_chg_0_sub_0(VFutureCore___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgBit(oldp+0,(vlSelf->clock));
    bufp->chgBit(oldp+1,(vlSelf->reset));
    bufp->chgIData(oldp+2,(vlSelf->io_debug_pcInstAddrOutput),32);
    bufp->chgIData(oldp+3,(vlSelf->FutureCore__DOT__pc__DOT__pc),32);
}

void VFutureCore___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_cleanup\n"); );
    // Init
    VFutureCore___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFutureCore___024root*>(voidSelf);
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
