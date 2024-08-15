package edu.colorado.csci3155.project2

sealed trait Environment {
    def lookup(s: String): Value
}
case object EmptyEnvironment extends Environment {
    override def lookup(s: String): Value = {throw new IllegalArgumentException(s"Undefined identifier $s")}
}
case class Extend(x: String, v: Value, env: Environment) extends Environment {
    override def lookup(s: String): Value = {
        if (s == x)
            v
        else
            env.lookup(s)
    }
}
case class ExtendREC(f: String, x: String, e: Expr, env: Environment) extends Environment {
    override def lookup(s: String): Value = {
        if (s == f)
            Closure(x, e, this)
        else
            env.lookup(s)
    }
}

