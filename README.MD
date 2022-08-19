# A simplified BASIC interpreter for your terminal!

To run: 
Note: after cloning the repository, make sure to clone submodules:
```
$ git submodule update --init
$ make
$ ./bin/interpreter.bin
```
Once the program is running, enter "HELP" to see a help function.

The following BASIC keywords are supported:
REM 
LET
PRINT
INPUT
GOTO
IF
END

# Project Structure

This project includes one submodule (CSON), a simple string-string hashmap I implemented to keep track of variable values during interpretation.

The important files are as follows:

interpreter.c reads user input and handles top-level commands (RUN, LIST, CLEAR, HELP, AND QUIT).

scanner/scanner.c is called when the RUN command is entered. It scans the program as entered into tokens of four possible types: o (operand: +, -, *, /), k (keyword: listed above), n (number), v (variable name: everything else). It then returns all these tokens as an array. Note that tokens are essentially just strings with an assigned type.

parser/parser.c is called next. It parses an array of tokens into an array of statements. Note that statements store the following information: the type of statement (basically, what keyword is being called - REM, LEt, PRINT, INPUT, GOTO, IF, or END) and the corresponding arguments.

parser/evals.c is called next. It evaluates an array of statements and is responsible for actually "running" the program. Not that this file calls CSON/hashmapLite.c, which is a barebones hashmap I implemented to keep track of variable values.