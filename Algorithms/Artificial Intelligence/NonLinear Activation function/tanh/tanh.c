#include <stdio.h>
#include <math.h>

//Function to calculate Tanh Function
double tanh(double x) {
    return ( exp(x) - exp(-x) ) / ( exp(x) + exp(-x) );
}

int main() {
    // Test the tanh function with some sample inputs
    double input[] = {-3.0, -1.0, 0.0, 1.0, 3.0};
    int size = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < size; i++) {
        printf("Tanh(%.2f) = %.6f\n", input[i], tanh(input[i]));
    }

    return 0;
}