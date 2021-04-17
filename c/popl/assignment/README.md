# Compiler Construction Assignment

Submission by Jashanpreet Singh: 2018A7PS0134G

## Summary of project

The assignment is written using `C`, `lex` and `yacc` and compiled Using `gcc`,`flex` and `bison`.

## Project Structure

These are following files in the directory.

- <code>lexer.l</code> : This is the scanner file written in `lex`. This converts the given input into various `Tokens`.
- <code>parser.y</code> : This is the parser file written in `yacc`. This receives tokens from the scanner and runs instructions accordingly.
- <code>game.h</code> : This is the header file contains function definitions and struct initialization.
- <code>makefile</code> : This is the make file used to compile the program.

## Compiling and Initialization

The entire compilation for the code can be done directly through the makefile and the make command.

To compile and run, use <code>make</code> command.

## Removing build files

Run <code>make clean</code> to clean and remove the temporary build files.

## Exiting the app

Once inside the interactive shell, press  ` Ctrl+ c` to stop the program.


## Assumption

Given a row ` 4 2 2 4 ` than, SUBTRACT LEFT will result in ` 4 4 0 0 `.