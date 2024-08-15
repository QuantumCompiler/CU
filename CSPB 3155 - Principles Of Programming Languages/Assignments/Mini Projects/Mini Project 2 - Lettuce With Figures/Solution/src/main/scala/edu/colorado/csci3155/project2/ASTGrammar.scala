package edu.colorado.csci3155.project2

sealed trait Program

sealed trait Expr

case class TopLevel(e: Expr) extends Program

case class Const(f: Double) extends Expr
case class ConstBool(b: Boolean) extends Expr

case class Ident(s: String) extends Expr

case class Line(length: Expr) extends Expr
case class Rectangle(sideLength: Expr) extends Expr
case class Circle(radius: Expr) extends Expr
case class EquiTriangle(sideLength: Expr) extends Expr

case class Plus (e1: Expr, e2: Expr) extends Expr
case class Minus(e1: Expr, e2: Expr) extends Expr
case class Mult(e1: Expr, e2: Expr) extends Expr
case class Div (e1: Expr, e2: Expr) extends Expr

case class Geq(e1: Expr, e2: Expr) extends Expr
case class Gt(e1: Expr, e2: Expr) extends Expr
case class Eq (e1: Expr, e2: Expr) extends Expr
case class Neq(e1: Expr, e2: Expr) extends Expr
case class And(e1: Expr, e2: Expr) extends Expr
case class Or(e1: Expr, e2: Expr) extends Expr
case class Not(e1: Expr) extends Expr


case class IfThenElse(e: Expr, e1: Expr, e2: Expr) extends Expr
case class Let(x: String, e1: Expr, e2: Expr) extends Expr
case class FunDef(x: String, e: Expr) extends Expr
case class FunCall(f: Expr, x: Expr) extends Expr
case class LetRec(f: String, x: String, e1: Expr, e2: Expr) extends Expr

