import os
import sys
import subprocess

#number of tests
numtests = int(sys.argv[1])

dir = os.getcwd() #gets the string for the working directory
dir1 = dir + "\\bottomup" #gets the bottomup folder
dir2 = dir + "\\recursivememo" #gets the recursivememo

try:
    os.mkdir("output") #makes output folder
except:
    "Output directory already exists."
for i in range(numtests):
    input = "input/input"+str(i+1)+".txt" #name of input file
    output1 = "output/output_bottomup"+str(i+1)+".txt" #name of bottomup solution file
    output2 = "output/output_recursivememo"+str(i+1)+".txt" #name of recursive solution file
    subprocess.call(['cmd', '/c', dir1, input, output1])
    subprocess.call(['cmd', '/c', dir2, input, output2])
