package edu.colorado.csci3155.project3

import java.awt.Graphics2D
import java.awt.Color
import java.awt.geom._


import scala.swing._
import scala.swing.BorderPanel.Position._
import scala.swing.{BorderPanel, Button,  MainFrame, SimpleSwingApplication}
import scala.swing.event.{ButtonClicked, MouseClicked}
import scala.util.Random

case class NodeStatus(isAlive: Boolean, x: Int, y: Int ) extends Event {
    override def appliesTo(e: Entity): Boolean = e match {
        case Node(_, x1, y1, _, _) => {
            ( (x1 != x) || (y1 != y) ) &&  (-1 <= x1 - x && x1 - x <= 1) && (-1 <= y1 - y && y1 - y <= 1 )
        }
        case _ => false
    }
}

case class Node ( id: Int, x: Int, y: Int, isAlive: Boolean,  neighborState: Map[(Int, Int), Boolean]) extends Entity {
    def computeNewStatus: Boolean = {
        if (neighborState.size < 3) {
            println(s"Warning number of neighbors is ${neighborState.size}")
            isAlive
        } else {
            val numLiveCell = neighborState.foldLeft[Int](0) {
                case (j, (_, alive)) => if (alive) j + 1 else j
            }

            if (isAlive) {
                if ((numLiveCell < 2) || (numLiveCell > 3))
                    false
                else
                    true
            } else {
                if (numLiveCell == 3)
                    true
                else
                    false
            }
        }
    }

    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) = e match {
        case NodeStatus(nAlive, x1, y1 ) => {
            val newNeighborState = neighborState + ((x1, y1) -> nAlive)
            (List(new Node(id, x, y, isAlive, newNeighborState)), List())
        }
        case Tick(_) => {
            val newStatus = this.computeNewStatus

            (List( Node(id, x, y, newStatus, neighborState)), List( NodeStatus(newStatus, x, y)))
        }
        case MouseClick(x1, y1) => {
            if ( 0 <= (x1 - 20.0 *x) && (x1 - 20.0 *x) <= 20 && 0 <= (y1 - 20*y) && (y1 - 20*y) <= 20){
                (List(new Node(id, x, y, !isAlive, neighborState)), List(NodeStatus(!isAlive, x, y)))
            } else {
                (List(this), List())
            }
        }
        case Stop => {
            (List(), List())
        }
        case _ => {
            (List(this), List())
        }
    }

    override def render(g: Graphics2D): Unit = {

        if (isAlive){
            g.setColor(Color.BLACK)
            g.setPaint(Color.BLACK)
            g.fillRect(20*x, 20*y, 20, 20)
           // g.drawString("A", 40*x+20, 40*y+20)

        } else {
            g.setColor(Color.BLACK)
            g.drawRect(20*x, 20*y, 20, 20)
            g.setColor(Color.RED)
            g.fillRect(20*x, 20*y, 20, 20)
           // g.drawString("D", 40*x+20, 40*y+20)
        }
    }
}




object GameOfLifeAnimation extends SimpleSwingApplication {
    def top = new MainFrame {
        title = "Game of Life"

        val global : MainEventLoop = new MainEventLoop()

        (1 to 40).foreach( x => {
            (1 to 40).foreach ( y => {
                global.addEntity(new Node(x * y, x, y, Random.nextBoolean(), Map.empty[(Int, Int), Boolean]))
            })
        })


        val canvas = global.getDefaultCanvas(900, 900)

        val button = new Button {
            text = "STOP!"
            foreground = Color.blue
            background = Color.red
            borderPainted = true
            enabled = true
            tooltip = "Click and See"
        }

        contents = new BorderPanel {
            layout(canvas) = Center
            layout(button) = South

        }
        listenTo(canvas.mouse.clicks)
        listenTo(button)

        size = new Dimension(900,900)
        reactions += {
            case MouseClicked(_, point, _, _, _) =>{
                global.click(point.x, point.y)
            }
            case ButtonClicked(c) if c == button =>{
                global.stop()
            }
        }

        global.start(canvas)
    }
}
