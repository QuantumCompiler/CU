package edu.colorado.csci3155.project3

import org.scalatest.FunSuite

class ArcadeGameTests extends FunSuite {
    test("Move event must apply to the DartShooter entity and nothing else") {
        val moveEvent = Move(-1)
        val dartShooterEntity = new DartShooter(10, 20)
        assert(moveEvent.appliesTo(dartShooterEntity), "Move event must apply to DartShooter")
        val arcadeGameManager = new ArcadeGameManager(500)
        assert(!moveEvent.appliesTo(arcadeGameManager), "Move event must not apply to ArcadeGameManager")
        val arcadeBaloon = new ArcadeBaloon(10, 20.0, 25.5, 13.2)
        assert(!moveEvent.appliesTo(arcadeBaloon), "Move event must not apply to the ArcadeBaloon")
        val dart = new Dart(2, 20.5, 35.2)
        assert(!moveEvent.appliesTo(dart), "Move event must not apply to the Dart entity")
    }

    test("ShootDart event must apply only to the DartShooter entity "){
        val shootDartEvent = ShootDart
        val dartShooterEntity = new DartShooter(10, 20)
        assert(shootDartEvent.appliesTo(dartShooterEntity), "ShootDart event must apply to DartShooter")
        val arcadeGameManager = new ArcadeGameManager(500)
        assert(!shootDartEvent.appliesTo(arcadeGameManager), "ShootDart event must not apply to ArcadeGameManager")
        val arcadeBaloon = new ArcadeBaloon(10, 20.0, 25.5, 13.2)
        assert(!shootDartEvent.appliesTo(arcadeBaloon), "ShootDart event must not apply to the ArcadeBaloon")
        val dart = new Dart(2, 20.5, 35.2)
        assert(!shootDartEvent.appliesTo(dart), "ShootDart event must not apply to the Dart entity")
    }

    test("BaloonBurst event must apply  the ArcadeGameManager and DartShooter"){
        val bbEvent = BaloonBurst
        val dartShooterEntity = new DartShooter(10, 20)
        assert(bbEvent.appliesTo(dartShooterEntity), "BaloonBurst event must  apply to DartShooter")
        val arcadeGameManager = new ArcadeGameManager(500)
        assert(bbEvent.appliesTo(arcadeGameManager), "BaloonBurst event must  apply to ArcadeGameManager")
        val arcadeBaloon = new ArcadeBaloon(10, 20.0, 25.5, 13.2)
        assert(!bbEvent.appliesTo(arcadeBaloon), "BaloonBurst event must not apply to the ArcadeBaloon")
        val dart = new Dart(2, 20.5, 35.2)
        assert(!bbEvent.appliesTo(dart), "BaloonBurst event must not apply to the Dart entity")
    }

    test("BaloonEscaped event must apply  to the ArcadeGameManager only"){
        val bbEvent = BaloonEscaped
        val dartShooterEntity = new DartShooter(10, 20)
        assert(!bbEvent.appliesTo(dartShooterEntity), "BaloonEscaped event must not apply to DartShooter")
        val arcadeGameManager = new ArcadeGameManager(500)
        assert(bbEvent.appliesTo(arcadeGameManager), "BaloonBurst event must  apply to ArcadeGameManager")
        val arcadeBaloon = new ArcadeBaloon(10, 20.0, 25.5, 13.2)
        assert(!bbEvent.appliesTo(arcadeBaloon), "BaloonEscaped event must not apply to the ArcadeBaloon")
        val dart = new Dart(2, 20.5, 35.2)
        assert(!bbEvent.appliesTo(dart), "BaloonEscaped event must not apply to the Dart entity")
    }

    test("Boom(x,y) event must apply to arcade baloons that are nearby") {
        val boomEvent = new Boom(10, 10)
        val arcadeBaloon1 = new ArcadeBaloon(10, 20.0, 25.5, 13.2)
        assert(boomEvent.appliesTo(arcadeBaloon1), s"Boom event at (10,10) must apply to a baloon at (20, 25.5) since distance is less than ${ScreenDimensions.baloonBurstDistance}")
        val arcadeBaloon2 = new ArcadeBaloon(10, 40, 40, 12.5)
        assert(!boomEvent.appliesTo(arcadeBaloon2), s"Boom event at (10,10) must not apply to a baloon at (40, 40) since distance is more than ${ScreenDimensions.baloonBurstDistance}")
    }

    test("Test for handling of Tick event for ArcadeGameManager entity") {
        val arcadeGameManager = new ArcadeGameManager(500)
        val tickEvent = Tick(0.2)
        val global = new MainEventLoop
        for (x <- 0 to 500 ) {
            val (newEntities, newEvents) = arcadeGameManager.handleEvent(global)(tickEvent)
            assert(newEvents.isEmpty, "No new events must be created")
            assert(newEntities.size <= 2, "No more than two entities must be returned.")
            assert(newEntities.contains(arcadeGameManager), "Arcade game manager must be returned back upon a tick event")
            if (newEntities.size > 1){
                assert(newEntities.exists {
                    case ArcadeBaloon(_,_,_,_) => true
                    case _ => false
                }, "If another entity is created, it must be of type ArcadeBaloon")
            }
        }
    }

    test("Test for handling BaloonEscaped/BaloonBurst Event for ArcadeGameManager entity "){
        val arcadeGameManager = ArcadeGameManager(500)
        val baloonEscaped = BaloonEscaped
        val global= new MainEventLoop
        val (newEntities, newEvents) = arcadeGameManager.handleEvent(global)(baloonEscaped)
        val updatedArcadeManager = ArcadeGameManager(500+ScreenDimensions.pointsBaloonEscaped)
        assert(newEntities.contains(updatedArcadeManager), "The points for baloon escaping must be deducted properly")
        assert(newEntities.length == 1, "Arcade manager must be updated and returned back for baloon escaped event")
        assert(newEvents.isEmpty, "No new events must be created for BaloonEscaped")
        val baloonBurst = BaloonBurst
        val (newEntities1, newEvents1) = arcadeGameManager.handleEvent(global)(baloonBurst)
        val newArcadeManager = ArcadeGameManager(500+ScreenDimensions.pointsBaloonBurst)
        assert(newEntities1.contains(newArcadeManager), "The points for baloon burst must be properly added")
        assert(newEntities1.length == 1, "Arcade manager must be updated and returned back for baloon burst event")
        assert(newEvents1.isEmpty, " No new events must be created for BaloonBurst")
    }

    test("Test for handling Tick event for ArcadeBaloon"){
        val arcadeBaloon = new ArcadeBaloon(1, 10.0, 10.0, 4.0)
        val tick = Tick(0.25)
        val global= new MainEventLoop
        val (newEntities, newEvents) = arcadeBaloon.handleEvent(global)(tick)
        assert( newEntities.exists {
            case ArcadeBaloon(1, 11.0, _, 4.0) => true
            case _ => false
        }, "The arcade baloon's x position must be properly updated and returned.")
        assert(newEvents.isEmpty, " No new events generated")
        val arcadeBaloon1 = new ArcadeBaloon(2, ScreenDimensions.shooterMax-1.0, 10.0, 8.0)
        val (newEntities1, newEvents1) = arcadeBaloon1.handleEvent(global)(tick)
        assert(newEntities1.isEmpty, s"Arcade baloons whose x positions exceed ${ScreenDimensions.shooterMax} must go out of existence")
        assert(newEvents1.contains(BaloonEscaped), " A baloon escaped event must be generated")

        val arcadeBaloon2 = new ArcadeBaloon(2, 1.0, 10.0, -8.0)
        val (newEntities2, newEvents2) = arcadeBaloon2.handleEvent(global)(tick)
        assert(newEntities2.isEmpty, "Arcade baloons whose x positions go below 0 must go out of existence")
        assert(newEvents2.contains(BaloonEscaped), "A baloon escaped event must be generated when the baloon goes out of existence")
    }

    test("Testing Boom event for arcade baloon"){
        val arcadeBaloon = new ArcadeBaloon(1, 10.0, 10.0, 4.0)
        val boom = new Boom(5.0, 12.0)
        val global= new MainEventLoop
        val (newEnt, newEv) = arcadeBaloon.handleEvent(global)(boom)
        assert(newEnt.isEmpty, "Baloon must go out of existence when it gets too close to a dart")
        assert(newEv.contains(BaloonBurst), "A BaloonBurst event must be generated")
    }

    test("Testing Tick event for a Dart "){
        val dart = new Dart(10, 50.0, 90.0)
        val tick = Tick(0.1)
        val y1: Double = 90.0 - 0.1 * ScreenDimensions.dartSpeed
        val updatedDart = new Dart(10, 50.0, y1)
        val global= new MainEventLoop
        val (newEnt, newEv) = dart.handleEvent(global)(tick)
        assert(newEnt.contains(updatedDart), "The y position of the dart must be updated correctly")
        assert(newEv.contains(Boom(50.0, y1)), "A Boom event must be generated at the updated position")

        val dart1 = new Dart(11, 50.0, 22.0)
        val y2 = 23.5 - 0.1 * ScreenDimensions.dartSpeed
        assume(y2 <= 20, "Incorrect assumption -- test needs to be updated by the author")
        val (newEnt1, newEv1) = dart1.handleEvent(global)(tick)
        assert(newEnt1.isEmpty, "Dart whose y position goes below 20.0 should be taken out of existence")
        assert(newEv1.isEmpty, "No new event must be generated when dart goes out of existence")
    }




}
