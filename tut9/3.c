#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

int main (int argc, char *argv[])
{
    int numThreads=1;
    if (argc>1){
        numThreads=atoi(argv[1]);
    }
    printf("%i\n",numThreads);
    double x[100000000];
    srand(12);
    for(int i=0;i<100000000;i++){
        x[i]=rand();
    }
    double norm=0;
    double time=omp_get_wtime(); 
    for (int i = 0; i < 100000000; ++i)
    {
        norm+=fabs(x[i]);
    }
    printf("%f\n",omp_get_wtime()-time);
    norm=0;
    #ifdef _OPENMP
    omp_set_num_threads(numThreads);
    #endif
    time=omp_get_wtime();
    #pragma omp parallel for reduction(+: norm)
    for (int i = 0; i < 100000000; ++i)
    {
        norm+=fabs(x[i]);
    }
    printf("%f\n",omp_get_wtime()-time);
}