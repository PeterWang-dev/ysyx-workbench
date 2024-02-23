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

import futurecore.frontend._
import futurecore.backend._

class DebugSignals extends Bundle {
  val pcInstAddr = Output(UInt(32.W))

  val instDecRs1         = Output(UInt(5.W))
  val instDecRs2         = Output(UInt(5.W))
  val instDecRd          = Output(UInt(5.W))
  val instDecWriteEnable = Output(Bool())
  val instDecIsImmidiate = Output(Bool())

  val regFileRs1Data = Output(UInt(32.W))
  val regFileRs2Data = Output(UInt(32.W))

  val immGenImmidiate = Output(UInt(32.W))

  val adderResult = Output(UInt(32.W))
}

class FutureCoreIO extends Bundle {
  val instAddrOut = Output(UInt(32.W))
  val instIn      = Input(UInt(32.W))
  // val debug       = new DebugSignals
}

class FutureCore extends Module {
  val io      = IO(new FutureCoreIO)
  val pc      = Module(new ProgramCounter)
  val instDec = Module(new InstDecoder)
  val regFile = Module(new RegFile)
  val immGen  = Module(new ImmGenerator)
  val adder   = Module(new Adder)

  io.instAddrOut  := pc.io.instAddr
  instDec.io.inst := io.instIn

  regFile.io.rs1Addr     := instDec.io.rs1
  regFile.io.rs2Addr     := instDec.io.rs2
  regFile.io.writeEnable := instDec.io.writeEnable
  regFile.io.rdAddr      := instDec.io.rd

  immGen.io.inst := io.instIn
  val isImm = instDec.io.isImmidiate

  adder.io.operand1 := regFile.io.rs1Data
  adder.io.operand2 := Mux(isImm, immGen.io.immidiate, regFile.io.rs2Data)

  regFile.io.rdData := adder.io.result

  // Debug signals
  // io.debug.pcInstAddr := pc.io.instAddr

  // io.debug.instDecRs1         := instDec.io.rs1
  // io.debug.instDecRs2         := instDec.io.rs2
  // io.debug.instDecRd          := instDec.io.rd
  // io.debug.instDecWriteEnable := instDec.io.writeEnable
  // io.debug.instDecIsImmidiate := instDec.io.isImmidiate

  // io.debug.regFileRs1Data := regFile.io.rs1Data
  // io.debug.regFileRs2Data := regFile.io.rs2Data

  // io.debug.immGenImmidiate := immGen.io.immidiate

  // io.debug.adderResult := adder.io.result
  // dontTouch(io.debug.pcInstAddr)
}
