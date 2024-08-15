package edu.colorado.csci3155.project2
import org.scalatest.FunSuite

class CanvasTests extends FunSuite {

    def distance(c1:(Double,Double), c2: (Double,Double)) =
        math.sqrt( math.pow((c1._1 - c2._1), 2) + math.pow(c1._2-c2._2, 2))

    def distanceToList(c1: (Double, Double), lst: List[(Double, Double)]): Double = {
        val dList = lst.map { case c => distance(c,c1) }
        dList.foldLeft[Double](Double.PositiveInfinity) (math.min(_,_))
    }



    def comparePolygons(poly1: Polygon, poly2: Polygon): Double = (poly1, poly2) match {
        case (Polygon(lst1), Polygon(lst2)) => {
            val lst3 = lst1.map(distanceToList(_, lst2))
            lst3.foldLeft(Double.NegativeInfinity)(math.max(_,_))
        }
    }

    def compareCircles(cir1: MyCircle, cir2: MyCircle) = (cir1, cir2) match {
        case (MyCircle( (x1: Double, y1: Double), r1: Double), MyCircle((x2, y2), r2)) => {
            math.max(distance((x1, y1), (x2, y2)), math.abs(r1-r2))
        }
    }

    test("Test Bounding Box with Polygon ") {
        val pointsList: List[(Double,Double)] = List((1.0, 2.0), (2.0, -3.0), (3.0, 4.0), (1.0, 5.0), (-1.0, -3.5))
        val poly = new Polygon(pointsList)
        println(poly.getBoundingBox)
        assert(poly.getBoundingBox == (-1.0, 3.0,-3.5,5.0))
        val myc = new MyCanvas(List(poly))
        println(myc.getBoundingBox)
        assert(myc.getBoundingBox == (-1.0, 3.0, -3.5, 5.0))
    }

    test("Test Bounding Box with Circle ") {

        val cir = new MyCircle((-2.0, 3.0), 1.0)
        println(cir.getBoundingBox)
        assert(cir.getBoundingBox == (-3.0, -1.0,2.0,4.0))
        val myc = new MyCanvas(List(cir))
        println(myc.getBoundingBox)
        assert(myc.getBoundingBox == (-3.0, -1.0,2.0,  4.0))
    }

    test("Test Bounding Box with two circles and one polygon"){
        val cir1  = new MyCircle((-1.0, 1.0), 0.5)
        val cir2 = new MyCircle((1.0, 2.0), 0.5)
        val poly1 = new Polygon(List((0,0.5), (-0.5,1), (-0.25, 2.1)))
        assert(cir1.getBoundingBox == (-1.5, -0.5, 0.5, 1.5))
        assert(cir2.getBoundingBox == (0.5, 1.5, 1.5, 2.5))
        assert(poly1.getBoundingBox == (-0.5, 0, 0.5, 2.1))
        val myc = new MyCanvas(List(cir1, cir2, poly1))
        assert(myc.getBoundingBox == (-1.5, 1.5, 0.5, 2.5))
    }


    test("Test Overlap of two figures"){
        val cir1  = new MyCircle((-1.0, 1.0), 0.5)
        val cir2 = new MyCircle((1.0, 2.0), 0.5)
        val poly1 = new Polygon(List((0,0.5), (-0.5,1), (-0.25, 2.1)))
        val cir3 = new MyCircle((-1.0, 1.0), 2.0 )
        val poly4 = new Polygon(List((1.5, 2.5), (1.1, 2.1), (1,2), (2,3)))
        val myc1 = new MyCanvas(List(cir1, cir2, poly1))
        val myc2 = new MyCanvas(List(cir3, poly4))
        val myc = myc1.overlap(myc2)
        val lst = myc.getListOfObjects
        assert(lst.contains(cir1))
        assert(lst.contains(cir2))
        assert(lst.contains(cir3))
        assert(lst.contains(poly1))
        assert(lst.contains(poly4))
    }

    test("Test Place Right"){
        val cir1  = new MyCircle((-1.0, 1.0), 0.5)
        val poly1 = new Polygon(List((1,1), (2,1), (1.5, 0)))
        val myc1 = new MyCanvas(List(cir1))
        val myc2 = new MyCanvas(List(poly1))
        val myc = myc1.placeRight(myc2)
        val shiftedPolygon = new Polygon(List((2,1), (3,1), (2.5,0)))
        val lst = myc.getListOfObjects
        assert(lst.contains(cir1))
        assert(lst.contains(shiftedPolygon))
    }

    test("Test Place Top"){
        val cir1  = new MyCircle((-1.0, 1.0), 0.5)
        val poly1 = new Polygon(List((1,1), (2,1), (1.5, 0)))
        val myc1 = new MyCanvas(List(cir1))
        val myc2 = new MyCanvas(List(poly1))
        val myc = myc1.placeTop(myc2)
        val shiftedPolygon = new Polygon(List((1,2), (2,2), (1.5,1.0)))
        val lst = myc.getListOfObjects
        assert(lst.contains(cir1))
        assert(lst.contains(shiftedPolygon))
    }

    test("Test Rotate"){
        val cir1  = new MyCircle((-1.0, 1.0), 0.5)
        val poly1 = new Polygon(List((1,1), (2,1), (1.5, 0)))
        val myc = new MyCanvas(List(cir1, poly1))
        val myc2 = myc.rotate(3.1415/6)
        println(myc2)
        val lst = myc2.getListOfObjects
        def reqdCircle = new MyCircle((-1.3660198,0.366046),0.5)
        assert(lst.exists {
                case c@MyCircle(_,_) => {
                    compareCircles(c, reqdCircle) <= 1E-03
                }
                case _ => false
        })
        val reqdPoly = new Polygon(List((0.36604,1.3660), (1.2320,1.8660), (1.2990,0.7499)))
        assert(lst.exists {
            case p@Polygon(_) => comparePolygons(p, reqdPoly) <= 1E-03
            case _ => false })
    }

    test("Test Translate") {
        val cir1 = new MyCircle((-1.0, 1.0), 0.5)
        val poly1 = new Polygon(List((1, 1), (2, 1), (1.5, 0)))
        val myc = new MyCanvas(List(cir1, poly1))
        val myc2 = myc.translate(1.25,2.25)
        val reqdCircle = new MyCircle((0.25, 3.25), 0.5)
        val reqdPoly = new Polygon(List((2.25, 3.25), (3.25, 3.25), (2.75, 2.25)))
        val lst = myc2.getListOfObjects
        assert(lst.exists {
            case c@MyCircle(_,_) => {
                compareCircles(c, reqdCircle) <= 1E-03
            }
            case _ => false
        })
        assert(lst.exists {
            case p@Polygon(_) => comparePolygons(p, reqdPoly) <= 1E-03
            case _ => false })


    }
}
