import time
from subprocess import run

def test(input,output):
    print(input)
    start = time.time()
    run("avl.exe", stdin=open(input), stdout=open(output, "w"))
    end = time.time()
    print("AVL: ", end - start)
    start = time.time()
    run("splay.exe", stdin=open(input), stdout=open(output, "w"))
    end = time.time()
    print("SPLAY: ", end - start)

input_dir = "in/"
input_name = ".in"
for i in range(1,11):
    file = input_dir + str(i) + input_name
    test(file, "output.txt")
