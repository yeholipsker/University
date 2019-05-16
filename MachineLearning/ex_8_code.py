import numpy as np
import torch
import torchvision
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torchvision import datasets, transforms
from torch.utils.data import Dataset
from torch.utils.data.sampler import SubsetRandomSampler
import matplotlib.pyplot as plot

BATCH_SIZE = 64
IMAGE_SIZE = 28*28

optim_dict = {
    'SGD': optim.SGD,
    'Adam': optim.Adam,
    'Adadelta': optim.Adadelta,
    'RMSprop': optim.RMSprop,
}

class FirstNet(nn.Module):

    def __init__(self, image_size):
        super(FirstNet, self).__init__()
        self.image_size = image_size
        self.fc0 = nn.Linear(image_size, 100)
        self.fc1 = nn.Linear(100, 50)
        self.fc2 = nn.Linear(50, 10)

    def forward(self, x):
        x = x.view(-1, self.image_size)
        x = F.relu(self.fc0(x))
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        return F.log_softmax(x, 0)


class SecondNet(nn.Module):

    def __init__(self, image_size):
        super(SecondNet, self).__init__()
        self.image_size = image_size
        self.fc0 = nn.Linear(image_size, 100)
        self.fc1 = nn.Linear(100, 50)
        self.fc2 = nn.Linear(50, 10)
        self.dropout1 = nn.Dropout(0.3)
        self.dropout2 = nn.Dropout(0.2)

    def forward(self, x):
        x = x.view(-1, self.image_size)
        x = F.relu(self.fc0(x))
        x = self.dropout1(x)
        x = F.relu(self.fc1(x))
        x = self.dropout2(x)
        x = F.relu(self.fc2(x))
        return F.log_softmax(x, 0)


class ThirdNet(nn.Module):

    def __init__(self, image_size):
        super(ThirdNet, self).__init__()
        self.image_size = image_size
        self.fc0 = nn.Linear(image_size, 100)
        self.fc1 = nn.Linear(100, 50)
        self.fc2 = nn.Linear(50, 10)
        self.dropout1 = nn.Dropout(0.3)
        self.dropout2 = nn.Dropout(0.2)
        self.batchNorm1 = nn.BatchNorm1d(self.image_size)
        self.batchNorm2 = nn.BatchNorm1d(100)

    def forward(self, x):
        x = x.view(-1, self.image_size)
        x = self.batchNorm1(x)
        x = F.relu(self.fc0(x))
        x = self.dropout1(x)
        x = self.batchNorm2(x)
        x = F.relu(self.fc1(x))
        x = self.dropout2(x)
        x = F.relu(self.fc2(x))
        return F.log_softmax(x, 0)


def train(model, optimizer, train_loader):
    model.train()
    avg_loss = 0
    correct = 0
    for batch_idx, (data, labels) in enumerate(train_loader):
        optimizer.zero_grad()
        output = model(data)
        loss = F.nll_loss(output, labels)
        avg_loss += loss
        model_prediction = output.data.max(1, keepdim=True)[1]
        correct += model_prediction.eq(labels.data.view_as(model_prediction)).cpu().sum()
        loss.backward()
        optimizer.step()
    avg_loss /= batch_idx
    print('Train: Avg loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(avg_loss, correct, len(train_loader.sampler),
                                                                      100. * correct / len(train_loader.sampler)))
    ##########################################
    with open("log.txt", 'a+') as f:
        f.write('Train: Avg loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(avg_loss, correct, len(train_loader.sampler),
                                                                      100. * correct / len(train_loader.sampler)))
    ##########################################
    return avg_loss


def test(model, data_set,is_test):
    model.eval()
    avg_loss = 0
    correct = 0
    predictions_list = []
    for data, target in data_set:
        output = model(data)
        avg_loss += F.nll_loss(output, target, size_average=False).data
        model_prediction = output.data.max(1, keepdim=True)[1]
        if is_test:
            for pred_result in model_prediction.data:
                predictions_list.append(pred_result.item())
        correct += model_prediction.eq(target.data.view_as(model_prediction)).cpu().sum()
    avg_loss /= len(test_loader.sampler)
    print('Test set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        avg_loss, correct, len(data_set.sampler),
        100. * correct / len(data_set.sampler)))
    ##########################################
    with open("log.txt", 'a+') as f:
        f.write('Test set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        avg_loss, correct, len(data_set.sampler),
        100. * correct / len(data_set.sampler)))
    ##########################################
    return avg_loss, predictions_list


train_valid_set = datasets.FashionMNIST(root='./data', train=True, transform=transforms.ToTensor(), download=True)
test_set = datasets.FashionMNIST(root='./data', train=False, transform=transforms.ToTensor())

indexes = list(range(len(train_valid_set)))
valid_size = int(len(train_valid_set) * 0.2)

validation_idx = np.random.choice(indexes, size=valid_size, replace=False)
train_idx = list(set(indexes) - set(validation_idx))

train_sampler = SubsetRandomSampler(train_idx)
validation_sampler = SubsetRandomSampler(validation_idx)

train_loader = torch.utils.data.DataLoader(dataset=train_valid_set, batch_size=BATCH_SIZE, sampler=train_sampler)
validation_loader = torch.utils.data.DataLoader(dataset=train_valid_set, batch_size=BATCH_SIZE,
                                                sampler=validation_sampler)
test_loader = torch.utils.data.DataLoader(dataset=test_set, batch_size=BATCH_SIZE, shuffle=False)

optim_list = ['SGD', 'Adam', 'Adadelta', 'RMSprop']
lr_list = [0.1, 0.3, 0.01]
net_models_list = [FirstNet, SecondNet, ThirdNet]
i = 0

for optimizer in optim_list:
    for lr in lr_list:
        for net_model in net_models_list:
            train_losses = []
            validation_losses = []
            model = net_model(IMAGE_SIZE)
            i += 1
            print('======= evaluating optimizer=' + optimizer + ', lr=' + str(lr) + ', net_model=' + str(net_model) +
                  '=======\n')
            ##########################################
            with open("log.txt", 'a+') as f:
                f.write('======= evaluating optimizer=' + optimizer + ', lr=' + str(lr) + ', net_model=' +
                        str(net_model) + '=======\n')
            ##########################################
            for epoch in range(10):
                print('----- Epoch #: ' + str(epoch) + '-----\n')
                ##########################################
                with open("log.txt", 'a+') as f:
                    f.write('----- Epoch #: ' + str(epoch) + '-----\n')
                ##########################################
                train_losses.append(train(model,optim_dict[optimizer](model.parameters(), lr=lr),train_loader))
                validation_avg_loss, validation_list = test(model, validation_loader, False)
                validation_losses.append(validation_avg_loss)
            avg_loss, prediction_list = test(model, test_loader, True)
            with open("testPreds/test.pred" + str(i), "w") as output_file:
                output_file.write('\n'.join(str(pred) for pred in prediction_list))
            '''
            p1, = plot.plot(list(range(0, 10)), train_losses)
            p2, = plot.plot(list(range(0, 10)), validation_losses)
            plot.legend([p1, p2], ["avg train loss", "avg validation loss"])
            plot.xlabel("Num of Epochs")
            plot.ylabel("Avg Loss")
            plot.show()'''