# CS-375-Group-Project
Group work for CS 375 with Miguel Gomez and Nick Pellegrino


# How to Compile & Run: 
- 'make' compiles the C++ program
- 'python makeData.py' generates test data; prompts for 3 inputs (FILENUM, N, and C) and yields a file "input<FILENUM>.txt" with 50 test cases for the given parameters
- 'python runTests.py <#inputfiles>' runs all test cases; each inputfile being ran must be consecutively named inputN.txt (N>=1)

# Computation and Run Time Analysis:
- Recursive w/ Memoization: O(n\*C), since there are n\*C unique cases that are each run (at maximum) once
  
- Bottom Up: O(n\*C), since we do an O(1) calculation for each cell in the table (table size is n+1 \* C+1)

# Classes & Interaction:


# Data Structures & Implementation: 

