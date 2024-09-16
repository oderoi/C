#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    double x[][2]={{0.5, 1.5}, {1, 1}, {1.5, 0.5}, {3, 0.5}, {2, 2}, {1, 2.5}};;          //X->(nx, m)=>(2,3)
    double w[2]={1.0,2.0};    
    double b=1.0;              //W->(nx,1)=>(2,)

    double fx[6]; 
    double z[6];                          //Z->(1,m)=>(3,)
    
    for (int i = 0; i < 6; i++)
    {
        z[i]=0;
        for (int j = 0; j < 2; j++)
        {
            fx[i] += w[j]*x[i][j];
        }
        fx[i] =fx[i] + b;
        z[i] = 1/(1+exp(-fx[i]));
        
    }

    for (int i = 0; i < 6; i++)
    {
        printf("%f\t", z[i]);
    }
       
    return 0;
}