#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>


int main(int argc, char *argv[]){
    int numThreads=1;
    if (argc>1){
        numThreads=atoi(argv[1]);
    }
    printf("%i\n",numThreads);
    double n = 100000000;
    double y[100000000];
    double dx=1/(n+1);
    double x;
    #ifdef _OPENMP
    omp_set_num_threads(numThreads);
    #endif
    
    #pragma omp parallel for private(x)
    for (int i = 0; i < 100000000; ++i)
    {
        #pragma omp critical
        {
          #ifdef _OPENMP
            x=dx*i;
            y[i]=exp(x)+cos(x)+sin(x)+sqrt(5*x+6);
            printf("%f\n",y[i]);
          #endif
        }
    }
}