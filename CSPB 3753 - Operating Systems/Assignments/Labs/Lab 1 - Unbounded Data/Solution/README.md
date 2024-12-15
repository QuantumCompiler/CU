# CSPB-3753 Lab: Unbounded Data Structures
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>
<br>
Often your implementation will need to handle an unspecified amount of data.  You can always try to create a buffer that is large enough to handle any data, but it is a waste of space in most instances and will not handle all quantities of data.

A better solution is to use the heap to dynamically allocate space as needed.  In this lab you will dynamically create two data structures to handle space efficiency and an unknown amount of data.
	
<hr>

You will implement two functions for this lab:  `get_unbounded_line()` and `get_value_table()`.   These functions will allocate the data structure needed from the heap using `malloc`, `realloc`, and `free` function calls to manage the allocated space.   Make sure that at the end of your program you have released any memory that has been allocated (no memory leaks should be detected).
	

    
<img src="images/construction-set-icon.jpg" alt="Under Construction" WIDTH=120 ALIGN="left" />

### This lab is still under construction.  
 
 Please report all speeling and grammered issues.<br>
 Also let us know about any unclear descriptions of work to be performed. 
 <br><br><br>
<hr>

**Objectives**
	
* use C to create simple application(s) 
* use C to read unbounded amount of characters from user
* use `malloc` and `realloc` to manage data structure sizes
* use memory checking to validate that all allocated memory is explicitly released
* use debugger (GDB or VSCode) to aid program development
* use return value checking on all system and library calls
	
<hr>
	
#### Knowledge and Skill Requirements
Presumably you have completed a computer systems course such as CSPB-2400 that covered the internal subsystems in a Computer.  During that course, you would have been introduced to debugging, machine language, code optimization, processes, and memory management.  You should have also learned about the different sections of memory allocated to a program or process.  The code, data, stack, and heap are different areas of memory that are used within a program.
	
In this lab you will use memory allocated from the HEAP for collecting an unknown quantity of data from the user.  The HEAP is used to dynamically allocate variables that are managed by the program itself.  You will only allocate a small amount of memory to begin with, and extend that memory in small amounts to use only as much memory as needed.
	
#### Follow the Steps
The steps of each lab will be listed in the order that I think provides the best way to implement the solution.  
The development cycle should be to add a small amount of code, compile the code, test that additional code, and proceed to the next subtask once the previous code is working as required.   
It is a common mistake for beginning developers to try to write all the code before testing.  
This strategy leads to a much longer development cycle. 
Each step will build on the code you already know is working so that you limit the number of places where the new code could be wrong.  This will focus your debugging to those small number of places that have changed.  
	
Each step requires the completion of the previous step.  Performing a stepwise inplementation will get you to the final results much quicker.  It also lets you *commit* and *push* your code changes as you complete each subtask.  That way you always have a working version in your remote repository.
	
<hr>
	
### Part 1 - Implement the `main()` function
The program should print a prompt and then collect the data from the user into a command line.  
Once the user terminates the input, parse the data into a set of values to be placed into a dynamically allocated list of integer values. 
Take the value table and print a summary of the data (# values, min, max, avg).
Release the data structures and exit the program.

#### Step 1 - Create an algorithm for `main()`
The requirements for the program are given above.  You should see from that description that a prompt will be printed and the user will type in data.  That data will need to be captured by the `get_unbounded_line()` function.  The resulting command line will be passed to the other function `get_value_table()` to be parsed and converted into integers.  The function will return a list of integer values that can be processed to provide the desired statistics.

From the description above, you can create an algorithm for the main function.
```
	Print a prompt

	Get the command line from user (call get_unbounded_line())
	Check the results for validity

	Parse the command line given (call get_value_table(...))
	Check validity of the results

	Process the table to generate required statistics
	Print results
```

For many developers, the inclination is to quickly write each of the simple functions and test it all at once.  
Below are the sub-steps that will make the development process work better.   
Before you write any code for the `get_unbounded_line()` or `get_value_table()`, you should get the main function ready to test your code for those other functions.

#### Step 1.1  - Getting `main()` ready for testing
Create the structure for the code where you can compile and test that the main function flow works.  This involves writing ***stub*** functions for any functions you need to create.  The ***stub*** functions will allow the `main()` code to call the function, but each stub function will return immediately without performing any work.

Because you are using C as your programming language, you will need to use the primitive printing functionality that it provides.   You will be using `printf(...)` as the main mechanism for displaying information to the terminal window.  Although I have provided you with a stub main function, the simplest main function would just print a message and exit.

```
int main() {
	// you will want to change the following line to display your prompt 
	printf("This is my prompt> ");  

	return 0;
}
```
That is as much code as I would write before making sure the program runs.  I know it seems really trivial, but often I will have a typo or forget to put a semicolon in the code.  Instead of receiving hundreds of compiler messages, the small amount of code will only generate a few warnings or errors that can easily be fixed.

#### Step 1.2  - Testing function calls
Now that you can print that prompt, let's add the call to the first function.  Make sure that you can handle a problem from the function, such as it returns a NULL pointer.   After updating your main code with the call, update the stub version of the `get_unbounded_line()` to immediately return a NULL so you can test this code.
```
	command_line = get_unbounded_line();
	// check that the call returns a valid response.  
	// If the return value is NULL, there is no further processing that can be performed
	if (command_line == NULL) {
		// report problem and exit program
	}
```
You will need to test the return values from all the functions that you call.  This includes any functions that you write, as well as all library and system calls.  Return value checking is required on all labs and programming assignments.
Compile and run the program to make sure it performs as required.  

This tests for the negative results from the function.  You can modify the stub function to return a test string.  Instead of returning a NULL, have the function `return "1 2 3";` to simulate getting a good command line.  Again, compile and run the program to make sure it performs as required.  


#### Step 1.3  - Add call to other function
Now you can proceed to add the call to the second function.  You should test the possibility that the function will not be able to perform its function.  Test for return of NULL.

```
	/// call and check results for parsing
	... table = get_value_table(command_line);
	if (table == NULL) ...
```
You can modify the  stub for the `get_value_table()` function to return a table with set values ([1, 2, 3, INT_MIN]). 

Now you can create the code for the processing of the table.  I suggest that you create your own function to perform the analysis.  Add a stub for the function and write the comments describing its functionality and algorithm if known.

Your code should now have all the functionality layed out and stubs created for the processing.  Your next steps should proceed to fill in the additional functionality  as needed.  Remember that using small increments followed by compiling and testing will provide the quickest path to completing the assignment.

```
int main() {
	// you will want to change the following line to display your prompt 
	printf("This is my prompt> ");  

	... command_line = get_unbounded_line();
	// check that the call returns a valid response.  
	// If the return value is NULL, there is no further processing that can be performed
	if (command_line == NULL) {
		// report problem and exit program
	}

	/// call and check results for parsing
	... table = get_value_table(command_line);
	if (table == NULL) ...

	/// call and check results for analysis
	... results = your_function(table);
	if (results ...) ...

	return 0;
}
```
	

<hr>
	
### Part 2 - Implement the `get_unbounded_line()` function

Now you can begin the development of the `get_unbounded_line()` function.  
Please make a small number of changes and make sure the program works as required before adding more complex code.

Here is a basic algorithm for the function:
```
	allocate a minimum amount of buffer space
	while not EOF or EOL
		get next character
		if (no space left in buffer)
			extend the buffer
		append the character to the buffer
	return buffer
```
The algorithm above has a couple of items that are very vague.  Such as allocating space, or checking for EOL and EOF.   These indicate that you will need to research ways to solve those issues.  In the first case, you should already be familar with the dynamic allocation of memory from previous courses.  The `malloc()` and `realloc()` functions should be used here.   You can find documentation and examples from an AI or by searching for `man malloc` in a web browser.

Remember to take small steps, allocate a memory buffer and check the return value.  Once that works, think about how to extend the buffer size without losing the data already in the buffer.

The next sub-step would be to read some data from the user that could be placed into the buffer.   You will need to use the `fgetc()` function to read one character at a time.   You will read from the C file descriptor that represents input from the terminal.  The `stdin` file is used to read from the terminal window.  You should use `fgetc(stdin)` to read each character until reaching a newline character (`'\n'`) or the end of file.  Checking for EOF is done by calling `feof(stdin)`, which will return `true` if the end of the data has been reached.

For reference, I would suggest that you create 4-5 individual sub-steps to complete the code for this function.  Steps would include getting a small amount of key strokes from the user and returning those to the caller, being able to remember the number of keys collected and number of characters allocated, and then adding the code to reallocate the buffer when it gets full. 
<hr>
	
### Part 3 - Implement the `get_value_table(command_line)` function
The idea is to parse the line of text into sections and convert each section of text into an integer value.  You will again store the data in a dynamically allocated and unbounded data structure.  Here is a basic algorithm for the function:
```
allocate a minimum amount of table space

while more data in command line
	get next token
	convert token into integer value
	if (no space left in table)
		extend the table
	append the value to the table
	
append terminator value to table 
return table
```

The functions that you can use to split the complete command line into a series of space delimited strings is `strtok()` or you can use `strtok_r()` if you need a recursive (reusable with different values) function.  Practice with the function for initializing and then progressively collecting all the strings.

For each string extracted, convert from the ASCII string into an integer value using `atoi()`.  For each new value, place it into the table.  If the table is full, extend the table by a small amount.

As with the previous step, I would suggest that you create 4-5 individual sub-steps to complete the code for this function. Steps would include getting a small amount of values and returning those to the caller, being able to remember the number of values collected and number of integers allocated, and then adding the code to reallocate the table when it gets full.
<hr>
    
### When you have completed the Lab tutorial 

By this time in your CSPB career you should be able to write small programs from scratch given only the requirements for its functionality.  You will need to design the algorithms needed to solve the problems and implement the code to perform those algorithms.  The programs you create will need to provide comments that describe the purpose and usage of the program, purpose and usage of each function, and comments with the functions describing the algorithm being used to solve the problem.

I will continue to provide frameworks for the individual recitation labs so that you have a good starting point to complete the intended training.  These templates should allow you to see the level of documentation expected and style of code I prefer to see.

***Make sure to `commit` to your local repository and `push` to the remote repository.*** 
Grading of your work will be based on the information that you have in your remote repository.

Your code should include:
* implementation of `get_unbounded_line`
* implementation of `get_value_table`
* code that is commented well (many comments missing from sample given)

	
<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" style="margin-right:10px" />
Although the grading of your code will be done by accessing your <br> remote repository,
you must submit the following to Moodle Assignment:

* Your name:
* CU ID: (4 letters - 4 digits)
* GitHub Username:
* hours to complete lab:

<hr><hr><hr>