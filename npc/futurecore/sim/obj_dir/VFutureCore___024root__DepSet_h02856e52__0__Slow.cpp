// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VFutureCore.h for the primary calling header

#include "VFutureCore__pch.h"
#include "VFutureCore___024root.h"

VL_ATTR_COLD void VFutureCore___024root___eval_static(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___eval_static\n"); );
}

VL_ATTR_COLD void VFutureCore___024root___eval_initial__TOP(VFutureCore___024root* vlSelf);

VL_ATTR_COLD void VFutureCore___024root___eval_initial(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___eval_initial\n"); );
    // Body
    VFutureCore___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = vlSelf->clock;
}

VL_ATTR_COLD void VFutureCore___024root___eval_final(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VFutureCore___024root___dump_triggers__stl(VFutureCore___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VFutureCore___024root___eval_phase__stl(VFutureCore___024root* vlSelf);

VL_ATTR_COLD void VFutureCore___024root___eval_settle(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            VFutureCore___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/data/peterw/Projects/ysyx/ysyx-workbench/npc/futurecore/sim/vsrc/FutureCore.v", 87, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (VFutureCore___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VFutureCore___024root___dump_triggers__stl(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VFutureCore___024root___stl_sequent__TOP__0(VFutureCore___024root* vlSelf);

VL_ATTR_COLD void VFutureCore___024root___eval_stl(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VFutureCore___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void VFutureCore___024root___eval_triggers__stl(VFutureCore___024root* vlSelf);

VL_ATTR_COLD bool VFutureCore___024root___eval_phase__stl(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    VFutureCore___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        VFutureCore___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VFutureCore___024root___dump_triggers__ico(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VFutureCore___024root___dump_triggers__act(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VFutureCore___024root___dump_triggers__nba(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VFutureCore___024root___ctor_var_reset(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = 0;
    vlSelf->reset = 0;
    vlSelf->io_debug_pcInstAddrOutput = 0;
    vlSelf->FutureCore__DOT____Vtogcov__clock = 0;
    vlSelf->FutureCore__DOT____Vtogcov__reset = 0;
    vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput = 0;
    vlSelf->FutureCore__DOT__pc__DOT__pc = 0;
    vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc = 0;
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = 0;
}
