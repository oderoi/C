#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Function to calculate Softmax of a given array
double* Softmax(double input[], int length){
    double *result = (double*)calloc(length, sizeof(double));
    double *input_exp = (double *)calloc(length, sizeof(double));
    double sum = 0.0;

    //Compute the exponential of each input element and the sum
    for (int i=0; i<length; i++){
        input_exp[i] = exp(input[i]);
        sum += exp(input[i]);
    }

    //Compute the softmax output
    for (int i=0; i<length; i++){
        result[i] = input_exp[i] / sum;
    }

    //Free the dynamically allocated memory
    free(input_exp);

    return result;
}

int main(){
    //input array
    double input[] = {2.0, 1.0, 0.5};
    int length = sizeof(input) / sizeof(input[0]);

    //Compute the softmax of the input array
    double* output = Softmax(input, length);

    //Print the softmax output
    printf("Softmax Output:\n");
    for (int i=0; i<length; i++){
        printf("%.6f ", output[i]);
    }

    //Free the dynamically allocated memory
    free(output);

    return 0;
}