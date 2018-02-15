#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void delay(int time){
    clock_t goal=time+clock();
    while(goal>clock());
}
void * hello(void * args){
    delay(rand()%1000000);
    printf("hello world\n");
    return NULL;
}
void * bye(void * args){
    delay(rand()%1000000);
    printf("goodbye\n");
    return NULL;
}
int main(void){
    srand(clock());
    printf("%d %d\n",clock(),rand);
    pthread_t A,B;
    pthread_create(&A, NULL, hello, NULL);
    pthread_create(&B, NULL, bye, NULL);
    pthread_join(A,NULL);
    pthread_join(B,NULL);
}
/*
void * doStudent(void  * arg){

}
int main(void){
    pthread_t A[5];
    double grade[5]; 
    for(int x=0;x<5;x++){
        scanf('%d', grade[x]);
    }
    for(int x=0;x<5;x++){
        pthread_create(A[x],NULL,doStudent,grade[x]);
    } 
    for(int x=0;x<5;x++){
        pthread_join(A[x],NULL);
    }
}*/