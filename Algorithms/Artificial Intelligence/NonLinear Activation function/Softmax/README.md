Here’s a GitHub README about the tanh activation function:

Hyperbolic Tangent (tanh) - Activation Function

The tanh (hyperbolic tangent) activation function is another popular activation function used in neural networks, especially in recurrent neural networks (RNNs). It is known for its ability to map input values into a range of (-1, 1), providing a centered output and making it useful for certain types of neural network architectures.

Table of Contents

	1.	What is tanh?
	2.	Mathematical Definition
	3.	Advantages
	4.	Disadvantages
	5.	Code Example
	6.	Alternatives to tanh
	7.	References

What is tanh?

The tanh (hyperbolic tangent) function is a common activation function used in neural networks. It is defined as:

￼

The function squashes input values to a range between -1 and 1, making it useful for cases where you need to handle negative and positive inputs symmetrically.

Characteristics:

	•	S-shaped curve: tanh is a smooth, continuous function with an S-shaped curve.
	•	Range: Outputs between -1 and 1.
	•	Zero-centered: Unlike ReLU and sigmoid, tanh is zero-centered, meaning negative inputs are strongly mapped to negative outputs.

Mathematical Definition

The tanh function is mathematically defined as:

￼

Key Properties:

	•	For large positive values of x, the output approaches 1.
	•	For large negative values of x, the output approaches -1.
	•	The output is zero-centered, unlike the sigmoid function, which outputs between 0 and 1.

Advantages

	1.	Zero-Centered Output:
	•	Unlike the sigmoid function, which outputs values between 0 and 1, tanh outputs values between -1 and 1. This makes it easier to model relationships where negative inputs should map to negative outputs, and helps with the symmetry of the gradients during training.
	2.	Smoother Gradients:
	•	The gradients of the tanh function are larger than those of the sigmoid in the range of -1 to 1. This makes it more suitable for backpropagation, as larger gradients help the model converge faster.
	3.	Better for Binary Classification:
	•	tanh is often used in binary classification tasks when output values need to be positive or negative rather than bounded between 0 and 1.

Disadvantages

	1.	Vanishing Gradient Problem:
	•	Similar to the sigmoid function, the tanh function can suffer from the vanishing gradient problem. When the input values are too large or too small, the gradients approach zero, slowing down learning in deeper networks.
	2.	Computationally Expensive:
	•	The tanh function involves exponentials, which are computationally more expensive compared to simpler activation functions like ReLU.
	3.	Not Suitable for Very Deep Networks:
	•	While tanh works well for shallow networks, its susceptibility to vanishing gradients makes it less useful in deep neural networks where many layers of activation functions are applied.

Alternatives to tanh

	1.	Sigmoid:
	•	Similar to tanh but squashes inputs to a range between 0 and 1. It is useful for tasks where you need probabilistic interpretations but suffers more from the vanishing gradient problem.
￼
	2.	ReLU (Rectified Linear Unit):
	•	Outputs zero for negative inputs and linear for positive ones. ReLU is computationally more efficient and addresses the vanishing gradient problem better than tanh.
￼
	3.	Leaky ReLU:
	•	An extension of ReLU, allowing a small negative slope for negative inputs. This helps address the “dying ReLU” problem.
	4.	Swish:
	•	A newer activation function, defined as ￼, it has been shown to outperform both ReLU and tanh in some tasks.

References

	1.	Understanding the tanh Activation Function
	2.	Activation Functions in Neural Networks
	3.	Exploring Activation Functions

Feel free to fork, contribute, or explore more about the tanh activation function!