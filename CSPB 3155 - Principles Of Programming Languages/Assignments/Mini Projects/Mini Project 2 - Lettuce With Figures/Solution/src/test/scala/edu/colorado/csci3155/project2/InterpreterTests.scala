package edu.colorado.csci3155.project2

import org.scalatest.FunSuite

class InterpreterTests extends FunSuite {
    test("Program 1")  {
        val s = TestPrograms.program1()
        val v1 = TestPrograms.parseAndInterpretProgram(s)
        v1 match {
            case FigValue(canvas) => {
                assert(canvas.numPolygons == 1)
                assert(canvas.numCircles == 1)
                assert(canvas.numVerticesTotal == 4)
            }
            case _ => assert(false)
        }
    }

    test("Program 2") {
        val s = TestPrograms.program2()
        val v1 = TestPrograms.parseAndInterpretProgram(s)
        v1 match {
            case FigValue(canvas) => {
                assert(canvas.numPolygons == 9)
                assert(canvas.numCircles == 3)
                assert(canvas.numVerticesTotal == 30)
            }
            case _ => assert(false)
        }
    }

    test("Program 3") {
        val s = TestPrograms.program3()
        val v1 = TestPrograms.parseAndInterpretProgram(s)
        v1 match {
            case FigValue(canvas) => {
                assert(canvas.numPolygons == 9)
                assert(canvas.numCircles == 0)
                assert(canvas.numVerticesTotal == 27)
            }
            case _ => assert(false)
        }
    }

    test("Serpinski") {
        val s = TestPrograms.serp()
        val v1 = TestPrograms.parseAndInterpretProgram(s)
        v1 match {
            case FigValue(canvas) => {
                assert(canvas.numPolygons == 243)
                assert(canvas.numCircles == 0)
                assert(canvas.numVerticesTotal == 729)


            }
            case _ => assert(false)
        }
    }

    test("Mandala") {
        val s = TestPrograms.mandala()
        val v1 = TestPrograms.parseAndInterpretProgram(s)
        v1 match {
            case FigValue(canvas) => {
                //print(canvas.numPolygons, canvas.numCircles, canvas.numVerticesTotal)
                assert(canvas.numPolygons==40)
                assert(canvas.numCircles==0)
                assert(canvas.numVerticesTotal==140)
            }
            case _ => assert(false)
        }
    }

    test("Petals") {
        val s = TestPrograms.petals()
        val v1 = TestPrograms.parseAndInterpretProgram(s)
        v1 match {
            case FigValue(canvas) => {
                //print(canvas.numPolygons, canvas.numCircles, canvas.numVerticesTotal)
                assert(canvas.numPolygons==40)
                assert(canvas.numCircles==40)
                assert(canvas.numVerticesTotal==120)
            }
            case _ => assert(false)
        }
    }


}
