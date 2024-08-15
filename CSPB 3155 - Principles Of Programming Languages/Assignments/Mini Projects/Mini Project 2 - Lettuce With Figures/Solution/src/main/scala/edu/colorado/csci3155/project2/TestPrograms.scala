package edu.colorado.csci3155.project2

object TestPrograms {
    val debug = true
    def program1(): String =
        """
          |let f = rectangle(1) in
          |   let g = circle(0.5) in
          |      f/g
        """.stripMargin

    def program2(): String =
    """
      |let f = function(x)
      |         (rectangle(x) + triangle(x))/(triangle(x) / circle(x))
      |         in
      |     let g = function (y) (f(y)*f(y)/f(y)) in
      |       g(3)
    """.stripMargin

    def program3(): String =
        """
          | let z0 = triangle(1) in
          | let z1 = (z0*z0)/z0 in
          | let z2 = (z1*z1)/z1 in
          | z2
        """.stripMargin

    def serp(): String =
        """
          |letrec serp = function (x)
          |       if (x <= 1)
          |       then (triangle(x)*triangle(x))/triangle(x)
          |       else (
          |           let f = serp(x-1) in
          |               (f * f) / f
          |            ) in
          |       serp(5)
        """.stripMargin

    def mandala(): String =
        """
          | letrec mandala = function (x)
          |    let ang = 3.1415/10 in
          |    if (x <= 1)
          |    then rectangle(2)+triangle(2)
          |    else (rectangle(2)+triangle(2))+(mandala(x-1)/ang)
          |  in
          |  mandala(20)
        """.stripMargin

    def petals(): String =
    """
      | letrec petals = function (x)
      |                      function (n)
      |                         let ang = 3.1415/n in
      |                         if (x <= 1)
      |                         then circle(2) + triangle(2)
      |                         else circle(2) + triangle(2)+ (petals(x-1)(n) / ang)
      |            in
      |       petals(40)(20)
    """.stripMargin

    def program4(): String = {
        """
          |let f1 = triangle(1) in
          |   (f1 * f1)/f1
        """.stripMargin
    }

    def program5(): String = {
        """
          |let f = function (x)
          |      rectangle(x) * ((triangle(x)/triangle(x)) * circle(x))
          |      in
          |    f(1) + f(2) / f(3)
        """.stripMargin
    }

def parseAndInterpretProgram(s: String): Value = {
    val p: Program = new LettuceParser().parseString(s)
    if (debug) {
        println("--- Debug --- ")
        println(p)
        println("--- Debug ---")
    }
    val v = Interpreter.evalProgram(p)
    if (debug)
        println(s"Returned value : $v")
    v
    }
}


