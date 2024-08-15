import java.nio.file.Paths

name := "cspb3155_project1"
version := "0.1"
scalaVersion := "2.11.12"
version := "0.1"
libraryDependencies ++= List(
    "org.scalactic" %% "scalactic" % "3.0.5",
    "org.scalatest" %% "scalatest" % "3.0.5" % "test"
)
unmanagedSources / excludeFilter := HiddenFileFilter || "*checkpoint*"

///
/// Everything that follows is for the `sbt checkAndZipSubmission` task
///

val solnFilePaths = List(
    "src/main/scala/edu/colorado/cspb3155/project1/Main.scala",
    "src/main/scala/edu/colorado/cspb3155/project1/StackMachineCompiler.scala",
    "src/main/scala/edu/colorado/cspb3155/project1/StackMachineEmulator.scala"
)
val testsPath = "src/test/scala/edu/colorado/cspb3155/project1"
val extraPath = "extra_submission_files"
val zipFilePath = "submission.zip"
val confirmBeforeOverwrite = false


lazy val checkAndZipSubmission = taskKey[Unit]("Zip answer source files into submission")
checkAndZipSubmission := {
    // Scala task dependencies
    val bd = baseDirectory.value
    (Compile / compile).value

    def fail[T](message: String): T = {
        throw new sbt.MessageOnlyException(s"$message\nZip not made")
    }

    println("\n\n - This task does not check that your solution is correct, only that the files are in the correct place.\n   To run tests, use `sbt test` or run the 'Run All Tests' configuration in Intellij")

    // Relative -> absolute paths
    val rootPath = bd.getAbsolutePath
    val solnFileAbsPaths = solnFilePaths map { path => s"$rootPath/$path"  }
    val zipFileAbsPath = s"$rootPath/$zipFilePath"
    val testsAbsPath = s"$rootPath/$testsPath"
    val extraAbsPath = s"$rootPath/$extraPath"

    // Ensure files exist and make zip list
    val testsAbsDir = new File(testsAbsPath)
    if (!testsAbsDir.isDirectory) fail(s"Test directory")
    var submissionFilePairs: List[(File,String)] = (solnFileAbsPaths map {
        solnFileAbsPath => {
            val maybeFile = new File(solnFileAbsPath)
            if (maybeFile.isFile) {
                (maybeFile, Paths.get(solnFileAbsPath).getFileName.toString)
            } else {

                // TODO: Possible bug report?
                // fail(s"File \"$solnFileAbsPath\" could not be found.")

                fail("File \"" + solnFileAbsPath + "\" could not be found.")
            }
        }
    }) ++ Path.allSubpaths(testsAbsDir) ++ Path.allSubpaths(new File(extraAbsPath))

    val zipFile = new File(zipFileAbsPath)
    if (zipFile.isFile && confirmBeforeOverwrite) {
        print("\n\n * INPUT REQUIRED: This will erase the old submission zip, continue?\n   Type 'y' or 'n' and press enter: ")
        val input = scala.io.StdIn.readChar()
        if (input != 'y') {
            fail("")
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
