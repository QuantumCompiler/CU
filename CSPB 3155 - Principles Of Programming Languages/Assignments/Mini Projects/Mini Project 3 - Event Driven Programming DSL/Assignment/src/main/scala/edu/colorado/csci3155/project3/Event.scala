package edu.colorado.csci3155.project3

trait Event {
    def appliesTo(e: Entity): Boolean = true
}

case class Tick(delta: Double) extends Event
case class MouseClick(x: Double, y: Double) extends Event
case object Stop extends Event

