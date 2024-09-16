#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define m 2             //row
#define n 1             //col

int **copy(int src[][n]);
int **deepcopy(int src[][n]);

int main(){
    //Initialized paramter
    int w_init[][n] = {3, 2};

    //perform shallow copy
    int **w=copy(w_init);
    
    printf("\nBefore changinge shallow copied parameter, w \n\n");
    printf("Original:  w_init[0][0]:   %d, w_init[1][0]:   %d \n", w_init[0][0], w_init[1][0]);
    printf("Deep copy:  w[0][0]:   %d, w[1][0]:   %d\n", w[0][0], w[1][0]);

    //change the copied parameter
    w[0][0] = 0;
    w[1][0] = 0;

    printf("\nAfter changinge shallow copied parameter, w\n\n");
    printf("Original:  w_init[0][0]:   %d, w_init[1][0]:   %d \n", w_init[0][0], w_init[1][0]);
    printf("Deep copy:  w[0][0]:   %d, w[1][0]:   %d\n", w[0][0], w[1][0]); 

    
    free(w);
    

    return 0;
}

int **copy(int src[][n]){

    /*
    Shallow copy
    Args:
        src (ndarray (row, col)):   initialized parameter

    Return:
        dest (ndarray (row, col)):  copy of the initilialized parameter
    */


    int **dest = (int **)calloc(m, sizeof(int *));
    if (dest ==NULL){
        perror("Error in allocating the memory");
        free(dest);
    }

    for (int i = 0; i < m; i++)
    {
        dest[i] = src[i];
    }

    return dest;
}

int **deepcopy(int src[][n]){
    /*
    Deep copy
    Args:
        src (ndarray (row, col)):   initialized parameter

    Return:
        dest (ndarray (row, col)):  copy of the initilialized parameter
    */

   int **dest = (int **)calloc(m, sizeof(int *));
   if (dest ==NULL)
   {
    perror("Error in allocating memory");
   }
   for (int i = 0; i < m; i++)
   {
    dest[i] = (int *)calloc(n, sizeof(int));

    if (dest[i]==NULL)
    {
        perror("Error in allocating memory");
        for (int j = 0; j < i; j++)
        {
            free(dest[j]);
        }
        free(dest);
        
    }

    for (int j = 0; j < n; j++)
    {
        dest[i][j] = src[i][j];
    }
    
   }
   
   
    return dest;
}