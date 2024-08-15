name := "GameTest"

version := "0.1"

scalaVersion := "2.12.8"

resolvers += "Typesafe Repository" at "https://repo.typesafe.com/typesafe/releases/"

libraryDependencies ++= Seq(
    "org.scala-lang.modules" %% "scala-swing" % "2.0.3",
    "org.scalactic" %% "scalactic" % "3.0.5",
    "org.scalatest" %% "scalatest" % "3.0.5" % "test"
)

///
/// Everything that follows is for the `sbt checkAndZipSubmission` task
///
val zipFilePath = "submission.zip"
val confirmBeforeOverwrite = false


lazy val zipSubmission = taskKey[Unit]("Zip answer source files into submission")
zipSubmission := {
    val bd = baseDirectory.value
    // Scala task dependencies
    (Compile / compile).value

    def fail[T](message: String): T = {
        throw new sbt.MessageOnlyException(s"$message\nZip not made")
    }

    println("\n\n - This task does not check that your solution is correct, only that the files are in the correct place.\n   To run tests, use `sbt test` or run the 'Run All Tests' configuration in Intellij")

    // Relative -> absolute paths
    val rootPath = bd.getAbsolutePath
    val zipFileAbsPath = s"$rootPath/$zipFilePath"
    val srcAbsPath = s"$rootPath/src"

    // Ensure files exist and make zip list
    val srcAbsDir = new File(srcAbsPath)
    if (!srcAbsDir.isDirectory) fail(s"X Could not find src directory (expected at $srcAbsPath)")
    val submissionFilePairs: Traversable[(File, String)] = Path.allSubpaths(srcAbsDir)

    val zipFile = new File(zipFileAbsPath)
    if (zipFile.isFile && confirmBeforeOverwrite) {
        print("\n\n * INPUT REQUIRED: This will erase the old submission zip, continue?\n   Type 'y' or 'n' and press enter: ")
        val input = scala.io.StdIn.readChar()
        if (input != 'y') {
            fail("Canceled by user")
        }
    }

    println("\n\n - Saving zip of files:")
    println(submissionFilePairs
      .map { case (_, path) => "      " + path }
      .mkString("\n"))
    println("   to:")
    println("      " + zipFileAbsPath + "\n\n")

    IO.zip(submissionFilePairs , new File(zipFileAbsPath))
}
