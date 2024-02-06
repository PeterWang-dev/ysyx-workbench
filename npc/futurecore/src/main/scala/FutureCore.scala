package futurecore

import chisel3._
import circt.stage._

import backend.Alu

class FutureCoreIO extends Bundle {
  val debug_aluOperandA  = Input(UInt(32.W))
  val debug_aluOperandB  = Input(UInt(32.W))
  val debug_aluOperation = Input(UInt(4.W))
  val debug_aluResult    = Output(UInt(32.W))
}

class FutureCore(width: Int) extends Module {
  val io  = IO(new FutureCoreIO)

  val datapathWidth = width.W

  val alu = Module(new Alu)
  alu.io.operandA    := io.debug_aluOperandA
  alu.io.operandB    := io.debug_aluOperandB
  alu.io.operation   := io.debug_aluOperation
  io.debug_aluResult := alu.io.result
}

object Elaborate extends App {
  def top       = new FutureCore(32)
  val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
  (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
}
