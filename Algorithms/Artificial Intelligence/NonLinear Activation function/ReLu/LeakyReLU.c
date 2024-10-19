#include <stdio.h>

// Function to compute Leaky ReLU
double LeakyReLU(double x) {
    double alpha = 0.01;
    return (x > 0) ? x : alpha * x; // Apply the slope for negative values
}

int main() {
    // Test the Leaky ReLU function with some sample inputs
    double input[] = {-3.0, -1.0, 0.0, 1.0, 3.0};
    int size = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < size; i++) {
        printf("Leaky ReLU(%.2f) = %.2f\n", input[i], LeakyReLU(input[i]));
    }

    return 0;
}