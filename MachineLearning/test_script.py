epochs = [10, 30, 50]
lrs = [0.1, 0.01]
functions = ["sigmoid", "relu"]
sizes = [50, 100, 200]

for epoch in epochs:
    for lr in lrs:
        for func in functions:
            for size in sizes:
                with open("output.txt", 'a+') as f:
                    f.write(
                        "current parameters: epochs = "+ str(epoch) + " lr = " + str(lr) + " func = " + str(func) + " layer size = " + str(size) +"\n")
                parameters = initializeParameters(size)
                train(parameters,trainSet_x,trainSet_y,validationSet_x,validationSet_y, epoch, func, lr)