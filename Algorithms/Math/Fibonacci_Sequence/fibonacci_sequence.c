#include<stdio.h>

/*
Function Declaration
--------------------
Our function will take in argument by value (integer) and return an interger
*/
int fibonacci(int n);

int main(){

    //i_nth number of fibonacci numbers
    int n=10;

    //printing the fibonnaci numbers
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\n",fibonacci(i));
    }
    
    return 0;
}
/*
Function definition
-------------------
fibonacci() function will take in an argument of i_nth integer number.

fibonacci() function will return fibonacci numbers one by one

Note:. that we use recursion function to solve this problem.
                   ------------------
Recursion function is the function that calls itself.
*/
int fibonacci( int n){

    //if n is 0 return 0
    if (n==0){
        return n;
    }

    //if n is 1 return 1
    if (n==1){
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}
