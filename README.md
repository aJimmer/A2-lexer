#A Lexical Analyzer for A2-Lexicon

Author: Angel Jimenez

Email: Ajl890889702@csu.fullerton.edu

Github: Github.com/ajimmer

Files: 
* main.cpp :  Source code for tokenizing input
* program.txt : Text file where could can be written according to A2-Lexicon Specifications
* Makefile : Needed when compiling in the command line


##General Usage Notes:

* This program was built and tested with Xcode on OSX 10.11

* It was also tested succesfully through terminal with gcc

* The language used was C/C++

* This program is designed for the user to write code into the provided text file and compiling it in an IDE or through the command line. After successfully compiling and processing the input the program will display information on the produced tokens in order to be used for Syntactic Analysis.


##Features

* Functioning Automatons recieve input from the text file character by character. 
* Input is processed in real time and assigned a token value according to the entry.
* The tokenized input is processed by the parse machine.
* Output is displayed according to the tokens in a stack vs factored non-terminals according to the grammar.
* Debugging can be accomplished by uncommenting the print statements throughout the code, or using the debugger.

##Bugs

* Although not thouroghly tested, all features work accoriding to given examples in specification.
* Further testing maybe necessary to find issues 
* Refactoring and optimization are still necessary

##How To Run

1. First, download or clone the repository https://github.com/aJimmer/A2-lexer to your preferred location.

2. Navigate to the directory via the command line.

3. Run the **MAKEFILE** by typing "make" into the command line.

4. Run the **MAIN** process by typing in "./main program.txt"

