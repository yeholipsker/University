#Yehoshua Lipsker
#204038533

import numpy as np
import pickle


#load the data and shuffle it and normalize it
def loadData():

    train_x = np.loadtxt("train_x")
    train_y = np.loadtxt("train_y")
    test_x = np.loadtxt("test_x")

    '''#########for improvement
    data = open("me.txt", "rb").read()
    c = pickle.loads(data)
    train_x = c[0]
    train_y = c[1]
    test_x = c[2]
    #########'''

    #zip shuffle divide
    zipped = zip(train_x,train_y)
    np.random.shuffle(zipped)
    validationSetSize = int(len(zipped)*0.2)
    trainSetZipped = zipped[:-validationSetSize]
    validationSetZipped = zipped[-validationSetSize:]

    #unzip
    trainSet_x, trainSet_y = zip(*trainSetZipped)
    validationSet_x, validationSet_y = zip(*validationSetZipped)
    trainSet_x = np.array(trainSet_x)
    trainSet_y = np.array(trainSet_y)
    validationSet_x = np.array(validationSet_x)
    validationSet_y = np.array(validationSet_y)

    #normalize
    trainSet_x = trainSet_x/255.0
    validationSet_x = validationSet_x/255.0
    test_x = test_x/255.0

    return trainSet_x, trainSet_y, validationSet_x, validationSet_y, test_x


def initializeParameters(size):
    inputSize, layerSize, outputSize = 784, size, 10
    w1 = np.random.uniform(-1,1, size=(layerSize,inputSize))
    b1 = np.random.uniform(-1,1,size=(layerSize,1))
    w2 = np.random.uniform(-1,1,size=(outputSize,layerSize))
    b2 = np.random.uniform(-1,1,size=(outputSize,1))
    parameters = {'w1':w1, 'b1':b1, 'w2':w2, 'b2':b2}
    return parameters


def shuffleSet(trainSet_x, trainSet_y):
    zipped = zip(trainSet_x, trainSet_y)
    np.random.shuffle(zipped)
    return zipped


def sigmoid(z):
    return 1 / (1 + np.exp(-z))


def sigmoidDerivative(z):
    x = sigmoid(z)
    return x * (1 - x)


def softmax(x):
    exp = np.exp(x - np.max(x))
    return exp / exp.sum()

def reLU(x):
    return x * (x > 0)


def reLUDerivative(x):
    return 1.0 * (x > 0)


def tanh(x):
    return np.tanh(x)


def tanhDerivative(x):
    return 1.0 - (tanh(x)**2)


funcsDict = {'sigmoid': [sigmoid, sigmoidDerivative],
             'relu': [reLU, reLUDerivative],
             'tanh': [tanh, tanhDerivative]}


def fProp(parameters, x, activationFunc):
    W1, b1, W2, b2 = [parameters[key] for key in ('w1', 'b1', 'w2', 'b2')]
    z1 = np.dot(W1, x) + b1
    h1 = funcsDict[activationFunc][0](z1)
    z2 = np.dot(W2, h1) + b2
    h2 = softmax(z2)
    ret = {'w1': W1, 'b1': b1, 'w2': W2, 'b2': b2, 'h1': h1, 'h2':h2, 'z1': z1}
    return ret


def bProp(fPropCache, x, y, activationFunc):
    W1, b1, W2, b2, h1, h2, z1 = [fPropCache[key] for key in ('w1', 'b1', 'w2', 'b2', 'h1', 'h2', 'z1')]
    yVector = np.zeros((10,1))
    yVector[int(y)] = 1
    loss_softmax_derivative = (h2 - yVector)
    dW2 = np.dot(loss_softmax_derivative,h1.T)
    db2 = loss_softmax_derivative
    dW1 = np.dot(np.dot(W2.T,loss_softmax_derivative) * funcsDict[activationFunc][1](z1),x.T)
    db1 = np.dot(W2.T,loss_softmax_derivative) * funcsDict[activationFunc][1](z1)
    return {'dW2': dW2, 'db2': db2, 'dW1': dW1, 'db1': db1}


def updateParameters(parameters, gradientParams, learningRate):
    oldW1, oldB1, oldW2, oldB2 = [parameters[key] for key in ('w1', 'b1', 'w2', 'b2')]
    parameters['w1'] = oldW1 - learningRate * gradientParams['dW1']
    parameters['w2'] = oldW2 - learningRate * gradientParams['dW2']
    parameters['b1'] = oldB1 - learningRate * gradientParams['db1']
    parameters['b2'] = oldB2 - learningRate * gradientParams['db2']
    return  parameters


def calcLoss(y_hat, y):
    return (-1.0) * np.log(y_hat[int(y)])


def validate(parameters, activationFunc, validationSet_x, validationSet_y):
    lossSum = 0.0
    counter = 0.0
    for i, x in enumerate(validationSet_x):
        x = np.reshape(x, (784, 1))
        outDict = fProp(parameters, x, activationFunc)
        y_hat = outDict['h2']
        y = validationSet_y[i]
        loss = calcLoss(y_hat, y)
        lossSum += loss
        if np.argmax(y_hat) == y:
            counter += 1
    accuracy = counter / validationSet_x.shape[0]
    averageLoss = lossSum / validationSet_x.shape[0]
    return accuracy, averageLoss


def train(parameters, trainSet_x, trainSet_y, validationSet_x, validationSet_y, epochsNum, activationFunc, learnRate):
    for i in range(epochsNum):
        lossSum = 0.0
        zippedSet = shuffleSet(trainSet_x,trainSet_y)
        for x,y in zippedSet:
            x = np.reshape(x,(784,1))
            fPropCache = fProp(parameters,x, activationFunc)
            gradientParams = bProp(fPropCache, x, y, activationFunc)
            parameters = updateParameters(parameters, gradientParams, learnRate)
            loss = calcLoss(fPropCache['h2'], y)
            lossSum += loss
        accuracy, averageLoss = validate(parameters, activationFunc, validationSet_x, validationSet_y)
        print "epoch number: {}, ".format(i) + "success rate: {:03.2f}%".format(float(accuracy * 100))
    return  parameters
        #with open("output.txt", 'a+') as f:
            #f.write("epoch number: {}, ".format(i) + "success rate: {:03.2f}%".format(float(accuracy * 100)) + "\n")

epochsNum, activationFunc, learnRate, layerSize = 20, 'sigmoid', 0.01, 200
trainSet_x, trainSet_y, validationSet_x, validationSet_y, test_x = loadData()
parameters = initializeParameters(layerSize)
parameters = train(parameters,trainSet_x,trainSet_y,validationSet_x,validationSet_y, epochsNum, activationFunc, learnRate)

with open("test.pred", 'w') as f:
    for x in test_x:
        x = np.reshape(x, (784, 1))
        fPropCache = fProp(parameters, x, activationFunc)
        decision = np.argmax(fPropCache['h2'])
        f.write(str(int(decision)) + "\n")
