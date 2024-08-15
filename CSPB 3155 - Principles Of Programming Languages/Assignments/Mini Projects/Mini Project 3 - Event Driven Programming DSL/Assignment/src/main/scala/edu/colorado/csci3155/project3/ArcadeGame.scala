package edu.colorado.csci3155.project3

import java.awt.{Color, Font, Graphics2D}

import scala.util.Random
import scala.swing.BorderPanel.Position._
import scala.swing.{BorderPanel, Button, Dimension, FlowPanel, MainFrame, SimpleSwingApplication}
import scala.swing.event.{ButtonClicked, Key, KeyPressed, KeyTyped, MouseClicked}

/* ArcadeGame:
    The game has a dartshooter at the bottom of the canvas that shoots dart when the "space" key is pressed on the
    keyboard. The dartshooter can move left/right using the arrow keys.

    The dart shooter fires a dart at baloons that float by on the top. If it hits a baloon, we get some points and
    some darts get added back. Otherwise, each baloon that leaves the screen unshot will reduce points.

    Author: Sriram Sankaranarayanan <srirams@colorado.edu>
    CSCI 3155 Project # 3 on Event Driven Programming
 */

/*
    ScreenDimensions has important parameters that we will use
 */
object ScreenDimensions {
    val width = 500 // The overall width/height of the game canvas
    val height = 800
    val shooterMin = 50 // The minimum x value for the dart shooter
    val shooterMax = 450  // The maximum x value for the d.s.
    val dartSpeed = 40 // The vertical speed of the dart
    val baloonBurstDistance = 30 // The maximum distance between dart and baloon for collision
    val numDartsAdded = 10 // The number of darts added back to the shooter each time a baloon is hit
    val pointsBaloonBurst = 10 // Points for hitting a baloon
    val pointsBaloonEscaped = -25 // Points for missing a baloon
}

/*
    Events are now declared
 */

/* The Move event asks dart shooter to move by dx (can be negative) */
case class Move(dx: Int) extends Event {
    /*- TODO: Define the appliesTo method so that this event can only be sent to the DartShooter Entity -*/
    override def appliesTo(e: Entity): Boolean = ???
}

case object ShootDart extends Event {
    /*- TODO: Define the appliesTo method so that this event can only be sent to the DartShooter Entity -*/
    override def appliesTo(e: Entity): Boolean = ???
}

case object BaloonEscaped extends Event {
    /*- TODO: Define the appliesTo method so that this event can only be sent to the ArcadeGameManager Entity -*/
    override def appliesTo(e: Entity): Boolean = ???
}

case object BaloonBurst extends Event {
    /*- TODO: Define the appliesTo method so that this event can only be sent to the ArcadeGameManager or DartShooter Entities -*/
    override def appliesTo(e: Entity): Boolean = ???
}

case class Boom(x: Double, y: Double) extends Event {
    override def appliesTo(e: Entity): Boolean = e match {
        case ArcadeBaloon(_, x1, y1, _) => {
           ??? /*-- TODO: Boom applies to an arcade baloon iff euclidean distance between (x1, y1) and (x,y) is less than ScreenDimensions.baloonBurstDistance --*/
        }
        case _ => false
    }
}

/*--
Entities are now defined
--*/


/*
    Entity: ArcadeGameManager(gamePoints)

    Functions:
       1. Randomly create Baloons
       2. Maintain the number of points the user has scored so far

 */

case class ArcadeGameManager(val gamePoints: Int) extends Entity {
    val id: Int = 0 // Hardwire the id to 0

    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) = e match {
        case Tick(_) => {
            ??? // TODO: see document on how ArcadeGameManager must handle the Tick event.
        }
        case BaloonEscaped => ??? //TODO: Add points given by ScreenDimensions.pointsBaloonEscaped, no new events
        case BaloonBurst => ??? //TODO: Add points given by ScreenDimensions.pointsBaloonBurst, no new events
        case Stop => ??? // TODO: Empty list of entities and events to stop the trampoline.
        case _ => ??? //TODO: Return this entity unchanged and the empty list of events.
    }

    /*- Graphics Render -*/
    override def render(g: Graphics2D): Unit = {
        if (gamePoints < 0)
            g.setColor(Color.RED) // Negative points to be shown in red
        else
            g.setColor(Color.GREEN) // Positive game points to be shown in green
        // Set font
        g.setFont(new Font("Helvetica", 1, 24))
        // Show the game points at somewhere near top right of the screen
        g.drawString(s"Points: $gamePoints",ScreenDimensions.width-200, 75)
    }
}

/*
 Entity: ArcadeBaloon
    This manages a baloon that floats above the shooter and drifts either left to right or right to left.
    id: integer id
    x, y: coordinates of the baloon on canvas
    driftX : rate at which the baloon is moving. +ve => move right on screen; -ve => move left on the screen
 */
case class ArcadeBaloon(id: Int, x: Double, y: Double, driftX: Double = 10.0 * Random.nextDouble) extends Entity {
    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) =
        e match {
            case Tick(delta) => {
                ??? /*- TODO: handle tick event for ArcadeBaloon -*/
            }
            case Boom(_, _) => {
                (List(), List(BaloonBurst))
            }
            case Stop => (List(), List())
            case _ => (List(this), List())
        }

    override def render(g: Graphics2D): Unit = {
        g.setColor(Color.CYAN)
        g.fillOval(x.toInt -20,y.toInt -10, 40, 20)
    }


}

case class Dart(id: Int, x: Double, y: Double) extends Entity{
    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) = e match  {
        case Tick(delta) => {
           ??? /*- TODO: handle tick event for Dart -*/
        }
        case Stop => (List(), List())
        case _ => (List(this), List())
    }

    override def render(g: Graphics2D): Unit = {
        g.setColor(Color.RED)
        //g.fillRect(x.toInt-10, y.toInt, 20, 30)
        g.fillPolygon(Array(x.toInt-10, x.toInt+10, x.toInt ), Array(y.toInt, y.toInt, y.toInt-15), 3)
    }
}
/*
    Entity DartShooter: The dart shooter entity at the bottom of the screen.
    The implementation is given for your reference.
 */
case class DartShooter(x: Int = ScreenDimensions.width/2, numDarts: Int) extends Entity {
    override val id: Int = 1
    val y: Int = ScreenDimensions.height - 20

    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) =
        e match {
            case Move(dx) => {
                val x1 = x + dx
                val newX = {
                    if (x1 <= ScreenDimensions.shooterMin) ScreenDimensions.shooterMin
                    else if (x1 >= ScreenDimensions.shooterMax) ScreenDimensions.shooterMax
                    else x1
                }
                (List(DartShooter(newX, numDarts)), List())
            }
            case ShootDart => {
                if (numDarts > 0){
                    val newDart = Dart(global.numEntities+1, x, y - 70)
                    (List(DartShooter(x, numDarts-1), newDart), List())
                } else {
                    (List(this), List())
                }
            }
            case BaloonBurst => {
                (List(DartShooter(x, numDarts+ScreenDimensions.numDartsAdded)), List())
            }
            case Stop => (List(), List())
            case _ => (List(this), List())
        }

    override def render(g: Graphics2D): Unit = {
        g.setColor(Color.RED)
        g.fillRect(x-25, y, 50, 25)
        g.setColor(Color.BLACK)
        g.fillRect(x-10, y-50, 20, 50)
        g.setFont(new Font("Arial", 0, 20))
        g.drawString(s"Darts Left: $numDarts", ScreenDimensions.width-200, 40)
    }
}


object ArcadeGame extends SimpleSwingApplication {
    def top = new MainFrame {
        title = "Arcade Game"
        val global : MainEventLoop = new MainEventLoop()
        global.addEntity(new DartShooter(ScreenDimensions.width/2, 50))
        global.addEntity(new ArcadeGameManager(100))

        val canvas = global.getDefaultCanvas(500, 800)

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
        listenTo(button)
        listenTo(canvas.keys)
        size = new Dimension(500,900)
        reactions += {

            case ButtonClicked(c) if c == button =>{
                global.stop()
            }
            case KeyPressed(_ , c, _, _) => {
                if (c == Key.Space || c == Key.Up){
                    global.addEvent(ShootDart)
                } else if (c == Key.Left){
                    global.addEvent(Move(-5))
                } else if (c == Key.Right){
                    global.addEvent(Move(5))
                } else {
                    println(s"You pressed: $c")
                }
            }

        }

        global.start(canvas)
    }
}
