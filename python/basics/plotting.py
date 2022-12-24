import numpy as np
# Generate the sum of k coin flips, repeat that n times
# Experiment is doing "k coin flips", and that experiment is repeated n times
def generate_counts(k=1000,n=100):
    X=2*(np.random.rand(k,n)>0.5)-1  # generate a kXn matrix of +-1 random
    print ("Shape of X: {}".format(X.shape))
    S=np.sum(X,axis=0) # sum all the rows (i.e. the k coin flips) to get n columns - ideally, these
                       # sums should be zero, as half of them should be 1 and
                       # other half -1
    print ("Shape of S = {}".format(S.shape))
    return S




import matplotlib.pyplot as plt
k=1000
n=1000
counts=generate_counts(k=k,n=n)
plt.figure(figsize=[10,4]) # width and height in inches
plt.hist(counts); # plot histogram
plt.xlim([-k,k])  # from -1000 to 1000
plt.xlabel("sum")
plt.ylabel("count") # frequency of each sum
plt.title("Histogram of coin flip sum when flipping a fair coin %d times"%k)
plt.grid()
plt.show()


