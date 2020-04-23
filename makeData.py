# In all experiments, we generated 50 different cases of N items with random weights in the range of 1 to (C + 2)
# and profit in the range of ($1 - $100). We then kept those generated items constant between both algorithms
# tested for that experiment.

import random

# Helper function that generates items for a given test
def getItems(N, weightRoof):
    weights = [] # Storage for generated weights, which will be up to size N
    profits = [] # Storage for generated profits, which will be up to size N
    # Generate N items
    for i in range(0, N):
        weights.append(random.randint(1, weightRoof)) # Add a random weight, range 1-(C+2), for the given item to storage
        profits.append(random.randint(1, 101)) # Add a random profit, range $1-$100, for the given item to storage
    # Return weights and profits for a given test
    return weights, profits

# Main function that calls getItems 50 times to create 50 tests, then saves the data to a file
def main():
    # Gather input data
    num = input("Enter Experiment #: ")
    N = (int)(input("Enter N: "))
    C = (int)(input("Enter C: "))

    # Our weights will range from 1 to C+2
    weightRoof = C+3

    # Format of the "input[experiment #].txt" file we are making data for:
    # weights  (test #1)
    # profits  (test #1)
    # capacity (test #1)
    # weights  (test #2)
    # profits  (test #2)
    # capacity (test #2)
    # ...
    # weights  (test #50)
    # profits  (test #50)
    # capacity (test #50)

    # Generate the data
    output = "" # String to store the final output for the file
    for i in range(0, 50): # Generate data for 50 tests
        weights, profits = getItems(N, weightRoof) # Helper function for generating 1 of our 50 tests

        # Format the data as specified in the comment block
        w = "" # Temp string for formatting purposes
        p = "" # Temp string for formatting purposes
        for j in range(0, N):
            w += str(weights[j]) + ' '
            p += str(profits[j]) + ' '
        w = w[:len(w)-1]
        p = p[:len(p)-1]
        # Concatenate the generated test (1 of 50) to our output string (which holds all 50)
        output += w + '\n' + p + '\n' + str(C) + '\n'

    # Save output to the file named "input[experiment #].txt"
    file = open("input/input" + str(num) + ".txt", "w")
    file.write(output)
    file.flush()
    file.close()

# Call main
main()
