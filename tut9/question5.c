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
	double n = 100000000;
	double dx = 1/(n+1);
	double x=0;
	double y =0;
	#ifdef _OPENMP
    omp_set_num_threads(numThreads);
    #endif
    //FILE *fp;

   	//fp = fopen("calculations.txt", "w+");
    #pragma omp parallel for private(x)
    for (int i = 0; i < 100000000; ++i)
    {
        #pragma omp critical
        {
          #ifdef _OPENMP
            x=dx*i;
            y=exp(x)+cos(x)+sin(x)+sqrt(5*x+6);
            //printf("%f\n",y[i]);
			if(i%1000000==0){
				FILE *fp;

   				fp = fopen("calculations.txt", "a");
   				fprintf(fp, "Current Index:%i,X=%f, Y=%f \n",i,x,y);
   				//fputs("This is testing for fputs...\n", fp);
   				fclose(fp);
			}
          #endif
        }
    }
	//fclose(fp);
}
