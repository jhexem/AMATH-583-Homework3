import numpy as np
import matplotlib.pyplot as plt
import csv

with open('results.csv', newline='') as f:
    reader = csv.reader(f)
    results_list = []
    for row in reader:
        results_list.append(int(row[0]))
    f.close()

size = int(len(results_list) / 2)
kij_array = np.array(results_list[0:size])
jki_array = np.array(results_list[size::])
xvals = np.arange(2, 513)
plt.plot(xvals, kij_array, "blue", label="kij Permutation")
plt.plot(xvals, jki_array, "red", label="jki Permutation")
plt.title("Problem 2 Speed for -ffast-math Compile")
plt.xlabel("Size of Matrices")
plt.ylabel("Speed in MFLOPS")
plt.legend(framealpha=1, frameon=True)
plt.show()