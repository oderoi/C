#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define m 6           //number of examples
#define nx 2          //number of input features
#define ny 1          //number of output features

float sigmoid(float );
float compute_cost_logistic( float X[][nx], int y[m], int w[][ny], int );

int main(){

    //input and output datasets
    float X_train[][nx] = {{0.5, 1.5}, {1, 1}, {1.5, 0.5}, {3, 0.5}, {2, 2}, {1, 2.5}};         //(m,n)
    int y_train[m] = {0, 0, 0 , 1, 1, 1};

    //w and b parameters
    int w_init[][ny] = {1, 1};                  //(n, )
    int b1_init = -3;                           //scalar
    int b2_init = -4;                           //scalar

    double cost_b1 = compute_cost_logistic(X_train, y_train, w_init, b1_init);
    double cost_b2 = compute_cost_logistic(X_train, y_train, w_init, b2_init);

    printf("Cost for b = %d : %le\n", b1_init, cost_b1);

    printf("Cost for b = %d : %le\n", b2_init, cost_b2);



    return 0;
}

float sigmoid(float z_i){

    /*
        Compute sigmoid

        Args:
            z_i (scalar ):  target values

        Returns:
            sigmoid (scalar ):  sigmoid
    
    */

    return (float)1/(1 + exp(-z_i));
}

float compute_cost_logistic(float X[][nx], int y[m], int w[][ny], int b){
    /*
        Compute cost

        Args:
            X (ndarray (m,n)):  Data, m exapmles with n features
            y (ndarray (m, )):  target values
            w (ndarray (n, )):  model parameters
            b (scalar) .     :  model parameter

        Returns:
            cost (scalar):  cost
    */

   float cost=0;
   float z_i;
   float f_wb_i;

   for (int i = 0; i < m; i++)
   {
    for (int j = 0; j < ny; j++)
    {
        z_i=0;
        f_wb_i=0;
        for (int k = 0; k < nx; k++)
        {
            z_i += X[i][k] * w[k][j];
        }
        z_i += b; 
        f_wb_i = sigmoid(z_i);
        cost +=  (-y[i]*log(f_wb_i)) - ((1 - y[i]) * log(1 - f_wb_i));
    }
    

   }
   cost /=m;

   return cost;
   
}