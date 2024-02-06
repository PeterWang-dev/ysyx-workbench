// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VFutureCore.h for the primary calling header

#include "VFutureCore__pch.h"
#include "VFutureCore__Syms.h"
#include "VFutureCore___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VFutureCore___024root___dump_triggers__ico(VFutureCore___024root* vlSelf);
#endif  // VL_DEBUG

void VFutureCore___024root___eval_triggers__ico(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.set(0U, (IData)(vlSelf->__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VFutureCore___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

VL_INLINE_OPT void VFutureCore___024root___ico_sequent__TOP__0(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___ico_sequent__TOP__0\n"); );
    // Body
    if (((IData)(vlSelf->clock) ^ (IData)(vlSelf->FutureCore__DOT____Vtogcov__clock))) {
        ++(vlSymsp->__Vcoverage[0]);
        vlSelf->FutureCore__DOT____Vtogcov__clock = vlSelf->clock;
    }
    if (((IData)(vlSelf->reset) ^ (IData)(vlSelf->FutureCore__DOT____Vtogcov__reset))) {
        ++(vlSymsp->__Vcoverage[1]);
        vlSelf->FutureCore__DOT____Vtogcov__reset = vlSelf->reset;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VFutureCore___024root___dump_triggers__act(VFutureCore___024root* vlSelf);
#endif  // VL_DEBUG

void VFutureCore___024root___eval_triggers__act(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clock) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clock__0))));
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = vlSelf->clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VFutureCore___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void VFutureCore___024root___nba_sequent__TOP__0(VFutureCore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root___nba_sequent__TOP__0\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[68]);
    if (vlSelf->reset) {
        ++(vlSymsp->__Vcoverage[66]);
        vlSelf->FutureCore__DOT__pc__DOT__pc = 0U;
    } else {
        vlSelf->FutureCore__DOT__pc__DOT__pc = ((IData)(4U) 
                                                + vlSelf->FutureCore__DOT__pc__DOT__pc);
    }
    if ((1U & (~ (IData)(vlSelf->reset)))) {
        ++(vlSymsp->__Vcoverage[67]);
    }
    if ((1U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
               ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[34]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffffffeU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (1U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((2U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
               ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[35]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffffffdU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (2U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((4U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
               ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[36]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffffffbU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (4U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((8U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
               ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[37]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffffff7U & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (8U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x10U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                  ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[38]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffffffefU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x10U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x20U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                  ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[39]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffffffdfU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x20U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x40U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                  ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[40]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffffffbfU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x40U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x80U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                  ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[41]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffffff7fU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x80U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x100U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                   ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[42]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffffeffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x100U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x200U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                   ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[43]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffffdffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x200U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x400U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                   ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[44]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffffbffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x400U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x800U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                   ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[45]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffff7ffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x800U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x1000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                    ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[46]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffffefffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x1000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x2000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                    ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[47]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffffdfffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x2000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x4000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                    ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[48]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffffbfffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x4000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x8000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                    ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[49]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffff7fffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x8000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x10000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                     ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[50]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffeffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x10000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x20000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                     ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[51]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffdffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x20000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x40000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                     ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[52]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfffbffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x40000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x80000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                     ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[53]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfff7ffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x80000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x100000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                      ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[54]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffefffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x100000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x200000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                      ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[55]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffdfffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x200000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x400000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                      ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[56]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xffbfffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x400000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x800000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                      ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[57]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xff7fffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x800000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x1000000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                       ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[58]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfeffffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x1000000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x2000000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                       ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[59]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfdffffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x2000000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x4000000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                       ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[60]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xfbffffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x4000000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x8000000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                       ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[61]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xf7ffffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x8000000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x10000000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                        ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[62]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xefffffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x10000000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x20000000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                        ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[63]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xdfffffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x20000000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if ((0x40000000U & (vlSelf->FutureCore__DOT__pc__DOT__pc 
                        ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc))) {
        ++(vlSymsp->__Vcoverage[64]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0xbfffffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x40000000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    if (((vlSelf->FutureCore__DOT__pc__DOT__pc ^ vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[65]);
        vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc 
            = ((0x7fffffffU & vlSelf->FutureCore__DOT__pc__DOT____Vtogcov__pc) 
               | (0x80000000U & vlSelf->FutureCore__DOT__pc__DOT__pc));
    }
    vlSelf->io_debug_pcInstAddrOutput = vlSelf->FutureCore__DOT__pc__DOT__pc;
    if ((1U & (vlSelf->io_debug_pcInstAddrOutput ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[2]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffffffeU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (1U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((2U & (vlSelf->io_debug_pcInstAddrOutput ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[3]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffffffdU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (2U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((4U & (vlSelf->io_debug_pcInstAddrOutput ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[4]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffffffbU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (4U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((8U & (vlSelf->io_debug_pcInstAddrOutput ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[5]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffffff7U & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (8U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x10U & (vlSelf->io_debug_pcInstAddrOutput 
                  ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[6]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffffffefU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x10U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x20U & (vlSelf->io_debug_pcInstAddrOutput 
                  ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[7]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffffffdfU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x20U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x40U & (vlSelf->io_debug_pcInstAddrOutput 
                  ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[8]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffffffbfU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x40U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x80U & (vlSelf->io_debug_pcInstAddrOutput 
                  ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[9]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffffff7fU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x80U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x100U & (vlSelf->io_debug_pcInstAddrOutput 
                   ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[10]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffffeffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x100U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x200U & (vlSelf->io_debug_pcInstAddrOutput 
                   ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[11]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffffdffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x200U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x400U & (vlSelf->io_debug_pcInstAddrOutput 
                   ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[12]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffffbffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x400U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x800U & (vlSelf->io_debug_pcInstAddrOutput 
                   ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[13]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffff7ffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x800U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x1000U & (vlSelf->io_debug_pcInstAddrOutput 
                    ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[14]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffffefffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x1000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x2000U & (vlSelf->io_debug_pcInstAddrOutput 
                    ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[15]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffffdfffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x2000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x4000U & (vlSelf->io_debug_pcInstAddrOutput 
                    ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[16]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffffbfffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x4000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x8000U & (vlSelf->io_debug_pcInstAddrOutput 
                    ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[17]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffff7fffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x8000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x10000U & (vlSelf->io_debug_pcInstAddrOutput 
                     ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[18]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffeffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x10000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x20000U & (vlSelf->io_debug_pcInstAddrOutput 
                     ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[19]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffdffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x20000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x40000U & (vlSelf->io_debug_pcInstAddrOutput 
                     ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[20]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfffbffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x40000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x80000U & (vlSelf->io_debug_pcInstAddrOutput 
                     ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[21]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfff7ffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x80000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x100000U & (vlSelf->io_debug_pcInstAddrOutput 
                      ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[22]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffefffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x100000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x200000U & (vlSelf->io_debug_pcInstAddrOutput 
                      ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[23]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffdfffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x200000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x400000U & (vlSelf->io_debug_pcInstAddrOutput 
                      ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[24]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xffbfffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x400000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x800000U & (vlSelf->io_debug_pcInstAddrOutput 
                      ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[25]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xff7fffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x800000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x1000000U & (vlSelf->io_debug_pcInstAddrOutput 
                       ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[26]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfeffffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x1000000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x2000000U & (vlSelf->io_debug_pcInstAddrOutput 
                       ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[27]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfdffffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x2000000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x4000000U & (vlSelf->io_debug_pcInstAddrOutput 
                       ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[28]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xfbffffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x4000000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x8000000U & (vlSelf->io_debug_pcInstAddrOutput 
                       ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[29]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xf7ffffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x8000000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x10000000U & (vlSelf->io_debug_pcInstAddrOutput 
                        ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[30]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xefffffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x10000000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x20000000U & (vlSelf->io_debug_pcInstAddrOutput 
                        ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[31]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xdfffffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x20000000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if ((0x40000000U & (vlSelf->io_debug_pcInstAddrOutput 
                        ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput))) {
        ++(vlSymsp->__Vcoverage[32]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0xbfffffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x40000000U & vlSelf->io_debug_pcInstAddrOutput));
    }
    if (((vlSelf->io_debug_pcInstAddrOutput ^ vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[33]);
        vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput 
            = ((0x7fffffffU & vlSelf->FutureCore__DOT____Vtogcov__io_debug_pcInstAddrOutput) 
               | (0x80000000U & vlSelf->io_debug_pcInstAddrOutput));
    }
}
