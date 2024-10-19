#include <stdio.h>
#include <math.h>

//Function to compute ELU function
double ELU(double x){
    //value to which ELU saturates for negative input   values
    double alpha = 1.0; 

    return (x >= 0) ? x : alpha * (exp(x) - 1.0);
}

int main(){
    // Test the ELU function with some sample inputs
    double input[] = {-10.0, -5.0, 0.0, 5.0, 10.0};
    int size = sizeof(input) / sizeof(input[0]);

    for(int i = 0; i < size; i++){
        printf("ELU(%.2f) = %.6f\n", input[i], ELU(input[i]));
    }
    return 0;
}