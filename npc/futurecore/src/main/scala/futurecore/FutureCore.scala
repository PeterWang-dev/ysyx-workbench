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
  val debug_pcInstAddr       = Output(UInt(32.W))
  val debug_instDecInst      = Output(UInt(32.W))
  val debug_regFileAddrRead1 = Output(UInt(32.W))
  val debug_regFileAddrRead2 = Output(UInt(32.W))
  val debug_regFileDataRead1 = Output(UInt(32.W))
  val debug_regFileDataRead2 = Output(UInt(32.W))
  val debug_regFileWriteEn   = Output(Bool())
  val debug_regFileAddrWrite = Output(UInt(32.W))
  val debug_regFileDataWrite = Output(UInt(32.W))
  val debug_adderOperand1    = Output(UInt(32.W))
  val debug_adderOperand2    = Output(UInt(32.W))
  val debug_adderResult      = Output(UInt(32.W))
}

class FutureCore extends Module {
  val io      = IO(new FutureCoreIO)
  val pc      = Module(new ProgramCounter)
  val instDec = Module(new InstDecoder)
  val regFile = Module(new RegFile)
  val adder   = Module(new Adder)

  io.instAddrOut  := pc.io.instAddr
  instDec.io.inst := io.instIn

  regFile.io.addrRead1   := instDec.io.regAddrRead1
  regFile.io.addrRead2   := instDec.io.regAddrRead2
  regFile.io.writeEnable := instDec.io.regWriteEnable
  regFile.io.addrWrite   := instDec.io.regAddrWrite

  adder.io.operand1 := regFile.io.dataRead1
  adder.io.operand2 := regFile.io.dataRead2

  regFile.io.dataWrite := adder.io.result
}
