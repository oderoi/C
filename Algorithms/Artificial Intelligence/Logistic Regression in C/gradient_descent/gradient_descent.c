#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define m 6
#define n 2

struct Grads{
    double *djdw;
    double djdb;
} ;

struct caches{
    double *J_history;
    double **w;
    double b;
};

double **deepcopy(double **src);
double compute_cost_logistic(float x[][n], int y[], double **w, double b);
struct Grads compute_gradient_logistic(float x[][n], int y[], double **w, double b);
struct caches gradient_descent(float x_in[][n], int y_in[], double **w_in, double b_in, float alpha, int num_iters);


int main(){

    float X_train[][n] = {{0.5, 1.5}, {1, 1}, {1.5, 0.5}, {3, 0.5}, {2, 2}, {1, 2.5}};
    int y_train[] = {0, 0, 0, 1, 1, 1};

    double **w_init=(double **)calloc(n, sizeof(double *));
    if (w_init == NULL)
    {
        perror("Error in allocating memory");
    }
    for (int i = 0; i < n; i++)
    {
        w_init[i] = (double *)calloc(1, sizeof(double));
        if (w_init[i]==NULL)
        {
            perror("Error in allocating memory");
            for (int j = 0; j < i; j++)
            {
                free(w_init[j]);
            }
            free(w_init);
            
        }
        w_init[i][0] = 0;
        
    }

    double b_init = 0;
    double alpha=1e-1;
    int num_iters=100000;

    struct caches cache;
    cache = gradient_descent(X_train, y_train, w_init, b_init, alpha, num_iters);

    printf("updated parameters: "); 
        for (int i = 0; i < n; i++)
        {
            printf("w[%d]: %f \t", i, cache.w[i][0]);
        }
        printf("b: %f\n", cache.b);

    for (int i = 0; i < n; i++)
    {
        free(w_init[i]);
        free(cache.w[i]);
    }
    free(cache.w);
    free(w_init);
    free(cache.J_history);
    
    return 0;
}



double **deepcopy(double **src){

    double **dest=(double **)calloc(n, sizeof(double *));
    if (dest==NULL)
    {
        perror("Error in alllocating memory");
    }
    for (int i = 0; i < n; i++)
    {
        dest[i] = (double *)calloc(1, sizeof(double));

        if (dest[i]==NULL)
        {
            perror("Error in allocating memory");
            for (int j = 0; j < i; j++)
            {
                free(dest[i]);
            }
            
            free(dest);
        }
        for (int j = 0; j < 1; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
    
    
    return dest;
}



double sigmoid(double z){
    /*
    compute sigmoid

    Args:
        z (scalar):  logistic function, f_wb

    Return:
        g (scalar):  sigmoid of f_wb
    */

    return 1 / (1 + exp(-z));
}

double compute_cost_logistic(float x[][n], int y[], double **w, double b){

    /*
    Compute cost
    Args:
        X (ndarray (m,n)):  input data 
        y (ndarray (m,)):   output data
        w (ndarray (n,)):   model parametrs 
        b (scalar):         model parameter

    Return:
        J (sclar):  Cost of logistic model
    */

    double J=0;
    double f_x;
    double f_wb;
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            f_wb = 0;
            f_x=0;
            for (int k = 0; k < n; k++)
            {
                f_x += x[i][k] * w[k][j];
            }
            f_x +=b;
            f_wb = sigmoid(f_x);
            J += (-y[i]*log(f_wb)) - ((1 - y[i])*log(1 - f_wb));
            
        }
        
    }
    J /= m;
    
    return J;
}


struct Grads compute_gradient_logistic(float x[][n], int y[], double **w, double b){
    /*
     Computes the gradient for linear regression

    Args:
        X (adarray (m,n)):  Data, m examples with n features
        y (ndarray (m,)):  target values
        w (ndarray (n,)):  model parameters
        b (scalar)       :  model parameter

    Returns:
        dj_dw (ndarray (n, )):  The gradient of the cost w.r.t the parameters w.
        dj_db (scalar)       :  The gradient of the cost w.r.t the parameter b.
    */

   struct Grads grads;

    double f_wx;
    double *f_wb = (double *)calloc(m, sizeof(double));
    double err;
    grads.djdw = (double *)calloc(n, sizeof(double));
    grads.djdb=0;

    for (int i = 0; i < m; i++)
    {
        f_wx=0;
        f_wb[i]=0;
        for (int j = 0; j < 1; j++)
        {
            for (int k = 0; k < n; k++)
            {
                f_wx += x[i][k] * w[k][j];
            }
             
        }
        f_wb[i] = sigmoid(f_wx + b);
        err = f_wb[i] - y[i];
        grads.djdb += err;
    }

    grads.djdb /= m;

    for (int i = 0; i < n; i++)
    {
        grads.djdw[i]=0;
        for (int j = 0; j < m; j++)
        {
            grads.djdw[i] += (f_wb[j] - y[j])*x[j][i];
        }
        grads.djdw[i] /= m;
       
    }

    free(f_wb);
    
    return grads;
}

struct caches gradient_descent(float x_in[][n], int y_in[], double **w_in, double b_in, float alpha, int num_iters){

    /*
     Performs batch gradient descent
    
     Args:
      X (ndarray (m,n)   : Data, m examples with n features
      y (ndarray (m,))   : target values
      w_in (ndarray (n,)): Initial values of model parameters  
      b_in (scalar)      : Initial values of model parameter
      alpha (float)      : Learning rate
      num_iters (scalar) : number of iterations to run gradient descent
      
    Returns:
      w (ndarray (n,))   : Updated values of parameters
      b (scalar)         : Updated value of parameter 
    */
    
    struct caches cache; 
    struct Grads grads;

    cache.J_history = (double *)calloc(num_iters, sizeof(double));
    cache.w = deepcopy(w_in);                   //avoid modifying global w within function
    cache.b=b_in;
    
    for (int i = 0; i < num_iters; i++)
    {
        //calculate gradient and update the parameters
        grads=compute_gradient_logistic(x_in, y_in, cache.w, cache.b);

        //update parameters using w, b, alpha and gradient
        for (int j = 0; j < n; j++)
        {
            cache.w[j][0] = cache.w[j][0] - (grads.djdw[j] * alpha);
        }
        cache.b = cache.b - (grads.djdb * alpha);

        double J=compute_cost_logistic(x_in, y_in, cache.w, cache.b);
        
        cache.J_history[i] = J;

        if (i % (num_iters / 10)==0)
        {
        printf("Iteration %d \t Cost %f\n", i, cache.J_history[i]);
        } 

    }

    return cache;
}
