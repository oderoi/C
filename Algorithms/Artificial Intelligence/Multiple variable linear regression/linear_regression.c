#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define m 100
#define n 4
#define lr 1e-7
#define num_iter 1000
#define num_col_x 5
#define col_y 4
#define FILE_NAME "data/houses.txt"

float **load_data(const char *file_id);

double *predict(float **x, double w[][1], double b);
double compute_cost(float **x, float y[m], double w[][1], double b);
double *compute_gradient(float **x, float y[m], double w[][1], double b);
double r_squared(float **x, float y[m], double w[][1], double b);


int main(){
    
    float **data=load_data(FILE_NAME);
    if (data == NULL)
    {
        return EXIT_FAILURE;
    }
    
    //alocate the memory for the input array dynamically
    float **x=(float **)malloc(m*sizeof(float *));
    for (int i = 0; i < m; i++)
    {
       x[i] = (float *)malloc(n*sizeof(float));
       if (x==NULL)
       {
        perror("Error in locatting memory");
        for (int j = 0; j < i; j++)
        {
           free(x[j]);
        }
        free(x); 
       }
    }

    //allocate the memory for the output array dynamically
    float *y=(float *)malloc(m*sizeof(float));
    if (y==NULL)
    {
        perror("Error in allocating memory");
        free(y);
    }
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            x[i][j] = data[i][j];
        }
        y[i] = data[i][col_y];  
    }

    double b_init = 785.1811367994083;
    double w_init[][1] = { 0.39133535, 18.75376741, -53.36032453, -26.42131618};

    for (int i = 0; i < num_iter; i++)
    {
        //compute cost
        double J_wb=compute_cost(x, y, w_init, b_init);

        // Calculate the gradient and update the parameters using gradient_function
        double *grads=compute_gradient( x, y, w_init, b_init);

        //R_Squared
        double r_square=r_squared( x, y, w_init, b_init);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                w_init[i][j] = w_init[i][j] - (lr * grads[i]);
            }   
        } 
        b_init =b_init - (lr * grads[n]);

        // Print cost every at intervals 10 times
        if (ceil(i%10)==0)
        {
            printf("Iter: %5d\t Cost: %10e\t R_Square: %10e\n ", i, J_wb, r_square);
        }     
    }

    //free the allocated memory
    for (int i = 0; i < m; i++)
    {
        free(data[i]);
        free(x[i]);
    }
    free(data);
    free(x);
    free(y);
    return 0;
}

float **load_data(const char *file_id){

    /*
    load dataset in '.txt' file
    
    Args:
      file_id (char): FILE_NAME   
      
    Returns:
      data (ndarray):  shape(m, num_col_x)
    
    */

    FILE *file = fopen(file_id, "r");
    if (file==NULL)
    {
        perror("Error opening file");
        return NULL;
    }
    
    //alocate the memory for the data array dynamically
    float **data=(float **)malloc(m*sizeof(float *));
    if (data==NULL)
    {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }
    
    for (int i = 0; i < m; i++)
    {
       data[i] = (float *)malloc(num_col_x*sizeof(float));

       if (data[i]==NULL)
       {
            perror("Error allocating memory");
            for (int j = 0; j < i; j++)
            {
                free(data[j]);
            }
            free(data);
            fclose(file);
            return NULL;
       }
       
    }
    
    //read the data into the array
    for (int i = 0; i < m; i++)
    {
        if (fscanf(file, "%e, %e, %e, %e, %e", &data[i][0], &data[i][1], &data[i][2], &data[i][3], &data[i][4]) != 5)
        {
            fprintf(stderr, "Error reading data at row: %d\n", i);
        
        //free allocated memory before exiting due to error
        for (int j = 0; j <= i; j++)
        {
            free(data[j]);
        }
        free(data);
        fclose(file);
        return NULL;
        }
        
    }

    fclose(file);

    

    return data;
}

double *predict(float **x, double w[][1], double b){

    /*
    single predict using linear regression
    
    Args:
      x (ndarray): Shape (m, n) example with multiple features
      w (ndarray): Shape (n, 1) model parameters    
      b (scalar):  model parameter     
      
    Returns:
      p (scalar):  prediction
    
    */

    double p;
    double *f_wb=(double *)malloc(m*sizeof(double));
    if (f_wb==NULL)
    {
        perror("Error allocating memory");
        free(f_wb);
    }
    

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 1; j++)
        {   
            p=0;
            for (int k = 0; k < n; k++)
            {
                p += (double)x[i][k]*w[k][j];
            }
            p += b;
            f_wb[i]=p;
            
        }
        
    }
    
    return f_wb;
}


double compute_cost(float **x, float y[m], double w[][1], double b){
    
    /*
     compute cost
    Args:
      X (ndarray (m,n)): Data, m examples with n features
      y (ndarray (m,1)) : target values
      w (ndarray (n,1)) : model parameters  
      b (scalar)       : model parameter
      
    Returns:
      cost (scalar): cost
    
    */

    double cost=0;
    double p;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            p=0;
            for (int k = 0; k < n; k++)
            {
                p += (double)x[i][k]*w[k][j];
            }
            p +=b;
        }
        cost += pow((p - (double) y[i]), 2);
    }
    cost /= (2*m);

    return cost;
}


double *compute_gradient(float **x, float y[m], double w[][1], double b){
    /*

    Computes the gradient for linear regression 
    Args:
      X (ndarray (m,n)): Data, m examples with n features
      y (ndarray (m,1)) : target values
      w (ndarray (n,1)) : model parameters  
      b (scalar)       : model parameter
      
    Returns:
      dj_dw (ndarray (n,1)): The gradient of the cost w.r.t. the parameters w. 
      dj_db (scalar):       The gradient of the cost w.r.t. the parameter b. 

      grads (ndarray ((n+1), 1)): dj_dw and dj_db. 
    */

    double *grads=(double *)malloc((n + 1)*sizeof(double));
    if (grads ==NULL)
    {
        perror("Error in allocating memory");
        free(grads);
    }

    double *f_wb=(double *)malloc(m*sizeof(double));
    if (f_wb ==NULL)
    {
        perror("Error in allocating memory");
        free(f_wb);
    }
    
    double p;
    double dj_dw;
    double dj_db=0;
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            p=0;
            for (int k = 0; k < n; k++)
            {
                p += x[i][k]*w[k][j];
            }
            p += b;
            f_wb[i]=p;
        }

        dj_db += f_wb[i] - y[i];
    }
    dj_db /= m;


    for (int i = 0; i < n; i++)
    {
        dj_dw=0;
        for (int j = 0; j < m; j++)
        {
            dj_dw += (f_wb[j] - y[j])*x[j][i];
        }
        dj_dw /= m;

        grads[i]=dj_dw;       
    }

    grads[n]=dj_db;

    free(f_wb);

    return grads;
}


double r_squared(float **x, float y[m], double w[][1], double b){

    /*

    Computes the gradient for linear regression 
    Args:
      X (ndarray (m,n)): Data, m examples with n features
      y (ndarray (m,1)) : target values
      w (ndarray (n,1)) : model parameters  
      b (scalar)       : model parameter
      
    Returns:
      r_square (scalar): r square score.
      r_square = (1 - rss/tss) 
      rss : measure of sum diff btn actual(y) value and predicted(f_wb) value.(y - f_wb)
      tss : measure of total variance in actual(y) value. (y - f_mean)
    
    */

    double r_square;
    double f_wb;
    double y_mean;
    double y_sum;
    double rss;
    double tss;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            f_wb=0;
            for (int k = 0; k < n; k++)
            {
                f_wb += x[i][k]*w[k][j];
            }
            f_wb +=b;
        }

        rss += pow((y[i] - f_wb), 2);
        y_sum += y[i];
        
    }
    y_mean = y_sum/m;

    for (int i = 0; i < m; i++)
    {
        tss += pow((y[i] - y_mean), 2);
    }
    
    r_square = 1 - (rss/tss);


    return r_square;
}