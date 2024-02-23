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
import chisel3._

import futurecore.backend.{Adder, RegFile}
import futurecore.frontend.{InstDecoder, ProgramCounter}

class FutureCoreIO extends Bundle {
  val instAddrOut = Output(UInt(32.W))
  val instIn      = Input(UInt(32.W))
  // debug signals
  // val debug_pcInstAddr         = Output(UInt(32.W))
  // val debug_instDecRs1         = Output(UInt(5.W))
  // val debug_instDecRs2         = Output(UInt(5.W))
  // val debug_instDecwriteEnable = Output(Bool())
  // val debug_instDecRd          = Output(UInt(5.W))
  // val debug_regFileRs1Data     = Output(UInt(32.W))
  // val debug_regFileRs2Data     = Output(UInt(32.W))
  // val debug_adderResult        = Output(UInt(32.W))
}

class FutureCore extends Module {
  val io      = IO(new FutureCoreIO)
  val pc      = Module(new ProgramCounter)
  val instDec = Module(new InstDecoder)
  val regFile = Module(new RegFile)
  val adder   = Module(new Adder)

  io.instAddrOut  := pc.io.instAddr
  instDec.io.inst := io.instIn

  regFile.io.rs1Addr     := instDec.io.rs1
  regFile.io.rs2Addr     := instDec.io.rs2
  regFile.io.writeEnable := instDec.io.writeEnable
  regFile.io.rdAddr      := instDec.io.rd

  adder.io.operand1 := regFile.io.rs1Data
  adder.io.operand2 := regFile.io.rs2Data

  regFile.io.rdData := adder.io.result

  // Debug signals
  // io.debug_pcInstAddr         := pc.io.instAddr
  // io.debug_instDecRs1         := instDec.io.rs1
  // io.debug_instDecRs2         := instDec.io.rs2
  // io.debug_instDecwriteEnable := instDec.io.writeEnable
  // io.debug_instDecRd          := instDec.io.rd
  // io.debug_regFileRs1Data     := regFile.io.rs1Data
  // io.debug_regFileRs2Data     := regFile.io.rs2Data
  // io.debug_adderResult        := adder.io.result
}
