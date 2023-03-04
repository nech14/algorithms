import time
import sys
import numpy as np
import matplotlib.pyplot as plt

n = 5

mapTest = input()
mapT = mapTest.split()
mapTime = []
mapMemory = []

for i in range(int(len(mapT)/2)):
    mapTime.append(float(mapT[i*2]))
    mapMemory.append(int(mapT[i*2+1]))

def test(n: int):
    steps = []
    for i in range(n+1):
        steps.append(10**i)

    t = time.perf_counter()
    mas = []
    dict = {}
    l = 1
    for i in steps:
        for j in range(l, i):
            dict[j] = j
        l = i

        elapsed = (time.perf_counter() - t)
        mas.append(elapsed)
        mas.append(sys.getsizeof(dict))
    return mas



masD = test(n)
masDictTime = []
masDictMemory = []

for i in range(int(len(masD)/2)):
    masDictTime.append(masD[i*2])
    masDictMemory.append(masD[i*2+1])

steps = []
for i in range(int(len(mapTime))):
    steps.append(10**i)

print(steps[:-2])

plt.plot(steps[:-2], masDictTime, label = 'Python')
plt.plot(steps, mapTime, label = 'C++')
plt.xlabel("number of iterations")
plt.ylabel("time")
plt.legend()

print("C++ time: ", mapTime)
print("Python time: ", masDictTime)

plt.show()





plt.plot(steps[:-2], masDictMemory, label = 'Python')
plt.plot(steps, mapMemory, label = 'C++')
plt.xlabel("number of iterations")
plt.ylabel("used memory")
plt.legend()

print("C++ use memory: ", mapMemory)
print("Python use memory: ", masDictMemory)

plt.show()

