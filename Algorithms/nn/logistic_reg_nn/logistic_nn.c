#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nx 12288
#define m 209
#define l_rate 1e-2
#define num_iters 10000

struct grads {
    double *djdw;
    double djdb;
    double cost;
};

struct  caches
{
    double *w;
    double b;
    double *costs;
};


float **load_X(const char *filename);
int *load_y(const char *filename);
double sigmoid(double z);
double compute_cost(float **X, double *w, double b, int *y);
struct grads propagate(float **X, double *w, double b, int *y);
double *deepcopy(double *src);
struct caches optimize(double *w, double b, float **X, int *y);
int *prediction(double *w, double b, float **X);

int main(){

    double *w_in=(double *)calloc(nx, sizeof(double));
    if(w_in==NULL){
        perror("Memory allocation failed for w_in");
        return 1;
    }

    for (int i = 0; i < nx; i++)
    {
        w_in[i]=0;
    }

    float **X_in=load_X("datasets/train_set_x.txt");
    int *y_in=load_y("datasets/train_set_y.txt");

    double b_in=0;

    struct caches cache;
    cache = optimize(w_in, b_in, X_in, y_in);
    
    for (int i = 0; i < m; i++)
    {
        free(X_in[i]);
    }

    free(X_in);
    free(y_in);
    // free(cache.w);
    free(w_in);
    // free(cache.costs);
 
    return 0;
}


float **load_X(const char *filename){

    FILE *file=fopen(filename, "r");
    if (file==NULL)
    {
        perror("Error opening file");
        return NULL;
    }
    

    float **data_x=(float **)calloc(m, sizeof(float *));
    if (data_x == NULL)
    {
        printf("Error in allocating memory");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < m; i++)
    {
        data_x[i]=(float *)calloc(nx, sizeof(float));
        if (data_x[i]==NULL)
        {
            printf("Error in memory allocation, %d", i);
            for (int j = 0; j < i; j++)
            {
                free(data_x[j]);
            }
            free(data_x);
            fclose(file);
            return NULL;
            
        }
        
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            if (fscanf(file, j < nx-1 ? "%f," : "%f", &data_x[i][j]) != 1)
            {
                printf("Error in reading file at, i=%d, j=%d", i,j);
                fclose(file);
                return NULL;
            }
            
        }
        
    }

    fclose(file);

    return data_x;
}


int *load_y(const char *filename){

    FILE *file=fopen(filename, "r");
    if (file==NULL)
    {
        perror("Error opening file");
        return NULL;
    }
    

    int *data_y=(int *)calloc(m, sizeof(int));
    if (data_y == NULL)
    {
        printf("Error in allocating memory");
        // free(data_y);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < m; i++)
    {
    
        if (fscanf(file, i < m-1 ? "%d," : "%d", &data_y[i])!=1)
        {
            printf("Error in reading file at, i=%d,", i);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);

    return data_y;
}


double *deepcopy(double *src){
    double *dest = (double *)calloc(nx, sizeof(double));
    if (dest==NULL)
    {
        perror("error in allocating memory");
        free(dest);
    }
    
    for (int i = 0; i < nx; i++)
    {
        dest[i]=src[i];
    }

    return dest;
}


double sigmoid(double z){
    /*
    Arg: 
        z - scalar

    Return:
        sigmoid - scalar
    */
    return (1/(1+exp(-z)));
}


double compute_cost(float **X, double *w, double b, int *y){

    /*
    Args:
        X: (nx, m)
        w: (nx, 1)
        y: (1, m)
        b: (1)scalar

    Return:
        cost: (1)scalar
    */


    double fx;
    double cost=0;
    double A;

    for (int i = 0; i < m; i++)
    {
        fx=0;
        for (int j = 0; j < nx; j++)
        {
            fx += X[i][j]*w[j];
        }
        fx =fx + b;
        A=sigmoid(fx);
        cost += ((-y[i]*log(A)) - ((1-y[i])*log(1-A)));
        
    }
    cost /=m;
    
    return cost;
}


struct grads propagate(float **X, double *w, double b, int *y){

    /*
    Args:
        X: (nx, m)
        w: (nx, 1)
        y: (1, m)
        b: (1)scalar

    Return:
        dw: (nx,1)
        db: (1)scalar
        cost: (1)scalar
    */

    struct grads grad;

    double fx;
    double A;
    grad.cost = 0.0;
    grad.djdw = (double *)calloc(nx, sizeof(double));
    double *djdz=(double *)calloc(m, sizeof(double));

    grad.djdb=0;
    
    for (int i = 0; i < m; i++)
    {
        fx=0;
        for (int j = 0; j < nx; j++)
        {
            fx += w[j]*X[i][j];
        }
        fx =fx + b;
        A = sigmoid(fx);

        grad.cost += ((-y[i]*log(A)) - ((1-y[i])*log(1-A)));

        djdz[i] = A - y[i];
        grad.djdb += djdz[i];
        
    }
    grad.djdb /= m;
    grad.cost /= m;

    for (int i = 0; i < nx; i++)
    {
        grad.djdw[i]=0;
        for (int j = 0; j < m; j++)
        {
            grad.djdw[i] = grad.djdw[i] + (djdz[j] * X[j][i]);
        }
        grad.djdw[i] /= m;    

    }


    //free memory
    free(djdz);
    
    return grad;
}

struct caches optimize(double *w_in, double b_in, float **X_in, int *y_in){
    struct caches cache;
    struct grads grad;

    
    cache.w = deepcopy(w_in);
    cache.b = b_in;
    cache.costs = (double *)calloc(num_iters, sizeof(double));

    for (int i = 0; i < num_iters; i++)
    {
        grad = propagate(X_in, cache.w, cache.b, y_in);

        // double cost = compute_cost(X_in, cache.w, cache.b, y_in);

        for (int j = 0; j < nx; j++)
        {
            cache.w[j] = cache.w[j] - (grad.djdw[j] * l_rate);
            
        }
        cache.b = cache.b - (grad.djdb * l_rate);

        cache.costs[i]=grad.cost;

        if (i%(num_iters/100)==0)
        {
            printf("Iter %d \t Cost %f\n", i, grad.cost);
        }

        // for (int i = 0; i < 10; i++)
        // {
        //     printf("dw[%d]: %f\n", i, grad.djdw[i]);
        // }
        
        
    }


    free(grad.djdw);
       
    return cache;
}

int *prediction(double *w, double b, float **X){

    /*
    Args:
        w (ndarray) -> (nx,)
        b (scalar) -> (1)
        X (ndarray) -> (m, nx)

    Return:
        prediction (ndarray) -> (m,)
    */

   double fx;
   double A;
   int *pred = (int *)calloc(m, sizeof(int));

   for (int i = 0; i < m; i++)
   {
        fx=0;
        for (int j = 0; j < nx; j++)
        {
            fx +=w[j] * X[i][j];  
        }
        fx = fx + b;
        A = sigmoid(fx);

        pred[i] = A>0.5? 1: 0;
        
   }

   return pred;
   
}