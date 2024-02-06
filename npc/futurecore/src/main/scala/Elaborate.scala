import circt.stage._

import futurecore.FutureCore

object Elaborate extends App {
  def top       = new FutureCore(width = 32)
  val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
  (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
}
