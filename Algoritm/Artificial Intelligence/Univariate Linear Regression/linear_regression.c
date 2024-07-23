#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Initializing functions
float * compute_model_output(float x[], float w, float b, int m);
float compute_cost(float x[], float y[], float w, float b, int m);
float *compute_gradients(float x[], float y[], float w, float b, int m);
float *compute_weight_bias(float w, float b,float dj_dw,float dj_db, float alpha);
float evaluate_model(float x[], float y[], float w, float b, int m);

int main(){

    //initialize w and b
    float w_in = 0;
    float b_in = 0;

    //initialize input, x
    float x[]={6.1101, 5.5277, 8.5186, 7.0032, 5.8598, 8.3829, 7.4764,8.5781, 6.4862,5.0546, 5.7107, 14.164, 5.734, 8.4084, 5.6407,5.3794, 6.3654,5.1301,6.4296,7.0708,6.1891};
    float y[]={17.592, 9.1302, 13.662, 11.854, 6.8233, 11.886, 4.3483, 12, 6.5987, 3.8166,3.2522, 15.505, 3.1551,7.2258,0.71618,3.5129,5.3048,0.56077,3.6518,5.3893,3.1386};

    //number of example, m
    int m=sizeof(x)/sizeof(x[0]);
    float alpha=1e-2;
    int num_iters = 10000;

    float w=0;
    float b=0;
    float J_wb=0;
    float dj_dw=0;
    float dj_db=0;

    //    float *p_hist=(float *)malloc(num_iters*sizeof(float))

    for (int i = 0; i <= num_iters; i++)
    {
        // Save cost J at each iteration
        J_wb = compute_cost( x, y,  w,  b,  m);
        
        // Calculate the gradient and update the parameters using gradient_function
        float *grads =compute_gradients(x, y, w, b, m);

        dj_dw = grads[0];
        dj_db = grads[1];

        // Update Parameters using equation (3) above
        float *p_hist=compute_weight_bias( w, b, dj_dw, dj_db, alpha);

        //R squqre
        float R_square=evaluate_model( x,  y,  w,  b,  m);

        w=p_hist[0];
        b=p_hist[1];
        
        // Print cost every at intervals 10 times or as many iterations if < 10
        if (ceil(i%1000)==0)
        {
            printf("Iteration: %5d\tCost: %10f\t R_Score: %10f\t dj_dw: %10f\t dj_db:%10f\t w: %10f\tb:%8f\n", i, J_wb, R_square, dj_dw, dj_db,  w, b);
        }
    }

    //Predicting the Profit of restaurent, with a given Population, popul for 1 example, eg=1
    int eg=2;
    float popul[]={3.5, 7.5};

    float weight=w;
    float bias=b;
    float * pred=compute_model_output( popul,  weight,  bias,  eg);
    for (int i = 0; i < eg; i++)
    {
        printf("\nFor population : %f,\t we predict the profit of:$ %f\n", popul[i]*10000, pred[i]*10000);
    }

    return 0;
}

float * compute_model_output(float x[], float w, float b, int m){

    /*

    Computes the prediction of a linear model
    Args:
      X[m] (ndarray (m,1)): Data, m examples 
      w,b (scalar)     : model parameters 
      m (scalar)       : number of examples, X
    Returns
      Y[m] (ndarray (m,1)): target values

    */
    
    float *f_x=(float *)malloc(m*sizeof(float));

    for(int i=0; i<m; i++){
        f_x[i] = x[i]*w + b;
    }
    return f_x;
}

float compute_cost(float x[],float y[], float w, float b, int m){

    /*
    Computes the cost function for linear regression.
    
    Args:
      X (ndarray (m,1)): Data, m examples 
      Y (ndarray (m,1)): target values
      w,b (scalar)     : model parameters  
      m (scalar)       : number of examples, X
    
    Returns
        total_cost (float): The cost of using w,b as the parameters for linear regression
               to fit the data points in X and Y
    */

   float J_wb=0;
   float f_x;

   for (int i = 0; i < m; i++)
   {
    f_x = x[i]*w + b; 
    J_wb += pow((f_x - y[i]), 2);
   }
   J_wb /= (2*m);
   
   return J_wb;
}

float *compute_gradients(float x[], float y[], float w, float b, int m){

    /*
    Computes the gradients w,b for linear regression 
    Args:
      x (ndarray (m,1)): Data, m examples 
      y (ndarray (m,1)): target values
      w,b (scalar)    : model parameters  
      m (scalar)       : number of examples, X
    Returns
      dj_dw (scalar): The gradient of the cost w.r.t. the parameters w  
      dj_db (scalar): The gradient of the cost w.r.t. the parameters b
      grads (ndarray (2,1)): gardients [dj_dw, dj_db]  
    
    */

    float f_x;
    float dj_dw=0;
    float dj_db=0;
    float *grads=(float *)malloc(2*sizeof(float));

    for (int i = 0; i < m; i++)
    {
        f_x = x[i]*w + b;
        dj_dw += (f_x - y[i])* x[i];
        dj_db += (f_x - y[i]);
    }
    dj_dw /= m;
    dj_db /= m;

    grads[0] = dj_dw;   //index 0: dj_dw
    grads[1] = dj_db;   //index 1: dj_db
    
    return grads;
}


float *compute_weight_bias(float w, float b, float dj_dw, float dj_db, float alpha){

    /*
    Performs gradient descent to fit w,b. Updates w,b by taking 
    gradient steps with learning rate alpha
    
    Args:
      w,b (scalar): initial values of model parameters  
      alpha (float):     Learning rate
      dj_dw (scalar): The gradient of the cost w.r.t. the parameters w  
      dj_db (scalar): The gradient of the cost w.r.t. the parameters b
      
    Returns:
      w (scalar): Updated value of parameter after running gradient descent
      b (scalar): Updated value of parameter after running gradient descent
      p_hist (ndarray (2,1)): History of parameters [w,b] 

    */

   float *p_hist=(float *)malloc(2*sizeof(float));

    w = w - (alpha*dj_dw);
    b = b - (alpha*dj_db);

    p_hist[0]=w; //weight
    p_hist[1]=b; //bias
    
    return p_hist;
}

float evaluate_model(float x[], float y[], float w, float b, int m){

    /*
    Calculate R squre score for each number of iterations
    
    Args:
      x (ndarray (m,1)):    Data, m examples 
      y (ndarray (m,1)):    target values
      w,b (scalar):         initial values of model parameters  
      m (int):              number of examples
      
    Returns:
      R_square score (scalar): Updated value of R square score in each iterations.
    */

    float f_x=0;
    float f_mean=0;
    float rss=0;
    float tss=0;
    float R_square=0;

    for (int i = 0; i < m; i++)
    {
        f_x = x[i]*w + b;
        rss += pow((f_x - y[i]), 2);
    }
    f_mean = f_x/m;

    for (int i = 0; i < m; i++)
    {
        f_x = x[i]*w + b;
        tss += pow((f_x - f_mean), 2);
    }

    R_square = 1 - (rss/tss);
    
    
    return R_square;
}

