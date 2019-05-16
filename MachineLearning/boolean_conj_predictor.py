#Yehoshua Lipsker
#204038533

import numpy as np
import sys


# function that get hypothesis and sequence of bits and evaluate the answer
def evaluate(hyp, seq):
    for i, bit in enumerate(seq):
        if bit:
            if 0 in hyp[i]:
                return 0
        else:
            if 1 in hyp[i]:
                return 0
    return 1

# load the training examples
training_examples = np.loadtxt(sys.argv[1])

# create the X matrix and Y vector i case it's more than one sample
if training_examples.ndim > 1:
    (rows, columns) = training_examples.shape
    d = columns - 1
    X = training_examples[:,:d]
    Y = training_examples[:,d]
else:
    (columns,) = training_examples.shape
    rows = 1
    d = columns - 1
    X = []
    X.append(training_examples[:d])
    Y = []
    Y.append(training_examples[d])

# create the deafult hypothesis
h0 =[]
for i in range(d):
    h0.append([1,0])

# for every sample - if labeled 1, and hypothesis evaluates to 0, remove the failing literals.
#                    else - leave it as is
for i in range(rows):
    if Y[i] == 1 and evaluate(h0, X[i]) == 0:
        for j in range(len(X[i])):
            if X[i][j]:
                if 0 in h0[j]:
                    h0[j].remove(0)
            else:
                if 1 in h0[j]:
                    h0[j].remove(1)
    if Y[i] == 0:
        continue

# generate output and write it to file
output = []
for idx,val in enumerate(h0):
    for bit in val:
        if bit:
            output.append('x' + str(idx + 1))
        else:
            output.append('not(x' + str(idx + 1) + ')')
writeToFile = ','.join(output)
with open('output.txt', 'w') as f:
    f.write(writeToFile)
