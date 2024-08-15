error id: file://<HOME>/Documents/CSPB%203155/Mini%20Project%202%20-%20Lettuce%20With%20Figures/Solution/src/main/scala/edu/colorado/csci3155/project2/MyCanvas.scala:[7951..7955) in Input.VirtualFile("file://<HOME>/Documents/CSPB%203155/Mini%20Project%202%20-%20Lettuce%20With%20Figures/Solution/src/main/scala/edu/colorado/csci3155/project2/MyCanvas.scala", "package edu.colorado.csci3155.project2

/* A class to maintain a canvas. */
import java.awt.geom.{Ellipse2D, Rectangle2D}
import java.awt.{Graphics2D}

/* A figure is a sealed trait. It can be a Polygon or a "MyCircle"*/
sealed trait Figure {
    def getBoundingBox: (Double, Double, Double, Double)
    def translate(shiftX: Double, shiftY: Double): Figure

    def render(g: Graphics2D, scaleX: Double, scaleY: Double, shiftX: Double, shiftY: Double): Unit
}

/*
 Class Polygon
   A polygon is defined by a list of its vertices
 */

case class Polygon(val cList: List[(Double, Double)]) extends Figure {
    //TODO: Define the bounding box of the polygon
    /*  getBoundingBox: Calculates the bounding box of the polygon
            Input: 
                None
            Algorithm:
                * Get the x and y coordinates of all the vertices in the polygon
                * Return the min and max of x and y coordinates
                * The bounding box is defined by the min and max of x and y coordinates
            Output:
                Returns a tuple of 4 values (minX, maxX, minY, maxY) for the bounding box
    */
    override def getBoundingBox: (Double, Double, Double, Double ) = {
        val x = cList.map(_._1)
        val y = cList.map(_._2)
        (x.min, x.max, y.min, y.max)
    }
    //TODO: Create a new polygon by shifting each vertex in cList by (x,y)
    //    Do not change the order in which the vertices appear
    override def translate(shiftX: Double, shiftY: Double): Polygon = {
        val newV = cList.map {case (x,y) => (x + shiftX, y + shiftY)}
        Polygon(newV)
    }

    // Function: render -- draw the polygon. Do not edit this function.
    override def render(g: Graphics2D, scaleX: Double, scaleY: Double, shiftX: Double, shiftY: Double) = {
        val xPoints: Array[Int] = new Array[Int](cList.length)
        val yPoints: Array[Int] = new Array[Int](cList.length)
        for (i <- 0 until cList.length){
            xPoints(i) = ((cList(i)._1 + shiftX )* scaleX).toInt
            yPoints(i) = ((cList(i)._2 + shiftY) * scaleY).toInt
        }
        g.drawPolygon(xPoints, yPoints, cList.length)
    }
}

/*
  Class MyCircle
  Define a circle with a given center c and radius r
 */
case class MyCircle(val c: (Double, Double), val r: Double) extends Figure {
    //TODO: Define the bounding box for the circle
    /*  getBoundingBox: Calculates the bounding box of the circle
            Input: 
                None
            Algorithm:
                * Get the x and y coordinates of the center of the circle
                * Get the radius of the circle
                * Return the min and max of x-r, x+r, y-r, y+r
                * The bounding box is defined by the min and max of x and y coordinates
            Output:
                Returns a tuple of 4 values (minX, maxX, minY, maxY) for the bounding box
    */
    override def getBoundingBox: (Double, Double, Double, Double) = {
        val (x, y) = c
        (x - r, x + r, y - r, y + r)
    }


    //TODO: Create a new circle by shifting the center
    /*  translate: Translates the circle by shiftX and shiftY
            Input: 
                shiftX: Double -- shift in x direction
                shiftY: Double -- shift in y direction
            Algorithm:
                * Get the center of the circle and shift it by shiftX and shiftY
                * Return a new circle with the new center and the same radius
            Output:
                Returns a new MyCircle object with the center shifted by shiftX and shiftY
    */
    override def translate(shiftX: Double, shiftY: Double): MyCircle = {
        MyCircle((c._1 + shiftX, c._2 + shiftY), r)
    }

    // Function: render -- draw the polygon. Do not edit this function.
    override def render(g: Graphics2D, scaleX: Double, scaleY: Double, shiftX: Double, shiftY: Double) = {
        val centerX = ((c._1 + shiftX) * scaleX) .toInt
        val centerY = ((c._2 + shiftY) * scaleY) .toInt
        val radX = (r * scaleX).toInt
        val radY = (r * math.abs(scaleY)).toInt
        //g.draw(new Ellipse2D.Double(centerX, centerY, radX, radY))
        g.drawOval(centerX-radX, centerY-radY, 2*radX, 2*radY)
    }
}

/*
  Class : MyCanvas
  Define a canvas through a list of figure objects. Figure objects can be circles or polygons.
 */
class MyCanvas (val listOfObjects: List[Figure]) {
    // TODO: Write a function to get the boundingbox for the entire canvas.
    // Hint: use existing boundingbox functions defined in each figure.
    /*  getBoundingBox: Calculates the bounding box of the canvas
            Input: 
                None
            Algorithm:
                * Get the bounding box of each object in the canvas
                * Get the min and max of x and y coordinates of all the objects
                * Return the min and max of x and y coordinates
                * The bounding box is defined by the min and max of x and y coordinates
            Output:
                Returns a tuple of 4 values (minX, maxX, minY, maxY) for the bounding box
    */
    def getBoundingBox: (Double, Double, Double, Double) = {
        val boxes = listOfObjects.map(_.getBoundingBox)
        val xMin = boxes.map(_._1)
        val xMax = boxes.map(_._2)
        val yMin = boxes.map(_._3)
        val yMax = boxes.map(_._4)
        (xMin.min, xMax.max, yMin.min, yMax.max)
    }

    //TODO: Write a function to translate each figure in the canvas by shiftX, shiftY
    /*  translate: Translates the canvas by shiftX and shiftY
            Input: 
                shiftX: Double -- shift in x direction
                shiftY: Double -- shift in y direction
            Algorithm:
                * Translate each object in the canvas by shiftX and shiftY
                * Return a new MyCanvas object with the translated objects
            Output:
                Returns a new MyCanvas object with all the objects translated by shiftX and shiftY
    */
    def translate(shiftX: Double, shiftY: Double): MyCanvas = {
        val translated = listOfObjects.map(_.translate(shiftX, shiftY))
        new MyCanvas(translated)
    }

    //TODO: Write a function that will return a new MyCanvas object that places
    // all the objects in myc2 to the right of the objects in this MyCanvas.
    // refer to the notebook documentation on how to perform this.
    /*  placeRight: Places the objects in myc2 to the right of the objects in this MyCanvas
            Input: 
                myc2: MyCanvas -- The canvas to be placed to the right
            Algorithm:
                * Get the bounding box of this canvas and myc2
                * Get the x coordinates of the bounding box
                * Calculate the shift in x direction
                * Translate myc2 by the shift in x direction
                * Return a new MyCanvas object with all the objects in this canvas and myc2
            Output:
                Returns a new MyCanvas object with all the objects in this canvas and myc2 placed to the right
    */
    def placeRight(myc2: MyCanvas): MyCanvas = {
        val (xMax1, _, _, _) = this.getBoundingBox
        val (xMin2, _, _, _) = myc2.getBoundingBox
        val gap = 1.0 // Define a gap to ensure there's no overlap
        val xShift = xMax1 - xMin2 + gap // Add the gap to the shift
        val translatedC2 = myc2.translate(xShift, 0)
        new MyCanvas(this.listOfObjects ::: translatedC2.listOfObjects)
    }*  placeTop: Places the objects in myc2 on top of the objects in this MyCanvas
            Input: 
                myc2: MyCanvas -- The canvas to be placed on top
            Algorithm:
                * Get the bounding box of this canvas and myc2
                * Get the y coordinates of the bounding box
                * Calculate the shift in y direction
                * Translate myc2 by the shift in y direction
                * Return a new MyCanvas object with all the objects in this canvas and myc2
            Output:
                Returns a new MyCanvas object with all the objects in this canvas and myc2 placed on top
    */
    def placeTop(myc2: MyCanvas): MyCanvas = {
        val (_, _, yMax1, _) = this.getBoundingBox
        val (_, _, _, yMin2) = myc2.getBoundingBox
        val yShift = yMax1 - yMin2
        val translatedC2 = myc2.translate(0, yShift)
        new MyCanvas(this.listOfObjects ++ translatedC2.listOfObjects)
    }

    //TODO: Write a function that will rotate each figure in the canvas using
    // the angle `ang` defined in radians.
    // Suggestion: first write rotation functions for polygon and circle.
    //             those functions have not been added in the classes but you can do so with the
    //             appropriate signature.
    // rotating a polygon is simply rotating each vertex.
    // rotating a circle is simply rotating the center with radius unchanged.
    /*  rotate: Rotates the canvas by angRad
            Input: 
                angRad: Double -- angle in radians
            Algorithm:
                * Rotate each object in the canvas by angRad
                * Return a new MyCanvas object with the rotated objects
            Output:
                Returns a new MyCanvas object with all the objects rotated by angRad
    */
    def rotate(angRad: Double): MyCanvas = {
        def rotatePoint(x: Double, y: Double, theta: Double): (Double, Double) = {
            val newX = x * math.cos(theta) - y * math.sin(theta)
            val newY = x * math.sin(theta) + y * math.cos(theta)
            (newX, newY)
        }

        val rotatedObjects = listOfObjects.map {
            case Polygon(vertices) =>
                Polygon(vertices.map { case (x, y) => rotatePoint(x, y, angRad) })
            case MyCircle((x, y), r) =>
                MyCircle(rotatePoint(x, y, angRad), r)
        }
        new MyCanvas(rotatedObjects)
    }

    // Function to draw the canvas. Do not edit.
    def render(g: Graphics2D, xMax: Double, yMax: Double) = {
        val (lx1, ux1, ly1, uy1) = this.getBoundingBox
        val shiftx = -lx1
        val shifty = -uy1
        val scaleX = xMax/(ux1 - lx1  + 1.0)
        val scaleY = yMax/(uy1 - ly1 + 1.0)
        listOfObjects.foreach(f => f.render(g,scaleX, -scaleY, shiftx, shifty))
    }

    def overlap(c2: MyCanvas): MyCanvas = {
        new MyCanvas(listOfObjects ++ c2.listOfObjects)
    }

    // DO NOT EDIT THE CODE BELOW
    override def toString: String = {
        listOfObjects.foldLeft[String] ("") { case (acc, fig) => acc ++ fig.toString }
    }
    // DO NOT EDIT
    def getListOfObjects: List[Figure] = listOfObjects

    // DO NOT EDIT
    def numPolygons: Int =
        listOfObjects.count {
            case Polygon(_) => true
            case _ => false }

    //DO NOT EDIT
    def numCircles: Int = {
        listOfObjects.count {
            case MyCircle(_,_) => true
            case _ => false }
    }
    //DO NOT EDIT
    def numVerticesTotal: Int = {
        listOfObjects.foldLeft[Int](0) ((acc, f) =>
            f match {
                case Polygon(lst1) => acc + lst1.length
                case _ => acc
            }
        )
    }
}
")
file://<HOME>/Documents/CSPB%203155/Mini%20Project%202%20-%20Lettuce%20With%20Figures/Solution/src/main/scala/edu/colorado/csci3155/project2/MyCanvas.scala
file://<HOME>/Documents/CSPB%203155/Mini%20Project%202%20-%20Lettuce%20With%20Figures/Solution/src/main/scala/edu/colorado/csci3155/project2/MyCanvas.scala:178: error: expected identifier; obtained with
                * Return a new MyCanvas object with all the objects in this canvas and myc2
                                               ^
#### Short summary: 

expected identifier; obtained with