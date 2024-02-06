/* Copyright PeterWang-dev (https://github.com/PeterWang-dev) 2024.

  This source describes Open Hardware and is licensed under the CERN-OHL-W v2

  You may redistribute and modify this documentation and make products
  using it under the terms of the CERN-OHL-W v2 (https:/cern.ch/cern-ohl).

  This documentation is distributed WITHOUT ANY EXPRESS OR IMPLIED
  WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY
  AND FITNESS FOR A PARTICULAR PURPOSE. Please see the CERN-OHL-W v2
  for applicable conditions.

  Source location: https://www.ohwr.org/project/wr-switch-hw

  As per CERN-OHL-W v2 section 4.1, should You produce hardware based on
  these sources, You must maintain the Source Location visible on the
  external case of the White Rabbit switch or other product you make using
  this documentation.
 */
package futurecore

import chisel3._
import circt.stage._

import backend.Alu
import frontend.ProgramCounter

class FutureCoreIO extends Bundle {
  val debug_pcInstAddrOutput = Output(UInt(32.W))
}

class FutureCore(width: Int) extends Module {
  val io = IO(new FutureCoreIO)

  val datapathWidth = width.W

  val pc = Module(new ProgramCounter)

  io.debug_pcInstAddrOutput := pc.io.instAddr
}

object Elaborate extends App {
  def top       = new FutureCore(width = 32)
  val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
  (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
}
