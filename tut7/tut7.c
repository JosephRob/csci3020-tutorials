#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>

struct proc{
    char name[256];
    int priority;
    int pid;
    int runtime;
};
struct queue{
    struct proc process;
    struct queue * next;
};
struct queue base;
void push(struct proc process){
    printf("%s\n",process.name);
    struct queue A;
    A.process = process;
    A.next=base.next;
    base.next=&A;

    //printf("|%s|\n",(*base.next).process.name);
}
void print(struct queue * thisOne){
    if((*thisOne).next!=NULL){
    printf("%s\n",(*thisOne).process.name);

        print((*thisOne).next);
    }
}
int main(){
    char name [256];
    int priority;
    int pid;
    int runtime;
    int size=10;
    freopen("processes.txt","r",stdin);
    for(int x=0;x<size;x++){
        scanf("%s,",name);
        scanf("%i,",&priority);
        scanf("%i,",&pid);
        scanf("%i",&runtime);
        struct proc process;
        strcpy(process.name,name);
        process.priority=priority;
        process.pid=pid;
        process.runtime=runtime;
        push(process);
    }
    //printf("\n");
    
    print(base.next);
}