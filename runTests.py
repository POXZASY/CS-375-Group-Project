import os
import subprocess

numtests = 6

dir = os.getcwd()
dir1 = dir + "\\bottomup.exe"
dir2 = dir + "\\recursivememo.exe"

#os.system("date")
try:
    os.mkdir("output")
except:
    "Output directory already exists."
for i in range(numtests):
    input = "input/input"+str(i+1)+".txt"
    output1 = "output/output_bottomup"+str(i+1)+".txt"
    output2 = "output/output_recursivememo"+str(i+1)+".txt"

    subprocess.call(['cmd', '/c', dir1, input, output1])
    subprocess.call(['cmd', '/c', dir2, input, output2])
