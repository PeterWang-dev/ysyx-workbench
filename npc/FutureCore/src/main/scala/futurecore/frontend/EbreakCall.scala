package futurecore.frontend

import chisel3._
import chisel3.util.HasBlackBoxResource

class EbreakCall extends BlackBox with HasBlackBoxResource {
  val io = IO(new Bundle {
    val clock = Input(Clock())
    val reset = Input(Reset())
    val isEbreak = Input(Bool())
  })
  addResource("EbreakCall.sv")
}
