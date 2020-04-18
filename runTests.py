import os
import subprocess

numtests = 7

dir = os.getcwd()
dir1 = dir + "\\bottomup.exe"
dir2 = dir + "\\recursivememo.exe"

#os.system("date")

for i in range(numtests):
    input = "input"+str(i+1)+".txt"
    output1 = "output_bottomup"+str(i+1)+".txt"
    output2 = "output_recursivememo"+str(i+1)+".txt"

    subprocess.call(['cmd', '/c', dir1, input, output1])
    subprocess.call(['cmd', '/c', dir2, input, output2])
