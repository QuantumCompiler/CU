package edu.colorado.csci3155.project3

import java.awt.{Color, Font, Graphics2D}

import scala.swing.{BorderPanel, Button, ButtonGroup, Dimension, FlowPanel, MainFrame, SimpleSwingApplication}
import scala.swing.BorderPanel.Position._
import scala.swing.event.{ButtonClicked, MouseClicked}

case object EmergencyNS extends Event {
    override def appliesTo(e: Entity) = true // Applies to all entities
}

case object EmergencyEW extends Event {
    override def appliesTo(e: Entity) = true // Applies to all entities
}

object Timings {
    val GreenTimer = 50
    val YellowTimer = 20
    val RedTimer = 70
}

object SignalColors extends Enumeration {
    val Green=Value(1)
    val Red = Value(2)
    val Yellow = Value(3)
    def nextSignal(cur: Value): (Value, Int) = cur match {
        case Green => (Yellow, Timings.YellowTimer)
        case Yellow => (Red, Timings.RedTimer)
        case Red => (Green, Timings.GreenTimer)
    }
}

/* Let us define a new case class called Signal that extends Entity */
case class Signal(id: Int, // id is going to determine which signal we are talking about
                  signalState: SignalColors.Value, // This is the current color of the signal
                  timeLeft: Int  // This is how long the signal must stay in that color.
                 ) extends Entity {

    // This is the most important function -- event handler for the entity.
    // It takes in a reference to the MainEventLoop which is ignored here
    // It also takes in a event e as input and must return a transformed list of new entities and a list of
    // newly generated events.
    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) = e match {
        // The event is a time tick event. We will assume each tick = 1 seconds for our animation.
        case Tick(_) => {
            val newTimeLeft = timeLeft - 1 // Decrement the amount of time left
            if (newTimeLeft > 0 ){ // We still have time left in the current color
                // Create a new Signal with same id
                //                          same signal color
                //                          newTimeLeft decrements current timeLeft by 1
                val entityList = List(Signal(id, signalState, newTimeLeft))
                val eventList = List() // We are not generating any new events
                ( entityList, eventList ) // Return the new transformed entity list and newly generated events
            } else {
                // Or else, we ran out of time in the current color
                // DEtermine the new color and the new time left
                val (nextState, newTimeLeft) = SignalColors.nextSignal(signalState)
                // Transform myself into a signal of the new color and new time left
                // No events need to be generated.
                (List(Signal(id, nextState , newTimeLeft )), List())
            }
        }
        // Handle a EmergencyEW events
        case EmergencyEW => {
            if (id == 1 || id == 2) {
                // If signal id is 1 or 2, then they must immediately go to green
                (List(Signal(id, SignalColors.Green, Timings.GreenTimer)), List())
            } else {
                // If signal id is not 1 and not 2, then them must immediately go to red
                (List(Signal(id, SignalColors.Red, Timings.RedTimer)), List())
            }
        }
        // Handle EmergencyNS events
        case EmergencyNS=> {
            if (id == 3 || id == 4) {
                // Signal IDs 3 an 4 go to green
                (List(Signal(id, SignalColors.Green, Timings.GreenTimer)), List())
            } else {
                // Other signals go to red
                (List(Signal(id, SignalColors.Red, Timings.RedTimer)), List())
            }
        }

        // Handle Stop event ==> Delete myself and generate no further events
        case Stop => (List(), List())
        // Any other event should be ignored by just propagate this entity unchanged and no new events
        case _ => (List(this), List())
    }

    override def render(g: Graphics2D): Unit = {
        // Draw a box and three circles inside
        val (xLo: Int, yLo: Int) = id match {
            case 1 => (20,50)
            case 2 => (120, 50)
            case 3 => (220, 50)
            case 4 => (320, 50)
            case _ => assert(false)
        }
        g.setColor(Color.BLACK)
        g.drawRect(xLo, yLo-20, 100, 340)
        g.setFont(new Font("Arial",1,28))
        g.drawString(s"$id", xLo+50, yLo-25)
        g.drawString(s"$timeLeft", xLo+50,yLo+350)
        g.setColor(Color.RED)
        g.drawOval(xLo + 25, yLo +250, 50, 50)
        g.setColor(Color.YELLOW)
        g.drawOval(xLo+25, yLo+150, 50, 50)
        g.setColor(Color.GREEN)
        g.drawOval(xLo+25, yLo+50, 50, 50)
        if (signalState == SignalColors.Red) {
            g.setColor(Color.RED)
            g.fillOval(xLo + 25, yLo + 250, 50, 50)
        } else if (signalState == SignalColors.Yellow){
            g.setColor(Color.YELLOW)
            g.fillOval(xLo+25, yLo+150, 50, 50)
        } else {
            g.setColor(Color.GREEN)
            g.fillOval(xLo+25, yLo+50, 50, 50)
        }

    }
}

object TrafficLightAnimation extends SimpleSwingApplication {
    def top = new MainFrame {
        title = "Traffic Light"
        val global : MainEventLoop = new MainEventLoop()
        global.addEntity(new Signal(1, SignalColors.Green, Timings.GreenTimer))
        global.addEntity(new Signal(2, SignalColors.Green, Timings.GreenTimer))
        global.addEntity(new Signal(3, SignalColors.Red, Timings.RedTimer))
        global.addEntity(new Signal(4, SignalColors.Red, Timings.RedTimer))

        val canvas = global.getDefaultCanvas(500, 500)

        val button = new Button {
            text = "STOP!"
            foreground = Color.blue
            background = Color.red
            borderPainted = true
            enabled = true
            tooltip = "Click and See"
        }

        val emergencyNSButton = new Button {
            text = "Emergency (North-South)"
            foreground = Color.blue
            background = Color.red
            borderPainted = true
            enabled = true
            tooltip = "Click and See"
        }

        val emergencyEWButton = new Button {
            text = "Emergency (East-West)"
            foreground = Color.blue
            background = Color.red
            borderPainted = true
            enabled = true
            tooltip = "Click and See"
        }


        contents = new FlowPanel {
            contents += canvas
            contents += button
            contents += emergencyNSButton
            contents += emergencyEWButton
        }
        listenTo(button)
        listenTo(emergencyNSButton)
        listenTo(emergencyEWButton)

        size = new Dimension(500,600)
        reactions += {
            case MouseClicked(_, point, _, _, _) =>{
                global.click(point.x, point.y)
            }
            case ButtonClicked(c) if c == button =>{
                global.stop()
            }
            case ButtonClicked(c) if c == emergencyEWButton => {
                global.addEvent (EmergencyEW)
            }

            case ButtonClicked(c) if c == emergencyNSButton => {
                global.addEvent (EmergencyNS)
            }
        }

        global.start(canvas)
    }
}

