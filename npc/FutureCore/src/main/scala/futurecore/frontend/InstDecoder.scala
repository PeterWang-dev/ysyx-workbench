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
package futurecore.frontend

import chisel3._
import chisel3.util.{switch, HasBlackBoxResource}
import chisel3.util.is

class InstDecoderIO extends Bundle {
  val inst        = Input(UInt(32.W))
  val rs1         = Output(UInt(5.W))
  val rs2         = Output(UInt(5.W))
  val rd          = Output(UInt(5.W))
  val writeEnable = Output(Bool())
  val isImmidiate = Output(Bool())
  val isEbreak    = Output(Bool())
}

class InstDecoder extends Module {
  val io = IO(new InstDecoderIO)

  io.rs1 := io.inst(19, 15)
  io.rs2 := io.inst(24, 20)
  io.rd  := io.inst(11, 7)

  // default value of control signals
  io.writeEnable := false.B
  io.isImmidiate := false.B
  io.isEbreak    := false.B

  // optcode decoder
  switch(io.inst(6, 0)) {
    is("b001_0011".U) { // addi
      io.writeEnable := true.B
      io.isImmidiate := true.B
    }
    is("b111_0011".U) { // ebreak
      io.isEbreak := Mux(io.inst(20), true.B, false.B)
    }
  }
}
