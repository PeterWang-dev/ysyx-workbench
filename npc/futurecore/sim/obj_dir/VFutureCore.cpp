// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VFutureCore__pch.h"

//============================================================
// Constructors

VFutureCore::VFutureCore(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VFutureCore__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_debug_pcInstAddrOutput{vlSymsp->TOP.io_debug_pcInstAddrOutput}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VFutureCore::VFutureCore(const char* _vcname__)
    : VFutureCore(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VFutureCore::~VFutureCore() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VFutureCore___024root___eval_debug_assertions(VFutureCore___024root* vlSelf);
#endif  // VL_DEBUG
void VFutureCore___024root___eval_static(VFutureCore___024root* vlSelf);
void VFutureCore___024root___eval_initial(VFutureCore___024root* vlSelf);
void VFutureCore___024root___eval_settle(VFutureCore___024root* vlSelf);
void VFutureCore___024root___eval(VFutureCore___024root* vlSelf);

void VFutureCore::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VFutureCore::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VFutureCore___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VFutureCore___024root___eval_static(&(vlSymsp->TOP));
        VFutureCore___024root___eval_initial(&(vlSymsp->TOP));
        VFutureCore___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VFutureCore___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VFutureCore::eventsPending() { return false; }

uint64_t VFutureCore::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VFutureCore::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VFutureCore___024root___eval_final(VFutureCore___024root* vlSelf);

VL_ATTR_COLD void VFutureCore::final() {
    VFutureCore___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VFutureCore::hierName() const { return vlSymsp->name(); }
const char* VFutureCore::modelName() const { return "VFutureCore"; }
unsigned VFutureCore::threads() const { return 1; }
void VFutureCore::prepareClone() const { contextp()->prepareClone(); }
void VFutureCore::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void VFutureCore::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'VFutureCore::trace()' called on model that was Verilated without --trace option");
}
