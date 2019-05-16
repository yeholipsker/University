# Test Script Usage:
# ./python gen_trainset.py <Examples to generate> <Length of each train example> <Boolean format>
# e.g. ./python gen_trainset.py 2 4 -1,2,-3
# (meaning not(x1),x2,not(x3))
#
# Example Output:
# 0 0 1 0 0
# 0 1 0 1 1
#
# The output goes to text-data.txt

import sys
import numpy as np


def test_hyp(hypothesis, instance):
    # This function performs a functional XNOR (Not + XOR)
    # If the hypothesis is ever 0 (not) and the input is 1 -> returns 0 -> False
    # Similarly, if the hypothesis is 1 (value) and the input is 0 -> returns 0
    for index, hyp_val in hypothesis.iteritems():
        x_instance = instance[abs(index) - 1]
        if hyp_val != x_instance:
            return 0
    return 1


num_examples = int(sys.argv[1])
num_variables = int(sys.argv[2])
correct = sys.argv[3].split(',')
hyp_form = {int(x): (0 if int(x) < 0 else 1) for x in correct}

with open('test-data.txt', 'w') as outfile:
    for i in range(num_examples):
        train = np.random.randint(2, size=num_variables, dtype=int)
        classify = test_hyp(hyp_form, train)
        train = np.append(train, classify)
        print np.array_str(train)[1:-1]
        outfile.write(np.array_str(train)[1:-1] + '\n')