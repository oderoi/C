#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define m 5
#define n 3

struct reg_grads{
    double *dj_dw;
    double dj_db;
};


double compute_cost_linear_reg(float X[][n], int y[], double w[][1], double b, float lambda_);
struct reg_grads compute_gradient_linear_reg(float X[][n], int y[], double w[][1], double b, float lambda_);

double compute_cost_logistic_reg(float X[][n], int y[], double w[][1], double b, float lambda_);
struct reg_grads compute_gradient_logistic_reg(float X[][n], int y[], double w[][1], double b, float lambda_);
double sigmoid(double z);

int main(){
    float X[][n]={{4.17022005e-01, 7.20324493e-01, 1.14374817e-04},
                  {1.86260211e-01, 3.45560727e-01, 3.96767474e-01},
                  {2.04452250e-01, 8.78117436e-01, 2.73875932e-02},
                  {1.40386939e-01, 1.98101489e-01, 8.00744569e-01},
                  {8.76389152e-01, 8.94606664e-01, 8.50442114e-02}}; 
    
    double w[][1] = {-0.40165317, -0.07889237,  0.45788953};

    int y[] = {0, 1, 0, 1, 0};

    double b = 0.5;
    float lambda_ = 0.7;

    
    double cost = compute_cost_logistic_reg( X, y, w, b, lambda_);

    printf("Regularized cost: %f\n", cost);
    
    return 0;
}

double compute_cost_linear_reg(float X[][n], int y[], double w[][1], double b, float lambda_){
    /*
    compute regularized linear cost
    Args:
        X (ndarray(m,n)): Data with m examples and n feature
        y (ndarray(n,)): target
        w (ndarray(n,)): model parameters
        b (scallar): model parameter
        lambda_ (scalar): control amount of regularization

    Return:
        total_cost (scallar): cost
    */

    double f_wb_i;
    double f_wx;
    double cost=0;
    double reg_cost;
    double total_cost=0;

    for (int i = 0; i < m; i++)
    {
       for (int j = 0; j < 1; j++)
       {
            f_wx = 0;
            f_wb_i=0;
            for (int k = 0; k < n; k++)
            {
                f_wx += X[i][k]*w[k][j];
            }
            f_wb_i = f_wx + b;
            cost +=pow((f_wb_i - y[i]),2);
        
       }
       
    }
    cost = cost/(2*m);

    reg_cost = 0;
    for (int i = 0; i < n; i++)
    {
        reg_cost += pow(w[i][0], 2);
    }
    reg_cost = reg_cost * (lambda_/(2*m));

    total_cost = cost + reg_cost;
    
    return total_cost;
}

double sigmoid(double z){

    /*
    Compute sigmoid
    Arg:
        z (scalar):  prediction
    Return:
        logistic prediction
    */

    return 1/(1 + exp(-z));
}

double compute_cost_logistic_reg(float X[][n], int y[], double w[][1], double b, float lambda_){

    /*
    compute regularized linear cost
    Args:
        X (ndarray(m,n)): Data with m examples and n feature
        y (ndarray(n,)): target
        w (ndarray(n,)): model parameters
        b (scallar): model parameter
        lambda_ (scalar): control amount of regularization

    Return:
        total_cost (scallar): cost
    */

    double cost=0;
    double f_wx;
    double f_wb;
    double reg_cost;
    double total_cost;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            f_wx=0;
            f_wb=0;
            for (int k = 0; k < n; k++)
            {
                f_wx += X[i][k] * w[k][j];
            }
            f_wb = sigmoid(f_wx + b);
            
        }
        cost += (-y[i]*log(f_wb)) - ((1-y[i])*log(1-f_wb));
        
    }
    cost /= m;

    reg_cost=0;
    for (int i = 0; i < n; i++)
    {
        reg_cost += pow(w[i][0], 2);
    }
    reg_cost = (lambda_ /(2*m))*reg_cost;
    
    total_cost = cost + reg_cost;

    return total_cost;
}


struct reg_grads compute_gradient_linear_reg(float X[][n], int y[], double w[][1], double b, float lambda_){
    /*
    Compute the gradient for linear regression
    Args:
      X (ndarray (m,n): Data, m examples with n features
      y (ndarray (m,)): target values
      w (ndarray (n,)): model parameters  
      b (scalar)      : model parameter
      lambda_ (scalar): Controls amount of regularization
      
    Returns:
      dj_dw (ndarray (n,)): The gradient of the cost w.r.t. the parameters w. 
      dj_db (scalar):       The gradient of the cost w.r.t. the parameter b.
    */

    struct  reg_grads grads;

    double f_wx;
    double *err = (double *)calloc(m, sizeof(double));
    grads.dj_dw = (double *)calloc(n, sizeof(double));
    grads.dj_db=0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            f_wx=0;
            for (int k = 0; k < n; k++)
            {
                f_wx += X[i][k] * w[k][j];
            }
            err[i] = ((f_wx + b) - y[i]); 
            grads.dj_db =grads.dj_db + err[i];   
        }
        
    }
    grads.dj_db =grads.dj_db/ m;


    for (int j = 0; j < n; j++)
    {
        grads.dj_dw[j]=0;
        for (int i = 0; i < m; i++)
        {
            grads.dj_dw[j] = grads.dj_dw[j] + (err[i]*X[i][j]);
        }
        grads.dj_dw[j] = grads.dj_dw[j]/ m;
        grads.dj_dw[j] += (lambda_*w[j][0]/m);
        
    }

    free(err);
       
    return grads;
}


struct reg_grads compute_gradient_logistic_reg(float X[][n], int y[], double w[][1], double b, float lambda_){
    /*
    Compute the gradient for linear regression
    Args:
      X (ndarray (m,n): Data, m examples with n features
      y (ndarray (m,)): target values
      w (ndarray (n,)): model parameters  
      b (scalar)      : model parameter
      lambda_ (scalar): Controls amount of regularization
      
    Returns:
      dj_dw (ndarray (n,)): The gradient of the cost w.r.t. the parameters w. 
      dj_db (scalar):       The gradient of the cost w.r.t. the parameter b.
    */

    struct reg_grads grads;

    grads.dj_db=0;
    grads.dj_dw = (double *)calloc(n, sizeof(double));
    double f_wx;
    double f_wb;
    double *err = (double *)calloc(m, sizeof(double));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            f_wx=0;
            f_wb=0;
            for (int k = 0; k < n; k++)
            {
                f_wx += X[i][k]*w[k][j];
            }
            f_wb = sigmoid(f_wx + b);
            
        }
        err[i] = (f_wb - y[i]);

        grads.dj_db += err[i];
        
    }

    grads.dj_db = grads.dj_db / m;

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            grads.dj_dw[j] += (err[i]*X[i][j]);
        }

        grads.dj_dw[j] /=m;

        grads.dj_dw[j] += (lambda_/m)*w[j][0];
        
    }
    
    
    return grads;
}
