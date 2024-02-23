
import chisel3._
// import chisel3.simulator.EphemeralSimulator._
import chiseltest._
import chiseltest.ChiselScalatestTester
import org.scalatest.flatspec.AnyFlatSpec

// class ProgramCounterSpec extends AnyFlatSpec {
class ProgramCounterSpec extends AnyFlatSpec with ChiselScalatestTester {
  "ProgramCounter" should "point to next instruction without any input" in {
    // simulate(new ProgramCounter) { c =>
    //   c.io.instAddr.expect(0.U)
    //   c.clock.step()
    //   c.io.instAddr.expect(4.U)
    // }
    test(new ProgramCounter) { c =>
      c.io.instAddr.expect(0.U)
      c.clock.step()
      c.io.instAddr.expect(4.U)
    }
  }
}
