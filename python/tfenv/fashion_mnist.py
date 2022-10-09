# full notebook: https://github.com/https-deeplearning-ai/tensorflow-1-public/blob/main/C1/W2/ungraded_labs/C1_W2_Lab_1_beyond_hello_world.ipynb

import tensorflow as tf
print(tf.__version__)

# fashion mnist database is part of tensorflow keras package
fmnist = tf.keras.datasets.fashion_mnist

# fmnist is an object of a class
#print (type(fmnist))
#print (dir(fmnist))
##see signature of load_data method
#import inspect
#print (inspect.signature(fmnist.load_data))
#print (help(fmnist.load_data))

# use its load_data member method to load the mnist database - it will return
# two tuples each with 2 lists
#
# Load the training and test split of the Fashion MNIST dataset
(training_images, training_labels), (test_images, test_labels) = fmnist.load_data()

print(type(training_images))

#import numpy as np
#import matplotlib.pyplot as plt

# You can put between 0 to 59999 here
#index = 0
#
# # Set number of characters per row when printing
#np.set_printoptions(linewidth=320)
#
# # Print the label and image
#print(f'LABEL: {training_labels[index]}')
#print(f'\nIMAGE PIXEL ARRAY:\n {training_images[index]}')
#
# # Visualize the image
#plt.imshow(training_images[index])
#plt.show()


# Normalize the pixel values of the train and test images
training_images  = training_images / 255.0
test_images = test_images / 255.0

# Build the classification model
# Sequential: That defines a sequence of layers in the neural network.

#Flatten: Remember earlier where our images were a 28x28 pixel matrix when you printed them out? Flatten just takes that square and turns it into a 1-dimensional array.

#Dense: Adds a dense (fully connected) hidden layer of neurons

#Each layer of neurons need an activation function to tell them what to do. There are a lot of options, but just use these for now:
#relu: for the hidden layer
#softmax: for the output layer
#softmax is a activation function that outputs probablity of a particular output.
#Like in this case, there are 10 possible outputs represented by each neuron.
#softmax would give high probablity for the output that is matching the input image 
model = tf.keras.models.Sequential([tf.keras.layers.Flatten(), 
                                    tf.keras.layers.Dense(128, activation=tf.nn.relu), 
                                    tf.keras.layers.Dense(10,  activation=tf.nn.softmax)])

# add the optimizer and loss function to the model
model.compile(optimizer = tf.optimizers.Adam(),
              loss = 'sparse_categorical_crossentropy',
              metrics=['accuracy'])

# train the model
model.fit(training_images, training_labels, epochs=5)

# Evaluate the model on unseen data
model.evaluate(test_images, test_labels)

# let's classify a particular image
#
import matplotlib.pyplot as plt
import numpy as np
# verify 11th image in the test images
plt.imshow(test_images[11])
plt.show()
# classify_outp is an array with each element of it being a list of 10 values,
# representing probablity for each category
classify_outp = model.predict(test_images);
# print the index with maximum value (i.e. probablity)
print(f'output: {np.argmax(classify_outp[11])}')
print(f'expected: {test_labels[11]}')

