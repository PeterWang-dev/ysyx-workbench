// import Mill dependency
import mill._
import mill.scalalib._
// support BSP
import mill.bsp._

object futurecore extends SbtModule with scalafmt.ScalafmtModule { m =>
  override def scalaVersion = "2.13.12"
  override def scalacOptions = Seq(
    "-language:reflectiveCalls",
    "-deprecation",
    "-feature",
    "-Xcheckinit"
  )
  override def ivyDeps = Agg(
    ivy"org.chipsalliance::chisel:6.0.0"
  )
  override def scalacPluginIvyDeps = Agg(
    ivy"org.chipsalliance:::chisel-plugin:6.0.0"
  )
  object test extends SbtModuleTests with TestModule.ScalaTest {
    override def ivyDeps = m.ivyDeps() ++ Agg(
      ivy"org.scalatest::scalatest::3.2.16",
    )
  }
  def repositoriesTask = T.task {
    Seq(
      coursier.MavenRepository("https://maven.aliyun.com/repository/central"),
      coursier.MavenRepository("https://repo.scala-sbt.org/scalasbt/maven-releases")
    ) ++ super.repositoriesTask()
  }
}
