#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

int main (int argc, char *argv[]){
	int numThreads=1;
    if (argc>1){
        numThreads=atoi(argv[1]);
    }

	int	tid, nthreads, i, j, k, chunk;
	double a[100][100];
	double b[100][100];
	double c[100][100];
	chunk = 10;
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
	{
		#ifdef _OPENMP
    	omp_set_num_threads(numThreads);
   		#endif
		//omp_set_num_threads(numThreads);
		//tid = omp_get_thread_num();
  		//if (tid == 0){
   			//nthreads = omp_get_num_threads();
   		//}
		#pragma omp for schedule (static, chunk) 
  		for (i=0; i<100; i++)
    		for (j=0; j<100; j++)
      			a[i][j]= i+j;
  		#pragma omp for schedule (static, chunk)
  		for (i=0; i<100; i++)
    		for (j=0; j<100; j++)
      			b[i][j]= i*j;
  		#pragma omp for schedule (static, chunk)
 		for (i=0; i<100; i++)
    		for (j=0; j<100; j++)
      			c[i][j]= 0;
		#pragma omp for schedule (static, chunk)
 		for (i=0; i<100; i++){
    	//printf("Thread=%d did row=%d\n",tid,i);
    		for(j=0; j<100; j++)       
      			for (k=0; k<100; k++)
        			c[i][j] += a[i][k] * b[k][j];   
  		} 
	}
	printf("Result Matrix:\n");
	for (i=0; i<100; i++){
  		for (j=0; j<100; j++){ 
    		printf("%6.2f   ", c[i][j]);
		}
  		printf("\n"); 
	}
}
