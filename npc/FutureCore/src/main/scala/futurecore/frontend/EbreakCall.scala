package futurecore.frontend

import chisel3._
import chisel3.util.HasBlackBoxResource

class EbreakCall extends BlackBox with HasBlackBoxResource {
  val io = IO(new Bundle {
    val isEbreak = Input(Bool())
  })
  printf("Preparing to call ebreak.\n")
  addResource("/sim/vsrc/EbreakCall.sv")
}
