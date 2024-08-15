package edu.colorado.csci3155.project1


/* -- Here are all the instructions to be supported --*/
sealed trait StackMachineInstruction
case class LoadI(s: String) extends StackMachineInstruction
case class  StoreI(s: String) extends StackMachineInstruction
case class PushI(f: Double) extends StackMachineInstruction
case object AddI extends StackMachineInstruction
case object SubI extends StackMachineInstruction
case object MultI extends StackMachineInstruction
case object DivI extends StackMachineInstruction
case object ExpI extends StackMachineInstruction
case object LogI extends StackMachineInstruction
case object SinI extends StackMachineInstruction
case object CosI extends StackMachineInstruction
case object PopI extends StackMachineInstruction


object StackMachineEmulator {
      /* Function emulateSingleInstruction
            Given a list of doubles to represent a stack
                  a map from string to double precision numbers for the environment
            and   a single instruction of type StackMachineInstruction
            Return a tuple that contains the
                  modified stack that results when the instruction is executed.
                  modified environment that results when the instruction is executed.

            Make sure you handle the error cases: eg., stack size must be appropriate for the instruction
            being executed. Division by zero, log of a non negative number
            Throw an exception or assertion violation when error happens.
      */
      def emulateSingleInstruction(stack: List[Double],
                                    env: Map[String, Double],
                                    ins: StackMachineInstruction): (List[Double], Map[String, Double]) = ins match {
            // TODO: Your code here.
            /*    LoadI - Load the value of the identifier from the environment onto the stack
                  Input:
                        s: String - The identifier to load from the environment
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack is not empty, load the value of the identifier from the environment onto the stack
                  Output:
                        Tuple containing the modified stack and environment
            */
            case LoadI(s) => {
                  // Check if the stack is empty
                  if (stack.isEmpty) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack is not empty, load the value of the identifier from the environment onto the stack
                  else {
                        val v = stack.head;
                        (stack.tail, env + (s -> v));
                  }
            }
            /*    StoreI - Store the value of the identifier onto the environment
                  Input:
                        s: String - The identifier to store onto the environment
                  Algorithm:
                        * Check if the identifier is in the environment
                        * If the identifier is in the environment, store the value of the identifier onto the environment
                  Output:
                        Tuple containing the modified stack and environment
            */
            case StoreI(s) => {
                  // Check if the identifier is in the environment
                  env.get(s) match {
                        // If the identifier is in the environment, store the value of the identifier onto the environment
                        case Some(v) => {
                              (v :: stack, env);
                        }
                        // If the identifier is not in the environment, throw an exception
                        case None => {
                              throw new RuntimeException(s"Identifier $s not found in environment");
                        }
                  }
            }
            /*    PushI - Push the constant value onto the stack
                  Input:
                        d: Double - The constant value to push onto the stack
                  Algorithm:
                        * Push the constant value onto the stack
                  Output:
                        Tuple containing the modified stack and environment
            */
            case PushI(d) => {
                  // Push the constant value onto the stack
                  (d :: stack, env);
            }
            /*    AddI - Add two expressions together
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack has at least two elements, add the two expressions together
                  Output:
                        Tuple containing the modified stack and environment
            */
            case AddI => {
                  // Check if the stack has at least two elements
                  if (stack.size < 2) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack has at least two elements, add the two expressions together
                  else {
                        val v1 = stack.head;
                        val v2 = stack.tail.head;
                        ((v1 + v2) :: stack.tail.tail, env);
                  }
            }
            /*    SubI - Subtract two expressions
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack has at least two elements, add the two expressions together
                  Output:
                        Tuple containing the modified stack and environment
            */
            case SubI => {
                  // Check if the stack has at least two elements
                  if (stack.size < 2) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack has at least two elements, subtract the two expressions
                  else {
                        val v1 = stack.head;
                        val v2 = stack.tail.head;
                        ((v2 - v1) :: stack.tail.tail, env);
                  }
            }
            /*    MultI - Multiply two expressions
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack has at least two elements, add the two expressions together
                  Output:
                        Tuple containing the modified stack and environment
            */
            case MultI => {
                  // Check if the stack has at least two elements
                  if (stack.size < 2) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack has at least two elements, multiply the two expressions
                  else {
                        val v1 = stack.head;
                        val v2 = stack.tail.head;
                        ((v1 * v2) :: stack.tail.tail, env);
                  }
            }
            /*    DivI - Divide two expressions
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack has at least two elements, add the two expressions together
                  Output:
                        Tuple containing the modified stack and environment
            */
            case DivI => {
                  // Check if the stack has at least two elements
                  if (stack.size < 2) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack has at least two elements, divide the two expressions
                  else {
                        val v1 = stack.head;
                        val v2 = stack.tail.head;
                        // Check if the divisor is zero
                        if (v1 == 0) {
                              throw new RuntimeException("Division by zero");
                        }
                        // If the divisor is not zero, divide the two expressions
                        else {
                              ((v2 / v2) :: stack.tail.tail, env);
                        }
                  }
            }
            /*    ExpI - Exponential of an expression
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack is not empty, calculate the exponential of the expression
                  Output:
                        Tuple containing the modified stack and environment
            */
            case ExpI => {
                  // Check if the stack is empty
                  if (stack.isEmpty) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack is not empty, calculate the exponential of the expression
                  else {
                        val v = stack.head;
                        (Math.exp(v) :: stack.tail, env);
                  }
            }
            /*    LogI - Logarithm of an expression
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack is not empty, calculate the logarithm of the expression
                  Output:
                        Tuple containing the modified stack and environment
            */
            case LogI => {
                  // Check if the stack is empty
                  if (stack.isEmpty) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack is not empty, calculate the logarithm of the expression
                  else {
                        val v = stack.head;
                        // Check if the number is non-positive
                        if (v <= 0) {
                              throw new RuntimeException("Log of non-positive number");
                        }
                        // If the number is positive, calculate the logarithm of the expression
                        else {
                              (Math.log(v) :: stack.tail, env);
                        }
                  }
            }
            /*    SinI - Sine of an expression
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack is not empty, calculate the sine of the expression
                  Output:
                        Tuple containing the modified stack and environment
            */
            case SinI => {
                  // Check if the stack is empty
                  if (stack.isEmpty) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack is not empty, calculate the sine of the expression
                  else {
                        val v = stack.head;
                        (Math.sin(v) :: stack.tail, env);
                  }
            }
            /*    CosI - Cosine of an expression
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack is not empty, calculate the cosine of the expression
                  Output:
                        Tuple containing the modified stack and environment
            */
            case CosI => {
                  // Check if the stack is empty
                  if (stack.isEmpty) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack is not empty, calculate the cosine of the expression
                  else {
                        val v = stack.head;
                        (Math.cos(v) :: stack.tail, env);
                  }
            }
            /*    PopI - Pop the top element from the stack
                  Algorithm:
                        * Check if the stack is empty
                        * If the stack is not empty, pop the top element from the stack
                  Output:
                        Tuple containing the modified stack and environment
            */
            case PopI => {
                  // Check if the stack is empty
                  if (stack.isEmpty) {
                        throw new RuntimeException("Stack underflow");
                  }
                  // If the stack is not empty, pop the top element from the stack
                  else {
                        (stack.tail, env);
                  }
            }
      }

      /* Function emulateStackMachine
            Execute the list of instructions provided as inputs using the
            emulateSingleInstruction function.
            Use foldLeft over list of instruction rather than a for loop if you can.
            Return value must be the final environment.

            Hint: accumulator for foldLeft must be a tuple (List[Double], Map[String,Double])
                  initial value of this accumulator must be (Nil, Map.empty)
                  You should use emulateSingleInstruction to update the accumulator.
                  It will all fit nicely once you figure it out.
      */
      def emulateStackMachine(instructionList: List[StackMachineInstruction]): Map[String, Double] = {
            // TODO: Your code here.
            // Create an initial stack and environment
            val initialStack: List[Double] = Nil
            // Create an initial environment
            val initialEnv: Map[String, Double] = Map.empty
            // Execute the list of instructions provided as inputs using the emulateSingleInstruction function
            val newEnv = instructionList.foldLeft((initialStack, initialEnv)) {
                  // Fold over list of instruction rather than a for loop
                  case ((stack, env), instruction) => {
                        emulateSingleInstruction(stack, env, instruction);
                  }
            }
            // Return the final environment, '._2' means the second element of the tuple
            newEnv._2;
      }
}

