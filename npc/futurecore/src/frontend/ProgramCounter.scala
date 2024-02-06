package futurecore.frontend

import chisel3._

class ProgramCounterIO extends Bundle {
  val instAddr = Output(UInt(32.W))
}

class ProgramCounter extends Module {
  val io        = IO(new ProgramCounterIO)
  val instWidth = 32.W

  val pc        = RegInit(0.U(instWidth))
  pc := pc + 4.U

  io.instAddr := pc
}
