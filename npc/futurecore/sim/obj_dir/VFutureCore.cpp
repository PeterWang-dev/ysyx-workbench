// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VFutureCore__pch.h"
#include "verilated_vcd_c.h"

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
    vlSymsp->__Vm_activity = true;
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
std::unique_ptr<VerilatedTraceConfig> VFutureCore::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void VFutureCore___024root__trace_decl_types(VerilatedVcd* tracep);

void VFutureCore___024root__trace_init_top(VFutureCore___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    VFutureCore___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFutureCore___024root*>(voidSelf);
    VFutureCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    VFutureCore___024root__trace_decl_types(tracep);
    VFutureCore___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void VFutureCore___024root__trace_register(VFutureCore___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void VFutureCore::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'VFutureCore::trace()' shall not be called after 'VerilatedVcdC::open()'.");
    }
    (void)levels; (void)options; // Prevent unused variable warning
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    VFutureCore___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
