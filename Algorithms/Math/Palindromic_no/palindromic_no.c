/*
This code help us to look if a given number is palindromic or not.
*/

#include<stdio.h>

int palindromic_no(int number, int reverse, int reaminder);

int main(){

    //Enter a number to check.
    int num;
    printf("Enter number: ");
    scanf("%d", &num);

    int rev=0;
    int rem;

    //check is done here
    palindromic_no(num, rev, rem);
    return 0;
}

int palindromic_no(int number, int reverse, int remainder){

    //reversing the given number
    int origin_no = number;
    while (number != 0)
    {
        remainder=number%10;
        reverse = reverse*10 +remainder;
        number /= 10;
    }

    //check if given number is pelindromic number or not.
    if (origin_no == reverse){
        printf("Number: %d, is palindromic number", origin_no);
    }else{
        printf("Number: %d, is not palindromic number", origin_no);
    }
    return 0;
}