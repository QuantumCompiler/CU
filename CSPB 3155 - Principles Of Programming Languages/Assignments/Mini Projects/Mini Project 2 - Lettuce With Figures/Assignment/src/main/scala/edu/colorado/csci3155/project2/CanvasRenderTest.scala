package edu.colorado.csci3155.project2

/*
  You can run the CanvasRenderTest below. However, nothing in this file
  should be edited for your project. This code uses swing to render graphics
  objects on a window.
 */

import scala.swing._
import scala.swing.BorderPanel.Position._
import scala.swing.{BorderPanel, Button,  MainFrame, SimpleSwingApplication}
import scala.swing.event.{ButtonClicked, MouseClicked}


class DrawingCanvas extends Panel{
    var canvas: Option[MyCanvas] = None

    override def paintComponent(g: Graphics2D) = {
       canvas match {
           case Some(c) => c.render(g, 500, 500)
           case _ => ()
        }
    }

    def setCanvas(c: MyCanvas) { canvas = Some(c)}
}

object CanvasRenderTest extends SimpleSwingApplication {
    def top = new MainFrame {
        title = "Testing Operations on Figs"
        val canvas = new DrawingCanvas {
            preferredSize = new Dimension(500,500)
        }
        val textArea = new TextArea("Program"){
            editable = false
            name = "Program"
            text = TestPrograms.mandala()
        }
        val button1 = new Button {
            text = "mandala"
            borderPainted = true
            enabled = true
            tooltip = "Click and See"
        }
        val button2 = new Button {
            text = "serpinski"
            borderPainted = true
            enabled = true
            tooltip = "Click and See"
        }

        def execProgram(name: String, fun: () => String) = {
            println(name)
            val v = TestPrograms.parseAndInterpretProgram(fun())
            v match {
                case FigValue(myc) => { canvas.setCanvas (myc); canvas.repaint()}
                case _ => assert(false)
            }
        }

        menuBar = new MenuBar {
            contents += new MenuItem(Action("Program1"){
                execProgram("Program1", TestPrograms.program1)
                textArea.text = TestPrograms.program1()
            })
            contents += new MenuItem(Action("Program2"){
                execProgram("Program2", TestPrograms.program2)
                textArea.text = TestPrograms.program2()
            })
            contents += new MenuItem(Action("Program3"){
                execProgram("Program3", TestPrograms.program3)
                textArea.text = TestPrograms.program3()
            })
            contents += new MenuItem(Action("Program4"){
                execProgram("Program4", TestPrograms.program4)
                textArea.text = TestPrograms.program4()
            })

            contents += new MenuItem(Action("Program5"){
                execProgram("Program5", TestPrograms.program5)
                textArea.text = TestPrograms.program5()
            })
            contents += new MenuItem(Action("Petals"){
                execProgram(name="Petals", TestPrograms.petals)
                textArea.text = TestPrograms.petals()
            })
            contents += new MenuItem( Action("Serpinski") {
                execProgram("Serpinski", TestPrograms.serp)
                textArea.text = TestPrograms.serp()
            })
            contents += new MenuItem(
                Action("Mandala") {
                    execProgram("Mandala", TestPrograms.mandala)
                    textArea.text = TestPrograms.mandala()
                }
            )


        }
        contents = new BorderPanel {
            layout(canvas) = Center
            layout(textArea) = West
        }
        size = new Dimension(1500,500)


    }
}
