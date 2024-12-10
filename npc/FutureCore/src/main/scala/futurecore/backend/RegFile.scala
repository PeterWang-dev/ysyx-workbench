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
  val rs1Addr = Input(UInt(5.W))
  val rs2Addr = Input(UInt(5.W))
  val rs1Data = Output(UInt(32.W))
  val rs2Data = Output(UInt(32.W))
  // synchronous write
  val writeEnable = Input(Bool())
  val rdAddr      = Input(UInt(5.W))
  val rdData      = Input(UInt(32.W))
}

class RegFile extends Module {
  val io      = IO(new RegFileIO)
  val regBank = Mem(32, UInt(32.W))

  io.rs1Data := Mux(io.rs1Addr =/= 0.U, regBank.read(io.rs1Addr), 0.U)
  io.rs2Data := Mux(io.rs2Addr =/= 0.U, regBank.read(io.rs2Addr), 0.U)

  when(io.writeEnable) {
    regBank.write(io.rdAddr, Mux(io.rdAddr =/= 0.U, io.rdData, 0.U))
  }
}
