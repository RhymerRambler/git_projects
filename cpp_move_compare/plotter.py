import pandas as p
csv_data = p.read_csv("out.csv", header=None)
print (csv_data)

import numpy
data2d = csv_data.values
print (type(data2d))
#x axis of the plot has the element count
xaxis = [1000, 2500, 5000, 7500, 10000, 25000, 50000, 75000, 100000, 250000]
import math
lxaxis = [math.log(x,10) for x in xaxis] 
# y1 axis has the data for the copy case and it is in the first column of data2d
y1axis = data2d[:,0]
y2axis = data2d[:,1]
y3axis = data2d[:,2]
print (y1axis)
print (y2axis)
print (y3axis)

import matplotlib
import matplotlib.pyplot as plt

#plt.plot(lxaxis, y1axis, '--ro', lxaxis, y2axis, ':bs', lxaxis, y3axis, ':g^')
plt.ylabel('Running time (in milliseconds)');
plt.xlabel('No of objects copied/moved/emplaced to std::vector (log10 scale)');
plt.plot(lxaxis, y1axis, linestyle='--', color='r', marker='o', label="copy");
plt.plot(lxaxis, y2axis, linestyle=':', color='b', marker='s', label="move");
plt.plot(lxaxis, y3axis, linestyle=':', color='g', marker='^', label="emplace");
plt.legend()
plt.savefig("plt.png")
plt.show()
