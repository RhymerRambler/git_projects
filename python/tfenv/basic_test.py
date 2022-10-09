# actual jupyter notebook:
# https://github.com/https-deeplearning-ai/tensorflow-1-public/blob/main/C1/W1/ungraded_lab/C1_W1_Lab_1_hello_world_nn.ipynb

import tensorflow as tf
from tensorflow import keras
import numpy as np

#disable gpus to avoid errors
exec(open('disable_gpus.py').read())

# create a basic neural net model - Sequential => a neural net with one tensor
# as input and other as output
model = keras.Sequential()

# add layers - just 1 layer with 1 neuron
model.add(keras.layers.Dense(units=1, input_shape=[1]))

# add optimizer and loss function
# sgd: stochastic gradient descent
# mean_squared_error: sum for all test values i = 0, N: [sqr(yi - (mxi + c))]
# : this loss needs to be minimized
model.compile(optimizer="sgd", loss="mean_squared_error")

# set up training data
xs = np.array([-1.0, 0.0, 1.0, 2.0, 3.0, 4.0], dtype='float')
ys = np.array([-3.0, -1.0, 1.0, 3.0, 5.0, 7.0], dtype='float')

# train the neural net
model.fit(xs, ys, epochs=200)

# test
print(model.predict([10.0]))

