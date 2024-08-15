package edu.colorado.csci3155.project1

import org.scalatest.FunSuite

class StackMachineTest extends FunSuite {

    def testValueOfIdent(env: Map[String, Double], x: String, f: Double) = {
        assert( env contains x)
        assert( math.abs(env(x) - f) <= 1E-05)
    }

    test("stack machine test 1") {
        val lst1 = List(PushI(2.5), PushI(3.5), AddI, LoadI("result"))
        val f = StackMachineEmulator.emulateStackMachine(lst1)
        assert(f("result") == 6.0)
    }

    test("stack machine test 2") {
        val lst1 = List(PushI(2.5), PushI(3.5), AddI, ExpI, LogI, LoadI("result"))
        val f = StackMachineEmulator.emulateStackMachine(lst1)
        assert(math.abs(f("result") - 6.0) <= 1e-05)
    }

    test("stack machine test 3") {
        val lst1 = List(PushI(3.5), PushI(2.5), PushI(4.5), PushI(5.2), AddI, LoadI("x"), LoadI("y"), LoadI("z"), StoreI("y"), LoadI("w"))
        val fenv = StackMachineEmulator.emulateStackMachine(lst1)
        assert(fenv contains "x")
        assert(fenv contains "y")
        assert(fenv contains "z")
        assert( math.abs(fenv("x") - 9.7 ) <= 1e-05 )
        assert( math.abs(fenv("y") - 2.5 ) <= 1e-05 )
        assert( math.abs(fenv("z") - 3.5 ) <= 1e-05 )
    }

    test("stack machine test 4") {
        val lst4 = List(PushI(3.5), PushI(2.5), PushI(4.5), PushI(5.2),  LoadI("x"), LoadI("y"), LoadI("z"), LoadI("w"),
                         StoreI("y"), StoreI("w"), AddI, LoadI("res1"), StoreI("x"), StoreI("z"), MultI, LoadI("res2"))
        val fenv = StackMachineEmulator.emulateStackMachine(lst4)
        assert(fenv contains "x")
        assert(fenv contains "y")
        assert(fenv contains "z")
        assert(fenv contains "w")
        assert(fenv contains "res1")
        assert(fenv contains "res2")
        testValueOfIdent(fenv, "x", 5.2)
        testValueOfIdent(fenv, "y", 4.5)
        testValueOfIdent(fenv, "z", 2.5)
        testValueOfIdent(fenv, "w", 3.5)
        testValueOfIdent(fenv, "res1", 8.0)
        testValueOfIdent(fenv, "res2", 5.2*2.5)
    }

    test("stack machine test 5") {
        val lst1 = List(PushI(1.5), PushI(2.4), AddI, PushI(2.5), PushI(2.5), MultI, SubI)
        val lst2 = List(PushI(1.0), PushI(2.5), AddI)
        val lst3 = lst1 ++ List(ExpI) ++ lst2 ++ List(ExpI) ++ List(AddI) ++ List(LogI) ++ List(LoadI("result"))
        val f = StackMachineEmulator.emulateStackMachine(lst3)
        assert(math.abs(f("result") - 3.50287) <= 1E-04)
    }


}
