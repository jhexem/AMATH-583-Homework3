import numpy as np
import matplotlib.pyplot as plt
import csv

with open('results.csv', newline='') as f:
    reader = csv.reader(f)
    results_list = []
    for row in reader:
        results_list.append(int(row[0]))
    f.close()
    
results_array = np.array(results_list)
xvals = np.arange(2, 513, 2)
plt.plot(xvals, results_array, "red")
plt.title("Problem 3 Strassen Multiplication Speed")
plt.xlabel("Size of Matrices")
plt.ylabel("Speed in MFLOPS")
plt.show()