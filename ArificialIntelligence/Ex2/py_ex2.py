# Author - Yehoshua Lipsker

import math


# Class - Node. Represents the structure of node in the Decision tree
# members- attribute, children(map to subNodes), and label if exists
class Node(object):
    def __init__(self, attribute, label):
        self.attribute = attribute
        self.children = {}
        self.label = label

    # Method to attach subNode to the appropriate child in children's map
    def add_child(self, value, sub_node):
        self.children[value] = sub_node


# Class - Prediction. Creates and calculates the 3 models of prediction
# knn, naive bayes and decision tree. members - train data, test data, attributes,
# labels and features
class Prediction:
    def __init__(self, train_data, test_data, attributes):
        self.train_data = train_data
        self.test_data = test_data
        self.attributes = attributes
        self.labels = list(set([x[1] for x in self.train_data]))
        features_list = [feature for x in self.train_data for feature in x[0]]
        self.features = list(set(features_list))

    # knn method for predicting the test data. for each row in test data it finds the k
    # closest rows in train data(by hamming distance) and predict according to this
    def knn(self, n):
        knn_predictions = []
        accuracy = 0
        for row in self.test_data:
            hamming_list = []
            for x in self.train_data:
                hamming_list.append((sum(0 if feature == row[0][i] else 1
                                         for i, feature in enumerate(x[0])), x[1]))
            hamming_list.sort(key=lambda y: y[0])
            top_k = [ham[1] for ham in hamming_list[:n]]
            label_0_counter = label_1_counter = 0
            for label in top_k:
                if label == self.labels[0]:
                    label_0_counter += 1
                else:
                    label_1_counter += 1
            prediction = self.labels[0] if label_0_counter > label_1_counter else self.labels[1]
            accuracy = accuracy + (1 if prediction == row[1] else 0)
            knn_predictions.append(prediction)
        accuracy = accuracy/len(self.test_data)
        return accuracy, knn_predictions

    # naive bayes method to predict on test data. for each row in test data it calculates the
    # probability of each feature according to every label in train data and the higher
    # probability predicts the label
    def nb_predict(self):
        accuracy = 0
        nb_predictions = []
        prediction = None
        prior_probabilities = {}
        for label in self.labels:
            prior_probabilities[label] = 0
        for row in self.train_data:
            prior_probabilities[row[1]] += 1
        for row in self.test_data:
            probabilities = []
            for label in self.labels:
                probability = 1
                for i, feature in enumerate(row[0]):
                    probability *= self.calculate_posterior_probability(i, feature, label)
                probability *= prior_probabilities[label]
                probabilities.append((label, probability))
            if probabilities[0][1] > probabilities[1][1]:
                prediction = probabilities[0][0]
            if probabilities[0][1] < probabilities[1][1]:
                prediction = probabilities[1][0]
            if probabilities[0][1] == probabilities[1][1]:
                prediction = self.majority()
            nb_predictions.append(prediction)
            accuracy = accuracy + (1 if prediction == row[1] else 0)
        accuracy /= len(self.test_data)
        return accuracy, nb_predictions

    # method to calculate posterior probability for each feature given that "label" is the label
    def calculate_posterior_probability(self, i, feature, label):
        counter = 1
        reduced_by_label_train = [row for row in self.train_data if row[1] == label]
        for x in reduced_by_label_train:
            if x[0][i] == feature:
                counter += 1
        return counter / (len(reduced_by_label_train) + len(self.attributes[0]))

    # recursive method for creating the decision tree using ID3 algorithm
    def DTL(self, examples, attributes, default):
        if not examples:
            return Node(None, default)
        is_same_label, label = self.has_same_label(examples)
        if is_same_label:
            return Node(None, label)
        if not attributes:
            return Node(None, self.MODE(examples))
        best = self.CHOOSE_ATRIBUTE(attributes, examples)
        node = Node(best, None)
        new_attributes = attributes[:]
        new_attributes.remove(best)
        attribute_index = self.attributes[0].index(best)
        for value in self.get_values_for_attribute(best, self.train_data):
            examples_i = [example for example in examples if value == example[0][attribute_index]]
            sub_node = self.DTL(examples_i, new_attributes, self.MODE(examples))
            node.add_child(value, sub_node)
        return node

    # MODE function that determines which label will be the default(according to majority)
    def MODE(self, examples):
        label_0_counter = label_1_counter = 0
        for row in examples:
            if row[1] == self.labels[0]:
                label_0_counter += 1
            else:
                label_1_counter += 1
        if label_0_counter > label_1_counter:
            return self.labels[0]
        elif label_1_counter > label_0_counter:
            return self.labels[1]
        return self.labels[0] if (self.labels[0] == "true" or self.labels[0] == "yes") else self.labels[1]

    # metod that checks if all the examples have the same label and we can stop the recursion
    def has_same_label(self, examples):
        label_0_counter = label_1_counter = 0
        for row in examples:
            if row[1] == self.labels[0]:
                label_0_counter += 1
            else:
                label_1_counter += 1
        if label_0_counter > 0 and label_1_counter > 0:
            return False,None
        if label_0_counter > 0 and label_1_counter == 0:
            return True, self.labels[0]
        if label_0_counter == 0 and label_1_counter > 0:
            return True, self.labels[1]

    # method that calculates info-gain of every attribute and returns the "best" attribute
    def CHOOSE_ATRIBUTE(self, attributes, examples):
        gain_list = []
        for i, attribute in enumerate(attributes):
            gain = self.calculate_gain(attribute, examples)
            gain_list.append(gain)
        attribute_index = gain_list.index(max(gain_list))
        return attributes[attribute_index]

    # method that returns all possible values for attribute
    def get_values_for_attribute(self, attribute, examples):
        attribute_index = self.attributes[0].index(attribute)
        return list(set([row[0][attribute_index] for row in examples]))

    # method that calculates entropy function
    def entropy(self, labels_column):
        result = 0
        for label in self.labels:
            frequency = self.calculate_frequency(label, labels_column)
            if frequency == 0:
                continue
            result -= (frequency * math.log(frequency, 2))
        return result

    # method that calculates the frequency of value in a given column
    def calculate_frequency(self, value, column):
        value_counter = 0
        for example in column:
            if value == example:
                value_counter += 1
        return value_counter / len(column)

    # method that gets attribute name and set of examples and calculates the info
    # gain for this attribute in this set of examples
    def calculate_gain(self, attribute, examples):
        labels_column = [example[1] for example in examples]
        result = self.entropy(labels_column)
        value_attribute_column = self.get_column_for_attribute(attribute, examples)
        values = self.get_values_for_attribute(attribute, examples)
        attribute_index = self.attributes[0].index(attribute)
        for value in values:
            value_labels_column = [example[1] for example in examples if value == example[0][attribute_index]]
            result -= (self.calculate_frequency(value, value_attribute_column) *
                       self.entropy(value_labels_column))
        return result

    # method that returns the whole column for specific attribute in set of examples
    def get_column_for_attribute(self, attribute, examples):
        attribute_index = self.attributes[0].index(attribute)
        return [example[0][attribute_index] for example in examples]

    # decision tree method that predicts on test data. for each row in test data, it runs on the
    # decision tree according to the features in the row and predicts by the label in the tree
    def dt_predict(self, decision_tree):
        accuracy = 0
        dt_predictions = []
        for row in self.test_data:
            node = decision_tree
            while(not node.label):
                attribute_index = self.attributes[0].index(node.attribute)
                node = node.children[row[0][attribute_index]]
            dt_predictions.append(node.label)
            accuracy = accuracy + (1 if node.label == row[1] else 0)
        accuracy /= len(self.test_data)
        return accuracy, dt_predictions

    # method that returns the majority label in the train data
    def majority(self):
        label_0_counter = label_1_counter = 0
        for row in self.train_data:
            if row[1] == self.labels[0]:
                label_0_counter += 1
            else:
                label_1_counter += 1
        if label_1_counter > label_0_counter:
            return self.labels[1]
        else:
            return self.labels[0]


# Utilities class - handles all the missions that not related directly to the 3 models
# of prediction such as read and write the data from/to files. all the methods are static
class Utils:
    # method for reading the train and test data from file and split it to attributes and data
    @staticmethod
    def read_data(file_name):
        with open(file_name, "r+") as f:
            headers_names = f.readline()
            data_lines = f.readlines()
            split_headers = headers_names.split("\t")
            attributes = [split_headers[:-1], split_headers[-1].rstrip("\n")]
            split_data = [x.split("\t") for x in data_lines]
            data = [(y[:-1], y[-1].rstrip("\n")) for y in split_data]
            return attributes, data

    # method for writing the predictions and their accuracy to output.txt
    @staticmethod
    def write_output(dt_predictions, knn_predictions, nb_predictions, dt_acc, knn_acc, nb_acc):
        with open("output.txt", "w+", newline='') as f:
            f.write("Num\tDT\tKNN\tnaiveBase\n")
            for i in range(1,len(dt_predictions) + 1):
                f.write(str(i) + "\t" + dt_predictions[i - 1] + "\t" + knn_predictions[i - 1] +
                        "\t" + nb_predictions[i - 1] + "\n")
            f.write("\t" + str(round(dt_acc, 2)) + "\t" + str(round(knn_acc, 2)) + "\t" + str(round(nb_acc, 2)))

    # method that takes the decision tree as object and returns string representation of it
    @staticmethod
    def create_output_tree(decision_tree, num_of_tabs):
        s = ""
        for key, value in sorted(decision_tree.children.items()):
            for i in range(num_of_tabs):
                s += "\t"
            if num_of_tabs:
                s += "|"
            if value.label:
                s += decision_tree.attribute + "=" + key + ":" + value.label + "\n"
            if not value.label:
                s += decision_tree.attribute + "=" + key + "\n"
                s += Utils.create_output_tree(value, num_of_tabs + 1)
        return s

    # method that writes the decision tree to output_tree.txt file
    @staticmethod
    def write_output_tree(s):
        with open("output_tree.txt", "w+", newline='') as f:
            f.write(s)


# main function - handles the logic of the program
def main():
    attributes, train_data = Utils.read_data("train.txt")
    _, test_data = Utils.read_data("test.txt")
    prediction = Prediction(train_data, test_data, attributes)
    knn_acc, knn_predictions = prediction.knn(5)
    nb_acc, nb_predictions = prediction.nb_predict()
    decision_tree = prediction.DTL(prediction.train_data[:], prediction.attributes[0][:],
                                   prediction.MODE(prediction.train_data[:]))
    dt_acc, dt_predictions = prediction.dt_predict(decision_tree)
    Utils.write_output(dt_predictions, knn_predictions, nb_predictions, dt_acc, knn_acc, nb_acc)
    s = Utils.create_output_tree(decision_tree, 0)
    Utils.write_output_tree(s[:-1])


if __name__ == "__main__":
    main()
