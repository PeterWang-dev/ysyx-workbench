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

class RegFileIO extends Bundle {
  // asynchronus read
  val addrRead1 = Input(UInt(5.W))
  val addrRead2 = Input(UInt(5.W))
  val dataRead1 = Output(UInt(32.W))
  val dataRead2 = Output(UInt(32.W))
  // synchronous write
  val writeEnable = Input(Bool())
  val addrWrite   = Input(UInt(5.W))
  val dataWrite   = Input(UInt(32.W))
}

class RegFile extends Module {
  val io   = IO(new RegFileIO)
  val regs = Vec(32, RegInit(0.U(32.W)))

  io.dataRead1 := regs(io.addrRead1)
  io.dataRead2 := regs(io.addrRead2)

  when(io.writeEnable) {
    regs(io.addrWrite) := Mux(io.addrWrite === 0.U, 0.U, io.dataWrite)
  }
}
