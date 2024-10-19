Here’s a GitHub README combining both ReLU (Rectified Linear Unit) and Leaky ReLU activation functions:

ReLU & Leaky ReLU - Activation Functions

This repository provides an overview of the Rectified Linear Unit (ReLU) and its variant Leaky ReLU. Both are commonly used activation functions in neural networks and deep learning, particularly for their simplicity and efficiency.

Table of Contents

	1.	What is ReLU?
	2.	What is Leaky ReLU?
	3.	Mathematical Definitions
	4.	Advantages of ReLU
	5.	Advantages of Leaky ReLU
	6.	Disadvantages of ReLU
	7.	Disadvantages of Leaky ReLU
	8.	Code Example
	9.	Alternatives
	10.	References

What is ReLU?

Rectified Linear Unit (ReLU) is one of the most widely used activation functions in modern deep learning models. It is defined as:

￼

ReLU sets any negative input to zero and passes positive input values through unchanged. This simplicity makes ReLU computationally efficient, especially for large networks.

Characteristics:

	•	Non-linear: Despite its simplicity, ReLU introduces non-linearity, allowing the network to learn complex mappings.
	•	Efficient: ReLU is computationally cheaper than other functions like tanh or sigmoid.

What is Leaky ReLU?

Leaky ReLU is a variant of ReLU that allows a small, non-zero gradient for negative input values, thereby addressing the “dying ReLU” problem. It is defined as:

￼

Where ￼ is a small positive value, usually set to 0.01 by default.

Characteristics:

	•	Fixes dying ReLU: Leaky ReLU provides small, non-zero outputs for negative inputs, avoiding the problem of neurons “dying” during training.
	•	Parameterized slope: The ￼ parameter can be tuned to control the negative slope.

Mathematical Definitions

ReLU:

￼

	•	For ￼, ￼
	•	For ￼, ￼

Leaky ReLU:

￼

	•	For ￼, ￼
	•	For ￼, ￼, where ￼ is typically small (e.g., 0.01).

Advantages of ReLU

	1.	Simplicity:
	•	ReLU is extremely easy to implement and computationally inexpensive, which is essential for deep neural networks.
	2.	Sparsity:
	•	ReLU activates only a subset of neurons (i.e., the neurons with positive inputs), leading to sparse representations, which can improve computational efficiency and make the model more robust.
	3.	Efficient Gradient Propagation:
	•	ReLU does not saturate in the positive region, which helps avoid the vanishing gradient problem during backpropagation.

Advantages of Leaky ReLU

	1.	Prevents Dying Neurons:
	•	By allowing a small gradient for negative values, Leaky ReLU prevents the “dying ReLU” problem where neurons get stuck with zero gradients and stop learning.
	2.	Improved Gradient Flow:
	•	Since it provides a non-zero slope for negative inputs, Leaky ReLU improves gradient flow and helps the model converge faster in some cases.

Disadvantages of ReLU

	1.	Dying ReLU Problem:
	•	Neurons can “die” during training if they consistently receive negative inputs, resulting in zero gradients and no further learning for those neurons.
	2.	Unbounded Output:
	•	ReLU is unbounded for positive inputs, which can sometimes lead to exploding gradients in deep networks.

Disadvantages of Leaky ReLU

	1.	Extra Parameter:
	•	Leaky ReLU introduces an additional parameter ￼, which needs to be tuned for optimal performance.
	2.	Still Unbounded:
	•	Like ReLU, Leaky ReLU is also unbounded for positive inputs, which could lead to large gradient updates if not controlled.


Alternatives

	1.	ELU (Exponential Linear Unit):
	•	A smoother alternative to ReLU, ELU allows negative inputs to have non-zero gradients while smoothing out the output.
￼
	2.	PReLU (Parametric ReLU):
	•	Similar to Leaky ReLU but with a learnable parameter for the slope of negative inputs. The slope is learned during training.
	3.	Swish:
	•	A newer activation function that outperforms ReLU in some cases, defined as ￼.

References

	1.	Understanding ReLU
	2.	Activation Functions in Deep Learning
	3.	Leaky ReLU Explained

Feel free to fork this repository, contribute, or explore more about the ReLU and Leaky ReLU activation functions!