// pythonicBooleanAlgebra.scala
import scala.util.parsing.combinator._

// descriptive grammar
// S -> T | not S | S or S | S and S | (S)
// T -> True | False


// Generative grammar
// CondExpr -> Bool | Not(CondExpr)| Or(CondExpr,CondExpr) | And(CondExpr,CondExpr)
// Bool -> ConstTrue | ConstFalse

// Class
// sealed trait CondExpr
// sealed trait Bool extends CondExpr
// case object ConstTrue extends Bool
// case object ConstFalse extends Bool
// case class Not(c1:CondExpr) extends CondExpr
// case class Or(c1:CondExpr, c2:CondExpr) extends CondExpr
// case class And(c1:CondExpr, c2:CondExpr) extends CondExpr


// INTERPRETER
sealed trait CondExpr {
    def eval():Bool = this match {
        case b:Bool => b
        case Not(c1) => !c1.eval()
        case And(c1, c2) => c1.eval() && c2.eval()
        case Or(c1, c2) => c1.eval() || c2.eval()
    }
}
sealed trait Bool extends CondExpr {
    def toBoolean():Boolean = this match {
        case ConstTrue => true
        case ConstFalse => false
    }
    def unary_!():Bool = this match {
        case ConstTrue => ConstFalse
        case ConstFalse => ConstTrue
    }
    def &&(b2:Bool):Bool = (this, b2) match {
        case (ConstFalse,_) | (_,ConstFalse) => ConstFalse
        case (ConstTrue, ConstTrue) => ConstTrue
    }
    def ||(b2:Bool):Bool = (this, b2) match {
        case (ConstTrue,_) | (_,ConstTrue) => ConstTrue
        case (ConstFalse, ConstFalse) => ConstFalse
    }
}
case object ConstTrue extends Bool
case object ConstFalse extends Bool
case class Not(c1:CondExpr) extends CondExpr
case class Or(c1:CondExpr, c2:CondExpr) extends CondExpr
case class And(c1:CondExpr, c2:CondExpr) extends CondExpr


// PARSER
// expr -> binary
// binary -> unary and binary | unary or binary | unary
// unary -> atom | not atom
// atom -> bool | (expr)
// bool -> True | False
class CondExprParser extends RegexParsers {
    def expr:Parser[CondExpr] = binary
    def binary:Parser[CondExpr] = {
        val opt1 = (unary <~ "and") ~ binary ^^ {
            case e1 ~ e2 => And(e1, e2)
        }
        val opt2 = (unary <~ "or") ~ binary ^^ {
            case e1 ~ e2 => Or(e1,e2)
        }
        val opt3 = unary
        opt1 | opt2 | opt3  // this order counts... GRRRRR
    }
    def unary:Parser[CondExpr] = {
        val opt1 = atom
        val opt2 = ("not" ~> atom) ^^ { Not(_) }
        opt1 | opt2
    }
    def atom:Parser[CondExpr] = {
        val opt1 = bool
        val opt2 = ("(" ~> expr) <~ ")"
        opt1 | opt2
    }
    def bool:Parser[CondExpr] = {
        val opt1 = "True" ^^ { _ => ConstTrue }
        val opt2 = "False" ^^ { _ => ConstFalse }
        opt1 | opt2
    }
}



/*
 *
 * TESTS
 *
 */


def runTests() = {

    println("\n\n\nBEGINING TESTS\n\n\n")
    val b = testParse()
    if (b) { testInterpret }

}


def testParse():Boolean = { 

    println("TESTING PARSER")

    val l:List[(String, CondExpr)] = List(
        ("True", ConstTrue),
        ("False", ConstFalse),
        ("not True", Not(ConstTrue)),
        ("True and False", And(ConstTrue, ConstFalse)),
        ("not True or False", Or(Not(ConstTrue), ConstFalse)),
        ("not(True or False)", Not(Or(ConstTrue, ConstFalse)))
    )

    val p = new CondExprParser()

    val out = l.foldLeft(true){
        case (acc, (sIn,cExpected)) => {
            try {
                val cFound = (p.parse(p.expr, sIn) get)  // ...not safe
                val b = cFound == cExpected
                if (!b) {
                    println("\n\nXXXXXXXXXXXXXXXXX")
                    println(s"\tFailed on string '''$sIn''':")
                    println(s"\t\tFound    : $cFound")
                    println(s"\t\tExpected : $cExpected")
                    println("XXXXXXXXXXXXXXXXX\n\n")
                }
                else {
                    println(s"\n\tPassed '''$sIn'''")
                }
                acc && b
            } catch {
                case _:Throwable => {
                    println("\n\nXXXXXXXXXXXXXXXXX")
                    println(s"\tUnable to parse '''$sIn''':")
                    println("XXXXXXXXXXXXXXXXX\n\n")
                    false
                }
            } 
        }
    }
    println("\nEND TEST PARSER\n\n\n")
    out
}


def testOne(s1:String, b2:Boolean):Unit = {
    val p = new CondExprParser()
    p.parse(p.expr, s1) map {
        case c1 => {
            val b1 = (c1 eval).toBoolean()
            if (b1 != b2) {
                println("\n\nXXXXXXXXXXXXXXXXX")
                println(s"\tFailed on test ''$s1''':")
                println(s"\t\tParsed   : $c1")
                println(s"\t\tFound    : $b1")
                println(s"\t\tExpected : $b2")
                println("XXXXXXXXXXXXXXXXX\n\n")
            } else {
                println(s"\n\tSuccess on '''$s1'''")
            }
        }
    }
}

def testInterpret = {
    println("TESTING INTERPRETOR")
    testInterpretConstants
    testInterpretUnary
    testInterpretBinaries
    testInterpretCombos
    println("\nEND TEST INTERPRETOR")
}

def testInterpretConstants = {
    testOne("True", true)
    testOne("False", false)
}
def testInterpretUnary = {
    testOne("~True", false)
    testOne("~False", true)
}
def testInterpretBinaries = {
    testOne("True and True", true)
    testOne("True and False", false)
    testOne("False and True", false)
    testOne("False and False", false)
    testOne("True or True", true)
    testOne("True or False", true)
    testOne("False or True", true)
    testOne("False or false", false)
}

def testInterpretCombos = {
    testOne("not True or False", false)
    testOne("not False and not True", false)
    testOne("not(False and not True)", true)
}



runTests()

