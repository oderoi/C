#include<stdio.h>
int bsearch(int arr[], int S, int E, int T);

int main(){

    //Array
    int arr[]={1,3,4,6,7,8,10,13,14,18,19,21,24,37,40,45,71};

    //size of array
    int n=sizeof(arr)/sizeof(int);

    //number we are to searche (element, n)
    //we ask user to enter the number
    int T;
    printf("Enter Element: T to find in the Array: ");
    scanf("%d", &T);

    //start_index, S
    int S=0;

    //end_index, E
    int E=n - 1;

    //initialize the index we are searching for to the binary search implementation
    int index=bsearch(arr, S, E, T);

    /*
    if binary search (bsearch() function) return -1, 
        - this means it did not find the number you are searching in the Array

    else, it will return the index of the searched number, (element, T).
    */
   
    if (index == -1)
    {
        printf("Element T: %d is Not found.\n", T);
    }else
    {
        printf("Element, T: %d is found at index: %d",T, index);
    }
    
    

    return 0;
}

int bsearch(int arr[], int S, int E, int T){

    //if end_index, E is greater or equal to start_index, S
    if (E >= S)
    {
        //find the middle_index, m
        int m= S + (E - S)/2;

        //if array element at middle_index, m is equal to element, T(number we are finding)
        //return the middle_index, m and end the program
        if (arr[m] == T){
            return m;
        }

        /*
        if array element at middle_index, m is greater than element, T(number we are searching)
            return this function (bsearch() function) with end_index, E is set to middle_index, m - 1
        else
            return this function (bsearch() function) with start_index, S is set to middle_index, m + 1 
        */
        if (arr[m] > T){
            return bsearch(arr, S, m - 1, T);
        }else
        {
            return bsearch(arr, m + 1, E, T);
        }
      
    }
    //return -1 if the number we are searching (element, T) is not found in Array
    return -1;
    
}
