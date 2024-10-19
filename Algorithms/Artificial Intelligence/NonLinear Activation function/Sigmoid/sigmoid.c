#include <stdio.h>
#include <math.h>

// Function to compute the sigmoid activation
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

int main() {
    // Test the sigmoid function with some sample inputs
    double input[] = {-3.0, -1.0, 0.0, 1.0, 3.0};
    int size = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < size; i++) {
        printf("Sigmoid(%.2f) = %.6f\n", input[i], sigmoid(input[i]));
    }

    return 0;
}