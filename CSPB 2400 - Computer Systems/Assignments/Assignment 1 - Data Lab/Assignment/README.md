# CSPB 2400 - Computer Systems - Data Lab: Manipulating Bits

## Introduction

The purpose of this assignment is to become more familiar with bit-level representations of integers (and floating point) numbers. You'll do this by solving a series of programming ``puzzles.'' Some of these puzzles are quite artificial, but you'll find yourself thinking much more about bits in working your way through them.

## Logistics

All handins are electronic via Github Classroom.  Clarifications and corrections will be posted on the course page. Grading will be done through interviews.

## Handout Instructions

You will be provided a link to download a Github repository containing the template code.

This will cause a number of files to be unpacked in the directory. The only file you will be modifying and turning in is `bits.c`.

The `bits.c` file contains a skeleton for each of the programming puzzles.  Your assignment is to complete each function skeleton. You should should not use loops or conditionals and you can only use a limited number of C arithmetic and logical operators as specified in each problem. Specifically, you are **only** allowed to use the following eight operators:
```
 ! ~ & ^ | + << >>
```
A few of the functions further restrict this list.  Also, you are not allowed to use any constants longer than 8 bits, but you can construct larger constants using 8 bit constants and operators.  See the comments in `bits.c` for detailed rules and a discussion of the desired coding style.

## The Puzzles

This section describes the puzzles that you will be solving in [bits.c](bits.c). Each problem has a **Difficulty Rating** and **maximum number of operations**.  The **Rating** field gives the difficulty rating (the number of points) for the puzzle, and the **Max ops** field gives the maximum number of operators you are allowed to use to implement each function.  The following report from `make grade` would score 100% and also score extra credit.

```
Correctness Results     Perf Results
Points  Rating  Errors  Points  Ops     Puzzle
1       1       0       2       4       bitAnd
1       1       0       2       4       fitsShort
1       1       0       2       4       thirdBits
2       2       0       2       7       anyEvenBit
2       2       0       2       2       copyLSB
2       2       0       2       2       implication
4       4       0       2       25      bitCount
3       3       0       2       6       ezThreeFourths
3       3       0       2       17      satMul3
4       4       0       2       11      bitParity
4       4       0       2       78      ilog2
4       4       0       2       12      trueThreeFourths
2       2       0       2       5       float_neg
4       4       0       2       27      float_i2f
4       4       0       2       15      float_twice

General Points = 55/55 [31/31 Corr + 24/24 Perf]
Extra Points = 16/16 [10/10 Corr + 6/6 Perf]

Conversion to 40% of DataLab grading (the remaining 60% will come from interview grading)
Execution Grade = 40
Execution Extra = 4

```
Three of these problems (`float_neg`, `float_i2f`, and `float_twice`) are optional extra credit problems.

See the comments in [bits.c](bits.c) for more details on the desired behavior of the functions. You may also refer to the test functions in [tests.c](tests.c).  These are used as reference functions to express the correct behavior of your functions, although they don't satisfy the coding rules for your functions.

### Floating-Point Puzzles

For Extra Credit, you can implement some common single-precision floating-point operations.  
For these, you are allowed to use standard control structures (conditionals, loops), and you may use both `int` and `unsigned` data types, including arbitrary unsigned and integer constants.  You may not use any unions, structs, or arrays.  You may not use any floating point data types, operations, or constants.  Instead, any floating-point operand will be passed to the function as having type `unsigned`, and any returned floating-point value will be of type `unsigned`.  Your code should perform the bit manipulations that implement the specified floating point operations.

Functions must handle the full range of possible argument values, including not-a-number (NaN) and infinity.  The IEEE standard does not specify precisely how to handle NaN's, and the IA32 behavior is a bit obscure.  We will follow a convention that for any function returning a NaN value, it will return the one with bit representation `0x7FC00000`. See [the longer README](README-longer.md) for details on using `fshow` to develop your solutions.

## Evaluation

The assignment is scored in two parts - you will receive 40 percent of the overall score for having correctly functioning functions handed in on time and 60 percent for being able to correctly explain how  your functions work in your interview grading section and how to generalize those solutions.

Running [make grade](README-longer.md) will grade your solution; it combines the scores for the Integer and extra-credit Floating Point puzzles. The [ longer README](README-longer.md) has information on how to test your puzzles.

## Extra Credit
You can receive up to 10% extra credit (for the whole assignment) by completing all of the floating point problems. You will have to read ahead to learn about floating point, because we're going to cover it later; however, you're going to have to learn it someday...


## Submitting Your Assignment

You should submit your assignment using `git`. The normal commands you would execute commit **a**ll the files with a **m**essage and then push them to Github.
```
git commit -a -m"some useful about your commit"
git push
```

## The ``Beat the Prof'' Contest

For fun, we're offering an optional ``Beat the Prof'' contest that allows you to compete with other students and the instructor to develop the most efficient puzzles. The goal is to solve each Data Lab puzzle using the fewest number of operators. Students who match or beat the instructor's operator count for each puzzle are winners!

To submit your entry to the contest, type:
```
    unix> ./driver.pl -u ``Your Nickname''
```
Nicknames are limited to 35 characters and can contain alphanumerics, apostrophes, commas, periods, dashes, underscores, and ampersands. You can submit as often as you like. Your most recent submission will appear on a real-time scoreboard, identified only by your nickname. You can view the scoreboard by pointing your browser at
[http://cs2400-applied.cs.colorado.edu:8080](http://cs2400-applied.cs.colorado.edu:8080).
