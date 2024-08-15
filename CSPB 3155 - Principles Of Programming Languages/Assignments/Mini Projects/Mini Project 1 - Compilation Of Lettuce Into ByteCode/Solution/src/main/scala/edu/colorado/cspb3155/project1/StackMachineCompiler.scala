package edu.colorado.csci3155.project1

object StackMachineCompiler {
    /* Function compileToStackMachineCode
        Given expression e as input, return a corresponding list of stack machine instructions.
        The type of stack machine instructions are in the file StackMachineEmulator.scala in this same directory
        The type of Expr is in the file Expr.scala in this directory.
     */
    def compileToStackMachineCode(e: Expr): List[StackMachineInstruction] = e match {
        //TODO: Your code here
        /*  Const - Pushes the constant value onto the stack
            Input:
                s: String - The constant value to push onto the stack
            Algorithm:
                * Push the constant value onto the stack with PushI
            Output:
                List of StackMachineInstructions
        */
        case Const(s) => {
            List(PushI(s));
        }
        /*  Ident - Stores the value of the identifier onto the stack
            Input:
                s: String - The identifier to store onto the stack
            Algorithm:
                * Store the identifier onto the stack with StoreI
            Output:
                List of StackMachineInstructions
        */
        case Ident(s) => {
            List(StoreI(s));
        }
        /*  Plus - Adds two expressions together
            Input:
                e1: Expr - The first expression to add
                e2: Expr - The second expression to add
            Algorithm:
                * Compile the first expression to stack machine code
                * Compile the second expression to stack machine code
                * Add the two expressions together with AddI
            Output:
                List of StackMachineInstructions
        */
        case Plus(e1, e2) => {
            compileToStackMachineCode(e1) ++ compileToStackMachineCode(e2) ++ List(AddI);
        }
        /*  Minus - Subtracts two expressions
            Input:
                e1: Expr - The first expression to subtract
                e2: Expr - The second expression to subtract
            Algorithm:
                * Compile the first expression to stack machine code
                * Compile the second expression to stack machine code
                * Subtract the two expressions with SubI
            Output:
                List of StackMachineInstructions
        */
        case Minus(e1, e2) => {
            compileToStackMachineCode(e1) ++ compileToStackMachineCode(e2) ++ List(SubI);
        }
        /*  Mult - Multiplies two expressions
            Input:
                e1: Expr - The first expression to multiply
                e2: Expr - The second expression to multiply
            Algorithm:
                * Compile the first expression to stack machine code
                * Compile the second expression to stack machine code
                * Multiply the two expressions with MultI
            Output:
                List of StackMachineInstructions
        */
        case Mult(e1, e2) => {
            compileToStackMachineCode(e1) ++ compileToStackMachineCode(e2) ++ List(MultI);
        }
        /*  Div - Divides two expressions
            Input:
                e1: Expr - The first expression to divide
                e2: Expr - The second expression to divide
            Algorithm:
                * Compile the first expression to stack machine code
                * Compile the second expression to stack machine code
                * Divide the two expressions with DivI
            Output:
                List of StackMachineInstructions
        */
        case Div(e1, e2) => {
            compileToStackMachineCode(e1) ++ compileToStackMachineCode(e2) ++ List(DivI);
        }
        /*  Exp - Takes the exponential of an expression
            Input:
                e: Expr - The expression to take the exponential of
            Algorithm:
                * Compile the expression to stack machine code
                * Take the exponential of the expression with ExpI
            Output:
                List of StackMachineInstructions
        */
        case Exp(e) => {
            compileToStackMachineCode(e) ++ List(ExpI);
        }
        /*  Log - Takes the natural logarithm of an expression
            Input:
                e: Expr - The expression to take the natural logarithm of
            Algorithm:
                * Compile the expression to stack machine code
                * Take the natural logarithm of the expression with LogI
            Output:
                List of StackMachineInstructions
        */
        case Log(e) => {
            compileToStackMachineCode(e) ++ List(LogI);
        }
        /*  Sine - Takes the sine of an expression
            Input:
                e: Expr - The expression to take the sine of
            Algorithm:
                * Compile the expression to stack machine code
                * Take the sine of the expression with SinI
            Output:
                List of StackMachineInstructions
        */
        case Sine(e) => {
            compileToStackMachineCode(e) ++ List(SinI);
        }
        /*  Cosine - Takes the cosine of an expression
            Input:
                e: Expr - The expression to take the cosine of
            Algorithm:
                * Compile the expression to stack machine code
                * Take the cosine of the expression with CosI
            Output:
                List of StackMachineInstructions
        */
        case Cosine(e) => {
            compileToStackMachineCode(e) ++ List(CosI);
        }
        /*  Let - Assigns a value to an identifier
            Input:
                s: String - The identifier to assign a value to
                e1: Expr - The value to assign to the identifier
                e2: Expr - The expression to evaluate after assigning the value to the identifier
            Algorithm:
                * Compile the value to assign to the identifier to stack machine code
                * Store the value of the identifier onto the stack with StoreI
                * Compile the expression to evaluate after assigning the value to the identifier to stack machine code
            Output:
                List of StackMachineInstructions
        */
        case Let(s, e1, e2) => {
            compileToStackMachineCode(e1) ++ List(LoadI(s)) ++ compileToStackMachineCode(e2);
        }
    }
}
