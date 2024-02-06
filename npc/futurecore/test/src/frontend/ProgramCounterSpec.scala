package futurecore.frontend

import chisel3._
import chiseltest._
import utest._

object ProgramCounterSpec extends ChiselUtestTester {
  val tests = Tests {
    test("ProgramCounter point to next instruction") {
      testCircuit(new ProgramCounter) { c =>
        c.io.instAddr.expect(0.U)
        c.clock.step()
        c.io.instAddr.expect(4.U)
      }
    }
  }
}
