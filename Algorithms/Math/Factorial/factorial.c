#include<stdio.h>

//function definition
double factorial(double a);

int main(){
    double a=98;

    //function calling
    double ans=factorial(a);
    printf("%f!:    %f\n", a, ans);
    return 0;
}

//function to compute factorila n! = n.)n - 1)!
double factorial(double a){
    if (a<=1){
        return 1;
    }

    //we use recursion
    return a*factorial(a-1);
}
