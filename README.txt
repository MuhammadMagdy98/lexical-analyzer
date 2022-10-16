I'm using the option 2

scanner.h:
we have utility functions
readInput() => reads input line by line
isIdentifier() 
isKeyWord()
isInteger()
isOperator()
isComment() 
scanner() returns the next token
testScanner() 

token.h:
contains Token struct which consists of 
tokenID
tokenInstance
lineNumber

contians all lexical definitions 

main.cpp: 
  accepts at most 2 command line arguments, othewise print "invocation error"
  reads input and test scanner


Usage:
first type "make" in terminal 
Usage 1: ./main 
Usage 2: ./main < file
Usage 3: ./main file

test cases conducted
P1_test1.cs4280:
x
P1_test2.cs4280:
x xy xyz x1 x2
1 12 23 12345
begin end loop void var exit scan print main fork then let data func
= >= <= == : ++ -- * / % . ( ) , { } ; [ ]
P1_test3.cs4280:
x x++2 x123=x1234 2%3 2 = = 3 2==3
P1_test4.cs4280:
#a comment test #
P1_test5.cs4280:
2x
2^x
