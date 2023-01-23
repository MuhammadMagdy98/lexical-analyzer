*Lexical Analyzer in C++*

`scanner.h`:
we have utility functions
- readInput() => reads input line by line
- scanner() returns the next token
- testScanner() 

`token.h`:
contains Token struct which consists of 
tokenID
tokenInstance
lineNumber

contians all lexical definitions 

`main.cpp`: 
  accepts at most 2 command line arguments, othewise print "invocation error"
  reads input and test scanner


Usage:

first type "make" in terminal 

- Usage 1: ./main 
- Usage 2: ./main < file
- Usage 3: ./main file

