#include <stdio.h>

// Function to compute ReLU
double ReLU(double x) {
    return (x > 0) ? x : 0; // Return x if x is positive, otherwise return 0
}

int main() {
    // Test the ReLU function with some sample inputs
    double input[] = {-3.0, -1.0, 0.0, 1.0, 3.0};
    int size = sizeof(input) / sizeof(input[0]);

    

    for (int i = 0; i < size; i++) {
        printf("ReLU(%.2f) = %.2f\n", input[i], ReLU(input[i]));
    }

    return 0;
}