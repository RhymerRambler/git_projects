#translate 2D vectors to 3D vectors using the translation formula
#(2x+3y, 4x+7y, 5x+9y)
import numpy as np
from timeit import default_timer as timer

#generate 2D vectors as input, 1 million in count
data_2d = np.random.randint(10, 1000, (2, 1000000))

#initialize the output
data_3d = np.zeros((3,data_2d.shape[1]), dtype="int")

#Way 1: use the formula and a for loop
start = timer()
for i in range(data_2d.shape[1]):
    ele1 = 2*data_2d[0,i] + 3*data_2d[1,i]
    ele2 = 4*data_2d[0,i] + 7*data_2d[1,i]
    ele3 = 5*data_2d[0,i] + 9*data_2d[1,i]
    data_3d[0,i] = ele1
    data_3d[1,i] = ele2
    data_3d[2,i] = ele3
end = timer()
print(end - start)

#Way 2: use matrix multiplication
#create a transformation matrix using the translation formula
tf_matrix = np.array([[2, 3],[4, 7],[5, 9]], dtype="int")
start = timer()
data_3d_2 = tf_matrix.dot(data_2d)
end = timer()
print(end - start)

print(np.array_equal(data_3d, data_3d_2))


