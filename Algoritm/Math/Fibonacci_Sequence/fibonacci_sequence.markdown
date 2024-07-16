# Fibonacci Sequence in C

Fibonacci Sequence is a sequence in which each number is the sum of the two preceding ones.

Number that are part of the Fibonacci sequence are known as Fibonacci numbers.

It is commonly start with 0 and 1.

The Fibonacci Sequence.


$F_{0} = 0,     F_{1} = 1,$

and

$f_{n} = F_{n - 1}  +   F_{n - 2}$

for $n > 1.$

![Fibonacci Spiral](images/Fibonacci_Spiral.svg.png)
$Fibonacci Spiral$

```c
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

```
