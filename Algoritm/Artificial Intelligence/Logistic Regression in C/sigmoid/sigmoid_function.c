#include<stdio.h>
#include <stdlib.h>
#include<math.h>

float *predict(float *x, int *w, int b, int m, int n);
float *sigmoid(float *p, int );
void save_data(float p[],const char * file_id, int num);

int main(){
    // input 
    float x_train[]={0,1,2,3,4,5,6,7,8,9};
    int y_train[]={0,0,0,0,0,1,1,1,1,1};

    // weight and bias
    int w_in[]={0};
    int b_in=0;

    // number of examples, m, n
    int m = sizeof(x_train)/sizeof(x_train[0]);
    int n=sizeof(x_train[0])/sizeof(x_train[0]);

    printf("m: %d\t n: %d\n", m,n); 
    
    float *p=predict(x_train, w_in, b_in, m, n);
    float *g_p=sigmoid(p, m);

    //print prediction (sigmoid)
    for (int i = 0; i < m; i++)
    {
         printf("prediction[%d]: %f\n",i, g_p[i]);
    }

    //save input data used here
    save_data(x_train, "data/x_train.txt", m);

    //save predicted values
    save_data(p, "data/pred.txt", m);

    //save predicted values from sigmoid function
    save_data(g_p, "data/pred_sig.txt", m);
    
    return 0;
}


float *predict(float *x, int *w, int b, int m , int n){

    /*
    args:
        x: (ndarray (m,)): input training data
        w (ndarray (n, )): weight parameter
        b (scalar): bias parameter
        m (scalar): number of examples
        n (scalar): number of features

    return:
        p (ndarray (m,)): model preiction return single value
    
    */

    float *p=(float *)calloc(m, sizeof(float ));
        if (p==NULL)
        {
            perror("error in allocating memory");
            free(p);
        } 
        

    for (int i = 0; i < m; i++)
    { 
        p[i]=x[i] * (float)w[n]+b;
        
    }
    
    return p;
}


float *sigmoid(float *p, int m){

    /*
    args:
        p (scalar): prediction of single example

    return:
        g_y (scalar): sigmoid of a single prediction
    */

    float *g_y=(float *)calloc(m, sizeof(float));

    for (int i = 0; i < m; i++)
    {
        g_y[i]= 1 / (1 + exp(-p[i]));
    }
   

    return g_y ;
}

void save_data(float p[],const char * file_id, int num){

    /*
    args:
        p (ndarray (m,)): array
        filename (char): file_path to save

    return:
        
    */

    FILE *file=fopen(file_id, "w");

    for (int i = 0; i < num; i++)
    {
        fprintf(file, "%e", p[i]);
        fprintf(file, "\n");
    }

    fclose(file);

    return ;
}