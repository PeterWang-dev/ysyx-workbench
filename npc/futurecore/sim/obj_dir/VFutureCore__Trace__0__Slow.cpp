// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VFutureCore__Syms.h"


VL_ATTR_COLD void VFutureCore___024root__trace_init_sub__TOP__0(VFutureCore___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+1,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"io_debug_pcInstAddrOutput",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("FutureCore", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+1,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"io_debug_pcInstAddrOutput",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("pc", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+1,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"io_instAddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void VFutureCore___024root__trace_init_top(VFutureCore___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_init_top\n"); );
    // Body
    VFutureCore___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void VFutureCore___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void VFutureCore___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VFutureCore___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VFutureCore___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void VFutureCore___024root__trace_register(VFutureCore___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_register\n"); );
    // Body
    tracep->addConstCb(&VFutureCore___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&VFutureCore___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&VFutureCore___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&VFutureCore___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void VFutureCore___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_const_0\n"); );
    // Init
    VFutureCore___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFutureCore___024root*>(voidSelf);
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
}

VL_ATTR_COLD void VFutureCore___024root__trace_full_0_sub_0(VFutureCore___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VFutureCore___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_full_0\n"); );
    // Init
    VFutureCore___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFutureCore___024root*>(voidSelf);
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    VFutureCore___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VFutureCore___024root__trace_full_0_sub_0(VFutureCore___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFutureCore___024root__trace_full_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->clock));
    bufp->fullBit(oldp+2,(vlSelf->reset));
    bufp->fullIData(oldp+3,(vlSelf->io_debug_pcInstAddrOutput),32);
    bufp->fullIData(oldp+4,(vlSelf->FutureCore__DOT__pc__DOT__pc),32);
}
