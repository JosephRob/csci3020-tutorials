#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*
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
}*/
/*void delay(int time){
    clock_t goal=time+clock();
    while(goal>clock());
}
int bellCurve(int grade){
    return grade*1.5;
}
void * doStudent(void  * arg){
    int grade=*((int *)arg);
    delay(rand()%1000000);
    printf("%d\t%d\n", grade, bellCurve(grade));
}
int main(void){
    srand(clock());
    pthread_t A[5];
    int grade[5]; 
    for(int x=0;x<5;x++){
        printf("input grade %d: ",x);
        int temp;
        scanf("%i", &temp);
        grade[x]=temp;
    }
    for(int x=0;x<5;x++){
        pthread_create(&A[x],NULL,doStudent,(void *)&grade[x]);
    } 
    for(int x=0;x<5;x++){
        pthread_join(A[x],NULL);
    }
}
struct student{
    int grade;
    int ID;
    char name[64];
};
void delay(int time){
    clock_t goal=time+clock();
    while(goal>clock());
}
int bellCurve(int grade){
    return grade*1.5;
}
void * doStudent(void  * arg){
    struct student data=*((struct student *)arg);
    delay(rand()%1000000);
    printf("%s\t%d\t%d\n", data.name,data.ID, bellCurve(data.grade));
}
int main(void){
    srand(clock());
    pthread_t A[5];
    int grade[5]; 
    int studentID[5]; 
    char name[5][64]; 
    for(int x=0;x<5;x++){
        int temp;
        printf("input grade %d: ",x);
        scanf("%i", &temp);
        grade[x]=temp;
        printf("input student ID: ");
        scanf("%i", &temp);
        studentID[x]=temp;
        char tempS[64];
        printf("input name: ");
        scanf("%s", tempS);
        strcpy(name[x],tempS);
        //name[x]=tempS;
    }
    struct student data[5];
    for(int x=0;x<5;x++){
        strcpy(data[x].name,name[x]);
        data[x].ID=studentID[x];
        data[x].grade=grade[x];
    //printf("\t%s\t%d\t%d\n", data.name,data.ID, bellCurve(data.grade));
        pthread_create(&A[x],NULL,doStudent,(void *)&data[x]);
    } 
    for(int x=0;x<5;x++){
        pthread_join(A[x],NULL);
    }
}
int total_grade=0;
int busy=0;
void class_total(int grade){
    total_grade+=grade;
    //printf("%d\t%d\n",grade,total_grade);
}
void * run(void * args){
    while (busy==1);
    busy=1;
    int grade=*((int *)args);
    class_total(grade);
    busy=0;
}
int main(){
    pthread_t A[10];
    int grades[10];
    for (int x=0;x<10;x++){
        int temp;
        printf("input grade %d: ",x);
        scanf("%i", &temp);
        grades[x]=temp;
    }
    for(int x=0;x<10;x++){
        pthread_create(&A[x],NULL,run,(void *)&grades[x]);
    }
    for(int x=0;x<10;x++){
        pthread_join(A[x],NULL);
    }
    printf("total=%d\n",total_grade);

}*/

double total_grade=0;
double total_bell=0;
int busy=0,done=0;
double grades[10];
pthread_barrier_t barrier;
void class_total(double grade){
    total_grade+=grade;
    //printf("%d\t%d\n",grade,total_grade);
}
void bell(double grade){
    total_bell+=grade*1.5;
    FILE * f=fopen("bellcurve.txt","a");
    fprintf(f,"%f\n",(grade*1.5));
    //printf("%d\n",(int)(grade*1.5));
    fclose(f);
} 
void * run(void * args){
    while (busy==1);
    busy=1;
    //printf("%d\n",(int)args);
    double grade=grades[(int)args];
    //printf("%d\n",grade);
    class_total(grade);
    bell(grade);
    busy=0;
}
void * readAll(){
    FILE * in;
    in=fopen("grades.txt","r");
    for (int x=0;x<10;x++){
        float temp;
        //printf("get grade %d \t",x);
        fscanf(in,"%f", &temp);
        grades[x]=temp;
        //printf("%f\t%f\n",temp,grades[x]);
    }
    fclose(in);
    pthread_barrier_wait(&barrier);

}
int main(){
    FILE * out;
    pthread_t A[10];
    pthread_t read;
    pthread_barrier_init(&barrier,NULL,2);
    out=fopen("bellcurve.txt","w");
    fprintf(out,"");
    fclose(out);
    pthread_create(&read,NULL,readAll,NULL);
    //pthread_join(read,NULL);
    pthread_barrier_wait(&barrier);

    //barrier here

    for(int x=0;x<10;x++){
        pthread_create(&A[x],NULL,run,(void *)x);
    }
    for(int x=0;x<10;x++){
        pthread_join(A[x],NULL);
    }
    out=fopen("bellcurve.txt","a");
    printf("total=%f\n",total_grade);
    printf("total bell=%f\n",total_bell);
    printf("average=%f\n",total_grade/10.0);
    printf("average bell=%f\n",total_bell/10.0);
    fclose(out);
}