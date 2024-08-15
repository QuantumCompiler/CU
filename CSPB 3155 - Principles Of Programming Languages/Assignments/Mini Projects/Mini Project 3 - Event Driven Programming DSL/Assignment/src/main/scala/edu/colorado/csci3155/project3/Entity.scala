package edu.colorado.csci3155.project3

import java.awt.Graphics2D

trait Entity {
    val id: Int
    def handleEvent(global: MainEventLoop) (e: Event): (List[Entity], List[Event])
    def render(g: Graphics2D): Unit = ()
}

