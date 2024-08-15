package edu.colorado.csci3155.project3

import org.scalatest.FunSuite

/*-- This is an example of an event driven system we will use to test --*/

/* Declare two events a and b */
case object EventA extends Event
case object EventB extends Event

/*-- Declare a state State1 --*/
case class State1(id: Int) extends Entity {
    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) = e match {
        case Stop => (List(), List()) // handle the stop event
        case EventA => (List(State2(id)), List()) // receiving an EventA transitions to state2 and generates no other events
        case EventB => ((List(State1(id))), List(EventA)) // receiving an EventB remain in State1 and generate a new EventA
        case Tick(_) => (List(State2(id)), List(EventA))    // receiving a tick, transition to state 2 and generate a new EventA
        case _ => (List(this), List())  // Handle any other event by ignoring it.
    }

}

case class State2(id: Int) extends Entity{
    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) =  e match {
        case Stop => (List(), List()) // handle the stop event
        case EventA => (List(State3(id)), List(EventB)) // receiving an EventA transitions to State3 and generates a new event EventB
        case _ => (List(this), List())  // Ignore all other events.
    }

}

case class State3(id: Int) extends Entity {
    override def handleEvent(global: MainEventLoop)(e: Event): (List[Entity], List[Event]) = e match {
        case Stop => (List(), List()) // handle the event Stop
        case EventB => (List(State1(id)), List(EventB)) // EventB moves to State1 and generates a new EventB
        case EventA => (List(State2(id)), List(EventA)) // EventA moves to state2 and generates a new EventA
        case _ => (List(this), List()) // Ignore all other events
    }

}

class Automaton1Tests extends FunSuite{
    test("Test 1 for MainEventLoop.processOneEvent"){
        // Create a main loop
        val glob: MainEventLoop = new MainEventLoop
        // Add an entity in state1 with id 1
        glob.addEntity(new State1(1))
        // add an entity in state2 with id 2
        glob.addEntity(new State2(2))
        //Call processOneEvent on the current entities with EventA as the event to be processed.
        val (newEntities, newEvents) = glob.processOneEvent(glob.entities)(EventA)
        // The result must contain two entities
        assert(newEntities.length == 2, "Must have 2 entities after processing one event")
        // The result must have generated one event.
        assert(newEvents.length == 1, "Must have generated one event after processing one event")
        // The event must be an EventB : lookup what State2 does when it receives an EventA
        assert(newEvents.head == EventB, "The generated event must be an eventB")
        //The new entities returned must contain a State2 with id 1 and State3 with id 2
        assert(newEntities.contains(State2(1)))
        assert(newEntities.contains(State3(2)))
    }

    test("Test 2 for MainEventLoop.processOneEvent"){
        // Same as Test 1 except we will now test handleAllEvents with two events
        val glob: MainEventLoop = new MainEventLoop
        // Add an entity in state1 with id 1
        glob.addEntity(new State1(1))
        // add an entity in state2 with id 2
        glob.addEntity(new State2(2))
        // Insert two events : an eventB followed by a Tick
        glob.events = List(EventB, Tick(0.2))
        val (newEntities, newEvents) = glob.performOneTransition
        assert(newEntities.length == 2, "Must have two entities after the transition is done")
        assert(newEntities.contains(State2(1)), "ID 1 must now be a State 2")
        assert(newEntities.contains(State2(2)), "ID 2 must now be a State 2")
        assert(newEvents.length == 2)
        assert(newEvents.contains(EventA), "Must have generated two copies of EventA")
        assert(!newEvents.contains(EventB), "Cannot have generated an EventB")
    }

    test("Stop Event must remove all entities"){
        // Same as Test 1 except we will now test handleAllEvents with two events
        val glob: MainEventLoop = new MainEventLoop
        // Add an entity in state1 with id 1
        glob.addEntity(new State1(1))
        // add an entity in state2 with id 2
        glob.addEntity(new State2(2))
        // Insert two events : an eventB followed by a Tick
        glob.events = List(EventB, Tick(0.2), EventA, Tick(0.2), Stop)
        glob.addEntity(new State1(1))
        // add an entity in state2 with id 2
        glob.addEntity(new State2(2))
        // add a new entity in State3 with id 3
        glob.addEntity(new State3(3))
        val (newEntities, newEvents) = glob.performOneTransition
        assert(newEntities.length == 0, "Stop event must remove all entities")
        assert(newEvents.length == 11,"11 events must be generated")
        assert(newEvents.count(e => e == EventB) == 6, "There must be 6 EventB events")
//        println(s"Number of events: ${newEvents}")
    }

    test("Test five ticks in a row"){
        // Same as Test 1 except we will now test handleAllEvents with two events
        val glob: MainEventLoop = new MainEventLoop
        // Insert two events : an eventB followed by a Tick
        glob.events = List(Tick(0.2),  Tick(0.2), Tick(0.2), Tick(0.2), Tick(0.2))
        glob.addEntity(new State1(1))
        // add an entity in state2 with id 2
        glob.addEntity(new State2(2))
        // add a new entity in State3 with id 3
        glob.addEntity(new State3(3))
        val (newEntities, newEvents) = glob.performOneTransition
        assert(newEntities.length == 3, "Three entities must be present")
        assert(newEntities.contains(State2(1)), "ID 1 must now be in State 2")
        assert(newEntities.contains(State2(2)), "ID 2 must now be in State 2")
        assert(newEntities.contains(State3(3)), "ID 3 must be in State 3")
        assert(newEvents.length == 1,"One event must be generated")
        assert(newEvents.head == EventA, "The single event generated must be an EventA")
    }
}
