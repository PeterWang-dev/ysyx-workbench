// import Mill dependency
import mill._
import mill.scalalib._
// support BSP
import mill.bsp._

object FutureCore extends SbtModule with scalafmt.ScalafmtModule { m =>
  def useChisel5            = true
  def chiselVersion         = if (useChisel5) "5.1.0" else "6.0.0"
  override def scalaVersion = "2.13.12"
  override def scalacOptions = Seq(
    "-language:reflectiveCalls",
    "-deprecation",
    "-feature",
    "-Xcheckinit"
  )
  override def ivyDeps = Agg(
    ivy"org.chipsalliance::chisel:${chiselVersion}"
  )
  override def scalacPluginIvyDeps = Agg(
    ivy"org.chipsalliance:::chisel-plugin:${chiselVersion}"
  )
  object test extends SbtModuleTests with TestModule.ScalaTest {
    override def ivyDeps = m.ivyDeps() ++ Agg(
      ivy"org.scalatest::scalatest::3.2.16",
      if (useChisel5)
        ivy"edu.berkeley.cs::chiseltest:5.0.0"
      else
        null
    )
  }
  def repositoriesTask = T.task {
    Seq(
      coursier.MavenRepository("https://maven.aliyun.com/repository/central"),
      coursier.MavenRepository("https://repo.scala-sbt.org/scalasbt/maven-releases")
    ) ++ super.repositoriesTask()
  }
}
