package edu.colorado.csci3155.project1

sealed trait Expr
case class Const(f: Double) extends  Expr
case class Ident(id: String) extends Expr
case class Plus(e1: Expr, e2: Expr) extends  Expr
case class Minus(e1: Expr, e2: Expr) extends  Expr
case class Mult(e1: Expr, e2: Expr) extends  Expr
case class Div(e1: Expr, e2: Expr) extends  Expr
case class Exp(e:Expr) extends Expr
case class Log(e: Expr) extends Expr
case class Sine(e: Expr) extends Expr
case class Cosine(e:Expr) extends Expr
case class Let(ident: String, e1: Expr, e2: Expr) extends Expr

