package futurecore.backend

import chisel3._

class AluIO extends Bundle {
  val operandA  = Input(UInt(32.W))
  val operandB  = Input(UInt(32.W))
  val operation = Input(UInt(4.W))
  val result    = Output(UInt(32.W))
}

class Alu extends Module {
  val io = IO(new AluIO)
}
