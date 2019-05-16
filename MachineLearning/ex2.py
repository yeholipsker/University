#Yehoshua Lipsker
#204038533

import numpy as np
import random
import matplotlib.pyplot as plt
from scipy.stats import norm


def createDistVec(mu):
    sigma = 1
    vec = np.random.normal(mu, sigma, 100)
    vecNormDistTagged = []
    for val in vec:
        vecNormDistTagged.append([val,mu])
    return vecNormDistTagged


def createTrainingData():
    vec2 = createDistVec(2)
    vec4 = createDistVec(4)
    vec6 = createDistVec(6)
    trainingData = vec2 + vec4 + vec6
    random.shuffle(trainingData)
    return trainingData


def softmax(x):
  exp = np.exp(x - np.max(x))
  return exp / exp.sum()


def getNormPrediction(weightsMatx,vec):
    beforeNorm = weightsMatx.dot(vec)
    return softmax(beforeNorm)


def getUpdateMatx(row,weightsMatx):
    vec = np.array([1, row[0]])
    afterNorm = getNormPrediction(weightsMatx,vec)
    if row[1] == 2:
        arr = np.array([1,0,0])
    if row[1] == 4:
        arr = np.array([0,1,0])
    if row[1] == 6:
        arr = np.array([0,0,1])
    loss = afterNorm - arr
    updateMatx = np.outer(loss,vec)
    return updateMatx


def getTrueProb(val):
    condProb2 = norm(2, 1).pdf(val)
    condProb4 = norm(4, 1).pdf(val)
    condProb6 = norm(6, 1).pdf(val)
    return condProb2 / (condProb2 + condProb4 + condProb6)


trainingData = createTrainingData()
weightsMatx = np.random.rand(3,2)
learningRate = 0.06
for i in range(300):
    for row in trainingData:
        updateMatx = getUpdateMatx(row,weightsMatx)
        weightsMatx = weightsMatx - learningRate * updateMatx

myProb = []
trueProb = []
values = []
for i in range(300):
    val = np.random.uniform(0,10)
    predArr = getNormPrediction(weightsMatx,np.array([1, val]))
    values.append(val)
    myProb.append(predArr[0])
    trueProb.append(getTrueProb(val))

plt.plot(values,myProb, 'ro', label='Predicted Prob')
plt.plot(values,trueProb, 'b*', label='True Prob')
plt.xlabel('values')
plt.ylabel('probability')
plt.legend(loc='upper right')
plt.show()