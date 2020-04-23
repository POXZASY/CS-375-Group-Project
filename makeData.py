# In all experiments, we generated 50 different cases of N items with random weights in the range of 1 to (C + 2)
# and profit in the range of ($1 - $100). We then kept those generated items constant between both algorithms
# tested for that experiment.

import random

# weights
# profits
# capacity

def getItems(N, weightRoof):
    weights = []
    profits = []
    for i in range(0, N):
        weights.append(random.randint(1, weightRoof))
        profits.append(random.randint(1, 101))
    return weights, profits

def main():
    num = input("Enter Experiment #: ")
    N = (int)(input("Enter N: "))
    C = (int)(input("Enter C: "))
    weightRoof = C+3
    output = ""
    for i in range(0, 50):
        w = ""
        p = ""
        weights, profits = getItems(N, weightRoof)
        for j in range(0, N):
            w += str(weights[j]) + ' '
            p += str(profits[j]) + ' '
        w = w[:len(w)-1]
        p = p[:len(p)-1]
        output += w + '\n' + p + '\n' + str(C) + '\n'
    file = open("input" + str(num) + ".txt", "w")
    file.write(output)
    file.flush()
    file.close()

main()
