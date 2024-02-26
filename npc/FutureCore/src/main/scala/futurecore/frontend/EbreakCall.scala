package futurecore.frontend

import chisel3._
import chisel3.util.HasBlackBoxResource

class EbreakCall extends BlackBox with HasBlackBoxResource {
  val io = IO(new Bundle {
    val clock = Input(Bool())
    val reset = Input(Bool())
    val isEbreak = Input(Bool())
  })
  addResource("/sim/vsrc/EbreakCall.sv")
}
