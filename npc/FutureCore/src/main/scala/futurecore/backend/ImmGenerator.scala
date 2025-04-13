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
package futurecore.backend

import chisel3._
import chisel3.util.{Cat, Fill}

class ImmGeneratorIO extends Bundle {
  val inst      = Input(UInt(32.W))
  val immidiate = Output(UInt(32.W))
}

class ImmGenerator extends Module {
  val io   = IO(new ImmGeneratorIO)
  val inst = io.inst
  val immI = Wire(UInt(32.W))
  val immS = Wire(UInt(32.W))
  val immB = Wire(UInt(32.W))
  val immU = Wire(UInt(32.W))
  val immJ = Wire(UInt(32.W))

  immI := Cat(Fill(20, inst(31)), inst(31, 20))
  immS := Cat(Fill(20, inst(31)), inst(31, 25), inst(11, 7))
  immB := Cat(Fill(19, inst(31)), inst(31), inst(7), inst(30, 25), inst(11, 8), 0.U)
  immU := Cat(inst(31, 12), Fill(12, 0.U))
  immJ := Cat(Fill(11, inst(31)), inst(31), inst(19, 12), inst(20), inst(30, 21), 0.U)

  io.immidiate := immI // TODO: Add support for other immediates
}
