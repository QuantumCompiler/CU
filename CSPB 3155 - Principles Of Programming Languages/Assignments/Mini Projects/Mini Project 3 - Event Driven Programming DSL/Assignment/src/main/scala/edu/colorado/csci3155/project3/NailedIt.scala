package edu.colorado.csci3155.project3
import java.awt.Graphics2D
import java.awt.Color
import java.awt.geom._


import scala.swing._
import scala.swing.BorderPanel.Position._
import scala.swing.{BorderPanel, Button,  MainFrame, SimpleSwingApplication}
import scala.swing.event.{ButtonClicked, MouseClicked}
import scala.util.Random

case class Prick(x: Double, y: Double) extends Event {
    val radius = 10.0
    override def appliesTo(e: Entity): Boolean = e match {
        case Balloon(_, x1, y1, _, _) => math.sqrt( (x - x1)*(x-x1) + (y-y1)*(y-y1) ) <= radius
        case _ => false
    }
}
case class ClickHandler(val id: Int) extends Entity {
    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) = e match {
        case MouseClick(x, y) => {
            ( List(this, new Nail(global.numEntities+1, x, y)),
              List())
        }
        case _ => (List(this), List())
    }

    override def render(g: Graphics2D): Unit = ()
}

case class Balloon(val id: Int,
                   val x: Double =  100*Random.nextDouble(),
                   val y: Double = 100* Random.nextDouble(),
                   val dx: Double = -5 + 10 * Random.nextDouble(),
                   val dy: Double = -5 + 10 * Random.nextDouble() ) extends Entity {
    val radius = 10

    override def handleEvent(global: MainEventLoop) (e: Event): (List[Entity], List[Event]) =  e match {
        case Tick(delta) => {
            val newX = x + delta * dx
            val newDX = if (newX >= 10 && newX <= 490.0) dx else -dx
            val newY = y + delta * dy
            val newDY = if (newY >= 10 && newY <= 490.0) dy else -dy
            (List(new Balloon(id, newX, newY, newDX, newDY)), List())
        }
        case Stop => (List(), List())
        case Prick(x1, y1) =>{
            val newNails = List(1, 2, 3, 4, 5).map(v => new Nail(v + global.numEntities, x, y))
            (newNails, List())
       }
        case _ => (List(this), List())

    }
    override def render(g: Graphics2D): Unit = {
        g.setColor(Color.BLUE)
        g.fill(new Ellipse2D.Double(x, y, 10.0, 15.5))
    }
}


case class Nail(val id: Int,
           val x: Double = Random.nextDouble * 100 ,
           val y: Double = Random.nextDouble * 100,
           val dx : Double = -5 + Random.nextDouble * 10,
           val dy: Double = -5 + Random.nextDouble * 10) extends Entity {

    override def handleEvent (global: MainEventLoop) (e: Event): (List[Entity], List[Event]) = e match {
        case Tick(delta) => {
            val newX = x + delta * dx
            val newDX = if (newX  >= 10 && newX <= 490.0) dx else -dx
            val newY = y + delta * dy
            val newDY = if (newY >= 10 && newY <= 490.0) dy else -dy
            (
              List(new Nail(id, newX, newY, newDX, newDY)),
              List(new Prick(newX, newY))
            )
        }
        case Stop => (List(), List())

        case _ => {
            (List(this), List())
        }
    }
    override def render(g: Graphics2D): Unit = {
        g.setColor(Color.BLACK)
        g.fillPolygon(Array(x.toInt-3,x.toInt+3,x.toInt), Array(y.toInt-2,y.toInt-2, y.toInt+1), 3)
    }

}


object NailedIt extends SimpleSwingApplication {
    def top = new MainFrame {
        title = "Nailed It!"
        val global : MainEventLoop = new MainEventLoop
        global.entities = List( new ClickHandler(id = 0), new Balloon(-1), new Balloon(-2), new Balloon(0), new Balloon(1), new Balloon(2), new Balloon(3), new Nail(4), new Nail(5))
        global.events = List()

        val canvas = global.getDefaultCanvas(500, 500)

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

        size = new Dimension(500,550)
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

