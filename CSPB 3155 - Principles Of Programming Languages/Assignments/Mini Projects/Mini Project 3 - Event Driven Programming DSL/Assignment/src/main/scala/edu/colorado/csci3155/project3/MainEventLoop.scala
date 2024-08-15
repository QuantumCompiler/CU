package edu.colorado.csci3155.project3
import java.awt.{Color, Dimension, Graphics2D}

import scala.annotation.tailrec
import scala.swing.Graphics2D
import scala.swing.Panel


class MyDefaultCanvas(global: MainEventLoop) extends Panel{

    override def paintComponent(g: Graphics2D) = {
        g.setPaint(Color.WHITE)
        g.fillRect(0,0,800,800)
        global.render(g)
    }


}

/*
    MainEventLoop class.
    This class will store a
        current list of entities
        current list of events

 */
class MainEventLoop {
    /*- This is the current list of entities -*/
    var entities: List[Entity] = List()

    /*- This is the current list of events -*/
    var events: List[Event] = List()

    def getDefaultCanvas(width: Int = 500, height: Int = 500): MyDefaultCanvas =
        new MyDefaultCanvas(this){
            preferredSize = new Dimension(width, height)
            focusable = true
        }

    /*- Utility function that returns the number of current entities -*/
    def numEntities = entities.length

    /*- Insert a new entity to the list of entities -*/
    def addEntity(e: Entity) = {
        entities= e::entities
    }
    /*- Insert a new event to the list of entities -*/
    def addEvent(ev: Event): Unit = {
        events = ev::events
    }

    /*- Render all the entities for the graphics -*/
    def render(g: Graphics2D) = {
        entities.foreach(u => u render g )
    }

    /*- Stop and destroy all entities -*/
    def stop(): Unit = {
        events = Stop :: events
    }
    /*- Add a tick event -*/
    def tick(delta: Double) = {
        events = Tick(delta)::events
    }

    /*- Add a click event -*/
    def click(x: Double, y: Double): Unit = {
        events = MouseClick(x, y)::events
    }

    /*-
        Partition a list of entities into two lists (l1, l2)
        l1 = list of all entities to which event ev applies to.
        l2 = list of all entities to which ev does not apply
        To determine if an event ev applies to an entity e, call ev.appliesTo(e)
     */

    def partition(l: List[Entity]) (ev: Event): (List[Entity], List[Entity]) = {
        l.partition(e => ev.appliesTo(e))
    }

    /*-
        Process one event given inputs
            l : Current list of entities
            ev: a single event
        Algorithm written using loops (you should use fold)
            returnListOfEntities = []
            returnListOfEvents = []
            For each entity e in list l
                if (event ev appliesTo entity e){
                     call e.handleEvent(ev) and let (ents, evs) be the new entities and events it returns.
                     add ents to the returnListOfEntities
                     add evs to the returnList of Events
                } else {
                    add e to the returnListofEntities
                }
             Note -- You should not be using a loop. Instead use the partition function above
                 and use foldLeft

        Returns:
           list of entities, list of events
     */
    /*--
    def processOneEventMutable(l: List[Entity])(ev: Event): (List[Entity], List[Event]) = {
        var newEntities: List[Entity] = List()
        var newEvents: List[Event] = List()
        val (lApplies, lDoesNotApply) = partition(l)(ev)
        for (ent <- lApplies) {
                val (l1: List[Entity], l2: List[Event]) = ent.handleEvent(this)(ev)
                newEntities = newEntities ++ l1
                newEvents = newEvents ++ l2
        }
        (lDoesNotApply ++ newEntities, newEvents)
    }
    */
    def processOneEvent (l: List[Entity]) (ev: Event): (List[Entity], List[Event]) = {
        /*-- TODO: implement processOneEventMutable without using for loops or var --*/
      ???

    }





    /*
        Transition function: given the current events (var events in this class)
        entities (var entities in this class)
        Apply process one event to each event in the current list of events to the entities.

     */
    /*---
    def performOneTransitionMutable: (List[Entity], List[Event]) = {
       var newEntities: List[Entity] = entities
       var newEvents: List[Event] = List()
       for (ev <- events) {
           val (trEntities, freshEvents) = processOneEventMutable(newEntities)(ev)
           newEntities = trEntities
           newEvents = freshEvents ++ newEvents
       }
       (newEntities, newEvents)
    }
   */
    final def performOneTransition: (List[Entity], List[Event]) = {
        /*-- TODO : implement performOneTransitionMutable without using for loops or var --*/
           ???
    }



    /*
        This is the main function runTrampoline.
        It runs a set of events. Uses a graphics panel to perform rendering.
        We have made it a tail
     */

    @tailrec
    final def runTrampoline( p: Panel, evLoopSleep: Int = 50, tickSpeed: Double = 0.4): Unit = {
        // If there are no entities left, let us exit the trampoline
        if (entities.size <= 0) {
            return
        }
        // Take the current list of entities and events and perform a transition
        val (newEntities, newEvents) = this.performOneTransition
        // Set the new set of entities and events
        entities = newEntities
        events = newEvents
        // Refresh the display
        p.repaint()
        // Sleep for sometime
        Thread.sleep(evLoopSleep)
        // Add a tick event to the set of events
        tick(tickSpeed)
        // Run the trampoline again -- this better get optimized away or else we are in deep trouble.
        runTrampoline(p, evLoopSleep, tickSpeed)
        // Look ma: no while loops used.
    }


    def start(canvas: Panel, evLoopSleep: Int = 50, tickSpeed: Double = 0.4)= {
        val runThread = new Thread {
            override def run() = {
               runTrampoline(canvas)
            }
        }
        runThread.start()
    }
}
