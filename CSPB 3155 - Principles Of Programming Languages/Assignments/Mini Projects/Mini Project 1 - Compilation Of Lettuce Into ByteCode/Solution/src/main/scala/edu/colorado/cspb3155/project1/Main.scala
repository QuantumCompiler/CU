package edu.colorado.csci3155.project1

object Main {
    def main(args: Array[String]) = {
        val e = Plus(Log(Plus(Const(1.0), Mult(Const(3.0), Exp(Const(4.1))))), Const(1.0))
        val instrList:List[StackMachineInstruction] = StackMachineCompiler.compileToStackMachineCode(e)
        println("Compiled Instructions")
        instrList.foreach {
            case ins => println(ins)
        }
        println("Emulated Value")
        println(StackMachineEmulator.emulateStackMachine(instrList))

        val e1 = Minus(Const(2.0), Minus(Const(3.0), Const(5.0)))
        val instrList2:List[StackMachineInstruction] = StackMachineCompiler.compileToStackMachineCode(e1)
        println("Compiled Instructions")
        instrList2.foreach {
            case ins => println(ins)
        }
        println("Emulated Value")
        println(StackMachineEmulator.emulateStackMachine(instrList2))
    }
}
