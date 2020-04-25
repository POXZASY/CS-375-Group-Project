# CS-375-Group-Project
Group work for CS 375 final project with Miguel Gomez, Nick Pellegrino, and Larkin Wisdom


# How to Compile & Run:
- 'make' compiles the C++ program
- 'python makeData.py' generates test data; prompts for 3 inputs (FILENUM, N, and C) and yields a file "input<FILENUM>.txt" in "input" directory with 50 test cases for the given parameters
- 'python runTests.py <number of input files>' runs all test cases and outputs files to "output" directory; each input file being ran must be consecutively named inputN.txt (N>=1)

# Computation and Run Time Analysis:
- Recursive w/ Memoization: O(n\*C), since there are n\*C unique cases that are each run (at maximum) once

- Bottom Up: O(n\*C), since we do an O(1) calculation for each cell in the table (table size is n+1 \* C+1)

# Classes & Interaction:
- Used a struct to represent the problem information: weights of items, values of items, and the capacity
- Used a struct to represent the solution information: the item numbers of the solution, weights of the items, values of the items, 2D matrix for the solution, total weight of all items, total value of all items, capacity of the problem, and the time spent computing the solution, in nanoseconds

# Data Structures & Implementation:
- All arrays for weights, values, the 2D solution matrix, etc used vectors from the standard C++ library
- A vector of Problems is populated, the knapsack function is called (relative to each solution type, recursive or bottom-up) on each Problem, and a Solution is produced, which populates a vector of Solutions
