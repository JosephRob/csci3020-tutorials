#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/types.h>
/*
int main(void){
    pid_t pid1=0, pid2=0;
    pid1=fork();
    if (pid1==0){
        pid2=fork();
    }
    if(pid1==0){
        freopen("child1.txt","w",stdout);
        printf("child1\n");
        freopen("/dev/tty","a+",stdout);
        freopen("child1.txt","r",stdin);
        char line[64];
        scanf("%s",line);
        freopen("/dev/tty","r",stdin);
        printf("%s\n",line);        
    }
    else if (pid2==0){
        freopen("child2.txt","w",stdout);
        printf("child2\n");
        freopen("/dev/tty","a+",stdout);
        freopen("child2.txt","r",stdin);
        char line[64];
        scanf("%s",line);
        freopen("/dev/tty","r",stdin);
        printf("%s\n",line);
        exit(0);
    }
    return 0;
}
int main(void){
    pid_t pid1=0;
    int status=0;
    pid1=fork();
    if (pid1>0){
        wait(NULL);
        printf("parent process\n");
    }
    else if(pid1==0){
        sleep(1);
        printf("child process\n");
        exit(0);
    }
}*/
int movingSum[5]={0,0,0,0,0};
struct fact{
    int number;
    int index;
};
void * run(void* args){
    struct fact number;
    int sum=1;
    for(int x=2;x<number.number;x++){
        sum*=x;
    }
    if(number.index>0){
        do {
            if(movingSum[number.index-1]>0){
                sum+=movingSum[number.index-1];
                movingSum[number.index]+=sum;
            }
        }
        while(movingSum[number.index]<=0);
    }
}
int main(void){
    pthread_t A[5];
    for(int x=0;x<5;x++){
        scanf("%d",&movingSum[x]);
    }
    for(int x=0;x<5;x++){
        struct fact number;
        number.number=movingSum[x];
        number.index=x;
        pthread_create(&A[x],NULL,run,(void *) &number);
    }
    for(int x=0;x<5;x++){
        pthread_join(A[x],NULL);
    }
}