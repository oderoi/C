import numpy as np

# Sigmoid function
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# Test the sigmoid function with some values
inputs = np.array([-3.0, -1.0, 0.0, 1.0, 3.0])
outputs = sigmoid(inputs)

# Print the input-output pairs
for i, o in zip(inputs, outputs):
    print(f"Sigmoid({i}) = {o:.5f}")