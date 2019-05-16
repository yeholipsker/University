NUM_OF_ITERATOR = 5
NUM_OF_INSTANCES = 50

import random

# generate random instances of boolean conjunctions, and their implementations
def main():
    booleanConjuction = list()

    # initialize the conjuction with 0
    for i in range(1, NUM_OF_ITERATOR + 1):
        booleanConjuction.append(0)

    # random 1 and 0
    for i in range(1, NUM_OF_ITERATOR):
        p = random.randint(0, 1)
        if p is 1:
            booleanConjuction[i] = 1

    # random dropping of iterators
    for i in range(1, NUM_OF_ITERATOR):
        p = random.randint(1, 99)
        if p > 50:
            booleanConjuction[i] = -1

    #random number of instances
    samples = list()
    for i in range(0, NUM_OF_INSTANCES):
        instance = list()
        for j in range(0, NUM_OF_ITERATOR):
            insItem = bool(random.getrandbits(1))
            instance.append(insItem)
        samples.append(instance)
        Y = True
        for j in range(0, NUM_OF_ITERATOR):
            # 0=^ | 1=not^ | -1=remove operator
            if(booleanConjuction[j] == 0):
                Y = Y and not samples[i][j]
            elif(booleanConjuction[j] == 1):
                Y = Y and samples[i][j]
        samples[i].append(Y)

    # write samples to file
    #file = open("trainingData/example1.txt", "w")
    file = open("myexample.txt", "w")
    for i in range(0, NUM_OF_INSTANCES):
        for j in range(0, NUM_OF_ITERATOR+1):
            if(samples[i][j] == True):
                file.write("1")
                if(j<NUM_OF_ITERATOR):
                    file.write(" ")
            else:
                file.write("0")
                if (j < NUM_OF_ITERATOR):
                    file.write(" ")
        if(i<NUM_OF_INSTANCES-1):
            file.writelines("\n")

    # print boolean conjunction
    lOutput = list()
    for i in range(0, len(booleanConjuction)):
        if(booleanConjuction[i] == 0):
            toStr = "not(x" + str(i+1) + ")"
            lOutput.append(toStr)
        elif(booleanConjuction[i] == 1):
            toStr = "x" + str(i+1)
            lOutput.append(toStr)

    sOutput = ""
    for i in range(0, len(lOutput)):
        sOutput = sOutput + lOutput[i]
        if(i < len(lOutput)-1):
            sOutput = sOutput + ","






    for i in range(0, len(samples)):
        print samples[i]
    print booleanConjuction
    print(sOutput)
    with open('output2.txt', 'w') as f:
        f.write(sOutput)











if __name__ == "__main__":
    main()